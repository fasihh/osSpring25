#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "File name required" << endl;
		return 1;
	}

	ifstream file(argv[1]);

	if (!file.is_open()) {
		cout << "File does not exist" << endl;
		return 1;
	}

	string buffer;
	while (getline(file, buffer))
		cout << buffer << "\n";

	return 0;
}
