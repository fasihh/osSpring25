#include <fstream>
#include <cctype>
#include "LetterCount.h"

LetterCount::LetterCount(const std::string& file_name) {
  std::ifstream file(file_name);

  char ch;
  int count = 0;
  while (file.get(ch))
    if (std::isalpha(ch))
      count++;
  this->count = count;

  file.close();
}

const int LetterCount::get() const { return this->count; }
