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
        if(linea != ""){
            in.push_back(linea);
        }
    }

    ll res = 0;

    vector<int> piezas = {5,7,6,7,7,7};
    rep(i,24,nn){
        vector<int> q = numrow(in[i]);
        int x = q[0];
        int y = q[1];
        int usado = 0;
        rep(j,2,q.size()){
            usado += (piezas[j-2]*q[j]);
        }
        if(usado <= x*y) res++;

    }
    cout<<res;
    return 0;
}







