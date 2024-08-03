#pragma once
#include <iostream>

namespace crypt {

#define XSTR_SEED ((__TIME__[7] - '0') * 1ull    + (__TIME__[6] - '0') * 10ull  + \
                   (__TIME__[4] - '0') * 60ull   + (__TIME__[3] - '0') * 600ull + \
                   (__TIME__[1] - '0') * 3600ull + (__TIME__[0] - '0') * 36000ull)

    constexpr unsigned long long linear_congruent_generator(unsigned rounds) {
        return 1013904223ull + (1664525ull * ((rounds > 0) ? linear_congruent_generator(rounds - 1) : (XSTR_SEED))) % 0xFFFFFFFF;
    }

#define Random() linear_congruent_generator(10)
#define XSTR_RANDOM_NUMBER(Min, Max) (Min + (Random() % (Max - Min + 1)))

    template <unsigned size>
    class Xor_string {
    public:
        const unsigned _nb_chars = (size - 1);
        char _string[size];
        unsigned char _key1 = XSTR_RANDOM_NUMBER(0x00, 0xA0);
        unsigned char _key2 = XSTR_RANDOM_NUMBER(0xA1, 0xFF);

        //���ܴ洢
        inline constexpr Xor_string(const char* string) : _string{}
        {
            for (unsigned i = 0u; i < size; ++i)
            {
                _string[i] = (string[i] ^ _key1) + _key2;   //����
            }
        }
        //����
        const char* decrypt() const
        {
            char* ret_string = const_cast<char*>(_string);
            for (unsigned i = 0; i < _nb_chars; i++)
            {
                ret_string[i] = (_string[i] - _key2) ^ _key1;   //����
            }
            ret_string[_nb_chars] = '\0';
            return ret_string;
        }
    };
   /* class Xor_String2 {
    public:
        unsigned _nb_chars;
        char* _string;
        unsigned char _key1 = XSTR_RANDOM_NUMBER(0x00, 0xA0);
        unsigned char _key2 = XSTR_RANDOM_NUMBER(0xA1, 0xFF);
        ULONG size = 0;
        inline  Xor_String2(const char* string) : _string{}
        {
            _string = (char*)string;
            size = strlen(string) + 1;
            _nb_chars = size - 1;
            for (unsigned i = 0u; i < size; ++i)
            {
                _string[i] = (string[i] ^ _key1) + _key2;   //����
            }
        }
        //����
        const char* decrypt() const
        {
            char* ret_string = const_cast<char*>(_string);
            for (unsigned i = 0; i < _nb_chars; i++)
            {
                ret_string[i] = (_string[i] - _key2) ^ _key1;   //����
            }
            ret_string[_nb_chars] = '\0';
            return ret_string;
        }
    };*/
    template <unsigned size>
    class Xor_stringW {
    public:
        const unsigned _nb_chars = (size - 1);
        WCHAR _string[size];
        unsigned char _key1 = XSTR_RANDOM_NUMBER(0x00, 0xA0);
        unsigned char _key2 = XSTR_RANDOM_NUMBER(0xA1, 0xFF);

        //���ܴ洢
        inline constexpr Xor_stringW(const WCHAR* string) : _string{}
        {
            for (unsigned i = 0u; i < size; ++i)
            {
                _string[i] = (string[i] ^ _key1) + _key2;   //����
            }
        }
        //����
        const WCHAR* decrypt() const
        {
            WCHAR* ret_string = const_cast<WCHAR*>(_string);
            for (unsigned i = 0; i < _nb_chars; i++)
            {
                ret_string[i] = (_string[i] - _key2) ^ _key1;   //����
            }
            ret_string[_nb_chars] = '\0';
            return ret_string;
        }

    };
}// END crypt NAMESPACE ========================================================

#define XorS(name, my_string)    constexpr crypt::Xor_string<(sizeof(my_string)/sizeof(char))> name(my_string)
#define XorString(my_string) []{ constexpr crypt::Xor_string<(sizeof(my_string)/sizeof(char))> expr(my_string); return expr; }().decrypt()
#define XorStringW(my_string) []{ constexpr crypt::Xor_stringW<(sizeof(my_string)/sizeof(WCHAR))> expr(my_string); return expr; }().decrypt()
#define _c( string ) (char*)XorString( string )

