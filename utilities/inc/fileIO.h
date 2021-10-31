#ifndef _FILEIO_H_
#define _FILEIO_H_

/*******ALL REQUIRED HEADERS GO HERE********/
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

#define fileSeekPosition


/***************************
 ***TEMPLATE DECLARATIONS***
 ***************************/
template <class ObjectType>
int addObjectToFile(ObjectType &object, const string filePath, char mode);

template <class ObjectType>
int getAllObjectsFromFile(const string filePath);

/***************************
 ***FUNCTION DECLARATIONS***
 ***************************/
string SetDBPath();
string CheckForDB();
unsigned long NewAccountNumber(const string dbPath);


/***************************
 ***TEMPLATE DEFINITIONS***
 ***************************/
template <class ObjectType>
int addObjectToFile(ObjectType& object, const string filePath, char mode) {

	// Object to write in file
	ofstream file_obj;

	//if append mode is mentioned
	if (mode == 'a' || mode == 'A') {

		// Opening file in append mode
		file_obj.open(filePath, ios::app);

		//if file has sucessusfully opened do a file operation
		//else return 0...indicating error
		if (file_obj.is_open()) {
			// Writing the object's data in file
			file_obj.write((char*)&object, sizeof(object));
			file_obj << "\n";
			file_obj.close();
			return 1;
		}
		else
			return 0;
	}

	if (mode == 't' || mode == 'T') {

		// Opening file in truncate mode
		file_obj.open(filePath, ios::trunc);

		//if file has sucessusfully opened do a file operation
		//else return 0...indicating error
		if (file_obj.is_open()) {
			// Writing the object's data in file
			file_obj.write((char*)&object, sizeof(object));
			file_obj << "\n";
			file_obj.close();
			return 1;
		}
		else
			return 0;
	}

	else {
		cout << "Enter a correct mode\n a or A for append\n s or S for seek\n";
		return -1;
	}
}

/*
 |*  getAllObjectsFromFile(const string filePath) takes filepath from where objects of
	 ObjectType need to be read and invokes printDetails() method of class ObjectType
 |* To use getAllObjectsFromFile(const string filePath) template the object must have a 
    prinDetails() member function that prints details of the class's data members.
*/
template <class ObjectType>
int getAllObjectsFromFile(const string filePath) {

	// Object to read from file
	ifstream file_obj;
	ObjectType *objectPtr = NULL;
	objectPtr = new ObjectType;
	string tempStr;

	// Opening file in input mode
	file_obj.open(filePath, ios::in);
	file_obj.seekg(0);

	if (file_obj.is_open()) {
		
		
		// Checking till we have the feed
		while (!file_obj.eof()) {
			

			// Checking further
			getline(file_obj, tempStr);

			if (tempStr.size() == sizeof(ObjectType)) {

				memcpy((char*)objectPtr, tempStr.c_str(), sizeof(ObjectType));
				objectPtr -> printDetails();
			}
		}

		file_obj.close();
		return 1;
	}

	//else 
	else {
		cout << "Path or file does not exist!!\n";
		cout << "Check the path provided\n";
		return 0;
	}
	
}


#endif // !_FILEIO_H_
