#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h"

Adafruit_MCP23X17 mcp;

void setup()
{
    Serial.begin(115200);

    if (!mcp.begin_I2C(0x21))
    {
        Serial.println("mcp nao iniciado");
        while (true)
            ;
    }

    for (int i = 0; i < 16; i++)
    {
        mcp.pinMode(i, OUTPUT);
        mcp.digitalWrite(i, HIGH);
        
    }
}
void loop()
{

}