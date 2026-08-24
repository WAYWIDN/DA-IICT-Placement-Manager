#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <iostream>
#include <fstream>
#include <string>
#include "../data/Repository.h"
#include "./CSVService.h"

using namespace std;

class FileService
{
private:
    Repository &repo;
    CSVService csvService;

    bool IsValidFilePath(string &filepath)
    {
        ifstream file(filepath);

        if (!file.is_open())
            return false;

        file.close();
        return true;
    }

public:
    FileService(Repository &repo) : repo(repo) {}

    void LoadCompanyData()
    {
        cin.ignore();

        string company;

        cout << "\n#-----> Enter Company Name : ";
        getline(cin, company);

        string r1Path;
        string r2Path;
        string r3Path;
        string r4Path;
        string frPath;

        cout << "\n#-----> Enter Round 1 File Path : ";
        getline(cin, r1Path);

        cout << "\n#-----> Enter Round 2 File Path : ";
        getline(cin, r2Path);

        cout << "\n#-----> Enter Round 3 File Path : ";
        getline(cin, r3Path);

        cout << "\n#-----> Enter Round 4 File Path : ";
        getline(cin, r4Path);

        cout << "\n#-----> Enter Final Round File Path : ";
        getline(cin, frPath);

        bool valid = true;

        if (!IsValidFilePath(r1Path))
        {
            cout << "\n-----> Invalid Round 1 File Path.";
            valid = false;
        }

        if (!IsValidFilePath(r2Path))
        {
            cout << "\n-----> Invalid Round 2 File Path.";
            valid = false;
        }

        if (!IsValidFilePath(r3Path))
        {
            cout << "\n-----> Invalid Round 3 File Path.";
            valid = false;
        }

        if (!IsValidFilePath(r4Path))
        {
            cout << "\n-----> Invalid Round 4 File Path.";
            valid = false;
        }

        if (!IsValidFilePath(frPath))
        {
            cout << "\n-----> Invalid Final Round File Path.";
            valid = false;
        }

        if (!valid)
        {
            cout << "\n\n-----> Invalid file path(s).";
            cout << "\n-----> No data has been inserted.\n\n";

            return;
        }

        cout << "\n-----> All file paths are valid.";
        cout << "\n-----> Loading data...\n";

        csvService.ReadFileForRound(repo.GetR1(), r1Path, company, "Round 1");
        csvService.ReadFileForRound(repo.GetR2(), r2Path, company, "Round 2");
        csvService.ReadFileForRound(repo.GetR3(), r3Path, company, "Round 3");
        csvService.ReadFileForRound(repo.GetR4(), r4Path, company, "Round 4");
        csvService.ReadFileForFinalRound(repo.GetFR(), frPath, company);

        cout << "\n-----> All data loaded successfully.\n";
    }
};

#endif
