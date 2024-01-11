#include "review.h"
#include <iostream>
#include <ctime>
#include "DBConnection.h"

review::review() {
	//initialize
	reviewID = 0;
	guestID = 0;
	rating = 0;
	comment = "";
	reviewDate = "";
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

review::~review() {

}