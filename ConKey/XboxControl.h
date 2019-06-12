// Author: Tim Jernigan
// Created On: 12.26.2018 
// Updated Last: 1.12.2019 
// Description : This is my h file for linking.

#pragma once

#ifndef XBOXCONTROL_H
#define XBOXCONTROL_H

#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

class XboxControl {
private:
	XINPUT_STATE controllerState;
	int controllerNum;
public:
	XboxControl(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void mouseRightClick();
	void mouseLeftClick();
	void mouseLeftClickReleased();
	void mouseMode(POINT);
	
	// later update // void keyboardMode();
};
#endif 