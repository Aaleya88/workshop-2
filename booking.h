#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include "DBConnection.h"

class booking
{
public:
	int bookingID, guestID, guestCount, noOfNights;
	double totalPayment;
	std::string checkInDate, checkOutDate, paymentStatus, paymentDateTime;

	booking();
	booking(sql::ResultSet* data);

	//void setGuestID(int guestID);

	void insertBooking();
	void updateBooking();
	void removeBooking();
	//int getGuestCount();

	//void insertPayment();

	//std::string formatDate() const;

	~booking();

	static booking findBooking(int bookingID);
	static std::vector<booking> findBooking(std::string checkInDate, std::string checkOutDate, int noOfNights, int guestCount, bool ascending);

	static std::vector<booking> bookingHistory(int guestID, std::string checkInDate, std::string checkOutDate, int noOfNights, int guestCount, bool ascending);

};

#endif