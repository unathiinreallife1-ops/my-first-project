//=================================================================================================
// Program: VukaFit Campus wellness centre 
// Membership Quotation - Question 1
//================================================================================================

// Design pseudocode:
// 1. Capture student number and name
// 2. display memebership menu and capure selection
// 3. validate selection (1-3), else error and stop
// 4.  Capture number of months, validate (1-6), else error and stop
// 5. Capture fitness assessment choice(Y/N), validate, else error and stop
// 6. Determine mouthly fee using switch
// 7. Subtotal = fee x months
// 8. Discount % = 6 months = 12% , 3-5 months = 7%, otherwise 0%
// 9.Discount = subtotal x percentage
// 10. Assessment fee = R180 if Y, otherwise R0
// 11. Final = subtotal - discount + assessment 
// 12. Desplay detailed quotation
// =================================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

int main()
{
	//Components
	const double BASIC_FEE = 220.00;
	const double PLUS_FEE = 350.00;
	const double COMPLETE_FEE = 480.00;
	const double ASSESSMENT_FEE = 180.00;
	const double DISCOUNT_3_TO_5 = 0.07;
	const double DISCOUNT_6 = 0.12;
	const int MIN_MONTHS = 1;
	const int MAX_MOUTHS = 6;

	// variables
	string studentNumber, studentName, membershipName;
	int membershipCode = 0;
	int months = 0;
	char assessmentChoice = 'N';
	double monthlyFee = 0.0, subtotal = 0.0, discountRate = 0.0;
	double discountAmount = 0.0, assessmentCharge = 0.0, finalAmount = 0.0;

	cout << fixed << setprecision(2);

	// Step 1: Student Details
	cout << "Student namber: ";
	getline(cin, studentNumber);
	cout << "Student name: ";
	getline(cin, studentName);

	// Step 2: Menu and selection 
	cout << "\n1. Basic Access - R" << BASIC_FEE << endl;
	cout << "2. Active Plus -R" << PLUS_FEE << endl;
	cout << "3. Complete Wellness - R" << COMPLETE_FEE << endl;
	cout << "Select membership: ";
	if (!(cin >> membershipCode) || membershipCode < 1 || membershipCode > 3)
	{
		cout << "Error: Invalid Membership code. Please enter 1, 2 or 3. Quotatuon cancelled" << endl;
		return 1;
	}
	// step 3 Months
	cout << "Number of months (" << MIN_MONTHS << "-" << MAX_MOUTHS << "):";
	if (!(cin >> months) || months < MIN_MONTHS || months > MAX_MOUTHS)
	{
		cout << "Error: Invalid number of months. Please enter a number between " << MIN_MONTHS << " and " << MAX_MOUTHS << ". Quotation cancelled." << endl;
		return 1;
	}

	// step 4 : Fitness Assessment
	cout << " Add Fitness Assessment? (Y/N): ";
	cin >> assessmentChoice;
	assessmentChoice = static_cast<char>(toupper(static_cast<unsigned char>(assessmentChoice)));
	if (assessmentChoice != 'Y' && assessmentChoice != 'N')
	{
		cout << "Error: Invalid choice. Please enter Y or N. Quotation cancelled." << endl;
		return 1;
	}

	// step 5 : Determine monthly fee
	switch (membershipCode)
	{
	case 1:
		membershipName = "Basic Access"; monthlyFee = BASIC_FEE;
		break;
	case 2:
		membershipName = "Active Plus"; monthlyFee = PLUS_FEE;
		break;
	case 3:
		membershipName = "Complete Wellness"; monthlyFee = COMPLETE_FEE;
		break;
	}
	// step 6: Calculations
	subtotal = monthlyFee * months;

	if (months == 6)
	{
		discountRate = DISCOUNT_6;
	}
	else if (months >= 3 && months <= 5)
	{
		discountRate = DISCOUNT_3_TO_5;
	}
	else
	{
		discountRate = 0.0;
	}
	discountAmount = subtotal * discountRate;

	if (assessmentChoice == 'Y')
	{
		assessmentCharge = ASSESSMENT_FEE;
	}
	else
	{
		assessmentCharge = 0.0;
	}
	finalAmount = subtotal - discountAmount + assessmentCharge;

	// Step 7: Output
	cout << "\n========VUKAFIT MEMBERSHIP QUOTATION========" << endl;
	cout << left << setw(16) << "Student" << ": " << studentNumber << " - " << studentName << endl;
	cout << left << setw(16) << "Membership" << ": " << membershipName << endl;
	cout << left << setw(16) << "Months" << ": " << months << endl;
	cout << left << setw(16) << "Monthly Fee" << ": R" << monthlyFee << endl;
	cout << left << setw(16) << "Subtotal" << ": R" << subtotal << endl;
	cout << left << setw(16) << "Discount" << ": R" << discountAmount << endl;
	cout << left << setw(16) << "Discount Rate" << ": " << discountRate * 100 << "%" << endl;
	cout << left << setw(16) << "Assessment Charge" << ": R" << assessmentCharge << endl;
	cout << left << setw(16) << "Final Amount" << ": R" << finalAmount << endl;
	cout << "=============================================" << endl;
	return 0;
}

//=================================================================================================
// End of Program, Quotation for VukaFit Campus wellness centre - Question 1
//=================================================================================================





# 