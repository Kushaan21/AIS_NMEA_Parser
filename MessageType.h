/*
 * MessageType.h
 *
 *  Created on: Jul 24, 2024
 *      Author: kusha
 */

#ifndef MESSAGETYPE_H_
#define MESSAGETYPE_H_

#include <string>
#include <iostream>
#include <vector>
#include "AISDecoder.h"

using namespace std;

class MessageType: AISDecoder{
public:
	int getMessageType(const string& s){
				string x = subparser(s)[5];
				string binaryPayload;
				for (char c : x) {
				     binaryPayload += charTo6BitBinary(c);
				}

				int messageType = decodeInt(binaryPayload, 0, 6);
				return messageType;
			}
};


#endif /* MESSAGETYPE_H_ */
