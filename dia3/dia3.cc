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

    long long res = 0;

    for(int i = 0; i<in.size(); i++){
        vector<int> biggest(13,0);

        for(int z = 0; z<in[i].size(); z++){
            int num = in[i][z] - '0';
            for(int j = 1; j <= 12; j++){
                if(j == 12 && num > biggest[12]){
                    biggest[12] = num;
                }
                else if(num > biggest[j] && in[i].size() - z - 1 > 12 - j - 1){
                    cout<<num<<" es mas grande que "<<biggest[j]<<" en la posicion "<<j<<endl;
                    biggest[j] = num;
                    for(int it = j+1; it <= 12; it++){
                        biggest[it] = 0;
                    }
                    break;
                }
            }
        }
        long long a = 0;
        for(int z = 1; z<=12; z++){
            cout<<biggest[z];
            a = a*10;
            a = a+biggest[z];
        }
        cout<<endl;
        res += a;
        cout<<res<<endl;
    }
    return 0;
}



