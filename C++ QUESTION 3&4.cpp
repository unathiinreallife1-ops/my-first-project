// ============================================================
// VukaFit Campus Wellness Centre - Questions 3 and 4
// Q3: Daily Check-in Processor (repetition + validation)
// Q4: Weekly Attendance Analytics (1D and 2D arrays)
// Both questions are in this one file. main() shows a menu so
// each question compiles and runs independently of the other.
// ============================================================
// Design  - Question 3:
//   counters = 0; attempts = 0
//   DO
//     attempts++
//     capture student number, activity code, duration
//     IF activity invalid OR duration outside 15-180
//         show INVALID CHECK-IN message, invalid++
//     ELSE
//         classify SHORT (15-44) / STANDARD (45-89) / EXTENDED (90-180)
//         IF duration >= 120 show LONG SESSION CHECK
//         update valid, category, activity counters and total minutes
//     IF attempts < 10 ask "continue (Y/N)?"
//   WHILE attempts < 10 AND operator chose Y
//   average = (valid > 0) ? totalMinutes / valid : 0    
//   display end-of-day summary
// 
//=====================================================================
// Design (pseudocode) - Question 4:
//   declare programmes[3], days[5], attendance[3][5] and populate
//   nested loops: display report, programme totals/averages, highest day
//   per programme, HIGH DEMAND flags (>= 40) and count
//   loop over days: weekday totals -> busiest weekday
//   find programme with highest weekly total
//   grand total and overall average from the array
// ====================================================================================--

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// Global constants (read-only) 
const int MAX_CHECKINS = 10;
const int MIN_DURATION = 15;
const int MAX_DURATION = 180;
const int SHORT_MAX = 44;    
const int STANDARD_MAX = 89;    
const int LONG_SESSION_MIN = 120;   
const int NOT_A_NUMBER = -1;    

const int PROGRAMMES = 3;
const int WEEKDAYS = 5;
const int HIGH_DEMAND_LIMIT = 40;

// Function prototypye
int  readInteger();
char readYesNo(const string& prompt);
void runQuestion3();
void displayCheckinSummary(int valid, int invalid, int shortV, int standardV,
    int extendedV, int gym, int group, int consult,
    int totalMinutes, double average);
void runQuestion4();
string demandCell(int value);


// main()

int main()
{
    int choice = -1;

    do
    {
        cout << "\n=========== VUKAFIT PROGRAMME MENU ===========" << endl;
        cout << "1. Question 3 - Daily Check-in Processor" << endl;
        cout << "2. Question 4 - Weekly Attendance Analytics" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        choice = readInteger();

        switch (choice)
        {
        case 1:  runQuestion3(); break;
        case 2:  runQuestion4(); break;
        case 0:  cout << "Goodbye." << endl; break;
        default: cout << "Invalid choice. Please enter 1, 2 or 0." << endl;
        }
    } while (choice != 0 && !cin.eof());

    return 0;
}


int readInteger()
{
    string line;
    getline(cin, line);

    stringstream ss(line);
    int value;
    char extra;
    if (!(ss >> value) || (ss >> extra))
        return NOT_A_NUMBER;
    return value;
}


char readYesNo(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
            return 'N';                      
        if (line.size() == 1)
        {
            char c = static_cast<char>(toupper(static_cast<unsigned char>(line[0])));
            if (c == 'Y' || c == 'N')
                return c;
        }
        cout << "Please enter Y or N." << endl;
    }
}

