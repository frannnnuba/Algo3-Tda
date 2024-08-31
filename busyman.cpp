#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


int N,i,j;
tuple<int,int> infoActividad;
std::vector<tuple<int,int>> actividades;
std::vector<tuple<int,int>> MayoresActividades;

//toma un vector de las tuplas con actividades que no uso aun, el maximo actual y el vector de la solucion actual
//si para la que estoy por revisar sirve si no sigue.
//Necesitaria pasar como parametro el "acumulador" de la solucion parcial que va explorando?? para que le sume uno y compare con el max actual o que calcule todo y  despues vea que hace 
//vendra a ser el max que declare como variable global aca pero pasado como parametro. Tambien asi puedo ver si
//con la suma de el max mas lasquequedansise() podria ser mayor igual al maxActual. Si veo que no ni sigo 
int fRecursiva(int max,int maxActual, vector<tuple<int,int>> lasQueQuedan, vector<tuple<int,int>> lasDelMejor){
    if(lasQueQuedan.size() == 0 ){
        if (max > maxActual) {
            return max;
        }
        else 
        return maxActual;
    }
    if (max + lasQueQuedan.size() <= maxActual) {
        return maxActual;
    }
    else{
        tuple<int,int> actividadCandidata = *lasQueQuedan.begin();
        lasQueQuedan.erase(lasQueQuedan.begin());
        if(esActividadValida(lasDelMejor,actividadCandidata)){
            max = max + 1,
            lasDelMejor.insert(lasDelMejor.begin(),actividadCandidata);
            fRecursiva(max,maxActual,lasQueQuedan,lasDelMejor);
        }else{
            fRecursiva(max,maxActual,lasQueQuedan,lasDelMejor);
        }
    }
    return 0;
}


bool esActividadValida(vector<tuple<int,int>> lasDelMejor, tuple<int,int> candidata){
    int inicioCand = get<0>(candidata);
    int finCand =  get<1>(candidata);
    for (int j =0; j < lasDelMejor.size();j++){
        int inicioSeleccionadas = get<0>(lasDelMejor[j]);
        int finSeleccionadas =  get<1>(lasDelMejor[j]);
        if (inicioSeleccionadas <= inicioCand <= finSeleccionadas || 
        inicioSeleccionadas <= finCand <= finSeleccionadas ){
            return false; 
        }
    }
    return true;
}

int cont = 0;

int main() {
    cin >> N;    //N es la cantidad de actividades que tendremos, i la hora de inicio y j la hora de fin
    while (cont < N){
        cin >> i >> j;
        infoActividad = {i,j};   //tupla que tiene el inicio y el final de la actividad
        actividades.push_back(infoActividad);  //aca va a haber que cargar las tuplas
        cont++;
    }
    MayoresActividades = {}; //aca va a ir la lista con los horarios de la mayor cantidad posible hasta el momento
    if (N > 0){
        fRecursiva(0,0,actividades,MayoresActividades);
    }
    else {
        return 0;
    }
}


// aca si ya calcule cual es la mejor combinacion posible para despues de cierto elem me conviene guardarla
// para no volver a calcularla pero como? matriz? De cuanto? 