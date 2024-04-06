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
//-------------------------------- Function to Find Year and Batch Wise Placement Statistics ------------------------------>
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindYearAndBatchWisePlacementStatistics()
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

        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        // To find Year and Batch is in the data or not

        if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\nStudents of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
            return;
        }

        //----> Variables to find attempts and job Offers

        int R1Attempts = 0;
        int R2Attempts = 0;
        int R3Attempts = 0;
        int R4Attempts = 0;
        int TotalOfferes = 0;

        //----> Finding Attempts in Round 1

        Node1 *Temp = HeadR1;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->batch == batch)
            {
                R1Attempts++;
            }

            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 2

        Temp = HeadR2;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->batch == batch)
            {
                R2Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 3

        Temp = HeadR3;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->batch == batch)
            {
                R3Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 4

        Temp = HeadR4;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->batch == batch)
            {
                R4Attempts++;
            }
            Temp = Temp->next;
        }

        Node2 *Current = HeadFR;

        vector<float> packages;

        float maxPackage = numeric_limits<float>::min();
        float minPackage = numeric_limits<float>::max();
        float totalPackage = 0;

        // Set to store unique Batches ,Programs and Companies

        set<string> uniqueProgramCompany;

        while (Current != NULL)
        {
            if (Current->year == year && Current->batch == batch)
            {

                TotalOfferes++;
                if (Current->package > maxPackage)
                    maxPackage = Current->package;
                if (Current->package < minPackage)
                    minPackage = Current->package;

                totalPackage += Current->package;

                packages.push_back(Current->package);

                // Insert program and company name into set
                uniqueProgramCompany.insert(Current->program + " - " + Current->company);
            }

            Current = Current->next;
        }

        cout <<endl;
        PrintHorizontalLine(60);
        cout << "\n# Placement Statistics of Batch " << batch << " in Year " << year << " : \n";

        cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
        cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
        cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
        cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
        cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
        cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
        cout << "\n\nMaximum Package Offered         : " << maxPackage;
        cout << "\nMinimum Package Offered         : " << minPackage;
        cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
        cout << "\nMedian Package                  : " << FindMedianPackage(packages);
        cout << endl
             << endl;

        PrintHorizontalLine(150);

        cout << "\nPrograms from which companies has hired Students in " << year << " from Batch " << batch << " : \n\n";

        int i = 0;
        for (string str : uniqueProgramCompany)
        {
            cout << str << " , ";
            if ((i + 1) % 5 == 0)
            {
                cout << endl;
            }
            i++;
        }
        cout << endl
             << endl;
        PrintHorizontalLine(150);
    }
}

