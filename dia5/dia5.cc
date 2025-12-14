
#include <bits/stdc++.h>
#include <fstream>
using namespace std;



int main(){
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string linea;
    vector<string> in;
    vector<string> in2;
    int x;

    ///Guarda el array de string del archivo
    while (getline(inFile,linea)){
        if(linea == "") break;
        in.push_back(linea);
    }

    while (getline(inFile,linea)){
        if(linea == "") break;
        in2.push_back(linea);
    }
    vector<pair<long long,long long>> rangos;

    for(int i = 0; i<in.size(); i++){
        long long a,b;
        for(int j = 0; j<in[i].size(); j++){
            if(in[i][j] == '-'){
                a = stoll(in[i].substr(0,j));
                b = stoll(in[i].substr(j+1));
                break;
            }
        }

        rangos.push_back({a,b});
    }
    cout<<"y luego"<<endl;
    long long res = 0;
    sort(rangos.begin(),rangos.end());
    for(int z = 0; z<rangos.size(); z++){
        long long izq = rangos[z].first;
        long long der = rangos[z].second;
        //cout<<izq<<" "<<der<<endl;
        for(int it = 1; it < z; it++){
            //cout<<rangos[z-it].second<<endl;
            if(rangos[z-it].second >= izq){
                izq = rangos[z-it].second+1;
            }
        }
        //cout<<"cambia a "<<izq<<" "<<der<<endl;
        if(izq <= der) res += der - izq + 1;
    }
    cout<<res;
    return 0;
}



