#include <iostream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------ Function to Display Not Selected Students BatchWise of particular Year ------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedYearAndBatchWise(int year, int batch)
{
    cout << "\n<-------------------------------------- Displaying Not Selected Students of Batch " << batch << " and Year " << year << "------------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->batch == batch && Current->year == year && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Year " << year << " are placed <---------------------------\n\n";
    }

    PrintHorizontalLine(157);
    cout << "\n<----------------------------------- End of Not Selected Students of Batch " << batch << " and Year " << year << " ------------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//-------------------------- Function to Write Not Selected Students BatchWise of particulat Year ------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedYearAndBatchWise(const string &filepath, int year, int batch)
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
        if (Current->batch == batch && Current->year == year && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Year " << year << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully....\n\n";
    }
    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//-------------------------- Function to Find Not Selected Students BatchWise of particular Year -------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedYearAndBatchWise()
{

    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , Insert Data and Try Again \nThank You \n\n";
        return;
    }

    int year;
    cout << "\nEnter Year : ";
    cin >> year;

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    // Find Batch or Year is in Data or Not

    if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
    {
        cout << "\nStudents of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
        return;
    }

    // Find Batch and Year is in Data or Not

    if (!IsYearAndBatchInData(year, batch))
    {
        cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
        return;
    }

    char choice1;
    cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
    cin >> choice1;

    if (choice1 == 'Y')
        DisplayNotSelectedYearAndBatchWise(year, batch);

    string filepath;
    cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedYearAndBatchWise(filepath, year, batch);
}
