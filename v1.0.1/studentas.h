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
#include <list>
#include <deque>

struct studentas{
    std::string vardas, pavarde;
    std::vector <float> paz;
    float egz;
    float galutinis_paz;
};

void writeTitle(std::ofstream &file);
void writeResults(studentas, std::ofstream &file);

void readFile(std::ifstream &file, std::list<studentas> &grupe);
void readFile(std::ifstream &file, std::vector<studentas> &grupe);
void readFile(std::ifstream &file, std::deque<studentas> &grupe);

void pazSkaic(std::list<studentas> &grupe);
void pazSkaic(std::vector<studentas> &grupe);
void pazSkaic(std::deque<studentas> &grupe);

bool compareNames(studentas a, studentas b);

#endif     