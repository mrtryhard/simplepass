#pragma once

#include <cstdint>
#include <climits>

#include <limits>
#include <random>

typedef std::uniform_int_distribution<int8_t> UIDist;

/**
 * Generator class. 
 * Generates the password with the given parameters.
 */
class Generator {
    
    using RNG = std::mt19937;    
public:
    Generator(uint16_t len, bool special);
    ~Generator();
    
    /**
     * Sets the flag for special chars.
     *
     * @param allow Determines if specials chars are allowed (true) or not (false).
     */
    void allowSpecial(bool allow);
    
    /**
     * Clears and resets the generator in its default state.
     */
    void clear();
    
    /**
     * Sets the length of the password.
     *
     * @param len Length of the password. 
     */
    void setLength(uint16_t len);
    
    /**
     * TODO: Replace with smart pointer ?
     * Generates the password
     *
     * @returns Password string.
     */
    char* generate();
    
private:
    /**
     * Gets the next randomly generated char.
     * This function handles the specialChar flag. 
     *
     * @returns Randomly generated ascii character. 
     */
    int8_t nextChar();
    
    /**
     * Determines if the given char is a normal char in the ascii set.
     *
     * @param c Character to verify.
     * @returns False if a special char, true otherwise.
     */
    bool isNormal(const int8_t c) const;
private:
    // STACK
    uint16_t m_length;          // Length of the generated password
    bool m_allowSpecial;        // Flag allowing special chars
    //bool m_isSimple;          // Simple mode determines if it can have word from a given 
                                // dictionary.
    RNG m_rand;                 
    
    // HEAP (owned)
    char* m_password;
};
