#include <iostream>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

// Helper function to print a horizontal line

//--------------------------------------------------------------------------------------------------------------------->
//---------------------------------------Function to Display Placement Data ------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

// Helper function to display data for rounds 1-4
void DisplayRound1to4Data(Node1 *Head)
{
    cout << endl;
    PrintHorizontalLine(147); // Printing horizontal line
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |\n";
    PrintHorizontalLine(147); // Printing horizontal line
    Node1 *Current = Head;
    while (Current != NULL)
    {
        cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
             << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
             << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << endl;
        Current = Current->next;
    }
}

// Helper function to display data for final round
void DisplayFinalRoundData(Node2 *Head)
{
    cout << "\nFinal Round:\n\n";
    PrintHorizontalLine(157); // Printing horizontal line
    cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package   |\n";
    PrintHorizontalLine(157); // Printing horizontal line
    Node2 *Current = Head;
    while (Current != NULL)
    {
        cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
             << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
             << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left<< "|" << endl;
        Current = Current->next;
    }
}

void DisplayPlacementData()
{
    cout << "\n----------------------------------------------- Displaying Placement Data For Round 1 ----------------------------------------------\n";
    cout << "Total number of students in Round 1: " << NOofStudentR1 << endl;
    DisplayRound1to4Data(HeadR1);
    cout << "\n--------------------------------------------- End of Placement Data For Round 1 ----------------------------------------------------\n";

    cout << "\n----------------------------------------------- Displaying Placement Data For Round 2 ----------------------------------------------\n";
    cout << "\nTotal number of students in Round 2: " << NOofStudentR2 << endl;
    DisplayRound1to4Data(HeadR2);
    cout << "\n--------------------------------------------- End of Placement Data For Round 2 ----------------------------------------------------\n";

    cout << "\n----------------------------------------------- Displaying Placement Data For Round 3 ----------------------------------------------\n";
    cout << "\nTotal number of students in Round 3: " << NOofStudentR3 << endl;
    DisplayRound1to4Data(HeadR3);
    cout << "\n--------------------------------------------- End of Placement Data For Round 3 ----------------------------------------------------\n";

    cout << "\n----------------------------------------------- Displaying Placement Data For Round 4 ----------------------------------------------\n";
    cout << "\nTotal number of students in Round 4: " << NOofStudentR4 << endl;
    DisplayRound1to4Data(HeadR4);
    cout << "\n--------------------------------------------- End of Placement Data For Round 4 ----------------------------------------------------\n";

    cout << "\n--------------------------------------------- Displaying Placement Data For Final Round --------------------------------------------\n";
    cout << "\nTotal number of students who got offers " << NOofStudentFR << endl;
    DisplayFinalRoundData(HeadFR);
    cout << "\n------------------------------------------- End of Placement Data For Final Round --------------------------------------------------\n";
}

int main()
{
    ReadFileForRound1("Input Files/Company6R1.csv", "Apple");
    ReadFileForRound2("Input Files/Company6R1.csv", "Apple");
    ReadFileForRound3("Input Files/Company6R1.csv", "Apple");
    ReadFileForRound4("Input Files/Company6R1.csv", "Apple");
    ReadFileForFinalRound("Input Files/Company6FR.csv", "Apple");
    SortWholeData();
    DisplayPlacementData();
    return 0;
}
