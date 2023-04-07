#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelp(
    std::string& in,
    std::queue<char> float_,
    const std::set<std::string>& dict,
    set<string>& rtn,
    size_t num)
{
    if(in.size() == 0) return;


    if(num == in.size())
    {
        if(dict.find(in) != dict.end()) rtn.insert(in);
        return;
    }

    if(in[num] == '-')
    {
        for(unsigned int i = 0; i < float_.size(); i++)
        {
            if(float_.front() == '0')
            {
                float_.pop();
                char i = 'a';
                while (i <= 'z') 
                {
                    in[num] = i;
                    wordleHelp(in, float_, dict, rtn, num+1);
                    i++;
                }
                in[num] = '-';
                float_.push('0');
            }
            else
            {
                in[num] = float_.front();
                float_.pop();
                wordleHelp(in, float_, dict, rtn, num+1);
                float_.push(in[num]);
                in[num] = '-';
            }
        }
    }
    else wordleHelp(in, float_, dict, rtn, num+1);




}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int dash = 0;
    queue<char> float_;
    set<string> rtn;
    string in_ = in;

    for(unsigned int i = 0; i < in.size(); i++)
    {
        if(in[i] == '-') dash++;
    }

    for(unsigned int i = 0; i < floating.size(); i++)
    {
        float_.push(floating[i]);
    }

    for(unsigned int i = 0; i < (dash-(floating.size())); i++)
    {
        float_.push('0');
    }


    wordleHelp(in_, float_, dict, rtn, 0);

    return rtn;
}

// Define any helper functions here
