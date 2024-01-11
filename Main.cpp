#include <iostream>  
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <string>
#include <ctime>
#include <regex>

// advanced
// include our custom class
#include "admin.h"
#include "guest.h" 
#include "Menu.h"
#include "booking.h"
#include "payment.h"
#include "Sale.h"
#include "review.h"

using namespace std;
using namespace std::chrono;

string tmpInput;

void guestRegister();
void guestLoginMenu();
void guestPage();
void guestHome(guest user, booking buser, review reviews);
guest profile(guest user);
void book(guest user, booking buser, review reviews);
void reviewPage(guest user, review reviews);
void writeReview(guest user, review reviews);
void bookingMenu(guest user, booking buser, review reviews);
booking viewBooking(booking buser);
void contact(guest user, booking buser, review reviews);
void guestForgotPassword(guest user, booking buser, review reviews);
bool guestResetPassword(guest user, booking buser, review reviews);

void adminPage();
void adminLoginMenu();
void adminForgotPassword();
bool adminResetPassword(admin admins);
void adminhome(admin admins);
admin adminProfile(admin admins);
void bookingManage(admin admins);
void guestManage(admin admins);

void homestayDetails(guest user, booking buser, review reviews);

void SaleReportMenu(admin admins);

//utility functions
bool isNumeric(string input);

bool validateDate(const std::string& date);
//double calculateNumNights(const string& checkInDate, const string& checkOutDate);

 //extras
bool toInteger(string* input, int* valueholder);

//MAIN PAGE
int main() {

	Menu mainmenu;
	mainmenu.header = "\n\t\t\t\t\t----------------------------------------\n\t\t\t\t\t\tWelcome to Sky Homestay\n\t\t\t\t\t----------------------------------------\n";
	mainmenu.addOption("Press 1 if you are a Guest");
	mainmenu.addOption("Press 2 if you are an Admin");
	mainmenu.addOption("Press 3 to Exit");
	mainmenu.footer = "\n\t\t\t\t\t-----------------------------\n\t\t\t\t\tSelect Option\n\t\t\t\t\t";

	while (1) {
		switch (mainmenu.prompt())
		{
		case 1:
			guestPage();
			break;
		case 2:
			adminPage();
			break;
		case 3:
			exit(0);
		}
	}
}

//ADMIN PAGE
void adminPage()
{
	Menu adminMenu;
	adminMenu.header = "\n\n\t\t\t\t\t----------- ADMIN PAGE -----------\n\n\t\t\t\t\tChoose:";
	adminMenu.addOption("Login Menu");
	adminMenu.addOption("Back to Main Menu");
	adminMenu.footer = "\n\t\t\t\t\t---------------------------------\n\t\t\t\t\tSelect Option";

	while (1) {
		switch (adminMenu.prompt())
		{
		case 1:
			adminLoginMenu();
			break;
		case 2:
			return;
		default:
			break;
			break;
		}
	}
}

//ADMIN LOGIN
void adminLoginMenu()
{
	Menu adminLoginMenu;
	adminLoginMenu.header = "\n\t\t\t\t\t------ ADMIN LOGIN -------\n\n\t\t\t\t\tChoose:";
	adminLoginMenu.addOption("Enter username");
	adminLoginMenu.addOption("Enter password");
	adminLoginMenu.addOption("Continue login");
	adminLoginMenu.addOption("Forgot password");
	adminLoginMenu.addOption("Back to Admin Page");
	adminLoginMenu.footer = "\n\t\t\t\t\t-------------------------\n\t\t\t\t\tSelect Option\n\t\t\t\t\t";

	admin admins;

	while (1) {
		switch (adminLoginMenu.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username: ";
			cin >> admins.adminUsername;
			adminLoginMenu.setValue(0, admins.adminUsername);
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Password: ";
			cin >> admins.adminPassword;
			adminLoginMenu.setValue(1, admins.adminPassword);
			break;
		case 3:
			if (admins.login()) {
				adminhome(admins);
			}
			else {
				cout << "\t\t\t\t\tInvalid Login";
				_getch();
			}
			break;
		case 4:
			adminForgotPassword();
		case 5:
			main();
			break;
		}
	}
}

//ADMIN FORGOT PASSWORD
void adminForgotPassword()
{
	admin admins;
	booking buser;
	review reviews;// copy the object
	Menu adminForgotPassword;
	adminForgotPassword.header = "\n\n\t\t\t\t\t------ FORGOT PASSWORD -------\n\n\t\t\t\t\tChoose:";
	adminForgotPassword.addOption("Enter username");
	adminForgotPassword.addOption("Enter Answer for Security Question ");
	adminForgotPassword.addOption("Continue");
	adminForgotPassword.addOption("Back to Admin Page");
	adminForgotPassword.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	bool valid = true;

	while (1) {
		switch (adminForgotPassword.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username:";
			cin >> admins.adminUsername;
			adminForgotPassword.setValue(0, admins.adminUsername);
			break;
		case 2:
			cout << "\t\t\t\t\tWhat is your mother's name?:";
			cin >> admins.adminSecQuestion;
			adminForgotPassword.setValue(1, admins.adminSecQuestion);
			break;
		case 3:
			if (admins.adminForgotPassword()) {
				adminResetPassword(admins);
			}
			else {
				cout << "\t\t\t\t\tInvalid username or answer!";
				_getch();
			}
			break;
		case 4:
			adminLoginMenu();
			break;
		}
	}
}

