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
//----------------------------- Function to Find Batch and Company Wise Placement Statistics ------------------------------>
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindBatchAndCompanyWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {
        int batch;
        cout << "\nEnter batch : ";
        cin >> batch;

        cin.ignore();

        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

        // Find Batch and Company is in Data or Not

        if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
        {
            cout << "\nStudents of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
            return;
        }

        //----> Variables to find attempts and job Offers

        int R1Attempts = 0;
        int R2Attempts = 0;
        int R3Attempts = 0;
        int R4Attempts = 0;
        int TotalOfferes = 0;


        Node1 *Temp = HeadR1;
        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
            {
                R1Attempts++;
            }

            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 2

        Temp = HeadR2;
        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
            {
                R2Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 3

        Temp = HeadR3;
        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
            {
                R3Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 4

        Temp = HeadR4;
        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
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

        // Set to store unique Programs
        set<string> uniquePrograms;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->company == company)
            {

                TotalOfferes++;
                if (Current->package > maxPackage)
                    maxPackage = Current->package;
                if (Current->package < minPackage)
                    minPackage = Current->package;

                totalPackage += Current->package;

                packages.push_back(Current->package);

                // Insert the program into the set
                uniquePrograms.insert(Current->program);
            }

            Current = Current->next;
        }

        cout <<endl;
        PrintHorizontalLine(60);
        cout << "\n# Placement Statistics of Batch " << batch << " and Company " << company << " : \n";

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
        cout << "\nNo. Of Programs whose Student got Job Offers : " << uniquePrograms.size();
        cout << "\n\nPrograms : \n\n";
        for (string program : uniquePrograms)
        {
            cout << program << " , ";
            if ((i + 1) % 15 == 0)
                cout << endl;

            i++;
        }
        cout << endl
             << endl;
        PrintHorizontalLine(150);
    }
}

