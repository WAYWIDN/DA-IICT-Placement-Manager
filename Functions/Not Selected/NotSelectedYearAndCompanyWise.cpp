#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------- Function to Display Not Selected Students Year and Company Wise ------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedYearAndCompanyWise(int year, string company)
{
    cout << "\n<-------------------------------- Displaying Not Selected Students of Year " << year << " and Company " << company << "----------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->year == year && Current->company == company && TotalStudnetOffers[Current->id] == 0)
        {

            Success = true;

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    if (!Success)
    {
        cout << "\n--------------------------> Wow !!! All Students of Year " << year << " and Company " << company << " are placed <--------------------------\n\n";
    }

    PrintHorizontalLine(157);
    cout << "\n<-------------------------------- End of Not Selected Students of Year " << year << " and Company " << company << " ---------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------- Function to Write Not Selected Students Year and Company Wise --------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedYearAndCompanyWise(const string &filepath, int year, string company)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

    int i = 1;
    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->year == year && Current->company == company && TotalStudnetOffers[Current->id] == 0)
        {

            Success = true;

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    if (!Success)
    {
        cout << "\n---------------------------> Wow !!! All Students of Year " << year << " and Company " << company << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully....\n\n";
    }
    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------- Function to Find Not Selected Students Year and Company Wise ---------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedYearAndCompanyWise()
{
    if (IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , Insert Data and Try Again \nThank You \n\n";
        return;
    }

    int year;
    cout << "\nEnter Year : ";
    cin >> year;

    cin.ignore();

    string company;
    cout << "\nEnter Company : ";
    getline(cin, company);

    // Find Year or Company is in Data or Not

    if (R1CompanyAttempts[company] == 0 || R1YearAttempts[year] == 0)
    {
        cout << "\nStudents of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
        return;
    }

    // Find Year and Company is in Data or Not

    if (!IsYearAndCompanyInData(year, company))
    {
        cout << "\n-----> Students of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
        return;
    }

    char choice;
    cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
    cin >> choice;

    if (choice == 'Y')
        DisplayNotSelectedYearAndCompanyWise(year, company);

    string filepath;
    cout << "\nEnter File Path Where you want to store the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedYearAndCompanyWise(filepath, year, company);
}
