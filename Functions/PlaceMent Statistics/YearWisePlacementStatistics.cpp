#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include "InputPlacementData.cpp"
using namespace std;

void FindYearWisePlacementStatistics()
{
    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "\nInsufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        if (R1YearAttempts[year] == 0)
        {
            cout << "\nInvalid Year entered , enter valid Year and Try Agian \nThank You\n";
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
                if (Current->year == year)
                {
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    uniqueCompanies.insert(Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 2 : " << R2YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 3 : " << R3YearAttempts[year];
            cout << "\nNo. Students Attempted in Round 4 : " << R4YearAttempts[year];
            cout << "\nNo. Students Got Job Offer        : " << TotalYearOffers[year];
            cout << "\nSucceess Rate                     : " << float(TotalYearOffers[year]) / R1YearAttempts[year] * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalYearOffers[year];
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nNo. Of Companies Visited in " << year << " : " << uniqueCompanies.size();
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

    FindYearWisePlacementStatistics();

    return 0;
}
