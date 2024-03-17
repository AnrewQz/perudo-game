#include "player.h"
#include <iostream>

Player::Player(std::string name) : name(name), numberOfDices(6) {
  cupOfDices = std::vector<Dice>(6, Dice());
}

void Player::ShuffleCup() {
  std::vector<int> tempHand;
  for (Dice dice : cupOfDices) {
    tempHand.push_back(dice.Shuffle());
  }
  std::swap(hand, tempHand);
}

void Player::LoseDice() {
  --numberOfDices;
  std::cout << "Игрок " << name << " теряет кубик\nУ него остается "
            << numberOfDices << " кубиков\n";
  cupOfDices.pop_back();
}