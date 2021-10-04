#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_MCP23X17.h" //Adafruit MCP23017 Arduino Library@^2.0.2
#include "PushButton.h"

const int MCP_EXPANSION_ADDRESS = 0X20;
const int MCP_PIN = 8;
const int MONITOR_SPEED = 115200;

const char* the_value_read_was = "The value read was: %d";
const char* mcp_not_started = "mcp not started";

using Georgines::PushButton;

Adafruit_MCP23X17 mcp;
PushButton mcp_button;

void actionCallback(unsigned char read_value)
{
    Serial.printf(the_value_read_was, read_value);
    Serial.println();
}

void mcpPinModeCallback(uint8_t pin, uint8_t mode)
{
    mcp.pinMode(pin, mode);
}

uint8_t mcpPinReadCallback(uint8_t pin)
{
    return mcp.digitalRead(pin);
}

void setup()
{

    Serial.begin(MONITOR_SPEED);

    if (!mcp.begin_I2C(MCP_EXPANSION_ADDRESS))
    {
        Serial.println(mcp_not_started);
        while (true)
            ;
    }

    mcp_button.registerAction(actionCallback);
    mcp_button.registerModeFunction(mcpPinModeCallback);
    mcp_button.registerReadFunction(mcpPinReadCallback);
    mcp_button.setPin(MCP_PIN);
    mcp_button.begin();
}

void loop()
{
    mcp_button.run();
}