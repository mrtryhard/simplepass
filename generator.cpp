#include "generator.hpp"

Generator::Generator(uint16_t len, bool special) 
    : m_length(len), m_allowSpecial(special), m_password(nullptr) {
    
    // This is a core assumption, otherwise this class doesn't make sense.    
    static_assert(CHAR_BIT == 8, "Generator requires signed char to be 8 bits!");
        
    m_rand.seed(std::random_device()());
}

Generator::~Generator() {
    clear();
}

void Generator::allowSpecial(bool allow) {
    m_allowSpecial = allow;
}

void Generator::clear() {
    delete [] m_password;
    m_password = nullptr;
    
    m_length = 0;
    m_allowSpecial = false;
}

void Generator::setLength(uint16_t len) {
    m_length = len;
}

char* Generator::generate() { 
    if(m_length == 0) return nullptr;
    
    // Regenerate buffer. 
    delete [] m_password;
    m_password = new char[m_length + 1]; 
	m_password[m_length] = '\0';

    // Generate the password, really.
    for(uint16_t i = 0; i < m_length; ++i) {
        m_password[i] = static_cast<char>(nextChar());
    }

    return m_password;
}

int16_t Generator::nextChar() {
    UIDist dist(33, 127);
    int16_t value;
        
	do {
		value = dist(m_rand);
	} while (!isNormal(value) && !m_allowSpecial);
    
    return value;
}

bool Generator::isNormal(const int16_t c) const {
    // On classic ascii, [33, 47], [58, 64], [91,96], [123,126] are special chars. 
    if(c >= 33 && c <= 47) return false;
    if(c >= 58 && c <= 64) return false;
    if(c >= 91 && c <= 96) return false;
    if(c >= 123 && c <= 126) return false;
    
    return true;
}
