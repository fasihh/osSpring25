#pragma once
#include <iostream>
#include "vehicle.h"

class Car : public Vehicle {
	std::string model;
public:
	Car(const std::string& owner = "undefined", const std::string& model = "undefined");
	Car(const Car& obj);

	void display() const override;
};