//ADMIN RESET PASSWORD
bool adminResetPassword(admin admins)
{
	admin temp = admins; // copy the object
	admin adminResetPassword;
	Menu newPassword;
	newPassword.header = "\n\n\t\t\t\t\t------ RESET PASSWORD -------\n\n\t\t\t\t\tChoose:";
	newPassword.addOption("Enter New Password");
	newPassword.addOption("Confirm Password");
	newPassword.addOption("Continue");
	newPassword.addOption("Back to Login Menu");
	newPassword.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	while (1) {
		newPassword.setValue(0, temp.adminPassword);
		newPassword.setValue(1, temp.adminNewPassword);

		switch (newPassword.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert new password:";
			cin >> tmpinput;
			if (tmpinput.length() < 6) {
				cout << "\n\t\t\t\t\tPassword must be at least 6 character long";
				_getch();
			}
			else {
				adminResetPassword.adminPassword = tmpinput;
				newPassword.setValue(0, adminResetPassword.adminPassword);
			}
			break;
		case 2:
			cout << "\t\t\t\t\tConfirm new password:";
			cin >> tmpinput;
			if (tmpinput == adminResetPassword.adminPassword)
			{
				cout << "\t\t\t\t\tNew Password Updated!";
			}
			else
			{
				cout << "\t\t\t\t\tPassword did not match. Try again";
				_getch();
			}
			break;
		case 3:
			if (admins.login()) {
				adminhome(admins);

			}
			else {
				cout << "\t\t\t\t\tInvalid Login";
				_getch();
			}
			break;
		}
	}
}

//ADMIN HOME
void adminhome(admin admins)
{
	guest user;
	Menu homeAdmin;
	homeAdmin.header = "\n\n\t\t\t\t\t----------- ADMIN MENU -----------\n\n\t\t\t\t\tChoose:";
	homeAdmin.addOption("View Profile");
	homeAdmin.addOption("Manage Booking"); 
	homeAdmin.addOption("Manage Guest");
	homeAdmin.addOption("View Sale Report");
	homeAdmin.addOption("Logout");
	homeAdmin.footer = "\n\t\t\t\t\t-----------------------------\n\t\t\t\t\tSelect Option\n";

	while (1) 
	{
		switch (homeAdmin.prompt())
		{
		case 1:
			admins = adminProfile(admins);
		case 2:
			bookingManage(admins);
			break;
		case 3:
			guestManage(admins);
		case 4:
			SaleReportMenu(admins);
			break;
		case 5:
			adminLoginMenu();
			return;
			break;
		default:
			break;
		}
	}
}

//ADMIN PROFILE
admin adminProfile(admin admins)
{
	admin temp = admins; // copy the object

	Menu profileMenu;
	profileMenu.header = "\n\n\t\t\t\t\t-------------- ADMIN MENU --------------\n\n\t\t\t\t\tChoose to edit your information:";
	profileMenu.addOption("First Name");
	profileMenu.addOption("Last Name");
	profileMenu.addOption("Press 1 to edit Username");
	profileMenu.addOption("Press 2 to edit Email");
	profileMenu.addOption("Press 3 to edit Password");
	profileMenu.addOption("Press 4 to edit Phone No");
	profileMenu.addOption("Press 5 to Reset");
	profileMenu.addOption("Press 6 to Save");
	profileMenu.addOption("Press 7 to Back");
	profileMenu.addOption("Press 8 to Delete Account");
	profileMenu.footer = "\n\t\t\t\t\t-----------------------------------------------\n\t\t\t\t\tSelect Option\n";

	//string tmpInput;
	while (1) 
	{
		profileMenu.setValue(0, temp.adminFirstName);
		profileMenu.setValue(1, temp.adminLastName);
		profileMenu.setValue(2, temp.adminUsername);
		profileMenu.setValue(3, temp.adminEmail);
		profileMenu.setValue(4, temp.adminPassword);
		profileMenu.setValue(5, temp.adminPhoneNo);

		switch (profileMenu.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username:";
			cin >> temp.adminUsername;
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Email:";
			cin >> temp.adminEmail;
			break;
		case 3:
			cout << "\t\t\t\t\tInsert Password:";
			cin >> temp.adminPassword;
			break;
		case 4:
			cout << "\t\t\t\t\tInsert Phone No: ";
			cin >> temp.adminPhoneNo;
			break;
		case 5:
			temp = admins;
			break;
		case 6:
			admins = temp;
			admins.update();
			cout << "\t\t\t\t\tUpdated";
			_getch();
		case 7:
			return admins;
			break;
		case 8:
			cout << "\t\t\t\t\tDelete your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				admins = temp;
				admins.remove();
				main();
			}
			break;
		default:
			break;
		}
	}
}

