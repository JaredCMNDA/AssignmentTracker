#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "./Functions.h"

using namespace std;
string returnValue;

void mainScreen() {
	system("CLS");

	int choice = 0;

	cout << "ASSIGNMENT TRACKER" << endl;
	cout << "Jared McIntyre (Commanda)" << endl;
	cout << "Project Created April 26, 2022" << endl;
	cout << endl << "Choose one of the following:" << endl;
	cout << "1. Create a new assignment" << endl << "2. Delete an existing assignment" << endl << "3. Modify an existing assignment" << endl;
	cout << "4. List assignments" << endl;


	cin >> choice;

	if (choice == 1) {
		returnValue = newAssignment();
		if (returnValue == "CharLimit") {
			cout << "Your assignment could not be created: Char limit is 50." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else if (returnValue == "fileType") {
			cout << "Your assignment could not be created: Illegal file name." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else {
			cout << "Your assignment has been added: " << returnValue << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
	}
	else if (choice == 2) {
		returnValue = deleteAssignment();
		if (returnValue == "Err1") {
			cout << "Your assignment could not be deleted: Assignment does not exist." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else if (returnValue == "Err2") {
			cout << "Your assignment could not be deleted: Assignment could not be opened." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else {
			cout << "Your assignment has been deleted: " << returnValue << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
	}
	else if (choice == 3) {
		returnValue = modifyAssignment();
		if (returnValue == "Err1") {
			cout << "Your assignment could not be modified: Assignment does not exist." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else if (returnValue == "Err2") {
			cout << "Your assignment could not be modified: Unexpected error, or file corrupted." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else if (returnValue == "Cancel") {
			cout << "You have cancelled the modification: Returning" << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else {
			cout << "Your assignment has been modified" << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}

		mainScreen();
	}
	else if (choice == 4) {
		returnValue = listAssignments();
		if (returnValue == "Err1") {
			cout << "Assignments could not be listed: Assignments not found, filepath err." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else if (returnValue == "Err2") {
			cout << "Assignments could not be listed: Assignment was corrupted." << endl;
			this_thread::sleep_for(std::chrono::seconds(2));
			mainScreen();
		}
		else {
			cout << "Assignments listed. Refreshing in 10 seconds..." << endl;
			this_thread::sleep_for(std::chrono::seconds(10));
			mainScreen();
		}
	}
	else if (choice >= 5 || choice <= 1) {
		cout << endl << "Err -> This number does not define a choice" << endl;
		cout << "Returning in three seconds" << endl;
		this_thread::sleep_for(std::chrono::seconds(3));
		mainScreen();

	}

}

int main() {
	

	mainScreen();

}

