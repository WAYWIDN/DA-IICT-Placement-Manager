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
//------------------------------ Function to Find Year and Company Wise Placement Statistics ------------------------------>
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindYearAndCompanyWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data to find Find Details,please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {

        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        cin.ignore();

        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

        // To find Year and Company is in the data or not

        if (R1CompanyAttempts[company] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\nStudents of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
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
            if (Temp->year == year && Temp->company == company)
            {
                R1Attempts++;
            }

            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 2

        Temp = HeadR2;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->company == company)
            {
                R2Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 3

        Temp = HeadR3;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->company == company)
            {
                R3Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 4

        Temp = HeadR4;
        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->company == company)
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

        // Set to store unique batches and programs names
        set<string> uniqueBatchAndProgram;

        while (Current != NULL)
        {
            if (Current->year == year && Current->company == company)
            {

                TotalOfferes++;
                if (Current->package > maxPackage)
                    maxPackage = Current->package;
                if (Current->package < minPackage)
                    minPackage = Current->package;

                totalPackage += Current->package;

                packages.push_back(Current->package);

                // Insert the batch and program name into the set
                uniqueBatchAndProgram.insert(to_string(Current->batch) + " - " + Current->program);
            }

            Current = Current->next;
        }

        cout <<endl;
        PrintHorizontalLine(60);
        cout << "\n# Placement Statistics of Company " << company << " in Year " << year << " : \n";

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

        int i = 0;
        cout << "\nBatches and Programs from which " << company << " has hired Students in " << year << " : \n\n";
        for (string str : uniqueBatchAndProgram)
        {
            cout << str << " , ";
            if ((i + 1) % 5 == 0)
                cout << endl;

            i++;
        }
        cout << endl
             << endl;
        PrintHorizontalLine(150);
    }
}

