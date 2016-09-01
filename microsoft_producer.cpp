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

struct FamilyData {
    int packetSize;
    int baud;
    int portConfig;
};

const FamilyData FAMILY_DATA[MicrosoftProducer::Family::NumFamilies] = {
    { 3, 1200, SERIAL_7N1 },        // Standard
    { 4, 1200, SERIAL_7N1 }         // Ballpoint
};

MicrosoftProducer::MicrosoftProducer(Family f) :
    family(f) {}

MicrosoftProducer::~MicrosoftProducer() {}

void MicrosoftProducer::initialize() {
    this->resetDataBuffer();    
}

int MicrosoftProducer::getSerialPortSpeed() {
    return FAMILY_DATA[this->family].baud;
}

byte MicrosoftProducer::getSerialPortConfig() {
    return FAMILY_DATA[this->family].portConfig;
}

int MicrosoftProducer::readIncomingSerialByte(byte data, MouseData *output) {
    if(data & 0x40) {
        // Start of new packet
        this->resetDataBuffer();
    }
    dataBuffer[dataBufferIndex++] = data;

    return this->processDataBuffer(output);
}
        
void MicrosoftProducer::resetDataBuffer() {
    memset(this->dataBuffer, 0, DATA_BUFFER_SIZE);
    this->dataBufferIndex = 0;
}

int MicrosoftProducer::bufferContainsValidPacket() {
    return ((this->dataBufferLength() > 0) && 
        (this->dataBufferLength() >= FAMILY_DATA[this->family].packetSize) &&
        (this->dataBuffer[0] & 0x40));
}

int MicrosoftProducer::processDataBuffer(MouseData *output) {
    if(this->bufferContainsValidPacket()) {
        output->leftButtonPressed   = this->dataBuffer[0] & 0x20;
        output->rightButtonPressed  = this->dataBuffer[0] & 0x10;
        output->xDelta              = (((this->dataBuffer[0] & 0x03) << 6) | (this->dataBuffer[1] & 0x3F));
        output->yDelta              = (((this->dataBuffer[0] & 0x0C) << 4) | (this->dataBuffer[2] & 0x3F));

        return 1;
    }

    return 0;
}

