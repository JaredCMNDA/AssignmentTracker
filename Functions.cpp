#include "./Functions.h"
#include <iostream>
#include <fstream> // File stream
#include "nlohmann/json.hpp"
#include <string>
#include <Windows.h>
#include <stdio.h>

using namespace std;
using namespace::nlohmann;


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
	string name;
	string date;
	string description;
	string className;

	json modifyData;

	cout << "Enter the name of the assignment you want to modify" << endl;
	cin.ignore();
	getline(cin, nameM);


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


		cout << "Initialized" << endl;
		cout << name << endl;
		cout << date << endl;
		cout << className << endl;
		cout << description << endl;

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

		newFile << modifyData;
		newFile.close();
		return "Done";

	}
	else {
		return "Err1";
	}

}
