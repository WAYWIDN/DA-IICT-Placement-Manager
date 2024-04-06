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
//------------------------------------- Function to Find Program Wise Placement Statistics -------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindProgramWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {
        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

        // Find Program is in Data or Not

        if (R1ProgramAttempts[program] == 0)
        {
            cout << "\nStudents of Program " << program << " does not found , Enter Valid program and Try Again \n\n";
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
                if (Current->program == program)
                {
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the company name into the set
                    uniqueCompanies.insert(Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Program " << program << " : \n";

            cout << "\nNo. Students Attempted in Round 1 : " << R1ProgramAttempts[program];
            cout << "\nNo. Students Attempted in Round 2 : " << R2ProgramAttempts[program];
            cout << "\nNo. Students Attempted in Round 3 : " << R3ProgramAttempts[program];
            cout << "\nNo. Students Attempted in Round 4 : " << R4ProgramAttempts[program];
            cout << "\nNo. Students Got Job Offer        : " << TotalProgramOffers[program];
            cout << "\nSucceess Rate                     : " << float(TotalProgramOffers[program]) / R1ProgramAttempts[program] * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalProgramOffers[program];
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl;

            PrintHorizontalLine(50);

            int i = 0;
            cout << "\nNo. Of Companies Visited : " << uniqueCompanies.size();
            cout << "\n\nCompanies : \n\n";
            for (string company : uniqueCompanies)
            {
                cout << company << " , ";
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
