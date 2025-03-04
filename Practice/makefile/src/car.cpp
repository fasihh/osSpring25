#include "../include/car.h"

Car::Car(const std::string& owner, const std::string& model) : Vehicle(owner), model(model) {}
Car::Car(const Car& obj) : Vehicle(obj), model(obj.model) {}

void Car::display() const {
	Vehicle::display();
	std::cout << "model: " << this->model << '\n';
}

