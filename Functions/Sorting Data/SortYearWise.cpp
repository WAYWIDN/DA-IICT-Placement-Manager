#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//---------------------------------- Functions to Display YearWise Data of Respective Round ------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//---------------------------------------Helper Function to Display YearWise Data for Round 1 to 4 ------------------------------>

void DisplayRound1to4YearWiseData(Node1 *Head, int year)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->year == year)
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

//---------------------------------------Helper Function to Display YearWise Data for Final Round ------------------------------->

void DisplayFinalRoundYearWiseData(Node2 *Head, int year)
{

    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->year == year)
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
//---------------------------------------Function to Display YearWise Data Round Wise -------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayYearWiseData(int choice, int year)
{

    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Year " << year << " ---------------------------------------->\n";
        DisplayRound1to4YearWiseData(HeadR1, year);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Year " << year << " ----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Year " << year << " ---------------------------------------->\n";
        DisplayRound1to4YearWiseData(HeadR2, year);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Year " << year << " ---------------------------------------------->\n";
        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Year " << year << " --------------------------------------->\n";
        DisplayRound1to4YearWiseData(HeadR3, year);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Year " << year << " --------------------------------------------->\n";
        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Year " << year << " --------------------------------------->\n";
        DisplayRound1to4YearWiseData(HeadR4, year);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Year " << year << " --------------------------------------------->\n";
        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Year " << year << " ------------------------------------->\n";
        DisplayFinalRoundYearWiseData(HeadFR, year);
        cout << "\n<------------------------------------------ End of Data For Final Round of Year " << year << " ------------------------------------------->\n";
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//---------------------------------------------- Functions to Write YearWise Data of Respective Round in file ----------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------------------------- Function to Write YearWise Sorted Data of Round 1 to 4 ----------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteYearWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int year)
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
        if (Current->year == year)
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
//----------------------------------- Function to Write BatchWise Sorted Data of Final Round ------------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteYearWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int year)
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
        if (Current->year == year)
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
//--------------------------------------- Function to Sort Whole Data Year Wise --------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataYearWise()
{
    if (IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    int year;
    cout << "\nEnter Year : ";
    cin >> year;

    if (R1YearAttempts[year] == 0)
    {
        cout << "\nStudents of Year " << year << " does not found , Enter Valid Year and Try Again \n\n";
        return;
    }

    cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

    int choice;
    cout << "\nEnter Choise : ";
    cin >> choice;

    string filepath;

    switch (choice)
    {
    case 1:

        char choice1;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayYearWiseData(1, year);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteYearWiseSortedDataForRound1to4(filepath, HeadR1, year);

        break;

    case 2:

        char choice2;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayYearWiseData(2, year);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteYearWiseSortedDataForRound1to4(filepath, HeadR2, year);

        break;

    case 3:

        char choice3;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayYearWiseData(3, year);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteYearWiseSortedDataForRound1to4(filepath, HeadR3, year);

        break;

    case 4:

        char choice4;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayYearWiseData(4, year);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteYearWiseSortedDataForRound1to4(filepath, HeadR4, year);

        break;

    case 5:

        char choice5;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayYearWiseData(5, year);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteYearWiseSortedDataForFinalRound(filepath, HeadFR, year);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
