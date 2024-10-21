#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

vector<tuple<int,int,int>> pretendiente;
int n ,m, a, b, w;

int cantApariciones(tuple<int,int,int> aristita, vector<vector<tuple<int,int,int>>>& losagms){ // esta idea es recontra ieficiente porque mira todos los agms buscando arista por arista si pertenece
    int apariciones = 0;
    for(int t = 0; t <losagms.size();t++){
        for(int i = 0; i < losagms[t].size();i++)
        if(losagms[t][i] == aristita){
            apariciones++;
        }
    }
    return apariciones;
}

int find_Set(int vertice,const vector<int>& representantes){
    if(vertice == representantes[vertice]){
        return vertice;
    }
    return find_Set(representantes[vertice],representantes);
}

void union_Set(int u, int v, vector<int>& representantes,vector<int>& ranks){
    int rep1 = find_Set(u,representantes);// rep1 es el representante del vertice u
    int rep2 = find_Set(v,representantes); // rep2 es el representante del vertice v
    if(ranks[rep1] == ranks[rep2]){ // si son iguales incremento cualquiera y le cambio el rep al otro
        ranks[rep1] = ranks[rep1] +1;
        representantes[rep2] = representantes[rep2];
    }
    if(ranks[rep1] > ranks[rep2]){
        representantes[rep2] = representantes[rep1];
    }else{
        representantes[rep1] = representantes[rep2];
    }
}


void make_set(int j, vector<int>& representantes, vector<int>& ranks){
    representantes[j] = j;
    ranks[j] = 0; 
}

pair<vector<tuple<int,int,int>>, vector<pair<int,vector<tuple<int,int,int>>>>> kruskal(vector<tuple<int,int,int>>& grafoOriginal){
    //para este algoritmo me baso en el pseudocodigo de Kruskal definido en wikipedia https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
    vector<int> representantes(n+1);
    vector<int> ranks(n+1);
    set<tuple<int,int,int>> aristasSet;
    vector<pair<int,vector<tuple<int,int,int>>>> aristasMismoPeso;
    for (int j = 1; j <= n; j++){
        make_set(j,representantes,ranks); //armo un set para c/nodo
    }
    vector<tuple<int,int,int>> aristasDelAgm; // aca guardo las aristas del agm
    for(const auto& [x,y,weight] : grafoOriginal){
        if(find_Set(x,representantes) != find_Set(y,representantes)){
            aristasDelAgm.push_back({x,y,weight});
            union_Set(find_Set(x,representantes),find_Set(y,representantes),representantes,ranks);
            aristasSet.insert({x,y,weight});
        }else{// aca busco que si no la pude agregar si hay alguna que tenga el mismo peso
            bool agregada = false;
            for(int p = 0; p < aristasDelAgm.size();p++){
                
                if (weight == get<2>(aristasDelAgm[p]) && !agregada){
                    if(aristasMismoPeso.size() != 0){
                        for(int l = 0; l < aristasMismoPeso.size();l++){
                            if(aristasMismoPeso[l].first == weight){
                                aristasMismoPeso[l].second.push_back({x,y,weight});
                                agregada = true;
                            }
                        }
                    }
                    if(!agregada){
                        vector<tuple<int,int,int>> tup = {{x,y,weight}};
                        pair<int,vector<tuple<int,int,int>>> ag = {weight,tup};
                        aristasMismoPeso.push_back(ag);
                        agregada = true;
                    }
                }
            }
        }
    }
    return {aristasDelAgm,aristasMismoPeso}; //aca tengo el primer agm que me sabe generar y luego tengo las aristas que repitieron el peso
}


