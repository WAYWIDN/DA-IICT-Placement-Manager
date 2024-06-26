#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------- Functions to Display CompanyWise Data of Respective Round  ----------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------- Helper Function to Display CompanyWise Data for Round 1 to 4 ------------------------------>

void DisplayRound1to4CompanyWiseData(Node1 *Head, string company)
{
    cout << endl;
    PrintHorizontalLine(157); 
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157); 

    Node1 *Current = Head;

    while (Current != NULL)
    {
        if (Current->company == company)
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

//-------------------------------------- Helper Function to Display CompanyWise Data for Final Round ------------------------------->

void DisplayFinalRoundCompanyWiseData(Node2 *Head, string company)
{
    cout << endl;
    PrintHorizontalLine(177); 
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
    PrintHorizontalLine(177); 

    Node2 *Current = Head;

    while (Current != NULL)
    {
        if (Current->company == company)
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
//--------------------------------- Function to Display CompanyWise Data Round Wise ----------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void DisplayCompanyWiseData(int choice, string company)
{
    switch (choice)
    {

    case 1:

        cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Company " << company << " ---------------------------------------->\n";
        DisplayRound1to4CompanyWiseData(HeadR1, company);
        cout << "\n<-------------------------------------------- End of Data For Round 1 of Company " << company << "----------------------------------------------->\n";

        break;

    case 2:

        cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Company " << company << " ---------------------------------------->\n";
        DisplayRound1to4CompanyWiseData(HeadR2, company);
        cout << "\n<-------------------------------------------- End of Data For Round 2 of Company " << company << " ---------------------------------------------->\n";

        break;

    case 3:

        cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Company " << company << " --------------------------------------->\n";
        DisplayRound1to4CompanyWiseData(HeadR3, company);
        cout << "\n<-------------------------------------------- End of Data For Round 3 of Company " << company << " --------------------------------------------->\n";

        break;

    case 4:

        cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Company " << company << " --------------------------------------->\n";
        DisplayRound1to4CompanyWiseData(HeadR4, company);
        cout << "\n<-------------------------------------------- End of Data For Round 4 of Company " << company << " --------------------------------------------->\n";

        break;

    case 5:

        cout << "\n<-------------------------------------------- Displaying Data For Final Round of Company " << company << " ------------------------------------->\n";
        DisplayFinalRoundCompanyWiseData(HeadFR, company);
        cout << "\n<------------------------------------------ End of Data For Final Round of Company " << company << " ------------------------------------------->\n";

        break;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//-------------------------------------------- Functions to Write CompanyWise Data of Respective Round in file ----------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//-------------------------------------------------------------------------------------------------------------------------->
//---------------------------------- Function to Write CompanyWise Sorted Data of Round 1 to 4 ----------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteCompanyWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string company)
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
        if (Current->company == company)
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
//--------------------------------- Function to Write CompanyWise Sorted Data of Final Round ------------------------------->
//-------------------------------------------------------------------------------------------------------------------------->

void WriteCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string company)
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
        if (Current->company == company)
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
//-------------------------------------- Function to Sort Data Company Wise ------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataCompanyWise()
{

    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , please insert Data and Try agian \nThank You\n\n";
        return;
    }

    string company;
    cout << "\nEnter Company Name : ";
    getline(cin, company);

    // Find Company is in Data or Not
    
    if (R1CompanyAttempts[company] == 0)
    {
        cout << "\nStudents of Company " << company << " does not found , Enter Valid Company and Try Again \n\n";
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
            DisplayCompanyWiseData(1, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR1, company);

        break;

    case 2:

        char choice2;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice2;

        if (choice2 == 'Y')
            DisplayCompanyWiseData(2, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR2, company);

        break;

    case 3:

        char choice3;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice3;

        if (choice3 == 'Y')
            DisplayCompanyWiseData(3, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR3, company);

        break;

    case 4:

        char choice4;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice4;

        if (choice4 == 'Y')
            DisplayCompanyWiseData(4, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR4, company);

        break;

    case 5:

        char choice5;
        cout << "\nDo you to Display Data(Y/N) ? \nAns : ";
        cin >> choice5;

        if (choice5 == 'Y')
            DisplayCompanyWiseData(5, company);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteCompanyWiseSortedDataForFinalRound(filepath, HeadFR, company);

        break;

    default:

        cout << "\nInvalid Choice \n\n";
    }
}
