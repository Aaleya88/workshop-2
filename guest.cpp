#include "guest.h"
#include <ctime>
#include <vector>
#include <iomanip>
#include "DBConnection.h" 
using namespace std; 

guest::guest() 
{
	//initialize
	guestID = 0;
	firstName = "";
	lastName = "";
	username = "";
	email = "";
	password = "";
	phoneNo = "";
	secQuestion = "";
	newPassword = "";
}

guest::guest(sql::ResultSet* data)
{
	guestID = data->getInt("guestID");
	username = data->getString("username");
	firstName = data->getString("firstName");
	lastName = data->getString("lastName");
	email = data->getString("email");
	phoneNo = data->getString("phoneNo");
	password = data->getString("password");
	email = data->getString("email");
	secQuestion = data->getString("secQuestion");


}

guest::guest(int guestID, std::string firstName, std::string lastName, std::string username, std::string email, std::string password, std::string phoneNo, std::string secQuestion, std::string newPassword) // std::string address, std::string city, std::string state
{
	this->guestID = guestID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->username = username;
	this->email = email;
	this->password = password;
	this->phoneNo = phoneNo;
	this->secQuestion = secQuestion;
	this->newPassword = newPassword;
}

bool guest::login() 
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM guest WHERE username=? AND password=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			guestID = db.res->getInt("guestID");
			firstName = db.res->getString("firstName");
			lastName = db.res->getString("lastName");
			username = db.res->getString("username");
			email = db.res->getString("email");
			password = db.res->getString("password");
			phoneNo = db.res->getString("phoneNo");
			secQuestion = db.res->getString("secQuestion");
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

void guest::insert() 
{
	DBConnection db;//instantiate
	db.prepareStatement("Insert into guest (firstName, lastName, username, email, password, phoneNo, secQuestion) VALUES (?,?,?,?,?,?,?)"); //address, city, state
	db.stmt->setString(1, firstName);
	db.stmt->setString(2, lastName);
	db.stmt->setString(3, username);
	db.stmt->setString(4, email);
	db.stmt->setString(5, password);
	db.stmt->setString(6, phoneNo);
	db.stmt->setString(7, secQuestion);
	db.QueryStatement();
	db.~DBConnection();
}

void guest::update() 
{
	DBConnection db;
	db.prepareStatement("UPDATE guest SET username=?, password=?, email=?, phoneNo=?, secQuestion=? WHERE guestID=?"); //address=?, city=?, state=?
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, email);
	db.stmt->setString(4, phoneNo);
	db.stmt->setString(5, secQuestion);
	db.stmt->setInt(6, guestID);
	db.QueryStatement();
	db.~DBConnection();
}

void guest::remove() 
{
	DBConnection db;
	db.prepareStatement("DELETE FROM guest WHERE guestID=?");
	db.stmt->setInt(1, guestID);
	db.QueryStatement();
	db.~DBConnection();
}

bool guest::forgotPassword()
{
    DBConnection db;
	db.prepareStatement("SELECT * FROM guest WHERE username=?, secQuestion=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, secQuestion);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			guestID = db.res->getInt("guestID");
			firstName = db.res->getString("firstName");
			lastName = db.res->getString("lastName");
			username = db.res->getString("username");
			email = db.res->getString("email");
			password = db.res->getString("password");
			phoneNo = db.res->getString("phoneNo");
			secQuestion = db.res->getString("secQuestion");
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

vector<guest>guest::findGuest(string firstName, string lastName, string email, string phoneNo, bool ascending)
{
	string query = "SELECT * FROM guest WHERE "
		" firstName LIKE ? AND lastName LIKE ? AND email LIKE ? AND phoneNo LIKE ? "
		" ORDER BY firstName ";

	if (ascending)
	{
		query += "ASC";
	}
	else
	{
		query += "DESC";
	}

	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + firstName + "%");
	db.stmt->setString(2, "%" + lastName + "%");
	db.stmt->setString(3, "%" + email + "%");
	db.stmt->setString(4, "%" + phoneNo + "%");

	vector<guest> user;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			guest tmpGuest(db.res);
			user.push_back(tmpGuest);

		}
		db.~DBConnection();
		return user;
	}
}

guest::~guest() 
{

}