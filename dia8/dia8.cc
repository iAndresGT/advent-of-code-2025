#include <bits/stdc++.h>
#include <fstream>

#define rep(i, ini, fin) for(int i = ini; i < fin; i ++)
#define lrep(i, ini, fin) for(int i = ini; i >= fin; i--)
#define lrepp(i, ini, fin, sum) for(int i = ini; i >= fin; i -= sum)
#define repp(i, ini, fin, sum) for(int i = ini; i < fin; i += sum)
#define nn in.size()
#define mm in[0].size()
#define vvl vector<vector<long long>>
#define vl vector<long long>

using namespace std;

typedef pair<int,int> ii;
typedef long long ll;

///Extraer los numeros de una línea (cualquier delimitador)
vector<long long> numrow(string texto, int id) {
    vector<long long> numeros;
    numeros.push_back(id);
    string numeroActual;

    for (char c : texto) {
        if (isdigit(c)) {
            numeroActual += c;
        } else if (!numeroActual.empty()) {
            numeros.push_back(stoll(numeroActual));
            numeroActual.clear();
        }
    }

    if (!numeroActual.empty()) {
        numeros.push_back(stoi(numeroActual));
    }

    return numeros;
}

///Extraer las palabras de una línea (delimitador que le digas)
vector<string> wordrow(const string& texto, const string& delimitadores) {
    vector<string> palabras;
    string palabraActual;

    for (char c : texto) {
        if (delimitadores.find(c) == string::npos) {
            palabraActual += c;
        } else if (!palabraActual.empty()) {
            palabras.push_back(palabraActual);
            palabraActual.clear();
        }
    }

    if (!palabraActual.empty()) {
        palabras.push_back(palabraActual);
    }

    return palabras;
}

vector<vector<int>> adj; ///adj[3][4] te dice las coordenadas adyacentes de (3,4)
queue<int> q;
vector<bool> used;

int bfs(int w){
    int elems = 1;
    q.push(w);
    used[w] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int u : adj[v]){
            if(!used[u]){
                used[u] = true;
                q.push(u);
                elems++;
            }
        }
    }
    return elems;
}


int main(){
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string linea;
    vector<string> in;

    ///Guarda el array de string del archivo
    while (getline(inFile,linea)){
        in.push_back(linea);
    }


    vvl grid;

    for(int i=0;i<in.size();i++){
        grid.push_back(numrow(in[i],i));
    }

    adj.resize(grid.size(),vector<int>());
    used.resize(grid.size(), false);

    ll res = 1;
    map<ii,int> counted;
    for(int it = 0; it<1000;it++){
        double best_prov = 100000000;
        int a = -1;
        int b = -1;
        rep(i,0,grid.size()){
            for(int j = i+1; j<grid.size(); j++){
                if(i == j ) continue;
                double euclidean = sqrt(pow(grid[i][1]-grid[j][1],2) + pow(grid[i][2]-grid[j][2],2) + pow(grid[i][3]-grid[j][3],2));
                if(euclidean <= best_prov && !counted.count({grid[i][0],grid[j][0]})){
                    a = grid[i][0];
                    b = grid[j][0];
                    best_prov = euclidean;
                }
            }
        }
        cout<<a<<" "<<b<<endl;
        counted[{a,b}] = 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> conjuntos;

    for(int i = 0; i<grid.size(); i++){
        if(!used[grid[i][0]]){
            conjuntos.push_back(bfs(grid[i][0]));
        }
    }

    sort(conjuntos.begin(),conjuntos.end(),greater<int>());


    for(int i = 0; i<conjuntos.size(); i++){
        if(i<3) res *= conjuntos[i];
        cout<<conjuntos[i]<<" ";
    }
    cout<<endl;

    cout<<res;

    return 0;
}




