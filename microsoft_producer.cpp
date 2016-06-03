#include "microsoft_producer.h"

/*
 * Microsoft Serial Mouse Protocol
 *              
 *              7   6   5   4       3   2   1   0
 * Byte 0:      1   1   LB  RB      Y7  Y6  X7  X6
 * Byte 1:      0   0   X5  X4      X3  X2  X1  X0
 * Byte 2:      0   0   Y5  Y4      Y3  Y2  Y1  Y0
 * 
 * 
 *  Microsoft Ballpoint Protocol (4 byte)
 *  
 *              7   6   5   4       3   2   1   0
 * Byte 0:      0   1   LB  RB      Y7  Y6  X7  X6
 * Byte 1:      0   0   X5  X4      X3  X2  X1  X0
 * Byte 2:      0   0   Y5  Y4      Y3  Y2  Y1  Y0
 * Byte 3:      0   0   XX  XX      B3  B4  Y8  X8
 *                                   |   |   +---+--------- I think these might be overflow bits? They don't seem super necessary
 *                                   +---+----------------- Extra buttons. Don't care.
 */

MicrosoftProducer::MicrosoftProducer(Family family) {
    switch(family) {
        case Standard3Byte:
            this->packetSize = 3;
            break;
            
        case Ballpoint4Byte:
            this->packetSize = 4;
            break;

        default:
            break;
    }
}

MicrosoftProducer::~MicrosoftProducer() {}

void MicrosoftProducer::initialize() {
    this->resetDataBuffer();    
}

int MicrosoftProducer::getSerialPortSpeed() {
    return 1200;    
}

byte MicrosoftProducer::getSerialPortConfig() {
    return SERIAL_7N1;
}

int MicrosoftProducer::readIncomingSerialByte(byte data, MouseData *output) {
    if(data & 0x40) {
        // Start of new packet
        this->resetDataBuffer();
    }
    dataBuffer[dataBufferIndex++] = data;

    if(dataBufferIndex >= this->packetSize) {                      // Packet ready to be consumed
        output->leftButtonPressed   = dataBuffer[0] & 0x20;
        output->rightButtonPressed  = dataBuffer[0] & 0x10;
        output->xDelta              = (((dataBuffer[0] & 0x03) << 6) | (dataBuffer[1] & 0x3F));
        output->yDelta              = (((dataBuffer[0] & 0x0C) << 4) | (dataBuffer[2] & 0x3F));

        resetDataBuffer();

        return 1;
    }
    
    return 0;    
}
        
void MicrosoftProducer::resetDataBuffer() {
    memset(this->dataBuffer, 0, DATA_BUFFER_SIZE);
    this->dataBufferIndex = 0;
}      

