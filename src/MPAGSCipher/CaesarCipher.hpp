#ifndef MPAGSCIPHER_CAESARCIPHER_HPP
#define MPAGSCIPHER_CAESARCIPHER_HPP

#include "CipherMode.hpp"

#include <cstddef>
#include <string>
#include <vector>

/**
 * \file CaesarCipher.hpp
 * \brief Contains the declaration of the CaesarCipher class
 */

/**
 * \class CaesarCipher
 * \brief Encrypt or decrypt text using the Caesar cipher with the given key
 */
class CaesarCipher {
  public:
    /**
     * \brief Create a new CaesarCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit CaesarCipher(const std::size_t key);

    /**
     * \brief Create a new CaesarCipher, converting the given string into the key
     *
     * \param key the string to convert into the key to be used in the cipher
     */
    explicit CaesarCipher(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText,
                            const CipherMode cipherMode) const;
    

  private:
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
    
    std::size_t key_{0};
};

#endif