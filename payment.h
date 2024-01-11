#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <vector>
#include "booking.h"

class payment
{
public:

	std::string paymentMethod, paymentDateTime, paymentStatus;
	int paymentID, bookingID;
	double totalPayment;

	std::vector<std::pair<booking, int>> items; // pair of product and its quantity, represents the transaction_item table

	payment();
	void addBooking(booking product, int quantity);
	void insertPayment();
	double total();
	int count();
};


#endif

