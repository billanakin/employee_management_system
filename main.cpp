#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Employee.hpp"
using namespace std;

// Formatting dont mind this
template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
    return center_helper<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
    std::streamsize w = s.width();
    if (w > c.str_.length()) {
        std::streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}

void display_menu();
char prompt_selection();
void get_data_from_csv();
void store_data_from_csv();
void handle_print_list_of_employees();
void handle_add_new_employees();
void handle_delete_employee();
void handle_edit_employee();
void handle_quit();
void handle_unknown();
bool have_found_id(int id);
int index_of_employee(int id);
bool file_is_empty(std::ifstream& pFile);

vector<Employee> list_of_employees {};
int main() {
	
	get_data_from_csv();
	
	char selection {};
	do {
		display_menu();
		selection = prompt_selection();	
		
		if (isalpha(selection)) {
			cout << "Invalid Input - try again" << endl;
			cout << endl;
			continue;
		}
		else {
			int i_selection = selection - '0';
			switch (i_selection) {
				case 1: 
					handle_print_list_of_employees();
					break;
				case 2: 
					handle_add_new_employees();
					break;
				case 3:
					handle_delete_employee();
					break;
				case 4:
					handle_edit_employee();
					break;
				case 5: 
					handle_quit();
					break;
				default:
					handle_unknown();
			}
		}
		
		cout << endl;
	} while (selection != 5);
	
	store_data_from_csv();
	
	return 0;
}

void display_menu() {
	cout << "+-----------------------+" << endl;
	cout << "|        -Menu-         |" << endl;
	cout << "+-----+-----------------+" << endl;
	cout << "| [1] | List Employees  |" << endl;
	cout << "| [2] | New Employees   |" << endl;
	cout << "| [3] | Delete Employee |" << endl;
	cout << "| [4] | Edit Employee   |" << endl;
	cout << "| [5] | Quit            |" << endl;
	cout << "+-----+-----------------+" << endl;
	cout << endl;
}

char prompt_selection() {
	char choice {};
	cout << "Enter choice: ";
	cin  >> choice;
	return choice;
}

void get_data_from_csv() {
	
	cout << "------------------------------------" << endl;
	cout << "Configuring Data from CSV...." << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << endl;
	
	ifstream my_file;
	my_file.open("employees.csv");
	
	if (!(file_is_empty(my_file))) {
		// Get data from CSV
		string object_attributes;
		while (getline(my_file, object_attributes, '\n')) {
			// Vector of string to save attributes 
			vector <string> list_of_attributes; 
			// stringstream class check1 
			stringstream check1(object_attributes); 
			string intermediate; 
			// Splitting string with separator ',' the store it to list_of_attributes
			while(getline(check1, intermediate, ',')) { 
				list_of_attributes.push_back(intermediate); 
			} 
			  
			// Setting values from list_of_attributes vector
			Employee employee;
			
			int id;
			string first_name;
			string last_name;
			// convert string to int ---------------------
			string str_id = list_of_attributes[0];
  
			// object from the class stringstream 
			stringstream convert_string(str_id); 
			// The object has the value 12345 and stream 
			// it to the integer x 
			id = 0; 
			convert_string >> id; 
			
			// ------------------------------------------
			employee.set_id(id);
			first_name = list_of_attributes[1];
			employee.set_first_name(first_name);
			last_name = list_of_attributes[2];
			employee.set_last_name(last_name);
			
			list_of_employees.push_back(employee);
		}
	}
	my_file.close();
}

void store_data_from_csv() {
	
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "Storing Data to CSV...." << endl;
	cout << "------------------------------------" << endl;
	cout << endl;

	
	if (!list_of_employees.empty()) {
		ofstream my_file;
		my_file.open("employees.csv");
	
		for (Employee objects: list_of_employees) {
			int csv_id = objects.get_id();
			string csv_first_name = objects.get_first_name();
			string csv_last_name = objects.get_last_name();
			
			my_file << csv_id << "," << csv_first_name << "," << csv_last_name << endl;
		}
	
		my_file.close();
	}
	else {
		std::ofstream my_file;
		my_file.open("employees.csv", std::ofstream::out | std::ofstream::trunc);
		my_file.close();
	}
}

void handle_print_list_of_employees() {
	cout << endl;
	if (!list_of_employees.empty()) {
		cout << "+-----+---------------------+--------------+" << endl;
		cout << "| ID  |     First Name      |  Last Name   |" << endl;
		cout << "+-----+---------------------+--------------+" << endl;
		for (Employee employee: list_of_employees) {
		employee.format_first_name();
		employee.format_last_name();
		cout << "|  " << employee.get_id() << "  |" << setw(21) << centered(employee.get_first_name()) 
			 << "|" << setw(14) << centered(employee.get_last_name()) << "|" << endl;
		}
		cout << "+-----+---------------------+--------------+" << endl;
	}
	else {
		cout << "+----------------------------+" << endl;
		cout << "|       No Employees         |" << endl;
		cout << "+----------------------------+" << endl;
	}
	
}

