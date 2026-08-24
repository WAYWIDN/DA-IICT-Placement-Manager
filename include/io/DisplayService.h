#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class DisplayService
{
private:
    void PrintHorizontalLine(int width, char ch = '-')
    {
        cout << setfill(ch) << setw(width) << "" << setfill(' ') << "\n";
    }

    void PrintHeaderR1to4()
    {
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |"
                "          Email          |   Contact No  |  WhatsApp No  |"
                "      Company       |   Year   |\n";
        PrintHorizontalLine(157);
    }

    void PrintRowR1to4(Record &record)
    {
        cout << "|" << setw(10) << left << record.id
             << "|" << setw(20) << left << record.name
             << "|" << setw(10) << left << record.batch
             << "|" << setw(15) << left << record.program
             << "|" << setw(25) << left << record.email
             << "|" << setw(15) << left << record.contactNO
             << "|" << setw(15) << left << record.whatsappNO
             << "|" << setw(20) << left << record.company
             << "|" << setw(10) << left << record.year << "|\n";
    }

    void PrintHeaderFinalRound()
    {
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |"
                "          Email          |   Contact No  |  WhatsApp No  |"
                "      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);
    }

    void PrintRowFinalRound(Record &record)
    {
        cout << "|" << setw(10) << left << record.id
             << "|" << setw(20) << left << record.name
             << "|" << setw(10) << left << record.batch
             << "|" << setw(15) << left << record.program
             << "|" << setw(25) << left << record.email
             << "|" << setw(15) << left << record.contactNO
             << "|" << setw(15) << left << record.whatsappNO
             << "|" << setw(20) << left << record.company
             << "|" << setw(15) << left << record.package
             << "|" << setw(10) << left << record.year << "|\n";
    }

public:
    void DisplayR1to4(vector<Record> &records, string label)
    {
        cout << "\n<--- " << label << " --->\n";
        PrintHeaderR1to4();
        for (auto &record : records)
        {
            PrintRowR1to4(record);
        }
        PrintHorizontalLine(157);
        cout << "<--- End of " << label << " --->\n";
    }

    void DisplayFinalRound(vector<Record> &records, string label)
    {
        cout << "\n<--- " << label << " --->\n";
        PrintHeaderFinalRound();
        for (auto &record : records)
        {
            PrintRowFinalRound(record);
        }
        PrintHorizontalLine(177);
        cout << "<--- End of " << label << " --->\n";
    }

    void DisplayNotSelected(vector<Record> &records, string label)
    {
        cout << "\n<--- " << label << " --->\n";
        PrintHeaderR1to4();

        for (auto &record : records)
        {
            PrintRowR1to4(record);
        }

        if (records.empty())
            cout << "\n---> Wow !!! All students in this filter are placed <---\n\n";
        PrintHorizontalLine(157);
        cout << "<--- End of " << label << " --->\n";
    }
};

#endif
