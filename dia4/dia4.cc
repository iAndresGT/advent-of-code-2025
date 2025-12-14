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

    ///Guarda el array de string del archivo
    while (getline(inFile,linea)){
        in.push_back(linea);
    }
    vector<vector<int>> visited(in.size(), vector<int>(in[0].size(),0));
    long long res = 0;
    bool seguir = true;
    while(seguir){

        long long prov = 0;

        for(int i = 0; i<in.size(); i++){
            for(int j = 0; j< in[i].size(); j++){
                if(in[i][j] == '@'){
                    int x = 0;
                    if(i > 0){
                        if(in[i-1][j] == '@') x++;
                        if(j>0 && in[i-1][j-1] == '@') x++;
                        if(j+1 < in[i].size() && in[i-1][j+1] == '@') x++;
                    }
                    if(j>0 && in[i][j-1] == '@') x++;
                    if(j+1 < in[i].size() && in[i][j+1] == '@') x++;
                    if(i+1 < in.size()){
                        if(in[i+1][j] == '@') x++;
                        if(j>0 && in[i+1][j-1] == '@') x++;
                        if(j+1 < in[i].size() && in[i+1][j+1] == '@') x++;
                    }
                    if(x < 4){
                        prov++;
                        visited[i][j] = 1;
                    }
                }
            }
        }

        for(int i = 0; i<in.size(); i++){
            for(int j = 0; j<in[i].size(); j++){
                if(visited[i][j] == 1){
                    in[i][j] = '.';
                }
            }
        }
        if(prov == 0) seguir = false;
        else res += prov;
    }
    cout<<res;
    return 0;
}




