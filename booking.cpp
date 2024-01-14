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
}

booking::booking(sql::ResultSet* data) 
{
	bookingID = data->getInt("bookingID");
	guestID = data->getInt("guestID");
	checkInDate = data->getString("checkInDate");
	checkOutDate = data->getString("checkOutDate");
	guestCount = data->getInt("guestCount");
	noOfNights = data->getInt("noOfNights");
}

void booking::insertBooking()
{
	DBConnection db;//instantiate
	db.prepareStatement("Insert into booking (guestID, checkInDate, checkOutDate, noOfNights, guestCount) VALUES (?,?,?,?,?)"); //address, city, state
	db.stmt->setInt(1, guestID);
	db.stmt->setString(2, checkInDate);
	db.stmt->setString(3, checkOutDate);
	db.stmt->setInt(4, noOfNights);
	db.stmt->setInt(5, guestCount); 
	db.QueryStatement();
    bookingID = db.getGeneratedId();
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
	db.stmt->setInt(5, bookingID);
	db.QueryStatement();
	db.~DBConnection();
}

void booking::removeBooking() {
	DBConnection db;
	db.prepareStatement("DELETE FROM booking WHERE bookingID=? AND guestID=?");
	db.stmt->setInt(1, bookingID);
    db.stmt->setInt(2, guestID);
	db.QueryStatement();
	db.~DBConnection();
}

//bool booking::checkInDateExist(const std::string & phoneNo) {
 //    DBConnection db;
 //    db.prepareStatement("SELECT * FROM guest WHERE phoneNo=?");
 //    db.stmt->setString(1, phoneNo);
 //    db.QueryResult();

 //    return (db.res->rowsCount() > 0);
 //}

vector<booking> booking::findBooking(string checkInDate, string checkOutDate, int noOfNights, int guestCount, bool ascending)
{
    string query = "SELECT * FROM booking WHERE guestID != 0 AND"
    " checkInDate LIKE ? AND checkOutDate LIKE ? AND noOfNights LIKE ? AND guestCount LIKE ? "
    " ORDER BY noOfNights ";

    // Check if any other conditions are provided
  /*  if (!checkInDate.empty() || !checkOutDate.empty() || noOfNights != 0 || guestCount != 0)
    {
        query += " AND";

        if (!checkInDate.empty())
            query += " checkInDate LIKE ?";
        if (!checkOutDate.empty())
        {
            if (!checkInDate.empty()) query += " AND";
            query += " checkOutDate LIKE ?";
        }
        if (noOfNights != 0)
        {
            if (!checkInDate.empty() || !checkOutDate.empty()) query += " AND";
            query += " noOfNights LIKE ?";
        }
        if (guestCount != 0)
        {
            if (!checkInDate.empty() || !checkOutDate.empty() || noOfNights != 0) query += " AND";
            query += " guestCount LIKE ?";
        }
    }

    query += " ORDER BY noOfNights ";*/

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

    //int parameterIndex = 1;
    /*if (!checkInDate.empty()) db.stmt->setString(parameterIndex++, "%" + checkInDate + "%");
    if (!checkOutDate.empty()) db.stmt->setString(parameterIndex++, "%" + checkOutDate + "%");
    if (noOfNights != 0) db.stmt->setInt(parameterIndex++, noOfNights);
    if (guestCount != 0) db.stmt->setInt(parameterIndex++, guestCount);*/

    db.stmt->setString(1, "%" + checkInDate + "%");
    db.stmt->setString(2, "%" + checkOutDate + "%");
    db.stmt->setInt(3, noOfNights);
    db.stmt->setInt(4, guestCount);

    vector<booking> buser;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            booking tmpBooking(db.res);
            buser.push_back(tmpBooking);
        }
        db.~DBConnection();
        return buser;
    }
}


vector<booking> booking::bookingHistory(int guestID, string checkInDate, string checkOutDate, int noOfNights, int guestCount, bool ascending)
{
    string query = "SELECT * FROM booking WHERE guestID = ?";

    // Continue with the existing conditions
    if (!checkInDate.empty() || !checkOutDate.empty() || noOfNights != 0 || guestCount != 0)
    {
        query += " AND";

        if (!checkInDate.empty())
            query += " checkInDate LIKE ?";
        if (!checkOutDate.empty())
        {
            if (!checkInDate.empty()) query += " AND";
            query += " checkOutDate LIKE ?";
        }
        if (noOfNights != 0)
        {
            if (!checkInDate.empty() || !checkOutDate.empty()) query += " AND";
            query += " noOfNights LIKE ?";
        }
        if (guestCount != 0)
        {
            if (!checkInDate.empty() || !checkOutDate.empty() || noOfNights != 0) query += " AND";
            query += " guestCount LIKE ?";
        }
    }

    query += " ORDER BY noOfNights ";

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

    // Set the guestID as a parameter
    db.stmt->setInt(1, guestID);

    int parameterIndex = 2;
    if (!checkInDate.empty()) db.stmt->setString(parameterIndex++, "%" + checkInDate + "%");
    if (!checkOutDate.empty()) db.stmt->setString(parameterIndex++, "%" + checkOutDate + "%");
    if (noOfNights != 0) db.stmt->setInt(parameterIndex++, noOfNights);
    if (guestCount != 0) db.stmt->setInt(parameterIndex++, guestCount);

    vector<booking> buser;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            booking tmpHistory(db.res);
            buser.push_back(tmpHistory);
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
