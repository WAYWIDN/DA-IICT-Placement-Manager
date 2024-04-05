#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"

using namespace std;

void FindBatchAndCompanyWisePlacementStatistics()
{
    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "\nInsufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        int batch;
        cout << "\nEnter batch : ";
        cin >> batch;
        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

        //----> Variables to find attempts and job Offers

        int R1Attempts = 0;
        int R2Attempts = 0;
        int R3Attempts = 0;
        int R4Attempts = 0;
        int TotalOfferes = 0;

        bool BatchAndCompanyFound = false; // To find Batch and Company is in the data or not

        //----> Finding Attempts in Round 1

        Node1 *Temp = HeadR1;
        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
            {
                BatchAndCompanyFound = true;
                R1Attempts++;
            }

            Temp = Temp->next;
        }

        if (!BatchAndCompanyFound)
        {
            cout << "\nInvalid Batch and Company , please Enter Valid Batch and Program , Try again \nThank You\n";
            return;
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

        //---->Finding Attempts in Round 2

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

                // Insert the company name into the set
                uniquePrograms.insert(Current->program);
            }

            Current = Current->next;
        }

        cout << endl;
        PrintHorizontalLine(50);
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

int main()
{
    ReadFileForRound1("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound2("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound3("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound4("Input Files/Company1R1.csv", "Apple");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Apple");

    ReadFileForRound1("Input Files/Company1R1.csv", "Google");
    ReadFileForRound2("Input Files/Company1R1.csv", "Google");
    ReadFileForRound3("Input Files/Company1R1.csv", "Google");
    ReadFileForRound4("Input Files/Company1R1.csv", "Google");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Google");

    ReadFileForRound1("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound2("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound3("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound4("Input Files/Company1R1.csv", "XYZ");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "XYZ");

    FindBatchAndCompanyWisePlacementStatistics();

    return 0;
}
