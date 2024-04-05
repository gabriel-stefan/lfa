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

bool dfs(int stare, const string& cuv, int pos)
{
    if(pos == cuv.size()) 
    {
        bool gasit = 0;
        for(int final : stariFinale) 
        {
            if(final == stare) 
            {
                gasit = 1;
                break;
            }
        }
        return gasit;
    }

    for(auto tranzitie : tranzitii[stare])
    {
        if(tranzitie.second == cuv[pos]) 
        {
            if(dfs(tranzitie.first, cuv, pos + 1))
            {
                return true;
            }
        }
    }
}

bool nfa(string cuv)
{
    return dfs(S, cuv, 0);
}

int main()
{
    citire();

    for (int i = 0; i < nrCuv; ++i) {
        fin >> cuv;
        if(nfa(cuv)) 
        {
            fout << "DA\n";
        } 
        else 
        {
            fout << "NU\n";
        }
    }

    return 0;
}