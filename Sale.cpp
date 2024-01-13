#include "Sale.h"
using namespace std;
using namespace sql;

Sale::Sale(ResultSet* data)
{
	value = data->getDouble("value");
	date = data->getString("date");
}

vector<Sale> Sale::salesReport(string start, string end, bool sortByDate, bool ascending) 
{
	
	string sql = " SELECT p.paymentDateTime as date, SUM(p.totalPayment) as value "
		" FROM payment p ";
		
// add the where clause 
	sql += " WHERE  p.paymentDateTime >= ? AND p.paymentDateTime <= ? ";

	// now construct our grouping
	sql += " GROUP BY ";

	// otherwise we skip the p.category to only groups it by its year and month
	sql += " CAST(MONTH(p.paymentDateTime) AS VARCHAR(2)) + '-' + CAST(YEAR(p.paymentDateTime) AS VARCHAR(4)) ";
	//    10-2023

// now construct the sorting clause
	sql += " ORDER BY  ";
	if (sortByDate) {
		// we have bool sortByDate parameter, if this value is true then we use date column for ordering
		sql += " p.paymentDateTime ";
	}
	else {
		// otherwise we use the result column sale for ordering
		sql += " value ";
	}

	// finally the ordering direction determined using boolean ascending
	if (ascending) {
		sql += " ASC ";
	}
	else {
		sql += " DESC ";
	}

	// declare vector > execute query > return result in vector 
	vector <Sale> salesReport;

	DBConnection db;

	db.prepareStatement(sql);
	// since we have non-fixed number of placeholder ? in our prepared statment we need to use a varaible to keep track of the index

	int index = 1; // start from 1
	
	db.stmt->setString(index, start);
	index++;//move index forward
	db.stmt->setString(index, end);
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Sale tmpSale(db.res);
			salesReport.push_back(tmpSale);

		}
	}

	db.~DBConnection();
	return salesReport;
}


// in Sale.h we have already give destructor ~Sale() so we do not need to define it in this file

