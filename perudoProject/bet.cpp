#include "bet.h"

Bet::Bet(std::pair<int, int> numbers)
    : count(numbers.first), value(numbers.second) {}

bool operator<(const Bet &first, const Bet &second) {
  if (first.value == second.value) {
    return first.count < second.count;
  } else if (first.value == 1) {
    return first.count * 2 < second.count;
  } else if (second.value == 1) {
    return (first.count + 1) / 2 <= second.count;
  } else if (first.value < second.value) {
    return first.count <= second.count;
  }
  return first.count < second.count;
}

std::ostream &operator<<(std::ostream &out, const Bet &bet) {
  out << bet.count << "\t\t" << bet.value;
  return out;
}