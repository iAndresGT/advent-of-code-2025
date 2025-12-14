#include<bits/stdc++.h>
using namespace std;

#define ii pair<int,int>
#define ll long long


struct Point{
    long long x;
    long long y;
};

struct Arista{
    Point A;
    Point B;
};

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
        numeros.push_back(stoll(numeroActual));
    }

    return numeros;
}

bool pointInBorder(Point A, Point ini, Point fin) {
    ///Misma columna
    if (ini.x == fin.x) {
        if (A.x != ini.x) return false;
        int ymin = min(ini.y, fin.y);
        int ymax = max(ini.y, fin.y);
        return (A.y >= ymin && A.y <= ymax);
    }

    ///Misma fila
    if (ini.y == fin.y) {
        if (A.y != ini.y) return false;
        int xmin = min(ini.x, fin.x);
        int xmax = max(ini.x, fin.x);
        return (A.x >= xmin && A.x <= xmax);
    }

    /// No es un segmento recto horizontal/vertical
    return false;
}


bool pointInPolygon(Point P, vector<Arista>& lados){
    int intersecciones = 0;

    for(int i = 0; i<lados.size(); i++){
        Point A = lados[i].A;
        Point B = lados[i].B;
        if(pointInBorder(P, lados[i].A, lados[i].B)) return true;

        bool intersect = (A.y > P.y) != (B.y > P.y);

        if(intersect) {
            double xIntersect =
                A.x + (double)(P.y - A.y) * (double)(B.x - A.x) / (double)(B.y - A.y);

            if (P.x < xIntersect)
                intersecciones++;
        }
    }

    return (intersecciones%2 == 1); ///si corta nº par está fuera, si es impar está dentro
}

bool crossRectanglePolygon(vector<Arista> rectangle, vector<Arista>& lados){

    for(int a = 0; a<rectangle.size(); a++){
        Arista curr = rectangle[a];
        if(curr.A.x == curr.B.x){
            for(int j = curr.A.y; j<= curr.B.y; j++){
                Point p = {curr.A.x, j};
                if(!pointInPolygon(p, lados)){
                    return true;
                }
            }
        }
        else{
            for(int i = curr.A.x; i<= curr.B.x; i++){
                Point p = {i, curr.A.y};
                if(!pointInPolygon(p, lados)){
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{

    ifstream inFile;
    inFile.open("inputP.txt");
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

    vector<Arista> aristas;
    for(int i=0;i<in.size();i++){
        vector<long long> n = numrow(in[i]);
        swap(n[0], n[1]);
        pos.push_back(n);
    }


    ll best = 0;
    ///first = l, second = r
    for(int i = 0; i<pos.size(); i++){
        Arista arista = {{pos[i][0], pos[i][1]},{pos[(i+1)%pos.size()][0], pos[(i+1)%pos.size()][1]}};
        aristas.push_back(arista);
    }

    sort(pos.begin(),pos.end());
    for(int i = 0; i<pos.size(); i++){
        for(int j = i+1; j<pos.size(); j++){

            vector<Arista> lados;
            Point A = {pos[i][0], pos[i][1]};
            if(!pointInPolygon(A, aristas)) continue;
            Point B = {pos[i][0], pos[j][1]};
            if(!pointInPolygon(B, aristas)) continue;
            Point C = {pos[j][0], pos[i][1]};
            if(!pointInPolygon(C, aristas)) continue;
            Point D = {pos[j][0], pos[j][1]};
            if(!pointInPolygon(D, aristas)) continue;

            lados.push_back({A,B});
            lados.push_back({A,C});
            lados.push_back({B,D});
            lados.push_back({C,D});


            if(crossRectanglePolygon(lados, aristas)) continue;
            //cout<<A.x<<" "<<A.y<<", "<<D.x<<" "<<D.y<<" sirve"<<endl;
            cout<<i<<" "<<j<<" sirve"<<endl;
            ll aa = abs(pos[i][0] - pos[j][0]) + 1;
            ll bb = abs(pos[i][1] - pos[j][1]) + 1;
            //cout<<a<<" "<<b;
            if(aa*bb > best) best = aa*bb;
        }
    }

    cout<<best;


    return 0;
}


//4595816092 too high
//2141097084 no es
