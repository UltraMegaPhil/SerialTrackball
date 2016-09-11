#include <AltSoftSerial.h>          // Shouldn't have to do this, but we do.
#include "mouse_data.h"
#include "bluefruit_consumer.h"
#include "human_readable_consumer.h"
#include "microsoft_producer.h"
#include "led_debug.h"

// Mouse Data
MouseDataProducer *producer;
MouseDataConsumer *consumer;
MouseData mouseData;

const int HUMAN_READABLE_OUTPUT = 0;
const int BLUEFRUIT_OUTPUT      = 1;
const int outputMode            = BLUEFRUIT_OUTPUT;

LedDebug ledDebug(13, 250);

void setup() {  
    // Setup producer
    producer = new MicrosoftProducer(MicrosoftProducer::Ballpoint);
    producer->initialize();

    // Setup incoming serial port
    Serial.begin(producer->getSerialPortSpeed(), producer->getSerialPortConfig());

    // Setup consumer
    switch(outputMode) {
        case HUMAN_READABLE_OUTPUT:
            consumer = new HumanReadableConsumer();
            break;

        case BLUEFRUIT_OUTPUT:
            consumer = new BluefruitConsumer();
            break;

        default:
            consumer = 0;
    }

    if(consumer) {
        consumer->initialize();
    }

    ledDebug.initialize();
}

void loop() {
    if(Serial.available()) {
        if(producer->readIncomingSerialByte((byte)Serial.read(), &mouseData)) {
            if(consumer) {
                consumer->consumeMouseData(&mouseData);    
            }
            ledDebug.flash();
        }
    }
    ledDebug.update();
}

