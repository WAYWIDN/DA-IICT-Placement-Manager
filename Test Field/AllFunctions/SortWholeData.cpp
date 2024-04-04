#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlaceMentData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//-------------------------------------------------- Functions to Display Whole Data of Respective Round ----------------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//--->Helper function to print a horizontal line

void PrintHorizontalLine(int width, char fillChar = '-')
{
    cout << setfill(fillChar) << setw(width) << "" << setfill(' ') << endl;
}

//---------------------------------------Helper Function to Display Whole Data for Round 1 to 4 ------------------------------>

void DisplayRound1to4WholeData(Node1 *Head)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    ;
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
             << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
             << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
             << "|" << setw(10) << left << Current->year << "|" << endl;
    }
    PrintHorizontalLine(157);
}

//---------------------------------------Helper Function to Display Whole Data for Final Round ------------------------------->

void DisplayFinalRoundWholeData(Node2 *Head)
{
    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
             << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
             << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
             << "|" << setw(10) << left << Current->year << "|" << endl;
    }
    PrintHorizontalLine(177);
}

//--------------------------------------------------------------------------------------------------------------------->
//---------------------------------------Function to Display Whole Data Round Wise ------------------------------------>
//--------------------------------------------------------------------------------------------------------------------->

void DisplayWholeDataRoundWise(int choice)
{
    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 --------------------------------------------->\n";
        cout << "Total number of students in Round 1: " << NOofStudentR1 << endl;
        DisplayRound1to4WholeData(HeadR1);
        cout << "\n<-------------------------------------------- End of Data For Round 1 --------------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 --------------------------------------------->\n";
        cout << "\nTotal number of students in Round 2: " << NOofStudentR2 << endl;
        DisplayRound1to4WholeData(HeadR2);
        cout << "\n<-------------------------------------------- End of Data For Round 2 --------------------------------------------------->\n";

        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 --------------------------------------------->\n";
        cout << "\nTotal number of students in Round 3: " << NOofStudentR3 << endl;
        DisplayRound1to4WholeData(HeadR3);
        cout << "\n<-------------------------------------------- End of Data For Round 3 --------------------------------------------------->\n";

        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 --------------------------------------------->\n";
        cout << "\nTotal number of students in Round 4: " << NOofStudentR4 << endl;
        DisplayRound1to4WholeData(HeadR4);
        cout << "\n<-------------------------------------------- End of Data For Round 4 --------------------------------------------------->\n";

        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round ------------------------------------------->\n";
        cout << "\nTotal number of students who got offers " << NOofStudentFR << endl;
        DisplayFinalRoundWholeData(HeadFR);
        cout << "\n<------------------------------------------ End of Data For Final Round ------------------------------------------------->\n";

        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//-------------------------------------------------- Functions to Write Whole Data of Respective Round in file ----------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//---------------------------------------Function to Write Whole Sorted Data of Round 1 to 4 ------------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteWholeSortedDataForRound1to4(const string &filepath, Node1 *Head)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

    int i = 1;
    Node1 *Current = Head;

    while (Current != nullptr)
    {
        outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                   << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                   << Current->year << "\n";

        Current = Current->next;
        i++;
    }

    cout << "\nData Written Successfully....\n";

    outputFile.close();
}

//-------------------------------------------------------------------------------------------------------------------------->
//---------------------------------------Function to Write Whole Sorted Data of Final Round ------------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteWholeSortedDataForFinalRound(const string &filepath, Node2 *Head)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

    int i = 1;
    Node2 *Current = Head;

    while (Current != nullptr)
    {
        outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                   << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                   << Current->package << "," << Current->year << "\n";

        Current = Current->next;
        i++;
    }

    cout << "\nData Written Successfully....\n";

    outputFile.close();
}

//--------------------------------------------------------------------------------------------------------------------->
//---------------------------------------Function to Sort Whole Data -------------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortWholeData()
{
    cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

    int choice;
    cout << "\nEnter Choise : ";
    cin >> choice;

    string filepath;

    switch (choice)
    {
    case 1:

        if (HeadR1 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 1 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice1;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayWholeDataRoundWise(1);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteWholeSortedDataForRound1to4(filepath, HeadR1);

        break;

    case 2:

        if (HeadR2 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice2;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayWholeDataRoundWise(2);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteWholeSortedDataForRound1to4(filepath, HeadR2);

        break;

    case 3:

        if (HeadR3 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice3;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayWholeDataRoundWise(3);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteWholeSortedDataForRound1to4(filepath, HeadR3);

        break;

    case 4:

        if (HeadR4 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice4;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayWholeDataRoundWise(4);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteWholeSortedDataForRound1to4(filepath, HeadR4);

        break;

    case 5:

        if (HeadFR == NULL)
        {
            cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice5;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayWholeDataRoundWise(5);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteWholeSortedDataForFinalRound(filepath, HeadFR);

        break;

    default:

        cout << "\nInvalid Choice \n";
    }
}
