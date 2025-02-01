#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "Course.h"

using namespace std;

int main() {
    Student student1("Alice");
    Student student2("Bob");

    Teacher teacher1("Dr. Smith");
    Teacher teacher2("Prof. Johnson");

    Course course1("Mathematics");
    Course course2("Physics");

    student1.enrollInCourse(&course1);
    student2.enrollInCourse(&course2);

    teacher1.addCourse(&course1);
    teacher2.addCourse(&course2);

    course1.addStudent(&student1);
    course2.addStudent(&student2);

    course1.addTeacher(&teacher1);
    course2.addTeacher(&teacher2);

    cout << student1.getName() << " is enrolled in: ";
    for (auto& course : student1.getCourses()) {
        cout << course->getCourseName() << " ";
    }
    cout << endl;

    cout << student2.getName() << " is enrolled in: ";
    for (auto& course : student2.getCourses()) {
        cout << course->getCourseName() << " ";
    }
    cout << endl;

    cout << teacher1.getName() << " is teaching: ";
    for (auto& course : teacher1.getCourses()) {
        cout << course->getCourseName() << " ";
    }
    cout << endl;

    cout << teacher2.getName() << " is teaching: ";
    for (auto& course : teacher2.getCourses()) {
        cout << course->getCourseName() << " ";
    }
    cout << endl;

    cout << course1.getCourseName() << " has students: ";
    for (auto& student : course1.getStudents()) {
        cout << student->getName() << " ";
    }
    cout << "and teachers: ";
    for (auto& teacher : course1.getTeachers()) {
        cout << teacher->getName() << " ";
    }
    cout << endl;

    cout << course2.getCourseName() << " has students: ";
    for (auto& student : course2.getStudents()) {
        cout << student->getName() << " ";
    }
    cout << "and teachers: ";
    for (auto& teacher : course2.getTeachers()) {
        cout << teacher->getName() << " ";
    }
    cout << endl;

    return 0;
}

