/*
 * AISDecoder.h
 *
 *  Created on: Jul 22, 2024
 *      Author: kusha
 */

#ifndef AISDECODER_H_
#define AISDECODER_H_

#include <string>
#include <iostream>

#include <sstream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

class AISDecoder {
public:



	vector<string> subparser (const string& s){
	       	stringstream ss(s);
	       	string token;
	       	vector<string> parsedValues;

	       	        while (getline(ss, token, ',')) {
	       	            if (token.empty()) {
	       	                token = "0";
	       	            }
	       	            parsedValues.push_back(token);
	       	        }
	       	 return parsedValues;
	       }


protected:
    string charTo6BitBinary(char c) {
        int value = c - 48;
        if (value > 40) value -= 8;
        return bitset<6>(value).to_string();
    }

    // Function to decode an integer from a binary string
    int decodeInt(const string& binaryString, int startBit, int length) {
        string bits = binaryString.substr(startBit, length);
        return bitset<32>(bits).to_ulong();
    }

    // Function to decode a signed integer from a binary string
    int decodeSignedInt(const string& binaryString, int startBit, int length) {
        string bits = binaryString.substr(startBit, length);
        int value = bitset<32>(bits).to_ulong();
        if (value >= pow(2, length - 1)) {
            value -= pow(2, length);
        }
        return value;
    }

    // Function to decode a double from a binary string
    double decodeDouble(const string& binaryString, int startBit, int length, double resolution) {
        string bits = binaryString.substr(startBit, length);
        int intValue = bitset<32>(bits).to_ulong();
        return intValue * resolution;
    }


    string decodeString(const string& binaryString, int startBit, int length) {
            string result;
            for (int i = startBit; i < startBit + length; i += 6) {
                int value = decodeInt(binaryString, i, 6);
                if (value <= 31) value += 64;
                result += static_cast<char>(value);
            }
            return result;
        }

public:
    virtual ~AISDecoder() {}
};


#endif /* AISDECODER_H_ */
