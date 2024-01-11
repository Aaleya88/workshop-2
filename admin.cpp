#include "admin.h"
#include <ctime>
#include "DBConnection.h" 
using namespace std;

admin::admin() {
	//initialize
	adminID = 1;
	adminFirstName = "";
	adminLastName = "";
	adminUsername = "";
	adminEmail = "";
	adminPassword = "";
	adminPhoneNo = "";
}
admin::admin(int adminID, std::string adminFirstName, std::string adminLastName, std::string adminUsername, std::string adminEmail, std::string adminPassword, std::string adminPhoneNo, std::string adminSecQuestion, std::string adminNewPassword) {
	this->adminID = adminID;
	this->adminFirstName = adminFirstName;
	this->adminLastName = adminLastName;
	this->adminUsername = adminUsername;
	this->adminEmail = adminEmail;
	this->adminPassword = adminPassword;
	this->adminPhoneNo = adminPhoneNo;
	this->adminSecQuestion = adminSecQuestion;
	this->adminNewPassword = adminNewPassword;

}
bool admin::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE adminUsername=? AND adminPassword=?");
	db.stmt->setString(1, adminUsername);
	db.stmt->setString(2, adminPassword);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			adminID = db.res->getInt("adminID");
			adminFirstName = db.res->getString("adminFirstName");
			adminLastName = db.res->getString("adminLastName");
			adminUsername = db.res->getString("adminUsername");
			adminEmail = db.res->getString("adminEmail");
			adminPassword = db.res->getString("adminPassword");
			adminPhoneNo = db.res->getString("adminPhoneNo");

		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}
void admin::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into admin (adminFirstName, adminLastName, adminUsername, adminEmail, adminPassword, adminPhoneNo) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, adminFirstName);
	db.stmt->setString(2, adminLastName);
	db.stmt->setString(3, adminUsername);
	db.stmt->setString(5, adminEmail);
	db.stmt->setString(6, adminPassword);
	db.stmt->setString(7, adminPhoneNo);

	db.QueryStatement();
	db.~DBConnection();
}
void admin::update() {

	DBConnection db;
	db.prepareStatement("UPDATE admin SET adminUsername=?, adminEmail=?, adminPassword=?, adminPhoneNo=? WHERE adminID=?");
	db.stmt->setString(1, adminUsername);
	db.stmt->setString(2, adminEmail);
	db.stmt->setString(3, adminPassword);
	db.stmt->setString(4, adminPhoneNo);
	db.stmt->setInt(5, adminID);
	db.QueryStatement();
	db.~DBConnection();
}
void admin::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM admin WHERE adminID=?");
	db.stmt->setInt(1, adminID);
	db.QueryStatement();
	db.~DBConnection();
}

bool admin::adminForgotPassword()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE adminUsername=?, adminSecQuestion=?");
	db.stmt->setString(1, adminUsername);
	db.stmt->setString(2, adminSecQuestion);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			adminID = db.res->getInt("adminID");
			adminFirstName = db.res->getString("adminFirstName");
			adminLastName = db.res->getString("adminLastName");
			adminUsername = db.res->getString("adminUsername");
			adminEmail = db.res->getString("adminEmail");
			adminPassword = db.res->getString("adminPassword");
			adminPhoneNo = db.res->getString("adminPhoneNo");
			adminSecQuestion = db.res->getString("adminSecQuestion");
		}
		db.~DBConnection();
		return true;
	}
	else
	{
		db.~DBConnection();
		return false;
	}
}

//vector<guest>guest::findGuest(string firstName, string lastName, string email, string phoneNo, bool ascending)
//{
//	string query = "SELECT * FROM guest WHERE "
//		"firstName LIKE ? AND lastName LIKE ? AND email LIKE ? AND phoneNo LIKE ?"
//		"ORDER BY firstName";
//
//	if (ascending)
//	{
//		query += "ASC";
//	}
//	else
//	{
//		query += "DESC";
//	}
//
//	DBConnection db;
//	db.prepareStatement(query);
//	db.stmt->setString(1, "%" + firstName + "%");
//	db.stmt->setString(2, "%" + lastName + "%");
//	db.stmt->setString(3, "%" + email + "%");
//	db.stmt->setString(4, "%" + phoneNo + "%");
//
//	vector<guest> user;
//
//	db.QueryResult();
//
//	if (db.res->rowsCount() > 0)
//	{
//		while (db.res->next())
//		{
//			guest tmpGuest(db.res);
//			user.push_back(tmpGuest);
//		}
//		db.~DBConnection();
//		return user;
//	}
//}

admin::~admin() {

}
