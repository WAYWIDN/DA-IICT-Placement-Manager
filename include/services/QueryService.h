#ifndef QUERY_SERVICE_H
#define QUERY_SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include "../data/Repository.h"
#include "../models/Query.h"
#include "../io/CSVService.h"
#include "../io/DisplayService.h"

using namespace std;

class QueryService
{
private:
    Repository &repo;
    CSVService csvService;
    DisplayService displayService;

    void DisplayR1to4(AVLTree<long long, Record> &tree, Query &q, string label)
    {
        vector<Record> records;
        repo.CollectRecords(tree, q, records);
        displayService.DisplayR1to4(records, label);
    }

    void DisplayFR(Query &q, string label)
    {
        vector<Record> records;
        repo.CollectRecords(repo.GetFR(), q, records);
        displayService.DisplayFinalRound(records, label);
    }

    void WriteR1to4(AVLTree<long long, Record> &tree, Query &q, string filepath)
    {
        vector<Record> records;
        repo.CollectRecords(tree, q, records);
        csvService.WriteR1to4(records, filepath);
    }

    void WriteFR(Query &q, string filepath)
    {
        vector<Record> records;
        repo.CollectRecords(repo.GetFR(), q, records);
        csvService.WriteFinalRound(records, filepath);
    }

    void AskAndSortR1to4(AVLTree<long long, Record> &tree, Query &q, string displayLabel)
    {
        char ch;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> ch;

        if (ch == 'Y')
            DisplayR1to4(tree, q, displayLabel);

        cin.ignore();

        string fp;
        cout << "\n#-----> Enter File Path to store Sorted Data : ";
        getline(cin, fp);

        WriteR1to4(tree, q, fp);
    }

    void AskAndSortFR(Query &q, string displayLabel)
    {
        char ch;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> ch;

        if (ch == 'Y')
            DisplayFR(q, displayLabel);

        cin.ignore();

        string fp;
        cout << "\n#-----> Enter File Path to store Sorted Data : ";
        getline(cin, fp);

        WriteFR(q, fp);
    }

    void SortByRound(Query &q, string filterDesc, bool showTotal = false)
    {
        cout << "\n#-----> Enter 1/2/3/4 for Round 1-4, or 5 for Final Round : ";
        int choice;
        cin >> choice;

        auto label = [&](int r)
        {
            return "Data For Round " + to_string(r) + " - " + filterDesc;
        };

        auto showRoundTotal = [&](AVLTree<long long, Record> &tree, int round)
        {
            if (showTotal)
            {
                cout << "\n<--- Displaying All Data For Round " << round
                     << " (Total: " << repo.CountInTree(tree, q) << ") --->\n";
            }
        };

        switch (choice)
        {
        case 1:
            showRoundTotal(repo.GetR1(), 1);
            AskAndSortR1to4(repo.GetR1(), q, label(1));
            break;
        case 2:
            showRoundTotal(repo.GetR2(), 2);
            AskAndSortR1to4(repo.GetR2(), q, label(2));
            break;
        case 3:
            showRoundTotal(repo.GetR3(), 3);
            AskAndSortR1to4(repo.GetR3(), q, label(3));
            break;
        case 4:
            showRoundTotal(repo.GetR4(), 4);
            AskAndSortR1to4(repo.GetR4(), q, label(4));
            break;
        case 5:
            if (showTotal)
                cout << "\n<--- Displaying All Data For Final Round (Total: "
                     << repo.CountInTree(repo.GetFR(), q) << ") --->\n";
            AskAndSortFR(q, "Final Round - " + filterDesc);
            break;
        default:
            cout << "\n<--- Invalid Choice --->\n\n";
        }
    }

