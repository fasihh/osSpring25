#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include "Course.h"

class Course;

class Student {
private:
    std::string name;
    std::vector<Course*> courses;
public:
    Student(const std::string& name);
    void enrollInCourse(Course* course);
    const std::vector<Course*>& getCourses() const;
    std::string getName() const;
};

#endif

