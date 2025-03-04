#include <iostream>
#include "include/car.h"

using namespace std;

int main() {
	Car c1, c2("fasih", "727");

	c1.display();

	cout << endl;

	c2.display();

	return 0;
}
