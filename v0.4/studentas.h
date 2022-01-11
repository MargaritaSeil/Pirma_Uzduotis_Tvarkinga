#ifndef STUDENTAS_H     //make sure not already exist
#define STUDENTAS_H     //define

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>

//HERE GOES STUFF
struct studentas{
    std::string vardas, pavarde;
    std::vector <float> paz;
    double med;
    float egz;
    float galutinis_paz;
};

// this function generates the student list.

void writeTitle(std::ofstream &file);
void writeResults(studentas, std::ofstream &file);
void writeGeneratedListTitle(int nPaz, std::ofstream &file);
void writeGeneratedList(studentas, std::ofstream &file);

void generateList(std::vector<studentas> &grupe, int nStudentai, int nPaz);
// make a function here for the mathies. it can be void and we need a vector to hold the group, like in generateList. you had it right. now you need to name it. you can use grupe here too.
void pazSkaic(std::vector<studentas> &grupe);
int randomNumber();
double median(std::vector<float> &vec);
bool compareStudents(studentas a, studentas b);

#endif     