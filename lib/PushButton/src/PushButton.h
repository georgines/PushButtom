/*
 * PushButton.h
 *
 *  Created on: 01 de oct de 2021
 *      Author: Georgines
 */
#pragma once
#define PUSHBUTTON_VERSION "2.0.0"
#include "Arduino.h"

typedef void (*pAction)(int);
typedef unsigned char (*pReadPin)(unsigned char);
typedef void (*pModePin)(unsigned char, unsigned char);

class PushButton
{
public:
	void begin(unsigned char pin, unsigned char pullup, unsigned char initial_state = LOW, unsigned char pressed = LOW, unsigned int release_time = 150);
	void begin();
	void registerAction(pAction action);
	void registerReadFunction(pReadPin readPin);
	void registerModeFunction(pModePin modePin);
	void setPin(unsigned char pin);
	void enablePullUp();
	void setPressedToHigh();
	void setPressedToLow();
	void setStateToHigh();
	void setStateToLow();
	unsigned char getCurrentState() const;
	void setReleaseTime(unsigned int release_time);
	void run();

private:
	pAction action = nullptr;
	pReadPin readPin = nullptr;
	pModePin modePin = nullptr;
	unsigned long last_time = 0;
	unsigned char pin = 0;
	unsigned char mode = INPUT;
	unsigned char pressed = LOW;
	unsigned char state = LOW;
	unsigned int release_time = 150;
	bool lock = false;
};
