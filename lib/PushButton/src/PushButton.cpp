/*
 * PushButton.cpp
 *
 *  Created on: 30 de abr de 2019
 *      Author: Georgines
 */

#include "PushButton.h"

void PushButton::begin(uint8_t pin, uint8_t pullup, uint8_t initial_state, uint8_t pressed, unsigned int waiting_time)
{
	this->pin = pin;
	this->io_expander = false;
	this->pressed = pressed;
	this->waiting_time = waiting_time;
	this->state = initial_state;
	uint8_t input_pullup = 0;
	pullup ? input_pullup = INPUT_PULLUP : input_pullup = INPUT;
	pinMode(pin, input_pullup);
}

void PushButton::begin(Adafruit_MCP23017 io, uint8_t pin, uint8_t pullup, uint8_t initial_state, uint8_t pressed, unsigned int waiting_time)
{
	this->pin = pin;
	this->io = io;
	this->io_expander = true;
	this->pressed = pressed;
	this->waiting_time = waiting_time;
	this->state = initial_state;
	io.pinMode(pin, INPUT);
	if (pullup)
	{
		io.pullUp(pin, HIGH);
	}
}

uint8_t PushButton::read()
{

	uint8_t pin_state = readPin(this->pin);
	if (pin_state == pressed)
	{
		if (!lock)
		{
			state = !state;
			if (this->registered_action)
			{
				this->action(state);
			}
			lock = true;
		}
		last_time = millis();
	}
	else
	{
		if (millis() - last_time >= waiting_time)
		{
			lock = false;
			last_time = millis();
		}
	}
	return state;
}

uint8_t PushButton::readPin(uint8_t pin)
{
	if (io_expander)
	{
		return io.digitalRead(pin);
	}
	else
	{
		return digitalRead(pin);
	}
}

void PushButton::registerAction(void (*action)(uint8_t))
{

	this->action = action;
	this->registered_action = true;
}
