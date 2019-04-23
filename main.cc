#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void print(string message);

string inputString();

int checkIfCorrect();

void clearZeros();

void appendDataOfEmployee(string first, string last, int id, int typeOfAppend);

void writeToFile(string first, string last, int id);

bool checkIfEmployeeExists(string first, string last, int id);

string greeting();

int main () {
    string Name;
    char response;
    Name = greeting();
    return 0;
}

void print(string message){
	cout << message << endl;
	return;
}

string inputString(){
	string value;
	cin >> value;
	return value;
}

int checkIfCorrect(){
	string response;
	int check, result;
	do {
	print ("Is this correct? [Y, n]");
	check = 1;
	response = inputString();
	if (response == "Y" || response == "y" || response == "Yes" || response == "yes" || response == "YES") {
		result = 1;
	}
	else if (response == "N" || response == "n" || response == "No" || response == "no" || response == "NO" ) {
		result = 0;
	}
	else {
		print("Invalid. Please try again.");
		check = 0;
	}

	}while (check == 0);
	return result;
}

void clearZeros(){
	print("Clearing Zeros...");
	ifstream readWorker;
	readWorker.open("employees.txt", fstream :: in);
	string Employees[100][2];
	int ids[100];
	int i = 0, j = 0;
	while(!readWorker.eof()){
		print("In the First Loop!");
		readWorker >> Employees[i][j];
		j++;
		readWorker >> Employees[i][j];
		j = 0;
		readWorker >> ids[i];
		i++;
	}
	int max = i - 1;
	readWorker.close();
	ofstream writeWorker;
	writeWorker.open("employees.txt", fstream :: out | fstream :: trunc);
	for(i = 0; i < max; i++){
		for(j = 0; j < 2; j++){
			if(Employees[i][j] != "0"){
				writeWorker << Employees[i][j] + " ";
			}
		}
		if(Employees[i][j-1] != "0" && Employees[i][j-2] != "0"){
			writeWorker << ids[i] << endl;
		}
	}
	print("Zeros are cleaned.....");
	writeWorker.close();
	return;
}

void appendDataOfEmployee(string first, string last, int id, int typeOfAppend){
	ifstream loadWorker;
	loadWorker.open("employees.txt", fstream::in | fstream::out | fstream::app);
	if(loadWorker.is_open()){
		print("------File Has Been Opened------");
	}
	else{
		print("File Failed To Open");
	}
	if(loadWorker.fail()){
		print("File Failed To Open");
	}
	else{
		print("No Failure Detected In Opening File!");
	}
	string Employees[100][2];
	int ids[100];
	int i = 0, j = 0;
	while(!loadWorker.eof()){
		loadWorker >> Employees[i][j];
		j++;
		loadWorker >> Employees[i][j];
		j = 0;
		loadWorker >> ids[i];
		i++;
	}
	loadWorker.close();
	int max = i;
	//typeOfAppend -3 is to remove employee
	//typeOfAppend -2 is to change ID
	//typeOfAppend -1 is to change LastName
	//typeOfAppend 0 is to REMOVE employee
	//forLaterUse change rate 1
	//change of hours 2
	if(typeOfAppend == -3){
		print("Listing what is currently in the file");
		for(i = 0; i < max - 1; i++){
			for(j = 0; j < 2; j++){
				cout << Employees[i][j] << " ";
			}
			cout << ids[i] << endl;
		}
		print("List Ended");
		for(i = 0; i < max; i++){
			if(Employees[i][0].compare(first) == 0 && Employees[i][1].compare(last) == 0 && ids[i] == id){
				for(int k = i; k < max; k++){
					print("loop count");
					cout << Employees[k][0] << " " << Employees[k+1][0] << endl;
					Employees[k][0] = Employees[k+1][0];
					cout << Employees[k][1] << " " << Employees[k+1][1] << endl;
					Employees[k][1] = Employees[k+1][1];
					cout << ids[k] << " " << ids[k+1]<< endl;
					ids[k] = ids[k+1];
				}
				break;
			}
		}

		ofstream writeNew;
		writeNew.open("employees.txt", ios::out | ios::trunc);
		//asumming opens fine.
		for(i = 0; i < max - 1; i++){
			for(j = 0; j < 2; j++){
				writeNew << Employees[i][j] << " ";
			}
			writeNew << ids[i] << endl;
		}
		clearZeros();
	}
	else if(typeOfAppend == -2){

	}
	else if(typeOfAppend == -1){

	}
	else if (typeOfAppend == 0){

	}
	return;
}


