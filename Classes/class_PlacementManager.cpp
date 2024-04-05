#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------- NODE'S TYPE ---------------------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>

//--->Node Type for Round1,Round2,Round3,HR Round

class Node1
{
public:
    long long id;
    string name;
    int batch;
    string program;
    string email;
    long long contactNO;
    long long whatsappNO;
    string company;
    int year;
    Node1 *next;

    Node1(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year)
    {
        this->id = id;
        this->name = name;
        this->batch = batch;
        this->program = program;
        this->email = email;
        this->contactNO = contactNO;
        this->whatsappNO = whatsappNO;
        this->company = company;
        this->year = year;
        next = NULL;
    }
};

//--->Node Type for Final Round

class Node2
{
public:
    long long id;
    string name;
    int batch;
    string program;
    string email;
    long long contactNO;
    long long whatsappNO;
    string company;
    int year;
    float package;
    Node2 *next;

    Node2(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year, float package)
    {
        this->id = id;
        this->name = name;
        this->batch = batch;
        this->program = program;
        this->email = email;
        this->contactNO = contactNO;
        this->whatsappNO = whatsappNO;
        this->company = company;
        this->year = year;
        this->package = package;
        next = NULL;
    }
};

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//----------------------------------------------------------- Placement Management Class --------------------------------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

class PlacementManager
{

private:
    //--------------- Variables for Creating List and to Manage Placement Statics  -------->

    // Head and Tail Pointers for Round 1

    Node1 *HeadR1;
    Node1 *TailR1;

    // Head and Tail Pointers for Round 2

    Node1 *HeadR2;
    Node1 *TailR2;

    // Head and Tail Pointers for Round 3

    Node1 *HeadR3;
    Node1 *TailR3;

    // Head and Tail Pointers for Round 4

    Node1 *HeadR4;
    Node1 *TailR4;

    // Head and Tail Pointers for Round 5

    Node2 *HeadFR;
    Node2 *TailFR;

    // Variables to Find Details of Student

    unordered_map<long long, string> StudentName;
    unordered_map<long long, int> StudentBatch;
    unordered_map<long long, string> StudentProgram;
    unordered_map<long long, string> StudentEmail;
    unordered_map<long long, long long> StudentContactNumber;
    unordered_map<long long, long long> StudentWhatsappNumber;

    // Variables to keep Track on student's attempt and Job Offers , Package Details and Company Details in which Student had Tried or Got Job Offer

    unordered_map<long long, int> R1StudnetAttempts;
    unordered_map<long long, int> R2StudentAttempts;
    unordered_map<long long, int> R3StudentAttempts;
    unordered_map<long long, int> R4StudentAttempts;
    unordered_map<long long, int> TotalStudnetOffers;
    unordered_map<long long, vector<string>> R1StudentCompany;
    unordered_map<long long, vector<string>> R2StudentCompany;
    unordered_map<long long, vector<string>> R3StudentCompany;
    unordered_map<long long, vector<string>> R4StudentCompany;
    unordered_map<long long, vector<string>> OfferedStudentCompany;
    unordered_map<long long, vector<float>> PackageOfferedStudent;

    // Variables to keep Track on student's attempt and Job Offers of particular batch

    unordered_map<int, int> R1BatchAttempts;
    unordered_map<int, int> R2BatchAttempts;
    unordered_map<int, int> R3BatchAttempts;
    unordered_map<int, int> R4BatchAttempts;
    unordered_map<int, int> TotalBatchOffers;

    // Variables to keep Track on How many students attempted and Got Job Offers for particular Company

    unordered_map<string, int> R1CompanyAttempts;
    unordered_map<string, int> R2CompanyAttempts;
    unordered_map<string, int> R3CompanyAttempts;
    unordered_map<string, int> R4CompanyAttempts;
    unordered_map<string, int> TotalCompanyOffers;

    // Variables to keep Track on How many students attempted and Got Job Offers for particular Program

    unordered_map<string, int> R1ProgramAttempts;
    unordered_map<string, int> R2ProgramAttempts;
    unordered_map<string, int> R3ProgramAttempts;
    unordered_map<string, int> R4ProgramAttempts;
    unordered_map<string, int> TotalProgramOffers;

    // Variables to keep Track on How many students attempted and got job Offeres for particular Year

    unordered_map<int, int> R1YearAttempts;
    unordered_map<int, int> R2YearAttempts;
    unordered_map<int, int> R3YearAttempts;
    unordered_map<int, int> R4YearAttempts;
    unordered_map<int, int> TotalYearOffers;

    // Variables to keep Track on whole Placement Statics

    int NOofStudentR1;
    int NOofStudentR2;
    int NOofStudentR3;
    int NOofStudentR4;
    int NOofStudentFR;
    float MinPackageOverall = numeric_limits<float>::max();
    float MaxPackageOverall = numeric_limits<float>::min();
    float TotalPackageOverall;
    float AveragePackageOverall;
    vector<float> PackagesOfferedOverall;
    vector<string> CompaniesVisitedOverall;

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------- Functions to Create list for Respective Round ----------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------Function to add Node in Round1's list-------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void addToListR1(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year)
    {
        Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company, year);

