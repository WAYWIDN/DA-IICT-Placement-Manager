#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"

using namespace std;


void FindProgramWisePlacementStatistics()
{
    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "Insufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        string program;
        cout << "\nEnter Program : ";
        getline(cin,program);

        if (R1ProgramAttempts[program] == 0)
        {
            cout << "\nInvalid Program entered, enter valid Batch and Try Agian \nThank You\n";
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
            
            cout<<endl;
            PrintHorizontalLine(50);
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
            cout << "\nNo. Of Companies Visted : " << uniqueCompanies.size();
            cout << "\n\nCompanies : \n\n";
            for (string company : uniqueCompanies)
            {
                cout << company << " , ";
                if ((i + 1) % 15 == 0)
                    cout << endl;

                i++;
            }
            cout << endl << endl ;
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

    FindProgramWisePlacementStatistics();

    return 0;
}
