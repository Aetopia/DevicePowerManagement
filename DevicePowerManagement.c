#include <windows.h>
#include <cfgmgr32.h>

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static WCHAR **cmdLineW;
    static DEVINST deviceInstance;
    switch (uMsg)
    {
    case WM_CREATE:
        const GUID GUID_ACDC_POWER_SOURCE = {0x5D3E9A59, 0xE9D5, 0x4B00, {0xA9, 0x28, 0xF4, 0x60, 0x5F, 0x46, 0xCB, 0x44}};
        INT numArgs;
        cmdLineW = CommandLineToArgvW(GetCommandLineW(), &numArgs);

        if (numArgs != 2)
        {
            MessageBoxW(hWnd, L"Syntax: <Device Instance ID>", L"DevicePowerManagement", MB_ICONASTERISK);
            ExitProcess(0);
        }
        if (CM_Locate_DevNodeW(&deviceInstance, (DEVINSTID_W)cmdLineW[1], CM_LOCATE_DEVINST_NORMAL))
        {
            MessageBoxW(hWnd, L"Error: Invalid Device Instance ID!", L"DevicePowerManagement", MB_ICONERROR);
            ExitProcess(0);
        }
        RegisterPowerSettingNotification(hWnd, &GUID_ACDC_POWER_SOURCE, DEVICE_NOTIFY_WINDOW_HANDLE);
        SendMessageW(hWnd, WM_POWERBROADCAST, PBT_APMPOWERSTATUSCHANGE, 0);
        return 0;

    case WM_POWERBROADCAST:
        if (wParam != PBT_APMPOWERSTATUSCHANGE)
            break;

        SYSTEM_POWER_STATUS systemPowerStatus;
        GetSystemPowerStatus(&systemPowerStatus);

        if (systemPowerStatus.ACLineStatus)
            CM_Enable_DevNode(deviceInstance, 0);
        else
            CM_Disable_DevNode(deviceInstance, 0);
        break;

    default:
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASSEXW wndClassExW = {.cbSize = sizeof(WNDCLASSEXW),
                               .lpfnWndProc = WndProc,
                               .hInstance = hInstance,
                               .lpszClassName = L"DevicePowerManagement"};
    if (!RegisterClassExW(&wndClassExW) ||
        !CreateWindowExW(0, L"DevicePowerManagement", 0, 0, 0, 0, 0, 0, 0, 0, hInstance, 0))
        return 1;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}