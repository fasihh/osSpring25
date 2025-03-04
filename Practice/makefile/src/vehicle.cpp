#include "../include/vehicle.h"

Vehicle::Vehicle(const std::string& owner) : id(Vehicle::global_id++), owner(owner) {}
Vehicle::Vehicle(const Vehicle& obj) : id(obj.id), owner("undefined") {}
Vehicle::~Vehicle() = default;

vid_t Vehicle::global_id = 0;

void Vehicle::display() const {
	std::cout << "id: " << this->id << "\nowner: " << this->owner << std::endl;
}
