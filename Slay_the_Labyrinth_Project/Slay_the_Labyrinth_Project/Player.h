#pragma once

#include <string>

#include "Stats.h"

class Player {
 private:
  std::string className;
  Stats stats;

 public:
  Player(std::string className, Stats stats);
};
