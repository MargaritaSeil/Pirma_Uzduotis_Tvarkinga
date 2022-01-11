#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include "studentas.h"
#include "lib.hpp"

int main() {
  
  string fn = " ";
  string varg = " ";
  string kiet = " ";
  
  ifstream ifStudentuFailas;
  ofstream ofVargsiukaiFailas;
  ofstream ofKietiakaiFailas;

  list<studentas> grupeStudentaiList;  
  list<studentas> vargsiukaiList;
  list<studentas> kietiakaiList;

  vector<studentas> grupeStudentaiVector;
  vector<studentas> vargsiukaiVector;
  vector<studentas> kietiakaiVector;
 
  auto start = std::chrono::high_resolution_clock::now(); // Paleisti
  auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
  std::chrono::duration<double> diff = end-start; // Skirtumas (s)
 
  cout << std::fixed;

  for(int i = 1000; i <= 10000000; i=i*10){
    fn = to_string(i) + " studentu sarasas.txt";
    varg = to_string(i) + " vargsiukai.txt";
    kiet = to_string(i) + " kietiakai.txt";

    ofVargsiukaiFailas.open(varg, std::ofstream::out  |std::ofstream::trunc);
    ofVargsiukaiFailas.close();
    
    ofKietiakaiFailas.open(kiet, std::ofstream::out  |std::ofstream::trunc);
    ofKietiakaiFailas.close();

    ifStudentuFailas.open(fn);
    //ima laika pries pradedant
    start = std::chrono::high_resolution_clock::now();
    readFile(ifStudentuFailas, grupeStudentaiList);
    ifStudentuFailas.close();
    //ima laiko pabaigus
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout <<"Failo iš " << i << " studentų įrašų nuskaitymo laikas naudojant list: ";
    cout << diff.count() << "s" << endl;

    pazSkaic(grupeStudentaiList);
    start = std::chrono::high_resolution_clock::now();
    for (const auto &kint: grupeStudentaiList) {
      if(kint.galutinis_paz < 5){
        vargsiukaiList.push_back(kint); 
      }
      else {
        kietiakaiList.push_back(kint);
      }
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i << " studentų dalijimas į dvi grupes užtruko naudojant list: ";
    cout << diff.count() << "s" << endl;
    
    grupeStudentaiList.sort(compareNames);
    vargsiukaiList.sort(compareNames);
    kietiakaiList.sort(compareNames);
    
    ofVargsiukaiFailas.open(varg);
    writeTitle(ofVargsiukaiFailas);
    for(const auto &kint : vargsiukaiList) {
      writeResults(kint, ofVargsiukaiFailas);
    }
    ofVargsiukaiFailas.close();
    
    ofKietiakaiFailas.open(kiet);
    writeTitle(ofKietiakaiFailas);
    for(const auto &kint : kietiakaiList) {
      writeResults(kint, ofKietiakaiFailas);
    }
    ofKietiakaiFailas.close();

    grupeStudentaiList.clear();
    vargsiukaiList.clear();
    kietiakaiList.clear();
    
    
    //-------vector-----//
    ifStudentuFailas.open(fn);
    start = std::chrono::high_resolution_clock::now();
    readFile(ifStudentuFailas, grupeStudentaiVector);
    ifStudentuFailas.close();
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << "Failo iš " << i << " studentų įrašų nuskaitymo laikas naudojant vector: ";
    cout << diff.count() << "s" << endl;

    pazSkaic(grupeStudentaiVector);
    start = std::chrono::high_resolution_clock::now();
    for (const auto &kint: grupeStudentaiVector) {
      if(kint.galutinis_paz < 5){
        vargsiukaiVector.push_back(kint); 
      }
      else {
        kietiakaiVector.push_back(kint);
      }
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i << " studentų dalijimas į dvi grupes užtruko naudojant vector: ";
    cout << diff.count() << "s" << endl;
    cout << endl;

    grupeStudentaiVector.clear();
    vargsiukaiVector.clear();
    kietiakaiVector.clear();

    grupeStudentaiVector.shrink_to_fit();
    vargsiukaiVector.shrink_to_fit();
    kietiakaiVector.shrink_to_fit();

    fn.clear();
    varg.clear();
    kiet.clear();
  }
} 