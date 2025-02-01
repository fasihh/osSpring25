#include <iostream>
#include <vector>

using namespace std;

double average(vector<int>& nums) {
  int sum = 0;
  for (int& num : nums)
    sum += num;
  return (double) sum / nums.size();
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    cout << "No parameters given" << endl;
    return 1;
  }
  
  vector<int> nums;
  for (int i = 1; i < argc; ++i)
    nums.push_back(atoi(argv[i]));

  cout << "Average: " << average(nums) << endl;

  return 0;
}