//ADMIN BOOKING MANAGE
void bookingManage(admin admins)
{
	vector<booking> buser;
	booking selBooking;
	string displayBooking = "";


	int bookingID = 0, guestID = 0, noOfNights = 0, guestCount = 0;
	double totalPayment = 0.00;
	string checkInDate = "", checkOutDate = "", paymentStatus = "";
	bool ascending = true;

	Menu bookingManage;
	bookingManage.header = "\n\n\t\t\t\t\t------ BOOKING MANAGE -------\n\n\t\t\t\t\tSearch for guest: ";
	bookingManage.addOption("Check-In Date");
	bookingManage.addOption("Check-Out Date");
	bookingManage.addOption("No of Nights");
	bookingManage.addOption("Guest Count");
	bookingManage.addOption("Ordering");
	bookingManage.addOption("View");
	bookingManage.addOption("Back to profile");
	bookingManage.footer = "\n\t\t\t\t\t--------------\n\t\t\t\t\tSelect Option\n";

	while (1)
	{
		if (ascending) {
			bookingManage.setValue(4, "Ascending");
		}
		else {
			bookingManage.setValue(4, "Descending");
		}

		if (displayBooking == "") {
			displayBooking = "\n\t\t\t\tSearch Result:\n";
			stringstream tmpGuest;
			tmpGuest << setw(4) << "\t\t\t\tBooking ID" << "|" << setw(15) << "Guest ID"
				<< "|" << setw(20) << "Check In Date" << "|" << setw(20) << "Check-Out Date" << "|" << setw(15) << "No of Nights" << "|" 
				<< setw(15) << "Guest Count" << "|" << endl;
			tmpGuest << "\t\t\t\t----------------------------------------------------------------------------------------------------------------" << endl;

			for (int i = 0; i < buser.size(); i++) {
				tmpGuest << "\t\t\t\t" << setw(8) << buser[i].bookingID << "|" << setw(20) << buser[i].guestID
					<< "|" << setw(20) << buser[i].checkInDate << "|" << setw(20) << buser[i].checkOutDate << "|" << setw(15) << buser[i].noOfNights << "|" 
					<< setw(15) << buser[i].guestCount << "|" << endl;
				tmpGuest << "\t\t\t\t________________________________________________________________________________________________________________" << endl;
			}

			displayBooking += tmpGuest.str();
		}
		bookingManage.footer = displayBooking;

		switch (bookingManage.prompt())
		{
		case 1:
			cout << "Insert Check-In Date: ";
			getline(cin, checkInDate);
			bookingManage.setValue(0, checkInDate);
			break;
		case 2:
			cout << "Insert Check-Out Date: ";
			getline(cin, checkOutDate);
			bookingManage.setValue(1, checkOutDate);
			break;
		case 3:
			cout << "Insert No of Nights: ";
			cin >> noOfNights;
			bookingManage.setValue(2, to_string(noOfNights));
			break;
		case 4:
			cout << "Insert Guest Count: ";
			cin >> guestCount;
			bookingManage.setValue(3, to_string(guestCount));
			break;
		case 5:
			ascending = !ascending;
			break;
		case 6:
			buser = booking::findBooking(guestID, checkInDate, checkOutDate, noOfNights, guestCount, ascending);
			displayBooking = "";
			break;
		case 7:
			adminhome(admins);
		}
	}
}

//ADMIN GUEST MANAGE
void guestManage(admin admins)
{
	vector<guest> user;
	guest selGuest;
	string displayGuest = "";

	int guestID = 0;
	string guestFirstName = "", guestLastName = "", guestEmail = "", guestPhoneNo = "";
	bool ascending = true;
	
	Menu guestManage;
	guestManage.header = "\n\n\t\t\t\t\t------ GUEST MANAGE -------\n\n\t\t\t\t\tSearch for guest: ";
	guestManage.addOption("First Name");
	guestManage.addOption("Last Name");
	guestManage.addOption("Email");
	guestManage.addOption("Phone No");
	guestManage.addOption("Ordering");
	guestManage.addOption("View");
	guestManage.addOption("Back to profile");
	guestManage.footer = "\n\t\t\t\t\t--------------\n\t\t\t\t\tSelect Option\n";

	while (1) 
	{
		if (ascending) {
			guestManage.setValue(4, "Ascending");
		}
		else {
			guestManage.setValue(4, "Descending");
		}

		if (displayGuest == "") {
			displayGuest = "\n\t\t\t\tSearch Result:\n";
			stringstream tmpGuest;
			tmpGuest << setw(4) << "\t\t\t\tGuest ID" << "|" << setw(20) << "First Name"
				<< "|" << setw(20) << "Last Name" << "|" << setw(25) << "Email" << "|" << setw(20) << "Phone No" << "|" << endl;
			tmpGuest << "\t\t\t\t--------------------------------------------------------------------------------------------------" << endl;


			for (int i = 0; i < user.size(); i++) {
				tmpGuest << "\t\t\t\t" << setw(8) << user[i].guestID << "|" << setw(20) << user[i].firstName
					<< "|" << setw(20) << user[i].lastName << "|" << setw(25) << user[i].email << "|" << setw(20) << user[i].phoneNo << "|" << endl;
				tmpGuest << "\t\t\t\t__________________________________________________________________________________________________" << endl;
			}

			displayGuest += tmpGuest.str();
		}
		guestManage.footer = displayGuest;


		switch (guestManage.prompt())
		{
		case 1:
			cout << "Insert Guest First Name: ";
			getline(cin, guestFirstName);
			guestManage.setValue(0, guestFirstName);
			break;
		case 2:
			cout << "Insert Guest Last Name: ";
			getline(cin, guestLastName);
			guestManage.setValue(1, guestLastName);
			break;
		case 3:
			cout << "Insert Guest Email: ";
			getline(cin, guestEmail);
			guestManage.setValue(2, guestEmail);
			break;
		case 4:
			cout << "Insert Guest PhoneNo: ";
			getline(cin, guestPhoneNo);
			guestManage.setValue(3, guestPhoneNo);
			break;
		case 5:
			ascending = !ascending;
			break;
		case 6:
			user = guest::findGuest(guestFirstName, guestLastName, guestEmail, guestPhoneNo, ascending);
		    displayGuest = "";
		    break;
		case 7:
			adminhome(admins); 
	    }
	}
}

