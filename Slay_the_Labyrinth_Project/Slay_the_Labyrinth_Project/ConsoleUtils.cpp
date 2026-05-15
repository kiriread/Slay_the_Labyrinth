#include "ConsoleUtils.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

void ConsoleUtils::ClearScreen() {
    system("cls");
}

void ConsoleUtils::Print(int x, int y, const std::string& text) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    std::cout << text;
}

int ConsoleUtils::GetKey() {
    return _getch();
}

void ConsoleUtils::WaitForEnter() {
    while (true) {
        int key = _getch();
        if (key == 13) break;  // Enter
    }
}