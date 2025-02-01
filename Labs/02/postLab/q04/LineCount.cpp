#include <fstream>
#include <sstream>
#include "LineCount.h"

LineCount::LineCount(const std::string& file_name) {
  std::ifstream file(file_name);
  std::string buffer;

  int count = 0;
  while (std::getline(file, buffer))
    count++;
  this->count = count;

  file.close();
}

const int LineCount::get() const { return this->count; }
