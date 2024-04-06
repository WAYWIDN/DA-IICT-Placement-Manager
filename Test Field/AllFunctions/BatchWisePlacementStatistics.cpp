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
//-------------------------------------- Function to Find Batch Wise Placement Statistics --------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindBatchWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        // Find Batch is in Data or Not

        if (R1BatchAttempts[batch] == 0)
        {
            cout << "\nStudents of Batch " << batch << " does not found , Enter Valid Batch and Try Again \n\n";
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
                if (Current->batch == batch)
                {
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert company name into set
                    uniqueCompanies.insert(Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Batch " << batch << " : \n";

            cout << "\nNo. Students Attempted in Round 1 : " << R1BatchAttempts[batch];
            cout << "\nNo. Students Attempted in Round 2 : " << R2BatchAttempts[batch];
            cout << "\nNo. Students Attempted in Round 3 : " << R3BatchAttempts[batch];
            cout << "\nNo. Students Attempted in Round 4 : " << R4BatchAttempts[batch];
            cout << "\nNo. Students Got Job Offer        : " << TotalBatchOffers[batch];
            cout << "\nSucceess Rate                     : " << float(TotalBatchOffers[batch]) / R1BatchAttempts[batch] * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalBatchOffers[batch];
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nNo. Of Companies Visited : " << uniqueCompanies.size();
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
