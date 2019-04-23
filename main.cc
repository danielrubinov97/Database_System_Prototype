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

int checkIfEmployeeExists(string first, string last, int id);

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
		//Two use cases:
			//One is for a user to delete their own data (Maybe).
			//Two is for admin to clean up users.
	//	for(i = 0; i < max - 1; i++){
	//		for(j = 0; j < 2; j++){
	//			cout << Employees[i][j] << " ";
	//		}
	//		cout << ids[i] << endl;
	//	}
		for(i = 0; i < max; i++){
			if(Employees[i][0].compare(first) == 0 && Employees[i][1].compare(last) == 0 && ids[i] == id){
				for(int k = i; k < max; k++){
					Employees[k][0] = Employees[k+1][0];
					Employees[k][1] = Employees[k+1][1];
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
		//Intended for Admin use.

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

int checkIfEmployeeExists(string first, string last, int id){
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
			return 1;
		}else if(Employees[i][0].compare(first) == 0 && Employees[i][1].compare(last) == 0 && id != ids[i]){
			print("The name you inputed and the ID you inputed doesn't match if you think this is a mistake please constact the admin.");
			cout << "\tInputed Name: " << first + " " + last << endl;
			cout << "\tInputed ID: " << id << endl;
			print("Rerunning program....");
			cout << endl << endl;
			return 2;
		}
		else if(Employees[i][0].compare(first) != 0 && Employees[i][1].compare(last) != 0 && id == ids[i]){
			print("This ID is already in use! If you think this is a mistake please contact the admin.");
			print("For now please try entering another ID.");
			print("Rerunning program....");
			cout << endl << endl;
			return 2;
		}
	}
	print("------File Has Been Closed------");
	readWorker.close();
	return 0;
}

string greeting(){
	string firstName, lastName;
	int id, response;
Top:
	response = 0;
	print("Welcome! To continue using the program please identify yourself.");
	while (response == 0){
	print("1) Please type in your first and last name:");
	firstName = inputString();
	lastName = inputString();
	print("2) Please type in your work ID:");
	cin >> id;
	if(id > 9999 || id < 1){
		print("Error: ID is invalid. Please enter only a 4 digit number. (0001 to 9999)");
		cout << endl << endl;
		goto Top;
	}
	cout << "\tYou entered: \n\t\t" << firstName << " " << lastName << endl << "\t\tID: " << id << endl;
	response = checkIfCorrect();
	}
	transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
	transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);
	//Create a limitation for ids to be at least up to 4 digits.
	//Once correct, write to file.
	response = checkIfEmployeeExists(firstName, lastName, id);
	if(response == 0){
		print("You are not yet in the system! Saving you for future inquries...");
		writeToFile(firstName, lastName, id);
	}
	else if(response == 1){//The first and last names along with the id correspond.
		cout << "\n------Welcome back " << firstName + " " + lastName + "!------" << endl;
		//Once data has been confirmed user may augment their data.
		print("Would you like to delete your data?");
		if(checkIfCorrect()){
			appendDataOfEmployee(firstName, lastName, id, -3);
		}else{
			print("Okay your data will not be deleted.");
		}
	}else if(response == 2){
		goto Top;
	}
	return firstName + " " + lastName;
}
