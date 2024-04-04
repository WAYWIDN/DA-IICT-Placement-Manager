#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "InputPlacementData.cpp"
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------- Functions to Display BatchWise Data of Respective Round of particular Batch --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //---------------------------------------Helper Function to Display BatchWise Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4BatchWiseData(Node1 *Head, int batch)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool batch_found = false;

        while (Current != NULL)
        {
            if (Current->batch == batch)
            {
                batch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!batch_found)
            cout << "\nStudents of Batch " << batch << "  does not found , Enter Valid Batch and Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //---------------------------------------Helper Function to Display BatchWise Data for Final Round ------------------------------->

    void DisplayFinalRoundBatchWiseData(Node2 *Head, int batch)
    {
        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool batch_found = false;

        while (Current != NULL)
        {
            if (Current->batch == batch)
            {
                batch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!batch_found)
            cout << "\nStudents of Batch " << batch << "  does not found , Enter Valid Batch and Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Display BatchWise Data Round Wise -------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayBatchWiseData(int choice, int batch)
    {
        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Batch " << batch << " ------------------------------------>\n";
            DisplayRound1to4BatchWiseData(HeadR1, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 1 " << batch << " --------------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Batch " << batch << " -------------------------------------->\n";
            DisplayRound1to4BatchWiseData(HeadR2, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Batch " << batch << " -------------------------------------------->\n";

            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4BatchWiseData(HeadR3, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Batch" << batch << " ---------------------------------------------->\n";

            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4BatchWiseData(HeadR4, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Batch " << batch << " --------------------------------------------->\n";

            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Batch " << batch << " ------------------------------------->\n";
            DisplayFinalRoundBatchWiseData(HeadFR, batch);
            cout << "\n<------------------------------------------ End of Data For Final Round of Batch " << batch << " ------------------------------------------->\n";

            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------------------------- Functions to Write BatchWise Data of Respective Round in file ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Write BatchWise Sorted Data of Round 1 to 4 ----------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int batch)
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

        bool batch_found = false;

        while (Current != nullptr)
        {
            if (Current->batch == batch)
            {
                batch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!batch_found)
            cout << "\nStudents of Batch " << batch << "  does not found , Enter Valid Batch and Try Again \n";
        else
            cout << "\nData Written Successfully....\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Write BatchWise Sorted Data of Final Round ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int batch)
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

        bool batch_found = false;

        while (Current != nullptr)
        {
            if (Current->batch == batch)
            {
                batch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!batch_found)
            cout << "\nStudents of Batch " << batch << "  does not found , Enter Valid Batch and Try Again \n";
        else
            cout << "\nData Written Successfully....\n";

        outputFile.close();
    }

//--------------------------------------------------------------------------------------------------------------------->
//-------------------------------------- Function to Sort Whole Data Batch Wise --------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

void SortDataBatchWise()
{

    int batch;
    cout << "\nEnter Batch : ";
    cin >> batch;

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
            DisplayBatchWiseData(1, batch);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchWiseSortedDataForRound1to4(filepath, HeadR1, batch);

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
            DisplayBatchWiseData(2, batch);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchWiseSortedDataForRound1to4(filepath, HeadR2, batch);

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
            DisplayBatchWiseData(3, batch);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchWiseSortedDataForRound1to4(filepath, HeadR3, batch);

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
            DisplayBatchWiseData(4, batch);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchWiseSortedDataForRound1to4(filepath, HeadR4, batch);

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
            DisplayBatchWiseData(5, batch);

        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteBatchWiseSortedDataForFinalRound(filepath, HeadFR, batch);

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


    SortDataBatchWise();

    return 0;
}