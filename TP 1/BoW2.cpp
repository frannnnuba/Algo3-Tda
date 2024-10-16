#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int elem,sinPintar,indice,UltBlanca,UltNegra;
std::vector<std::vector<std::vector<int> > > tablaSoluciones;

int fRecursiva(int indice, int W, int B,const vector<int>& secAP,vector<std::vector<std::vector<int>>>& tablaSoluciones){
    int laBlanca = -1;
    int laNegra = 10000001;
    if(indice >= secAP.size()){ //caso base
            return 0; 
    }  
    if(tablaSoluciones[indice][W+1][B] != -1){
    return tablaSoluciones[indice][W+1][B] ;
    }
    if(W != -1){
        laBlanca = secAP[W] ;
    }
    if(B != 201){
        laNegra = secAP[B];
    }
    int laMejor = 0;
    if(secAP[indice] > laBlanca && secAP[indice] < laNegra){
        return tablaSoluciones[indice][W+1][B] = max(fRecursiva(indice +1,indice, B, secAP,tablaSoluciones) +1,max( 
                        fRecursiva(indice +1,W, indice,secAP,tablaSoluciones) +1,
                        fRecursiva(indice +1,W , B,secAP,tablaSoluciones))); 
    }
    if (secAP[indice] > laBlanca){
        return tablaSoluciones[indice][W+1][B] = max(fRecursiva(indice +1,indice, B, secAP,tablaSoluciones) +1, 
                        fRecursiva(indice +1,W , B,secAP,tablaSoluciones));
    }
    if(secAP[indice] < laNegra){
        return tablaSoluciones[indice][W+1][B] = max(fRecursiva(indice +1,W, indice, secAP,tablaSoluciones) +1, 
        fRecursiva(indice +1,W , B,secAP,tablaSoluciones));
    }
    return tablaSoluciones[indice][W+1][B] = fRecursiva(indice +1,W , B,secAP,tablaSoluciones);
}

int main(){
    int N;
    while(true){
        cin >> N;
        if(N == -1){
            return 0;
        }
        std::vector<int> secAPintar(N,0);
        tablaSoluciones = vector<vector<vector<int>>>(202, vector<vector<int>>(202, vector<int>(202,-1))); //si es -1 sabes que no esta calculada
        //cout << tablaSoluciones[0][0][0] << endl;
        int cont = 0;
        while (cont < N){
            cin >> elem;
            secAPintar[cont] = elem;
            cont++;
        }
        if (N == 0){
            std::cout << 0 << "\n";
        }else{
            //agarar el max entre fRecursiva blanca y frecursiva negra y sin pintar. Primera es la blanca,segunda negra y ultima ninguna
            int maxCantPintados = fRecursiva(0,-1,201,secAPintar,tablaSoluciones);
            sinPintar = (N- maxCantPintados);
            std::cout << sinPintar << "\n";
        }
    }
    return 0;
}