#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int precio;
vector<int> miDinero;
std::vector<vector<int,int>> soluciones;

int maxDelVector(vector<int> V){
    int tam =V.size();
    int max = V[0];
    for(int k =0; k < tam; k++)
    {
        if (max <= V[k])
        max = V[k];
    }
    return max;
}

vector<int> sacarElMax(vector<int> V, int max){
    std::vector<int> aDevolver;
    int VecesQueLoSaque = 0;
    int j = V.size() -1;
    for (int k =0; k < j;k++)
    {
        if (V[k] != max)
        aDevolver[k] = V[k];
        if (V[k] == max && VecesQueLoSaque == 0)
        VecesQueLoSaque = 1;
        if (V[k] == max && VecesQueLoSaque != 0)
        aDevolver[k] = max;
    }
    return aDevolver;
}


tuple<int,int> cjtoSoluciones(vector<int> V,int precio) {
    cin >> precio >> V;
    int elMayor = maxDelVector(miDinero);
    tuple<int,int> aDevo = {elMayor, 1};
    if (V.size() == 0)
    ////////
    if (precio - elMayor < 0)
    //aca la idea es cuando ya pago basicamente me armo la tupla de (plata, cant de billetes)   
    soluciones.push_back(aDevo); 
    return soluciones;
    if ((precio - elMayor) = 0)
    //aca la ideaes que llego a el precio justo asi que con este camino se termino
    ////////
    else //este es el caso en el que todavia tengo que pagar 
    vector<int> aRecursar = sacarElMax(miDinero,elMayor);
    int nuevoValor = precio - elMayor ; 
    aDevo = {get<0>(aDevo) + cjtoSoluciones(aRecursar,nuevoValor), get<1>(aDevo) +1};
}