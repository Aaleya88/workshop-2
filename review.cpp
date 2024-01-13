#include "review.h"
#include <vector> 
#include <iostream>
#include <iomanip>
#include <string>
#include "DBConnection.h"

using namespace std;

review::review() {
	//initialize
	reviewID = 0;
	guestID = 0;
	rating = 0;
	comment = "";
	reviewDate = "";
}

review::review(sql::ResultSet* data)
{
	reviewID = data->getInt("reviewID");
	guestID = data->getInt("guestID");
	rating = data->getInt("rating");
	comment = data->getString("comment");
	reviewDate = data->getString("reviewDate");
}

review::review(int reviewID, int guestID, int rating, std::string comment, std::string reviewDate) {
	this->reviewID = reviewID;
	this->guestID = guestID;
	this->comment = comment;
	this->rating = rating;
	this->reviewDate = reviewDate;
}

void review::insertReview() {
	DBConnection db;
	db.prepareStatement("Select guestID from guest where guestID = ?");
	db.prepareStatement("Insert into review (comment, rating, guestID) VALUES (?,?,?)");
	db.stmt->setString(1, comment);
	db.stmt->setInt(2, rating);
	db.stmt->setInt(3, guestID);
	db.QueryStatement();
	db.~DBConnection();
}

void review::editReview() {

	DBConnection db;
	db.prepareStatement("UPDATE review SET comment=?, rating=?, reviewDate=? WHERE reviewID=?");
	db.stmt->setString(1, comment);
	db.stmt->setInt(2, rating);
	db.stmt->setString(3, reviewDate);
	db.stmt->setInt(4, reviewID);
	db.QueryStatement();
	db.~DBConnection();

}
void review::removeReview() {
	DBConnection db;
	db.prepareStatement("DELETE FROM review WHERE reviewID=?");
	db.stmt->setInt(1, reviewID);
	db.QueryStatement();
	db.~DBConnection();
}

vector<review> review::findReview(int rating, string comment, bool ascending)
{
    string query = "SELECT * FROM review WHERE guestID != 0";

    // Check if any other conditions are provided
    if (!comment.empty() || rating != 0)
    {
        if (!comment.empty())
            query += " comment LIKE ?";
        if (rating != 0)
        {
            if (!comment.empty()) query += " AND";
            query += " rating LIKE ?";
        }
    }

    query += " ORDER BY rating ";

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

    int parameterIndex = 1;
    
    if (!comment.empty()) db.stmt->setString(parameterIndex++, "%" + comment + "%");
    if (rating != 0) db.stmt->setInt(parameterIndex++, rating);

    vector<review> reviews;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            review tmpReview(db.res);
            reviews.push_back(tmpReview);
        }
        db.~DBConnection();
        return reviews;
    }
}

review::~review() {

}