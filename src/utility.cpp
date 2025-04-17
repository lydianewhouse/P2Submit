#include "utility.h"

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd)
{
    //Initializes the vector we will return
    std::vector<char*> cstylevector;

    //Loops for each string in input vector
    for (int i = 0; i < static_cast<int>(cmd.size()); i++)
    {
        //Creates the cstyle string
        char* cstylestring = new char[cmd[i].length() + 1];

        for (int j = 0; j < static_cast<int>(cmd[i].length()); j++)
        {
            //Adds each character
            cstylestring[j] = cmd[i][j];
        }

        //Adds the terminating value
        cstylestring[cmd[i].length()] = '\0';

        //Adds to cstylevector
        cstylevector.push_back(cstylestring);

    }

    //Need to add nullptr to end for commands
    cstylevector.push_back(nullptr);

    return cstylevector;
}

// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter)
{
    //initalizes the vector of words
    std::vector<std::string> words;

    //Loops through all the characters in the string, checking for the delimiter
    //Creates word variable to store individual words
    std::string word;
    for (int i = 0; i < static_cast<int>(command.length()); i++)
    {
        
        if (command[i] == delimiter)
        {
            //Character is delimiter, adds word to vector
            words.push_back(word);

            //Resets word variable
            word = "";
        }
        else if (i == static_cast<int>(command.length()) - 1) //Checking to see if on last value, so end of word even without delimiter
        {
            //Adds letter to word
            word.push_back(command[i]);

            //Adds word to vector
            words.push_back(word);
        }
        else if (command[i] != delimiter)
        {
            //Adds letter to word
            word.push_back(command[i]);
        }
    }

    return words;

}