#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

int find_missing(vector<int>& nums) {
  int n = nums.size() + 1;
  int original_sum = (n * (nums.front() + nums.back())) / 2;

  return original_sum - accumulate(nums.begin(), nums.end(), 0);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    cout << "No parameters" << endl;
    return 1;
  }

  vector<int> nums;
  for (int i = 1; i < argc; ++i)
    nums.push_back(atoi(argv[i]));

  ofstream file("missing.txt");
  file << find_missing(nums) << "\n";
  file.close();

  return 0;
}
