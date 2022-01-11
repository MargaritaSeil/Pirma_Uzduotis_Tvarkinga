#include "math.h"

bool compareStudents(studentas a, studentas b){
	return a.vardas.compare(b.vardas) < 0;
}

double median(std::vector<float> &vec) {
  typedef std::vector<float>::size_type vecSize;
  vecSize size = vec.size();
  if (size == 0) ///tikrinam ar vektorius nera tuscias
  throw std::domain_error("negalima skaičiuoti medianos tuščiam vekotoriui");
  std::sort(vec.begin(), vec.end()); ///surusiuojam elementus didejimo tvarka
  vecSize vid = size/2; ///randamas vidurkis
  return size%2==0 ? (vec[vid] + vec[vid]) / 2 : vec[vid];
}

int random_grade() //sugeneruoja random skaiciu nuo 1 iki 10
{
    return rand() % 10 + 1;
}

float avgExam(float vid, studentas s){
  //new local variable here
  float sad;
  sad=0.4*vid+0.6*s.egz;
  return sad;
}

float medExam(studentas s){
  float sad;
  sad=0.4*s.med+0.6*s.egz;
  return sad;
}