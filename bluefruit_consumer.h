#ifndef BLUEFRUIT_CONSUMER_H
#define BLUEFRUIT_CONSUMER_H

#include <Arduino.h>
#include <AltSoftSerial.h>
#include "mouse_Data.h"

/*
 * Consumes incoming MouseData and dumps output compatible with the
 * AdaFruit Bluefruit EZ-Key on an AltSoftSerial port (transmits on pin 9)
 */
class BluefruitConsumer : public MouseDataConsumer {
    public:
        void initialize();
        void consumeMouseData(MouseData *data);

    private:

        void fillOutputBuffer(byte leftButton, byte rightButton, char xDelta, char yDelta);
        void resetOutputBuffer();

    
        static const int BF_DATA_BUFFER_SIZE = 9;
        
        byte outputBuffer[BF_DATA_BUFFER_SIZE];
        AltSoftSerial serialOut;
};

#endif

