#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

 
using namespace std;
vector<vector<pair<int,int>>> adyacencias;
int n, a, b, w;
vector<string> resultados;  
long long int m;
vector<int> visitados;// en este guardo todos los que cambiaron para no tener que hacer assign constantemente
vector<bool> visitado;
vector<int> tin, low;
int timer;

void armarAdyacencias(const vector<tuple<int,int,int>>& elAGM){
    for(int i = 0; i < elAGM.size(); i++){
        int u = get<0>(elAGM[i]);
        int v = get<1>(elAGM[i]);
        int indice = get<2>(elAGM[i]);
        adyacencias[u].push_back({v,indice});
        adyacencias[v].push_back({u,indice});
    }
}


void esPuente(int v){
    resultados[v] = "any";

}

void dfs(int v,int indice,int p = -1) { //para este algoritmo de puentes me baso en el algoritmo de tarjan para encontrar puentes en una sola corrida de dfs con time of entry y low
    visitado[v] = true;                 // este lo encontre en esta pagina, paso creditos https://cp-algorithms.com/graph/bridge-searching.html
    tin[v] = low[v] = timer++;
    visitados.push_back(v);
    int parent_skipped = 0;
    for (const auto& [u,ind] : adyacencias[v]) {
        if (u == p && parent_skipped < 1) {
           parent_skipped ++;
           continue;
        }
        if (visitado[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u,ind,v);
            low[v] = min(low[v], low[u]);
         //   cout << "low en " << u << low[u] << " tin en " << v << tin[v] << "\n"; 
            if (low[u] > tin[v]){
                esPuente(ind);
            }
        }
    }
}


int find_Set(int vertice, vector<int>& representantes){
    if(vertice == representantes[vertice]){
        return vertice;
    }
    representantes[vertice] = find_Set(representantes[vertice],representantes); //hago path compression
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
        //vector<tuple<int,int,int,int>> aristasMismoPeso;
        vector<tuple<int,int,int>> gPrima;
        for(int j = i;get<2>(grafoOriginal[j]) == get<2>(grafoOriginal[i]);i++){ // cargo los de mismo peso y voy armando el agm de paso
            j = i;
            int x = get<0>(grafoOriginal[j]);
            int y = get<1>(grafoOriginal[j]);
            int indiceOriginal = get<3>(grafoOriginal[j]); 
            int weight = get<2>(grafoOriginal[j]);
            //aristasMismoPeso.push_back(grafoOriginal[j]);
            int repX = find_Set(x,representantes);
            int repY = find_Set(y,representantes);
            if((repX != repY) ){
                gPrima.push_back({repX,repY,indiceOriginal}); // si conectan comp conexas distintas lo sumo a g'
            }else{
                resultados[indiceOriginal] = "none"; //caso contrario loopean en la comp conexa y son none
            }
        }
        timer = 0;
        armarAdyacencias(gPrima);
        for(int h = 0; h < gPrima.size();h++){ //encuentro los puentes corriendo dfs sobre las no visitadas
            int a = get<0>(gPrima[h]);
            int b = get<1>(gPrima[h]);
            int c = get<2>(gPrima[h]);
            int repA = find_Set(a,representantes);
            int repB = find_Set(b,representantes) ;
            if(!(visitado[repA]) || !(visitado[repB]) ){   
                  if(!visitado[repB]){
                    dfs(repB,c);
                  }else{
                    dfs(repA,c); 
                  }
            }
        }

        for(const auto& [l,m,q] : gPrima){ // hago el union set para aglomerar todo en una sola comp conea
            int repA = find_Set(l,representantes);
            int repB = find_Set(m,representantes);
            if(repA != repB){
                union_Set(repA,repB,representantes,ranks);
            }
        }
        for(int o : visitados){ // mantenimiento de las estructuras
            visitado[o] = false;
            tin[o] = -1;
            low[o] = -1;
            adyacencias[o].clear();
        }
        visitados.clear();
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
    //hago sorting por peso, la tupla es tal que {u,v,peso,posicion en la que entro}
    sort(grafo.begin(), grafo.end(), [](const tuple<int, int,int, int>& primero, const tuple<int,int, int, int>& segundo) {
        return get<2>(primero) < get<2>(segundo); 
    });
    visitado.assign(n+1,false);
    resultados.assign(m,"at least one");
    tin.assign(n+1, -1);
    low.assign(n+1, -1);  
    adyacencias.assign(n+1,{});
    vector<string> agm = kruskal(grafo); //nos devuelve su estado 
    for(int r = 0; r < agm.size();r++){
        cout << agm[r] << "\n";
    }
}
