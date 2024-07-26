/*
 * AISDynamicMessage.h
 *
 *  Created on: Jul 22, 2024
 *      Author: kusha
 */

#ifndef AISDYNAMICMESSAGE_H
#define AISDYNAMICMESSAGE_H

#include "AISDecoder.h"
#include <iostream>

using namespace std;

class AISDynamicMessage : public AISDecoder {

private:
	string packetType;
	string channel;
	int totalParts;
	int thisPart;
	int partID;
	string checksum;

	string payload;

	int messageType;
	int repeatIndicator;
	 int MMSI;
	 int navigationalStatus;
	 int rateOfTurn;
	 double speedOverGround;
	 int positionAccuracy;
	 double longitude;
	 double latitude;
	 double courseOverGround;
	 int trueHeading;
	 int timeStamp;
	 int specialManoeuvre;
	 int spare;
	 int raimFlag;
	 int communicationState;

	 string binaryPayload;

public:


    void parse(const string& aisMessage) {


    	vector<string> parsedValues ;
    	parsedValues =  subparser (aisMessage);

    	size_t asteriskPos = parsedValues.back().find('*');
    	//unknown = (parsedValues.back().substr(0, asteriskPos));
    	checksum = (parsedValues.back().substr(asteriskPos + 1));

    	packetType = parsedValues[0];
    	totalParts = stoi(parsedValues[1]);
    	thisPart = stoi(parsedValues[2]);
    	partID = stoi(parsedValues[3]);
    	channel = parsedValues[4];
    	payload = parsedValues[5];




        // Convert payload from ASCII to binary

        for (char c : payload) {
            binaryPayload += charTo6BitBinary(c);
        }

        // Decode message ID (bits 1-6)
         messageType = decodeInt(binaryPayload, 0, 6);

        // Decode repeat indicator (bits 7-8)
         repeatIndicator = decodeInt(binaryPayload, 6, 2);

        // Decode userID (bits 9-38)
         MMSI = decodeInt(binaryPayload, 8, 30);

        // Decode navigational status (bits 39-42)
         navigationalStatus = decodeInt(binaryPayload, 38, 4);

        // Decode rate of turn (bits 43-50)
         rateOfTurn = decodeSignedInt(binaryPayload, 42, 8);

        // Decode speed over ground (bits 51-60)
         speedOverGround = decodeDouble(binaryPayload, 50, 10, 0.1);

        // Decode position accuracy (bits 61)
         positionAccuracy = decodeInt(binaryPayload, 60, 1);

        // Decode longitude (bits 62-89)
         longitude = decodeSignedInt(binaryPayload, 61, 28) / 600000.0;

        // Decode latitude (bits 90-116)
         latitude = decodeSignedInt(binaryPayload, 89, 27) / 600000.0;

        // Decode course over ground (bits 117-128)
         courseOverGround = decodeDouble(binaryPayload, 116, 12, 0.1);

        // Decode true heading (bits 129-137)
         trueHeading = decodeInt(binaryPayload, 128, 9);

        // Decode time stamp (bits 138-143)
         timeStamp = decodeInt(binaryPayload, 137, 6);

        // Decode special manoeuvre (bits 144-145)
         specialManoeuvre = decodeInt(binaryPayload, 143, 2);

        // Decode spare (bits 146-148)
         spare = decodeInt(binaryPayload, 145, 3);

        // Decode RAIM flag (bits 149)
         raimFlag = decodeInt(binaryPayload, 148, 1);

        // Decode communication state (bits 150-168)
         communicationState = decodeInt(binaryPayload, 149, 19);

    }
public:

    int getMessageType() const { return messageType; }
       int getRepeatIndicator() const { return repeatIndicator; }
       int getUserID() const { return MMSI; }
       int getNavigationalStatus() const { return navigationalStatus; }
       int getRateOfTurn() const { return rateOfTurn; }
       double getSpeedOverGround() const { return speedOverGround; }
       int getPositionAccuracy() const { return positionAccuracy; }
       double getLongitude() const { return longitude; }
       double getLatitude() const { return latitude; }
       double getCourseOverGround() const { return courseOverGround; }
       int getTrueHeading() const { return trueHeading; }
       int getTimeStamp() const { return timeStamp; }
       int getSpecialManoeuvre() const { return specialManoeuvre; }
       int getSpare() const { return spare; }
       int getRaimFlag() const { return raimFlag; }
       int getCommunicationState() const { return communicationState; }

       string getPacketType() const { return packetType; }
       string getChannel() const { return channel; }
       int getTotalParts() const { return totalParts; }
       int getThisPart() const { return thisPart; }
       int getPartID() const { return partID; }
       string getChecksum() const { return checksum; }





};

#endif // AISDYNAMICMESSAGE_H
