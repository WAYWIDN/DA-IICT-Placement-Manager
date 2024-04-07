#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------ Function to Display Not Selected Students Batch and Program Wise ------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedBatchAndProgramWise(int batch, string program)
{
    cout << "\n<-------------------------------- Displaying Not Selected Students of Batch " << batch << " and Program " << program << "----------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->batch == batch && Current->program == program && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n--------------------------> Wow !!! All Students of Batch " << batch << " and Program " << program << " are placed <--------------------------\n\n";
    }

    PrintHorizontalLine(157);
    cout << "\n<-------------------------------- End of Not Selected Students of Batch " << batch << " and Program " << program << " ---------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//---------------------------- Function to Write Not Selected Students Batch and Program Wise ----------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedBatchAndProgramWise(const string &filepath, int batch, string program)
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
        if (Current->batch == batch && Current->program == program && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Program " << program << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully....\n\n";
    }
    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//---------------------------- Function to Find Not Selected Students Batch and Program Wise ------------------------------>
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedBatchAndProgramWise()
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

    string program;
    cout << "\nEnter Program : ";
    getline(cin, program);

    // Find Batch or Program is in Data or Not

    if (R1BatchAttempts[batch] == 0 || R1ProgramAttempts[program] == 0)
    {
        cout << "\nStudents of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
        return;
    }

    // Find Batch And Program is in Data or Not

    if (!IsBatchAndProgramInData(batch, program))
    {
        cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
        return;
    }

    char choice;
    cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
    cin >> choice;

    if (choice == 'Y')
        DisplayNotSelectedBatchAndProgramWise(batch, program);

    string filepath;
    cout << "\nEnter File Path Where you want to store the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedBatchAndProgramWise(filepath, batch, program);
}