        if (NewNode == NULL)
        {
            cerr << "\nUnable to allocate Memory For Creating Node for Round1\n";
            return;
        }
        else
        {
            if (HeadR1 == NULL)
            {
                HeadR1 = NewNode;
                TailR1 = NewNode;
                return;
            }
            if (NewNode->id <= HeadR1->id)
            {
                NewNode->next = HeadR1;
                HeadR1 = NewNode;
                return;
            }
            if (TailR1->id <= NewNode->id)
            {
                TailR1->next = NewNode;
                TailR1 = NewNode;
                return;
            }
            else
            {
                Node1 *Prev = NULL;
                Node1 *Current = HeadR1;
                while (!(NewNode->id <= Current->id) && Current != NULL)
                {
                    Prev = Current;
                    Current = Current->next;
                }

                if (Current == NULL)
                {
                    cerr << "\nSomething went wrong while inserting node in Round1's List\n";
                    return;
                }
                else
                {
                    Prev->next = NewNode;
                    NewNode->next = Current;
                    return;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------Function to add Node in Round2's list-------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void addToListR2(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year)
    {
        Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company, year);

        if (NewNode == NULL)
        {
            cerr << "\nUnable to allocate Memory For Creating Node for Round2\n";
            return;
        }
        else
        {
            if (HeadR2 == NULL)
            {
                HeadR2 = NewNode;
                TailR2 = NewNode;
                return;
            }
            if (NewNode->id <= HeadR2->id)
            {
                NewNode->next = HeadR2;
                HeadR2 = NewNode;
                return;
            }
            if (TailR2->id <= NewNode->id)
            {
                TailR2->next = NewNode;
                TailR2 = NewNode;
                return;
            }
            else
            {
                Node1 *Prev = NULL;
                Node1 *Current = HeadR2;
                while (!(NewNode->id <= Current->id) && Current != NULL)
                {
                    Prev = Current;
                    Current = Current->next;
                }

                if (Current == NULL)
                {
                    cerr << "\nSomething went wrong while inserting node in Round2's List\n";
                    return;
                }
                else
                {
                    Prev->next = NewNode;
                    NewNode->next = Current;
                    return;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------Function to add Node in Round3's list-------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void addToListR3(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year)
    {
        Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company, year);

        if (NewNode == NULL)
        {
            cerr << "\nUnable to allocate Memory For Creating Node for Round3\n";
            return;
        }
        else
        {
            if (HeadR3 == NULL)
            {
                HeadR3 = NewNode;
                TailR3 = NewNode;
                return;
            }
            if (NewNode->id <= HeadR3->id)
            {
                NewNode->next = HeadR3;
                HeadR3 = NewNode;
                return;
            }
            if (TailR3->id <= NewNode->id)
            {
                TailR3->next = NewNode;
                TailR3 = NewNode;
                return;
            }
            else
            {
                Node1 *Prev = NULL;
                Node1 *Current = HeadR3;
                while (!(NewNode->id <= Current->id) && Current != NULL)
                {
                    Prev = Current;
                    Current = Current->next;
                }

                if (Current == NULL)
                {
                    cerr << "\nSomething went wrong while inserting node in Round3's List\n";
                    return;
                }
                else
                {
                    Prev->next = NewNode;
                    NewNode->next = Current;
                    return;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------Function to add Node in Round4's list-------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void addToListR4(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year)
    {
        Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company, year);

        if (NewNode == NULL)
        {
            cerr << "\nUnable to allocate Memory For Creating Node for Round4\n";
            return;
        }
        else
        {
            if (HeadR4 == NULL)
            {
                HeadR4 = NewNode;
                TailR4 = NewNode;
                return;
            }
            if (NewNode->id <= HeadR4->id)
            {
                NewNode->next = HeadR4;
                HeadR4 = NewNode;
                return;
            }
            if (TailR4->id <= NewNode->id)
            {
                TailR4->next = NewNode;
                TailR4 = NewNode;
                return;
            }
            else
            {
                Node1 *Prev = NULL;
                Node1 *Current = HeadR4;
                while (!(NewNode->id <= Current->id) && Current != NULL)
                {
                    Prev = Current;
                    Current = Current->next;
                }

                if (Current == NULL)
                {
                    cerr << "\nSomething went wrong while inserting node in Round4's List\n";
                    return;
                }
                else
                {
                    Prev->next = NewNode;
                    NewNode->next = Current;
                    return;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------------Function to add Node in Final Round's list-------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void addToListFR(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, int year, float pakage)
    {
        Node2 *NewNode = new Node2(id, name, batch, program, email, contactNO, whatsappNO, company, year, pakage);

        if (NewNode == NULL)
        {
            cerr << "\nUnable to allocate Memory For Creating Node for Final Round\n";
            return;
        }
        else
        {
            if (HeadFR == NULL)
            {
                HeadFR = NewNode;
                TailFR = NewNode;
                return;
            }
            if (NewNode->id <= HeadFR->id)
            {
                NewNode->next = HeadFR;
                HeadFR = NewNode;
                return;
            }
            if (TailFR->id <= NewNode->id)
            {
                TailFR->next = NewNode;
                TailFR = NewNode;
                return;
            }
            else
            {
                Node2 *Prev = NULL;
                Node2 *Current = HeadFR;
                while (!(NewNode->id <= Current->id) && Current != NULL)
                {
                    Prev = Current;
                    Current = Current->next;
                }

                if (Current == NULL)
                {
                    cerr << "\nSomething went wrong while inserting node in Final Round's List\n";
                    return;
                }
                else
                {
                    Prev->next = NewNode;
                    NewNode->next = Current;
                    return;
                }
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------- Functions to Read Files for Respective Round ------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------------Function to Read Round 1's File------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void ReadFileForRound1(const string &filepath, const string &CompanyName)
    {

        ifstream file(filepath);

        if (!file.is_open())
        {
            cerr << "\nError in Opening Round1's File\nPlease Try again with valid File Path :) \n";
            return;
        }
        else
        {

            cout << "\n-----------> Fetching Data from The \" Round1's File \" of Company \" " << CompanyName << " \" --------------->\n";

            //--->Extract data from each line

            string line;

            getline(file, line); // Skip the first line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str, date_str;
            int batch, year;
            long long id, contactNO, whatsappNO;

            while (getline(file, line))
            {
                stringstream ss(line);

                getline(ss, WordToSkip, ','); // Ignore the Sr No.
                getline(ss, id_str, ',');
                id = stoll(id_str);
                batch = stoi(id_str.substr(0, 4)); // First 4 digits of ID is batch
                getline(ss, name, ',');
                getline(ss, program, ',');
                getline(ss, date_str, ',');
                year = stoi(date_str.substr(6, 10)); // Last 4 digits of Date is Year
                getline(ss, email, ',');
                getline(ss, conatctNO_str, ',');
                contactNO = stoll(conatctNO_str);
                getline(ss, whatsappNO_str, ',');
                whatsappNO = stoll(whatsappNO_str);

                addToListR1(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, year); // Insert the extracted data into the list

                // Store Student Details

                StudentName[id] = name;
                StudentBatch[id] = batch;
                StudentProgram[id] = program;
                StudentEmail[id] = email;
                StudentContactNumber[id] = contactNO;
                StudentWhatsappNumber[id] = whatsappNO;

                R1StudnetAttempts[id]++;          // Increment in Number of Attempts in R1 by student
                R1BatchAttempts[batch]++;         // Increment in Number of Student of particular Batch who had attempted in Round 1
                R1CompanyAttempts[CompanyName]++; // Increment in Number of Student who had attempted in Round 1 of particular Company
                R1ProgramAttempts[program]++;     // Increment in Number of Student who had attemped in Round 1 of particular Program
                R1YearAttempts[year]++;           // Increment in Number of Student who had attemped in Round 1 in particular Year

                R1StudentCompany[id].push_back(CompanyName); // Push Company Name in which Student had attempted in Round 1

                NOofStudentR1++; // Increment in Number of student who passed in Round 1
            }

            CompaniesVisitedOverall.push_back(CompanyName); // Push Company Name who has visited College

            file.close();

            cout << "\n<------ Successfully Data Fetched From the \" Round1's File \" of Company \" " << CompanyName << " \" <--------\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------------Function to Read Round 2's File------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void ReadFileForRound2(const string &filepath, const string &CompanyName)
    {

        ifstream file(filepath);

        if (!file.is_open())
        {
            cerr << "\nError in Opening Round2's File\nPlease Try again with valid File Path :) \n";
            return;
        }
        else
        {

            cout << "\n-----------> Fetching Data from The \" Round2's File \" of Company \" " << CompanyName << " \" --------------->\n";

            string line;

            getline(file, line); // Skip the first line

            while (getline(file, line))
            {
                stringstream ss(line);

                //--->Extract data from each line

                // Variables to Extact Data

                string WordToSkip; // To Skip Unnecessary data

                string id_str, name, program, email, conatctNO_str, whatsappNO_str, date_str;
                int batch, year;
                long long id, contactNO, whatsappNO;

                getline(ss, WordToSkip, ','); // Ignore the Sr No.
                getline(ss, id_str, ',');
                id = stoll(id_str);
                batch = stoi(id_str.substr(0, 4)); // First 4 digits of ID is batch
                getline(ss, name, ',');
                getline(ss, program, ',');
                getline(ss, date_str, ','); // Last 4 digits of Date is Year
                year = stoi(date_str.substr(6, 10));
                getline(ss, email, ',');
                getline(ss, conatctNO_str, ',');
                contactNO = stoll(conatctNO_str);
                getline(ss, whatsappNO_str, ',');
                whatsappNO = stoll(whatsappNO_str);

                addToListR2(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, year); // Insert the extracted data into the list

                R2StudentAttempts[id]++;          // Increment in Number of Attempts in R2 by student
                R2BatchAttempts[batch]++;         // Increment in Number of Student of particular Batch who had attempted in Round 2
                R2CompanyAttempts[CompanyName]++; // Increment in Number of Student who had attempted in Round 2 of particular Company
                R2ProgramAttempts[program]++;     // Increment in Number of Student who had attemped in Round 2 of particular Program
                R2YearAttempts[year]++;           // Increment in Number of Student who had attemped in Round 2 in particular Year

                R2StudentCompany[id].push_back(CompanyName); // Push Company Name in which Student had attempted in Round 2

                NOofStudentR2++; // Increment in Number of student who passed in Round 2
            }

            file.close();

            cout << "\n<------ Successfully Data Fetched From the \" Round2's File \" of Company \" " << CompanyName << " \" <--------\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------------Function to Read Round 3's File------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void ReadFileForRound3(const string &filepath, const string &CompanyName)
    {

        ifstream file(filepath);

        if (!file.is_open())
        {
            cerr << "\nError in Opening Round3's File\nPlease Try again with valid File Path :) \n";
            return;
        }
        else
        {

            cout << "\n-----------> Fetching Data from The \" Round3's File \" of Company \" " << CompanyName << " \" --------------->\n";

            string line;

            getline(file, line); // Skip the first line

            while (getline(file, line))
            {
                stringstream ss(line);

                //--->Extract data from each line

                // Variables to Extact Data

                string WordToSkip; // To Skip Unnecessary data

                string id_str, name, program, email, conatctNO_str, whatsappNO_str, date_str;
                int batch, year;
                long long id, contactNO, whatsappNO;

                getline(ss, WordToSkip, ','); // Ignore the Sr No.
                getline(ss, id_str, ',');
                id = stoll(id_str);
                batch = stoi(id_str.substr(0, 4)); // First 4 digits of ID is batch
                getline(ss, name, ',');
                getline(ss, program, ',');
                getline(ss, date_str, ','); // Last 4 digits of Date is Year
                year = stoi(date_str.substr(6, 10));
                getline(ss, email, ',');
                getline(ss, conatctNO_str, ',');
                contactNO = stoll(conatctNO_str);
                getline(ss, whatsappNO_str, ',');
                whatsappNO = stoll(whatsappNO_str);

                addToListR3(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, year); // Insert the extracted data into the list

                R3StudentAttempts[id]++;          // Increment in Number of Attempts in R3 by student
                R3BatchAttempts[batch]++;         // Increment in Number of Student of particular Batch who had attempted in Round 3
                R3CompanyAttempts[CompanyName]++; // Increment in Number of Student who had attempted in Round 3 of particular Company
                R3ProgramAttempts[program]++;     // Increment in Number of Student who had attemped in Round 3 of particular Program

                R3YearAttempts[year]++;                      // Increment in Number of Student who had attemped in Round 3 in particular Year
                R3StudentCompany[id].push_back(CompanyName); // Push Company Name in which Student had attempted in Round 3

                NOofStudentR3++; // Increment in Number of student who passed in Round 3
            }

            file.close();

            cout << "\n<------ Successfully Data Fetched From the \" Round3's \" File of Company \" " << CompanyName << " \" <--------\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------------Function to Read Round 4's File------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void ReadFileForRound4(const string &filepath, const string &CompanyName)
    {

        ifstream file(filepath);

        if (!file.is_open())
        {
            cerr << "\nError in Opening Round4's File\nPlease Try again with valid File Path :) \n";
            return;
        }
        else
        {

            cout << "\n-----------> Fetching Data from The \" Round4's File \" of Company \" " << CompanyName << " \" --------------->\n";

            string line;

            getline(file, line); // Skip the first line

            while (getline(file, line))
            {
                stringstream ss(line);

                //--->Extract data from each line

                // Variables to Extact Data

                string WordToSkip; // To Skip Unnecessary data

                string id_str, name, program, email, conatctNO_str, whatsappNO_str, date_str;
                int batch, year;
                long long id, contactNO, whatsappNO;

                getline(ss, WordToSkip, ','); // Ignore the Sr No.
                getline(ss, id_str, ',');
                id = stoll(id_str);
                batch = stoi(id_str.substr(0, 4)); // First 4 digits of ID is batch
                getline(ss, name, ',');
                getline(ss, program, ',');
                getline(ss, date_str, ','); // Last 4 digits of Date is Year
                year = stoi(date_str.substr(6, 10));
                getline(ss, email, ',');
                getline(ss, conatctNO_str, ',');
                contactNO = stoll(conatctNO_str);
                getline(ss, whatsappNO_str, ',');
                whatsappNO = stoll(whatsappNO_str);

                addToListR4(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, year); // Insert the extracted data into the list

                R4StudentAttempts[id]++;                     // Increment in Number of Attempts in R4 by student
                R4BatchAttempts[batch]++;                    // Increment in Number of Student of particular Batch who had attempted in Round 4
                R4CompanyAttempts[CompanyName]++;            // Increment in Number of Student who had attempted in Round 4 of particular Company
                R4ProgramAttempts[program]++;                // Increment in Number of Student who had attemped in Round 4 of particular Program
                R4YearAttempts[year]++;                      // Increment in Number of Student who had attemped in Round 4 in particular Year\

                R4StudentCompany[id].push_back(CompanyName); // Push Company Name in which Student had attempted in Round 4

                NOofStudentR4++; // Increment in Number of student who passed in Round 4
            }

            file.close();

            cout << "\n<------ Successfully Data Fetched From the \" Round4's File \" of Company \" " << CompanyName << " \" <--------\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Read Final Round's File------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void ReadFileForFinalRound(const string &filepath, const string &CompanyName)
    {

        ifstream file(filepath);

        if (!file.is_open())
        {
            cerr << "\nError in Opening Final Round's File\nPlease Try again with valid File Path :) \n";
            return;
        }
        else
        {

            cout << "\n---------> Fetching Data from The \" Final Round's File \" of Company \" " << CompanyName << " \" ------------>\n";
            string line;

            getline(file, line); // Skip the first line

            while (getline(file, line))
            {
                stringstream ss(line);

                //--->Extract data from each line

                // Variables to Extact Data

                string WordToSkip; // To Skip Unnecessary data

                string id_str, name, program, email, conatctNO_str, whatsappNO_str, package_str, date_str;
                int batch, year;
                long long id, contactNO, whatsappNO;
                float package;

                getline(ss, WordToSkip, ','); // Ignore the Sr No.
                getline(ss, id_str, ',');

                id = stoll(id_str);
                batch = stoi(id_str.substr(0, 4)); // First 4 digits of ID is batch
                getline(ss, name, ',');
                getline(ss, program, ',');
                getline(ss, date_str, ',');
                year = stoi(date_str.substr(6, 10)); // Last 4 digits of Date is Year
                getline(ss, email, ',');
                getline(ss, conatctNO_str, ',');
                contactNO = stoll(conatctNO_str);
                getline(ss, whatsappNO_str, ',');
                whatsappNO = stoll(whatsappNO_str);
                getline(ss, package_str, ',');
                package = stof(package_str);

                addToListFR(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, year, package); // Insert the extracted data into the list

                TotalStudnetOffers[id]++;          // Increment in Number of Job Offeres offered to student
                TotalBatchOffers[batch]++;         // Increment in Number of Student of particulr Batch who had got Job Offer
                TotalCompanyOffers[CompanyName]++; // Increment in Number of Student who had got Job Offer in particular Company
                TotalProgramOffers[program]++;     // Increment in Number of Student who had got Job Offer of particular Company
                TotalYearOffers[year]++;           // Increment in Number of Student who had got job Offer in particular year

                OfferedStudentCompany[id].push_back(CompanyName); // Push Company Name in which Student got Job Offer
                PackageOfferedStudent[id].push_back(package);     // Push Package Offerd to Student

                NOofStudentFR++; // Increment in Number of student who passed in Final Round

                //----->Change in Value of Variables to Find Overall Placement Statistics

                if (package < MinPackageOverall)
                    MinPackageOverall = package; // Change in Min Package if the Current Package offered to Student is Less Then Previous Min Package
                if (package > MaxPackageOverall)
                    MaxPackageOverall = package; // Change in Max Package if the Current Package offered to Student is Greater Then Previous Max Package

                TotalPackageOverall += package; // Increment in Total Amount of Pakage Offered

                AveragePackageOverall = TotalPackageOverall / NOofStudentFR; // Average Pakage Offered

                PackagesOfferedOverall.push_back(package); // Push the Package Offered
            }

            file.close();

            cout << "\n<---- Successfully Data Fetched From the \" Final Round's File \" of Company \" " << CompanyName << " \" <-----\n\n";
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------- Functions to Display Whole Data of Respective Round ----------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //--->Helper function to print a horizontal line

    void PrintHorizontalLine(int width, char fillChar = '-')
    {
        cout << setfill(fillChar) << setw(width) << "" << setfill(' ') << endl;
    }

    //---------------------------------------Helper Function to Display Whole Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4WholeData(Node1 *Head)
    {
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        ;
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }
        PrintHorizontalLine(157);
    }

    //---------------------------------------Helper Function to Display Whole Data for Final Round ------------------------------->

    void DisplayFinalRoundWholeData(Node2 *Head)
    {
        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                 << "|" << setw(10) << left << Current->year << "|" << endl;
        }
        PrintHorizontalLine(177);
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Display Whole Data Round Wise ------------------------------------>
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayWholeDataRoundWise(int choice)
    {
        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 --------------------------------------------->\n";
            cout << "Total number of students in Round 1: " << NOofStudentR1 << endl;
            DisplayRound1to4WholeData(HeadR1);
            cout << "\n<-------------------------------------------- End of Data For Round 1 --------------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 --------------------------------------------->\n";
            cout << "\nTotal number of students in Round 2: " << NOofStudentR2 << endl;
            DisplayRound1to4WholeData(HeadR2);
            cout << "\n<-------------------------------------------- End of Data For Round 2 --------------------------------------------------->\n";

            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 --------------------------------------------->\n";
            cout << "\nTotal number of students in Round 3: " << NOofStudentR3 << endl;
            DisplayRound1to4WholeData(HeadR3);
            cout << "\n<-------------------------------------------- End of Data For Round 3 --------------------------------------------------->\n";

            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 --------------------------------------------->\n";
            cout << "\nTotal number of students in Round 4: " << NOofStudentR4 << endl;
            DisplayRound1to4WholeData(HeadR4);
            cout << "\n<-------------------------------------------- End of Data For Round 4 --------------------------------------------------->\n";

            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round ------------------------------------------->\n";
            cout << "\nTotal number of students who got offers " << NOofStudentFR << endl;
            DisplayFinalRoundWholeData(HeadFR);
            cout << "\n<------------------------------------------ End of Data For Final Round ------------------------------------------------->\n";

            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------- Functions to Write Whole Data of Respective Round in file ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Write Whole Sorted Data of Round 1 to 4 ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteWholeSortedDataForRound1to4(const string &filepath, Node1 *Head)
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

        while (Current != nullptr)
        {
            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->year << "\n";

            Current = Current->next;
            i++;
        }

        cout << "\nData Written Successfully....\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Write Whole Sorted Data of Final Round ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteWholeSortedDataForFinalRound(const string &filepath, Node2 *Head)
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

        while (Current != nullptr)
        {
            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->package << "," << Current->year << "\n";

            Current = Current->next;
            i++;
        }

        cout << "\nData Written Successfully....\n";

        outputFile.close();
    }

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

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------- Functions to Display ProgramWise Data of Respective Round ------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------- Helper Function to Display ProgramWise Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4ProgramWiseData(Node1 *Head, string program)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool program_found = false;

        while (Current != NULL)
        {
            if (Current->program == program)
            {
                program_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!program_found)
            cout << "\nStudent of Program " << program << "  does not found , Enter Valid Program Name and Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //-------------------------------------- Helper Function to Display ProgramWise Data for Final Round ------------------------------->

    void DisplayFinalRoundProgramWiseData(Node2 *Head, string program)
    {
        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool program_found = false;

        while (Current != NULL)
        {
            if (Current->program == program)
            {
                program_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!program_found)
            cout << "\nStudents of Program " << program << "  does not found , Enter Valid Program Name and Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------- Function to Display ProgramWise Data Round Wise ----------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayProgramWiseData(int choice, string program)
    {
        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " ---------------------------------------->\n";
            DisplayRound1to4ProgramWiseData(HeadR1, program);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << "----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " ---------------------------------------->\n";
            DisplayRound1to4ProgramWiseData(HeadR2, program);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " ---------------------------------------------->\n";

            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " --------------------------------------->\n";
            DisplayRound1to4ProgramWiseData(HeadR3, program);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " --------------------------------------------->\n";

            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " --------------------------------------->\n";
            DisplayRound1to4ProgramWiseData(HeadR4, program);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " --------------------------------------------->\n";

            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " ------------------------------------->\n";
            DisplayFinalRoundProgramWiseData(HeadFR, program);
            cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " ------------------------------------------->\n";

            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------- Functions to Write ProgramWise Data of Respective Round in file ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //---------------------------------- Function to Write ProgramWise Sorted Data of Round 1 to 4 ----------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program)
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

        bool program_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program)
            {
                program_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!program_found)
            cout << "\nStudents of Program " << program << "  does not found , Enter Valid Program Name and Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------------------- Function to Write ProgramWise Sorted Data of Final Round ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program)
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

        bool program_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program)
            {
                program_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!program_found)
            cout << "\nStudents of Program " << program << "  does not found , Enter Valid Program Name and Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------- Functions to Display CompanyWise Data of Respective Round  ----------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------- Helper Function to Display CompanyWise Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4CompanyWiseData(Node1 *Head, string company)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool company_found = false;

        while (Current != NULL)
        {
            if (Current->company == company)
            {
                company_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!company_found)
            cout << "\nStudents of Company " << company << "  does not found , Enter Valid Company Name and Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //-------------------------------------- Helper Function to Display CompanyWise Data for Final Round ------------------------------->

    void DisplayFinalRoundCompanyWiseData(Node2 *Head, string company)
    {
        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool company_found = false;

        while (Current != NULL)
        {
            if (Current->company == company)
            {
                company_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!company_found)
            cout << "\nStudents of Company " << company << "  does not found , Enter Valid Program Name and Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------- Function to Display CompanyWise Data Round Wise ----------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayCompanyWiseData(int choice, string company)
    {
        switch (choice)
        {

        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Company " << company << " ---------------------------------------->\n";
            DisplayRound1to4CompanyWiseData(HeadR1, company);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Company " << company << "----------------------------------------------->\n";

            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Company " << company << " ---------------------------------------->\n";
            DisplayRound1to4CompanyWiseData(HeadR2, company);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Company " << company << " ---------------------------------------------->\n";

            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Company " << company << " --------------------------------------->\n";
            DisplayRound1to4CompanyWiseData(HeadR3, company);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Company " << company << " --------------------------------------------->\n";

            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Company " << company << " --------------------------------------->\n";
            DisplayRound1to4CompanyWiseData(HeadR4, company);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Company " << company << " --------------------------------------------->\n";

            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Company " << company << " ------------------------------------->\n";
            DisplayFinalRoundCompanyWiseData(HeadFR, company);
            cout << "\n<------------------------------------------ End of Data For Final Round of Company " << company << " ------------------------------------------->\n";

            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------- Functions to Write CompanyWise Data of Respective Round in file ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //---------------------------------- Function to Write CompanyWise Sorted Data of Round 1 to 4 ----------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteCompanyWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string company)
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

        bool company_found = false;

        while (Current != nullptr)
        {
            if (Current->company == company)
            {
                company_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!company_found)
            cout << "\nStudents of Company " << company << "  does not found , Enter Valid Company Name and Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------------------- Function to Write CompanyWise Sorted Data of Final Round ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string company)
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

        bool company_found = false;

        while (Current != nullptr)
        {
            if (Current->company == company)
            {
                company_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!company_found)
            cout << "\nStudents of Company " << company << "  does not found , Enter Valid Company Name and Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------- Functions to Display Programwise Data of a Particular Batch for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Programwise Data of particular Batch for Rounds 1 to 4 ------------------------------>

    void DisplayRound1to4ProgramOFBatchWiseData(Node1 *Head, string program, int batch)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool programOFbatch_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->batch == batch)
            {
                programOFbatch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Name and Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Batch for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFBatchWiseData(Node2 *Head, string program, int batch)
    {

        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool programOFbatch_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->batch == batch)
            {
                programOFbatch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Name and Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------- Function to Display Programwise Data of a Particular Batch for Respective Rounds ---------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayProgramOFBatchWiseData(int choice, string program, int batch)
    {

        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Batch " << batch << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFBatchWiseData(HeadR1, program, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Batch " << batch << "----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Batch " << batch << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFBatchWiseData(HeadR2, program, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Batch " << batch << " ---------------------------------------------->\n";
            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFBatchWiseData(HeadR3, program, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Batch " << batch << " --------------------------------------------->\n";
            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFBatchWiseData(HeadR4, program, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Batch " << batch << " --------------------------------------------->\n";
            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Batch " << batch << " ------------------------------------->\n";
            DisplayFinalRoundProgramOFBatchWiseData(HeadFR, program, batch);
            cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Batch " << batch << " ------------------------------------------->\n";
            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------- Functions to Write Programwise Data of Particular Batch for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Write Programwise Sorted Data of Particular Batch for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, int batch)
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

        bool programOFbatch_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->batch == batch)
            {
                programOFbatch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Try Again \n";
        else
            cout << "Data Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------- Function to Write Programwise Sorted Data of Particular Batch for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, int batch)
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

        bool programOFbatch_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->batch == batch)
            {
                programOFbatch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Program " << program << " and Batch " << batch << " do not found, Enter Valid Program and Batch Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------- Functions to Display Programwise Data of a Particular Company for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Programwise Data of particular Company for Rounds 1 to 4 ------------------------------>

    void DisplayRound1to4ProgramOFCompanyWiseData(Node1 *Head, string program, string company)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;
        bool programOFcompany_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company)
            {
                programOFcompany_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFcompany_found)
            cout << "\nStudents of Program " << program << " and Company " << company << " do not found, Enter Valid Program and Company Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Company for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFCompanyWiseData(Node2 *Head, string program, string company)
    {

        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool programOFcompany_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company)
            {
                programOFcompany_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFcompany_found)
            cout << "\nStudents of Program " << program << " and Company " << company << " do not found, Enter Valid Program and Company Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------- Function to Display Programwise Data of a Particular Company for Respective Rounds ---------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayProgramOFCompanyWiseData(int choice, string program, string company)
    {

        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Company " << company << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFCompanyWiseData(HeadR1, program, company);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Company " << company << "----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Company " << company << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFCompanyWiseData(HeadR2, program, company);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Company " << company << " ---------------------------------------------->\n";
            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Company " << company << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFCompanyWiseData(HeadR3, program, company);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Company " << company << " --------------------------------------------->\n";
            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Company " << company << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFCompanyWiseData(HeadR4, program, company);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Company " << company << " --------------------------------------------->\n";
            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Company " << company << " ------------------------------------->\n";
            DisplayFinalRoundProgramOFCompanyWiseData(HeadFR, program, company);
            cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Company " << company << " ------------------------------------------->\n";
            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------- Functions to Write Programwise Data of Particular Company for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Write Programwise Sorted Data of Particular Company for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFCompanyWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, string company)
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

        bool programOFcompany_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->company == company)
            {
                programOFcompany_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFcompany_found)
            cout << "\nStudents of Program " << program << " and Company " << company << " do not found, Enter Valid Program and Company Try Again \n";
        else
            cout << "Data Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------- Function to Write Programwise Sorted Data of Particular Company for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, string company)
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

        bool programOFcompany_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->company == company)
            {
                programOFcompany_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFcompany_found)
            cout << "\nStudents of Program " << program << " and Company " << company << " do not found, Enter Valid Program and Company Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------- Functions to Display Yearwise Data of a Particular Batch for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Yearwise Data of particular Batch for Rounds 1 to 4 ------------------------------>

    void DisplayRound1to4YearAndBatchWiseData(Node1 *Head, int year, int batch)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool programOFbatch_found = false;
        while (Current != NULL)
        {
            if (Current->year == year && Current->batch == batch)
            {
                programOFbatch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Year " << year << " and Batch " << batch << " do not found, Enter Valid Year and Batch Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //---------------------------- Helper Function to Display Yearwise Data of particluar Batch for the Final Round ---------------------------->

    void DisplayFinalRoundYearAndBatchWiseData(Node2 *Head, int year, int batch)
    {

        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool programOFbatch_found = false;

        while (Current != NULL)
        {
            if (Current->year == year && Current->batch == batch)
            {
                programOFbatch_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Year " << year << " and Batch " << batch << " do not found, Enter Valid Year and Batch Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------- Function to Display Yearwise Data of a Particular Batch for Respective Rounds ---------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayYearAndBatchWiseData(int choice, int year, int batch)
    {

        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Year " << year << " and Batch " << batch << " ---------------------------------------->\n";
            DisplayRound1to4YearAndBatchWiseData(HeadR1, year, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Year " << year << " and Batch " << batch << "----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Year " << year << " and Batch " << batch << " ---------------------------------------->\n";
            DisplayRound1to4YearAndBatchWiseData(HeadR2, year, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Year " << year << " and Batch " << batch << " ---------------------------------------------->\n";
            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Year " << year << " and Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4YearAndBatchWiseData(HeadR3, year, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Year " << year << " and Batch " << batch << " --------------------------------------------->\n";
            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Year " << year << " and Batch " << batch << " --------------------------------------->\n";
            DisplayRound1to4YearAndBatchWiseData(HeadR4, year, batch);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Year " << year << " and Batch " << batch << " --------------------------------------------->\n";
            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Year " << year << " and Batch " << batch << " ------------------------------------->\n";
            DisplayFinalRoundYearAndBatchWiseData(HeadFR, year, batch);
            cout << "\n<------------------------------------------ End of Data For Final Round of Year " << year << " and Batch " << batch << " ------------------------------------------->\n";
            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------- Functions to Write Yearwise Data of Particular Batch for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Write Yearwise Sorted Data of Particular Batch for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearAndBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int year, int batch)
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

        bool programOFbatch_found = false;

        while (Current != nullptr)
        {
            if (Current->year == year && Current->batch == batch)
            {
                programOFbatch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Year " << year << " and Batch " << batch << " do not found, Enter Valid Year and Batch Try Again \n";
        else
            cout << "Data Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------- Function to Write Yearwise Sorted Data of Particular Batch for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearAndBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int year, int batch)
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

        bool programOFbatch_found = false;

        while (Current != nullptr)
        {
            if (Current->year == year && Current->batch == batch)
            {
                programOFbatch_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFbatch_found)
            cout << "\nStudents of Year " << year << " and Batch " << batch << " do not found, Enter Valid Year and Batch and Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------- Functions to Display Programwise Data of a Particular Year for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Programwise Data of particular Year for Rounds 1 to 4 ------------------------------>

    void DisplayRound1to4ProgramOFYearWiseData(Node1 *Head, string program, int year)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157); // Printing horizontal line

        Node1 *Current = Head;

        bool programOFyear_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year)
            {
                programOFyear_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFyear_found)
            cout << "\nStudents of Program " << program << " and Year " << year << " do not found, Enter Valid Year and Program Try Again \n";

        PrintHorizontalLine(157); // Printing horizontal line
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Year for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFYearWiseData(Node2 *Head, string program, int year)
    {

        cout << endl;
        PrintHorizontalLine(177); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177); // Printing horizontal line

        Node2 *Current = Head;

        bool programOFyear_found = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year)
            {
                programOFyear_found = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!programOFyear_found)
            cout << "\nStudents of Program " << program << " and Batch " << year << " do not found, Enter Valid Year and Program Try Again \n";

        PrintHorizontalLine(177); // Printing horizontal line
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------- Function to Display Programwise Data of a Particular Year for Respective Rounds ---------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayProgramOFYearWiseData(int choice, string program, int year)
    {

        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Program " << program << " and Year " << year << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFYearWiseData(HeadR1, program, year);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Program " << program << " and Year " << year << "----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Program " << program << " and Year " << year << " ---------------------------------------->\n";
            DisplayRound1to4ProgramOFYearWiseData(HeadR2, program, year);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Program " << program << " and Year " << year << " ---------------------------------------------->\n";
            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Program " << program << " and Year " << year << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFYearWiseData(HeadR3, program, year);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Program " << program << " and Year " << year << " --------------------------------------------->\n";
            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Program " << program << " and Year " << year << " --------------------------------------->\n";
            DisplayRound1to4ProgramOFYearWiseData(HeadR4, program, year);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Program " << program << " and Year " << year << " --------------------------------------------->\n";
            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Program " << program << " and Year " << year << " ------------------------------------->\n";
            DisplayFinalRoundProgramOFYearWiseData(HeadFR, program, year);
            cout << "\n<------------------------------------------ End of Data For Final Round of Program " << program << " and Year " << year << " ------------------------------------------->\n";
            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------- Functions to Write Programwise Data of Particular Year for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Write Programwise Sorted Data of Particular Year for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFYearWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, string program, int year)
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

        bool programOFyear_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->year == year)
            {
                programOFyear_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFyear_found)
            cout << "\nStudents of Program " << program << " and Year " << year << " do not found, Enter Valid Year and Program Try Again \n";
        else
            cout << "Data Written Successfully...\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------- Function to Write Programwise Sorted Data of Particular Year for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteProgramOFYearWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, string program, int year)
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

        bool programOFyear_found = false;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->year == year)
            {
                programOFyear_found = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!programOFyear_found)
            cout << "\nStudents of Program " << program << " and Year " << year << " do not found, Enter Valid Year and Program  Try Again \n";
        else
            cout << "\nData Written Successfully...\n";

        outputFile.close();
    }

    ////////////////

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Find Median Package --------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    float FindMedianPackage(vector<float> &nums)
    {
        int n = nums.size();
        std ::sort(nums.begin(), nums.end());

        if (n % 2 == 0)
        {
            // If number of elements is even, median is the average of the middle two elements
            return (nums[n / 2 - 1] + nums[n / 2]) / 2.0f;
        }
        else
        {
            // If number of elements is odd, median is the middle element
            return nums[n / 2];
        }
    }

public:
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Input Data ------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void InputPlacementData()
    {
        string CompanyName;
        cout << "\nEnter Company's Name : ";
        getline(cin, CompanyName);

        string filepath;
        cout << "\nEnter File Path for Round 1's file : ";
        cin >> filepath;
        ReadFileForRound1(filepath, CompanyName); // Collect Data From Round1's File

        cout << "\nEnter File Path for Round 2's file : ";
        cin >> filepath;
        ReadFileForRound2(filepath, CompanyName); // Collect Data From Round2's File

        cout << "\nEnter File Path for Round 3's file : ";
        cin >> filepath;
        ReadFileForRound3(filepath, CompanyName); // Collect Data From Round3's File

        cout << "\nEnter File Path for Round 4's file : ";
        cin >> filepath;
        ReadFileForRound4(filepath, CompanyName); // Collect Data From Round4's File

        cout << "\nEnter File Path for Final Round's file : ";
        cin >> filepath;
        ReadFileForFinalRound(filepath, CompanyName); // Collect Data From Final Round's File
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------------- Functions To Sort Data ----------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Sort Whole Data -------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortWholeData()
    {
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
                DisplayWholeDataRoundWise(1);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR1);

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
                DisplayWholeDataRoundWise(2);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR2);

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
                DisplayWholeDataRoundWise(3);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR3);

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
                DisplayWholeDataRoundWise(4);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR4);

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
                DisplayWholeDataRoundWise(5);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForFinalRound(filepath, HeadFR);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Data Batch Wise --------------------------------------------->
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

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Data Program Wise ------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramWise()
    {

        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

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
                DisplayProgramWiseData(1, program);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR1, program);

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
                DisplayProgramWiseData(2, program);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR2, program);

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
                DisplayProgramWiseData(3, program);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR3, program);

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
                DisplayProgramWiseData(4, program);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR4, program);

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
                DisplayProgramWiseData(5, program);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForFinalRound(filepath, HeadFR, program);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Data Company Wise ------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataCompanyWise()
    {

        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

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
                DisplayCompanyWiseData(1, company);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR1, company);

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
                DisplayCompanyWiseData(2, company);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR2, company);

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
                DisplayCompanyWiseData(3, company);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR3, company);

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
                DisplayCompanyWiseData(4, company);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR4, company);

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
                DisplayCompanyWiseData(5, company);

            cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForFinalRound(filepath, HeadFR, company);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------- Function to Sort Programwise Data of a Particular Batch for Respective Rounds ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramOFBatchWise()
    {

        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\nEnter Choice : ";
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
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFBatchWiseData(1, program, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR1, program, batch);

            break;

        case 2:

            if (HeadR2 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice2;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFBatchWiseData(2, program, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR2, program, batch);

            break;

        case 3:

            if (HeadR3 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice3;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFBatchWiseData(3, program, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR3, program, batch);

            break;

        case 4:

            if (HeadR4 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice4;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFBatchWiseData(4, program, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR4, program, batch);

            break;

        case 5:

            if (HeadFR == NULL)
            {
                cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice5;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFBatchWiseData(5, program, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForFinalRound(filepath, HeadFR, program, batch);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------- Function to Sort Programwise Data of a Particular Company for Respective Rounds ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramOFCompanyWise()
    {

        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

        string company;
        cout << "\nEnter Company Name : ";
        getline(cin, company);

        cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\nEnter Choice : ";
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
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFCompanyWiseData(1, program, company);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR1, program, company);

            break;

        case 2:

            if (HeadR2 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice2;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFCompanyWiseData(2, program, company);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR2, program, company);

            break;

        case 3:

            if (HeadR3 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice3;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFCompanyWiseData(3, program, company);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR3, program, company);

            break;

        case 4:

            if (HeadR4 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice4;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFCompanyWiseData(4, program, company);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR4, program, company);

            break;

        case 5:

            if (HeadFR == NULL)
            {
                cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice5;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFCompanyWiseData(5, program, company);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForFinalRound(filepath, HeadFR, program, company);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------- Function to Sort Yearwise Data of a Particular Batch for Respective Rounds ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataYearAndBatchWise()
    {

        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\nEnter Choice : ";
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
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayYearAndBatchWiseData(1, year, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR1, year, batch);

            break;

        case 2:

            if (HeadR2 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice2;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayYearAndBatchWiseData(2, year, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR2, year, batch);

            break;

        case 3:

            if (HeadR3 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice3;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayYearAndBatchWiseData(3, year, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR3, year, batch);

            break;

        case 4:

            if (HeadR4 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice4;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayYearAndBatchWiseData(4, year, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR4, year, batch);

            break;

        case 5:

            if (HeadFR == NULL)
            {
                cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice5;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayYearAndBatchWiseData(5, year, batch);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForFinalRound(filepath, HeadFR, year, batch);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------- Function to Sort Programwise Data of a Particular Year for Respective Rounds ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramOFYearWise()
    {

        string program;
        cout << "\nEnter Program : ";
        getline(cin, program);

        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        cout << "\nTo sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\nEnter Choice : ";
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
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFYearWiseData(1, program, year);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR1, program, year);

            break;

        case 2:

            if (HeadR2 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 2 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice2;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFYearWiseData(2, program, year);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR2, program, year);

            break;

        case 3:

            if (HeadR3 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 3 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice3;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFYearWiseData(3, program, year);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR3, program, year);

            break;

        case 4:

            if (HeadR4 == NULL)
            {
                cout << "\nInsufficient data Inserted for Round 4 , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice4;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFYearWiseData(4, program, year);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR4, program, year);

            break;

        case 5:

            if (HeadFR == NULL)
            {
                cout << "\nInsufficient data Inserted for Final Round , Insert the data and try again \n Thank You \n";
                break;
            }

            char choice5;
            cout << "\nDo you want to Display Data(Y/N) ? \nAns : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFYearWiseData(5, program, year);

            cout << "\nEnter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForFinalRound(filepath, HeadFR, program, year);

            break;

        default:

            cout << "\nInvalid Choice \n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------- Functions To Find Placement Statistics ------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Find Placement Details OF Student ---------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindStudentPlacementDetails()
    {
        long long id;
        cout << "\nEnter Student's ID : ";
        cin >> id;

        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }

        if (StudentName[id] == "")
        {
            cout << "\nInvalid ID entered , enter valid ID and Try Agian \nThank You\n";
            return;
        }

        else
        {
            cout << endl;
            PrintHorizontalLine(50);

            cout << "\nName             : " << StudentName[id];
            cout << "\nID               : " << id;
            cout << "\nBatch            : " << StudentBatch[id];
            cout << "\nProgram          : " << StudentProgram[id];
            cout << "\nEmail            : " << StudentEmail[id];
            cout << "\nContact Number   : " << StudentContactNumber[id];
            cout << "\nWhtasapp Number  : " << StudentWhatsappNumber[id];
            cout << "\nSuuccessRate     : " << float(TotalStudnetOffers[id]) / R1StudnetAttempts[id] * 100 << "%\n\n";

            PrintHorizontalLine(100);

            cout << "\nNo. of Attemptes in Round 1 : " << R1StudnetAttempts[id];
            cout << "\nCompanies : ";
            for (string Company : R1StudentCompany[id])
            {
                cout << Company << " , ";
            }

            cout << "\n\nNo. of Attemptes in Round 2 : " << R2StudentAttempts[id];
            cout << "\nCompanies : ";
            for (string Company : R2StudentCompany[id])
            {
                cout << Company << " , ";
            }

            cout << "\n\nNo. of Attemptes in Round 3 : " << R3StudentAttempts[id];
            cout << "\nCompanies : ";
            for (string Company : R3StudentCompany[id])
            {
                cout << Company << " , ";
            }

            cout << "\n\nNo. of Attemptes in Round 4 : " << R4StudentAttempts[id];
            cout << "\nCompanies : ";
            for (string Company : R4StudentCompany[id])
            {
                cout << Company << " , ";
            }

            cout << "\n\nNo. of Job Offeres  : " << TotalStudnetOffers[id];
            cout << "\nCompanies : ";
            for (string Company : R1StudentCompany[id])
            {
                cout << Company << " , ";
            }
            cout << "\nPackages : ";
            for (float Package : PackageOfferedStudent[id])
            {
                cout << Package << " , ";
            }

            cout << endl
                 << endl;
            PrintHorizontalLine(50);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Find Overall Placement Statistics ---------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindOverallPlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << NOofStudentR1;
            cout << "\nNo. Students Attempted in Round 2 : " << NOofStudentR2;
            cout << "\nNo. Students Attempted in Round 3 : " << NOofStudentR3;
            cout << "\nNo. Students Attempted in Round 4 : " << NOofStudentR4;
            cout << "\nNo. Students Got Job Offer        : " << NOofStudentFR;
            cout << "\nSucceess Rate                     : " << float(NOofStudentFR) / NOofStudentR1 * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << MaxPackageOverall;
            cout << "\nMinimum Package Offered         : " << MinPackageOverall;
            cout << "\nAverage Package                 : " << AveragePackageOverall;
            cout << "\nMedian Package                  : " << FindMedianPackage(PackagesOfferedOverall);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nNo. Of Companis Visted : " << CompaniesVisitedOverall.size();
            cout << "\nCompanies : \n";
            for (int i = 0; i < CompaniesVisitedOverall.size(); i++)
            {
                cout << CompaniesVisitedOverall[i] << " , ";
                if ((i + 1) % 15 == 0)
                    cout << endl;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Find BatchWise Placement Statistics -------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindBatchWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            int batch;
            cout << "\nEnter Batch : ";
            cin >> batch;

            if (R1BatchAttempts[batch] == 0)
            {
                cout << "\nInvalid Batch entered , enter valid Batch and Try Agian \nThank You\n";
                return;
            }
            else
            {
                Node2 *Current = HeadFR;

                vector<float> packages;

                float maxPackage = numeric_limits<float>::min();
                float minPackage = numeric_limits<float>::max();
                float totalPackage = 0;

                // Set to store unique company names
                set<string> uniqueCompanies;

                while (Current != NULL)
                {
                    if (Current->batch == batch)
                    {
                        if (Current->package > maxPackage)
                            maxPackage = Current->package;
                        if (Current->package < minPackage)
                            minPackage = Current->package;

                        totalPackage += Current->package;

                        packages.push_back(Current->package);

                        uniqueCompanies.insert(Current->company);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(50);
                cout << "\nNo. Students Attempted in Round 1 : " << R1BatchAttempts[batch];
                cout << "\nNo. Students Attempted in Round 2 : " << R2BatchAttempts[batch];
                cout << "\nNo. Students Attempted in Round 3 : " << R3BatchAttempts[batch];
                cout << "\nNo. Students Attempted in Round 4 : " << R4BatchAttempts[batch];
                cout << "\nNo. Students Got Job Offer        : " << TotalBatchOffers[batch];
                cout << "\nSucceess Rate                     : " << float(TotalBatchOffers[batch]) / R1BatchAttempts[batch] * 100 << "%";
                cout << "\n\nMaximum Package Offered         : " << maxPackage;
                cout << "\nMinimum Package Offered         : " << minPackage;
                cout << "\nAverage Package                 : " << totalPackage / TotalBatchOffers[batch];
                cout << "\nMedian Package                  : " << FindMedianPackage(packages);
                cout << endl
                     << endl;

                PrintHorizontalLine(150);

                cout << "\nNo. Of Companies Visted : " << uniqueCompanies.size();
                cout << "\n\nCompanies : \n\n";

                int i = 0;
                for (string Companies : uniqueCompanies)
                {
                    cout << Companies << " , ";
                    if ((i + 1) % 15 == 0)
                        cout << endl;

                    i++;
                }
                cout << endl
                     << endl;
                PrintHorizontalLine(150);
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Find ProgramWise Placement Statistics ------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindProgramWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "Insufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            string program;
            cout << "\nEnter Program : ";
            getline(cin, program);

            if (R1ProgramAttempts[program] == 0)
            {
                cout << "\nInvalid Program entered, enter valid Program and Try Agian \nThank You\n";
                return;
            }
            else
            {
                Node2 *Current = HeadFR;

                vector<float> packages;

                float maxPackage = numeric_limits<float>::min();
                float minPackage = numeric_limits<float>::max();
                float totalPackage = 0;

                // Set to store unique company names
                set<string> uniqueCompanies;

                while (Current != NULL)
                {
                    if (Current->program == program)
                    {
                        if (Current->package > maxPackage)
                            maxPackage = Current->package;
                        if (Current->package < minPackage)
                            minPackage = Current->package;

                        totalPackage += Current->package;

                        packages.push_back(Current->package);

                        // Insert the company name into the set
                        uniqueCompanies.insert(Current->company);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(50);
                cout << "\nNo. Students Attempted in Round 1 : " << R1ProgramAttempts[program];
                cout << "\nNo. Students Attempted in Round 2 : " << R2ProgramAttempts[program];
                cout << "\nNo. Students Attempted in Round 3 : " << R3ProgramAttempts[program];
                cout << "\nNo. Students Attempted in Round 4 : " << R4ProgramAttempts[program];
                cout << "\nNo. Students Got Job Offer        : " << TotalProgramOffers[program];
                cout << "\nSucceess Rate                     : " << float(TotalProgramOffers[program]) / R1ProgramAttempts[program] * 100 << "%";
                cout << "\n\nMaximum Package Offered         : " << maxPackage;
                cout << "\nMinimum Package Offered         : " << minPackage;
                cout << "\nAverage Package                 : " << totalPackage / TotalProgramOffers[program];
                cout << "\nMedian Package                  : " << FindMedianPackage(packages);
                cout << endl
                     << endl;

                PrintHorizontalLine(150);

                int i = 0;
                cout << "\nNo. Of Companies Visted : " << uniqueCompanies.size();
                cout << "\n\nCompanies : \n\n";
                for (string company : uniqueCompanies)
                {
                    cout << company << " , ";
                    if ((i + 1) % 15 == 0)
                        cout << endl;

                    i++;
                }
                cout << endl
                     << endl;
                PrintHorizontalLine(150);
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Find CompanyWise Placement Statistics ------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindCompanyWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            string company;
            cout << "\nEnter Company Name : ";
            getline(cin, company);

            if (R1CompanyAttempts[company] == 0)
            {
                cout << "\nInvalid Company Name entered, enter valid Company Name and Try Agian \nThank You\n";
                return;
            }
            else
            {
                Node2 *Current = HeadFR;

                vector<float> packages;

                float maxPackage = numeric_limits<float>::min();
                float minPackage = numeric_limits<float>::max();
                float totalPackage = 0;

                // Set to store unique company names
                set<string> uniqueProgramOFBatch;

                while (Current != NULL)
                {
                    if (Current->company == company)
                    {
                        if (Current->package > maxPackage)
                            maxPackage = Current->package;
                        if (Current->package < minPackage)
                            minPackage = Current->package;

                        totalPackage += Current->package;

                        packages.push_back(Current->package);

                        // Insert the company name and program into the set
                        uniqueProgramOFBatch.insert(to_string(Current->batch) + " " + Current->program);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(50);
                cout << "\nNo. Students Attempted in Round 1 : " << R1CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 2 : " << R2CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 3 : " << R3CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 4 : " << R4CompanyAttempts[company];
                cout << "\nNo. Students Got Job Offer        : " << TotalCompanyOffers[company];
                cout << "\nSucceess Rate                     : " << float(TotalCompanyOffers[company]) / R1CompanyAttempts[company] * 100 << "%";
                cout << "\n\nMaximum Package Offered         : " << maxPackage;
                cout << "\nMinimum Package Offered         : " << minPackage;
                cout << "\nAverage Package                 : " << totalPackage / TotalCompanyOffers[company];
                cout << "\nMedian Package                  : " << FindMedianPackage(packages);
                cout << endl
                     << endl;

                PrintHorizontalLine(150);

                cout << "\nPograms of Batch from " << company << " has hired students : \n\n";

                int i = 0;
                for (string str : uniqueProgramOFBatch)
                {
                    cout << str << " , ";
                    if ((i + 1) % 5 == 0)
                    {
                        cout << endl;
                    }
                    i++;
                }

                cout << endl;
                PrintHorizontalLine(150);
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Find YearWise Placement Statistics ------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindYearWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            int year;
            cout << "\nEnter Year : ";
            cin >> year;

            if (R1YearAttempts[year] == 0)
            {
                cout << "\nInvalid Year entered , enter valid Year and Try Agian \nThank You\n";
                return;
            }
            else
            {
                Node2 *Current = HeadFR;

                vector<float> packages;

                float maxPackage = numeric_limits<float>::min();
                float minPackage = numeric_limits<float>::max();
                float totalPackage = 0;

                // Set to store unique company names
                set<string> uniqueCompanies;

                while (Current != NULL)
                {
                    if (Current->year == year)
                    {
                        if (Current->package > maxPackage)
                            maxPackage = Current->package;
                        if (Current->package < minPackage)
                            minPackage = Current->package;

                        totalPackage += Current->package;

                        packages.push_back(Current->package);

                        uniqueCompanies.insert(Current->company);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(50);
                cout << "\nNo. Students Attempted in Round 1 : " << R1YearAttempts[year];
                cout << "\nNo. Students Attempted in Round 2 : " << R2YearAttempts[year];
                cout << "\nNo. Students Attempted in Round 3 : " << R3YearAttempts[year];
                cout << "\nNo. Students Attempted in Round 4 : " << R4YearAttempts[year];
                cout << "\nNo. Students Got Job Offer        : " << TotalYearOffers[year];
                cout << "\nSucceess Rate                     : " << float(TotalYearOffers[year]) / R1YearAttempts[year] * 100 << "%";
                cout << "\n\nMaximum Package Offered         : " << maxPackage;
                cout << "\nMinimum Package Offered         : " << minPackage;
                cout << "\nAverage Package                 : " << totalPackage / TotalYearOffers[year];
                cout << "\nMedian Package                  : " << FindMedianPackage(packages);
                cout << endl
                     << endl;

                PrintHorizontalLine(150);

                cout << "\nNo. Of Companies Visited in " << year << " : " << uniqueCompanies.size();
                cout << "\n\nCompanies : \n\n";

                int i = 0;
                for (string Companies : uniqueCompanies)
                {
                    cout << Companies << " , ";
                    if ((i + 1) % 10 == 0)
                        cout << endl;

                    i++;
                }
                cout << endl
                     << endl;
                PrintHorizontalLine(150);
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------- Function to Find Program with BatchWise Placement Statistics --------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindProgramAndBatchWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            string program;
            cout << "\nEnter Program : ";
            getline(cin, program);
            int batch;
            cout << "\nEnter Batch : ";
            cin >> batch;

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool ProgramAndBatchFound = false; // To find Program and Batch is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->batch == batch)
                {
                    ProgramAndBatchFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!ProgramAndBatchFound)
            {
                cout << "\nInvalid Batch and Program , please Enter Valid Batch and Program \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->batch == batch)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->batch == batch)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->batch == batch)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique company names
            set<string> uniqueCompanies;

            while (Current != NULL)
            {
                if (Current->program == program && Current->batch == batch)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the company name into the set
                    uniqueCompanies.insert(Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            int i = 0;
            cout << "\nNo. Of Companies Visted : " << uniqueCompanies.size();
            cout << "\n\nCompanies : \n\n";
            for (string company : uniqueCompanies)
            {
                cout << company << " , ";
                if ((i + 1) % 10 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------- Function to Find Program with CompanyWise Placement Statistics ---------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindProgramAndCompanyWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            string program;
            cout << "\nEnter Program : ";
            getline(cin, program);
            string company;
            cout << "\nEnter Company Name : ";
            getline(cin, company);

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool ProgramAndCompanyFound = false; // To find Program and Company is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->company == company)
                {
                    ProgramAndCompanyFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!ProgramAndCompanyFound)
            {
                cout << "\nInvalid Program and Company , please Enter Valid Program and Company , Try again \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->company == company)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->company == company)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->company == company)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique batch
            set<int> uniqueBatches;

            while (Current != NULL)
            {
                if (Current->program == program && Current->company == company)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the batch into the set
                    uniqueBatches.insert(Current->batch);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            int i = 0;
            cout << "\nNo. Of Batches whose Student got Job Offers : " << uniqueBatches.size();
            cout << "\n\nBatches : \n\n";
            for (int batch : uniqueBatches)
            {
                cout << batch << " , ";
                if ((i + 1) % 10 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------------------- Function to Find Batch with CompanyWise Placement Statistics ------------------------------>
    //--------------------------------------------------------------------------------------------------------------------->

    void FindBatchAndCompanyWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            int batch;
            cout << "\nEnter batch : ";
            cin >> batch;
            string company;
            cout << "\nEnter Company Name : ";
            getline(cin, company);

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool BatchAndCompanyFound = false; // To find  Batch and Company is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->batch == batch && Temp->company == company)
                {
                    BatchAndCompanyFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!BatchAndCompanyFound)
            {
                cout << "\nInvalid Batch and Company , please Enter Valid Batch and Company , Try again \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->batch == batch && Temp->company == company)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->batch == batch && Temp->company == company)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->batch == batch && Temp->company == company)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique Programs
            set<string> uniquePrograms;

            while (Current != NULL)
            {
                if (Current->batch == batch && Current->company == company)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the program into the set
                    uniquePrograms.insert(Current->program);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            int i = 0;
            cout << "\nNo. Of Programs whose Student got Job Offers : " << uniquePrograms.size();
            cout << "\n\nPrograms : \n\n";
            for (string program : uniquePrograms)
            {
                cout << program << " , ";
                if ((i + 1) % 10 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------- Function to Find Year with BatchWise Placement Statistics ------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindYearAndBatchWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {
            int year;
            cout << "\nEnter Year : ";
            cin >> year;
            int batch;
            cout << "\nEnter Batch : ";
            cin >> batch;

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool YearAndBatchFound = false; // To find Year and Batch is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->batch == batch)
                {
                    YearAndBatchFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!YearAndBatchFound)
            {
                cout << "\nInvalid Year and Batch , please Enter Valid Year and Batch , Try again \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->batch == batch)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->batch == batch)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->batch == batch)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique Batches ,Programs and Companies

            set<string> uniqueProgramCompany;

            while (Current != NULL)
            {
                if (Current->year == year && Current->batch == batch)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the program and company name into the set
                    uniqueProgramCompany.insert(Current->program + " - " + Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            cout << "\nPrograms from which company has hired Students in " << year << " from Batch " << batch << " : \n\n";

            int i = 0;
            for (string str : uniqueProgramCompany)
            {
                cout << str << " , ";
                if ((i + 1) % 5 == 0)
                {
                    cout << endl;
                }
                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------- Function to Find Year with ProgramWise Placement Statistics ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindYearAndProgramWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {

            int year;
            cout << "\nEnter Year : ";
            cin >> year;
            string program;
            cout << "\nEnter Program : ";
            getline(cin, program);

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool YearAndProgramFound = false; // To find Year and Program is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->program == program)
                {
                    YearAndProgramFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!YearAndProgramFound)
            {
                cout << "\nInvalid Year and Program , please Enter Valid Year and Program , Try Again \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->program == program)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->program == program)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->program == program)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique batches and company names
            set<string> uniqueBatchAndCompany;

            while (Current != NULL)
            {
                if (Current->year == year && Current->program == program)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the batch and company name into the set
                    uniqueBatchAndCompany.insert(to_string(Current->batch) + " - " + Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            int i = 0;
            cout << "\nBatches from company has hired Students in " << year << " from " << program << " : \n\n";
            for (string str : uniqueBatchAndCompany)
            {
                cout << str << " , ";
                if ((i + 1) % 5 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //----------------------------- Function to Find Year with CompanyWise Placement Statistics---------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void FindYearAndCompanyWisePlacementStatistics()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            cout << "\nInsufficient Data to Find Details,please insert Data and Try agian \nThank You\n";
            return;
        }
        else
        {

            int year;
            cout << "\nEnter Year : ";
            cin >> year;
            string company;
            cout << "\nEnter Company Name : ";
            getline(cin, company);

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            bool YearAndCompanyFound = false; // To find Year and Company is in the data or not

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->company == company)
                {
                    YearAndCompanyFound = true;
                    R1Attempts++;
                }

                Temp = Temp->next;
            }

            if (!YearAndCompanyFound)
            {
                cout << "\nInvalid Year and Program , please Enter Valid Year and Program , Try Again \nThank You\n";
                return;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR2;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->company == company)
                {
                    R2Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 3

            Temp = HeadR3;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->company == company)
                {
                    R3Attempts++;
                }
                Temp = Temp->next;
            }

            //---->Finding Attempts in Round 2

            Temp = HeadR4;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->company == company)
                {
                    R4Attempts++;
                }
                Temp = Temp->next;
            }

            Node2 *Current = HeadFR;

            vector<float> packages;

            float maxPackage = numeric_limits<float>::min();
            float minPackage = numeric_limits<float>::max();
            float totalPackage = 0;

            // Set to store unique batches and programs names
            set<string> uniqueBatchAndProgram;

            while (Current != NULL)
            {
                if (Current->year == year && Current->company == company)
                {

                    TotalOfferes++;
                    if (Current->package > maxPackage)
                        maxPackage = Current->package;
                    if (Current->package < minPackage)
                        minPackage = Current->package;

                    totalPackage += Current->package;

                    packages.push_back(Current->package);

                    // Insert the company name into the set
                    uniqueBatchAndProgram.insert(to_string(Current->batch) + " - " + Current->program);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(50);
            cout << "\nNo. Students Attempted in Round 1 : " << R1Attempts;
            cout << "\nNo. Students Attempted in Round 2 : " << R2Attempts;
            cout << "\nNo. Students Attempted in Round 3 : " << R3Attempts;
            cout << "\nNo. Students Attempted in Round 4 : " << R4Attempts;
            cout << "\nNo. Students Got Job Offer        : " << TotalOfferes;
            cout << "\nSucceess Rate                     : " << float(TotalOfferes) / R1Attempts * 100 << "%";
            cout << "\n\nMaximum Package Offered         : " << maxPackage;
            cout << "\nMinimum Package Offered         : " << minPackage;
            cout << "\nAverage Package                 : " << totalPackage / TotalOfferes;
            cout << "\nMedian Package                  : " << FindMedianPackage(packages);
            cout << endl
                 << endl;

            PrintHorizontalLine(150);

            int i = 0;
            cout << "\nBatches and Programs from which " << company << " has hired Students in " << year << " : \n\n";
            for (string str : uniqueBatchAndProgram)
            {
                cout << str << " , ";
                if ((i + 1) % 5 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }
};
