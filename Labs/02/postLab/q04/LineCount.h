#include <string>

class LineCount {
  int count = 0;
public:
  LineCount(const std::string& file_name);

  const int get() const;
};
