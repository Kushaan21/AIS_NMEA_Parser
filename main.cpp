/*
 * main.cpp
 *
 *  Created on: Jul 22, 2024
 *      Author: kusha
 */




#include <iostream>

#include "AISDynamicMessage.h"
#include "AISStaticMessage.h"
#include "MessageType.h"
using namespace std;

int main() {



    // Example complete AIS message
    string eg = "!AIVDM,1,1,,A,15MgK45P3@G?fl0E`JbR0OwT0@MS,0*4E";



    MessageType obj;
    cout << obj.getMessageType(eg)<< endl;

//    AISStaticMessage x;
//    x.parse(eg);
//    cout << x.getMessageType()<<endl;


    AISDynamicMessage x;
    x.parse(eg);
    cout << x.getMessageType()<<endl;
    cout << x.getTrueHeading()<< endl;
    cout << x.getChecksum()<<endl;
    cout << x.getTotalParts()<<endl;

    return 0;
}
