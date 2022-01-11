#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric> //accumulate 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>	
#include "studentas.h"
#include "math.h"
#include "output.h"
#include "lib.hpp"

int main() {
  vector <studentas> grupe;
  studentas temp; ///laikinas kintamasis
  int n; ///studentu sk
  float sum=0, laik, vid, med; //laik - laikinas kintamamsis ivesciai
  string strAuto;         
  srand(time(NULL));
  string strLoad;
  string line;
  string v_m;
  ifstream readFile("studentai10000.txt");
  ofstream writeFile("rez.txt");

  cin.exceptions(std::istream::failbit); //programa automatikškai nepagauna išimčių, todėl reikia cin.exception() :((

  cout << "Ar skaityti iš failo? (t/n) ";
  cin >> strLoad;

  if(strLoad == "t"){
    cout << "Ar galutinį skaičiuoti su mediana ar vidurkiu? (m/v) ";
    cin >> v_m;

    if(readFile.is_open()){
      float studentGrade; //kintamasis pazymiams

      getline(readFile, line); //ignoruoja pirma eilute
      while(getline(readFile, line)){ //skaito po viena eilute ir laiko 'line' kintamajame
        istringstream iss(line); //in-built class

        iss >> temp.vardas >> temp.pavarde;	
        while(iss >> studentGrade){
          temp.paz.push_back(studentGrade);
          temp.egz = studentGrade;
        }
			  temp.paz.pop_back();
 
        vid=accumulate(temp.paz.begin(), temp.paz.end(), 0.0) / temp.paz.size();
        temp.med=median(temp.paz);
        
        if(v_m == "v"){
          temp.galutinis_paz=avgExam(vid, temp);
        }
        else {
          temp.galutinis_paz=medExam(temp);
        }
        grupe.push_back(temp);
        temp.paz.clear();
      }
      readFile.close();
    }
    else{ cout << "neišeina atidaryti failo"; }
  }
  else {
    try {
      cout << "Įveskite studentų skaičių: " <<endl;
      cin >> n;
    }
    catch(const std::ios_base::failure& e) {
      cout << "Įvestis nėra skaičius." << endl;
      cin.clear();    
    }
    
    grupe.reserve(n);
    
    cout << "Ar galutinį skaičiuoti su mediana ar vidurkiu? (m/v) ";
    cin >> v_m;

    for (int i=0; i<n; i++){
      cout<<"Įveskite "<<i+1<<"-o studento vardą: ";
      cin>>temp.vardas;

      cout<<"Įveskite "<<i+1<<"-o studento pavardę: ";
      cin>>temp.pavarde;

      cout<<"Ar įvesti pažymius automatiškai? (t/n) ";
      cin>>strAuto;

      sum=0;

      if(strAuto == "t") {
        int k;
        float random;

        cout<<"Kiek bus pažymių? ";
        cin>>k;

        for(int j=0; j<k; j++) {
          random = (float) random_grade();
          temp.paz.push_back(random);
          sum+= random;
        }

        random = (float) random_grade();
        temp.egz = random;
      }
      else {
        cout<<"Įveskite "<<i+1<<"-o studento pažymius (1-10), baigę, įveskite simbolį, kuris nėra skaičius: ";
        while(cin>>laik) {
          temp.paz.push_back(laik);
          sum+= laik; ///kol nesibaigs ciklas, bus sumuojami pazymiai
        }

        cin.clear(); ///ignoruoti bloga ivesti
        cin.ignore(10000, '\n'); ///ingoruoti paskutini ivesta n
        
        cout<<"Įveskite "<<i+1<<"-o studento egzamino pažymį(1-10): ";
        cin>>temp.egz;
      }

      vid=accumulate(temp.paz.begin(), temp.paz.end(), 0.0) / temp.paz.size();
      temp.med=median(temp.paz);

      if(v_m == "v"){
          temp.galutinis_paz=avgExam(vid, temp);
      }
      else {
          temp.galutinis_paz=medExam(temp);
      }

      grupe.push_back(temp);
      temp.paz.clear(); //kintamojo isvalymas
    }
  }
  sort(grupe.begin(), grupe.end(), compareStudents);

  names();
  writeTitle(writeFile);

  for (const auto &kint: grupe) {
    print(kint);
    writeResults(kint, writeFile);
  }
  writeFile.close();  
}

