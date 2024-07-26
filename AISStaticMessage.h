/*
 * AISStaticMessage.h
 *
 *  Created on: Jul 22, 2024
 *      Author: kusha
 */

#ifndef AISSTATICMESSAGE_H
#define AISSTATICMESSAGE_H

#include "AISDecoder.h"
#include <iostream>
#include <vector>

using namespace std;

class AISStaticMessage : public AISDecoder {

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
    int aisVersion;
    int imoNumber;
    string callSign;
    string vesselName;
    int shipType;
    int dimensionToBow;
    int dimensionToStern;
    int dimensionToPort;
    int dimensionToStarboard;
    int positionFixType;
    int etaMonth;
    int etaDay;
    int etaHour;
    int etaMinute;
    double maxDraught;
    string destination;
    int dte;
    int spare;

    string binaryPayload;

public:

    void parse(const string& aisMessage) {
        vector<string> parsedValues;
        parsedValues = subparser(aisMessage);

        size_t asteriskPos = parsedValues.back().find('*');
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
        //cout<< binaryPayload.length();
        if (binaryPayload.length() < 424) {
                   throw runtime_error("Binary payload is too short for a type 5 message");
         }

        // Decode fields from binary payload
        messageType = decodeInt(binaryPayload, 0, 6);
        repeatIndicator = decodeInt(binaryPayload, 6, 2);
        MMSI = decodeInt(binaryPayload, 8, 30);
        aisVersion = decodeInt(binaryPayload, 38, 2);
        imoNumber = decodeInt(binaryPayload, 40, 30);
        callSign = decodeString(binaryPayload, 70, 42);
        vesselName = decodeString(binaryPayload, 112, 120);
        shipType = decodeInt(binaryPayload, 232, 8);
        dimensionToBow = decodeInt(binaryPayload, 240, 9);
        dimensionToStern = decodeInt(binaryPayload, 249, 9);
        dimensionToPort = decodeInt(binaryPayload, 258, 6);
        dimensionToStarboard = decodeInt(binaryPayload, 264, 6);
        positionFixType = decodeInt(binaryPayload, 270, 4);
        etaMonth = decodeInt(binaryPayload, 274, 4);
        etaDay = decodeInt(binaryPayload, 278, 5);
        etaHour = decodeInt(binaryPayload, 283, 5);
        etaMinute = decodeInt(binaryPayload, 288, 6);
        maxDraught = decodeDouble(binaryPayload, 294, 8, 0.1);
        destination = decodeString(binaryPayload, 302, 120);
        dte = decodeInt(binaryPayload, 422, 1);
        spare = decodeInt(binaryPayload, 423, 1);
    }

    // Getters for the parsed fields
    int getMessageType() const { return messageType; }
    int getRepeatIndicator() const { return repeatIndicator; }
    int getMMSI() const { return MMSI; }
    int getAisVersion() const { return aisVersion; }
    int getImoNumber() const { return imoNumber; }
    string getCallSign() const { return callSign; }
    string getVesselName() const { return vesselName; }
    int getShipType() const { return shipType; }
    int getDimensionToBow() const { return dimensionToBow; }
    int getDimensionToStern() const { return dimensionToStern; }
    int getDimensionToPort() const { return dimensionToPort; }
    int getDimensionToStarboard() const { return dimensionToStarboard; }
    int getPositionFixType() const { return positionFixType; }
    int getEtaMonth() const { return etaMonth; }
    int getEtaDay() const { return etaDay; }
    int getEtaHour() const { return etaHour; }
    int getEtaMinute() const { return etaMinute; }
    double getMaxDraught() const { return maxDraught; }
    string getDestination() const { return destination; }
    int getDte() const { return dte; }
    int getSpare() const { return spare; }

    string getPacketType() const { return packetType; }
    string getChannel() const { return channel; }
    int getTotalParts() const { return totalParts; }
    int getThisPart() const { return thisPart; }
    int getPartID() const { return partID; }
    string getChecksum() const { return checksum; }

};

#endif // AISSTATICMESSAGE_H
