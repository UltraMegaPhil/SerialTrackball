#ifndef MOUSE_DATA_H
#define MOUSE_DATA_H

#include <Arduino.h>

/*
 * Simple structure containing data baout the current state of a 2-button, 2-axis mouse
 */
struct MouseData {
    byte leftButtonPressed;         // Current state of the left button, 1 = pressed, 2 = not pressed
    byte rightButtonPressed;        // Current state of the right button, 1 = pressed, 2 = not pressed
    char xDelta;                    // Current x-axis movement amount
    char yDelta;                    // Current y-axis movement amount

    void reset() {
        this->leftButtonPressed     = 0;
        this->rightButtonPressed    = 0;    
        this->xDelta                = 0;
        this->yDelta                = 0;
    }    
};

/*
 * Reads incoming serial data from a physical port and converts it into a MouseData struct
 */
class MouseDataProducer {
    public:
        virtual void initialize() {}
    
        virtual int getSerialPortSpeed() {
            return 1200;    
        }
        
        virtual byte getSerialPortConfig() {
            return SERIAL_7N1;
        }

        // Process an incoming serial byte. If the byte completes an entire packet
        // of data, the supplied MouseData object is filled out and 1 is returned.
        // Otherwise 0 is returned and no change is made to the supplied MouseData object
        virtual int readIncomingSerialByte(byte, MouseData*) { return 0; }
};

/*
 * Processes MouseData
 */
class MouseDataConsumer {
    public: 
        virtual void initialize() {}
        virtual void consumeMouseData(MouseData*) {}
};

#endif

