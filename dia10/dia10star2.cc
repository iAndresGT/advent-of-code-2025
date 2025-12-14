#include <bits/stdc++.h>
#include <fstream>
#include <ortools/sat/cp_model.h>
using namespace operations_research;
using namespace sat;
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

int solve_cp_sat(vector<vector<int>>& deltas, vector<int>& objetivo){
    CpModelBuilder model;

    int B = deltas.size();      /// número de botones
    int N = objetivo.size();    /// número de contadores

    /// límite razonable para cada variable: nunca necesitas presionar más que max(objetivo)
    int LIM = 0;
    for (int x : objetivo) LIM = max(LIM, x);

    vector<IntVar> x;
    for(int i = 0; i < B; i++){
        x.push_back(model.NewIntVar(0, LIM, "x" + to_string(i)));
    }

    /// restricciones: sum(x[b] si b toca i) = objetivo[i]
    for(int i = 0; i < N; i++){
        LinearExpr sum;
        for(int b = 0; b < B; b++){
            for(int k : deltas[b]){
                if(k == i) sum += x[b];
            }
        }
        model.AddEquality(sum, objetivo[i]);
    }

    /// minimizar sum(x)
    model.Minimize(LinearExpr::Sum(x));

    CpSolverResponse resp = Solve(model.Build());

    if(resp.status() != CpSolverStatus::OPTIMAL &&
       resp.status() != CpSolverStatus::FEASIBLE){
        cerr << "ERROR: no hay solución CP-SAT\n";
        return -1;
    }

    /// devolver valor óptimo
    return (int)resp.objective_value();
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



        deltas.clear();
        used.clear();
        d.clear();


        for(int j = 1; j<lights[i].size()-1; j++){
            deltas.push_back(numrow(lights[i][j]));
        }

        vector<int> objetivo;
        objetivo = (numrow(lights[i][lights[i].size()-1]));
        vector<int> inicio(objetivo.size(), 0);


        int mejor = solve_cp_sat(deltas, objetivo);
        cout<<mejor<<endl;
        res += mejor;
    }
    cout<<res;
    return 0;
}





