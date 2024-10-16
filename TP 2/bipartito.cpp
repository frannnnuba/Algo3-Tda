#include<iostream>
#include <vector>

using namespace std;

long long int N;
int i,j;

int main(){
    cin >> N;
    vector<int> bipartito(N+1,-1);
    vector<vector<int>> listaAdy(N+1);
    long long int contv0 = 0;
    long long int contv1 = 0;
    for(int cont = 1;cont < N;cont++){
        cin >> i >> j;
        listaAdy[i].push_back(j);
        listaAdy[j].push_back(i);
    }
    for(int p = 1; p < N + 1;p++){
        if(bipartito[p] == -1 && p == 1){
            bipartito[p] = 0;
            contv0++;
            for(int j = 0; j < listaAdy[p].size();j++){
                bipartito[listaAdy[p][j]] = 1;
                contv1++;
            }
        }else if(bipartito[p]== -1 && p != 1){
            int k = listaAdy[p].size();
            int neg = -1;
            int contr = 0;
            while(neg == -1 && contr < k){
                if(bipartito[listaAdy[p][contr]] != -1){
                    neg = bipartito[listaAdy[p][contr]];
                    k = 0;
                } 
                contr++;
            }
            bipartito[p] = 1 - neg;
            if(bipartito[p] == 0){
                contv0++;
            }else{
                contv1++;
            }
            for(int r = 0; r < listaAdy[p].size();r++){
                if(bipartito[listaAdy[p][r]] == -1 && neg == 1){
                    if(bipartito[listaAdy[p][r]] != 1){
                        bipartito[listaAdy[p][r]] =1;
                        contv1++;
                    }
                }else if(bipartito[listaAdy[p][r]] == -1 && neg == 0){
                    if(bipartito[listaAdy[p][r]] != 0){
                        bipartito[listaAdy[p][r]] = 0;
                        contv0++;
                    }
                }
            }
        }else if(bipartito[p] != -1 && p != 1){
            if(bipartito[p] == 1){
                for(int q = 0; q < listaAdy[p].size();q++){
                    if(bipartito[listaAdy[p][q]] != 0){
                        bipartito[listaAdy[p][q]] = 0;
                        contv0++;
                    }
                }
            }else if (bipartito[p] == 0){
                for(int q = 0; q < listaAdy[p].size();q++){
                    if(bipartito[listaAdy[p][q]] != 1){
                        bipartito[listaAdy[p][q]] = 1;
                        contv1++;
                    }
                }
            }
        }
    }
    long long int aDevo = (contv1 * contv0)- (N-1);
    if(aDevo >= 0){
        std::cout << aDevo << "\n";
    }else{
        std::cout << 0 << "\n";
    }
    return 0;
}





