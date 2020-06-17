#include "Employee.hpp"
#include <cctype>
#include <string>

// methods
void Employee::format_first_name() {
	std::string tstring {};
	for (int i{0}; i < first_name.length(); i++) {
		if (i == 0) {
			tstring += toupper(first_name[i]);
		}
		else if (first_name[i - 1] == ' ') {
			tstring += toupper(first_name[i]);
		}
		else {
			tstring += first_name[i];
		}
		
	}
	first_name = tstring;
}

void Employee::format_last_name() {
	std::string tstring {};
	for (int i{0}; i < last_name.length(); i++) {
		if (i == 0) {
			tstring += toupper(last_name[i]);
		}
		else {
			tstring += last_name[i];
		}
	}
	last_name = tstring;
}


// getters
int Employee::get_id() {return id;}
std::string Employee::get_first_name() {return first_name;}
std::string Employee::get_last_name() {return last_name;}


// setters
void Employee::set_id(int id_val) {
	id = id_val;
}

void Employee::set_first_name(std::string first_name_val) {
	first_name = first_name_val;
}

void Employee::set_last_name(std::string last_name_val) {
	last_name = last_name_val;
}


// Constructor
Employee::Employee(int id_val, std::string first_name_val, std::string last_name_val) 
	: id{id_val}, first_name{first_name_val}, last_name{last_name_val} {
}

// Copy Constructor
Employee::Employee(const Employee &source) 
	: Employee{source.id, source.first_name, source.last_name} {
}