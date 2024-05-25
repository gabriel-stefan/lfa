#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");


map<string, string> cyk(const string &input, map<string, string> &dp, const vector<pair<string, string>> &grammar) {
    if (dp.find(input) != dp.end()) 
    {
        return dp;
    } 
    else 
    {
        if (input.size() == 1) 
        {
            dp[input] = "";
            for (const auto &notation : grammar) {
                if (notation.second == input) {
                    dp[input] += notation.first;
                }
            }
            sort(dp[input].begin(), dp[input].end());
            return dp;
        } 
        else 
        {
            dp[input] = "";
            for (size_t i = 1; i < input.size(); ++i) 
            {
                string splitted1 = input.substr(0, i);
                string splitted2 = input.substr(i);
                string computed1 = cyk(splitted1, dp, grammar)[splitted1];
                string computed2 = cyk(splitted2, dp, grammar)[splitted2];
                if (!computed1.empty() && !computed2.empty()) 
                {
                    for (char var1 : computed1) 
                    {
                        for (char var2 : computed2) 
                        {
                            for (const auto &notation : grammar) 
                            {
                                if (notation.second == string(1, var1) + var2 && dp[input].find(notation.first) == string::npos) 
                                {
                                    dp[input] += notation.first;
                                }
                            }
                        }
                    }
                }
            }
            sort(dp[input].begin(), dp[input].end());
            return dp;
        }
    }
}

void print_cyk(const string &input, const vector<pair<string, string>> &grammar) {
    map<string, string> dp;
    map<string, string> rez = cyk(input, dp, grammar);
    if (rez[input] != "[]" && rez[input].find('S') != string::npos) 
    {
        fout << "Da" << '\n';
    } 
    else 
    {
        fout << "Nu" << '\n';
    }
}

int main() 
{

   
    if (!fin.is_open() & !fout.is_open()) 
    {
        cout << "Nu s-au gasit fisierele." << '\n';
        return 1;
    }

    int num;
    fin >> num;

    vector<pair<string, string>> grammar;
    for (int i = 0; i < num; ++i) 
    {
        string stanga, dreapta;
        fin >> stanga >> dreapta;
        grammar.emplace_back(stanga, dreapta);
    }

    string input;
    fin >> input;

    print_cyk(input, grammar);

    fin.close();
    fout.close();

    return 0;
}