// ============================================================
// QUESTION 3
// ============================================================
void runQuestion3()
{
    // ---------- Counters and accumulators ----------
    int attempts = 0, validCount = 0, invalidCount = 0;
    int shortVisits = 0, standardVisits = 0, extendedVisits = 0;
    int gymVisits = 0, groupVisits = 0, consultVisits = 0;
    int totalMinutes = 0;
    double averageDuration = 0.0;
    char again = 'Y';

    do
    {
        attempts++;

        // ----- Capture -----
        string studentNumber;
        cout << "\nStudent number: ";
        getline(cin, studentNumber);

        cout << "Activity (1=Gym, 2=Group Class, 3=Consultation): ";
        int activity = readInteger();

        cout << "Duration in minutes (" << MIN_DURATION << "-" << MAX_DURATION << "): ";
        int duration = readInteger();

        // ----- Validate -----
        bool activityOk = (activity >= 1 && activity <= 3);
        bool durationOk = (duration >= MIN_DURATION && duration <= MAX_DURATION);

        if (!activityOk || !durationOk)
        {
            invalidCount++;
            if (!activityOk && !durationOk)
                cout << "INVALID CHECK-IN - invalid activity and invalid duration" << endl;
            else if (!activityOk)
                cout << "INVALID CHECK-IN - invalid activity" << endl;
            else
                cout << "INVALID CHECK-IN - invalid duration" << endl;
        }
        else
        {
            validCount++;
            totalMinutes += duration;

            // ----- Classify visit -----
            if (duration <= SHORT_MAX)
            {
                shortVisits++;
                cout << "SHORT VISIT" << endl;
            }
            else if (duration <= STANDARD_MAX)
            {
                standardVisits++;
                cout << "STANDARD VISIT" << endl;
            }
            else
            {
                extendedVisits++;
                cout << "EXTENDED VISIT" << endl;
            }

            if (duration >= LONG_SESSION_MIN)
                cout << "LONG SESSION CHECK" << endl;

            // ----- Count activity type -----
            switch (activity)
            {
            case 1: gymVisits++;     break;
            case 2: groupVisits++;   break;
            case 3: consultVisits++; break;
            }
        }

        // ----- Continue? (only if the daily limit is not yet reached) -----
        if (attempts < MAX_CHECKINS)
        {
            again = readYesNo("Process another check-in? (Y/N): ");
        }
        else
        {
            cout << "\nDaily limit of " << MAX_CHECKINS << " check-ins reached." << endl;
            again = 'N';
        }
    } while (again == 'Y');

    // ----- Average (safe against division by zero) -----
    if (validCount > 0)
        averageDuration = static_cast<double>(totalMinutes) / validCount;
    else
        averageDuration = 0.0;

    displayCheckinSummary(validCount, invalidCount, shortVisits, standardVisits,
        extendedVisits, gymVisits, groupVisits, consultVisits,
        totalMinutes, averageDuration);
}

// Displays the end-of-day summary for Question 3
void displayCheckinSummary(int valid, int invalid, int shortV, int standardV,
    int extendedV, int gym, int group, int consult,
    int totalMinutes, double average)
{
    cout << "\n=========== VUKAFIT DAILY CHECK-IN SUMMARY ===========" << endl;
    cout << left << setw(22) << "Valid Check-ins" << ": " << valid << endl;
    cout << left << setw(22) << "Invalid Attempts" << ": " << invalid << endl;
    cout << left << setw(22) << "Short Visits" << ": " << shortV << endl;
    cout << left << setw(22) << "Standard Visits" << ": " << standardV << endl;
    cout << left << setw(22) << "Extended Visits" << ": " << extendedV << endl;
    cout << left << setw(22) << "Gym Floor Visits" << ": " << gym << endl;
    cout << left << setw(22) << "Group Class Visits" << ": " << group << endl;
    cout << left << setw(22) << "Consultations" << ": " << consult << endl;
    cout << left << setw(22) << "Total Valid Minutes" << ": " << totalMinutes << endl;
    cout << left << setw(22) << "Average Visit Duration" << ": "
        << fixed << setprecision(2) << average << endl;
    cout << "======================================================" << endl;
}

// ============================================================
// QUESTION 4
// ============================================================

// Returns the value as text, with HIGH DEMAND beside it when value >= 40
string demandCell(int value)
{
    string cell = to_string(value);
    if (value >= HIGH_DEMAND_LIMIT)
        cell += " HIGH DEMAND";
    return cell;
}

