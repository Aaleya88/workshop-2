#include "payment.h"
#include <string>
#include <vector> 
#include <iostream>
#include <iomanip>

using namespace std;

payment::payment() 
{
	paymentDateTime = "";
	paymentStatus = "";
	totalPayment = 0;
	paymentID = 0;
	bookingID = 0;
}

payment::payment(sql::ResultSet* data)
{
	paymentID = data->getInt("paymentID");
	bookingID = data->getInt("bookingID");
	totalPayment = data->getDouble("totalPayment");
	paymentStatus = data->getString("paymentStatus");
	paymentDateTime = data->getString("paymentDateTime");
}

void payment::insertPayment() 
{
	DBConnection db;
	db.prepareStatement("INSERT INTO payment (bookingID, totalPayment) VALUES (?,?)");
	db.stmt->setInt(1, bookingID);
	db.stmt->setInt(2, totalPayment);
	db.QueryStatement();
	db.~DBConnection();
}

payment::~payment()
{

}
