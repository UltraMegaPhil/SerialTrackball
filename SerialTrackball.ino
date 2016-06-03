#include <AltSoftSerial.h>          // Shouldn't have to do this, but we do.
#include "mouse_data.h"
#include "bluefruit_consumer.h"
#include "human_readable_consumer.h"
#include "microsoft_producer.h"

// Mouse Data
MouseDataProducer *producer;
MouseDataConsumer *consumer;
MouseData mouseData;

const int HUMAN_READABLE_OUTPUT = 0;
const int BLUEFRUIT_OUTPUT      = 1;
const int outputMode            = HUMAN_READABLE_OUTPUT;


void setup() {  
    // Setup producer
    producer = new MicrosoftProducer(MicrosoftProducer::Ballpoint4Byte);
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
}

void loop() {
    if(Serial.available()) {
        if(producer->readIncomingSerialByte((byte)Serial.read(), &mouseData)) {
            if(consumer) {
                consumer->consumeMouseData(&mouseData);    
            }
        }
    }
}

