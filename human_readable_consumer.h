#ifndef HUMAN_READABLE_CONSUMER_H
#define HUMAN_READABLE_CONSUMER_H

#include <Arduino.h>
#include <AltSoftSerial.h>
#include "mouse_Data.h"

/*
 * Consumes incoming MouseData and dumps human-readable output to 
 * an AltSoftSerial port (transmits on pin 9)
 */
class HumanReadableConsumer : public MouseDataConsumer {
    public:
        void initialize();
        void consumeMouseData(MouseData *data);

    private:
        AltSoftSerial serialOut;
};

#endif

