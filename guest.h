#pragma once
#ifndef GUEST_H
#define GUEST_H

#include <string>
#include <vector>
#include <string>
#include "DBConnection.h"

class guest
{
public://access specifier

	int guestID ; //numerical attributes
	std::string username, password, email, firstName, lastName, phoneNo, secQuestion, newPassword; // text attributes // address, city, state

	guest(); // constructor method
	guest(int guestID, std::string firstName, std::string lastName, std::string username, std::string password, std::string email, std::string phoneNo, std::string secQuestion, std::string newPassword); //std::string address, std::string city, std::string state
	guest(sql::ResultSet* data);

	bool login();
	void insert();
	void update();
	void remove();
	bool forgotPassword();

	//static std::vector<guest> findGuest(std::string firstName, std::string lastName, std::string email, std::string phoneNo, bool ascending);

	~guest(); //destructor method 

	static guest selectGuest(int guestID);
	static std::vector<guest> findGuest(std::string firstName, std::string lastName, std::string email, std::string phoneNo, bool ascending);

};

#endif
