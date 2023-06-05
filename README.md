# DevicePowerManagement
Enable/Disable a specific device driver depending on AC adapter status.

## Aim
This project allows for a specific device driver to be enabled/disabled depending on the AC adapter status.
- This table shows when a device driver will be enabled/disabled.

    |AC Adapter Status|Device Driver Status|
    |-|-|
    |Plugged|Enabled|
    |Unplugged|Disabled|

## Usage
> This program originally intended use is to enable/disable dGPU in MS hybrid graphics system to save on power and improve battery life.

1. You will first need to get the instance ID of the desired device driver to be managed by the program.<br>
    To get that, do the following:
    1. Open Device Manager.
    2. Find the device driver, you would like the program to manage.
    3. Go into the device driver's properties and then go into the `Details` tab.
    4. Select the `Device Instance Path` property from the property dropdown.
    5. Right click the obtained output and select copy.
2. Open a Command Prompt/PowerShell window as an Administrator in the directory where `DevicePowerManagement.exe` is present in.
3. Use the following syntax:
    ```
    DevicePowerManagement.exe <Device Instance ID>
    ```
    Example:
    ```
    DevicePowerManagement.exe "PCI\VEN_10DE\&DEV_1D13&SUBSYS_09571028&REV_A1\4&4FD3F61&00E0"
    ```
    Here the program will manage a laptop's NVIDIA MX250 device driver.
4. Now open up Device Manager and check if the device driver gets enabled/disabled depending on the AC adapter status.

# Building
1. Install [`GCC`](https://github.com/brechtsanders/winlibs_mingw/latest) & [`UPX`](https://upx.github.io/) for optional compression.
2. Run `build.bat`.

