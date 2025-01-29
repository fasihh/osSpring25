#include "Teacher.h"
#include "Course.h"

Teacher::Teacher(const std::string& name) : name(name) {}

void Teacher::addCourse(Course* course) {
    courses.push_back(course);
}

const std::vector<Course*>& Teacher::getCourses() const {
    return courses;
}

std::string Teacher::getName() const {
    return name;
}

