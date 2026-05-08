/*

                                SCRIPTKIT OFFICIAL DLL SOURCE

                     =====================================================

                                        Version: 0.0.1
                            Description: basic maleware functionality.
        Method: Connects using TCP, lists system specs and sends it through discord webhook.

*/

#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

extern "C" __declspec(dllexport) void msgBox(const char* message)
{
    MessageBoxA(NULL, message, "Scriptus", MB_OK);
}

std::string getCPU() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    std::ostringstream oss;
    oss << "Processors: " << info.dwNumberOfProcessors;
    return oss.str();
}

std::string getRAM() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);

    std::ostringstream oss;
    oss << "Total RAM: " << (statex.ullTotalPhys / (1024 * 1024)) << " MB";
    return oss.str();
}

std::string getOS() {
#ifdef _WIN32
    return "Windows";
#elif __linux__
    return "Linux";
#elif __APPLE__
    return "macOS";
#else
    return "Unknown";
#endif
}

std::string getArch() {
#if INTPTR_MAX == INT64_MAX
    return "64-bit";
#else
    return "32-bit";
#endif
}

extern "C" __declspec(dllexport) const char* getSystemSpecs()
{
    json j;

    j["os"] = getOS();
    j["architecture"] = getArch();
    j["cpu"] = getCPU();
    j["ram"] = getRAM();

    static std::string output;  // must persist after return
    output = j.dump();          // convert JSON → string

    return output.c_str();
}