void runQuestion4()
{
    // ---------- Declare and populate the arrays ----------
    string programmes[PROGRAMMES] = { "Yoga", "Strength", "Wellness Workshop" };
    string days[WEEKDAYS] = { "Mon", "Tue", "Wed", "Thu", "Fri" };
    int attendance[PROGRAMMES][WEEKDAYS] = {
        { 24, 31, 28, 35, 30 },
        { 38, 42, 36, 45, 41 },
        { 18, 22, 25, 20, 27 }
    };

    // ---------- Option to enter different data (used for testing) ----------
    char useDefault = readYesNo("\nUse the default attendance data? (Y/N): ");
    if (useDefault == 'N')
    {
        for (int p = 0; p < PROGRAMMES; p++)
        {
            for (int d = 0; d < WEEKDAYS; d++)
            {
                int value = NOT_A_NUMBER;
                while (value == NOT_A_NUMBER && !cin.eof())
                {
                    cout << programmes[p] << " - " << days[d] << ": ";
                    value = readInteger();
                    if (value == NOT_A_NUMBER)
                        cout << "Enter a whole number (0 or more)." << endl;
                }
                if (value == NOT_A_NUMBER)
                    value = 0;                // input closed: use 0
                attendance[p][d] = value;
            }
        }
    }

    // ---------- Results derived from the arrays ----------
    int    programmeTotal[PROGRAMMES] = { 0 };
    double programmeAverage[PROGRAMMES] = { 0.0 };
    int    bestDay[PROGRAMMES] = { 0 };          // index of highest day per programme
    int    dayTotal[WEEKDAYS] = { 0 };
    int    grandTotal = 0;
    int    highDemandCount = 0;

    // Nested loops: totals, highest day, high-demand count
    for (int p = 0; p < PROGRAMMES; p++)
    {
        for (int d = 0; d < WEEKDAYS; d++)
        {
            programmeTotal[p] += attendance[p][d];
            dayTotal[d] += attendance[p][d];
            grandTotal += attendance[p][d];

            if (attendance[p][d] > attendance[p][bestDay[p]])
                bestDay[p] = d;

            if (attendance[p][d] >= HIGH_DEMAND_LIMIT)
                highDemandCount++;
        }
        programmeAverage[p] = static_cast<double>(programmeTotal[p]) / WEEKDAYS;
    }

    // Busiest weekday
    int busiestDay = 0;
    for (int d = 1; d < WEEKDAYS; d++)
        if (dayTotal[d] > dayTotal[busiestDay])
            busiestDay = d;

    // Programme with the highest weekly total
    int topProgramme = 0;
    for (int p = 1; p < PROGRAMMES; p++)
        if (programmeTotal[p] > programmeTotal[topProgramme])
            topProgramme = p;

    double overallAverage = static_cast<double>(grandTotal) / (PROGRAMMES * WEEKDAYS);

    // ---------- Output: attendance report ----------
    cout << fixed << setprecision(2);
    cout << "\n=============== VUKAFIT WEEKLY ANALYTICS ===============" << endl;

    cout << left << setw(20) << "Programme";
    for (int d = 0; d < WEEKDAYS; d++)
        cout << setw(16) << days[d];
    cout << setw(8) << "Total" << "Average" << endl;
    cout << string(112, '-') << endl;

    for (int p = 0; p < PROGRAMMES; p++)
    {
        cout << left << setw(20) << programmes[p];
        for (int d = 0; d < WEEKDAYS; d++)
            cout << setw(16) << demandCell(attendance[p][d]);
        cout << setw(8) << programmeTotal[p] << programmeAverage[p] << endl;
        cout << "  Highest day for " << programmes[p] << ": "
            << days[bestDay[p]] << " (" << attendance[p][bestDay[p]] << ")" << endl;
    }

    // ---------- Output: weekday totals ----------
    cout << "\nDay Totals:" << endl;
    for (int d = 0; d < WEEKDAYS; d++)
        cout << "  " << left << setw(5) << days[d] << ": " << dayTotal[d] << endl;

    // ---------- Output: key indicators ----------
    cout << "\n" << left << setw(22) << "Busiest weekday"
        << ": " << days[busiestDay] << " (" << dayTotal[busiestDay] << ")" << endl;
    cout << left << setw(22) << "Top programme"
        << ": " << programmes[topProgramme] << " (" << programmeTotal[topProgramme] << ")" << endl;
    cout << left << setw(22) << "HIGH DEMAND values"
        << ": " << highDemandCount << " (attendance of " << HIGH_DEMAND_LIMIT << " or more)" << endl;
    cout << left << setw(22) << "Grand total" << ": " << grandTotal << endl;
    cout << left << setw(22) << "Overall average" << ": " << overallAverage << endl;
    cout << "========================================================" << endl;
}