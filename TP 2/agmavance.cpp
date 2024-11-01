#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

 
using namespace std;
int n, a, b, w;
vector<string> resultados;  
long long int m;
 
vector<vector<int>> armarAdyacencias(const vector<tuple<int,int,int>> elAGM){
    vector<vector<int>> listaADev(n+1);
    for(int i = 0; i < elAGM.size(); i++){
        int u = get<0>(elAGM[i]);
        int v = get<1>(elAGM[i]);
        listaADev[u].push_back(v);
        listaADev[v].push_back(u);
    }
    return listaADev ;
}
/*
void dfsMio(vector<int>& visitados,const vector<vector<pair<int,pair<int,int>>>>& adyacencias,int indice, int x,int y){
    // 1 cuando mi dfs actual lo recorrio
    visitados[x] = 1; // empece a ver
   // contador++;
    for(const auto& arista: adyacencias[x]){
        int u = arista.second.first;
        int v = arista.second.second;
        int id = arista.first;
        if (indice != id){
            int siguiente;
            if(x == u){
                siguiente = v;
            }else if(x == v){
                siguiente = u;
            }
         if(visitados[siguiente] != 1){
            dfsMio(visitados,adyacencias,indice,siguiente,y);
         }
      }
    } // termine de ver
  //  return contador; // contador son la cantidad de nodos que llego a contar, para aristas es +1
}

bool esPuente(vector<int> aDevo,const vector<vector<pair<int,pair<int,int>>>>& adyacenciasDELAGM,int indice ,int u, int v){
    aDevo[v] = 2;
    dfsMio(aDevo,adyacenciasDELAGM,indice,u,v);
        if(aDevo[v] == 2){
            return true; 
        }
    return false;
}*/

void esPuente(int v, int u,vector<string>& res,int pos ){
    resultados[pos] = "any";
}

vector<bool> visitado;
vector<int> tin, low;
int timer;
vector<vector<int>> adyacencias;

void dfs(int v, int p = -1,vector<vector<int>> adyacencias,vector<string> resultados ,int pos) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int u : adyacencias[v]) {
        if (u == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visitado[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v])
                esPuente(v, u,resultados,pos);
        }
    }
}

void find_bridges() {
    timer = 0;
    visitado.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs(i);
    }
}

int find_Set(int vertice, vector<int>& representantes){
    if(vertice == representantes[vertice]){
        return vertice;
    }
    representantes[vertice] = find_Set(representantes[vertice],representantes);
    return representantes[vertice];
}
 
void union_Set(int u, int v, vector<int>& representantes,vector<int>& ranks){
    int rep1 = find_Set(u,representantes);// rep1 es el representante del vertice u
    int rep2 = find_Set(v,representantes); // rep2 es el representante del vertice v
    if(ranks[rep1] == ranks[rep2]){ // si son iguales incremento cualquiera y le cambio el rep al otro
        ranks[rep1] = ranks[rep1] +1;
        representantes[rep2] = representantes[rep1];
    }else if(ranks[rep1] > ranks[rep2]){
        representantes[rep2] = representantes[rep1];
    }else{
        representantes[rep1] = representantes[rep2];
    }
}
 
void make_set(int j, vector<int>& representantes, vector<int>& ranks){
    representantes[j] = j;
    ranks[j] = 0; 
}
 
vector<string> kruskal(vector<tuple<int,int,int,int>>& grafoOriginal){
    //para este algoritmo me baso en el pseudocodigo de Kruskal definido en wikipedia https://en.wikipedia.org/wiki/Kruskal%27s_algorithm 
    vector<int> representantes(n+1);
    vector<int> ranks(n+1);
    for (int j = 1; j <= n; j++){
        make_set(j,representantes,ranks); //armo un set para c/nodo
    }
    vector<tuple<int,int,int,int>> aristasDelAgm; // aca guardo las aristas del agm
    vector<pair<int,vector<tuple<int,int,int,int>>>>cConexasGPrima;
    int i = 0;
    //vector<tuple<int,int,int>> noagregadas;
    while(i < grafoOriginal.size() ){ //aca armo el agm y veo hasta que arista incluyo
        pair<int,vector<tuple<int,int,int,int>>> aAgregar;
        vector<tuple<int,int,int,int>> aristasMismoPeso;
        vector<tuple<int,int,int>> gPrima;
        int avanzo = 0;
        for(int j = i;get<2>(grafoOriginal[j]) == get<2>(grafoOriginal[i]);i++){ // cargo los de mismo peso y voy armando el agm de paso
            j = i;
            int x = get<0>(grafoOriginal[j]);
            int y = get<1>(grafoOriginal[j]);
            int indiceOriginal = get<3>(grafoOriginal[j]); 
            int weight = get<2>(grafoOriginal[j]);
            aristasMismoPeso.push_back(grafoOriginal[j]);
            int repX = find_Set(x,representantes);
            int repY = find_Set(y,representantes);
            if((repX != repY) ){
                gPrima.push_back({repX,repY,indiceOriginal});
            }else{
                resultados[indiceOriginal] = "none";
            }
            avanzo = j;
        }
        adyacencias = armarAdyacencias(gPrima);
        find_bridges();
        for(int h = 0; h < gPrima.size();h++){
            int a = get<0>(gPrima[h]);
            int b = get<1>(gPrima[h]);
            int c = get<2>(gPrima[h]);
            int repA = find_Set(a,representantes);
            int repB = find_Set(b,representantes) ;
            if(!(visitado[repA]) || !(visitado[repB]) ){   
              //  bool es = esPuente(visitados,ady,h,a,b);
                    dfs(repA,repB,adyacencias,resultados,c);
               
            }
        }
        /*for(int h = 0; h < avanzo;h++){
            int a = get<0>(grafoOriginal[h]);
            int b = get<1>(grafoOriginal[h]);
            int c = get<2>(grafoOriginal[h]);
            //if(agregados[a] == 1 || agregados[b] == 1){ // (agregados[a] == 0) || (agregados[b] == 0) ||( agregados[a] == 1 || agregados[b] == 1))
            if((agregados[a] == 0 && agregados[b] == 1) || (agregados[b] == 0 && agregados[a] == 1) /*||( agregados[a] == 1 || agregados[b] == 1))){  
                bool es = esPuente(ady,h,a,b);
                if(es){
                    resultados[c].first = "any";
                }else{
                    resultados[c].first = "at least one";
                }
            }
        }*/
        for(const auto& [l,m,q] : gPrima){
            int repA = find_Set(l,representantes);
            int repB = find_Set(m,representantes);
            if(repA != repB){
                union_Set(repA,repB,representantes,ranks);
            }
        }
        adyacencias.clear();
        visitado.clear();
    } 
    return resultados;
}

 
int main(){
    cin >> n >> m;
    vector<tuple<int,int,int,int>> grafo;
    for(long long int k = 0; k < m ; k++){
        cin >> a >> b >> w; 
        grafo.push_back({a,b,w,k}); // en w voy a guardar los resultados en un vector de ese modo despues printeo
    }
    sort(grafo.begin(), grafo.end(), [](const tuple<int, int,int, int>& primero, const tuple<int,int, int, int>& segundo) {
        return get<2>(primero) < get<2>(segundo); 
    });
    visitado.assign(n+1,false);
    resultados.assign(m,"at least one");  
    vector<string> agm = kruskal(grafo); //nos devuelve su estado 
    for(int r = 0; r < agm.size();r++){
        cout << agm[r] << "\n";
    }
}
