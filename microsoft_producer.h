#ifndef MICROSOFT_BALLPOINT_PRODUCER_H
#define MICROSOFT_BALLPOINT_PRODUCER_H

#include <Arduino.h>
#include "mouse_data.h"

/*
 * Produces MouseData based off incoming serial data conforming to
 * the Microsoft serial mouse protocol
 */
class MicrosoftProducer : public MouseDataProducer {
    public:
        enum Family {
            Standard        = 0,
            Ballpoint,

            NumFamilies
        };

        MicrosoftProducer(Family f);
        ~MicrosoftProducer();
    
        virtual void initialize();
        virtual int getSerialPortSpeed();
        virtual byte getSerialPortConfig();
        virtual int readIncomingSerialByte(byte data, MouseData *output);
        
    private:
        int dataBufferLength() { return dataBufferIndex; }
        void resetDataBuffer();
        int bufferContainsValidPacket();
        int processDataBuffer(MouseData *output);
        
        static const int DATA_BUFFER_SIZE = 16;
        byte dataBuffer[DATA_BUFFER_SIZE];
        int dataBufferIndex;
        Family family;
};

#endif

