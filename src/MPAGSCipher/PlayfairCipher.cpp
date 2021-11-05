#include "PlayfairCipher.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <map>


PlayfairCipher::PlayfairCipher(const std::string& key)
: key_{key}
{
}

void PlayfairCipher::setKey(const std::string& key) 
{
    /// Store the original key
    key_ = key;
    /// Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
    /// Remove non-alpha characters
    key_.erase(std::remove_if(key_.begin(), key_.end(),
            [](unsigned char ch){ return !std::isalpha(ch); }
        ),
        key_.end());
    /// Change J -> I 
    std::replace(key_.begin(), key_.end(), 'J','I');
    /// Remove duplicated letters
    key_.erase(std::remove_if(key_.begin(),key_.end(),
        [&](unsigned char ch){return key_.find(ch); }
        ),
        key_.end());
    /// Store the coords of each letter
    
    std::size_t keysize{key_.length()};

    std::vector<std::size_t> pos{0,0};

    for (std::size_t t{0}; t < keysize; t++) {
        if (t < 5) {
            pos[0] = 0;
            pos[1] = t;
        } else if (t >=5 && t <= 10) {
            pos[0] = 0;
            pos[1] = t-5;
        } else if (t >=10 && t < 15) {
            pos[0] = 0;
            pos[1] = t-10;
        } else if (t >=15 && t < 20) {
            pos[0] = 0;
            pos[1] = t-15;
        } else if (t >=20 && t < 25) {
            pos[0] = 0;
            pos[1] = t-20;
        }
        Str2IntMap::value_type p0{ key_[t], pos};
        Int2String::value_type p1{pos, key_[t]};
        str_.insert( p0 );
        inte_.insert( p1 );
    }
    /// Store the playfir cipher key

}

char PlayfairCipher::convert(std::vector<std::size_t> npos) {
        auto cher1 = inte_.find(npos);
        char nchar = (*cher1).second;
        return nchar;
    }

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) 
{
    std::string input = inputText;
    /// Change J → I
    switch (cipherMode) {
        case CipherMode::Encrypt:
            std::replace(input.begin(), input.end(), 'J','I');
            /// If repeated chars in a digraph add an X or Q if XX
            for (std::size_t i; i < input.length(); i++) {
                if (input[i] == input[i-1] && input[i] == input[i-2]) {
                    input[i] = 'Q';
                    input[i-1] = 'Q';
                } else if (input[i] == input[i-1]) {
                    input[i] = 'X';
                }
            }
            /// if the size of input is odd, add a trailing Z
            if (input.length() % 2 != 0) {
                input.append("Z");
            }
            /// Loop over the input in Digraphs
            for (std::size_t i; i < input.length(); i+=2) {
            ///   - Find the coords in the grid for each digraph
                auto iter1 = str_.find(input[i]);
                auto iter2 = str_.find(input[i+1]);
                std::vector<std::size_t> val1 = (*iter1).second;
                std::vector<std::size_t> val2 = (*iter2).second;
                std::vector<std::size_t> npos{0,0};
                std::vector<std::size_t> npos2{0,0};
            ///   - Apply the rules to these coords to get 'new' coords
                if (val1[0] == val2[0]) {
                    /// First i
                    npos = {val1[0],val1[1]+1};
                    input[i] = convert(npos);
                    /// Second i
                    npos2 = {val2[0],val2[1]+1};
                    input[i+1] = convert(npos2);
                } else if (val1[1] == val2[1]) {
                    /// First i
                    npos = {val1[0]+1,val1[1]};
                    input[i+1] = convert(npos);

                    /// Second i
                    npos2 = {val2[0],val2[1]+1};
                    input[i+1] = convert(npos2);

                } else if (abs(val1[1]-val2[1]) == 0 && val1[1] != val2[1] && abs(val1[0]-val2[0]) == 1) {
                    
                    if (val1[0] == 0) {
                        /// First i 
                        npos = { npos[0], npos[1]+4};
                        input[i] = convert(npos2);

                        /// Second i
                        npos2 = {val2[0],val2[1]-4};
                        input[i+1] = convert(npos2);
                    } else {
                        /// First i 
                        npos = { npos[0], npos[1]-4};
                        input[i] = convert(npos);

                        /// Second i
                        npos2 = {val2[0],val2[1]+4};
                        input[i+1] = convert(npos2);
                    }
                }
            }
            break;

        case CipherMode::Decrypt:
            std::replace(input.begin(), input.end(), 'I','J');
            /// If repeated chars in a digraph add an X or Q if XX
            for (std::size_t i; i < input.length(); i++) {
                if (input[i] == 'Q') {
                    input[i] = input[i-2];
                    input[i-1] = input[i-2];
                } else if (input[i] == 'X') {
                    input[i] = input[i-1];
                }
            }
            /// if the size of input is odd, add a trailing Z
            if (input.length() % 2 != 0) {
                input.pop_back();
            }

            for (std::size_t i; i < input.length(); i+=2) {
            ///   - Find the coords in the grid for each digraph
                auto iter1 = str_.find(input[i]);
                auto iter2 = str_.find(input[i+1]);
                std::vector<std::size_t> val1 = (*iter1).second;
                std::vector<std::size_t> val2 = (*iter2).second;
                std::vector<std::size_t> npos{0,0};
                std::vector<std::size_t> npos2{0,0};

                if (val1[0] == val2[0]) {
                        /// First i
                        npos = {val1[0],val1[1]-1};
                        input[i] = convert(npos);
                        /// Second i
                        npos2 = {val2[0],val2[1]-1};
                        input[i+1] = convert(npos2);
                } else if (val1[1] == val2[1]) {
                        /// First i
                        npos = {val1[0]-1,val1[1]};
                        input[i+1] = convert(npos);

                        /// Second i
                        npos2 = {val2[0],val2[1]-1};
                        input[i+1] = convert(npos2);

                } else if (abs(val1[1]-val2[1]) == 0 && val1[1] != val2[1] && abs(val1[0]-val2[0]) == 1) {
                        
                        if (val1[0] == 0) {
                            /// First i 
                            npos = { npos[0], npos[1]-4};
                            input[i] = convert(npos2);

                            /// Second i
                            npos2 = {val2[0],val2[1]+4};
                            input[i+1] = convert(npos2);
                        } else {
                            /// First i 
                            npos = { npos[0], npos[1]+4};
                            input[i] = convert(npos);

                            /// Second i
                            npos2 = {val2[0],val2[1]-4};
                            input[i+1] = convert(npos2);
                        }
                    }
            }
            break;
    }
    return input;
}