void writeToFile (string first, string last, int id){
	ofstream inputWorker;
	inputWorker.open("employees.txt", fstream::in | fstream::out | fstream::app);
	if(inputWorker.is_open()){
		print("------File Has Been Opened------");
	}
	else{
		print("File Failed To Open");
	}
	if(inputWorker.fail()){
		print("File Failed To Open");
	}
	else{
		print("No Failure Detected In Opening File!");
	}

	inputWorker << first + " " + last + " " << id << endl;

	inputWorker.close();
	print("------File Has Been Closed------");
	return;
}

bool checkIfEmployeeExists(string first, string last, int id){
	ifstream readWorker;
	readWorker.open("employees.txt", fstream::in | fstream::out | fstream::app);
	if(readWorker.is_open()){
		print("------File Has Been Opened------");
	}
	else{
		print("File Failed To Open");
	}
	if(readWorker.fail()){
		print("File Failed To Open");
	}
	else{
		print("No Failure Detected In Opening File!");
	}
	clearZeros();
	string Employees[100][2];
	int ids[100];
	int i = 0, j = 0;
	while(!readWorker.eof()){
		readWorker >> Employees[i][j];
		j++;
		readWorker >> Employees[i][j];
		j = 0;
		readWorker >> ids[i];
		i++;
	}
	int max = i;
	for(i = 0; i < max; i++){
		if(Employees[i][0].compare(first) == 0 && Employees[i][1].compare(last) == 0 && id == ids[i]){
			readWorker.close();
			print("------File Has Been Closed------");
			return true;
		}else if(Employees[i][0].compare(first) == 0 && Employees[i][1].compare(last) == 0 && id != ids[i]){
			print("Your name is in the system but your ID is not.");
			print("Changing your ID on file....");
			cout << "\tInputed ID: " << id << endl;
			if(checkIfCorrect()){
				readWorker.close();
				ofstream writeWorker;
				writeWorker.close();
			}
		}else if(Employees[i][0].compare(first) != 0 && Employees[i][1].compare(last) != 0 && id == ids[i]){
			print("This ID is already in use! If you think this is a mistake please contact the admin.");
			print("For now please try entering another ID by re-running the program.");
			exit(EXIT_FAILURE);
		}
	}
	print("------File Has Been Closed------");
	readWorker.close();
	return false;
}

string greeting(){
	string firstName, lastName;
	int id, response = 0;
	print("Welcome! To continue using the program please identify yourself.");
	while (response == 0){
	print("1) Please type in your first and last name:");
	firstName = inputString();
	lastName = inputString();
	print("2) Please type in your work ID:");
	cin >> id;
	cout << "\tYou entered: \n\t\t" << firstName << " " << lastName << endl << "\t\tID: " << id << endl;
	response = checkIfCorrect();
	}
	transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
	transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);
	//Create a limitation for ids to be at least up to 4 digits.
	//Once correct, write to file.
	if(!checkIfEmployeeExists(firstName, lastName, id)){
		print("You are not yet in the system! Saving you for future inquries...");
		writeToFile(firstName, lastName, id);
	}
	else{
		cout << "\n------Welcome back " << firstName + " " + lastName + "!------" << endl;
		print("Would you like to delete your data?");
		if(checkIfCorrect()){
			appendDataOfEmployee(firstName, lastName, id, -3);
		}else{
			print("Okay your data will not be deleted.");
		}
	}
	return firstName + " " + lastName;
}
