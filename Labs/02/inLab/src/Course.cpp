#include "Course.h"
#include "Student.h"
#include "Teacher.h"

Course::Course(const std::string& courseName) : courseName(courseName) {}

void Course::addStudent(Student* student) {
    students.push_back(student);
}

void Course::addTeacher(Teacher* teacher) {
    teachers.push_back(teacher);
}

const std::vector<Student*>& Course::getStudents() const {
    return students;
}

const std::vector<Teacher*>& Course::getTeachers() const {
    return teachers;
}

std::string Course::getCourseName() const {
    return courseName;
}

