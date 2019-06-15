#ifndef DHT_H
#define DHT_H
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/* AM2302 library
 MIT license
 written by cactus.io with inspiration from the Adafruit Industries DHT22 library
 */

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

class AM2302 {

private:
    uint8_t data[6];
    uint8_t _pin, _count;
    unsigned long _lastreadtime;
    boolean firstreading;
    boolean read(void);
    
public:
    AM2302(uint8_t pin, uint8_t count=6);
    void begin(void);
    void readHumidity(void);
    void readTemperature(void);
    float computeHeatIndex_C(void);
    float computeHeatIndex_F(void);
    
    float humidity;
    float temperature_C;
    float temperature_F;
    
};
#endif
