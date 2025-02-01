#include <iostream>
#include "LetterCount.h"
#include "LineCount.h"
#include "WordCount.h"

using namespace std;

int main() {
  LetterCount letter_count("hello.txt");
  LineCount line_count("hello.txt");
  WordCount word_count("hello.txt");
  cout << letter_count.get() << endl;
  cout << line_count.get() << endl;
  cout << word_count.get() << endl;
  return 0;
}
