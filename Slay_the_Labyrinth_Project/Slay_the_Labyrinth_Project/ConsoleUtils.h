#pragma once
#include <string>

class ConsoleUtils {
 public:
  void ClearScreen();
  void Print(int x, int y, const std::string& text);
  int GetKey();
  void WaitForEnter();
};
