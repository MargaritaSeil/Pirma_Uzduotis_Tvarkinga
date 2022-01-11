#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lib.hpp"

struct studentas{
   string vardas, pavarde;
   float* paz;
   float med;
   float egz;
   float galutinis_paz;
   void setPazDyd(int n) {
       paz = new float[n];
   }
};

int random_grade();
void names();
void print(studentas);

int main() {
    studentas temp; ///laikinas kintamasis
    int n; ///studentu sk
    float sum=0, laik, vid, med; //laik - laikinas kintamamsis ivesciai
    string str_auto;
    srand(time(NULL));
    int k; //paz dydis

    cout << "Įveskite studentų skaičių: " <<endl;
    cin >> n;
    studentas grupe[n];
    for (int i=0; i<n; i++){
        cout<<"Įveskite "<<i+1<<"-o studento vardą: ";
        cin>>temp.vardas;       
        cout<<"Įveskite "<<i+1<<"-o studento pavardę: ";
        cin>>temp.pavarde;
        sum=0;
        cout<<"Ar įvesti pažymius automatiškai? (t/n) ";
        cin>>str_auto;
        cout<<"Kiek bus pažymių? ";
        cin>>k;
        temp.setPazDyd(k);
        
        if(str_auto == "t") {
            float random;
            
            for(int j=0; j<k; j++) {
                random = (float) random_grade();
                temp.paz[j] = random;
                sum+= random;
            }
            random = (float) random_grade();
            temp.egz = random;
        }
        else {
            cout<<"Įveskite "<<i+1<<"-o studento pažymius (1-10), baigę, spauskite 'enter' : ";
            
            for(int q = 0; q<k; q++){
                cin>>laik;
                temp.paz[q] = laik;
                sum+=laik;
            }
            cin.clear(); ///ignoruoti bloga ivesti
            cin.ignore(10000, '\n'); ///ingoruoti paskutini ivesta n
            cout<<"Įveskite "<<i+1<<"-o studento egzamino pažymį(1-10): ";
            cin>>temp.egz;
        }
        vid = sum / k;
        sort(temp.paz, temp.paz+k);
        if(k%2 == 0) {
            temp.med = (temp.paz[k/2] + temp.paz[k/2 - 1])/2.0f;
        }
        else {
            temp.med = temp.paz[k/2];
        }
        temp.galutinis_paz=0.4*vid+0.6*temp.egz;
        grupe[i] = temp;
    }
    names();
    for (const auto &kint: grupe) {
        print(kint);
    }
    delete[] temp.paz;
}

void names () {
  cout<<"\n";
  cout<<setw(15)<<left<<"Vardas"
  <<setw(15)<<left<<"Pavarde"<<setw(15)<<left<<"Galutinis(vid.)"<<setw(15)<<left<<" / Galutinis(med.)"
  <<"\n---------------------------------------------------------------------\n";
}

void print(studentas kint) {
  cout<<setw(15)<<kint.vardas<<setw(15)<<kint.pavarde;
  cout<<setw(16)<<setprecision(3)<<kint.galutinis_paz<<setw(15)<<kint.med<<endl;
}
int random_grade() { //sugeneruoja random skaiciu nuo 1 iki 10
    return rand() % 10 + 1;
}
