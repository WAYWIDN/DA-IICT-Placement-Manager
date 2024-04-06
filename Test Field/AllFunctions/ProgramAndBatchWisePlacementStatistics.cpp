#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"

using namespace std;

//-------------------------------------------- Function To Find Batch and Program is in Data or Not ---------------------------------------->

bool IsBatchAndProgramInData(int batch, string program)
{
    bool found = false;

    Node1 *Temp = HeadR1;

    while (Temp != NULL)
    {
        if (Temp->batch == batch && Temp->program == program)
        {
            found = true;
        }

        Temp = Temp->next;
    }

    return found;
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//----------------------------- Function to Find Program and Batch Wise Placement Statistics ------------------------------>
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindProgramAndBatchWisePlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {

        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        cin.ignore();

        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

        // Find Batch and Program is in Data or not

        if (R1BatchAttempts[batch] == 0 || R1ProgramAttempts[program] == 0)
        {
            cout << "\nStudents of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
            return;
        }

        // Find Batch and Program is in Data or not

        if (!IsBatchAndProgramInData(batch, program))
        {
            cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
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
            if (Temp->program == program && Temp->batch == batch)
            {
                R1Attempts++;
            }

            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 2

        Temp = HeadR2;
        while (Temp != NULL)
        {
            if (Temp->program == program && Temp->batch == batch)
            {
                R2Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 3

        Temp = HeadR3;
        while (Temp != NULL)
        {
            if (Temp->program == program && Temp->batch == batch)
            {
                R3Attempts++;
            }
            Temp = Temp->next;
        }

        //---->Finding Attempts in Round 4

        Temp = HeadR4;
        while (Temp != NULL)
        {
            if (Temp->program == program && Temp->batch == batch)
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

        // Set to store unique company names
        set<string> uniqueCompanies;

        while (Current != NULL)
        {
            if (Current->program == program && Current->batch == batch)
            {

                TotalOfferes++;
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
        cout << "\n# Placement Statistics of Batch " << batch << " and Program " << program << " : \n";

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
