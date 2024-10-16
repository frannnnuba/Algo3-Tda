#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int T, N,C,ei;


bool esPosible(int Vacas,const vector<int>& posiciones,int laDist){
    int puestas = 1;
    int ultimaPos = 0;
    for (int i = 1; i < posiciones.size();i++){
        if(posiciones[i] - posiciones[ultimaPos] >= laDist){
            puestas++;
            ultimaPos = i;
        }
        if(puestas >= Vacas){
            return true;
        }
    }
    return false;
}

int encontrarMaxMin(int Vacas,const vector<int>& posiciones){
    int n = posiciones.size();
    int izq = 1;
    int der = posiciones[n-1];
    int distMin = 1;
    int distMAx = posiciones[n -1] - posiciones[0]; 
    while(izq <= der){
        int mid = floor((der + izq)/2);
        if(esPosible(Vacas,posiciones,mid)){
                distMin = mid;
                izq = mid +1 ;
            }else{
                der = mid -1 ;
            }
        }
        return distMin;
}

vector<int> establo ;
int maxii = 0;

int main() {
    cin >> T;
    int cont1 = 0;
    while(cont1 < T){
        cin >> N;
        cin >> C;
        establo.clear();
        for(int cont2 = 0;cont2 < N; cont2++){
            cin >> ei;
            establo.emplace_back(ei);
        }
        std::sort(establo.begin(),establo.end());
        maxii = encontrarMaxMin(C,establo);
        std::cout << maxii <<std::endl;
        cont1++;
    }
    return 0;
}