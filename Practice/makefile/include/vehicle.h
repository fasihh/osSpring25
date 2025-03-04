#pragma once

#include <iostream>

typedef unsigned long long vid_t;

class Vehicle {
	vid_t id;
	std::string owner;

	static vid_t global_id;
public:
	Vehicle(const std::string& owner = "undefined");
	Vehicle(const Vehicle& obj);
	virtual ~Vehicle();

	virtual void display() const;
};

