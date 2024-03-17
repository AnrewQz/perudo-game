#include <iostream>

class Bet {
public:
  int count = 0;
  int value = 0;
  Bet() = default;
  Bet(std::pair<int, int> numbers);
};

bool operator<(const Bet &first, const Bet &second);

std::ostream &operator<<(std::ostream &out, const Bet &bet);