#include<bits/stdc++.h>
using namespace std;

#define ii pair<int,int>
#define ll long long
///Extraer los numeros de una línea (cualquier delimitador)
vector<long long> numrow(string texto) {
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

int main()
{

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

    vector<vector<long long>> pos;


    for(int i=0;i<in.size();i++){
        pos.push_back(numrow(in[i]));
    }

    ll best = 0;
    for(int i = 0; i<pos.size(); i++){
        for(int j = i; j<pos.size(); j++){
            ll a = abs(pos[i][0] - pos[j][0]) + 1;
            ll b = abs(pos[i][1] - pos[j][1]) + 1;
            //cout<<a<<" "<<b;
            if(a*b > best) best = a*b;
        }
    }

    cout<<best;


    return 0;
}

