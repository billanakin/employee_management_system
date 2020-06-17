#pragma once
#include <string>


class Employee {
private:
	int id;
	std::string first_name;
	std::string last_name;

public:
	// methods
	void format_first_name();
	void format_last_name();

	// getters
	int get_id();
	std::string get_first_name();
	std::string get_last_name();
	
	// setters
	void set_id(int id_val);
	void set_first_name(std::string first_name_val);
	void set_last_name(std::string first_name_val);
	
	// Constructor
	Employee(int id_val = 0, std::string first_name_val = "None", std::string last_name_val = "None");
	
	// Copy Constructor
	Employee(const Employee &source);
};

