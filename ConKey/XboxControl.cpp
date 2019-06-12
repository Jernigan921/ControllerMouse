// Author: Tim Jernigan
// Created On: 12.26.2018 
// Updated Last: 1.12.2019 
// Description : This is my function file.

#include "stdafx.h"
#include "XboxControl.h"
#include <shellapi.h>

XboxControl::XboxControl(int playerNumber) {
	// sets the controller number //
	controllerNum = playerNumber - 1;
}

XINPUT_STATE XboxControl::GetState() {
	// zeroise state //
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// get state //
	XInputGetState(controllerNum, &controllerState);

	return controllerState;
}

bool XboxControl::IsConnected() {
	// zeroise state //
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// get state //
	DWORD Result = XInputGetState(controllerNum, &controllerState);

	if (Result == ERROR_SUCCESS) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void XboxControl::mouseRightClick() {
	INPUT action;

	action.type = INPUT_MOUSE;
	action.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &action, sizeof(INPUT));

	Sleep(10);

	ZeroMemory(&action, sizeof(INPUT));
	action.type = INPUT_MOUSE;
	action.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::SendInput(1, &action, sizeof(INPUT));
}

void XboxControl::mouseLeftClick() {
	/*
	INPUT in;
	in.type = INPUT_MOUSE;
	in.mi.dx = 0;
	in.mi.dy = 0;
	in.mi.dwFlags = MOUSEEVENTF_WHEEL;
	in.mi.time = 0;
	in.mi.dwExtraInfo = 0;
	in.mi.mouseData = WHEEL_DELTA;
	SendInput(1, &in, sizeof(in));
	*/
	INPUT action;

	action.type = INPUT_MOUSE;
	action.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &action, sizeof(INPUT));
}

void XboxControl::mouseLeftClickReleased() {
	INPUT action;

	ZeroMemory(&action, sizeof(INPUT));
	action.type = INPUT_MOUSE;
	action.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &action, sizeof(INPUT));
}


void XboxControl::mouseMode(POINT mouse) {
	// Deals with dead zones //
	float LX = GetState().Gamepad.sThumbLX;
	float LY = GetState().Gamepad.sThumbLY;

	// direction the controller is pushed //
	float magnitude = sqrt(LX * LX + LY * LY);
	int normalizedLX = LX / magnitude;
	int normalizedLY = LY / magnitude;
	float normalizedMagnitude = 0;

	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) 
	{
		if (magnitude > 32767) 
		{
			magnitude = 32767;
		}
		// adjust //
		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		normalizedLX = LX / magnitude;
		normalizedLY = LY / magnitude;
	}
	else
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
		normalizedLX = 0.0;
		normalizedLY = 0.0;
		LX = 0.0;
		LY = 0.0;
	}

	// Same for the right joystick //
	// Deals with dead zones //
	float RX = GetState().Gamepad.sThumbRX;
	float RY = GetState().Gamepad.sThumbRY;

	// direction the controller is pushed //
	float rightMagnitude = sqrt(RX * RX + RY * RY);
	int normalizedRX = RX / rightMagnitude;
	int normalizedRY = RY / rightMagnitude;
	float normalizedRightMagnitude = 0;

	if (rightMagnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		if (rightMagnitude > 32767)
		{
			rightMagnitude = 32767;
		}
		// adjust //
		rightMagnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

		normalizedRightMagnitude = rightMagnitude / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		normalizedRX = RX / rightMagnitude;
		normalizedRY = RY / rightMagnitude;
	}
	else
	{
		rightMagnitude = 0.0;
		normalizedRightMagnitude = 0.0;
		normalizedRX = 0.0;
		normalizedRY = 0.0;
		RX = 0.0;
		RY = 0.0;
	}

	if (normalizedMagnitude == 1) 
	{
		// up //
		if (normalizedLY == 1 && normalizedLX == 0) 
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x, mouse.y - 1);
		}
		// up right //
		if (normalizedLY == 1 && normalizedLX == 1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x + 1, mouse.y - 1);
		}
		// up left //
		if (normalizedLY == 1 && normalizedLX == -1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x - 1, mouse.y - 1);
		}

		// down //
		if (normalizedLY == -1 && normalizedLX == 0)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x, mouse.y + 1);
		}
		// down right //
		if (normalizedLY == -1 && normalizedLX == 1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x + 1 , mouse.y + 1);
		}
		// down left //
		if (normalizedLY == -1 && normalizedLX == -1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x - 1, mouse.y + 1);
		}
		// right //
		if (normalizedLY == 0 && normalizedLX == 1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x + 1, mouse.y);
		}
		// left //
		if (normalizedLY == 0 && normalizedLX == -1)
		{
			GetCursorPos(&mouse);
			SetCursorPos(mouse.x - 1, mouse.y);
		}
		 
	}
	
	// moves the scroll wheel up //
	if (normalizedRY == 1 && normalizedRX == 0)
	{
		if (normalizedRightMagnitude != 1) 
		{
			Sleep(150);
		}
		INPUT in;
		in.type = INPUT_MOUSE;
		in.mi.dx = 0;
		in.mi.dy = 0;
		in.mi.dwFlags = MOUSEEVENTF_WHEEL;
		in.mi.time = 0;
		in.mi.dwExtraInfo = 0;
		in.mi.mouseData = WHEEL_DELTA;
		SendInput(1, &in, sizeof(in));
	}

	// moves the scroll wheel down //
	if (normalizedRY == -1 && normalizedRX == 0)
	{
		if (normalizedRightMagnitude != 1) 
		{
			Sleep(150);
		}
		INPUT in;
		in.type = INPUT_MOUSE;
		in.mi.dx = 0;
		in.mi.dy = 0;
		in.mi.dwFlags = MOUSEEVENTF_WHEEL;
		in.mi.time = 0;
		in.mi.dwExtraInfo = 0;
		in.mi.mouseData = -WHEEL_DELTA;
		SendInput(1, &in, sizeof(in));
	}

	// mouse left click //
	if (GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		mouseLeftClick();
		Sleep(100);
		mouseLeftClickReleased();
	}

	// mouse right click //
	if (GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		Sleep(100);
		mouseRightClick();
	}

	Sleep(1);
}
 
// Currently this is the keyboard test. It is still being worked on by the joystick axis is off.
// Comming in a later update. - Tim Jernigan
/*
void XboxControl::keyboardMode()
{
ShellExecuteA(NULL, "open", "C:\Windows\system32\osk.exe", NULL, NULL, SW_SHOWNORMAL);
}
*/


