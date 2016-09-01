#include "human_readable_consumer.h"

void HumanReadableConsumer::initialize() {
    this->serialOut.begin(9600);
    this->serialOut.print("Mouse output ready!\n");
}

void HumanReadableConsumer::consumeMouseData(MouseData *data) {
    if(data) {
        if(data->leftButtonPressed) {
            serialOut.print("[  ON  ] ");
        } else {
            serialOut.print("[  OFF ] ");        
        }
        if(data->rightButtonPressed) {
            serialOut.print("[  ON   ] ");
        } else {
            serialOut.print("[  OFF  ] ");        
        }
        serialOut.print("\n");
    
        serialOut.print("  X: ");
        serialOut.print((char) data->xDelta, DEC);
        serialOut.print("\n");
    
        serialOut.print("  Y: ");
        serialOut.print((char) data->yDelta, DEC);
        serialOut.print("\n");
    }
}

