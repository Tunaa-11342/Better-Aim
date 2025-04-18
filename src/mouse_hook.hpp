#pragma once

#include "includes.h"

extern bool isTargetFound;

HHOOK hook;

LRESULT CALLBACK hoolCallback(int niggerCode, WPARAM wideAssParam, LPARAM longAssParam) {
    if (niggerCode > -1 && wideAssParam == WM_MOUSEMOVE && isTargetFound) {
        Sleep(config.gravity);
    }

    return CallNextHookEx(hook, niggerCode, wideAssParam, longAssParam);
}

void startTheHook() {
    hook = SetWindowsHookEx(WH_MOUSE_LL, hoolCallback, 0, 0);

    if (!hook) {
        std::cerr << "Failed to initialize hook" << std::endl;
        return;
    }
}
