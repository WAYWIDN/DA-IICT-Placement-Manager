#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------- Functions to Display ProgramWise Data of Respective Round ------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------- Helper Function to Display ProgramWise Data for Round 1 to 4 ------------------------------>

void DisplayRound1to4ProgramWiseData(Node1 *Head, string program)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program)
        {

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    PrintHorizontalLine(157); // Printing horizontal line
}

//-------------------------------------- Helper Function to Display ProgramWise Data for Final Round ------------------------------->

void DisplayFinalRoundProgramWiseData(Node2 *Head, string program)
{
    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program)
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
//--------------------------------- Function to Display ProgramWise Data Round Wise ----------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayProgramWiseData(int choice, string program)
{
    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " ---------------------------------------->\n";
        DisplayRound1to4ProgramWiseData(HeadR1, program);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << "----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " ---------------------------------------->\n";
        DisplayRound1to4ProgramWiseData(HeadR2, program);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " ---------------------------------------------->\n";

        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " --------------------------------------->\n";
        DisplayRound1to4ProgramWiseData(HeadR3, program);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " --------------------------------------------->\n";

        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " --------------------------------------->\n";
        DisplayRound1to4ProgramWiseData(HeadR4, program);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " --------------------------------------------->\n";

        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " ------------------------------------->\n";
        DisplayFinalRoundProgramWiseData(HeadFR, program);
        cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " ------------------------------------------->\n";

        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//-------------------------------------------- Functions to Write ProgramWise Data of Respective Round in file ----------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//---------------------------------- Function to Write ProgramWise Sorted Data of Round 1 to 4 ----------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program)
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
        if (Current->program == program)
        {

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    cout << "\nData Written Successfully...\n\n";

    outputFile.close();
}

//-------------------------------------------------------------------------------------------------------------------------->
//--------------------------------- Function to Write ProgramWise Sorted Data of Final Round ------------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program)
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
        if (Current->program == program)
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
//-------------------------------------- Function to Sort Data Program Wise ------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataProgramWise()
{

    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    string program;
    cout << "\nEnter Program : ";
    getline(cin, program);

    // Find Program is in Data or Not

    if (R1ProgramAttempts[program] == 0)
    {
        cout << "\nStudents of Program " << program << " does not found , Enter Valid program and Try Again \n\n";
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
            DisplayProgramWiseData(1, program);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteProgramWiseSortedDataForRound1to4(filepath, HeadR1, program);

        break;

    case 2:

        char choice2;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayProgramWiseData(2, program);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteProgramWiseSortedDataForRound1to4(filepath, HeadR2, program);

        break;

    case 3:

        char choice3;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayProgramWiseData(3, program);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteProgramWiseSortedDataForRound1to4(filepath, HeadR3, program);

        break;

    case 4:

        char choice4;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayProgramWiseData(4, program);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteProgramWiseSortedDataForRound1to4(filepath, HeadR4, program);

        break;

    case 5:

        char choice5;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayProgramWiseData(5, program);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteProgramWiseSortedDataForFinalRound(filepath, HeadFR, program);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
