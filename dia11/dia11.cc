#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef long long ll;

vector<pair<int,int>> dirs = {{0,1},{1,0}, {0,-1}, {-1,0}};
//vector<pair<int,int>> dirs = {{0,1},{1,0}, {0,-1}, {-1,0}, {1,1},{1,-1}, {-1,-1}, {-1,1}};
///Extraer los numeros de una línea (cualquier delimitador)
vector<int> numrow(string texto) {
    vector<int> numeros;
    string numeroActual;

    for (char c : texto) {
        if (isdigit(c)) {
            numeroActual += c;
        } else if (!numeroActual.empty()) {
            numeros.push_back(stoi(numeroActual));
            numeroActual.clear();
        }
    }

    if (!numeroActual.empty()) {
        numeros.push_back(stoi(numeroActual));
    }

    return numeros;
}
// Extrae palabras usando múltiples delimitadores (cadenas completas)
vector<string> wordrow(const string& texto, const vector<string>& delimitadores) {
    vector<string> palabras;
    string palabraActual;
    size_t i = 0;

    while (i < texto.size()) {
        bool esDelimitador = false;
        size_t delimLen = 0;

        // Revisar si en la posición actual comienza algún delimitador
        for (const auto& d : delimitadores) {
            if (!d.empty() && texto.compare(i, d.size(), d) == 0) {
                esDelimitador = true;
                delimLen = d.size();
                break;
            }
        }

        if (esDelimitador) {
            if (!palabraActual.empty()) {
                palabras.push_back(palabraActual);
                palabraActual.clear();
            }
            i += delimLen;  // Saltar el delimitador completo
        } else {
            palabraActual += texto[i];
            ++i;
        }
    }

    if (!palabraActual.empty()) {
        palabras.push_back(palabraActual);
    }

    return palabras;
}

int caminos = 0;
unordered_map<string,bool> canReachDAC;
unordered_map<string,bool> canReachFFT;

void DFS(string node, unordered_map<string, vector<string>>& adj, unordered_map<string, bool>& visited, string fin, bool dac, bool fft) {
    // Marcar nodo como visitado
    visited[node] = true;

    if (node == "dac") dac = true;
    if (node == "fft") fft = true;

    if(!dac && !canReachDAC[node]) return;
    if(!fft && !canReachFFT[node]) return;
    //cout<<node<<endl;
    // Visitar recursivamente los nodos adyacentes a este
    for (string neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if(neighbor == fin){
                if(dac && fft) caminos++;
                else{} ///do nothing
            }
            else DFS(neighbor, adj, visited, fin, dac, fft);
        }
    }
    visited[node] = false;
}


void reachDFS(string u, unordered_map<string,bool> &seen, unordered_map<string,bool> &canReach, unordered_map<string, vector<string>> &graph)
{
    seen[u] = true;
    canReach[u] = true;

    for (auto v : graph[u]) {
        if (!seen[v]) {
            reachDFS(v, seen, canReach, graph);
        }
    }
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
    vector<string> delim = {": ", " "};
    vector<vector<string>> a;

    map<string,int> id;
    int ini;
    int fin;

    for(int i = 0; i<in.size(); i++){
        a.push_back(wordrow(in[i],delim));
    }

    unordered_map<string, vector<string>> graph;
    unordered_map<string, bool> visited;

    for(int i = 0; i<a.size(); i++){
        for(int j = 1; j<a[i].size(); j++){
            graph[a[i][0]].push_back(a[i][j]);
        }
    }


    unordered_map<string, vector<string>> graphalreves;
    ///Grafo inverso
    for (auto p : graph) {
        string u = p.first;
        for (auto v : p.second) {
            graphalreves[v].push_back(u);   // invierte la arista u -> v a v -> u
        }
    }

    unordered_map<string,bool> seen1;
    reachDFS("fft", seen1, canReachFFT,graphalreves);
    unordered_map<string,bool> seen2;
    reachDFS("dac", seen2, canReachDAC,graphalreves);

    DFS("svr",graph,visited,"out", false,false);



    cout<<caminos;
    return 0;
}





