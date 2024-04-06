#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------------- Functions to Display Programwise Data of a Particular Year for Respective Rounds ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//---------------------------------------------- Function To Find Year And Program is in Data or Not ----------------------------------------->

bool IsYearAndProgramInData(int year, string program)
{
    bool found = false;

    Node1 *Temp = HeadR1;

    while (Temp != NULL)
    {
        if (Temp->year == year && Temp->program == program)
        {
            found = true;
        }

        Temp = Temp->next;
    }

    return found;
}

//------------------------- Helper Function to Display Programwise Data of particular Year for Rounds 1 to 4 ------------------------------>

void DisplayRound1to4ProgramOFYearWiseData(Node1 *Head, string program, int year)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program && Current->year == year)
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

//---------------------------- Helper Function to Display Programwise Data of particluar Year for the Final Round ---------------------------->

void DisplayFinalRoundProgramOFYearWiseData(Node2 *Head, string program, int year)
{

    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program && Current->year == year)
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
//------------- Function to Display Programwise Data of a Particular Year for Respective Rounds ---------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayProgramOFYearWiseData(int choice, string program, int year)
{

    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Year " << year << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFYearWiseData(HeadR1, program, year);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Year " << year << "----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Year " << year << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFYearWiseData(HeadR2, program, year);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Year " << year << " ---------------------------------------------->\n";
        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Year " << year << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFYearWiseData(HeadR3, program, year);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Year " << year << " --------------------------------------------->\n";
        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Year " << year << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFYearWiseData(HeadR4, program, year);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Year " << year << " --------------------------------------------->\n";
        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Year " << year << " ------------------------------------->\n";
        DisplayFinalRoundProgramOFYearWiseData(HeadFR, program, year);
        cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Year " << year << " ------------------------------------------->\n";
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------- Functions to Write Programwise Data of Particular Year for Respective Rounds in a file ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------- Function to Write Programwise Sorted Data of Particular Year for Rounds 1 to 4 ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFYearWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, int year)
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
        if (Current->program == program && Current->year == year)
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
//--------------------- Function to Write Programwise Sorted Data of Particular Year for Final Round ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFYearWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, int year)
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
        if (Current->program == program && Current->year == year)
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
//---------------- Function to Sort Programwise Data of a Particular Year for Respective Rounds ----------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataProgramOFYearWise()
{

    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    int year;
    cout << "\nEnter Year : ";
    cin >> year;

    cin.ignore();

    string program;
    cout << "\nEnter Program : ";
    getline(cin, program);

    // To find Year and Program is in the data or not

    if (R1ProgramAttempts[program] == 0 || R1YearAttempts[year] == 0)
    {
        cout << "\nStudents of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
        return;
    }

    // To find Year and Program is in the data or not

    if (!IsYearAndProgramInData(year, program))
    {
        cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
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
            DisplayProgramOFYearWiseData(1, program, year);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR1, program, year);

        break;

    case 2:

        char choice2;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayProgramOFYearWiseData(2, program, year);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR2, program, year);

        break;

    case 3:

        char choice3;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayProgramOFYearWiseData(3, program, year);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR3, program, year);

        break;

    case 4:

        char choice4;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayProgramOFYearWiseData(4, program, year);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR4, program, year);

        break;

    case 5:

        char choice5;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayProgramOFYearWiseData(5, program, year);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFYearWiseSortedDataForFinalRound(filepath, HeadFR, program, year);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
