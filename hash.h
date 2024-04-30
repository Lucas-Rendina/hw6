
#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        unsigned long long w[5] = {};

        HASH_INDEX_T resultHash = 0;
        std::string temp = k;
        
        for(size_t i = 0; i < 5; ++i) {
            if (k.length() > 6 * (4 - i)) {
                int len = 6;
                if (temp.length() > 6 && temp.length() % 6 != 0) {
                    len = temp.length() % 6;
                }

                std::string current = temp.substr(0, len);
                temp.erase(0, len);

                int power = current.size() - 1;
                for (int charPos = power; charPos >= 0; --charPos) {
                    char ch = current[charPos];
                    int numericval = letterDigitToNumber(ch);
                    w[i] += pow(36, power - charPos) * numericval;
                }
            }

            resultHash += rValues[i] * w[i];
        }
        return resultHash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

            letter = tolower(letter);
            if (isalpha(letter)) {
                return letter - 'a';  
            } else if (isdigit(letter)) {
                return 26 + (letter - '0'); 
            }
            return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

