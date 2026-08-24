#ifndef STATISTICS_SERVICE_H
#define STATISTICS_SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "../data/Repository.h"
#include "../models/Query.h"

using namespace std;

class StatisticsService
{
private:
    Repository &repo;

    struct PkgStats
    {
        float min, max, total;
        int count;
        vector<float> list;
    };

    void PrintHorizontalLine(int width, char ch = '-')
    {
        cout << setfill(ch) << setw(width) << "" << setfill(' ') << "\n";
    }

    PkgStats CalcPkgStats(Query &q)
    {
        PkgStats s{numeric_limits<float>::max(), numeric_limits<float>::lowest(), 0, 0, {}};
        vector<Record> all;
        repo.CollectRecords(repo.GetFR(), q, all);
        for (auto &r : all)
        {
            s.count++;
            s.total += r.package;
            if (r.package < s.min)
                s.min = r.package;
            if (r.package > s.max)
                s.max = r.package;
            s.list.push_back(r.package);
        }
        return s;
    }

    void PrintPkgStats(PkgStats &s, int r1att, int r2att, int r3att, int r4att, string label)
    {
        PrintHorizontalLine(60);
        cout << "\n# Placement Statistics - " << label << " :\n";
        cout << "\nNo. Students Attempted in Round 1 : " << r1att;
        cout << "\nNo. Students Attempted in Round 2 : " << r2att;
        cout << "\nNo. Students Attempted in Round 3 : " << r3att;
        cout << "\nNo. Students Attempted in Round 4 : " << r4att;
        cout << "\nNo. Students Got Job Offer        : " << s.count;
        if (r1att > 0)
            cout << "\nSuccess Rate                      : " << float(s.count) / r1att * 100 << "%";
        if (s.count > 0)
        {
            cout << "\n\nMaximum Package Offered : " << s.max;
            cout << "\nMinimum Package Offered : " << s.min;
            cout << "\nAverage Package         : " << s.total / s.count;
            cout << "\nMedian Package          : " << FindMedianPackage(s.list);
        }
        cout << "\n\n";
        PrintHorizontalLine(150);
    }

    void PrintCompanyList(set<string> &companies)
    {
        cout << "\nNo. Of Companies : " << companies.size() << "\n\nCompanies :\n\n";
        int i = 0;
        for (auto &c : companies)
        {
            cout << c << " , ";
            if ((++i) % 15 == 0)
            {
                cout << "\n";
            }
        }
        cout << "\n\n";
        PrintHorizontalLine(150);
    }

    float FindMedianPackage(vector<float> nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n == 0)
            return 0;
        return (n % 2 == 0) ? (nums[n / 2 - 1] + nums[n / 2]) / 2 : nums[n / 2];
    }

