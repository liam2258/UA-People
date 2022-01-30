#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//Can be replaced with any SQL server, "tcp://"Your sever here":"Your server port number here"
const string server = "tcp://localhost:3306";
const string username = "root";
const string password = "lyman089";

//Function that prints the students selected from the database
bool PrintStudents(sql::ResultSet* result) {
	bool empty = true;
	while (result->next()) {
		empty = false;
		cout << "ID: " << result->getString(1).c_str() << " "
			<< "First Name: " << result->getString(2).c_str() << " "
			<< "Last Name: " << result->getString(3).c_str() << " "
			<< "Major: " << result->getString(4).c_str() << " "
			<< "Minor: " << result->getString(5).c_str() << " "
			<< "Year: " << result->getString(6).c_str() << " "
			<< "GPA: " << result->getDouble(7) << " "
			<< "Campus: " << result->getString(8).c_str() << " "
			<< "Gender: " << result->getString(9).c_str() << endl;
	}
	return empty;
}


//Function that prints the professors selected from the database
bool PrintProfessors(sql::ResultSet* result) {
	bool empty = true;
	while (result->next()) {
		empty = false;
		cout << "ID: " << result->getString(1).c_str() << " "
			<< "First Name: " << result->getString(2).c_str() << " "
			<< "Last Name: " << result->getString(3).c_str() << " "
			<< "Department: " << result->getString(4).c_str() << " "
			<< "Campus: " << result->getString(5).c_str() << " "
			<< "Gender: " << result->getString(6).c_str() << endl;
	}
	return empty;
}

//Function to print the education departments
void PrintDepartments() {
	cout << "1: Math" << endl;
	cout << "2: History" << endl;
	cout << "3: Music" << endl;
	cout << "4: Biology" << endl;
	cout << "5: Chemistry" << endl;
	cout << "6: Japanese" << endl;
	cout << "7: German" << endl;
	cout << "8: Computer Science" << endl;
	cout << "9: Communications" << endl;
	cout << "10: Undeclared" << endl;
}

//Function to select a department
string SelectDepartment(int i) {
	string department;
	switch (i) {
	case 1:
		return("Math");
	case 2:
		return("History");
	case 3:
		return("Music");
	case 4:
		return("Biology");
	case 5:
		return("Chemistry");
	case 6:
		return("Japanese");
	case 7:
		return("German");
	case 8:
		return("Computer Science");
	case 9:
		return("Communications");
	case 10:
		return("Undeclared");
	}
}

//Function to select a campus
string SelectCampus(int p) {
	switch (p) {
	case 1:
		return("Anchorage");
	case 2:
		return("Bethel");
	case 3:
		return("Fairbanks");
	case 4:
		return("Juneau");
	case 5:
		return("Kenai");
	case 6:
		return("Ketchikan");
	case 7:
		return("Kodiak");
	case 8:
		return("Nome");
	case 9:
		return("Palmer");
	case 10:
		return("Sitka");
	case 11:
		return("Valdez");
	}
}

//Function to print gender options
void PrintGenders() {
	cout << "1: Male" << endl;
	cout << "2: Female" << endl;
	cout << "3: Other" << endl;
}

//Function to select a gender
string SelectGender(int p) {
	switch (p) {
	case 1:
		return("Male");
	case 2:
		return("Female");
	case 3:
		return("Other");
	}
}

