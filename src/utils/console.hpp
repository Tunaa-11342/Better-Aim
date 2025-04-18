#pragma once

void noMoreQuickEdit() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}

void printLogo() {
    std::cout << "  _____                  _           _____ " << std::endl;
    std::cout << " |  __ \\                | |         / ____|" << std::endl;
    std::cout << " | |__) |__  _ __   ___ | |_ ______| |     " << std::endl;
    std::cout << " |  ___/ _ \\| '_ \\ / _ \\| __|______| |     " << std::endl;
    std::cout << " | |  | (_) | | | | (_) | |_       | |____ " << std::endl;
    std::cout << " |_|   \\___/|_| |_|\\___/ \\__|       \\_____|" << std::endl;
    std::cout << std::endl;
    std::cout << "               reVersion 1.0.0 by Tunaa      " << std::endl;
    std::cout << "  (credits to berk000x for the original version)" << std::endl;
    std::cout << std::endl;
}
