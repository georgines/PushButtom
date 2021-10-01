/*
 * PushButton.cpp
 *
 *  Created on: 30 de abr de 2019
 *      Author: Georgines
 */

#include "PushButton.h"

void PushButton::begin(unsigned char pin, unsigned char pullup, unsigned char initial_state, unsigned char pressed, unsigned int release_time)
{
	this->pin = pin;
	this->pressed = pressed;
	this->release_time = release_time;
	this->state = initial_state;
	this->begin();
}

void PushButton::begin()
{
	if (this->modePin)
	{
		this->modePin(this->pin, this->mode);
	}
}

void PushButton::registerAction(pAction action = nullptr)
{
	this->action = action;
}

void PushButton::registerReadFunction(pReadPin readPin = nullptr)
{
	this->readPin = readPin;
}

void PushButton::registerModeFunction(pModePin modePin = nullptr)
{
	this->modePin = modePin;
}

void PushButton::setPin(unsigned char pin)
{
	this->pin = pin;
}

void PushButton::enablePullUp()
{
	this->mode = INPUT_PULLUP;
}

void PushButton::setPressedToHigh()
{
	this->state = HIGH;
}

void PushButton::setPressedToLow()
{
	this->state = LOW;
}

void PushButton::setStateToHigh()
{
	this->state = HIGH;
}

void PushButton::setStateToLow()
{
	this->state = LOW;
}

unsigned char PushButton::getCurrentState() const
{
	return state;
}

void PushButton::setReleaseTime(unsigned int release_time)
{
	this->release_time = release_time;
}

void PushButton::run()
{

	if (this->readPin)
	{
		unsigned char pin_state = this->readPin(this->pin);

		if (pin_state == pressed)
		{
			if (!lock)
			{
				state = !state;
				if (this->action)
				{
					this->action(state);
				}
				lock = true;
			}
			last_time = millis();
		}
		else
		{
			if (millis() - last_time >= release_time)
			{
				lock = false;
				last_time = millis();
			}
		}
	}
	return;
}