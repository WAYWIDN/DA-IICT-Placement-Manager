#ifndef CSV_SERVICE_H
#define CSV_SERVICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include "../models/Record.h"
#include "../ds/AVLTree.h"

using namespace std;

class CSVService
{
private:
    bool IsValidInputPath(string filepath)
    {
        if (filepath.empty())
            return false;

        ifstream file(filepath);
        return file.is_open();
    }

    bool IsValidOutputPath(string filepath)
    {
        if (filepath.empty())
            return false;

        ofstream file(filepath, ios::app);
        return file.is_open();
    }

    void PrintHorizontalLine(int width, char ch = '-')
    {
        cout << setfill(ch) << setw(width) << "" << setfill(' ') << "\n";
    }

public:
    void ReadFileForRound(AVLTree<long long, Record> &tree, string filepath, string company, string roundLabel)
    {
        if (!IsValidInputPath(filepath))
        {
            PrintHorizontalLine(115);
            cerr << "\n-----> Invalid " << roundLabel << " file path for " << company << "\n\n";
            PrintHorizontalLine(115);
            return;
        }

        ifstream file(filepath);
        if (!file.is_open())
        {
            PrintHorizontalLine(115);
            cerr << "\n-----> Error opening " << roundLabel << " file of " << company << "\n\n";
            PrintHorizontalLine(115);
            return;
        }

        // cout << "\n---> Fetching " << roundLabel << " data for " << company << " ...\n";
        string line;
        getline(file, line); // skip header

        while (getline(file, line))
        {
            stringstream ss(line);
            string skip, id_str, name, program, email, cno_str, wno_str, date_str;

            getline(ss, skip, ',');
            getline(ss, id_str, ',');
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, date_str, ',');
            getline(ss, email, ',');
            getline(ss, cno_str, ',');
            getline(ss, wno_str, ',');

            Record r;
            r.id = stoll(id_str);
            r.batch = stoi(id_str.substr(0, 4));
            r.name = name;
            r.program = program;
            r.year = stoi(date_str.substr(6, 4));
            r.email = email;
            r.contactNO = stoll(cno_str);
            r.whatsappNO = stoll(wno_str);
            r.company = company;
            r.package = 0;

            tree.insert(r.id, r);
        }
        file.close();
        // cout << "<--- Done: " << roundLabel << " for " << company << " <---\n\n";
    }

    void ReadFileForFinalRound(AVLTree<long long, Record> &tree, string filepath, string company)
    {
        if (!IsValidInputPath(filepath))
        {
            PrintHorizontalLine(115);
            cerr << "\n-----> Invalid Final Round file path for " << company << "\n\n";
            PrintHorizontalLine(115);
            return;
        }

        ifstream file(filepath);
        if (!file.is_open())
        {
            PrintHorizontalLine(115);
            cerr << "\n-----> Error opening Final Round file of " << company << "\n\n";
            PrintHorizontalLine(115);
            return;
        }

        // cout << "\n---> Fetching Final Round data for " << company << " ...\n";
        string line;
        getline(file, line); // skip header

        while (getline(file, line))
        {
            stringstream ss(line);
            string skip, id_str, name, program, email, cno_str, wno_str, pkg_str, date_str;

            getline(ss, skip, ',');
            getline(ss, id_str, ',');
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, date_str, ',');
            getline(ss, email, ',');
            getline(ss, cno_str, ',');
            getline(ss, wno_str, ',');
            getline(ss, pkg_str, ',');

            Record r;
            r.id = stoll(id_str);
            r.batch = stoi(id_str.substr(0, 4));
            r.name = name;
            r.program = program;
            r.year = stoi(date_str.substr(6, 4));
            r.email = email;
            r.contactNO = stoll(cno_str);
            r.whatsappNO = stoll(wno_str);
            r.company = company;
            r.package = stof(pkg_str);

            tree.insert(r.id, r);
        }
        file.close();
        // cout << "<--- Done: Final Round for " << company << " <---\n\n";
    }

    void WriteR1to4(vector<Record> &records, string filepath)
    {
        if (!IsValidOutputPath(filepath))
        {
            cerr << "\n-----> Invalid output file path\n\n";
            return;
        }

        ofstream file(filepath);
        if (!file.is_open())
        {
            cerr << "\n-----> Error opening file for writing\n\n";
            return;
        }

        file << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";
        int serialNumber = 1;
        for (auto &record : records)
        {
            file << serialNumber++ << "," << record.id << "," << record.name << ","
                 << record.batch << "," << record.program << "," << record.email << ","
                 << record.contactNO << "," << record.whatsappNO << ","
                 << record.company << "," << record.year << "\n";
        }

        cout << "\n-----> Data Written Successfully....\n\n";
    }

    void WriteFinalRound(vector<Record> &records, string filepath)
    {
        if (!IsValidOutputPath(filepath))
        {
            cerr << "\n-----> Invalid output file path\n\n";
            return;
        }

        ofstream file(filepath);
        if (!file.is_open())
        {
            cerr << "\n-----> Error opening file for writing\n\n";
            return;
        }

        file << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";
        int serialNumber = 1;
        for (auto &record : records)
        {
            file << serialNumber++ << "," << record.id << "," << record.name << ","
                 << record.batch << "," << record.program << "," << record.email << ","
                 << record.contactNO << "," << record.whatsappNO << ","
                 << record.company << "," << record.package << "," << record.year << "\n";
        }

        cout << "\n-----> Data Written Successfully....\n\n";
    }
};

#endif
