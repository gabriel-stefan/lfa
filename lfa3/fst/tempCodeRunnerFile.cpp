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
                output += out_char; // Add the output character
                gasit = true;
                break;
            }
        }
        if(!gasit)
        {
            return {false, ""}; // No valid transition found
        }
    }
    // Check if the current state is a final state
    for(int final : stariFinale) 
    {
        if(final == stareCurenta) 
        {
            return {true, output};
        }
    }
    return {false, ""};
}