vector<vector<tuple<int,int,int>>> generar_todos_los_agms(const pair< vector<tuple<int,int,int>>, vector<pair<int,vector<tuple<int,int,int>>>>>& agm){
    vector<vector<tuple<int,int,int>>> aDevo;
    aDevo.push_back(agm.first);
    for(int f = 0; f < agm.second.size();f++){ //ve los pares con aristas repetidas
        for(int g = 0; g < agm.second[f].second.size();g++){ // ve especificamente la arista dentro de c/par
            tuple<int,int,int> elRepetidoDePeso = agm.second[f].second[g];
            pretendiente.clear();
            pretendiente.push_back(elRepetidoDePeso);
            int cantVecesQueSonIguales = 0;
            vector<tuple<int,int,int>> sinAgregarLaQueCambio;
            for(int r = 0; r < agm.first.size(); r++){
                if(get<2>(agm.first[r]) != get<2>(elRepetidoDePeso)){
                    pretendiente.push_back(agm.first[r]);
                }else{
                    cantVecesQueSonIguales++;
                    sinAgregarLaQueCambio.push_back(agm.first[r]);
                }
            }
            if(sinAgregarLaQueCambio.size() == 1){
                vector<tuple<int,int,int>> otroAgm = kruskal(pretendiente).first;
                if(otroAgm.size() == n-1){
                    aDevo.push_back(otroAgm);
                } 
            }else{
                vector<vector<tuple<int,int,int>>> posiblesAAGregar;
                for(int pi = 0; pi < sinAgregarLaQueCambio.size();pi++){
                    if(pi == 0){ // agrego todos menos el primero de sinAgregar
                        vector<tuple<int,int,int>> nuevo = pretendiente;
                        int contp = 1;
                        while(contp < sinAgregarLaQueCambio.size()){
                         nuevo.push_back(sinAgregarLaQueCambio[contp]);
                         contp++;
                        }
                        posiblesAAGregar.push_back(nuevo);
                    }else{
                        int contp = 0;
                        vector<tuple<int,int,int>> nuevo = pretendiente;
                        while(contp < sinAgregarLaQueCambio.size()){
                         if(contp != pi){
                            nuevo.push_back(sinAgregarLaQueCambio[contp]);
                         } 
                         contp++;
                        }
                        posiblesAAGregar.push_back(nuevo);
                    }
                }
                for(int cansado = 0; cansado < posiblesAAGregar.size(); cansado++){
                    vector<tuple<int,int,int>> otroAgm = kruskal(posiblesAAGregar[cansado]).first;
                    if(otroAgm.size() == n-1){
                        aDevo.push_back(otroAgm);
                    }
                }
            }
        }
    }
    return aDevo;
}

int main(){
    cin >> n >> m;
    vector<tuple<int,int,int>> grafo;
    for(int k = 0; k < m ; k++){
        cin >> a >> b >> w; 
        grafo.push_back({a,b,w});
    }
    vector<tuple<int,int,int>> grafoSinSorting = grafo;
    sort(grafo.begin(), grafo.end(), [](const tuple<int, int, int>& primero, const tuple<int, int, int>& segundo) {
        return get<2>(primero) < get<2>(segundo); 
    });
    pair<vector<tuple<int,int,int>>, vector<pair<int,vector<tuple<int,int,int>>>>> agm = kruskal(grafo);
       /* for (int j = 0; j < agm.first.size(); ++j) {  // Itera sobre las aristas del AGM
            auto [u, v, w] = agm.first[j];  // Descompone la tupla
            cout << "Arista: (" << u << ", " << v << ") - Peso: " << w << "\n";
        }
        cout << "\n";  */
    /*for(int i = 0; i < agm.second.size();i++){
        for(int j = 0; j < agm.second[i].second.size();j++){
            auto [u,v,w] = agm.second[i].second[j];
            cout << "Arista: (" << u << ", " << v << ") - Peso: " << w << "\n";
        }
        cout << "\n"; 
    }*/
    vector<vector<tuple<int,int,int>>> todosLosAgms = generar_todos_los_agms(agm);
    /*for (int i = 0; i < todosLosAgms.size(); ++i) {  // Itera sobre todos los AGM
        cout << "AGM " << i + 1 << ":\n";
        for (int j = 0; j < todosLosAgms[i].size(); ++j) {  // Itera sobre las aristas del AGM
            auto [u, v, w] = todosLosAgms[i][j];  // Descompone la tupla
            cout << "Arista: (" << u << ", " << v << ") - Peso: " << w << "\n";
        }
        cout << "\n";  // Línea en blanco entre los diferentes AGM
    }*/
    for(int contr = 0;contr < grafoSinSorting.size(); contr++){
        tuple<int,int,int> x = grafoSinSorting[contr];
        int cantAp = cantApariciones(x,todosLosAgms);
        if(cantAp == 0){
            std::cout << "none" << "\n";
        }
        if(cantAp == todosLosAgms.size()){
            std::cout << "any" << "\n";
        }
        if (cantAp > 0 && cantAp < todosLosAgms.size()){
            std::cout << "at least one" << "\n";
        }
    }
    return 0;
}