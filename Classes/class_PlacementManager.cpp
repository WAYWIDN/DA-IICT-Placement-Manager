#include <iostream>
#include <string>
#include "Classes/class_PlacementManager.cpp"
using namespace std;

void displayMainMenu()
{
    cout << "\n\n<-------------------------------------------> Placement Management System Menu <--------------------------------------->\n";
    cout << "\n\n-------> Please select an option from the menu below : " << endl;
    cout << "\n1. Input Placement Data\n";
    cout << "2. Sort Data\n";
    cout << "3. View Placement Statistics\n";
    cout << "4. View Not Selected Students\n";
    cout << "5. Exit\n";
    cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n";
    cout << "\nEnter your choice: ";
}

void displaySortMenu(PlacementManager &p)
{
    cout << "\n\n<---------------------------------------------------> Sort Data Menu <------------------------------------------------->\n";
    cout << "\n\n-------> Please select an option from the menu below : " << endl;
    cout << "\n1. Sort Whole Data\n";
    cout << "2. Sort Data Batch Wise\n";
    cout << "3. Sort Data Program Wise\n";
    cout << "4. Sort Data Year Wise\n";
    cout << "5. Sort Data Company Wise\n";
    cout << "6. Sort Data Batch and Company Wise\n";
    cout << "7. Sort Data Program of Batch Wise\n";
    cout << "8. Sort Data Program of Company Wise\n";
    cout << "9. Sort Data Program of Year Wise\n";
    cout << "10. Sort Data Year and Batch Wise\n";
    cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n";
    cout << "\nEnter your choice: ";

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortWholeData();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";

        break;

    case 2:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataBatchWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 3:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataProgramWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 4:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataYearWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 5:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 6:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataBatchAndCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 7:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataProgramOFBatchWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 8:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataProgramOFCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 9:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataProgramOFYearWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 10:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.SortDataYearAndBatchWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    default:

        cout << "\n<-------------------------- Invalid choice! -------------------->\n\n";
        break;
    }
}

void displayStatisticsMenu(PlacementManager &p)
{
    cout << "\n\n<---------------------------------------------> View Placement Statistics Menu <---------------------------------------->\n";
    cout << "\n\n-------> Please select an option from the menu below : " << endl;
    cout << "\n1. Overall Placement Statistics\n";
    cout << "2. Student Placement Details\n";
    cout << "3. Batch Wise Placement Statistics\n";
    cout << "4. Program Wise Placement Statistics\n";
    cout << "5. Company Wise Placement Statistics\n";
    cout << "6. Year Wise Placement Statistics\n";
    cout << "7. Batch and Company Wise Placement Statistics\n";
    cout << "8. Program and Batch Wise Placement Statistics\n";
    cout << "9. Program and Company Wise Placement Statistics\n";
    cout << "10. Year and Batch Wise Placement Statistics\n";
    cout << "11. Year and Company Wise Placement Statistics\n";
    cout << "12. Year and Program Wise Placement Statistics\n";
    cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n";
    cout << "\nEnter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindOverallPlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 2:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindStudentPlacementDetails();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 3:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindBatchWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 4:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindProgramWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 5:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindCompanyWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 6:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindYearWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 7:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindBatchAndCompanyWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 8:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindProgramAndBatchWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 9:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindProgramAndCompanyWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 10:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindYearAndBatchWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 11:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindYearAndCompanyWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 12:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindYearAndProgramWisePlacementStatistics();
        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    default:
        cout << "\n<-------------------------- Invalid choice! -------------------->\n\n";
        break;
    }
}

void displayNotSelectedMenu(PlacementManager &p)
{

    cout << "\n\n<--------------------------------------------> View Not Selected Students Menu <--------------------------------------->\n";
    cout << "\n\n-------> Please select an option from the menu below : " << endl;
    cout << "\n1. Not Selected Batch Wise\n";
    cout << "2. Not Selected Program Wise\n";
    cout << "3. Not Selected Company Wise\n";
    cout << "4. Not Selected Year Wise\n";
    cout << "5. Not Selected Batch and Program Wise\n";
    cout << "6. Not Selected Batch and Company Wise\n";
    cout << "7. Not Selected Company and Program Wise\n";
    cout << "8. Not Selected Year and Batch Wise\n";
    cout << "9. Not Selected Year and Program Wise\n";
    cout << "10. Not Selected Year and Company Wise\n";
    cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n";
    cout << "\nEnter your choice: ";

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedBatchWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 2:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedProgramWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 3:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 4:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedYearWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 5:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedBatchAndProgramWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 6:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedBatchAndCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 7:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedCompanyAndProgramWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 8:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedYearAndBatchWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 9:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedYearAndProgramWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    case 10:

        cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        p.FindNotSelectedYearAndCompanyWise();
        cout << "<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
        break;

    default:

        cout << "\n<-------------------------- Invalid choice! -------------------->\n\n";
        break;
    }
}

int main()
{
    PlacementManager p;

    int choice;

    cout << "\n*******************************************************************************************************************************************************" << endl;
    cout << "*************************************************************                              ************************************************************" << endl;
    cout << "*********************************************************       Welcome to the Placement        *******************************************************" << endl;
    cout << "************************************************                   Management System!                   ***********************************************" << endl;
    cout << "*********************************************************                                       *******************************************************" << endl;
    cout << "*************************************************************                              ************************************************************" << endl;
    cout << "*******************************************************************************************************************************************************" << endl;

    do
    {
        displayMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:

            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n\n";
            p.InputPlacementData();
            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
            break;

        case 2:

            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n\n";
            displaySortMenu(p);

            break;

        case 3:

            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n\n";
            displayStatisticsMenu(p);
            break;

        case 4:

            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n\n";
            displayNotSelectedMenu(p);
            break;

        case 5:

            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n";
            cout << "\n<------------------------------------------------- Exiting the program. Goodbye! -------------------------------------->\n";
            cout << "\n<-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x-------x------>\n\n";
            break;

        default:
            cout << "\n<-------------------------- Invalid choice! -------------------->\n\n";
        }

    } while (choice != 5);

    return 0;
}
