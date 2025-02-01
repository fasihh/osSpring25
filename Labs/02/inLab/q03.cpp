#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	vector<int> nums;
	for (int i = 1; i < argc; ++i)
		nums.push_back(atoi(argv[i]));

	sort(nums.begin(), nums.end());

	for (int& num : nums)
		cout << num << " ";
	cout << endl;

	return 0;
}

