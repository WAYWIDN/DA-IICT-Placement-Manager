#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"

using namespace std;

void FindCompanyWisePlacementStatistics()
{
    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "\nInsufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        string company;
        cout << "\nEnter Company Name : ";
        cin >> company;

        if (R1CompanyAttempts[company] == 0)
        {
            cout << "\nInvalid Company Name entered, enter valid Batch and Try Agian \nThank You\n";
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

                    // Insert the company name into the set
                    uniqueProgramOFBatch.insert(to_string(Current->batch) + " " + Current->program);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
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

            cout << "\nPograms of Batch from " << company << " has hired students : \n\n";

            int i=0;
            for (string str : uniqueProgramOFBatch)
            {
                cout << str << " , ";
                if( (i+1) % 5 == 0)
                {
                    cout<<endl;
                }
                i++;
            }

            cout << endl ;
            PrintHorizontalLine(150);
        }
    }
}

int main()
{
    ReadFileForRound1("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound2("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound3("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound4("Input Files/Company1R1.csv", "Apple");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Apple");

    ReadFileForRound1("Input Files/Company1R3.csv", "Google");
    ReadFileForRound2("Input Files/Company1R3.csv", "Google");
    ReadFileForRound3("Input Files/Company1R3.csv", "Google");
    ReadFileForRound4("Input Files/Company1R3.csv", "Google");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Google");

    ReadFileForRound1("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound2("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound3("Input Files/Company1R1.csv", "XYZ");
    ReadFileForRound4("Input Files/Company1R1.csv", "XYZ");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "XYZ");

    FindCompanyWisePlacementStatistics();

    return 0;
}
