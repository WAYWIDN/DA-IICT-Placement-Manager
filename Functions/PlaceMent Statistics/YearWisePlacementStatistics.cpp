#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//--------------------------------------- Function to Find Year Wise Placement Statistics --------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindYearWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {
        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        if (R1YearAttempts[year] == 0)
        {
            cout << "\nStudents of Year " << year << " does not found , Enter Valid Year and Try Again \n\n";
            return;
        }

        else
        {
            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique company names
            set<string> uniqueCompanies;

            while (Current != NULL)
            {
                if (Current->year == year)
                {
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    uniqueCompanies.insert(Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics in Year " << year << " : \n";

            cout << "\nNo. Students Attempted in Round 1 : " << R1YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 2 : " << R2YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 3 : " << R3YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 4 : " << R4YearAttempts[year];
            cout << "\nNo. Students Got Job Offer        : " << TotalYearOffers[year];
            cout << "\nSucceess Rate                     : " << float(TotalYearOffers[year]) / R1YearAttempts[year] * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalYearOffers[year];
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nNo. Of Companies Visited in " << year << " : " << uniqueCompanies.size();
            cout << "\n\nCompanies : \n\n";

            int i = 0;
            for (string Companies : uniqueCompanies)
            {
                cout << Companies << " , ";
                if ((i + 1) % 15 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }
}
