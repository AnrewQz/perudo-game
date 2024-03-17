#include "lobby.h"
#include <iostream>

Lobby::Lobby(int numberOfPlayers) : numberOfPlayers(numberOfPlayers) {
  for (int i = 0; i < numberOfPlayers; ++i) {
    std::cout << "Введите имя игрока номер " << i + 1 << "\n";
    std::string name;
    std::cin >> name;
    players.push_back(Player(name));
  }
  historyOfBets.push_back({currentBet, Player("NoName")});
  ClearConsole();
}

void Lobby::AnotherTurn() {
  ClearConsole();
  std::cout << "История ставок:\n";
  std::cout << "Количество\t"
            << "Номинал\t\t"
            << "Игрок\n";
  for (auto bet : historyOfBets) {
    std::cout << bet.first << "\t\t" << bet.second.name << '\n';
  }
  std::cout << "Ход игрока " << (players.front()).name
            << "\nВведите любой символ, чтобы продолжить\n";

  char temp;
  std::cin >> temp;
  std::cout << "Ваши кубики: ";
  for (int value : players.front().hand) {
    std::cout << value << " ";
  }
  std::cout
      << "\nВведите 'check' чтобы сделать проверку или 'bet' чтобы поднять "
         "ставку.\n";
  std::string commamd;
  std::cin >> commamd;
  while (commamd != "check" && commamd != "bet") {
    std::cout << "некорректный ввод, повторите.\n";
    std::cin >> commamd;
  }
  if (commamd == "check") {
    SeparateConsole();
    return Check();
  } else {
    SeparateConsole();
    return MakeBet();
  }
}

void Lobby::Check() {
  std::cout << "Последняя ставка: " << currentBet.count << " кубиков номиналом "
            << currentBet.value << '\n';
  int resultCount = 0;

  for (int i = 0; i < numberOfPlayers; ++i) {
    int valueCount = 0;
    int onesCount = 0;
    Player player = players.front();
    players.pop_front();
    for (int number : player.hand) {
      if (number == 1) {
        ++onesCount;
      } else if (number == currentBet.value) {
        ++valueCount;
      }
    }
    if (currentBet.value == 1) {
      std::cout << "У игрока " << player.name << "\t" << onesCount
                << " кубиков номиналом 1\n";
    } else {
      std::cout << "У игрока " << player.name << "\t" << valueCount
                << " кубиков номиналом " << currentBet.value << " и "
                << onesCount << " кубиков номиналом 1\n";
    }
    if (currentBet.value == 1) {
      resultCount += onesCount;
    } else {
      resultCount += onesCount + valueCount;
    }
    players.push_back(player);
  }
  std::cout << "Итого на столе: " << resultCount << " кубиков номиналом "
            << currentBet.value << '\n';
  Player &curPlayer = players.front();
  Player &prevPlayer = players.back();
  if (resultCount < currentBet.count) {
    prevPlayer.LoseDice();
    if (prevPlayer.numberOfDices == 0) {
      std::cout << "Игрок " << prevPlayer.name << " выбывает из игры.\n";
      players.pop_back();
    }
  } else {
    curPlayer.LoseDice();
    if (curPlayer.numberOfDices == 0) {
      std::cout << "Игрок " << curPlayer.name << " выбывает из игры.\n";
      players.pop_front();
    }
  }
  historyOfBets.clear();
  currentBet = Bet();
  historyOfBets.push_back({currentBet, Player("NoName")});
  Shuffle();
  std::cout << "Введите любой символ, чтобы продолжить\n";
  char temp;
  std::cin >> temp;
  ClearConsole();
}

void Lobby::CorrectBet(Bet &bet) {
  while (!(currentBet < bet)) {
    std::cout << "Некорректная ставка. Поменяйте её.\nВведите через пробел "
                 "сначала количество, затем номинал кубиков\n";
    std::cin >> bet.count >> bet.value;
  }
}

void Lobby::MakeBet() {
  std::cout << "Вы обязаны либо увеличить количество кубиков в ставке,\nлибо "
               "поднять номинал кубика в ставке,\nлибо поставить на хотя бы "
               "[целая часть(предыдущее количество / 2)] единиц\n";
  std::cout
      << "Введите через пробел сначала количество, затем номинал кубиков\n";
  Player player = players.front();
  int count;
  int value;
  std::cin >> count >> value;
  Bet newBet({count, value});
  CorrectBet(newBet);
  currentBet = newBet;
  historyOfBets.push_back({currentBet, player});
  players.pop_front();
  players.push_back(player);
  ClearConsole();
}

void Lobby::Shuffle() {
  for (int i = 0; i < numberOfPlayers; ++i) {
    Player player = players.front();
    players.pop_front();
    player.ShuffleCup();
    players.push_back(player);
  }
}

void Lobby::ClearConsole() {
  for (int i = 0; i < 25; ++i) {
    std::cout << '\n';
  }
}

void Lobby::SeparateConsole() {
  for (int i = 0; i < 3; ++i) {
    std::cout << '\n';
  }
}

void Lobby::Start() {
  Shuffle();
  while (players.size() > 1) {
    AnotherTurn();
  }
  std::cout << "Победил(a) " << players.front().name << '\n';
}