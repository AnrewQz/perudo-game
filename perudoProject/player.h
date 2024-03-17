#include "dice.h"
#include <string>
#include <vector>

class Player {
private:
  std::vector<Dice> cupOfDices;

public:
  std::string name;
  Player(std::string name);
  int numberOfDices;
  std::vector<int> hand;
  void ShuffleCup();
  void LoseDice();
};