//ADMIN VEIW SALE REPORT
void SaleReportMenu(admin admins) {
	
	string start, endDate;

	vector<int> categoryIds;

	bool sortByDate = true, ascending = true;

	Menu saleMenu;
	saleMenu.addOption("Press 1 to enter Start Date");
	saleMenu.addOption("Press 2 to enter End Date");
	//saleMenu.addOption("Sort By");
	saleMenu.setValue(3, "Date");
	saleMenu.addOption("Order");
	saleMenu.setValue(4, "Ascending");
	//saleMenu.addOption("Generate");
	saleMenu.addOption("Back");

	vector<Sale> result; // vector to store the result

	// we declare it like this so that the index matches their id in the database
	string categoryNames[] = { "None","Apparel","Food","Furniture" };

	//declare outside so that we don't unnecesarily declare new variable in each loop iteration
	string selectedCategoryName;
	int tmpSelectedCategory;

	vector<int>::iterator iterator; //iterator is declare using what we are iterating, in this case it is vector of integer

	while (1)
	{
		selectedCategoryName = "";
		if (categoryIds.empty()) {
			selectedCategoryName = "NONE";
		}
		else {
			for (int i = 0; i < categoryIds.size(); i++) {
				selectedCategoryName += categoryNames[categoryIds[i]] + ", ";
			}
		}
		saleMenu.setValue(2, selectedCategoryName);

		// report display
		stringstream ss;
		// construct our report header
		ss << endl << "\n\n\t\t\t\t\t--------------- SALES REPORT -------------- \n" << endl << "\t\t\t\t\t|" << setw(20) << "Date Time" << "|";
		if (!categoryIds.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "\t\t\t\t\tCategory" << "|";
		}
		ss << setw(20) << "Sale" << "|";

		double totalSale = 0;
		// repeat same structure for content of the report
		for (int i = 0; i < result.size(); i++) 
		{
			ss << endl << "|\t\t\t\t\t" << setw(20) << result[i].date.substr(0, 7) << "|";
			if (!categoryIds.empty()) 
			{
				// if category id not empty we add category column
				ss << setw(20) << result[i].categoryName << "|";
			}
			ss << setw(20) << result[i].value << "|";
			totalSale += result[i].value;

		}

		ss << endl << "\t\t\t\t\t|" << setw(20) << "Total Sale" << "|";
		if (!categoryIds.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "" << " ";
		}
		ss << setw(20) << totalSale << "|";

		ss << endl << "\n\t\t\t\t\t-------------- END OF REPORT --------------" << endl;
		saleMenu.header = ss.str();


		switch (saleMenu.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert start date (yyyy-mm-dd): ";
			cin >> start;
			saleMenu.setValue(0, start);
			break;
		case 2:
			cout << "\t\t\t\t\tInsert end date (yyyy-mm-dd): ";
			cin >> endDate;
			saleMenu.setValue(1, endDate);
			break;
		//case 3: //toggle category
		//	tmpSelectedCategory = productCategorySelection();

		//	//find the selcted category id inside our categoryIds vector
		//	iterator = find(categoryIds.begin(), categoryIds.end(), tmpSelectedCategory);

		//	if (iterator == categoryIds.end()) {//if the iterator reaches the end means not found
		//		categoryIds.push_back(tmpSelectedCategory);
		//	}
		//	else {
		//		categoryIds.erase(iterator); //if it exist erase it
		//	}

		//	break;
		case 4:// sort by
			sortByDate = !sortByDate;
			if (sortByDate)
				saleMenu.setValue(3, "Date");
			else
				saleMenu.setValue(3, "Price");
			break;
		case 5:
			ascending = !ascending;
			if (ascending)
				saleMenu.setValue(4, "Ascending");
			else
				saleMenu.setValue(4, "Descending");
			break;
		//case 6:
		//	result.clear();
		//	result = Sale::salesReport(start, endDate, sortByDate, ascending);
		//	break;
		case 6:
			return;
			break;
		}
	}
}

//GUEST PAGE
void guestPage()
{
	guest user;
	Menu guestMenu;
	guestMenu.header = "\n\n\t\t\t\t\t----------- GUEST PAGE -----------\n\n\t\t\t\t\tChoose:";
	guestMenu.addOption("Register");
	guestMenu.addOption("Login");
	guestMenu.addOption("Back to main menu");
	guestMenu.footer = "\n\t\t\t\t\t----------------------------------\n\t\t\t\t\tSelect Option\n";

	while (1) {
		switch (guestMenu.prompt())
		{
		case 1:
			guestRegister();
			break;
		case 2:
			guestLoginMenu();
			break;
		case 3:
			main();
		}
	}
}

