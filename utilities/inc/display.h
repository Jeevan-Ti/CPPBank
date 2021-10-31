#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Windows.h>
#include <iostream>

class Display
{
public:
	Display(const char* color);
	virtual ~Display();
	void SetFontSize(int y, const char* bc);
	void WindowSize(int height, int width);
	void DisplayBar(float value);
	void WindowMax();
	void StartScreen(Display d1);
};

void displayBar(float value);
void SetColor(int x);
std::string EnterPassword(const std::string& prompt = "Enter password> ");

#endif // !_DISPLAY_H_
