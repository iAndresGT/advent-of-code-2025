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
    getline(inFile,linea);
    int it = 0;
    for(int i = 0; i<linea.size(); i++){
        if(linea[i] == ','){
            string s = linea.substr(it, i-it);
            it = i+1;
            in.push_back(s);
        }
    }

    in.push_back(linea.substr(it));
    long long res = 0;
    for(int i = 0; i<in.size(); i++){
        string s = in[i];
        long long num1;
        long long num2;
        long long num11;
        long long num22;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '-'){
                string a = s.substr(0,i);
                string b = s.substr(i+1);
                string a1;
                string b1;
                if(a.size() > 1) a1 = s.substr(0,i/2);
                else a1 = "1";
                a1 += a1;
                cout<<a<<" "<<b<<" "<<a1<<endl;
                num1 = stoll(a);
                num2 = stoll(b);
                num11 = stoll(a1);

                while(num11 <= num2){

                    if(num11 >= num1) res += num11;

                    a1 = a1.substr(0,a1.size()/2);
                    long long aux = stoll(a1) + 1;
                    a1 = to_string(aux) + to_string(aux);
                    num11 = stoll(a1);
                }
            }
        }
        cout<<res<<endl;
    }

    return 0;
}



