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
    int x;

    ///Guarda el array de string del archivo
    while (getline(inFile,linea)){
        in.push_back(linea);
    }
    int pos = 50;
    int res = 0;
    for(int i = 0; i<in.size(); i++){
        int sum = stoi(in[i].substr(1));
        if(in[i][0] == 'L'){
            for(int i = 0; i<sum; i++){
                pos--;
                if(pos==0) res++;
                if(pos == -1) pos = 99;
            }
        }
        else{
            for(int i = 0; i<sum; i++){
                pos++;
                if(pos==100){
                    res++;
                    pos = 0;
                }
            }
        }
    }
    cout<<res;
    return 0;
}


