#include <admin.h>

Admin::~Admin(){}

bool Admin::Login() {
	
	string password;
	password = EnterPassword("Enter Admin Password\n");
	if (password == "admin")
		return 1;
	else
		return 0;
}

//1 To create new account
int Admin::addNewAccount(const string dbPath) {

	User newAccount;
	int check;
	string tempStr,tempStr1;
	tempStr = dbPath;
	tempStr += "\\AccountDetails.objects";

	cout << "Enter account holder name	:  ";

	getline(cin, tempStr1);	
	newAccount.accountHolderName = tempStr1;

	while (1) {
		cout << "Enter account type(s,c)    :  ";
		check = cin.get();
		getline(cin, tempStr1);

		if (check == 's' || check == 'c') {
			newAccount.accountType = check;
			break;
		}
		else {
			cout << "Enter a proper account type\n";
		}
	}
	
	cout << "Enter initial deposit amount :  ";
	cin >> newAccount.accountBalance;

	while (std::cin.fail()) {
		std::cout << "Enter an integer for initial deposit	:" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> newAccount.accountBalance;
	}
	getline(cin, tempStr1);

	newAccount.accountNumber = NewAccountNumber(dbPath);

	check = addObjectToFile(newAccount, tempStr, 'a');

	if (check == 1) {
		return 1;
	}

	return 0;
	
}

//2 To get all account holder details
int Admin::allAccountHolders(const string dbPath) {

	string tempStr;
	int check;
	tempStr = dbPath;
	tempStr += "\\AccountDetails.objects";
	check = getAllObjectsFromFile<User>(tempStr);
	return check;
}

//3 To search an Account Number detail
int Admin::GetAccountDetail(unsigned long accountNumber, const string dbPath) {

	string tempStr, tempStr1;
	tempStr = dbPath;
	tempStr += "\\AccountDetails.objects";

	// Object to read from file
	ifstream file_obj;
	User* objectPtr = NULL;
	objectPtr = new User;


	// Opening file in input mode
	file_obj.open(tempStr, ios::in);
	file_obj.seekg(0);

	if (file_obj.is_open()) {


		// Checking till we have the feed
		while (!file_obj.eof()) {


			// Checking further
			getline(file_obj, tempStr1);

			if (tempStr1.size() == sizeof(User)) {

				memcpy((char*)objectPtr, tempStr1.c_str(), sizeof(User));

				if (objectPtr->accountNumber == accountNumber) {

					cout << "\n Details found \n";
					objectPtr->printDetails();
					return 1;
				}				
			}
		}

		file_obj.close();
		return 2;
	}

	//else 
	else {
		cout << "Path or file does not exist!!\n";
		cout << "Check the path provided\n";
		return 0;
	}

}

//5 To delete an account
void Admin::deleteAccount(unsigned long accountNumber, const string dbPath) {

	User* objectPtr = NULL;
	objectPtr = new User;

	ifstream inFile;
	ofstream outFile;
	string tempStr, tempStr1, tempStr2;
	tempStr = dbPath;
	tempStr += "\\AccountDetails.objects";
	inFile.open(tempStr);
	
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}

	tempStr1 = dbPath;
	tempStr1 += "\\temp.objects";
	outFile.open(tempStr1);

	inFile.seekg(0, ios::beg);

	while (!inFile.eof()) {


		// Checking further
		getline(inFile, tempStr2);

		if (tempStr2.size() == sizeof(User)) {

			memcpy((char*)objectPtr, tempStr2.c_str(), sizeof(User));

			if (objectPtr -> accountNumber != accountNumber)
			{
				outFile.write((char*)objectPtr, sizeof(User));
				outFile << "\n";
			}
		}
	}

	inFile.close();
	outFile.close();
	remove(tempStr.c_str());
	rename(tempStr1.c_str(), tempStr.c_str());
	//cout << "\n\n\tRecord Deleted ..";
}

void Admin::AdminSubRoutine(const string dbPath) {
	char check;
	string tempStr;
	while (1) {

		cin.clear();
		cout << "To create new account press N\n";					//done 1
		cout << "To get all account holder details press A\n";		//done 2
		cout << "To search an Account Number detail press S\n";		//3 done
		cout << "To make a transaction press T\n";					//4 done
		cout << "To delete an account press D\n";					//5 done
		cout << "To view transaction details of an account press P\n";		//6 
		cout << "To view interest summed for an account press I\n";			//7 
		cout << "To logout press E\n";
		check = _getch();
		system("CLS");

		//1 To create new account
		if (check == 'N' || check == 'n') {

			//cin.ignore(256, '\n');

			if (this->addNewAccount(dbPath)) {

				cout << "\n\n*****ENTRY SUCESSFULL*****\n";
				Sleep(700);
				system("CLS");
			}

			else {
				cout << "Error Occured\n";
				Sleep(700);
				system("CLS");
			}
		}

		//2 To get all account holder details
		else if (check == 'A' || check == 'a') {

			//cin >> ws;

			cout << "Press E for previous menu\n";
			this->allAccountHolders(dbPath);
			cout << "\nPress E for previous menu\n";
			while (1) {
				check = _getch();
				if (check == 'e' || check == 'E') {
					break;
				}

				else {
					cout << "\nPress E for previous menu\n";
				}
			}
			system("CLS");
		}

		//3 To search an Account Number detail
		else if (check == 'S' || check == 's') {

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

			check = this->GetAccountDetail(accountNumber, dbPath);

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

		//4 To make a transaction
		else if (check == 'T' || check == 't') {

			unsigned long accountNumber;

			cout << "Enter account number to initiate transaction\n";
			cin >> accountNumber;

			while (std::cin.fail()) {
				std::cout << "Enter a correct account number\n" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> accountNumber;
			}
			cin.ignore(256, '\n');
			system("CLS");

			while (1) {
				
				cout << "Choose to make transaction for " << accountNumber << "\n";
				cout << "\n--> For money deposite press D\n";
				cout << "\n--> For money withdraw press W\n";
				cout << "\nTo exit press E\n";

				check = _getch();
				system("CLS");

				if (check == 'D' || check == 'd') {

					makeTransaction(accountNumber, 'c', dbPath);
					Sleep(700);
					system("CLS");
				}

				else if (check == 'W' || check == 'w') {

					makeTransaction(accountNumber, 'd', dbPath);
					Sleep(700);
					system("CLS");
				}

				else if (check == 'E' || check == 'e') {
					system("CLS");
					break;
				}

				else {
					cout << "Press a proper key\n";
					Sleep(500);
					system("CLS");
				}
				
			}
		}

		//5 To delete an account
		else if (check == 'D' || check == 'd') {

			//cin.ignore(256, '\n');

			unsigned long accountNumber;
			cout << "Enter account number to delete\n";
			cin >> accountNumber;

			while (std::cin.fail()) {
				std::cout << "Enter a correct account number\n" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> accountNumber;
			}
			//getline(cin, tempStr1);
			this->deleteAccount(accountNumber, dbPath);
			cout << "\n\n*****DELETE SUCESSFULL*****\n";
			cin.ignore(256, '\n');
			Sleep(700);
			system("CLS");

		}


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

