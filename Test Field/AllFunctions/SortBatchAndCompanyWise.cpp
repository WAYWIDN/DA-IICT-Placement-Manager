#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------------- Functions to Display Batchwise Data of a Particular Company for Respective Rounds ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//------------------------- Helper Function to Display Batchwise Data of particular Company for Rounds 1 to 4 ------------------------------>

void DisplayBatchOFCompanyWiseDataForRound1to4(Node1 *Head, int batch, string company)
{
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = Head;

    while (Current != nullptr)
    {
        if (Current->batch == batch && Current->company == company)
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

//---------------------------- Helper Function to Display Batchwise Data of particluar Company for the Final Round ---------------------------->

void DisplayBatchOFCompanyWiseDataForFinalRound(Node2 *Head, int batch, string company)
{
    cout << endl;
    PrintHorizontalLine(177);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177);

    Node2 *Current = Head;

    while (Current != nullptr)
    {
        if (Current->batch == batch && Current->company == company)
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
//------------- Function to Display Batchwise Data of a Particular Company for Respective Rounds ---------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayBatchOFCompanyWiseData(int roundChoice, int batch, string company)
{
    switch (roundChoice)
    {
    case 1:
        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
        DisplayBatchOFCompanyWiseDataForRound1to4(HeadR1, batch, company);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Batch " << batch << " and Company " << company << "----------------------------------------------->\n";
        break;
    case 2:
        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
        DisplayBatchOFCompanyWiseDataForRound1to4(HeadR2, batch, company);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Batch " << batch << " and Company " << company << " ---------------------------------------------->\n";
        break;
    case 3:
        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Batch " << batch << " and Company " << company << " --------------------------------------->\n";
        DisplayBatchOFCompanyWiseDataForRound1to4(HeadR3, batch, company);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Batch " << batch << " and Company " << company << " --------------------------------------------->\n";
        break;
    case 4:
        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Batch " << batch << " and Company " << company << " --------------------------------------->\n";
        DisplayBatchOFCompanyWiseDataForRound1to4(HeadR4, batch, company);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Batch " << batch << " and Company " << company << " --------------------------------------------->\n";
        break;
    case 5:
        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Batch " << batch << " and Company " << company << " ------------------------------------->\n";
        DisplayBatchOFCompanyWiseDataForFinalRound(HeadFR, batch, company);
        cout << "\n<------------------------------------------ End of Data For Final Round of Batch " << batch << " and Company " << company << " ------------------------------------------->\n";
        break;
    default:
        cout << "\nInvalid Choice \n\n";
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//--------------------- Functions to Write Batchwise Data of Particular Company for Respective Rounds in a file ---------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//------------------- Function to Write Batchwise Sorted Data of Particular Company for Rounds 1 to 4 ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteBatchOFCompanyWiseSortedDataForRound1To4(const string &filepath, Node1 *Head, int batch, string company)
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
        if (Current->batch == batch && Current->company == company)
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
//--------------------- Function to Write Batchwise Sorted Data of Particular Company for Final Round ---------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteBatchOFCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int batch, string company)
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
        if (Current->batch == batch && Current->company == company)
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
//------------- Function to Sort Batchwise Data of a Particular Company for Respective Rounds ------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataBatchAndCompanyWise()
{

    if (!IsDataInserted())
    {
        cout << "\nInsufficient data Inserted,please insert Data and Try agian \nThank You\n\n";
        return;
    }

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

    cin.ignore();

    string company;
    cout << "\nEnter Company Name : ";
    getline(cin, company);

    // Find Batch and Company is in Data or Not

    if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
    {
        cout << "\nStudents of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
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
            DisplayBatchOFCompanyWiseData(1, batch, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR1, batch, company);

        break;

    case 2:

        char choice2;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayBatchOFCompanyWiseData(2, batch, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR2, batch, company);

        break;

    case 3:

        char choice3;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayBatchOFCompanyWiseData(3, batch, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR3, batch, company);

        break;

    case 4:

        char choice4;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayBatchOFCompanyWiseData(4, batch, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR4, batch, company);
        break;

    case 5:

        char choice5;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayBatchOFCompanyWiseData(5, batch, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchOFCompanyWiseSortedDataForFinalRound(filepath, HeadFR, batch, company);

        break;

    default:

        cout << "\nInvalid Choice \n";
    }
}
