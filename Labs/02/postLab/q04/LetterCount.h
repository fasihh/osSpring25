#include <string>

class LetterCount {
  int count = 0;
public:
  LetterCount(const std::string& file_name);

  const int get() const;
};
