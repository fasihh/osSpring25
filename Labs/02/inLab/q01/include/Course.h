#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>
#include "Student.h"
#include "Teacher.h"

class Student;
class Teacher;

class Course {
private:
    std::string courseName;
    std::vector<Student*> students;
    std::vector<Teacher*> teachers;

public:
    Course(const std::string& courseName);
    void addStudent(Student* student);
    void addTeacher(Teacher* teacher);
    const std::vector<Student*>& getStudents() const;
    const std::vector<Teacher*>& getTeachers() const;
    std::string getCourseName() const;
};

#endif