//GUEST REGISTER
void guestRegister() {
	guest newacc;

	Menu rgMenu;
	rgMenu.header = "\n\n\t\t\t\t\t-------------- GUEST REGISTRATION --------------\n\n\t\t\t\t\tChoose to insert your information:\n";
	rgMenu.addOption("First Name");
	rgMenu.addOption("Last Name");
	rgMenu.addOption("Username");
	rgMenu.addOption("Email");
	rgMenu.addOption("Password");
	rgMenu.addOption("Phone No");
	rgMenu.addOption("Security Question");
	rgMenu.addOption("Register");
	rgMenu.addOption("Back");
	rgMenu.footer = "\n\t\t\t\t\t-------------------------------------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	bool valid = true;

	while (1) {

		switch (rgMenu.prompt()) {
		case 1:
			cout << "\t\t\t\t\tInsert First Name: ";
			getline(cin, newacc.firstName);
			rgMenu.setValue(0, newacc.firstName);
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Last Name: ";
			getline(cin,  newacc.lastName);
			rgMenu.setValue(1, newacc.lastName);
			break;
		case 3:
			cout << "\t\t\t\t\tInsert Username: ";
			cin >> newacc.username;
			rgMenu.setValue(2, newacc.username);
			break;
		case 4:
			cout << "\t\t\t\t\tInsert Email:";
			cin >> newacc.email;
			rgMenu.setValue(3, newacc.email);
			break;
		case 5:
			cout << "\t\t\t\t\tInsert Password:";
			cin >> tmpinput;
			if (tmpinput.length() < 6) {
				cout << "\n\t\t\t\t\tPassword must be at least 6 character long";
				_getch();
			}
			else {
				newacc.password = tmpinput;
				rgMenu.setValue(4, newacc.password);
			}
			break;
		case 6:
			cout << "\t\t\t\t\tInsert Phone No: ";
			cin >> newacc.phoneNo;
			rgMenu.setValue(5, newacc.phoneNo);
			break;
		case 7:
			cout << "\t\t\t\t\tIn what city were you born?: ";
			getline(cin, newacc.secQuestion);
			rgMenu.setValue(6, newacc.secQuestion);
			break;
		case 8:
			if (newacc.firstName.empty() || newacc.lastName.empty() || newacc.username.empty() || newacc.email.empty() ||
				newacc.password.empty() || newacc.phoneNo.empty() || newacc.secQuestion.empty()) {
				cout << "\n\t\t\t\t\tPlease complete all fields before registering.\n";
				_getch();
				break;  // Repeat the loop to allow the user to enter missing information
			}
			valid = true;
			newacc.insert();
			cout << "\t\t\t\t\tRegistered. Press enter to go back.";
			_getch();
			return;
			break;
		case 9:
			return;
		default:
			break;
		}
	}
}

//GUEST LOGIN
void guestLoginMenu() {
	Menu loginMenu;
	loginMenu.header = "\n\n\t\t\t\t\t------ GUEST LOGIN -------\n\n\t\t\t\t\tChoose:";
	loginMenu.addOption("Enter Username");
	loginMenu.addOption("Enter Password");
	loginMenu.addOption("Continue Login");
	loginMenu.addOption("Forgot Password");
	loginMenu.addOption("Back to Guest Page");
	loginMenu.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	guest user;
	booking buser;
	review reviews;

	while (1) {
		switch (loginMenu.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username:";
			cin >> user.username;
			loginMenu.setValue(0, user.username);
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Password:";
			cin >> user.password;
			loginMenu.setValue(1, user.password);
			break;
		case 3:
			if (user.login()) {
				guestHome(user, buser, reviews);
			}
			else {
				cout << "\t\t\t\t\tInvalid Login";
				_getch();
			}
			break;
		case 4:
			guestForgotPassword(user, buser, reviews);
		case 5:
			guestPage();
			break;
		}
	}
}

//GUEST FORGOT PASSWORD
void guestForgotPassword(guest user, booking buser, review reviews)
{
	//guest user;
	//booking buser;
	//review reviews;// copy the object
	Menu forgotPassword;
	forgotPassword.header = "\n\n\t\t\t\t\t------ FORGOT PASSWORD -------\n\n\t\t\t\t\tChoose:";
	forgotPassword.addOption("Enter username");
	forgotPassword.addOption("Enter Answer for Security Question ");
	forgotPassword.addOption("Continue");
	forgotPassword.addOption("Back to Guest Page");
	forgotPassword.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	bool valid = true;

	while (1) {
		switch (forgotPassword.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username:";
			cin >> user.username;
			forgotPassword.setValue(0, user.username);
			break;
		case 2:
			cout << "\t\t\t\t\tWhat is your mother's name?:";
			cin >> user.secQuestion;
			forgotPassword.setValue(1, user.secQuestion);
			break;
		case 3:
			if (user.forgotPassword()) {
				guestResetPassword(user, buser, reviews);
			}
			else {
				cout << "\t\t\t\t\tInvalid username or answer!";
				_getch();
			}
			break;
		case 4:
			guestLoginMenu();
			break;
		}
	}
}

//GUEST RESET PASSWORD
bool guestResetPassword(guest user, booking buser, review reviews)
{
	/*booking buser;
	review reviews;*/
	guest temp = user; // copy the object
	guest resetPassword;
	Menu newPassword;
	newPassword.header = "\n\n\t\t\t\t\t------ RESET PASSWORD -------\n\n\t\t\t\t\tChoose:";
	newPassword.addOption("Enter New Password");
	newPassword.addOption("Confirm Password");
	newPassword.addOption("Continue");
	newPassword.addOption("Back to Login Menu");
	newPassword.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	while (1) {
		newPassword.setValue(0, temp.password);
		newPassword.setValue(1, temp.newPassword);
		//newPassword.footer = "\n----------------------------\nSelect Option \n";

		switch (newPassword.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert new password:";
			cin >> tmpinput;
			if (tmpinput.length() < 6) {
				cout << "\n\t\t\t\t\tPassword must be at least 6 character long";
				_getch();
			}
			else {
				resetPassword.password = tmpinput;
				newPassword.setValue(0, resetPassword.password);
			}
			break;
		case 2:
			cout << "\t\t\t\t\tConfirm new password:";
			cin >> tmpinput;
			if (tmpinput == resetPassword.password)
			{
				cout << "\t\t\t\t\tNew Password Updated!";
			}
			else
			{
				cout << "\t\t\t\t\tPassword did not match. Try again";
				_getch();
			}
			break;
		case 3:
			if (user.login()) {
				guestHome(user, buser, reviews);
				
			}
			else {
				cout << "\t\t\t\t\tInvalid Login";
				_getch();
			}
			break;
		}
	}
}

