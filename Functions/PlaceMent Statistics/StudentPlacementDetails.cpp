#include <iostream>
#include <string>
#include "InputPlacementData.cpp"
using namespace std;

//--->Helper function to print a horizontal line

void FindStudentPlacementDetails()
{
    long long id;
    cout << "\nEnter Student's ID : ";
    cin >> id;

    if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
    {
        cout << "Insufficient Data to find Find Details,please insert Data and Try agian \nThank You\n";
        return;
    }

    if (StudentName[id] == "")
    {
        cout << "\nInvalid ID entered , enter valid ID and Try Agian \nThank You\n";
        return;
    }

    else
    {
        cout << endl;
        PrintHorizontalLine(50);

        cout << "\nName             : " << StudentName[id];
        cout << "\nID               : " << id;
        cout << "\nBatch            : " << StudentBatch[id];
        cout << "\nProgram          : " << StudentProgram[id];
        cout << "\nEmail            : " << StudentEmail[id];
        cout << "\nContact Number   : " << StudentContactNumber[id];
        cout << "\nWhtasapp Number  : " << StudentWhatsappNumber[id];
        cout << "\nSuuccessRate     : " << float(TotalStudnetOffers[id]) / R1StudnetAttempts[id] * 100 << "%\n\n";

        PrintHorizontalLine(100);

        cout << "\nNo. of Attemptes in Round 1 : " << R1StudnetAttempts[id];
        cout << "\nCompanies : ";
        for (string Company : R1StudentCompany[id])
        {
            cout << Company << " , ";
        }

        cout << "\n\nNo. of Attemptes in Round 2 : " << R2StudentAttempts[id];
        cout << "\nCompanies : ";
        for (string Company : R2StudentCompany[id])
        {
            cout << Company << " , ";
        }

        cout << "\n\nNo. of Attemptes in Round 3 : " << R3StudentAttempts[id];
        cout << "\nCompanies : ";
        for (string Company : R3StudentCompany[id])
        {
            cout << Company << " , ";
        }

        cout << "\n\nNo. of Attemptes in Round 4 : " << R4StudentAttempts[id];
        cout << "\nCompanies : ";
        for (string Company : R4StudentCompany[id])
        {
            cout << Company << " , ";
        }

        cout << "\n\nNo. of Job Offeres  : " << TotalStudnetOffers[id];
        cout << "\nCompanies : ";
        for (string Company : R1StudentCompany[id])
        {
            cout << Company << " , ";
        }
        cout << "\nPacakges : ";
        for (float Package : PackageOfferedStudent[id])
        {
            cout << Package << " , ";
        }

        cout << endl
             << endl;
        PrintHorizontalLine(100);
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

    FindStudentPlacementDetails();

    return 0;
}