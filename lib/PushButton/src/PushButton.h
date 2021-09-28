/*
 * PushButton.h
 *
 *  Created on: 30 de abr de 2019
 *      Author: Georgines
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#define PUSHBUTTON_VERSION "1.0.0"
#include "Arduino.h"
#include "Adafruit_MCP23017.h"

class PushButton
{
public:
	void begin(uint8_t pin, uint8_t pullup, uint8_t initial_state = 0, uint8_t pressed = 0, unsigned int waiting_time = 150);
	void begin(Adafruit_MCP23017 io, uint8_t pin, uint8_t pullup, uint8_t initial_state = 0,
			   uint8_t pressed = 0, unsigned int waiting_time = 150);
	void registerAction(void (*action)(uint8_t));
	uint8_t read();
	void setState(uint8_t state = 0) {
		this->state = state;
	}

	uint8_t getState() const {
		return state;
	}

private:
	void (*action)(uint8_t) = NULL;
	unsigned long tempoAtual = 0;
	unsigned long last_time = 0;
	bool io_expander = false;
	uint8_t pin = 0;
	Adafruit_MCP23017 io;
	uint8_t readPin(uint8_t pin);
	uint8_t pressed = 0;
	uint8_t state = 0;
	unsigned int waiting_time = 150;
	bool lock = false;
	bool registered_action = false;
};

#endif /* PUSHBUTTON_H_ */
