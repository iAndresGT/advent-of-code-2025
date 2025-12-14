#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef pair<int,int> ii;

vector<int> extraerNumeros(string texto) {
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
    inFile.open("input2.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string linea;

    vector<string> in;

    while (getline(inFile,linea)){
        in.push_back(linea);
    }

    vector<vector<int>> numeros;
    vector<char> ops;

    for(int i=0;i<in.size()-1;i++){
        numeros.push_back(extraerNumeros(in[i]));
    }
    int n = in.size();
    for(int j = 0; j<in[n-1].size(); j++){
        if(in[n-1][j] == '*'){
            ops.push_back('*');
        }

        if(in[n-1][j] == '+'){
            ops.push_back('+');
        }
    }
    vector<long long> res(in[0].size(),0);

    for(int j = 0; j<numeros[0].size(); j++){
        for(int i = 0; i<numeros.size(); i++){
            if(ops[j] == '*'){
                if(res[j] == 0) res[j] = numeros[i][j];
                else res[j] *= numeros[i][j];
            }
            else{
                res[j] += numeros[i][j];
            }
        }
    }
    long long def = 0;
    for(int i = 0; i<ops.size(); i++){
        def += res[i];
    }
    cout<<def;
    return 0;
}









