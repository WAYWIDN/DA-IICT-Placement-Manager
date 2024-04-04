#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------------- Functions to Display Programwise Data of a Particular Batch for Respective Rounds ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//------------------------- Helper Function to Display Programwise Data of particular Batch for Rounds 1 to 4 ------------------------------>

void DisplayRound1to4ProgramOFBatchWiseData(Node1 *Head, string program, int batch)
{
    cout << endl;
    PrintHorizontalLine(157); // Printing horizontal line
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157); // Printing horizontal line

    Node1 *Current = Head;

    bool programOFbatch_found = false;

    while (Current != NULL)
    {
        if (Current->program == program && Current->batch == batch)
        {
            programOFbatch_found = true;

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    if (!programOFbatch_found)
        cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Try Again \n";

    PrintHorizontalLine(157); // Printing horizontal line
}

//---------------------------- Helper Function to Display Programwise Data of particluar Batch for the Final Round ---------------------------->

void DisplayFinalRoundProgramOFBatchWiseData(Node2 *Head, string program, int batch)
{

    cout << endl;
    PrintHorizontalLine(177); // Printing horizontal line
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177); // Printing horizontal line

    Node2 *Current = Head;

    bool programOFbatch_found = false;

    while (Current != NULL)
    {
        if (Current->program == program && Current->batch == batch)
        {
            programOFbatch_found = true;

            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }

        Current = Current->next;
    }

    if (!programOFbatch_found)
        cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Try Again \n";

    PrintHorizontalLine(177); // Printing horizontal line
}

//--------------------------------------------------------------------------------------------------------------------->
//------------- Function to Display Programwise Data of a Particular Batch for Respective Rounds ---------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayProgramOFBatchWiseData(int choice, string program, int batch)
{

    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Batch " << batch << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFBatchWiseData(HeadR1, program, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Batch " << batch << "----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Batch " << batch << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFBatchWiseData(HeadR2, program, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Batch " << batch << " ---------------------------------------------->\n";
        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Batch " << batch << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFBatchWiseData(HeadR3, program, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Batch " << batch << " --------------------------------------------->\n";
        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Batch " << batch << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFBatchWiseData(HeadR4, program, batch);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Batch " << batch << " --------------------------------------------->\n";
        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Batch " << batch << " ------------------------------------->\n";
        DisplayFinalRoundProgramOFBatchWiseData(HeadFR, program, batch);
        cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Batch " << batch << " ------------------------------------------->\n";
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------- Functions to Write Programwise Data of Particular Batch for Respective Rounds in a file ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------- Function to Write Programwise Sorted Data of Particular Batch for Rounds 1 to 4 ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, int batch)
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

    bool programOFbatch_found = false;

    while (Current != nullptr)
    {
        if (Current->program == program && Current->batch == batch)
        {
            programOFbatch_found = true;

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    if (!programOFbatch_found)
        cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program Name and Try Again \n";
    else
        cout << "Data Written Successfully...\n";

    outputFile.close();
}

//-------------------------------------------------------------------------------------------------------------------------->
//--------------------- Function to Write Programwise Sorted Data of Particular Batch for Final Round ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, int batch)
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

    bool programOFbatch_found = false;

    while (Current != nullptr)
    {
        if (Current->program == program && Current->batch == batch)
        {
            programOFbatch_found = true;

            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->package << "," << Current->year << "\n";

            i++;
        }

        Current = Current->next;
    }

    if (!programOFbatch_found)
        cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program Name and Try Again \n";
    else
        cout << "\nData Written Successfully...\n";

    outputFile.close();
}

//--------------------------------------------------------------------------------------------------------------------->
//--------- Function to Sort Programwise Data of a Particular Batch for Respective Rounds ----------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataProgramOFBatchWise()
{

    string program;
    cout << "\nEnter Program : ";
    cin >> program;

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

    int choice;
    cout << "\nEnter Choice : ";
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
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayProgramOFBatchWiseData(1, program, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR1, program, batch);

        break;

    case 2:

        if (HeadR2 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice2;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayProgramOFBatchWiseData(2, program, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR2, program, batch);

        break;

    case 3:

        if (HeadR3 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice3;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayProgramOFBatchWiseData(3, program, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR3, program, batch);

        break;

    case 4:

        if (HeadR4 == NULL)
        {
            cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice4;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayProgramOFBatchWiseData(4, program, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR4, program, batch);

        break;

    case 5:

        if (HeadFR == NULL)
        {
            cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
            break;
        }

        char choice5;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayProgramOFBatchWiseData(5, program, batch);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFBatchWiseSortedDataForFinalRound(filepath, HeadFR, program, batch);

        break;

    default:

        cout << "\nInvalid Choice \n";
    }
}

int main()
{
    ReadFileForRound1("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound2("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound3("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound4("Input Files/Company1R1.csv", "Apple");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Apple");

    SortDataProgramOFBatchWise();

    return 0;
}