//GUEST HOME
void guestHome(guest user, booking buser, review reviews) {

	Menu homeMenu;
	homeMenu.header = "\n\t\t\t\t\t--------- GUEST MENU ---------\n\n\t\t\t\t\t ------- Welcome " + user.username + " -------\n\n\t\t\t\t\tChoose:";

	homeMenu.addOption("Profile");
	homeMenu.addOption("Homestay Booking");
	homeMenu.addOption("Review Page");
	homeMenu.addOption("Logout");
	homeMenu.footer = "\n\t\t\t\t\t----------------------\n\t\t\t\t\tSelect Option\n";

	while (1) {
		//homeMenu.header = "\n\t\t\t\t\t--------- GUEST MENU ---------\n\n\t\t\t\t\t ------- Welcome " + user.username + " -------\n\n\t\t\t\t\tChoose:";
		switch (homeMenu.prompt())
		{
		case 1:
			user = profile(user);
			break;
		case 2:
			book(user, buser, reviews);
			break;
		case 3:
			reviewPage(user, reviews);
			break;
		case 4:
			guestLoginMenu();
			return;
			break;
		default:
			break;
		}
	}
}

//GUEST PROFILE
guest profile(guest user) {

	guest temp = user; // copy the object

	Menu profileMenu;
	profileMenu.header = "\t\t\t\t\t------------ GUEST PROFILE -------------\n\n\t\t\t\t\tChoose to edit your information:";
	profileMenu.addOption("First Name");
	profileMenu.addOption("Last Name");
	profileMenu.addOption("Press 1 to edit Username");
	profileMenu.addOption("Press 2 to edit Email");
	profileMenu.addOption("Press 3 to edit Password");
	profileMenu.addOption("Press 4 to edit Phone No");
	profileMenu.addOption("Press 5 to edit Security Question Answer");
	profileMenu.addOption("Press 6 to Reset");
	profileMenu.addOption("Press 7 to Save");
	profileMenu.addOption("Press 8 to Back");
	profileMenu.addOption("Press 9 to Delete Account");

	string tmpInput;
	while (1) {
		profileMenu.setValue(0, temp.firstName);
		profileMenu.setValue(1, temp.lastName);
		profileMenu.setValue(2, temp.username);
		profileMenu.setValue(3, temp.email);
		profileMenu.setValue(4, temp.password);
		profileMenu.setValue(5, temp.phoneNo);
		profileMenu.setValue(6, temp.secQuestion);

		profileMenu.footer = "\n\t\t\t\t\t----------------------------\n\t\t\t\t\tSelect Option \n";

		switch (profileMenu.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Username:";
			cin >> temp.username;
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Email:";
			cin >> temp.email;
			break;
		case 3:
			cout << "\t\t\t\t\tInsert Password:";
			cin >> temp.password;
			break;
		case 4:
			cout << "\t\t\t\t\tInsert Phone No: ";
			cin >> temp.phoneNo;
			break;
		case 5:
			cout << "\t\t\t\t\tInsert Answer for Security Question: \n\t\t\t\t\tIn what city were you born?: ";
			cin >> temp.secQuestion;
			break;
		case 6:
			temp = user;
			break;
		case 7:
			user = temp;
			user.update();
			cout << "\t\t\t\t\tUpdated";
			_getch();
		case 8:
			return user;
			break;
		case 9:
			cout << "\t\t\t\t\tDelete your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				user = temp;
				user.remove();
				main();
			}
			break;
		default:
			break;
		}
	}
}

//BOOK
void book(guest user, booking buser, review reviews) {

	Menu bookMenu;

	bookMenu.header = "\t\t\t\t\t----------- HOMESTAY MENU -----------\n\n\t\t\t\t\tChoose:";
	bookMenu.addOption("Homestay Accommodation Details");
	bookMenu.addOption("Booking");
	bookMenu.addOption("View Bookings");
	bookMenu.addOption("Admin Contact Information");
	bookMenu.addOption("Back");
	bookMenu.footer = "\n\t\t\t\t\t--------------------------------\n\t\t\t\t\tSelect Option\n";

	while (1) {
		switch (bookMenu.prompt())
		{
		case 1:
			homestayDetails(user, buser, reviews);
		case 2:
			bookingMenu(user, buser, reviews); //
		case 3:
			viewBooking(buser);
		case 4:
			contact(user, buser, reviews);
		case 5:
			guestHome(user, buser, reviews);
		}
	}
}

//HOMESTAY DETAILS
void homestayDetails(guest user, booking buser, review reviews)
{
	/*guest user;
	booking buser*/;
	Menu homestayMenu;
	//Menu details;

	homestayMenu.header = "\t\t\t\t\t----------- HOMESTAY DETAILS -----------\n\n\t\t\t\t\t2 STORY BUNGALOW\n\n\t\t\t\t\tPrice: RM 580 per night\n\t\t\t\t\t * tax and charges is included\n"
		"\n\t\t\t\t\t- 4 Bedrooms\n\n\t\t\t\t\t Master bedroom with balcony:\n\t\t\t\t\t- 1 King bed\n\t\t\t\t\t- Toilet with bath tub\n\t\t\t\t\t - Air-conditioning\n\t\t\t\t\t- Wardrobe\n\t\t\t\t\t"
		"\n\t\t\t\t\t3 Bedrooms:\n\t\t\t\t\t- 1 Queen bed\n\t\t\t\t\t- Wardrobes\n\t\t\t\t\t- Air-conditioning\n\n\t\t\t\t\t- 3 Toilets\n\t\t\t\t\t- Kitchen\n\t\t\t\t\t- Washer\n\t\t\t\t\t- Living room with sofa\n\t\t\t\t\t"
		"- Dining table\n\t\t\t\t\t- Parking\n\t\t\t\t\t- Free Wi-Fi\n\t\t\t\t\t- Tv\n\t\t\t\t\t- Swimming pool\n\n\t\t\t\t\t*Pets are not allowed.\n\n\t\t\t\t\tChoose:";


	homestayMenu.addOption("Back");
	homestayMenu.addOption("Exit");
	homestayMenu.footer = "\n\t\t\t\t\t--------------------------------\n\t\t\t\t\tSelect Option\n";
	
	while (1) {

		switch (homestayMenu.prompt())
		{
		case 1:
			book(user, buser, reviews);
		case 2:
			exit(0);
		}
	}
}

