#include "output.h"

void names () {
  std::cout<<"\n";
  std::cout<<std::setw(15)<<std::left<<"Vardas"
  <<std::setw(15)<<std::left<<"Pavarde"<<std::setw(15)<<std::left<<"Galutinis"
  <<"\n--------------------------------------------------\n";
}

void print(studentas kint) {
  std::cout<<std::setw(15)<<kint.vardas<<std::setw(15)<<kint.pavarde;
  std::cout<<std::setw(16)<<std::setprecision(3)<<kint.galutinis_paz<<std::endl;
}

void writeTitle(std::ofstream &file){

  if(file.is_open()){
    file<<std::setw(15)<<std::left<<"Vardas"<<std::setw(15)<<std::left<<"Pavarde"
    <<std::setw(15)<<std::left<<"Galutinis"<<std::setw(15)
    <<"\n--------------------------------------------------\n";
  }
  else {
    std::cout << "negalima įrašyti. ";
  }
}

void writeResults(studentas kint, std::ofstream &file){

  if(file.is_open()) {
    file<<std::setw(15)<<kint.vardas<<std::setw(15)<<kint.pavarde;
    file<<std::setw(15)<<std::setprecision(3)<<kint.galutinis_paz<<std::endl;
    }
  else {
    std::cout << "negalima įrašyti." ;
  }
}
