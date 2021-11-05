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

    for (std::size_t t{0}; t < keysize; t++) {
        for (std::size_t i{0}; i < alphabetSize_; ++i) {
            if (alphabet_[i] == key_[i]) {
                Str2IntMap::value_type p0{ key_[t], i };
                Int2String::value_type p1{i, key_[t]};
                str_.insert( p0 );
                inte_.insert( p1 );
            }
        }
    }
    /// Store the playfir cipher key

}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    std::string input{inputText};
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
            ///   - Find the coords in the grid for each digraph
            ///   - Apply the rules to these coords to get 'new' coords
            ///   - Find the letter associated with the new coords
            /// return the text
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
            /// Loop over the input in Digraphs
            ///   - Find the coords in the grid for each digraph
            ///   - Apply the rules to these coords to get 'new' coords
            ///   - Find the letter associated with the new coords
            /// return the text
            break;
    }
    return input;
}