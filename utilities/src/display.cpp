#include "display.h"

using namespace std;

Display::Display(const char* color)
{
	system(color);
}

Display::~Display()
{
}

void Display::WindowMax()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void Display::WindowSize(int height, int width)
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}

void Display::SetFontSize(int y, const char* bc)
{
	const wchar_t* x = (wchar_t*)bc;
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = y;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, x); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void SetColor(int x)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);
}

void Display::StartScreen(Display d1)
{
	int i = 0;
	WindowMax();
	/*SetColor(79);
	d1.SetFontSize(100, "Arial");
	for (i = 0; i < 30; i++)
		cout << " ";
	cout << "\n";
	for (i = 0; i < 30; i++)
		cout << " ";
	cout << "\n";
	for (i = 0; i < 30; i++)
		cout << " ";
	cout << "\n Student Record Manager   \n";
	for (i = 0; i < 30; i++)
		cout << " ";
	cout << "\n";
	for (i = 0; i < 30; i++)
		cout << " ";
	cout << "\n";
	for (i = 0; i < 30; i++)
		cout << " ";*/
	system("COLOR 4F");
	d1.SetFontSize(100, "Arial");
	cout << "\n\n\n";
	cout << "        CPP Bank         ";
	Sleep(2000);
	system("CLS");
}

void Display::DisplayBar(float value)
{

}

void displayBar(float value)
{
	int i, temp;
	float t;
	t = value * 0.7;
	temp = t;
	SetColor(252);
	for (i = 0; i < temp; i++)
	{
		cout << "#";
	}
	for (i = 0; i < 72 - temp; i++)
		cout << " ";
	SetColor(79);
	cout << "\n\n";
}

string EnterPassword(const string& prompt)
{
	string result;

	// Set the console mode to no-echo, not-line-buffered input
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw runtime_error(
			"getpassword: You must be connected to a console to use this program.\n"
		);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	// Get the password string
	WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}

	// Restore the console mode
	SetConsoleMode(ih, mode);
	cout << endl;
	//cout << result << endl;
	return result;
}