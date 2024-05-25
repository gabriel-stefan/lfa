#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int n; 
vector<int> stari; 
int m; 
int start, final; 
char inputChar, outputChar;
unordered_map<int, vector<tuple<int, char, char>>> tranzitii;
int S; 
int nrF; 
vector<int> stariFinale; 
int nrCuv; 
string cuv; 


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
        fin >> start >> final >> inputChar >> outputChar;
        tranzitii[start].emplace_back(final, inputChar, outputChar);
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


pair<bool, string> fst(string cuvant)
{
    int stareCurenta = S; 
    string output = "";
    for(char litera : cuvant) 
    {
        bool gasit = false;
        for(auto& trans : tranzitii[stareCurenta]) 
        {
            int next_state;
            char in_char, out_char;
            tie(next_state, in_char, out_char) = trans;
            if(in_char == litera) 
            {
                stareCurenta = next_state; 
                output += out_char; 
                gasit = true;
                break;
            }
        }
        if(!gasit)
        {
            return {false, ""}; 
        }
    }
    for(int final : stariFinale) 
    {
        if(final == stareCurenta) 
        {
            return {true, output};
        }
    }
    return {false, ""};
}

int main()
{
    citire(); 

    for (int i = 0; i < nrCuv; ++i) {
        fin >> cuv;
        auto result = fst(cuv);
        if(result.first) 
        {
            fout << "DA: " << result.second << "\n";
        } 
        else 
        {
            fout << "NU\n";
        }
    }
    
    return 0;
}