int main()
{

	//Declares SQL classes
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	sql::ResultSet* result2;

	//Connects to the SQL Server, returns error if unable to connect
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		cout << "Connecting to server..." << endl;
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	cout << "Connected Successfully!" << endl;

	bool flag = true;

	//Prints welcome and intro menu
	while (flag == true) {

		cout << "Welcome to the UA People Management system!" << endl
			<< "Please select an option:" << endl;

		con->setSchema("uamanagement");

		cout << "1: View Students" << endl;
		cout << "2: View Profesors" << endl;
		cout << "3: View Campuses" << endl;
		cout << "4: Search Records" << endl;
		cout << "5: Add Student" << endl;
		cout << "6: Add Professor" << endl;
		cout << "7: Delete Record" << endl;
		cout << "8: Exit" << endl;

		int x;
		cin >> x;
		while (std::cin.fail() || (x < 1 || x > 8)) {
			std::cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error: Invalid input" << endl << "Please try again:" << endl;
			cin >> x;
		}

		switch (x) {
		//Shows all student records
		case 1:
			pstmt = con->prepareStatement("SELECT * FROM Student;");
			result = pstmt->executeQuery();
			PrintStudents(result);
			break;
		//Shows all professor records
		case 2:
			pstmt = con->prepareStatement("SELECT * FROM Professor;");
			result = pstmt->executeQuery();
			PrintProfessors(result);
			break;
		//Shows all campuses and their matchin universities
		case 3:
			pstmt = con->prepareStatement("SELECT * FROM Campuses;");
			result = pstmt->executeQuery();
			cout << "University | Campus  |" << endl;
			while (result->next()) {
				cout << result->getString(1).c_str() << "         " << result->getString(2).c_str() << endl;
			}
			break;
		//Allows the user to search records by name or id
		case 4: {
			cout << "1: Search by ID" << endl
				 << "2: Search by first name" << endl
				 << "3: Search by last name" << endl;

			bool flag2 = false;
			string g;
			int h;

			while (flag2 == false) {
				cin >> h;
				switch (h) {
					case 1:
						flag2 = true;
						cout << "Please enter an ID:" << endl;
						g = "ID";
						break;
					case 2:
						flag2 = true;
						cout << "Please enter a first name:" << endl;
						g = "First_Name";
						break;
					case 3:
						flag2 = true;
						cout << "Please enter a last name:" << endl;
						g = "Last_Name";
						break;
					default:
						cout << "Invalid entry, please try again:" << endl;
				}
			}
					bool empty = true;
					bool empty2 = true;
					string e;
					cin >> e;

					//Choose which method to search records by
					switch (h) {
					case 1:
						pstmt = con->prepareStatement("SELECT * FROM Student WHERE ID = ?;");
						pstmt->setString(1, e);
						result = pstmt->executeQuery();
						empty = PrintStudents(result);

						pstmt = con->prepareStatement("SELECT * FROM Professor WHERE ID = ?;");
						pstmt->setString(1, e);;
						result = pstmt->executeQuery();
						empty2 = PrintProfessors(result);
						break;
					case 2:
						pstmt = con->prepareStatement("SELECT * FROM Student WHERE First_Name = ?;");
						pstmt->setString(1, e);
						result = pstmt->executeQuery();
						empty = PrintStudents(result);

						pstmt = con->prepareStatement("SELECT * FROM Professor WHERE First_Name = ?;");
						pstmt->setString(1, e);;
						result = pstmt->executeQuery();
						empty2 = PrintProfessors(result);
						break;
					case 3:
						pstmt = con->prepareStatement("SELECT * FROM Student WHERE Last_Name = ?;");
						pstmt->setString(1, e);
						result = pstmt->executeQuery();
						empty = PrintStudents(result);

						pstmt = con->prepareStatement("SELECT * FROM Professor WHERE Last_Name = ?;");
						pstmt->setString(1, e);;
						result = pstmt->executeQuery();
						empty2 = PrintProfessors(result);
						break;
					}

					if (empty == true && empty2 == true) {
						cout << "No records found" << endl;
					}
					break;
				}
		
		//Allows the addition of a new student record
		case 5: {
			cout << "Please enter an ID: " << endl;
			string ID;
			cin >> ID;

			//Checks to see if the ID entered is already in use
			pstmt = con->prepareStatement("SELECT * FROM Student WHERE ID = ?;");
			pstmt->setString(1, ID);
			result = pstmt->executeQuery();
			pstmt = con->prepareStatement("SELECT * FROM Professor WHERE ID = ?;");
			pstmt->setString(1, ID);
			result2 = pstmt->executeQuery();

			while (result->next() || result2->next()) {
				cout << "Error: Invalid entry" << endl << "Please enter an integer that is not already in use:" << endl;
				cin >> ID;
				pstmt = con->prepareStatement("SELECT * FROM Student WHERE ID = ?;");
				pstmt->setString(1, ID);
				result = pstmt->executeQuery();
				pstmt = con->prepareStatement("SELECT * FROM Professor WHERE ID = ?;");
				pstmt->setString(1, ID);
				result2 = pstmt->executeQuery();
			}


			cout << "Please enter a first name: " << endl;
			string first;
			cin >> first;
			cout << "Please enter a last name: " << endl;
			string last;
			cin >> last;
			cout << "Please select a major: " << endl;
			int i;
			PrintDepartments();
			cin >> i;
			while (std::cin.fail() || (i < 0 || i > 10)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> i;
			}
			string major = SelectDepartment(i);
			cout << "Please select a minor: " << endl;
			int y;
			PrintDepartments();
			cin >> y;
			while (std::cin.fail() || (y < 1 || y > 10)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> y;
			}
			string minor = SelectDepartment(y);
			cout << "Please select a year: " << endl;
			cout << "1: Freshman" << endl;
			cout << "2: Sophmore" << endl;
			cout << "3: Junior" << endl;
			cout << "4: Senior" << endl;
			cout << "5: Graduate" << endl;
			int u;
			cin >> u;
			string grade;
			while (std::cin.fail() || (u < 1 || u > 5)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> u;
			}
			switch (u) {
			case 1:
				grade = "Freshman";
				break;
			case 2:
				grade = "Sophmore";
				break;
			case 3:
				grade = "Junior";
				break;
			case 4:
				grade = "Senior";
				break;
			case 5:
				grade = "Graduate";
				break;
			}

			cout << "Please enter a GPA: " << endl;
			double GPA;
			cin >> GPA;
			while (std::cin.fail() || (GPA < 0 || GPA > 4)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> GPA;
			}

			cout << "Please select a campus: " << endl;

			pstmt = con->prepareStatement("SELECT Campus FROM Campuses;");
			result = pstmt->executeQuery();
			int o = 1;
			while (result->next()) {
				cout << o << ": " << result->getString(1).c_str() << endl;
				o++;
			}
			o = 0;

			string campus;
			int p;
			cin >> p;
			while (std::cin.fail() || (p < 1 || p > 11)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> p;
			}
			campus = SelectCampus(p);
			cout << "Please select a gender: " << endl;
			PrintGenders();
			string gender;
			int r;
			cin >> r;
			while (std::cin.fail() || (r < 0 || r > 3)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> r;
			}

			gender = SelectGender(r);

			//Inserts user enter data as an entry into the "Student" table of the SQL database
			pstmt = con->prepareStatement("INSERT INTO `Student`(ID, First_Name, Last_Name, Major, Minor, Grade, GPA, Campus, Gender) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);");
			pstmt->setString(1, ID);
			pstmt->setString(2, first);
			pstmt->setString(3, last);
			pstmt->setString(4, major);
			pstmt->setString(5, minor);
			pstmt->setString(6, grade);
			pstmt->setDouble(7, GPA);
			pstmt->setString(8, campus);
			pstmt->setString(9, gender);
			pstmt->execute();
			cout << "One row inserted." << endl;
			break;
		}

		//Allows the addition of a new professor record
		case 6: {
			cout << "Please enter an ID: " << endl;
			string ID;
			cin >> ID;

			pstmt = con->prepareStatement("SELECT * FROM Student WHERE ID = ?;");
			pstmt->setString(1, ID);
			result = pstmt->executeQuery();
			pstmt = con->prepareStatement("SELECT * FROM Professor WHERE ID = ?;");
			pstmt->setString(1, ID);
			result2 = pstmt->executeQuery();

			while (result->next() || result2->next()) {
				cout << "Error: Invalid entry" << endl << "Please enter an integer that is not already in use:" << endl;
				cin >> ID;
				pstmt = con->prepareStatement("SELECT * FROM Student WHERE ID = ?;");
				pstmt->setString(1, ID);
				result = pstmt->executeQuery();
				pstmt = con->prepareStatement("SELECT * FROM Professor WHERE ID = ?;");
				pstmt->setString(1, ID);
				result2 = pstmt->executeQuery();
			}

			cout << "Please enter a first name: " << endl;
			string first;
			cin >> first;
			cout << "Please enter a last name: " << endl;
			string last;
			cin >> last;
			cout << "Please select a major: " << endl;
			int i;
			PrintDepartments();
			cin >> i;
			while (std::cin.fail() || (i < 0 || i > 10)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> i;
			}

			string department = SelectDepartment(i);

			cout << "Please select a campus: " << endl;

			pstmt = con->prepareStatement("SELECT Campus FROM Campuses;");
			result = pstmt->executeQuery();
			int o = 1;
			while (result->next()) {
				cout << o << ": " << result->getString(1).c_str() << endl;
				o++;
			}

			string campus;
			int p;
			cin >> p;
			while (std::cin.fail() || (p < 1 || p > 11)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> p;
			}
			campus = SelectCampus(p);

			cout << "Please select a gender: " << endl;
			PrintGenders();
			string gender;
			int r;
			cin >> r;
			while (std::cin.fail() || (r < 0 || r > 3)) {
				std::cin.clear();
				cin.ignore(10000, '\n');
				cout << "Error: Invalid input" << endl << "Please try again:" << endl;
				cin >> r;
			}

			gender = SelectGender(r);

			//Inserts user enter data as an entry into the "Professor" Table of the SQL database
			pstmt = con->prepareStatement("INSERT INTO `Professor`(ID, First_Name, Last_Name, Department, Campus, Gender) VALUES(?, ?, ?, ?, ?, ?);");
			pstmt->setString(1, ID);
			pstmt->setString(2, first);
			pstmt->setString(3, last);
			pstmt->setString(4, department);
			pstmt->setString(5, campus);
			pstmt->setString(6, gender);
			pstmt->execute();
			cout << "One row inserted." << endl;
			break;
		}
		//Deletes exising records matching user input ID
		case 7: {
			cout << "Please enter ID of the record to be deleted: " << endl;
			string ID;
			cin >> ID;
			pstmt = con->prepareStatement("DELETE FROM Student WHERE ID = ?;");
			pstmt->setString(1, ID);
			pstmt->execute();
			pstmt = con->prepareStatement("DELETE FROM Professor WHERE ID = ?;");
			pstmt->setString(1, ID);
			pstmt->execute();

			cout << "Record Deleted" << endl;

			break;
		}
		case 8:
			break;
		}

		//Checks if user wants to exit or return to menu
		cout << "Exit UA People Management System? y/n" << endl;
		char pin;
		cin >> pin;

		switch (pin) {
			case 'y':
				flag = false;
				cout << "Exiting";
				break;
			case 'n':
				break;
			default:
				cout << "Invalid entry. Returning to menu" << endl;
		}
	}
}
