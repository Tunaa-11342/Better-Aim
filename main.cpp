#include "src/includes.h"
#include "src/utils.hpp"
#include "src/mouse_hook.hpp"
#include <chrono>  
#include <thread>  

bool isItDutyTime = false;
bool isTargetFound = false;

long long averageResponseTime = 0;  

void screenRefresher() {
    while (true) {
        system("cls");
        noMoreQuickEdit();
        printLogo();
        std::cout << std::endl << "Current Config: " << std::endl;
        printConfig();
        std::cout << std::endl;
        std::cout << "Average Response time " << averageResponseTime << "ms (" << (averageResponseTime <= FRAME_DURATION_MS(config.refreshRate) ? "faster" : "slower") << " than screen's refresh rate)" << std::endl;
        std::cout << "Status: " << (isItDutyTime ? "Active (watching 'em on your screen)" : "Idle (press toggle button to activate)") << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void listenForAlt() {
    while (true) {
        if (GetAsyncKeyState(getKeyFromString(config.toggleKey)) & 0x8000) {
            isItDutyTime = !isItDutyTime;
            std::cout << (isItDutyTime ? "Here my watch begins" : "I'm taking a break") << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void trackThemDown() {
    int frameDuration = FRAME_DURATION_MS(config.refreshRate);

    while (true) {
        if (!isItDutyTime) {
            isTargetFound = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        auto frameStart = std::chrono::high_resolution_clock::now();

        // Capture screenshot and process it
        unsigned int* screenshotPixels = get_screenshot(config.scanAreaX, config.scanAreaY);

        isTargetFound = findOurTarget(screenshotPixels, config.scanAreaX, config.scanAreaY, config.tolerance);

        auto frameEnd = std::chrono::high_resolution_clock::now();
        averageResponseTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

        if (averageResponseTime < frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration - averageResponseTime));
        }
    }
}

// Dummy WndProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int main() {
    startupRoutine();

    startTheHook();

    std::thread altKeyListener(listenForAlt);
    std::thread consoleRefresher(screenRefresher);
    std::thread thePredator(trackThemDown);

    altKeyListener.detach();
    consoleRefresher.detach();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        Sleep(1);
    }

    thePredator.join();
    return 0;
}