void handle_add_new_employees() {
	cout << endl;
	Employee employee {};
	int id {};
	string first_name {};
	string last_name {};
	if (!list_of_employees.empty()) {
		while (true) {
			cout << "ID: ";
			cin  >> id;
			if (have_found_id(id)) {
				cout << "ID is taken - try again" << endl;
				continue;
			}
			else {
				break;
			}
		}
	}
	else {
		cout << "ID: ";
		cin  >> id;
	}
	employee.set_id(id);
	cout << "First Name: ";
	cin.ignore();
	getline(std::cin, first_name);
	employee.set_first_name(first_name);
	cout << "Last Name: ";
	cin  >> last_name;
	employee.set_last_name(last_name);
	list_of_employees.push_back(employee);
	cout << endl;
	employee.format_first_name();
	employee.format_last_name();
	cout << "+------------ New Employee ---------------+" << endl;
	cout << "| ID: " << employee.get_id() << endl;
	cout << "| First Name: " << employee.get_first_name() << endl;
	cout << "| Last Name: " << employee.get_last_name() << endl;
	cout << "+-----------------------------------------+" << endl;
	
}

void handle_delete_employee() {
	if (!list_of_employees.empty()) {
		while(true) {
			handle_print_list_of_employees();
			int id {};
			cout << "Enter Employee ID to delete: ";
			cin  >> id;
			if (!have_found_id(id)) {
				cout << "ID not found - try again" << endl;
				continue;
			} else {
				cout << endl;
				int index{};
				index = index_of_employee(id);
				list_of_employees[index].format_first_name();
				list_of_employees[index].format_last_name();
				cout << endl;
				cout << "+------------ Deleted ---------------+" << endl;
				cout << "| ID: " << list_of_employees[index].get_id() << endl;
				cout << "| First Name: " << list_of_employees[index].get_first_name() << endl;
				cout << "| Last Name: " << list_of_employees[index].get_last_name() << endl;
				cout << "+------------------------------------+" << endl;
				list_of_employees.erase(list_of_employees.begin() + index);
				break;
			}	
		}
	} else {
		cout << "+----------------------------+" << endl;
		cout << "|       No Employees         |" << endl;
		cout << "+----------------------------+" << endl;
	}
}

void handle_edit_employee() {
	cout << endl;
	if (!list_of_employees.empty()) {
		while (true) {
			handle_print_list_of_employees();
			int id {};
			cout << "Enter employee id to edit: ";
			cin  >> id;
			if (!have_found_id(id)) {
				cout << "ID not found - try again" << endl;
				continue;
			}
			else {
				int new_id {};
				string new_first_name;
				string new_last_name;
				int index {};
				index = index_of_employee(id);
				cout << endl;
				while (true) {
					cout << "New ID: ";
					cin  >> new_id;
					if (new_id == list_of_employees[index].get_id()) {
						list_of_employees[index].set_id(new_id);
						break;
					}
					else if (new_id != list_of_employees[index].get_id() && !have_found_id(new_id)) {
						list_of_employees[index].set_id(new_id);
						break;
					}
					else if (have_found_id(new_id)) {
						cout << "ID is taken - try again" << endl;
						continue;
					}
				}
				cout << "New First Name: ";
				cin.ignore();
				getline(cin, new_first_name);
				list_of_employees[index].set_first_name(new_first_name);
				cout << "New Last Name: ";
				cin  >> new_last_name;
				list_of_employees[index].set_last_name(new_last_name);
				cout << endl;
				list_of_employees[index].format_first_name();
				list_of_employees[index].format_last_name();
				cout << "+------------ Edited ---------------+" << endl;
				cout << "| ID: " << list_of_employees[index].get_id() << endl;
				cout << "| First Name: " << list_of_employees[index].get_first_name() << endl;
				cout << "| Last Name: " << list_of_employees[index].get_last_name() << endl;
				cout << "+-----------------------------------+" << endl;
 				break;
			} 	
		}
	} else {
		cout << "+----------------------------+" << endl;
		cout << "|       No Employees         |" << endl;
		cout << "+----------------------------+" << endl;
	}
}

void handle_quit() {
	cout << "Goodbye!" << endl;
}

void handle_unknown() {
	cout << "Unknown Selection - try again" << endl;
}

bool have_found_id(int id) {
	bool id_is_find {false};
	for (Employee employee: list_of_employees) {
		if (id == employee.get_id()) {
			id_is_find = true;
			break;
		}
	}
	return id_is_find;
}

int index_of_employee(int id) {
	int index {-1};
	for (size_t i{0}; i < list_of_employees.size(); i++) {
		if (id == list_of_employees[i].get_id()) {
			index = i;
			break;
		}
	}
	return index;
}

bool file_is_empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}