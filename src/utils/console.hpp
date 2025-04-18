#pragma once

void noMoreQuickEdit() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE);
}

void printLogo() {
    std::cout << " _                          _        ______                    " << std::endl;
    std::cout << "( \\                        | \\      (  ___ \\           ___     " << std::endl;
    std::cout << "| (                        | |      | (   ) )          ) (     " << std::endl;
    std::cout << "| |       _______  _______ | |   /\\ | (__/ /  _______  | |_____" << std::endl;
    std::cout << "| |      (  ___  )(  ____ \\| |__/ / |  __ (  (  ___  ) |  ____/" << std::endl;
    std::cout << "| |      | |   | || (    \\/| |__ (  | (  \\ \\ | |   | | | |     " << std::endl;
    std::cout << "| (____/\\| |___| || (____/\\| |  \\ \\ | )___) )| |___| | | |_____" << std::endl;
    std::cout << "(_______/(_______)(_______/|_/   \\/ |______/ (_______) )_(____/" << std::endl;
    std::cout << "                                    reVersion 1.0.0 by Rhaym   " << std::endl;
    std::cout << "               (credits to berk000x for the originl version)   " << std::endl;
}