// CPPBank.cpp : Defines the entry point for the application.
//

#include "CPPBank.h"

using namespace std;

int main()
{
	
	char check;
	bool c = FALSE;
	Display d1("COLOR FC");
	SetConsoleTitle(TEXT("CPP Bank"));
	d1.StartScreen(d1);
	d1.SetFontSize(35, "Arial");
	system("COLOR 4F");
	SetColor(236);
	cout << "Welcome to CPP Bank...\n";
	SetColor(79);
	
	//perform the database directory check in every start
	string dbPath = CheckForDB();
	system("CLS");
	
	User user;
	Admin admin;


	while (1) {
		SetColor(236);
		cout << "Welcome to CPP Bank...\n";
		SetColor(79);

		//main menu to enter into user or admin mode
		cout << "For Admin login press A\n";
		cout << "For user realted services press U\n";
		cout << "To exit press E\n";
		check = _getch();
		system("CLS");

		//This is the Admin SubRoutine
		if (check == 'A' || check == 'a') {
			
			if (admin.Login()) {

				system("CLS");
				admin.AdminSubRoutine(dbPath);
			}

			else {
				cout << "Entered password is wrong. Please try again!\n";
				Sleep(700);
				system("CLS");
			}
		}

		//User SubRoutine
		else if (check == 'U' || check == 'u') {

			system("CLS");
			user.UserSubRoutine(dbPath);
		}

		else if (check == 'E' || check == 'e') {
			break;
		}
	}

	return 0;

}
