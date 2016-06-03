#include "bluefruit_consumer.h"
#include "mouse_data.h"

void BluefruitConsumer::initialize() {
    this->serialOut.begin(9600);
    this->resetOutputBuffer();
}

void BluefruitConsumer::consumeMouseData(MouseData *data) {
    if(data) {
        this->resetOutputBuffer();
        this->fillOutputBuffer(data->leftButtonPressed, data->rightButtonPressed, data->xDelta, data->yDelta);   

        for(int i = 0; i < BF_DATA_BUFFER_SIZE; ++i) {
            serialOut.write(this->outputBuffer[i]);
        }
    }
}

void BluefruitConsumer::fillOutputBuffer(byte leftButton, byte rightButton, char xDelta, char yDelta) {
    this->outputBuffer[0]       = 0xFD;
    this->outputBuffer[1]       = 0x00;
    this->outputBuffer[2]       = 0x03;
    this->outputBuffer[3]       = ((leftButton ? 0x01 : 0x00) | (rightButton ? 0x02 : 0x00));
    this->outputBuffer[4]       = xDelta;
    this->outputBuffer[5]       = yDelta;
    this->outputBuffer[6]       = 0x00;
    this->outputBuffer[7]       = 0x00;
    this->outputBuffer[8]       = 0x00;
}

void BluefruitConsumer::resetOutputBuffer() {
    memset(outputBuffer, 0, BF_DATA_BUFFER_SIZE);
}

