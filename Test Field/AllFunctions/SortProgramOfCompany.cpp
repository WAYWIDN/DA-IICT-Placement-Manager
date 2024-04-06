#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------------- Functions to Display Programwise Data of a Particular Company for Respective Rounds ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//------------------------------------------ Function To Find Program And Company is in Data or Not ---------------------------------------->

bool IsProgramAndCompanyInData(string program, string company)
{
    bool found = false;

    Node1 *Temp = HeadR1;

    while (Temp != NULL)
    {
        if (Temp->program == program && Temp->company == company)
        {
            found = true;
        }

        Temp = Temp->next;
    }

    return found;
}
//------------------------- Helper Function to Display Programwise Data of particular Company for Rounds 1 to 4 ------------------------------>

void DisplayRound1to4ProgramOFCompanyWiseData(Node1 *Head, string program, string company)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program && Current->company == company)
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

//---------------------------- Helper Function to Display Programwise Data of particluar Company for the Final Round ---------------------------->

void DisplayFinalRoundProgramOFCompanyWiseData(Node2 *Head, string program, string company)
{

    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->program == program && Current->company == company)
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
//------------- Function to Display Programwise Data of a Particular Company for Respective Rounds ---------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayProgramOFCompanyWiseData(int choice, string program, string company)
{

    switch (choice)
    {
    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Company " << company << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFCompanyWiseData(HeadR1, program, company);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Company " << company << "----------------------------------------------->\n";
        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Company " << company << " ---------------------------------------->\n";
        DisplayRound1to4ProgramOFCompanyWiseData(HeadR2, program, company);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Company " << company << " ---------------------------------------------->\n";
        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Company " << company << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFCompanyWiseData(HeadR3, program, company);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Company " << company << " --------------------------------------------->\n";
        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Company " << company << " --------------------------------------->\n";
        DisplayRound1to4ProgramOFCompanyWiseData(HeadR4, program, company);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Company " << company << " --------------------------------------------->\n";
        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Company " << company << " ------------------------------------->\n";
        DisplayFinalRoundProgramOFCompanyWiseData(HeadFR, program, company);
        cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Company " << company << " ------------------------------------------->\n";
        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------- Functions to Write Programwise Data of Particular Company for Respective Rounds in a file ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------- Function to Write Programwise Sorted Data of Particular Company for Rounds 1 to 4 ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFCompanyWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, string company)
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
        if (Current->program == program && Current->company == company)
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
//--------------------- Function to Write Programwise Sorted Data of Particular Company for Final Round ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteProgramOFCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, string company)
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
        if (Current->program == program && Current->company == company)
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
//--------- Function to Sort Programwise Data of a Particular Company for Respective Rounds ----------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataProgramOFCompanyWise()
{

    if (!IsDataInserted())
    {
        cout << "Insufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    string program;
    cout << "\nEnter Program : ";
    getline(cin, program);

    cin.ignore();

    string company;
    cout << "\nEnter Company Name : ";
    getline(cin, company);

    // To find Program and Company is in the data or not

    if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
    {
        cout << "\nStudents of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
        return;
    }

    // To find Program or Company is in the data or not

    if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
    {
        cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
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
            DisplayProgramOFCompanyWiseData(1, program, company);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR1, program, company);

        break;

    case 2:

        char choice2;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayProgramOFCompanyWiseData(2, program, company);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR2, program, company);

        break;

    case 3:

        char choice3;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayProgramOFCompanyWiseData(3, program, company);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR3, program, company);

        break;

    case 4:

        char choice4;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayProgramOFCompanyWiseData(4, program, company);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR4, program, company);

        break;

    case 5:

        char choice5;
        cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayProgramOFCompanyWiseData(5, program, company);

        cout << "\nEnter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteProgramOFCompanyWiseSortedDataForFinalRound(filepath, HeadFR, program, company);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
