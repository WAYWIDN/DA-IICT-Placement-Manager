#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------------- Functions to Display Yearwise Data of a Particular Batch for Respective Rounds ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//------------------------- Helper Function to Display Yearwise Data of particular Batch for Rounds 1 to 4 ------------------------------>

void DisplayRound1to4YearAndBatchWiseData(Node1 *Head, int year, int batch)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->year == year && Current->batch == batch)
        {

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    PrintHorizontalLine(157);
}

//---------------------------- Helper Function to Display Yearwise Data of particluar Batch for the Final Round ---------------------------->

void DisplayFinalRoundYearAndBatchWiseData(Node2 *Head, int year, int batch)
{

    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->year == year && Current->batch == batch)
        {

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    PrintHorizontalLine(177);
}

//--------------------------------------------------------------------------------------------------------------------->
//------------- Function to Display Yearwise Data of a Particular Batch for Respective Rounds ---------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayYearAndBatchWiseData(int choice, int year, int batch)
{

    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Year " << year << " and Batch " << batch << " ---------------------------------------->\n";
        DisplayRound1to4YearAndBatchWiseData(HeadR1, year, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Year " << year << " and Batch " << batch << "----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Year " << year << " and Batch " << batch << " ---------------------------------------->\n";
        DisplayRound1to4YearAndBatchWiseData(HeadR2, year, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Year " << year << " and Batch " << batch << " ---------------------------------------------->\n";
        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Year " << year << " and Batch " << batch << " --------------------------------------->\n";
        DisplayRound1to4YearAndBatchWiseData(HeadR3, year, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Year " << year << " and Batch " << batch << " --------------------------------------------->\n";
        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Year " << year << " and Batch " << batch << " --------------------------------------->\n";
        DisplayRound1to4YearAndBatchWiseData(HeadR4, year, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Year " << year << " and Batch " << batch << " --------------------------------------------->\n";
        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Year " << year << " and Batch " << batch << " ------------------------------------->\n";
        DisplayFinalRoundYearAndBatchWiseData(HeadFR, year, batch);
        cout << "\n<------------------------------------------ End of Data For Final Round of Year " << year << " and Batch " << batch << " ------------------------------------------->\n";
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------- Functions to Write Yearwise Data of Particular Batch for Respective Rounds in a file ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------- Function to Write Yearwise Sorted Data of Particular Batch for Rounds 1 to 4 ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteYearAndBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int year, int batch)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

    int i = 1;
    Node1 *Current = Head;

    while (Current != nullptr)
    {
        if (Current->year == year && Current->batch == batch)
        {

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    cout << "Data Written Successfully...\n\n";

    outputFile.close();
}

//-------------------------------------------------------------------------------------------------------------------------->
//--------------------- Function to Write Yearwise Sorted Data of Particular Batch for Final Round ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteYearAndBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int year, int batch)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

    int i = 1;
    Node2 *Current = Head;

    while (Current != nullptr)
    {
        if (Current->year == year && Current->batch == batch)
        {

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->package << "," << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    cout << "\nData Written Successfully...\n\n";

    outputFile.close();
}

//--------------------------------------------------------------------------------------------------------------------->
//------------ Function to Sort Yearwise Data of a Particular Batch for Respective Rounds ----------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataYearAndBatchWise()
{

    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    int year;
    cout << "\nEnter Year : ";
    cin >> year;

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    // To find Year and Batch is in the data or not

    if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
    {
        cout << "\nStudents of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
        return;
    }

    cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

    int choice;
    cout << "\nEnter Choice : ";
    cin >> choice;

    string filepath;

    switch (choice)
    {
    case 1:

        char choice1;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayYearAndBatchWiseData(1, year, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR1, year, batch);

        break;

    case 2:

        char choice2;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayYearAndBatchWiseData(2, year, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR2, year, batch);

        break;

    case 3:

        char choice3;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayYearAndBatchWiseData(3, year, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR3, year, batch);

        break;

    case 4:

        char choice4;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayYearAndBatchWiseData(4, year, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR4, year, batch);

        break;

    case 5:

        char choice5;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayYearAndBatchWiseData(5, year, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteYearAndBatchWiseSortedDataForFinalRound(filepath, HeadFR, year, batch);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
