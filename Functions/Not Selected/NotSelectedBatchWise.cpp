#include <iostream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------ Function to Display Not Selected Students BatchWise -------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedBatchWise(int batch)
{

    cout << "\n<------------------------------------------------ Displaying Not Selected Students of Batch " << batch << " ----------------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->batch == batch && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " are placed <---------------------------\n\n";
    }

    PrintHorizontalLine(157);

    cout << "\n<----------------------------------------------- End of Not Selected Students of Batch " << batch << " --------------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------ Function to Write Not Selected Students BatchWise ---------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedBatchWise(const string &filepath, int batch)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

    bool Success = false;

    int i = 1;
    Node1 *Current = HeadR1;

    while (Current != NULL)
    {
        if (Current->batch == batch && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully....\n\n";
    }

    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//-------------------------------------- Function to Find Not Selected Students BatchWise --------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedBatchWise()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , Insert Data and Try Again \nThank You \n\n";
        return;
    }

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    if (R1BatchAttempts[batch] == 0)
    {
        cout << "\nStudents of Batch " << batch << " does not found , Enter Valid Batch and Try Again \n\n";
        return;
    }

    char choice1;
    cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
    cin >> choice1;

    if (choice1 == 'Y')
        DisplayNotSelectedBatchWise(batch);

    string filepath;
    cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedBatchWise(filepath, batch);
}
