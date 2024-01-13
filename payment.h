#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <vector>
#include "booking.h"
#include "DBConnection.h"

class payment
{
public:

	std::string paymentDateTime, paymentStatus;
	int paymentID, bookingID;
	double totalPayment;

	std::vector<std::pair<booking, int>> items; // pair of product and its quantity, represents the transaction_item table

	payment(sql::ResultSet* data);
	payment();
	//void addBooking(booking product, int quantity);
	void insertPayment();
	double total();
	int count();

	~payment();

	static payment findPayment(int paymentID);
	static std::vector<payment> paymentHistory(double totalPayment, std::string paymentDateTime, bool ascending);


};


#endif

