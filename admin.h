#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class admin
{
public://access specifier
	int adminID; //numerical attributes
	std::string adminUsername, adminPassword, adminEmail, adminFirstName, adminLastName, adminPhoneNo, adminSecQuestion, adminNewPassword; // text attributes


	admin(); // constructor method
	admin(int adminID, std::string adminFirstName, std::string adminLastName, std::string adminUsername, std::string adminPassword, std::string adminEmail, std::string adminPhoneNo, std::string adminSecQuestion, std::string adminNewPassword);

	bool login();
	void insert();
	void update();
	void remove();
	bool adminForgotPassword();

	//static std::vector<guest> findGuest(std::string firstName, std::string lastName, std::string email, std::string phoneNo, bool ascending);

	~admin(); //destructor method 

};
#endif
