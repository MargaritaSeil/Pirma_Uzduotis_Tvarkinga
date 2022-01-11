#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> //accumulate 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>	
#include "lib.hpp"

struct studentas{
    string vardas, pavarde;
    vector <float> paz;
    double med;
    float egz;
    float galutinis_paz;
};

int random_grade();
void names();
void print(studentas);
double median(vector<float> &vec);
bool compareStudents(studentas a, studentas b);

int main() {
    vector <studentas> grupe;
    studentas temp; ///laikinas kintamasis
    int n; ///studentu sk
    float sum=0, laik, vid, med; //laik - laikinas kintamamsis ivesciai
    string strAuto;         //changed from str_auto
    srand(time(NULL));
    string strLoad;
    string line;
    string v_m;
    ifstream readFile("studentai100000.txt");
    ofstream writeFile("rez.txt");
    
    cout << "Ar skaityti iš failo? (t/n) ";
    cin >> strLoad;
    if(strLoad == "t"){
        cout << "Ar galutinį skaičiuoti su mediana ar vidurkiu? (m/v) ";
        cin >> v_m;
        if(readFile.is_open()){
            float studentGrade;		//variable for grades.
            getline(readFile, line); //ignoruoja pirma eilute
            while(getline(readFile, line)){ //skaito po viena eilute ir laiko 'line' kintamajame
                istringstream iss(line); //in-built class
                iss >> temp.vardas >> temp.pavarde;	//first/last name
                while(iss >> studentGrade){
                    temp.paz.push_back(studentGrade);
                    temp.egz = studentGrade;
                }
                temp.paz.pop_back();
                
                vid=accumulate(temp.paz.begin(), temp.paz.end(), 0.0) / temp.paz.size();
                temp.med=median(temp.paz);
                
                if(v_m == "v"){
                    temp.galutinis_paz=0.4*vid+0.6*temp.egz;
                }
                else {
                    temp.galutinis_paz=0.4*temp.med+0.6*temp.egz;
                }
                
                grupe.push_back(temp);
                temp.paz.clear();
            }
            readFile.close();
        }
        else{ cout << "neišeina atidaryti failo"; }
    }
    else {
        cout << "Įveskite studentų skaičių: " <<endl;
        cin >> n;
        grupe.reserve(n);
        
        cout << "Ar galutinį skaičiuoti su mediana ar vidurkiu? (m/v) ";
        cin >> v_m;
        for (int i=0; i<n; i++){
            cout<<"Įveskite "<<i+1<<"-o studento vardą: ";
            cin>>temp.vardas;
            cout<<"Įveskite "<<i+1<<"-o studento pavardę: ";
            cin>>temp.pavarde;
            sum=0;
            cout<<"Ar įvesti pažymius automatiškai? (t/n) ";
            cin>>strAuto;
            
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
                temp.galutinis_paz=0.4*vid+0.6*temp.egz;
            }
            else {
                temp.galutinis_paz=0.4*temp.med+0.6*temp.egz;
            }
            grupe.push_back(temp);
            temp.paz.clear(); //kintamojo isvalymas
        }
    }
    sort(grupe.begin(), grupe.end(), compareStudents);
    names();
    if(writeFile.is_open()){
       writeFile<<setw(15)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<setw(15)<<left<<"Galutinis"
       <<"\n--------------------------------------------------\n";
    }
    else {
        cout << "negalima įrašyti. ";
    }
    for (const auto &kint: grupe) {
        print(kint);
        if(writeFile.is_open()) {
            writeFile<<setw(15)<<kint.vardas<<setw(15)<<kint.pavarde;
            writeFile<<setw(16)<<setprecision(3)<<kint.galutinis_paz<<endl;
        }
        else {
            cout << "negalima įrašyti." ;
        }
    }
    writeFile.close();     
}

void names () {
  cout<<"\n";
  cout<<setw(15)<<left<<"Vardas"
  <<setw(15)<<left<<"Pavarde"<<setw(15)<<left<<"Galutinis(vid.)"
  <<"\n--------------------------------------------------\n";
}

void print(studentas kint) {
  cout<<setw(15)<<kint.vardas<<setw(15)<<kint.pavarde;
  cout<<setw(16)<<setprecision(3)<<kint.galutinis_paz<<endl;
}

double median(vector<float> &vec) {
  typedef vector<float>::size_type vecSize;
  vecSize size = vec.size();
  if (size == 0) ///tikrinam ar vektorius nera tuscias
  throw domain_error("negalima skaičiuoti medianos tuščiam vekotoriui");
  sort(vec.begin(), vec.end()); ///surusiuojam elementus didejimo tvarka
  vecSize vid = size/2; ///randamas vidurkis
  return size%2==0 ? (vec[vid] + vec[vid]) / 2 : vec[vid];
}

int random_grade() {//sugeneruoja random skaiciu nuo 1 iki 10
    return rand() % 10 + 1;
}

bool compareStudents(studentas a, studentas b){
	return a.vardas.compare(b.vardas) < 0;
}