#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------- Function to Find Overall Placement Statistics ------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindOverallPlacementStatistics()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient data Inserted,please insert Data and Try agian \nThank You\n\n";
        return;
    }
    else
    {
        cout <<endl;
        PrintHorizontalLine(60);
        cout << "\n# Overall Placement Statistics : \n";
        
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

        cout << "\nNo. Of Companies Visted : " << CompaniesVisitedOverall.size();
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
