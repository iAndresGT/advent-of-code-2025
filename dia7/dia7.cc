#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef pair<int,int> ii;

///Extraer los numeros de una línea (cualquier delimitador)
vector<long long> extraerNumeros(string texto) {
    vector<long long> numeros;
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
vector<string> extraerPalabras(const string& texto, const string& delimitadores) {
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
vector<int> d;
vector<bool> used;

void bfs(int w){
    q.push(w);
    used[w] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int u : adj[v]){
            if(!used[u]){
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
            }
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


    int res = 0;
    for(int i=1;i<in.size();i++){
        for(int j = 0; j<in[i].size(); j++){
            if(in[i][j] == '^'){
                if(in[i-1][j] == '|') res++;
                if(j>0) in[i][j-1] = '|';
                if(j+1 < in[i].size()) in[i][j+1] = '|';
            }

            else if(in[i-1][j] == 'S' || in[i-1][j] == '|'){
                in[i][j] = '|';
            }

        }
    }

    for(int i=1;i<in.size();i++){
        for(int j = 0; j<in[i].size(); j++){
            cout<<in[i][j];
        }
        cout<<endl;
    }

    cout<<res;

    return 0;
}



