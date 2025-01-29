#ifndef TEACHER_H
#define TEACHER_H

#include <vector>
#include <string>
#include "Course.h"

class Course;

class Teacher {
private:
    std::string name;
    std::vector<Course*> courses;
public:
    Teacher(const std::string& name);
    void addCourse(Course* course);
    const std::vector<Course*>& getCourses() const;
    std::string getName() const;
};

#endif

