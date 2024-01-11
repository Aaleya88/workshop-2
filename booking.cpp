#include "booking.h"
#include <vector> 
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

booking::booking() 
{
	bookingID = 0;
	guestID = 0;
	checkInDate = "";
	checkOutDate = "";
	guestCount = 0;
	noOfNights = 0;
	totalPayment = 0;
	paymentStatus = "";
	paymentDateTime = "";
}

booking::booking(sql::ResultSet* data) 
{
	bookingID = data->getInt("bookingID");
	guestID = data->getInt("guestID");
	checkInDate = data->getString("checkInDate");
	checkOutDate = data->getString("checkOutDate");
	guestCount = data->getInt("guestCount");
	noOfNights = data->getInt("noOfNights");
	totalPayment = data->getDouble("totalPayment");
	paymentStatus = data->getString("paymentStatus");
	paymentDateTime = data->getString("paymentDateTime");
}

void booking::insertBooking()
{
	DBConnection db;//instantiate
	db.prepareStatement("Insert into booking (guestID, checkInDate, checkOutDate, noOfNights, guestCount, totalPayment) VALUES (?,?,?,?,?,?)"); //address, city, state
	db.stmt->setInt(1, guestID);
	db.stmt->setString(2, checkInDate);
	db.stmt->setString(3, checkOutDate);
	db.stmt->setInt(4, noOfNights);
	db.stmt->setInt(5, guestCount); 
	db.stmt->setDouble(6, totalPayment);
	db.QueryStatement();
	db.~DBConnection();
}

void booking::updateBooking()
{
	DBConnection db;
	db.prepareStatement("UPDATE booking SET checkInDate=?, checkOutDate=?, guestCount=?, noOfNights=? WHERE bookingID=?");
	db.stmt->setString(1, checkInDate);
	db.stmt->setString(2, checkOutDate);
	db.stmt->setInt(3, guestCount);
	db.stmt->setInt(4, noOfNights);
	//db.stmt->setString(4, paymentDateTime);
	db.stmt->setInt(5, bookingID);
	db.QueryStatement();
	db.~DBConnection();
}

void booking::removeBooking() {
	DBConnection db;
	db.prepareStatement("DELETE FROM booking WHERE bookingID=?");
	db.stmt->setInt(1, bookingID);
	db.QueryStatement();
	db.~DBConnection();
}

vector<booking>booking::findBooking(int guestID, string checkInDate, string checkOutDate, int noOfNights, int guestCount, bool ascending)
{
	string query = "SELECT * FROM booking WHERE "
		" guestID LIKE ? AND checkInDate LIKE ? AND checkOutDate LIKE ? AND noOfNights LIKE ? AND guestCount LIKE ? "
		" ORDER BY noOfNights ";

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
	db.stmt->setInt(1, guestID);
	db.stmt->setString(2, "%" + checkInDate + "%");
	db.stmt->setString(3, "%" + checkOutDate + "%");
	db.stmt->setInt(4, noOfNights);
	db.stmt->setInt(5, guestCount);
	//db.stmt->setDouble(5, totalPayment);
	//db.stmt->setString(6, paymentStatus);

	vector<booking> buser;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			booking tmpGuest(db.res);
			buser.push_back(tmpGuest);

		}
		db.~DBConnection();
		return buser;
	}
}

booking::~booking()
{

}



//DATE
//std::string booking::formatDate() const {
//	// Use member variables directly
//	std::istringstream issCheckIn(checkInDate);
//	int checkInYear, checkInMonth, checkInDay;
//	char delimiter;
//
//	if (!(issCheckIn >> checkInYear >> delimiter >> checkInMonth >> delimiter >> checkInDay)) {
//		return "Invalid date format";
//	}
//
//	std::istringstream issCheckOut(checkOutDate);
//	int checkOutYear, checkOutMonth, checkOutDay;
//
//	if (!(issCheckOut >> checkOutYear >> delimiter >> checkOutMonth >> delimiter >> checkOutDay)) {
//		return "Invalid check-out date format";
//	}
//
//	std::stringstream ss;
//	ss << "Check-in date: " << std::setfill('0') << std::setw(4) << checkInYear << "-"
//		<< std::setw(2) << checkInMonth << "-" << std::setw(2) << checkInDay << "\n";
//	ss << "Check-out date: " << std::setfill('0') << std::setw(4) << checkOutYear << "-"
//		<< std::setw(2) << checkOutMonth << "-" << std::setw(2) << checkOutDay;
//
//	return ss.str();
//}
