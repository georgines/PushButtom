#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"
#include "PushButton.h"

Adafruit_MCP23X17 mcp;
PushButton b1;

void setup()
{
    

    // b1.registerModeFunction();
    Serial.begin(115200);

    if (!mcp.begin_I2C(0x20))
    {
        Serial.println("mcp nao iniciado");
        while (true)
            ;
    }

    b1.registerAction([](int read_value) {
        Serial.printf("O valor lido foi: %d", read_value);
        Serial.println();
    });

    b1.registerModeFunction([]( uint8_t pin, uint8_t mode){
        mcp.pinMode(pin, mode);
    });

    b1.registerReadFunction([](uint8_t pin)->uint8_t{
        return mcp.digitalRead(pin);
    });

    b1.setPin(8);
    b1.begin();

   /* for (int i = 0; i < 16; i++)
    {
      
        mcp.pinMode(i, OUTPUT);
        mcp.digitalWrite(i, HIGH);
        mcp.digitalRead(i);
    }*/
}
void loop()
{
    b1.run();
}