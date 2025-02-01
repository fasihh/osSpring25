#include <string>

class WordCount {
  int count = 0;
public:
  WordCount(const std::string& file_name);

  const int get() const;
};
