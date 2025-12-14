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

int nodes;
int auxnodes;

int lightInt(string light){
    int res = 0;
    for(int i = 0; i<light.size(); i++){
        if(light[i] == '#'){
            res += pow(2,light.size() - i - 1);
        }
    }
    return res;
}

string lightString(int light){
    string res = "";
    while(light/2 > 0){
        if(light%2 == 1) res = "#" + res;
        else res = "." + res;
        light = light/2;
    }
    if(light == 1) res = "#" + res;
    else res = "." + res;
    if(res.length() < auxnodes){
        for(int z = res.length(); z < auxnodes; z++){
            res = "." + res;
        }
    }

    return res;
}


vector<vector<int>> deltas;
queue<int> q;
vector<int> d;
vector<bool> used;

void bfs(int w){
    q.push(w);
    used[w] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(vector<int> del : deltas){
            string aux = lightString(v);
            //cout<<aux<<" ";
            for(int i = 0; i<del.size(); i++){
                if(aux[del[i]] == '.') aux[del[i]] = '#';
                else aux[del[i]] = '.';
            }
            //cout<<" - "<<aux<<endl;
            int u = lightInt(aux);
            if(!used[u]){
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
            }
        }
    }
    //cout<<endl;
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
    vector<string> delim = {"[","] ", "(",") (", ") {", "}"};
    vector<vector<string>> lights;
    for(int i = 0; i<in.size(); i++){
        lights.push_back(wordrow(in[i],delim));
    }


    ll res = 0;
    for(int i = 0; i<lights.size(); i++){
        nodes = pow(2,lights[i][0].size());
        auxnodes = lights[i][0].size();
        //cout<<nodes<<endl;
        ///lights[0], situacion final
        deltas.clear();
        used.clear();
        d.clear();
        deltas.resize(lights.size()-2,vector<int>());
        used.resize(nodes, false);
        d.resize(nodes,0);


        int destino = lightInt(lights[i][0]);
        //cout<<destino<<endl;
        //cout<<lightString(destino)<<endl;
        int inicio = 0;

        for(int j = 1; j<lights[i].size()-1; j++){
            deltas.push_back(numrow(lights[i][j]));
        }



        bfs(inicio);

        res += d[destino];
    }
    cout<<res;
    return 0;
}