    void AskAndWriteNotSelected(Query &q, string label)
    {
        char ch;
        cout << "\n#-----> Display Data(Y/N)? ";
        cin >> ch;
        vector<Record> records;
        repo.CollectRecords(repo.GetR1(), q, records);
        vector<Record> notSelectedRecords;
        for (auto &record : records)
        {
            if (repo.GetOfferCount(record.id) == 0)
                notSelectedRecords.push_back(record);
        }

        if (ch == 'Y')
            displayService.DisplayNotSelected(notSelectedRecords, label);

        cin.ignore();

        string fp;
        cout << "\n#-----> Enter File Path : ";
        getline(cin, fp);
        csvService.WriteR1to4(notSelectedRecords, fp);
    }

public:
    QueryService(Repository &repo) : repo(repo) {}

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //----------------------------------------------------> Sorting Functions <----------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void SortWholeData()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data. Insert Data and Try Again.\n\n";
            return;
        }

        Query q; // empty query = match all
        cout << "\n#-----> Enter 1/2/3/4 for Round 1-4, or 5 for Final Round : ";
        int choice;
        cin >> choice;

        SortByRound(q, "All Data", true);
    }

    void SortDataBatchWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        Query q;
        q.setBatch(batch);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch not found.\n\n";
            return;
        }

        SortByRound(q, "Batch " + to_string(batch));
    }

    void SortDataProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();
        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Program not found.\n\n";
            return;
        }

        SortByRound(q, "Program " + program);
    }

    void SortDataYearWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        Query q;
        q.setYear(year);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year not found.\n\n";
            return;
        }

        SortByRound(q, "Year " + to_string(year));
    }

    void SortDataCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();
        string company;
        cout << "\n#-----> Enter Company Name : ";
        getline(cin, company);

        Query q;
        q.setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Company not found.\n\n";
            return;
        }

        SortByRound(q, "Company " + company);
    }

    void SortDataBatchAndProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setBatch(batch).setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch+Program not found.\n\n";
            return;
        }

        SortByRound(q, "Batch " + to_string(batch) + " Program " + program);
    }

    void SortDataBatchAndCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setBatch(batch).setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch+Company not found.\n\n";
            return;
        }

        SortByRound(q, "Batch " + to_string(batch) + " Company " + company);
    }

    void SortDataProgramAndCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setProgram(program).setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Program+Company not found.\n\n";
            return;
        }

        SortByRound(q, "Program " + program + " Company " + company);
    }

    void SortDataYearAndBatchWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        Query q;
        q.setYear(year).setBatch(batch);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Batch not found.\n\n";
            return;
        }

        SortByRound(q, "Year " + to_string(year) + " Batch " + to_string(batch));
    }

    void SortDataYearAndProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setYear(year).setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Program not found.\n\n";
            return;
        }

        SortByRound(q, "Year " + to_string(year) + " Program " + program);
    }

    void SortDataYearAndCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setYear(year).setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Company not found.\n\n";
            return;
        }

        SortByRound(q, "Year " + to_string(year) + " Company " + company);
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------------------------> Not-Selected Student Functions <------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void FindNotSelectedBatchWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        Query q;
        q.setBatch(batch);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Batch " + to_string(batch));
    }

    void FindNotSelectedProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Program not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Program " + program);
    }

    void FindNotSelectedCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Company not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Company " + company);
    }

    void FindNotSelectedYearWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        Query q;
        q.setYear(year);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Year " + to_string(year));
    }

    void FindNotSelectedBatchAndCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setBatch(batch).setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch+Company not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Batch " + to_string(batch) + " Company " + company);
    }

    void FindNotSelectedBatchAndProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setBatch(batch).setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Batch+Program not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Batch " + to_string(batch) + " Program " + program);
    }

    void FindNotSelectedCompanyAndProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setCompany(company).setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Company+Program not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Company " + company + " Program " + program);
    }

    void FindNotSelectedYearAndBatchWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        Query q;
        q.setYear(year).setBatch(batch);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Batch not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Year " + to_string(year) + " Batch " + to_string(batch));
    }

    void FindNotSelectedYearAndProgramWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        Query q;
        q.setYear(year).setProgram(program);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Program not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Year " + to_string(year) + " Program " + program);
    }

    void FindNotSelectedYearAndCompanyWise()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        Query q;
        q.setYear(year).setCompany(company);

        if (!repo.IsInData(q))
        {
            cout << "\n-----> Year+Company not found.\n\n";
            return;
        }

        AskAndWriteNotSelected(q, "Not Selected - Year " + to_string(year) + " Company " + company);
    }
};

#endif
