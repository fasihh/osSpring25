#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>

using namespace std;

int find_missing(vector<int>& nums) {
  int n = nums.size() + 1;
  int original_sum = (n * (nums.front() + nums.back())) / 2;

  return original_sum - accumulate(nums.begin(), nums.end(), 0);
}

int main() {
  ifstream series("series.txt");
  string buffer;
  vector<int> nums;

  getline(series, buffer);
  series.close();

  string number;
  stringstream ss(buffer);
  while (ss >> number)
    nums.push_back(stoi(number));

  ofstream new_nums("missing.txt");
  new_nums << find_missing(nums) << "\n";
  new_nums.close();

  return 0;
}
