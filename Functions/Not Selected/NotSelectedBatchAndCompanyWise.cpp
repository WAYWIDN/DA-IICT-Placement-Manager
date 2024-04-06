#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//---------------------------- Function to Display Not Selected Students Batch and Company Wise --------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedBatchAndCompanyWise(int batch, string company)
{
    cout << "\n<-------------------------------- Displaying Not Selected Students of Batch " << batch << " and Company " << company << "----------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->batch == batch && Current->company == company && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n--------------------------> Wow !!! All Students of Batch " << batch << " and Company " << company << " are placed <--------------------------\n\n";
    }

    PrintHorizontalLine(157);
    cout << "\n<-------------------------------- End of Not Selected Students of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//----------------------------- Function to Write Not Selected Students Batch and Company Wise ---------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedBatchAndCompanyWise(const string &filepath, int batch, string company)
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
        if (Current->batch == batch && Current->company == company && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Company " << company << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully...\n\n";
    }
    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------- Function to Find Not Selected Students Batch and Company Wise --------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedBatchAndCompanyWise()
{

    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , Insert Data and Try Again \nThank You \n\n";
        return;
    }

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    cin.ignore();

    string company;
    cout << "\nEnter Company : ";
    getline(cin, company);

    if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
    {
        cout << "\nStudents of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
        return;
    }

    char choice;
    cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
    cin >> choice;

    if (choice == 'Y')
        DisplayNotSelectedBatchAndCompanyWise(batch, company);

    string filepath;
    cout << "\nEnter File Path Where you want to store the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedBatchAndCompanyWise(filepath, batch, company);
}