//BOOKING PROCESS
void bookingMenu(guest user, booking buser, review reviews)
{
	booking temp = buser;
	temp.guestID = user.guestID;
	Menu makeBooking;
	string tmpInput;

	makeBooking.header = "\t\t\t\t\t----------- HOMESTAY BOOKING -----------\n\n\t\t\t\t\tPrice per night: RM750\n\t\t\t\t\tChoose:";
	makeBooking.addOption("Check-In Date");
	makeBooking.addOption("Check-Out Date");
	makeBooking.addOption("Number of night(s)");
	makeBooking.addOption("Guest Count");
	makeBooking.addOption("Continue Payment");
	makeBooking.addOption("Back to Book Menu");
	makeBooking.addOption("Exit");
	makeBooking.footer = "\n\t\t\t\t\t--------------------------------\n\t\t\t\t\tSelect Option\n";

	bool valid = true;
	string tmpinput;

	while (1) {
		switch (makeBooking.prompt())
		{
		case 1:
			while (true) {
				cout << "\t\t\t\t\tEnter Check-In Date (YYYY-MM-DD):";
				cin.ignore();
				getline(cin, temp.checkInDate);

				if (validateDate(temp.checkInDate)) {
					break;
				}
				else {
					cout << "\n\t\t\t\t\tInvalid date format. Please use YYYY-MM-DD.\n";
				}
			}
			makeBooking.setValue(0, temp.checkInDate);
			break;
		case 2:
			while (true) 
			{
				cout << "\t\t\t\t\tEnter Check-Out Date (YYYY-MM-DD):";
				getline(cin, temp.checkOutDate);

				if (validateDate(temp.checkOutDate)) {
					break;
				}
				else {
					cout << "\n\t\t\t\t\tInvalid date format. Please use YYYY-MM-DD.\n";
				}
			}
			makeBooking.setValue(1, temp.checkOutDate);
			break;
		case 3:
			cout << "\t\t\t\t\tInsert No of night(s): ";
			cin >> temp.noOfNights;
			makeBooking.setValue(2, to_string(temp.noOfNights));
			break;
		case 4:

			while (true) {
				cout << "\t\t\t\t\tInsert No of Guest: ";
				cin >> temp.guestCount;

				if (temp.guestCount > 20)
				{
					cout << endl << "\t\t\t\t\tNumber of guest cannot be more than 20." << endl
						<< "\t\t\t\t\tPress enter to try again or press 0 to cancel booking.\n";

					while (!_kbhit()) {
						// Wait for a key to be pressed
					}

					char userInput = _getch();

					if (userInput == '0') {
						cout << "\t\t\t\t\tBooking canceled.";
						guestHome(user, buser, reviews);
						return;
					}
				}
				else
				{
					makeBooking.setValue(3, to_string(temp.guestCount));
					break;
				}
			}
			break;
		case 5:

			if (temp.checkInDate.empty() || temp.checkOutDate.empty() || temp.noOfNights <= 0 || temp.guestCount <= 0) 
			{
				cout << "\t\t\t\t\tPlease complete all the information before proceeding to payment.\n";
				_getch();
				break;  // Repeat the loop to allow the user to enter missing information
			}

			temp.totalPayment = temp.noOfNights * 750;
			cout << "\t\t\t\t\tYour total payment is RM " << temp.totalPayment <<
				"\n\t\t\t\t\tDo you want to continue make payment? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y')
			{
				temp = temp;
				temp.insertBooking();
				cout << "\n\t\t\t\t\tYour payment is successful !";
				cout << "\n\t\t\t\t\tPress Enter to continue...";  // Prompt for Enter key
			}
			else
			{
				cout << "Payment Cancelled.";
			}
			_getch();
			guestHome(user, buser, reviews);
			break;
		case 6:
			book(user, buser, reviews);
			break;
		case 7:
			exit(0);
		}
	}
}

//double calculateNumNights(const string& checkInDate, const string& checkOutDate) {
//	tm checkInStruct, checkOutStruct;
//	strptime(checkInDate.c_str(), "%Y-%m-%d", &checkInStruct);
//	strptime(checkOutDate.c_str(), "%Y-%m-%d", &checkOutStruct);
//
//	time_t checkInTime = mktime(&checkInStruct);
//	time_t checkOutTime = mktime(&checkOutStruct);
//
//	// Ensure check-out time is later than check-in time
//	if (checkOutTime <= checkInTime) {
//		return 0;  // Invalid date range
//	}
//
//	// Calculate difference in seconds and convert to days
//	double numNights = difftime(checkOutTime, checkInTime) / (60 * 60 * 24);
//	return numNights;
//}

