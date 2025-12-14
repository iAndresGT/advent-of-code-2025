

#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef pair<int,int> ii;

int main(){
    ifstream inFile;
    inFile.open("input.txt");
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

    int n = in.size();

    char op;
    vector<long long> res;
    long long x = 0;
    for(int j = 0; j<in[0].size(); j++){
        if(in[n-1][j] == '*'){
            op = '*';
            res.push_back(x);
            x = 0;
        }
        else if(in[n-1][j] == '+'){
            op = '+';
            res.push_back(x);
            x = 0;
        }
        long long num = 0;
        for(int i = 0; i<n; i++){
            if(isdigit(in[i][j])){
                string s = in[i];
                s = s.substr(j,1);
                //cout<<s<<endl;
                num = num*10 + stoi(s);
            }
        }
        cout<<num<<endl;
        if(num != 0){
            if(op == '*'){
                if(x == 0) x = num;
                else x *= num;
            }
            else{
                x += num;
            }
        }


    }
    res.push_back(x);

    long long def = 0;
    for(int i = 0; i<res.size(); i++){
        def += res[i];
    }
    cout<<def;
    return 0;
}









