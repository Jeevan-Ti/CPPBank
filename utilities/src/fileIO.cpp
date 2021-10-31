#include<fileIO.h>
using namespace std;



string SetDBPath() {

	ofstream ofile;
	string temp;
	ofile.open("dbpath.txt", ios::trunc);
	cout << "\nOh! It seems no path for db exists or path not properly set\n";
	cout << "FIX : Enter db path by replacing \\ with \\\\ \n";
	cout << "EXAMPLE -> \"D:\\\\Assignment\\\\CPPBank\\\\db\" without quotes\n";
	getline(cin, temp);
	cout << "\n\n****PATH SUCESSFULLY SET****";
	Sleep(500);
	system("CLS");
	
	ofile << temp << endl;


	return temp;
}

/*
|* CheckForDB() first checks if there is any dbpath.txt file in the processes current working directory
|* If no file exists it prompts user to enter path for /db directory and creates a new dbpath.txt file
  to store the entered path
|* If file already exists, it prompts user to check if the current /db path is correct
	-> The user can either change it
	-> Or continue if the path displayed is correct
*/

string CheckForDB() {
	ifstream file_obj;
	string temp;
	file_obj.open("dbpath.txt");
	if (file_obj.is_open()) //checking whether the file is open
	{
		std::getline(file_obj, temp);
		file_obj.close();
		cout << "Your db path is \"" << temp << "\"\nTo modify press m\nTo continue press any keyn\n";
		char check;
		check = _getch();

		if (check == 'm' || check == 'M') {
			temp = SetDBPath();
			return temp;
		}
		else {
			system("CLS");
			return temp;
		}
		
	}

	else
	{
		temp = SetDBPath();
		return temp;
	}
}


unsigned long NewAccountNumber(const string dbPath) {
	
	ifstream file_obj;
	ofstream ofile;
	string tempStr;
	unsigned long newAccNo;
	tempStr = dbPath;
	tempStr += "\\accNoCounter.txt";

	file_obj.open(tempStr);
	if (file_obj.is_open()) //checking whether the file is open
	{
		//get acc number in string format
		getline(file_obj, tempStr);
		//convert it to unsigned long
		newAccNo = stoul(tempStr);
		//close file for reading
		file_obj.close();

		tempStr = dbPath;
		tempStr += "\\accNoCounter.txt";
		//opening the same file in out mode
		ofile.open(tempStr, ios::trunc);
		//write next account number to file i.e. newAccNo + 1
		ofile << to_string(newAccNo + 1);
		ofile.close();
		return newAccNo;
	}

	else 
	{
		//opening the same file in out mode
		ofile.open(tempStr, ios::trunc);
		ofile << "50200301";
		ofile.close();
		return 50200300;
	}
}