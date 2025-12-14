#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef long long ll;

vector<pair<long long,long long>> dirs = {{0,1},{1,0}, {0,-1}, {-1,0}};
//vector<pair<long long,long long>> dirs = {{0,1},{1,0}, {0,-1}, {-1,0}, {1,1},{1,-1}, {-1,-1}, {-1,1}};
///Extraer los numeros de una línea (cualquier delimitador)
vector<long long> numrow(string texto) {
    vector<long long> numeros;
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


unordered_map<string,long long> id;
vector<string> rid;


long long getID(string s) {
    if (!id.count(s)) {
        id[s] = id.size();
        rid.push_back(s);
    }
    return id[s];
}


long long countPaths(vector<pair<string,string>> &edges, string ini, string fin){
    for (auto &e : edges) {
        getID(e.first);
        getID(e.second);
    }
    long long n = id.size();

    ///Grafo dirigido
    vector<vector<long long>> graph(n);
    vector<long long> indegree(n, 0);

    for (auto &e : edges) {
        long long u = id[e.first];
        long long v = id[e.second];
        graph[u].push_back(v);
        indegree[v]++;
    }

    ///Topological sort (algoritmo de Kahn)
    queue<long long> q;
    for (long long i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<long long> topoOrder;
    while (!q.empty()) {
        long long u = q.front();
        q.pop();
        topoOrder.push_back(u);
        for (long long v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0){
               q.push(v);
            }
        }
    }

    ///DP para contar caminos
    vector<long long> ways(n, 0);
    long long source = id[ini];
    long long destination = id[fin];

    ways[source] = 1;

    for (long long u : topoOrder) {
        for (long long v : graph[u])
            ways[v] += ways[u];
    }

    return ways[destination];
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

    map<string,long long> id;
    long long ini;
    long long fin;

    for(long long i = 0; i<in.size(); i++){
        a.push_back(wordrow(in[i],delim));
    }

    unordered_map<string, vector<string>> graph;

    for(long long i = 0; i<a.size(); i++){
        for(long long j = 1; j<a[i].size(); j++){
            graph[a[i][0]].push_back(a[i][j]);
        }
    }


    vector<pair<string,string>> edges;

    for (auto p : graph) {
        string u = p.first;
        for (string v : p.second) {
            edges.push_back({u, v});
        }
    }
    long long res1 = countPaths(edges,"svr","dac")*countPaths(edges,"dac","fft")*countPaths(edges,"fft","out");
    long long res2 = countPaths(edges,"svr","fft")*countPaths(edges,"fft","dac")*countPaths(edges,"dac","out");
    cout<<res1+res2;
    return 0;
}






