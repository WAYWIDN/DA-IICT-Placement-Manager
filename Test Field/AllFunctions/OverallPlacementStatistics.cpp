#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "InputPlacementData.cpp"
using namespace std;

void FindOverallPlacementStatistics()
{
    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "\nInsufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }
    else
    {
        cout << endl;
        PrintHorizontalLine(50);
        cout << "\nNo. Students Attempted in Round 1 : " << NOofStudentR1;
        cout << "\nNo. Students Attempted in Round 2 : " << NOofStudentR2;
        cout << "\nNo. Students Attempted in Round 3 : " << NOofStudentR3;
        cout << "\nNo. Students Attempted in Round 4 : " << NOofStudentR4;
        cout << "\nNo. Students Got Job Offer        : " << NOofStudentFR;
        cout << "\nSucceess Rate                     : " << float(NOofStudentFR) / NOofStudentR1 * 100 << "%";
        cout << "\n\nMaximum Package Offered         : " << MaxPackageOverall;
        cout << "\nMinimum Package Offered         : " << MinPackageOverall;
        cout << "\nAverage Package                 : " << AveragePackageOverall;
        cout << "\nMedian Package                  : " << FindMedianPackage(PackagesOfferedOverall);
        cout << endl
             << endl;

        PrintHorizontalLine(150);

        cout << "\nNo. Of Companis Visted : " << CompaniesVisitedOverall.size();
        cout << "\n\nCompanies : \n\n";
        for (int i = 0; i < CompaniesVisitedOverall.size(); i++)
        {
            cout << CompaniesVisitedOverall[i] << " , ";
            if ((i + 1) % 15 == 0)
                cout << endl;
        }
        cout << endl;
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

    FindOverallPlacementStatistics();

    return 0;
}