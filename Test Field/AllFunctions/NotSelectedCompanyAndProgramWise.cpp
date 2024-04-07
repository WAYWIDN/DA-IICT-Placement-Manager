#include <iostream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------->
//------------------------ Function to Display Not Selected Students ProgramWise of particular Company -------------------->
//------------------------------------------------------------------------------------------------------------------------->

void DisplayNotSelectedCompanyAndProgramWise(string company, string program)
{
    cout << "\n<-------------------------------------- Displaying Not Selected Students of Program " << program << " and Company " << company << "------------------------------------->\n";
    cout << endl;
    PrintHorizontalLine(157);
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
    PrintHorizontalLine(157);

    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->program == program && Current->company == company && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Company " << company << " are placed <---------------------------\n\n";
    }

    PrintHorizontalLine(157);
    cout << "\n<----------------------------------- End of Not Selected Students of Program " << program << " and Company " << company << " ------------------------------------------->\n";
}

//------------------------------------------------------------------------------------------------------------------------->
//---------------------- Function to Write Not Selected Students ProgramWise of particular Company ------------------------>
//------------------------------------------------------------------------------------------------------------------------->

void WriteNotSelectedCompanyAndProgramWise(const string &filepath, string company, string program)
{
    ofstream outputFile(filepath);

    if (!outputFile.is_open())
    {
        cerr << "\nError in Opening File for Writing Data\n\n";
        return;
    }

    outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

    int i = 1;
    Node1 *Current = HeadR1;

    bool Success = false;

    while (Current != NULL)
    {
        if (Current->program == program && Current->company == company && TotalStudnetOffers[Current->id] == 0)
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
        cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Company " << company << " are placed <---------------------------\n\n";
    }
    else
    {
        cout << "\nData Written Successfully....\n\n";
    }
    outputFile.close();
}

//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//---------------------- Function to Find Not Selected Students ProgramWise of particular Company ------------------------->
//------------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------->

void FindNotSelectedCompanyAndProgramWise()
{
    if (!IsDataInserted())
    {
        cout << "\nInsufficient Data Inserted , Insert Data and Try Again \nThank You \n\n";
        return;
    }

    string company;
    cout << "\nEnter Company : ";
    getline(cin, company);

    string program;
    cout << "\nEnter Program : ";
    getline(cin, program);

    // Find Program or Company is in Data or Not

    if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
    {
        cout << "\nStudents of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
        return;
    }

    // Find Program And Company is in Data or Not

    if (!IsProgramAndCompanyInData(program, company))
    {
        cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
        return;
    }

    char choice1;
    cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
    cin >> choice1;

    if (choice1 == 'Y')
        DisplayNotSelectedCompanyAndProgramWise(company, program);

    string filepath;
    cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
    cin >> filepath;

    WriteNotSelectedCompanyAndProgramWise(filepath, company, program);
}
