#include <fstream>
#include <sstream>
#include "WordCount.h"

WordCount::WordCount(const std::string& file_name) {
  std::ifstream file(file_name);
  std::stringstream ss;
  ss << file.rdbuf();

  std::string buffer;
  int count = 0;
  while (ss >> buffer)
    count++;

  this->count = count;

  file.close();
}

const int WordCount::get() const { return this->count; }
