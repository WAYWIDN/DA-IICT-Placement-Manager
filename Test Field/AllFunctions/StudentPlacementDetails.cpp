#include <iostream>
#include <string>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//--------------------------------------- Function to Find Student's Placement Statistics --------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindStudentPlacementDetails()
{
    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    long long id;
    cout << "\nEnter Student's ID : ";
    cin >> id;

    if (StudentName[id] == "")
    {
        cout << "\nInvalid ID entered , enter valid ID and Try Agian \nThank You\n";
        return;
    }

    else
    {
        cout << endl;
        PrintHorizontalLine(60);
        cout << "\n# " << id << "'s Placement Details : \n";

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
        cout << "\nPackages : ";
        for (float Package : PackageOfferedStudent[id])
        {
            cout << Package << " , ";
        }

        cout << endl
             << endl;
        PrintHorizontalLine(100);
    }
}
