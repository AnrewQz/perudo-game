#include "dice.h"
#include <random>

int Dice::Shuffle() {
  return rand() % 6 + 1;
}