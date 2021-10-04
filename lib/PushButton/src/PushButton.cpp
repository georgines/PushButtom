/*
 * PushButton.cpp
 *
 *  Created on: 30 de abr de 2019
 *      Author: Georgines
 */

#include "PushButton.h"

void Georgines::PushButton::begin(unsigned char pin, unsigned char pullup, unsigned char initial_state, unsigned char pressed, unsigned int release_time)
{
	this->pin = pin;
	this->pressed = pressed;
	this->release_time = release_time;
	this->state = initial_state;
	this->begin();
}

void Georgines::PushButton::begin()
{
	if (this->modePin)
	{
		this->modePin(this->pin, this->mode);
	}
}

void Georgines::PushButton::registerAction(pAction action = nullptr)
{
	this->action = action;
}

void Georgines::PushButton::registerReadFunction(pReadPin readPin = nullptr)
{
	this->readPin = readPin;
}

void Georgines::PushButton::registerModeFunction(pModePin modePin = nullptr)
{
	this->modePin = modePin;
}

void Georgines::PushButton::setPin(unsigned char pin)
{
	this->pin = pin;
}

void Georgines::PushButton::enablePullUp()
{
	this->mode = INPUT_PULLUP;
}

void Georgines::PushButton::setPressedToHigh()
{
	this->state = HIGH;
}

void Georgines::PushButton::setPressedToLow()
{
	this->state = LOW;
}

void Georgines::PushButton::setStateToHigh()
{
	this->state = HIGH;
}

void Georgines::PushButton::setStateToLow()
{
	this->state = LOW;
}

unsigned char Georgines::PushButton::getCurrentState()
{
	return state;
}

void Georgines::PushButton::setReleaseTime(unsigned int release_time)
{
	this->release_time = release_time;
}

void Georgines::PushButton::run()
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