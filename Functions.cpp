#include <Windows.h>

#include "./Functions.h"
#include <iostream>
#include <fstream> // File stream
#include <filesystem>
#include "nlohmann/json.hpp"
#include <string>
#include <stdio.h>

using namespace std;
using namespace::nlohmann;
std::byte;



string name;
string className;
string date;
string description;

string newAssignment() {
	name = "";
	description = "";
	date = "";
	className = "";
	json datanew;

	cout << "New Assignment" << endl;
	cout << "Please enter the requested values:" << endl;
	cout << "Name of the assignment:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Class name:" << endl;

	getline(cin, className);
	cout << "Date due:" << endl;
	getline(cin, date);
	cout << "Description:" << endl;
	getline(cin, description);

	if (name.length() > 51) {
		return "CharLimit";
	}

	datanew["name"] = name;
	datanew["className"] = className;
	datanew["date"] = date;
	datanew["description"] = description;

	ofstream newFile("./assignments/" + name + ".json");
	newFile << datanew;
	newFile.close();

	return name;
	
}

string deleteAssignment() {
	string nameD;
	string* nameDP;
	char choice;

	cout << "Please enter the name of the file that you want to delete" << endl;

	cin.ignore(); // Ignore any previous lines
	getline(cin, nameD); // Get name input
	
	nameD = +"./assignments/" + nameD + ".json"; // Add .json to name

	// Find file and open, then display content.
	ifstream myFile;
	myFile.open(nameD);
	if (myFile.is_open()) {
		json datadelete = json::parse(myFile);
		cout << endl << "Is this the correct assignment? (Y | N):" << endl;
		cout << "Name: " << datadelete.at("name") << endl;
		cout << "Class: " << datadelete.at("className") << endl;
		cout << "Date Due: " << datadelete.at("date") << endl;
		cout << "Description: " << datadelete.at("description") << endl;
		cin >> choice;
		myFile.close();
		if (choice == 'y') {
			nameDP = &nameD; // NameDP Pointer is assigned to value of NameD and passed through remove() method
			if (remove(nameDP->c_str())) {
				perror("Error deleting file");
				return("Err");
			}
			else {
				return(nameD);
			}
		}
		else {
			return "Err2";
		}
	}
	else {
		return "Err1";
	}
}

string modifyAssignment() {
	string nameM;
	string* nameMP;
	string oldNameS;
	string name;
	string date;
	string description;
	string className;

	json modifyData;

	cout << "Enter the name of the assignment you want to modify" << endl;
	cin.ignore();
	getline(cin, nameM);

	oldNameS = nameM;
	nameM = "./assignments/" + nameM + ".json";
	nameMP = &nameM;

	ifstream myFile;
	myFile.open(nameM);
	if (myFile.is_open()) {
		modifyData = json::parse(myFile);



		name = modifyData.at("name");
		date = modifyData.at("date");
		description = modifyData.at("description");
		className = modifyData.at("className");

		// After initialization, close the file so we can re-open it with truncate.
		myFile.close();
	}
	else {
		return "Err1";
	}

	ofstream newFile;
	newFile.open(nameM, ios::trunc);
	if (newFile.is_open()) {

		// Get parameter
		string parameter;

		cout << "Please enter which parameter you would like to modify (case sensitive)" << endl;
		cout << "name\nclass\ndate\ndescription" << endl;
		cout << "Enter \"STOP\" to return" << endl;
		
		getline(cin, parameter);

		if (parameter == "name") {
			cout << "Please enter the name of the assignment" << endl;
			getline(cin, name);
		}
		else if (parameter == "class") {
			cout << "Please enter the class of the assignment" << endl;
			getline(cin, className);
		}
		else if (parameter == "date") {
			cout << "Please enter the date of the assignment" << endl;
			getline(cin, date);
		}
		else if (parameter == "description") {
			cout << "Please enter the description of the assignment" << endl;
			getline(cin, description);
		}
		else if (parameter == "STOP") {
			return "Cancel";
		}

		modifyData["name"] = name;
		modifyData["description"] = description;
		modifyData["date"] = date;
		modifyData["className"] = className;

		name = "./assignments/" + name + ".json";

		char* oldName;
		oldName = &nameM[0];
		char* newName;
		newName = &name[0];

		// 0X85391530 -> &name[0] *note [0] is spot 0 in an array that does not exist, so it is just the entire string that occupies [0]

		newFile << modifyData;
		newFile.close();
		int result = rename(oldName, newName);
		if (result != 0) {
			return "Err2";
		}
		return "Done";

	}
	else {
		return "Err1";
	}

}

string listAssignments() {
	string filePath;
	char const* fileName;
	char const* ptrToJson;
	string ptrToJsonString;
	char sectionDivider = '-'; // 1 byte
	


	// Filesystem path
	std::filesystem::path assignments{ "assignments" };


	// I = directory_iterator, which will iterate through all the files. Stop the loop after it is not equal to the directory_iterator (meaning it does not exist)
	// which indicates that there are no more files to be iterated through. i++ to advance to the next file in the directory_iterator.

	for (int i = 0; i != 48; i++) {
		cout << sectionDivider;
		if (i == 23) {
			cout << "ASSIGNMENTS";
		}
	}
	cout << endl; 

	for (auto i = std::filesystem::directory_iterator(assignments); i != std::filesystem::directory_iterator(); i++) {
		if (!is_directory(i->path())) {
			filePath = i->path().filename().string(); // i->path() references a specific member inside of the path which is "./assignments". In this case, i references a file inside the path

			fileName = filePath.c_str(); // Convert filePath string to fileName const char ptr
			ptrToJson = strchr(fileName, '.'); // intialize ptrToJson that will point to the location of the '.' and everything after

			filePath.erase(ptrToJson - fileName);
			cout << filePath << endl;

		}
	}

	for (int i = 0; i != 48; i++) {
		cout << sectionDivider;
		if (i == 23) {
			cout << "ASSIGNMENTS";
		}
	}
	cout << endl;

	return "true"; // Return anything other than the keywords to indicate that the operation was successful ( i am lazy )

}
