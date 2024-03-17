#include "bet.h"
#include "deque"
#include "player.h"

class Lobby {

public:
  int numberOfPlayers;
  std::deque<Player> players;
  Lobby(int numberOfPlayers);
  ~Lobby() = default;

  Bet currentBet;
  std::vector<std::pair<Bet, Player>> historyOfBets;
  void AnotherTurn();
  void CorrectBet(Bet &bet);
  void MakeBet();
  void Check();
  void Shuffle();
  void ClearConsole();
  void SeparateConsole();
  void Start();
};
