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
//-------------------------------------- Function to Find Company Wise Placement Statistics ------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindCompanyWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

        // Find Company is in Data or Not
        if (R1CompanyAttempts[company] == 0)
        {
            cout << "\nStudents of Company " << company << " does not found , Enter Valid Company and Try Again \n\n";
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
            set<string> uniqueProgramOFBatch;

            while (Current != NULL)
            {
                if (Current->company == company)
                {
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the batch and program into the set
                    uniqueProgramOFBatch.insert(to_string(Current->batch) + " " + Current->program);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Company " << company << " : \n";

            cout << "\nNo. Students Attempted in Round 1 : " << R1CompanyAttempts[company];
            cout << "\nNo. Students Attempted in Round 2 : " << R1CompanyAttempts[company];
            cout << "\nNo. Students Attempted in Round 3 : " << R1CompanyAttempts[company];
            cout << "\nNo. Students Attempted in Round 4 : " << R1CompanyAttempts[company];
            cout << "\nNo. Students Got Job Offer        : " << TotalCompanyOffers[company];
            cout << "\nSucceess Rate                     : " << float(TotalCompanyOffers[company]) / R1CompanyAttempts[company] * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalCompanyOffers[company];
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nPrograms of Batch from " << company << " has hired students : \n\n";

            int i = 0;
            for (string str : uniqueProgramOFBatch)
            {
                cout << str << " , ";
                if ((i + 1) % 5 == 0)
                {
                    cout << endl;
                }
                i++;
            }

            cout << endl;
            PrintHorizontalLine(150);
        }
    }
}
