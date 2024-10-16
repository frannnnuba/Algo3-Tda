#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, i, j;
vector<pair<int, int>> actividades;
// v={{2,3},{},..} v(1)={}, v(0)
int fIterativa(vector<pair<int, int>>& lasQueQuedan){
    int maxActual = 1;
    pair<int,int> ultimaAg = lasQueQuedan[0];
    for(int indice = 1; indice < lasQueQuedan.size(); indice++){
        pair<int,int> candidata = lasQueQuedan[indice];
        int inicioCand = candidata.first;
        int finUltima = ultimaAg.second;
        if(inicioCand >= finUltima){
            maxActual++;
            ultimaAg = candidata;
        }
    }
    return maxActual;
}

int main()
{
    cin >> T; // N es la cantidad de actividades que tendremos, i la hora de inicio y j la hora de fin
    for(int cont2 = 0; cont2 < T; cont2++){
    int cont = 0;
    cin >> N; // N es la cantidad de actividades que tendremos, i la hora de inicio y j la hora de fin  
    actividades.clear();
    while (cont < N)
    {
        cin >> i >> j;
        actividades.emplace_back(i,j); // aca va a haber que cargar las tuplas
        cont++;
    }
    if (N > 0){
        std::sort(actividades.begin(), actividades.end(), [](const pair<int, int>& delPrim, const pair<int, int>& delSeg) {
                return delPrim.second < delSeg.second;
            });
        int aDevo = fIterativa(actividades);
        std::cout  << aDevo << '\n';
    }
    else{
        std::cout << 0 << '\n';
        }
    }
    return 0;
}
