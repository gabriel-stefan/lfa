#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

void pda(const std::string& inputString) 
{
    std::stack<char> stack;
    stack.push('Z');  

    std::string input = inputString + 'e';
    std::string finalStates = "q2";
    std::string initialState = "q0";
    std::vector<std::vector<std::string>> reguli = {
        {"q0", "0", "Z", "q0", "0Z"},
        {"q0", "0", "0", "q0", "00"},
        {"q0", "1", "0", "q1", "e"},
        {"q1", "1", "0", "q1", "e"},
        {"q1", "e", "Z", "q2", "Z"}
    };

    char currentStackSymbol = 'Z';
    std::string currentState = initialState;

    for (char caracter : input) 
    {
        bool gasit = false;
        for (const auto& regula : reguli) 
        {
            if (regula[0] == currentState && regula[1][0] == caracter && regula[2][0] == currentStackSymbol) 
            {
                currentState = regula[3];
                if (regula[4].length() == 2) 
                {
                    stack.push(caracter);
                } 
                else if (regula[4] == "e" && stack.size() > 1) 
                {
                    stack.pop();
                }
                gasit = true;
                break;
            }
        }
        if (!gasit) 
        {
            break;
        }
        currentStackSymbol = stack.top();
    }

    if (currentState == "q2") 
    {
        fout << "Da\n"; 
    } 
    else 
    {
        fout << "Nu\n";  
    }
}

int main() 
{

    std::string inputString;
    fin >> inputString;

    pda(inputString);

    fin.close();
    fout.close();

    return 0;
}
