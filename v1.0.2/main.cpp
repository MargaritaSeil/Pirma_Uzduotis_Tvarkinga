#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
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

  vector<studentas> grupeStudentaiVector;
  vector<studentas> vargsiukaiVector;

  deque<studentas> grupeStudentaiDeque;  
  deque<studentas> vargsiukaiDeque;
 
  auto start = std::chrono::high_resolution_clock::now(); // Paleisti
  auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
  std::chrono::duration<double> diff = end-start; // Skirtumas (s)
  
  auto titList = grupeStudentaiList.begin();
  auto titVector = grupeStudentaiVector.begin();
  auto titDeque = grupeStudentaiDeque.begin();
 
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
    readFile(ifStudentuFailas, grupeStudentaiList);
    ifStudentuFailas.close();

    pazSkaic(grupeStudentaiList);
    start = std::chrono::high_resolution_clock::now();

    copy_if(
    grupeStudentaiList.begin(),
    grupeStudentaiList.end(),
    std::back_inserter(vargsiukaiList),
    isLowGrade);
    
    titList = remove_if(grupeStudentaiList.begin(), grupeStudentaiList.end(), isLowGrade);
    grupeStudentaiList.erase(titList, grupeStudentaiList.end());
    
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i << " studentų dalijimas į dvi grupes užtruko naudojant list: ";
    cout << diff.count() << "s" << endl;
    
    grupeStudentaiList.sort(compareNames);
    vargsiukaiList.sort(compareNames);

    ofVargsiukaiFailas.open(varg);
    writeTitle(ofVargsiukaiFailas);
    for(const auto &kint : vargsiukaiList) {
      writeResults(kint, ofVargsiukaiFailas);
    }
    ofVargsiukaiFailas.close();
    
    ofKietiakaiFailas.open(kiet);
    writeTitle(ofKietiakaiFailas);
    for(const auto &kint : grupeStudentaiList) {
      writeResults(kint, ofKietiakaiFailas);
    }
    ofKietiakaiFailas.close();

    grupeStudentaiList.clear();
    vargsiukaiList.clear();

    //------deque-----//
    ifStudentuFailas.open(fn);
    readFile(ifStudentuFailas, grupeStudentaiDeque);
    ifStudentuFailas.close();

    pazSkaic(grupeStudentaiDeque);
    start = std::chrono::high_resolution_clock::now();
    
    copy_if(
    grupeStudentaiDeque.begin(),
    grupeStudentaiDeque.end(),
    std::back_inserter(vargsiukaiDeque),
    isLowGrade);
    
    titDeque = remove_if(grupeStudentaiDeque.begin(), grupeStudentaiDeque.end(), isLowGrade);
    grupeStudentaiDeque.erase(titDeque, grupeStudentaiDeque.end());

    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i <<" studentų dalijimas į dvi grupes užtruko naudojant deque: ";
    cout << diff.count() << "s" << endl;

    grupeStudentaiDeque.clear();
    vargsiukaiDeque.clear();  

    grupeStudentaiDeque.shrink_to_fit();
    vargsiukaiDeque.shrink_to_fit();

    //-------vector COPY_IF + REMOVE_IF-----//
    ifStudentuFailas.open(fn);
    readFile(ifStudentuFailas, grupeStudentaiVector);
    ifStudentuFailas.close();

    pazSkaic(grupeStudentaiVector);
    start = std::chrono::high_resolution_clock::now();
    
    copy_if(
    grupeStudentaiVector.begin(),
    grupeStudentaiVector.end(),
    std::back_inserter(vargsiukaiVector),
    isLowGrade);
    
    titVector = remove_if(grupeStudentaiVector.begin(), grupeStudentaiVector.end(), isLowGrade);
    grupeStudentaiVector.erase(titVector, grupeStudentaiVector.end());
    
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i << " studentų dalijimas į dvi grupes užtruko naudojant vector: ";
    cout << diff.count() << "s" << endl;
    
    grupeStudentaiVector.clear();
    vargsiukaiVector.clear();

    grupeStudentaiVector.shrink_to_fit();
    vargsiukaiVector.shrink_to_fit();

    //----vector STABLE_PARTITION + COPY_N------//
    ifStudentuFailas.open(fn);
    readFile(ifStudentuFailas, grupeStudentaiVector);
    ifStudentuFailas.close();

    pazSkaic(grupeStudentaiVector);
    start = std::chrono::high_resolution_clock::now();
    
    titVector = stable_partition(grupeStudentaiVector.begin(), grupeStudentaiVector.end(), isLowGrade);

    copy_n(
      grupeStudentaiVector.begin(),
      std::distance(grupeStudentaiVector.begin(), titVector),
      std::back_inserter(vargsiukaiVector));
  
    grupeStudentaiVector.erase(grupeStudentaiVector.begin(), titVector);
    
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << i <<" studentų dalijimas į dvi grupes užtruko naudojant vector" <<endl;
    cout << "(stable_partition): ";
    cout << diff.count() << "s" << endl;

    cout << endl;
    
    grupeStudentaiVector.clear();
    vargsiukaiVector.clear();

    grupeStudentaiVector.shrink_to_fit();
    vargsiukaiVector.shrink_to_fit();
    
    fn.clear();
    varg.clear();
    kiet.clear();
  }
} 