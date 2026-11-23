//=================================================================================================
// VukaFit Campus wellness centre - Question 2
// Group Booking Calculator
//=================================================================================================
// Design 
// main():
// 1. Capture booking reference
// 2. displaySessionMenu() capture session code
// 3. Get session rate > rate (0 means invalid code) > stop if invalid
// 4. capture participants, validParticipants() > stop if invalid
// 5. Capture Saturday booking (Y/N) > validSaturday() > stop if invalid
// 6. subtotal = calculateSubtotal(rate, participants)
// 7. discount = calculateDiscount(participants, subtotal)
// 8. afterDisc = subtotal - discount
// 9. surcharge = calculateWeekendSurcharge (afterDisc, saturday
// 10. finalAmount = afterDisc + surcharge
// 11. displayBookingSummary(...) (also show cost per participant)
//=================================================================================================

#include <iostream>
#include <iomanip>
#include <string> 
#include <limits>
using namespace std;

// Global Constants
const int MIN_PARTICIPANTS = 1;
const int MAX_PARTICIPANTS = 12;
const int GROUP_DISCOUNT_MIN = 8;
const double GROUP_DISCOUNT_RATE = 0.10;
const double SATURDAY_SURCHARGE_RATE = 0.15;

// Function Prototypes
void displaySessionMenu();
double getSessionRate(int sessionCode);
string getSessionName(int sessionCode);
bool validParticipants(int participants);
double calculateSubtotal(double rate, int participants);
double calculateDiscount(int participants, double subtotal);
double calculateWeekendSurcharge(double afterDiscount, char saturday);
void displayBookingSummary(string bookingRef, string sessionName, int participants, double subtotal, double discount, double surcharge, double finalAmount);

// main(): capture input, call functions,coordinate solutions
int main()
{
	string bookingRef;
	int sessionCode = 0;
	int perticipants = 0;
	char saturday = 'N';
	double rate, subtotal, discount, afterDiscount, surcharge, finalAmount;

	// Capture booking reference
	cout << "Booking reference: ";
	getline(cin, bookingRef);

	// Session Selection and validation
	displaySessionMenu();
	cout << "Select session code: ";
	if (!(cin >> sessionCode)) {
		cout << "Error: Session code must be a number (1-3). Booking cancelled," << endl;
		return 1;
	}
	rate = getSessionRate(sessionCode);
	if (rate == 0.0) {
		cout << "Error: Invalid session code. Please enter 1, 2, or 3. Booking cancelled." << endl;
		return 1;
	}

	// Participants validation
	cout << "Participants (" << MIN_PARTICIPANTS << "-" << MAX_PARTICIPANTS << "): ";
	if (!(cin >> perticipants) || !validParticipants(perticipants)) {
		cout << "Error: Invalid number of participants. Please enter a number between 1 to 12. Booking " << endl;
		return 1;
	}

	//Saturday booking validation
	cout << "Saturday booking (Y/N): ";
	cin >> saturday;
	saturday = static_cast<char>(toupper(static_cast<unsigned char>(saturday)));
	if (saturday != 'Y' && saturday != 'N') {
		cout << "Error: Invalid input. Please enter Y or N. Booking cancelled." << endl;
		return 1;
	}


	// Calculate subtotal, discount, after discount, surcharge, final amount
	subtotal = calculateSubtotal(rate, perticipants);
	discount = calculateDiscount(perticipants, subtotal);
	afterDiscount = subtotal - discount;
	surcharge = calculateWeekendSurcharge(afterDiscount, saturday);
	finalAmount = afterDiscount + surcharge;

	// Output booking summary
	displayBookingSummary(bookingRef, getSessionName(sessionCode), perticipants, subtotal, discount, surcharge, finalAmount);

	return 0;

}

//============================================================
// Function definitions
// ============================================================

// Displays the session menu with prices per participant
void displaySessionMenu()
{
	cout << fixed << setprecision(0);
	cout << "\n1. Yoga Fundamentals - R" << getSessionRate(1) << endl;
	cout << "2. Strength Circuit  - R" << getSessionRate(2) << endl;
	cout << "3. Stress Management - R" << getSessionRate(3) << endl;
}

// Returns the price per participant for a session code, or 0 if invalid
double getSessionRate(int sessionCode)
{
	switch (sessionCode)
	{
	case 1:  return 75.00;
	case 2:  return 110.00;
	case 3:  return 90.00;
	default: return 0.0;
	}
}

// Returns the session name for a session code (used by the summary)
string getSessionName(int sessionCode)
{
	switch (sessionCode)
	{
	case 1:  return "Yoga Fundamentals";
	case 2:  return "Strength Circuit";
	case 3:  return "Stress Management";
	default: return "Unknown";
	}
}

// Returns true if participants is between 1 and 12 inclusive
bool validParticipants(int participants)
{
	return (participants >= MIN_PARTICIPANTS && participants <= MAX_PARTICIPANTS);
}

// Subtotal = rate x participants
double calculateSubtotal(double rate, int participants)
{
	return rate * participants;
}

// 10% group discount for 8 or more participants, otherwise 0
double calculateDiscount(double subtotal, int participants)
{
	if (participants >= GROUP_DISCOUNT_MIN)
		return subtotal * GROUP_DISCOUNT_RATE;
	return 0.0;
}

// 15% surcharge on the amount AFTER discount if the booking is on a Saturday
double calculateWeekendSurcharge(double amountAfterDiscount, char saturday)
{
	if (saturday == 'Y')
		return amountAfterDiscount * WEEKEND_SURCHARGE_RATE;
	return 0.0;
}

// Displays the detailed booking summary, including cost per participant
void displayBookingSummary(string bookingRef, string sessionName,
	int participants, double subtotal,
	double discount, double surcharge,
	double finalTotal)
{
	double costPerParticipant = finalTotal / participants;

	cout << fixed << setprecision(2);
	cout << "\n========== VUKAFIT BOOKING SUMMARY ==========" << endl;
	cout << left << setw(22) << "Booking Ref" << ": " << bookingRef << endl;
	cout << left << setw(22) << "Session" << ": " << sessionName << endl;
	cout << left << setw(22) << "Participants" << ": " << participants << endl;
	cout << left << setw(22) << "Subtotal" << ": R" << subtotal << endl;
	cout << left << setw(22) << "Group Discount" << ": R" << discount << endl;
	cout << left << setw(22) << "Weekend Surcharge" << ": R" << surcharge << endl;
	cout << left << setw(22) << "Final Total" << ": R" << finalTotal << endl;
	cout << left << setw(22) << "Cost per Participant" << ": R" << costPerParticipant << endl;
	cout << "=============================================" << endl;
}
