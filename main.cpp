#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include "studentas.h"
#include "lib.hpp"

int main() {
  ifstream ifStudentuFailas("studentų sąrašas.txt");
  ofstream ofStudentuFailas("studentų sąrašas.txt");
  ofstream ofVargsiukaiFailas("vargšiukai.txt");
  ofstream ofKietiakaiFailas("kietiakai.txt");

  vector <studentas> grupeStudentai;  
  vector <studentas> vargsiukai;
  vector <studentas> kietiakai;

  int nStudentai;
  int nPaz;
  
  auto start = std::chrono::high_resolution_clock::now(); // Paleisti
  auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
  std::chrono::duration<double> diff = end-start; // Skirtumas (s)
 
  cout << "Įveskite studentų skaičių: " <<endl;
  cin >> nStudentai;
  
  cout<<"Kiek bus namų darbų pažymių? ";
  cin >> nPaz;

  start = std::chrono::high_resolution_clock::now();
  generateList(grupeStudentai, nStudentai, nPaz);
  end = std::chrono::high_resolution_clock::now();
  diff = end-start;
  cout << nStudentai <<" studentų pažymių užpildymas užtruko: ";
  cout << diff.count() << "s" << endl;

  writeGeneratedListTitle(nPaz, ofStudentuFailas);
  for(const auto &kint : grupeStudentai) { 
    writeGeneratedList(kint, ofStudentuFailas);   
  }
  grupeStudentai.clear();
  ofStudentuFailas.close();

  //ima laika pries pradedant
  start = std::chrono::high_resolution_clock::now();
  readFile(ifStudentuFailas, grupeStudentai);
  ifStudentuFailas.close();
  //ima laiko pabaigus
  end = std::chrono::high_resolution_clock::now();
  diff = end-start;
  cout <<"Failo iš " << nStudentai <<" studentų įrašų nuskaitymo laikas: ";
  cout << diff.count() << "s" << endl;

  pazSkaic(grupeStudentai);
  start = std::chrono::high_resolution_clock::now();
  for (const auto &kint: grupeStudentai) {
    if(kint.galutinis_paz < 5){
      vargsiukai.push_back(kint); 
    }
    else {
      kietiakai.push_back(kint);
    }
  }
  end = std::chrono::high_resolution_clock::now();
  diff = end-start;
  cout << nStudentai <<" studentų dalijimas į dvi grupes užtruko: ";
  cout << diff.count() << "s" << endl;

  //sort lists as names
  sort(grupeStudentai.begin(), grupeStudentai.end(), compareStudents);
  sort(vargsiukai.begin(), vargsiukai.end(), compareStudents);
  sort(kietiakai.begin(), kietiakai.end(), compareStudents);

  start = std::chrono::high_resolution_clock::now();
  writeTitle(ofVargsiukaiFailas);
  for(const auto &kint : vargsiukai) {
    writeResults(kint, ofVargsiukaiFailas);
  }
  ofVargsiukaiFailas.close();
  end = std::chrono::high_resolution_clock::now();
  diff = end-start;
  cout <<"vargšiukų įrašymas į failą užtruko: ";
  cout << diff.count() << "s" << endl;
  
  start = std::chrono::high_resolution_clock::now();
  writeTitle(ofKietiakaiFailas);
  for(const auto &kint : kietiakai) {
    writeResults(kint, ofKietiakaiFailas);
  }
  ofKietiakaiFailas.close();
  end = std::chrono::high_resolution_clock::now();
  diff = end-start;
  cout <<"kietiakų įrašymas į failą užtruko: ";
  cout << diff.count() << "s" << endl;

  grupeStudentai.clear();
  vargsiukai.clear();
  kietiakai.clear();

  grupeStudentai.shrink_to_fit();
  vargsiukai.shrink_to_fit();
  kietiakai.shrink_to_fit();
} 