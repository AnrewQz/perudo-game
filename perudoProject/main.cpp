#include "lobby.h"
#include<iostream>

int main() {
  std::cout << "Введите число игроков: ";
  int numberOfPlayers;
  std::cin >> numberOfPlayers;
  Lobby lobby(numberOfPlayers);
  lobby.Start();
}