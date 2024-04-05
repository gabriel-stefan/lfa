#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n; //numar de stari/noduri
vector<int> stari; //starile
int m; //numarul de tranzitii/muchii
int start, final; //informatii pentru tranzitii
char litera; 
unordered_map<int, vector<pair<int, char>>> tranzitii; //mapare tranzitii
int S; //starea initiala
int nrF; //numarul de stari finale
vector<int> stariFinale; //starile finale
int nrCuv; //numarul de cuvinte
string cuv; //cate un cuvant

void citire() 
{
    fin >> n;
    stari.resize(n);
    for(int i = 0; i < n; ++i)
    {
        fin >> stari[i];
    }
    fin >> m;
    for(int i = 0; i < m; ++i) 
    {
        fin >> start >> final >> litera;
        tranzitii[start].push_back({final,litera});
    }
    fin >> S;
    fin >> nrF;
    stariFinale.resize(nrF);
    for(int i = 0; i < nrF; ++i) 
    {
        fin >> stariFinale[i];
    }
    fin >> nrCuv;
}