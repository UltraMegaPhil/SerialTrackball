#ifndef LED_DEBUG_H
#define LED_DEBUG_H

class LedDebug {
    public:
        LedDebug(const int pin, const long flashTimeMS);
        ~LedDebug();

        void initialize();
        void update();

        void flash();

    private:
        const int ledPin;
        const unsigned long flashTimeMS;
        unsigned long lastFlashTime;
};

#endif

