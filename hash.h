#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <ctime>
#include <cstdlib>

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

				// converting each char in k to int
				int temp[30];
				for (int i = 0; i < 30; i++){
					if (i < 30 - (int) k.size()){
						temp[i] = 0;
					}
					else {
						temp[i] = letterDigitToNumber(k[i - (30 - (int) k.size())]);
					}
				}

				// setting up w
				unsigned long long w[5];

				for (int i = 4; i >= 0; i--){
					unsigned long long w_val = 0;
					for (int k = 5; k >= 0; k--){
						// add last letter x 36 ^ exp
						w_val += temp[(i * 6) + k] * pow(36, 5 - k);
					}
					w[i] = w_val;
				}

			// hash the string
			HASH_INDEX_T h = rValues[0]* w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
			return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

				int ltr = (int) letter;
				// Number->ASCII: 0->48 to 9->57
				if (ltr >= 48 && ltr <= 57){
					ltr = ltr - 48 + 26;
				}
				// A->65 to Z->90, a->97 to z->122
				else{
					if (ltr >=65 && ltr <= 90){
						// convert to lowercase letter via ASCII
						ltr += 32;
					}
					ltr = ltr - 97;
				}
				return ltr;
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
