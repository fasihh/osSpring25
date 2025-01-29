#include "Student.h"
#include "Course.h"

Student::Student(const std::string& name) : name(name) {}

void Student::enrollInCourse(Course* course) {
    courses.push_back(course);
}

const std::vector<Course*>& Student::getCourses() const {
    return courses;
}

std::string Student::getName() const {
    return name;
}

