#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "studentas.h"

void names();
void print(studentas);
void writeTitle(std::ofstream &file);
void writeResults(studentas, std::ofstream &file);

#endif