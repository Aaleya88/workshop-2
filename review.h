#pragma once
#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <vector>
#include "DBConnection.h"

class review
{
public:
    // Constructor
    int reviewID, guestID, rating;
    std::string comment, reviewDate;

    review();
    review(sql::ResultSet* data);
    review(int reviewID, int guestID, int rating, std::string comment, std::string reviewDate);


    // Function to write a review
    void insertReview();

    // Function to view the review
    void editReview();
    void removeReview();

    ~review();

    static review findReview(int reviewID);
    static std::vector<review> findReview(int rating, std::string comment, bool ascending);

};

#endif

