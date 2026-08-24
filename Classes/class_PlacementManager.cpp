    #include <iostream>
    #include <fstream>
    #include <string>
    #include <sstream>
    #include <vector>
    #include <iomanip>
    #include <limits>
    #include <algorithm>
    #include <set>
    #include <thread>
    #include "avl.h"
    #include "query.h"

    using namespace std;

    struct Record
    {
        long long id;
        string name;
        int batch;
        string program;
        string email;
        long long contactNO;
        long long whatsappNO;
        string company;
        int year;
        float package; // 0 for rounds 1-4
    };

    class PlacementManager
    {
    private:
        AVLTree<long long, Record> R1, R2, R3, R4, FR;

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //----------------------------------------------------> Overall Statistics <---------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>
        int NOofStudentR1 = 0, NOofStudentR2 = 0;
        int NOofStudentR3 = 0, NOofStudentR4 = 0, NOofStudentFR = 0;

        float MinPackageOverall = numeric_limits<float>::max();
        float MaxPackageOverall = numeric_limits<float>::min();
        float TotalPackageOverall = 0;
        vector<float> PackagesOfferedOverall;
        set<string> CompaniesVisitedOverall;

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //------------------------------------------------------->  Helper Functions <-------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void PrintHorizontalLine(int width, char ch = '-')
        {
            cout << setfill(ch) << setw(width) << "" << setfill(' ') << "\n";
        }

        bool IsDataInserted()
        {
            return R1.getRoot() && R2.getRoot() && R3.getRoot() && R4.getRoot() && FR.getRoot();
        }

        float FindMedianPackage(vector<float> nums)
        {
            sort(nums.begin(), nums.end());
            int n = nums.size();
            if (n == 0)
                return 0;
            return (n % 2 == 0) ? (nums[n / 2 - 1] + nums[n / 2]) / 2 : nums[n / 2];
        }

        bool IsInData(Query &q)
        {
            vector<Record> records;
            collectRecords(R1.getRoot(), q, records);
            return records.size() ? true : false;
        }

        void collectRecords(Node<long long, Record> *node, Query &q, vector<Record> &out)
        {
            if (!node)
                return;
            collectRecords(node->left, q, out);
            for (auto &r : node->value)
            {
                if (q.matches(r))
                    out.push_back(r);
            }
            collectRecords(node->right, q, out);
        }

        bool studentExists(long long id)
        {
            Node<long long, Record> *node = R1.getRoot();
            while (node)
            {
                if (id == node->key)
                    return true;
                else if (id < node->key)
                    node = node->left;
                else
                    node = node->right;
            }
            return false;
        }

        Record getStudentInfo(long long id)
        {
            Node<long long, Record> *node = R1.getRoot();
            while (node)
            {
                if (id == node->key)
                    return node->value[0];
                else if (id < node->key)
                    node = node->left;
                else
                    node = node->right;
            }
            return Record{};
        }

        // Offers which Student had offered
        int getOfferCount(long long id)
        {
            Node<long long, Record> *node = FR.getRoot();
            while (node)
            {
                if (id == node->key)
                    return (int)node->value.size();
                else if (id < node->key)
                    node = node->left;
                else
                    node = node->right;
            }
            return 0;
        }

        // Count of Node which matches the query (students matching query)
        int CountInTree(AVLTree<long long, Record> &tree, Query &q)
        {
            vector<Record> records;
            collectRecords(tree.getRoot(), q, records);
            return records.size();
        }

        void PrintHeaderR1to4()
        {
            PrintHorizontalLine(157);
            cout << "|    ID    |        Name        |   Batch  |    Program    |"
                    "          Email          |   Contact No  |  WhatsApp No  |"
                    "      Company       |   Year   |\n";
            PrintHorizontalLine(157);
        }

        void PrintRowR1to4(Record &r)
        {
            cout << "|" << setw(10) << left << r.id
                << "|" << setw(20) << left << r.name
                << "|" << setw(10) << left << r.batch
                << "|" << setw(15) << left << r.program
                << "|" << setw(25) << left << r.email
                << "|" << setw(15) << left << r.contactNO
                << "|" << setw(15) << left << r.whatsappNO
                << "|" << setw(20) << left << r.company
                << "|" << setw(10) << left << r.year << "|\n";
        }

        void PrintHeaderFR()
        {
            PrintHorizontalLine(177);
            cout << "|    ID    |        Name        |   Batch  |    Program    |"
                    "          Email          |   Contact No  |  WhatsApp No  |"
                    "      Company       |    Package    |   Year   |\n";
            PrintHorizontalLine(177);
        }

        void PrintRowFR(Record &r)
        {
            cout << "|" << setw(10) << left << r.id
                << "|" << setw(20) << left << r.name
                << "|" << setw(10) << left << r.batch
                << "|" << setw(15) << left << r.program
                << "|" << setw(25) << left << r.email
                << "|" << setw(15) << left << r.contactNO
                << "|" << setw(15) << left << r.whatsappNO
                << "|" << setw(20) << left << r.company
                << "|" << setw(15) << left << r.package
                << "|" << setw(10) << left << r.year << "|\n";
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //-----------------------------------------------> Sorting and File Output Helpers <-------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void DisplayR1to4(AVLTree<long long, Record> &tree, Query &q, string label)
        {
            vector<Record> records;
            collectRecords(tree.getRoot(), q, records);

            cout << "\n<--- " << label << " --->\n";
            PrintHeaderR1to4();
            for (auto &r : records)
            {
                PrintRowR1to4(r);
            }
            PrintHorizontalLine(157);
            cout << "<--- End of " << label << " --->\n";
        }

        void DisplayFR(Query &q, string label)
        {
            vector<Record> records;
            collectRecords(FR.getRoot(), q, records);

            cout << "\n<--- " << label << " --->\n";
            PrintHeaderFR();
            for (auto &r : records)
            {
                PrintRowFR(r);
            }
            PrintHorizontalLine(177);
            cout << "<--- End of " << label << " --->\n";
        }

        void WriteR1to4(AVLTree<long long, Record> &tree, Query &q, string filepath)
        {
            ofstream f(filepath);
            if (!f.is_open())
            {
                cerr << "\n-----> Error opening file for writing\n\n";
                return;
            }

            vector<Record> records;
            collectRecords(tree.getRoot(), q, records);

            f << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";
            int i = 1;
            for (auto &r : records)
            {
                f << i++ << "," << r.id << "," << r.name << "," << r.batch << ","
                << r.program << "," << r.email << "," << r.contactNO << ","
                << r.whatsappNO << "," << r.company << "," << r.year << "\n";
            }

            cout << "\n-----> Data Written Successfully....\n\n";
            f.close();
        }

        void WriteFR(Query &q, string filepath)
        {
            ofstream f(filepath);
            if (!f.is_open())
            {
                cerr << "\n-----> Error opening file for writing\n\n";
                return;
            }

            vector<Record> records;
            collectRecords(FR.getRoot(), q, records);

            f << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";
            int i = 1;
            for (auto &r : records)
            {
                f << i++ << "," << r.id << "," << r.name << "," << r.batch << ","
                << r.program << "," << r.email << "," << r.contactNO << ","
                << r.whatsappNO << "," << r.company << "," << r.package << ","
                << r.year << "\n";
            }

            cout << "\n-----> Data Written Successfully....\n\n";
            f.close();
        }

        void AskAndSortR1to4(AVLTree<long long, Record> &tree, Query &q, string displayLabel)
        {
            char ch;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> ch;

            if (ch == 'Y')
                DisplayR1to4(tree, q, displayLabel);

            string fp;
            cout << "\n#-----> Enter File Path to store Sorted Data : ";
            cin >> fp;

            WriteR1to4(tree, q, fp);
        }

        void AskAndSortFR(Query &q, string displayLabel)
        {
            char ch;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> ch;

            if (ch == 'Y')
                DisplayFR(q, displayLabel);

            string fp;
            cout << "\n#-----> Enter File Path to store Sorted Data : ";
            cin >> fp;

            WriteFR(q, fp);
        }

        void SortByRound(Query &q, string filterDesc)
        {
            cout << "\n#-----> Enter 1/2/3/4 for Round 1-4, or 5 for Final Round : ";
            int choice;
            cin >> choice;

            auto label = [&](int r)
            {
                return "Data For Round " + to_string(r) + " - " + filterDesc;
            };

            switch (choice)
            {
            case 1:
                AskAndSortR1to4(R1, q, label(1));
                break;
            case 2:
                AskAndSortR1to4(R2, q, label(2));
                break;
            case 3:
                AskAndSortR1to4(R3, q, label(3));
                break;
            case 4:
                AskAndSortR1to4(R4, q, label(4));
                break;
            case 5:
                AskAndSortFR(q, "Final Round - " + filterDesc);
                break;
            default:
                cout << "\n<--- Invalid Choice --->\n\n";
            }
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //--------------------------------------------------->  Not-Selected Helpers <-------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void DisplayNotSelected(Query &q, string label)
        {
            vector<Record> all;
            collectRecords(R1.getRoot(), q, all);

            cout << "\n<--- " << label << " --->\n";
            PrintHeaderR1to4();

            bool any = false;
            for (auto &r : all)
            {
                if (getOfferCount(r.id) == 0)
                {
                    PrintRowR1to4(r);
                    any = true;
                }
            }

            if (!any)
                cout << "\n---> Wow !!! All students in this filter are placed <---\n\n";
            PrintHorizontalLine(157);
            cout << "<--- End of " << label << " --->\n";
        }

        void WriteNotSelected(Query &q, string filepath)
        {
            ofstream f(filepath);
            if (!f.is_open())
            {
                cerr << "\n-----> Error opening file for writing\n\n";
                return;
            }

            vector<Record> all;
            collectRecords(R1.getRoot(), q, all);

            f << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";
            int i = 1;
            bool any = false;
            for (auto &r : all)
            {
                if (getOfferCount(r.id) == 0)
                {
                    f << i++ << "," << r.id << "," << r.name << "," << r.batch << ","
                    << r.program << "," << r.email << "," << r.contactNO << ","
                    << r.whatsappNO << "," << r.company << "," << r.year << "\n";
                    any = true;
                }
            }

            if (!any)
                cout << "\n---> Wow !!! All students in this filter are placed <---\n\n";
            else
                cout << "\n-----> Data Written Successfully....\n\n";
            f.close();
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //----------------------------------------------------> Input File Readers <---------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void ReadFileForRound(AVLTree<long long, Record> &tree, int &counter, string filepath, string company, string roundLabel)
        {
            ifstream file(filepath);
            if (!file.is_open())
            {
                PrintHorizontalLine(115);
                cerr << "\n-----> Error opening " << roundLabel << " file of " << company << "\n\n";
                PrintHorizontalLine(115);
                return;
            }

            cout << "\n---> Fetching " << roundLabel << " data for " << company << " ...\n";
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
                counter++;
            }
            file.close();
            cout << "<--- Done: " << roundLabel << " for " << company << " <---\n\n";
        }

        void ReadFileForFinalRound(string filepath, string company)
        {
            ifstream file(filepath);
            if (!file.is_open())
            {
                PrintHorizontalLine(115);
                cerr << "\n-----> Error opening Final Round file of " << company << "\n\n";
                PrintHorizontalLine(115);
                return;
            }

            cout << "\n---> Fetching Final Round data for " << company << " ...\n";
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

                FR.insert(r.id, r);
                NOofStudentFR++;

                if (r.package < MinPackageOverall)
                    MinPackageOverall = r.package;
                if (r.package > MaxPackageOverall)
                    MaxPackageOverall = r.package;
                TotalPackageOverall += r.package;
                PackagesOfferedOverall.push_back(r.package);
            }
            file.close();
            cout << "<--- Done: Final Round for " << company << " <---\n\n";
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //-----------------------------------------------> Package Statistics Helpers <------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        struct PkgStats
        {
            float min, max, total;
            int count;
            vector<float> list;
        };

        PkgStats CalcPkgStats(Query &q)
        {
            PkgStats s{numeric_limits<float>::max(), numeric_limits<float>::lowest(), 0, 0, {}};
            vector<Record> all;
            collectRecords(FR.getRoot(), q, all);
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

    public:
        //------------------------------------------------------------------------------------------------------------------------------------------>
        //----------------------------------------------------> Input Placement Data <-------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void LoadCompanyData()
        {
            cin.ignore();
            string company;
            cout << "\n#-----> Enter Company Name : ";
            getline(cin, company);

            string fp;
            cout << "\n#-----> Enter Round 1 File Path : ";
            cin >> fp;
            ReadFileForRound(R1, NOofStudentR1, fp, company, "Round 1");

            cout << "\n#-----> Enter Round 2 File Path : ";
            cin >> fp;
            ReadFileForRound(R2, NOofStudentR2, fp, company, "Round 2");

            cout << "\n#-----> Enter Round 3 File Path : ";
            cin >> fp;
            ReadFileForRound(R3, NOofStudentR3, fp, company, "Round 3");

            cout << "\n#-----> Enter Round 4 File Path : ";
            cin >> fp;
            ReadFileForRound(R4, NOofStudentR4, fp, company, "Round 4");

            cout << "\n#-----> Enter Final Round File Path : ";
            cin >> fp;
            ReadFileForFinalRound(fp, company);

            CompaniesVisitedOverall.insert(company);
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //----------------------------------------------------> Sorting Functions <------------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void SortWholeData()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data. Insert Data and Try Again.\n\n";
                return;
            }

            Query q; // empty query = match all
            cout << "\n#-----> Enter 1/2/3/4 for Round 1-4, or 5 for Final Round : ";
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "\n<--- Displaying All Data For Round 1 (Total: " << NOofStudentR1 << ") --->\n";
                AskAndSortR1to4(R1, q, "All Data - Round 1");
                break;
            case 2:
                cout << "\n<--- Displaying All Data For Round 2 (Total: " << NOofStudentR2 << ") --->\n";
                AskAndSortR1to4(R2, q, "All Data - Round 2");
                break;
            case 3:
                cout << "\n<--- Displaying All Data For Round 3 (Total: " << NOofStudentR3 << ") --->\n";
                AskAndSortR1to4(R3, q, "All Data - Round 3");
                break;
            case 4:
                cout << "\n<--- Displaying All Data For Round 4 (Total: " << NOofStudentR4 << ") --->\n";
                AskAndSortR1to4(R4, q, "All Data - Round 4");
                break;
            case 5:
                cout << "\n<--- Displaying All Data For Final Round (Total: " << NOofStudentFR << ") --->\n";
                AskAndSortFR(q, "All Data - Final Round");
                break;
            default:
                cout << "\n<--- Invalid Choice --->\n\n";
            }
        }

        void SortDataBatchWise()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            Query q;
            q.setBatch(batch);

            if (!IsInData(q))
            {
                cout << "\n-----> Batch not found.\n\n";
                return;
            }

            SortByRound(q, "Batch " + to_string(batch));
        }

        void SortDataProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Program not found.\n\n";
                return;
            }

            SortByRound(q, "Program " + program);
        }

        void SortDataYearWise()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            Query q;
            q.setYear(year);

            if (!IsInData(q))
            {
                cout << "\n-----> Year not found.\n\n";
                return;
            }

            SortByRound(q, "Year " + to_string(year));
        }

        void SortDataCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Company not found.\n\n";
                return;
            }

            SortByRound(q, "Company " + company);
        }

        void SortDataBatchAndProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Program not found.\n\n";
                return;
            }

            SortByRound(q, "Batch " + to_string(batch) + " Program " + program);
        }

        void SortDataBatchAndCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Company not found.\n\n";
                return;
            }

            SortByRound(q, "Batch " + to_string(batch) + " Company " + company);
        }

        void SortDataProgramAndCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Program+Company not found.\n\n";
                return;
            }

            SortByRound(q, "Program " + program + " Company " + company);
        }

        void SortDataYearAndBatchWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Batch not found.\n\n";
                return;
            }

            SortByRound(q, "Year " + to_string(year) + " Batch " + to_string(batch));
        }

        void SortDataYearAndProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Program not found.\n\n";
                return;
            }

            SortByRound(q, "Year " + to_string(year) + " Program " + program);
        }

        void SortDataYearAndCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Company not found.\n\n";
                return;
            }

            SortByRound(q, "Year " + to_string(year) + " Company " + company);
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //-----------------------------------------------> Placement Statistics Functions <---------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void FindOverallPlacementStatistics()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            PrintHorizontalLine(60);

            cout << "\n# Overall Placement Statistics :\n";
            cout << "\nNo. Students Attempted in Round 1 : " << NOofStudentR1;
            cout << "\nNo. Students Attempted in Round 2 : " << NOofStudentR2;
            cout << "\nNo. Students Attempted in Round 3 : " << NOofStudentR3;
            cout << "\nNo. Students Attempted in Round 4 : " << NOofStudentR4;
            cout << "\nNo. Students Got Job Offer        : " << NOofStudentFR;
            cout << "\nSuccess Rate                      : " << float(NOofStudentFR) / NOofStudentR1 * 100 << "%";
            cout << "\n\nMaximum Package Offered : " << MaxPackageOverall;
            cout << "\nMinimum Package Offered : " << MinPackageOverall;
            cout << "\nAverage Package         : " << TotalPackageOverall / NOofStudentFR;
            cout << "\nMedian Package          : " << FindMedianPackage(PackagesOfferedOverall);
            cout << "\n\n";

            PrintHorizontalLine(150);

            cout << "\nNo. Of Companies Visited : " << CompaniesVisitedOverall.size();
            cout << "\n\nCompanies :\n\n";
            int cnt = 0;
            for (string s : CompaniesVisitedOverall)
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
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            long long id;
            cout << "\n#-----> Enter Student ID : ";
            cin >> id;

            if (!studentExists(id))
            {
                cout << "\n-----> Invalid ID.\n\n";
                return;
            }

            Record info = getStudentInfo(id);

            // Count attempts per round
            Query q;
            q.setId(id);

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            int offers = getOfferCount(id);

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

            // Show company + package from FR
            vector<Record> frRecords;

            Query offerQuery;
            offerQuery.setId(id);

            collectRecords(FR.getRoot(), offerQuery, frRecords);

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
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            Query q;
            q.setBatch(batch);

            if (!IsInData(q))
            {
                cout << "\n-----> Batch not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch));

            // Unique companies
            set<string> companies;
            vector<Record> fr;
            collectRecords(FR.getRoot(), q, fr);

            for (auto &r : fr)
            {
                companies.insert(r.company);
            }

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

        void FindProgramWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Program not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Program " + program);

            set<string> companies;
            vector<Record> fr;
            collectRecords(FR.getRoot(), q, fr);

            for (auto &r : fr)
            {
                companies.insert(r.company);
            }

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

        void FindCompanyWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Company not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Company " + company);

            set<int> batches;
            vector<Record> fr;
            collectRecords(FR.getRoot(), q, fr);

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
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            Query q;
            q.setYear(year);

            if (!IsInData(q))
            {
                cout << "\n-----> Year not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year));

            set<string> companies;
            vector<Record> fr;
            collectRecords(FR.getRoot(), q, fr);

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
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Company not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch) + " Company " + company);
        }

        void FindBatchAndProgramWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Program not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Batch " + to_string(batch) + " Program " + program);
        }

        void FindProgramAndCompanyWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Program+Company not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Program " + program + " Company " + company);
        }

        void FindYearAndBatchWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Batch not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Batch " + to_string(batch));
        }

        void FindYearAndProgramWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Program not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Program " + program);
        }

        void FindYearAndCompanyWisePlacementStatistics()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Company not found.\n\n";
                return;
            }

            int r1 = CountInTree(R1, q);
            int r2 = CountInTree(R2, q);
            int r3 = CountInTree(R3, q);
            int r4 = CountInTree(R4, q);
            PkgStats s = CalcPkgStats(q);

            PrintPkgStats(s, r1, r2, r3, r4, "Year " + to_string(year) + " Company " + company);
        }

        //------------------------------------------------------------------------------------------------------------------------------------------>
        //--------------------------------------------> Not-Selected Student Functions <------------------------------------------------------------->
        //------------------------------------------------------------------------------------------------------------------------------------------>

        void FindNotSelectedBatchWise()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            Query q;
            q.setBatch(batch);

            if (!IsInData(q))
            {
                cout << "\n-----> Batch not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Batch " + to_string(batch));

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Program not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Program " + program);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Company not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Company " + company);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedYearWise()
        {
            if (!IsDataInserted())
            {
                cout << "\n-----> Insufficient Data.\n\n";
                return;
            }

            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            Query q;
            q.setYear(year);

            if (!IsInData(q))
            {
                cout << "\n-----> Year not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Year " + to_string(year));

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedBatchAndCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Company not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Batch " + to_string(batch) + " Company " + company);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedBatchAndProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Batch+Program not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Batch " + to_string(batch) + " Program " + program);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedCompanyAndProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Company+Program not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Company " + company + " Program " + program);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedYearAndBatchWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Batch not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Year " + to_string(year) + " Batch " + to_string(batch));

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedYearAndProgramWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Program not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;
            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Year " + to_string(year) + " Program " + program);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }

        void FindNotSelectedYearAndCompanyWise()
        {
            if (!IsDataInserted())
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

            if (!IsInData(q))
            {
                cout << "\n-----> Year+Company not found.\n\n";
                return;
            }

            char ch;
            cout << "\n#-----> Display Data(Y/N)? ";
            cin >> ch;

            if (ch == 'Y')
                DisplayNotSelected(q, "Not Selected - Year " + to_string(year) + " Company " + company);

            string fp;
            cout << "\n#-----> Enter File Path : ";
            cin >> fp;
            WriteNotSelected(q, fp);
        }
    };