public:
    StatisticsService(Repository &repo) : repo(repo) {}

    void FindOverallPlacementStatistics()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        PrintHorizontalLine(60);

        Query q; // Empty Query
        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats packageStats = CalcPkgStats(q);

        vector<Record> finalRecords;
        repo.CollectRecords(repo.GetFR(), q, finalRecords);
        set<string> companies;

        for (auto &record : finalRecords)
        {
            companies.insert(record.company);
        }

        cout << "\n# Overall Placement Statistics :\n";
        cout << "\nNo. Students Attempted in Round 1 : " << r1;
        cout << "\nNo. Students Attempted in Round 2 : " << r2;
        cout << "\nNo. Students Attempted in Round 3 : " << r3;
        cout << "\nNo. Students Attempted in Round 4 : " << r4;
        cout << "\nNo. Students Got Job Offer        : " << packageStats.count;
        cout << "\nSuccess Rate                      : " << float(packageStats.count) / r1 * 100 << "%";
        cout << "\n\nMaximum Package Offered : " << packageStats.max;
        cout << "\nMinimum Package Offered : " << packageStats.min;
        cout << "\nAverage Package         : " << packageStats.total / packageStats.count;
        cout << "\nMedian Package          : " << FindMedianPackage(packageStats.list);
        cout << "\n\n";

        PrintHorizontalLine(150);

        cout << "\nNo. Of Companies Visited : " << companies.size();
        cout << "\n\nCompanies :\n\n";
        int cnt = 0;
        for (string s : companies)
        {
            cout << s << " , ";
            if (cnt == 15)
                cout << "\n";
            cnt++;
            cnt %= 16;
        }
        cout << "\n\n";

        PrintHorizontalLine(150);
    }

    void FindStudentPlacementDetails()
    {
        if (!repo.IsDataInserted())
        {
            cout << "\n-----> Insufficient Data.\n\n";
            return;
        }

        long long id;
        cout << "\n#-----> Enter Student ID : ";
        cin >> id;

        if (!repo.StudentExists(id))
        {
            cout << "\n-----> Invalid ID.\n\n";
            return;
        }

        Record info = repo.GetStudentInfo(id);

        Query q;
        q.setId(id);

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        int offers = repo.GetOfferCount(id);

        PrintHorizontalLine(60);

        cout << "\n# " << id << "'s Placement Details :\n";
        cout << "\nName           : " << info.name;
        cout << "\nID             : " << id;
        cout << "\nBatch          : " << info.batch;
        cout << "\nProgram        : " << info.program;
        cout << "\nEmail          : " << info.email;
        cout << "\nContact Number : " << info.contactNO;
        cout << "\nWhatsApp Number: " << info.whatsappNO;
        if (r1 > 0)
            cout << "\nSuccess Rate   : " << float(offers) / r1 * 100 << "%\n\n";

        PrintHorizontalLine(100);

        cout << "\nNo. of Attempts in Round 1 : " << r1;
        cout << "\nNo. of Attempts in Round 2 : " << r2;
        cout << "\nNo. of Attempts in Round 3 : " << r3;
        cout << "\nNo. of Attempts in Round 4 : " << r4;
        cout << "\nNo. of Job Offers           : " << offers;

        vector<Record> frRecords;

        Query offerQuery;
        offerQuery.setId(id);

        repo.CollectRecords(repo.GetFR(), offerQuery, frRecords);

        cout << "\n\nJob Offer Details:\n";
        for (auto &r : frRecords)
        {
            cout << "  Company: " << r.company << "  Package: " << r.package << " LPA\n";
        }
        cout << "\n\n";

        PrintHorizontalLine(100);
    }

    void FindBatchWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch));

        set<string> companies;
        vector<Record> fr;
        repo.CollectRecords(repo.GetFR(), q, fr);

        for (auto &r : fr)
        {
            companies.insert(r.company);
        }

        PrintCompanyList(companies);
    }

    void FindProgramWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Program " + program);

        set<string> companies;
        vector<Record> fr;
        repo.CollectRecords(repo.GetFR(), q, fr);

        for (auto &r : fr)
        {
            companies.insert(r.company);
        }

        PrintCompanyList(companies);
    }

    void FindCompanyWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Company " + company);

        set<int> batches;
        vector<Record> fr;
        repo.CollectRecords(repo.GetFR(), q, fr);

        for (auto &r : fr)
        {
            batches.insert(r.batch);
        }

        cout << "\nBatches whose students got offers :\n";
        for (auto &b : batches)
        {
            cout << b << " , ";
        }

        cout << "\n\n";
        PrintHorizontalLine(150);
    }

    void FindYearWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year));

        set<string> companies;
        vector<Record> fr;
        repo.CollectRecords(repo.GetFR(), q, fr);

        for (auto &r : fr)
        {
            companies.insert(r.company);
        }

        cout << "\nCompanies that hired in " << year << " :\n";
        int i = 0;
        for (auto &c : companies)
        {
            cout << c << " , ";
            if ((++i) % 15 == 0)
            {
                cout << "\n";
            }
        }
        cout << "\n\n";
        PrintHorizontalLine(150);
    }

    void FindBatchAndCompanyWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch) + " Company " + company);
    }

    void FindBatchAndProgramWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch) + " Program " + program);
    }

    void FindProgramAndCompanyWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Program " + program + " Company " + company);
    }

    void FindYearAndBatchWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Batch " + to_string(batch));
    }

    void FindYearAndProgramWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Program " + program);
    }

    void FindYearAndCompanyWisePlacementStatistics()
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

        int r1 = repo.CountInTree(repo.GetR1(), q);
        int r2 = repo.CountInTree(repo.GetR2(), q);
        int r3 = repo.CountInTree(repo.GetR3(), q);
        int r4 = repo.CountInTree(repo.GetR4(), q);
        PkgStats s = CalcPkgStats(q);

        PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Company " + company);
    }
};

#endif
