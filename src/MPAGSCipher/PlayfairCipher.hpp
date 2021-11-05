#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <map>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayFair class
 */

/**
 * \class PlyFair
 * \brief Encrypt or decrypt text using the PlayFair cipher with the given key
 */
class PlayfairCipher {
  public: 
    /**
     * \brief Create a new PlayFair with the given key
     *
     * \param key the key to use in the cipher
     */
    PlayfairCipher(const std::string& key);
    /**
     * \brief Create a new PlayFair, converting the given string into the key
     *
     * \param key the key to use in the cipher
     */
    void setKey(const std::string& key);
    /**
     * \brief Create a new PlayFair with the given key
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText,
                            const CipherMode cipherMode);

  private:

    char convert(std::vector<std::size_t> npos);

    std::string input_{""};
    /**
     * 
     * \brief Used to determine the cipher character given the plain character and the key
     * 
     * \private alphabet_ 
     * 
     */
    const std::vector<char> alphabet_{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /**
     * 
     * \brief The size of the alphabet 
     * 
     * \private alphabetSize_ 
     */
    const std::size_t alphabetSize_{alphabet_.size()};

    /**
     * 
     * \brief The cipher key, essentially a constant shift to be applied 
     * 
     * \private key_ 
     */

    std::string key_{""};

    using Str2IntMap = std::map<char, std::vector<std::size_t>>;
    Str2IntMap str_;
    using Int2String = std::map<std::vector<std::size_t>,char>;
    Int2String inte_;
};

#endif