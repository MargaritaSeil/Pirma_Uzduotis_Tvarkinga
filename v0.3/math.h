#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "studentas.h"

int random_grade();
float avgExam(float vid, studentas s);
float medExam(studentas s);
double median(std::vector<float> &vec);
bool compareStudents(studentas a, studentas b);

#endif
