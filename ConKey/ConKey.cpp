// Author: Tim Jernigan
// Created On: 12.26.2018 
// Updated Last: 1.12.2019 
// Description : This is my main driver.
// Version: 1.04 I have basic mouse functionality.

#include "stdafx.h"
#include "XboxControl.h"
#include <string>


XboxControl* mainUser;
POINT mouse;

int main(){
	std::string name;
	mainUser = new XboxControl(1);
	bool mouseModeToggle = false;
	bool keyboardModeToggle = true;
	int counter = 1;
	int onOffCounter = 1;
	std::cout << "Instructions: " << std::endl;
	std::cout << "  By Default the Mouse is Off and the Keyboard is On." << std::endl;
	std::cout << "  Press Down on the Dpad to toggle between the mouse and keyboard." << std::endl;
	std::cout << "  Press Right on the Dpad to toggle between the controller On or Off." << std::endl;
	std::cout << "  Writen By: Tim Jernigan. " << std::endl;
	std::cout << std::endl;
	std::cout << "Mouse Mode: " << std::endl;
	std::cout << "  The A button is the Left Click." << std::endl;
	std::cout << "  The B button is the Right Click." << std::endl;
	std::cout << "  The Right Joystick controlls the scroll wheel. " << std::endl;
	std::cout << "    move the Joystick Up to Scroll Up and the Joystick Down to Scroll Down." << std::endl;
	std::cout << std::endl;
	std::cout << "Keyboard Mode: " << std::endl;
	std::cout << "  Comming Soon " << std::endl;
	std::cout << std::endl;
	std::cout << "MOUSE MODE: OFF" << std::endl;
	std::cout << "KEYBOARD MODE: ACTIVATED" << std::endl;

	while (true) 
	{
		if (mainUser->IsConnected())
		{
			if (mainUser->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) // turns on and off
			{
				Sleep(250);
				onOffCounter++;
				if (onOffCounter % 2 == 0)
				{
					std::cout << "XBOX Controller MODE: OFF\n" << std::endl;
					mouseModeToggle = false;
					keyboardModeToggle = false;
				}
				else 
				{
					if (counter % 2 == 0)
					{
						std::cout << "\nMOUSE MODE: ACTIVATED" << std::endl;
						std::cout << "KEYBOARD MODE: OFF\n" << std::endl;
						mouseModeToggle = true;
						keyboardModeToggle = false;
					}
					else
					{
						std::cout << "\nMOUSE MODE: OFF" << std::endl;
						std::cout << "KEYBOARD MODE: ACTIVATED\n" << std::endl;
						mouseModeToggle = false;
						keyboardModeToggle = true;
					}
				}

			}
			if (mainUser->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) // changes the mouse and keyboard
			{
				Sleep(250);
				counter++;
				if (counter % 2 == 0)
				{
					std::cout << "\nMOUSE MODE: ACTIVATED" << std::endl;
					std::cout << "KEYBOARD MODE: OFF\n" << std::endl;
					mouseModeToggle = true;
					keyboardModeToggle = false;
				}
				else {
					std::cout << "\nMOUSE MODE: OFF" << std::endl;
					std::cout << "KEYBOARD MODE: ACTIVATED\n" << std::endl;
					mouseModeToggle = false;
					keyboardModeToggle = true;
				}
			}

			if (mouseModeToggle) 
			{
				mainUser->mouseMode(mouse);
			}
			
			/*
			// This will come in a later update //
			if (keyboardModeToggle)
			{
				mainUser->keyboardMode();
			}
			*/
			
		}

		else
		{
			std::cout << "\nERROR! Your XBOX Controller was not found!\n";
			std::system("Pause");
			
			break;
		}
	}
    return 0;
}

