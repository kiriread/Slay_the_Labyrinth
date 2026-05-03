#include "ConsoleUtils.h"

#include <conio.h>
#include <windows.h>

#include <iostream>

void ClearScreen() { system("cls"); }

void DrawText(int x, int y, const std::string& text) {
  COORD coord = {(SHORT)x, (SHORT)y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  std::cout << text;
}

int GetKey() { return _getch(); }
