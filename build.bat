@echo off
cd "%~dp0"
gcc -mwindows -s DevicePowerManagement.c -lCfgMgr32 -o DevicePowerManagement.exe
upx --best --ultra-brute DevicePowerManagement.exe>nul 2>&1