//VIEW BOOKING
booking viewBooking(booking buser) //refer demo shop
{
	booking temp = buser;

	/*booking bookings;
	bookings.guestID = user.guestID;*/

	Menu bookingList;
	bookingList.header = "\t\t\t\t\t----------- BOOKING DETAILS -----------\n\n\t\t\t\t\tChoose:";
	bookingList.footer = "\n\t\t\t\t\tSelect Option";
	bookingList.addOption("Press 1 to edit check-in date");
	bookingList.addOption("Press 2 to edit check-out date");
	bookingList.addOption("Press 3 to edit guest count");
	bookingList.addOption("Save");
	bookingList.addOption("Back");
	bookingList.addOption("Delete booking");

	string tmpInput;
	while (1)
	{
		bookingList.setValue(0, temp.checkInDate);
		bookingList.setValue(1, temp.checkOutDate);
		bookingList.setValue(2, to_string(temp.guestCount));

		switch (bookingList.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tInsert Check-In Date:";
			cin >> temp.checkInDate;
			break;
		case 2:
			cout << "\t\t\t\t\tInsert Check-Out Date:";
			cin >> temp.checkOutDate;
			break;
		case 3:
			cout << "\t\t\t\t\tInsert guest Count:";
			cin >> tmpInput;
			if (isNumeric(tmpInput))
			{
				temp.guestCount = stoi(tmpInput);
			}
			else
			{
				cout << "Input for guest count must be numeric";
				_getch();
			}
			break;
		case 4:
			temp = buser;
			break;
		case 5:
			buser = temp;
			buser.updateBooking();
			cout << "\t\t\t\t\tUpdated.";
			_getch();
		case 6:
			return buser;
			break;
		case 7:
			cout << "\t\t\t\t\tDelete your booking? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				buser = temp;
				buser.removeBooking();
				main();
			}
			break;
		default:
			break;
		}
	}
}

//ADMIN CONTACT DETAILS
void contact(guest user, booking buser, review reviews)
{
	Menu adminContact;

	adminContact.header = "\t\t\t\t\t---------- ADMIN CONTACT INFORMATION ----------\n\n"
		"\t\t\t\t\t WhatsApp: 0196431714\n\n\t\t\t\t\t Call: 03-8456257\n\n\t\t\t\t\t Email:aaleya.aisya90@gmail.com\n";
	adminContact.addOption("Back");
	adminContact.addOption("Exit");
	adminContact.footer = "\n\n\t\t\t\t\t-----------------------------------------------\n\t\t\t\t\tSelect Option";

	while (1)
	{
		switch (adminContact.prompt())
		{
		case 1:
			book(user, buser, reviews);
			break;
		case 2:
			exit(0);
		}
	}
}

//REVIEW PAGE
void reviewPage(guest user, review reviews)
{
	review temp = reviews;
	Menu reviewMenu;

	reviewMenu.header = "\t\t\t\t\t------- REVIEW MENU -------\n\n\t\t\t\t\tChoose:";
	reviewMenu.addOption("Make a Review");
	reviewMenu.addOption("Homestay Reviews");
	//reviewMenu.addOption("My Reviews");
	reviewMenu.addOption("Back");
	reviewMenu.footer = "\n\t\t\t\t\t--------------------\n\t\t\t\t\tSelect Option\n";

	while (1) {
		
		switch (reviewMenu.prompt())
		{
		case 1:
			writeReview(user, reviews);
			break;
		/*case 2:
			homestayreviews();*/
		/*case 3:
			myreviews();*/
		case 3:
			return;
			break;
		}
	}
}

//WRITE REVIEW
void writeReview(guest user, review reviews)
{
	review temp = reviews;
	temp.guestID = user.guestID;
	Menu writeReview;

	writeReview.header = "\n\n\t\t\t\t\t---------- REVIEW ----------\n\n\t\t\t\t\tChoose Option";
	writeReview.addOption("Write review");
	writeReview.addOption("Enter rating");
	writeReview.addOption("Save My Review");
	writeReview.addOption("Back");
	writeReview.footer = "\n\t\t\t\t\t-------------------------------\n\t\t\t\t\tSelect Option\n";

	string tmpinput;
	bool valid = true;

	while (1) {
		switch (writeReview.prompt())
		{
		case 1:
			cout << "\t\t\t\t\tEnter your comment:";
			getline(cin, temp.comment);
			writeReview.setValue(0, temp.comment);
			break;
		case 2:
			cout << "\t\t\t\t\tInsert rating (1 to 5):";
			cin >> tmpinput;
			if (tmpinput.length() == 1 && isNumeric(tmpinput))
			{
				temp.rating = stoi(tmpinput);
				if (temp.rating >= 1 && temp.rating <= 5) {
					temp.rating = stoi(tmpinput);
					writeReview.setValue(1, to_string(temp.rating));
					break;
				}
			}
			else
			{
				cout << "Input for rating must be number between 1 to 5";
				_getch();
			}
			break;
		case 3:
			reviews = temp;
			reviews.insertReview();
			cout << "\t\t\t\t\tYour review is succesfully submitted!";
			_getch();
			break;
		case 4:
			return;
			break;
		}
	}
}

bool isNumeric(string input) {
	for (int i = 0; i < input.length(); i++) {
		// loop through the string and if the character at index is not digit return false
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	// if loop finishes means all is digit so return true
	return true;
}

bool validateDate(const std::string& date) {
	// Define a regex pattern for YYYY-MM-DD format
	std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");

	// Check if the date matches the format
	return std::regex_match(date, dateRegex);
}


