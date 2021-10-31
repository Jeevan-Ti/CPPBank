#include <user.h>
#include <admin.h>

using namespace std;

User::~User(){}



int makeTransaction(unsigned long accountNumber, char transactionType, string dbPath) {

	long amt;
	int found = 0;
	User* ac = NULL;
	ac = new User;
	fstream File;
	ofstream outFile;
	string tranFilePath, accountsDbFilePath, tempStr1, tempFilePath;
	accountsDbFilePath = dbPath + "\\AccountDetails.objects";
	tranFilePath = dbPath + "\\" + to_string(accountNumber) + ".tran";
	tempFilePath = dbPath + "\\TempFile.objects";

	File.open(accountsDbFilePath, ios::in | ios::out);

	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return 0;
	}


	outFile.open(tempFilePath);
	File.seekg(0, ios::beg);

	// Checking till we have the feed
	while (!File.eof()) {


		// Checking further
		getline(File, tempStr1);

		if (tempStr1.size() == sizeof(User)) {

			memcpy((char*)ac, tempStr1.c_str(), sizeof(User));

			if (ac->accountNumber == accountNumber)
			{
				ac->printDetails();

				//To deposit to account
				if (transactionType == 'c')
				{
					cout << "\n\n\tTO DEPOSITE AMOUNT ";
					cout << "\n\nEnter The amount to be deposited\n";

					cin >> amt;
					while (std::cin.fail()) {
						std::cout << "Enter a correct amount\n" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> amt;
					}
					cin.ignore(256, '\n');

					ac->accountBalance += amt;
					outFile.write((char*)ac, sizeof(User));
					outFile << "\n";
					cout << "\n\n\t Record Updated";

				}

				//To withdraw from account
				else if (transactionType == 'd')
				{
					cout << "\n\n\tTO WITHDRAW AMOUNT ";
					cout << "\n\nEnter The amount to be withdraw\n";

					cin >> amt;
					while (std::cin.fail()) {
						std::cout << "Enter a correct amount\n" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> amt;
					}
					cin.ignore(256, '\n');

					unsigned long bal = ac->accountBalance - amt;
					if ((bal < 500 && (ac->accountType == 'S' || ac->accountType == 's')) || (bal < 1000 && (ac->accountType == 'C' || ac->accountType == 'c')))
					{
						cout << "\nInsufficience balance\n";
						outFile.write((char*)ac, sizeof(User));
						outFile << "\n";
					}
					//draw amount
					else
					{
						ac->accountBalance -= amt;
						outFile.write((char*)ac, sizeof(User));
						outFile << "\n";
						cout << "\n\n\t Record Updated";
					}

				}

				found = 1;
			}

			else {
				outFile.write((char*)ac, sizeof(User));
				outFile << "\n";
			}

		}


	}


	File.close();
	outFile.close();

	remove(accountsDbFilePath.c_str());
	rename(tempFilePath.c_str(), accountsDbFilePath.c_str());

	if (found == 0) {
		cout << "\n\n Record Not Found ";
		return 2;
	}
		
	return 1;
}

void User::printDetails() {
	cout << endl << " NAME		:	" << this->accountHolderName << endl;
	cout << " AccNo		:	" << this->accountNumber << endl;
	cout << " Acctype	:	" << this->accountType << endl;
	cout << " Bal		:	" << this->accountBalance << endl;
}

void User::UserSubRoutine(const string dbPath) {
	char check;
	string tempStr;


	while (1) {

		cin.clear();
		cout << "To check account details press C\n";					//done 1
		cout << "For account statement press S\n";		//done 2
		cout << "For main menu press E\n";

		check = _getch();
		system("CLS");

		//1 To check account details
		if (check == 'C' || check == 'c') {

			Admin* admin = NULL;
			admin = new Admin;

			unsigned long accountNumber;
			cout << "Enter account number to search\n";
			cin >> accountNumber;

			while (std::cin.fail()) {
				std::cout << "Enter a correct account number\n" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> accountNumber;
			}
			cin.ignore(256, '\n');

			check = admin->GetAccountDetail(accountNumber, dbPath);

			if (check == 2) {
				cout << "Account does not exist\n";
				Sleep(700);
				system("CLS");
			}

			else {
				while (1) {
					cout << "\nPress E for previous menu\n";
					check = _getch();

					if (check == 'e' || check == 'E') {
						system("CLS");
						break;
					}
				}

			}
		}

		//2 For account statement

		//To exit to main menu
		else if (check == 'E' || check == 'e') {
			break;
		}

		//else
		else {
			cout << "!!!!Press a correct letter!!!!\n";
			Sleep(500);
			system("CLS");
		}

	}
}
