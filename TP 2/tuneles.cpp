#include<iostream>
#include <vector>
#include <queue>

using namespace std;

long long int N;
int i;

vector<int> bfsParaDistancia(const vector<vector<int>>& G, int r,vector<bool>& visitados, vector<int>& adevo){
    queue<int> cola; 
    visitados[r] = true;
    adevo[0]= 0;
    adevo[1]= 1;
    cola.push(r);
    while (!cola.empty()) {
        int actual = cola.front(); 
        cola.pop();
        for (int x : G[actual]) {
            if(x != actual){
                if (!visitados[x]) {
                visitados[x] = true; 
                cola.push(x);
                adevo[x] = adevo[actual] + 1;
            }else{
                int distActual = adevo[x];
                if(actual - x == 1 || -1){ // caso en que estan pegados, y si mi backedge es al anterior?? o el forward el de adelante  
                    adevo[x] = adevo[actual] + 1;   
                }else{ //osea es un forward//back
                    if(adevo[actual] +1 < abs(1 - x)){
                        adevo[x] = adevo[actual] +1;
                    }
                }
            }
            }   
        }
    }
    for(int p = 0; p < adevo.size();p++){
        std::cout << adevo[p];
    }
    return adevo;
}

int main(){
    cin >> N;
    int cont = 1;
    vector<vector<int>> G(N +1); // G es lista de adyacencias, 
    while(cont <= N){//cargo los atajos
        cin >> i;
        if(cont != N){
            G[cont].push_back(cont+1);
        }
        G[cont].push_back(i);
        cont++;
    }
    vector<bool> vis(N,false);
    vector<int> distancias(N,1);
    vector<int> aDevolver = bfsParaDistancia(G,1,vis,distancias);
}