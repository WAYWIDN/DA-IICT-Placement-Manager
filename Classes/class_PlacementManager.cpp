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

public:
    // Constructor to intilize all Head and Tail to initialize NULL

    PlacementManager()
    {
        HeadR1 = NULL;
        HeadR2 = NULL;
        HeadR3 = NULL;
        HeadR4 = NULL;
        HeadFR = NULL;

        TailR1 = NULL;
        TailR2 = NULL;
        TailR3 = NULL;
        TailR4 = NULL;
        TailFR = NULL;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //----------------------------------------------------> Some Helper Functions <------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

private:
    // Function to Print HorizontalLine

    void PrintHorizontalLine(int width, char fillChar = '-')
    {
        cout << setfill(fillChar) << setw(width) << "" << setfill(' ') << endl;
    }

    // Function to find Data is Inserted or Not

    bool IsDataInserted()
    {
        if (HeadR1 == NULL || HeadR2 == NULL || HeadR3 == NULL || HeadR4 == NULL || HeadFR == NULL)
        {
            return false;
        }

        return true;
    }

    // Function to find Meadian

    float FindMedianPackage(vector<float> &nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

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

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<------------------------------------------------- // FUNCTIONS TO FIND IS IN DATA OR NOT  // -------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------- Function To Find Batch and Company is in Data or Not ---------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsBatchAndCompanyInData(int batch, string company)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->company == company)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------- Function To Find Batch and Program is in Data or Not ---------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsBatchAndProgramInData(int batch, string program)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->batch == batch && Temp->program == program)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------ Function To Find Program And Company is in Data or Not ---------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsProgramAndCompanyInData(string program, string company)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->program == program && Temp->company == company)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------------------------- Function To Find Year And Batch is in Data or Not ----------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsYearAndBatchInData(int year, int batch)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->batch == batch)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------------------------- Function To Find Year And Program is in Data or Not ----------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsYearAndProgramInData(int year, string program)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->program == program)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------------------------- Function To Find Year And Company is in Data or Not ----------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    bool IsYearAndCompanyInData(int year, string company)
    {
        bool found = false;

        Node1 *Temp = HeadR1;

        while (Temp != NULL)
        {
            if (Temp->year == year && Temp->company == company)
            {
                found = true;
            }

            Temp = Temp->next;
        }

        return found;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<---------------------------------------------------// FUNCTIONS TO COLLECT DATA //------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

private:
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
            cerr << "\n-----> Unable to allocate Memory For Creating Node for Round1\n\n";
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
                    cerr << "\n-----> Something went wrong while inserting node in Round1's List\n\n";
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
            cerr << "\n-----> Unable to allocate Memory For Creating Node for Round2\n\n";
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
                    cerr << "\n-----> Something went wrong while inserting node in Round2's List\n\n";
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
            cerr << "\n-----> Unable to allocate Memory For Creating Node for Round3\n\n";
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
                    cerr << "\n-----> Something went wrong while inserting node in Round3's List\n\n";
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
            cerr << "\n-----> Unable to allocate Memory For Creating Node for Round4\n\n";
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
                    cerr << "\n-----> Something went wrong while inserting node in Round4's List\n\n";
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
            cerr << "\n-----> Unable to allocate Memory For Creating Node for Final Round\n\n";
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
                    cerr << "\n-----> Something went wrong while inserting node in Final Round's List\n\n";
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening \" Round 1's File \" of Company \" " << CompanyName << " \" \n-----> Please Try again with valid File Path :) \n\n";
            PrintHorizontalLine(115);
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

            cout << "<------ Successfully Data Fetched From the \" Round1's File \" of Company \" " << CompanyName << " \" <--------\n\n";
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening \" Round 2's File \" of Company \" " << CompanyName << " \" \n-----> Please Try again with valid File Path :) \n\n";
            PrintHorizontalLine(115);
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

            cout << "<------ Successfully Data Fetched From the \" Round2's File \" of Company \" " << CompanyName << " \" <--------\n\n";
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening \" Round 3's File \" of Company \" " << CompanyName << " \" \n-----> Please Try again with valid File Path :) \n\n";
            PrintHorizontalLine(115);
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

            cout << "<------ Successfully Data Fetched From the \" Round3's \" File of Company \" " << CompanyName << " \" <--------\n\n";
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening \" Round 4's File \" of Company \" " << CompanyName << " \" \n-----> Please Try again with valid File Path :) \n\n";
            PrintHorizontalLine(115);
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

            cout << "<------ Successfully Data Fetched From the \" Round4's File \" of Company \" " << CompanyName << " \" <--------\n\n";
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening \" Final Round's File \" of Company \" " << CompanyName << " \" \n-----> Please Try again with valid File Path :) \n\n";
            PrintHorizontalLine(115);
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

            cout << "<---- Successfully Data Fetched From the \" Final Round's File \" of Company \" " << CompanyName << " \" <-----\n\n";

            cout << "\n\n<---------------------------------------------------------------------------------------------------------------------->\n";
            cout << "\n----------------------------> Successfully Data fechted from The Files of Company \" " << CompanyName << " \" <---------------------------\n";
            cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------------------- Function Input Data -------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

public:
    void InputPlacementData()
    {
        cin.ignore();

        string CompanyName;
        cout << "\n#-----> Enter Company's Name : ";
        getline(cin, CompanyName);

        cout << "\n\n<---------------------------------------------------------------------------------------------------------------------->\n";
        cout << "\n----------------------------------> Fetching Data from The Files of Company \" " << CompanyName << " \" <--------------------------------\n";
        cout << "\n<---------------------------------------------------------------------------------------------------------------------->\n\n";

        string filepath;
        cout << "\n#----> Enter File Path for Round 1's file : ";
        getline(cin, filepath);
        ReadFileForRound1(filepath, CompanyName); // Collect Data From Round1's File

        cout << "\n#-----> Enter File Path for Round 2's file : ";
        getline(cin, filepath);
        ReadFileForRound2(filepath, CompanyName); // Collect Data From Round2's File

        cout << "\n#-----> Enter File Path for Round 3's file : ";
        getline(cin, filepath);
        ReadFileForRound3(filepath, CompanyName); // Collect Data From Round3's File

        cout << "\n#-----> Enter File Path for Round 4's file : ";
        getline(cin, filepath);
        ReadFileForRound4(filepath, CompanyName); // Collect Data From Round4's File

        cout << "\n#-----> Enter File Path for Final Round's file : ";
        getline(cin, filepath);
        ReadFileForFinalRound(filepath, CompanyName); // Collect Data From Final Round's File
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<---------------------------------------------------- // FUNCTIONS TO Sort DATA // ------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

private:
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------ // Helper Functions for Display and Writing Sorted Data //------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------- Functions to Display Whole Data of Respective Round ----------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //--------------------------------------- Helper Function to Display Whole Data for Round 1 to 4 ------------------------------>

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

            Current = Current->next;
        }
        PrintHorizontalLine(157);
    }

    //--------------------------------------- Helper Function to Display Whole Data for Final Round ------------------------------->

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

            Current = Current->next;
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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            PrintHorizontalLine(115);
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

        cout << "\n-----> Data Written Successfully....\n\n";

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
            cout << endl;
            PrintHorizontalLine(115);
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            PrintHorizontalLine(115);
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

        cout << "\n-----> Data Written Successfully....\n\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------- Functions to Display BatchWise Data of Respective Round -------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //---------------------------------------Helper Function to Display BatchWise Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4BatchWiseData(Node1 *Head, int batch)
    {
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------------------Helper Function to Display BatchWise Data for Final Round ------------------------------->

    void DisplayFinalRoundBatchWiseData(Node2 *Head, int batch)
    {
        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

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

            cerr << "\n----> Error in Opening File for Writing Data\n\n";
            PrintHorizontalLine(115);
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully....\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";

            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully....\n\n";

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
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //-------------------------------------- Helper Function to Display ProgramWise Data for Final Round ------------------------------->

    void DisplayFinalRoundProgramWiseData(Node2 *Head, string program)
    {
        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
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

            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //---------------------------------- Functions to Display YearWise Data of Respective Round ------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //---------------------------------------Helper Function to Display YearWise Data for Round 1 to 4 ------------------------------>

    void DisplayRound1to4YearWiseData(Node1 *Head, int year)
    {
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->year == year)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------------------Helper Function to Display YearWise Data for Final Round ------------------------------->

    void DisplayFinalRoundYearWiseData(Node2 *Head, int year)
    {

        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->year == year)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Display YearWise Data Round Wise -------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayYearWiseData(int choice, int year)
    {

        switch (choice)
        {
        case 1:

            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Year " << year << " ---------------------------------------->\n";
            DisplayRound1to4YearWiseData(HeadR1, year);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Year " << year << " ----------------------------------------------->\n";
            break;

        case 2:

            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Year " << year << " ---------------------------------------->\n";
            DisplayRound1to4YearWiseData(HeadR2, year);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Year " << year << " ---------------------------------------------->\n";
            break;

        case 3:

            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Year " << year << " --------------------------------------->\n";
            DisplayRound1to4YearWiseData(HeadR3, year);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Year " << year << " --------------------------------------------->\n";
            break;

        case 4:

            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Year " << year << " --------------------------------------->\n";
            DisplayRound1to4YearWiseData(HeadR4, year);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Year " << year << " --------------------------------------------->\n";
            break;

        case 5:

            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Year " << year << " ------------------------------------->\n";
            DisplayFinalRoundYearWiseData(HeadFR, year);
            cout << "\n<------------------------------------------ End of Data For Final Round of Year " << year << " ------------------------------------------->\n";
            break;
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //----------------------------------------------- Functions to Write YearWise Data of Respective Round in file ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------- Function to Write YearWise Sorted Data of Round 1 to 4 ----------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int year)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->year == year)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Write BatchWise Sorted Data of Final Round ------------------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int year)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->year == year)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->company == company)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //-------------------------------------- Helper Function to Display CompanyWise Data for Final Round ------------------------------->

    void DisplayFinalRoundCompanyWiseData(Node2 *Head, string company)
    {
        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->company == company)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------- Functions to Display Batchwise Data of a Particular Company for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Batchwise Data of particular Company for Rounds 1 to 4 ------------------------------>

    void DisplayBatchOFCompanyWiseDataForRound1to4(Node1 *Head, int batch, string company)
    {
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        bool found = false; // To find

        while (Current != nullptr)
        {
            if (Current->batch == batch && Current->company == company)
            {
                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------- Helper Function to Display Batchwise Data of particluar Company for the Final Round ---------------------------->

    void DisplayBatchOFCompanyWiseDataForFinalRound(Node2 *Head, int batch, string company)
    {
        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->batch == batch && Current->company == company)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //------------- Function to Display Batchwise Data of a Particular Company for Respective Rounds ---------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void DisplayBatchOFCompanyWiseData(int roundChoice, int batch, string company)
    {
        switch (roundChoice)
        {
        case 1:
            cout << "\n<---------------------------------------------- Displaying Data For Round 1 of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
            DisplayBatchOFCompanyWiseDataForRound1to4(HeadR1, batch, company);
            cout << "\n<-------------------------------------------- End of Data For Round 1 of Batch " << batch << " and Company " << company << "----------------------------------------------->\n";
            break;
        case 2:
            cout << "\n<---------------------------------------------- Displaying Data For Round 2 of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
            DisplayBatchOFCompanyWiseDataForRound1to4(HeadR2, batch, company);
            cout << "\n<-------------------------------------------- End of Data For Round 2 of Batch " << batch << " and Company " << company << " ---------------------------------------------->\n";
            break;
        case 3:
            cout << "\n<---------------------------------------------- Displaying Data For Round 3 of Batch " << batch << " and Company " << company << " --------------------------------------->\n";
            DisplayBatchOFCompanyWiseDataForRound1to4(HeadR3, batch, company);
            cout << "\n<-------------------------------------------- End of Data For Round 3 of Batch " << batch << " and Company " << company << " --------------------------------------------->\n";
            break;
        case 4:
            cout << "\n<---------------------------------------------- Displaying Data For Round 4 of Batch " << batch << " and Company " << company << " --------------------------------------->\n";
            DisplayBatchOFCompanyWiseDataForRound1to4(HeadR4, batch, company);
            cout << "\n<-------------------------------------------- End of Data For Round 4 of Batch " << batch << " and Company " << company << " --------------------------------------------->\n";
            break;
        case 5:
            cout << "\n<-------------------------------------------- Displaying Data For Final Round of Batch " << batch << " and Company " << company << " ------------------------------------->\n";
            DisplayBatchOFCompanyWiseDataForFinalRound(HeadFR, batch, company);
            cout << "\n<------------------------------------------ End of Data For Final Round of Batch " << batch << " and Company " << company << " ------------------------------------------->\n";
            break;
        default:
            cout << "\nInvalid Choice \n\n";
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------- Functions to Write Batchwise Data of Particular Company for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Write Batchwise Sorted Data of Particular Company for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteBatchOFCompanyWiseSortedDataForRound1To4(const string &filepath, Node1 *Head, int batch, string company)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->batch == batch && Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //--------------------- Function to Write Batchwise Sorted Data of Particular Company for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteBatchOFCompanyWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int batch, string company)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->batch == batch && Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Batch for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFBatchWiseData(Node2 *Head, string program, int batch)
    {

        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Company for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFCompanyWiseData(Node2 *Head, string program, string company)
    {

        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->company == company)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------ Functions to Display Yearwise Data of a Particular Batch for Respective Rounds ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------- Helper Function to Display Yearwise Data of particular Batch for Rounds 1 to 4 ------------------------------>

    void DisplayRound1to4YearAndBatchWiseData(Node1 *Head, int year, int batch)
    {
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->year == year && Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------- Helper Function to Display Yearwise Data of particluar Batch for the Final Round ---------------------------->

    void DisplayFinalRoundYearAndBatchWiseData(Node2 *Head, int year, int batch)
    {

        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->year == year && Current->batch == batch)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //----------------- Function to Display Yearwise Data of a Particular Batch for Respective Rounds --------------------->
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
    //------------------------ Functions to Write Yearwise Data of Particular Batch for Respective Rounds in a file ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //-------------------------------------------------------------------------------------------------------------------------->
    //---------------------- Function to Write Yearwise Sorted Data of Particular Batch for Rounds 1 to 4 ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearAndBatchWiseSortedDataForRound1to4(const string &filepath, Node1 *Head, int year, int batch)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->year == year && Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //-------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Write Yearwise Sorted Data of Particular Batch for Final Round ---------------------->
    //-------------------------------------------------------------------------------------------------------------------------->

    void WriteYearAndBatchWiseSortedDataForFinalRound(const string &filepath, Node2 *Head, int year, int batch)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->year == year && Current->batch == batch)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(157);
    }

    //---------------------------- Helper Function to Display Programwise Data of particluar Year for the Final Round ---------------------------->

    void DisplayFinalRoundProgramOFYearWiseData(Node2 *Head, string program, int year)
    {

        cout << endl;
        PrintHorizontalLine(177);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package    |   Year   |\n";
        PrintHorizontalLine(177);

        Node2 *Current = Head;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year)
            {

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->package
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        PrintHorizontalLine(177);
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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->year == year)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

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
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Package,Year\n";

        int i = 1;
        Node2 *Current = Head;

        while (Current != nullptr)
        {
            if (Current->program == program && Current->year == year)
            {

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->package << "," << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        cout << "\n-----> Data Written Successfully...\n\n";

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-------------------------------------------------------- //  Functions for Sorting Data // ----------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

public:
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------------------------------Function to Sort Whole Data -------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortWholeData()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayWholeDataRoundWise(1);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR1);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayWholeDataRoundWise(2);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR2);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayWholeDataRoundWise(3);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR3);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayWholeDataRoundWise(4);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForRound1to4(filepath, HeadR4);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayWholeDataRoundWise(5);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteWholeSortedDataForFinalRound(filepath, HeadFR);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Whole Data Batch Wise --------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataBatchWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        // Find Batch is in Data or Not

        if (R1BatchAttempts[batch] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " does not found , Enter Valid Batch and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayBatchWiseData(1, batch);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchWiseSortedDataForRound1to4(filepath, HeadR1, batch);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayBatchWiseData(2, batch);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchWiseSortedDataForRound1to4(filepath, HeadR2, batch);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayBatchWiseData(3, batch);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchWiseSortedDataForRound1to4(filepath, HeadR3, batch);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayBatchWiseData(4, batch);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchWiseSortedDataForRound1to4(filepath, HeadR4, batch);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayBatchWiseData(5, batch);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchWiseSortedDataForFinalRound(filepath, HeadFR, batch);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Data Program Wise ------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // Find Program is in Data or Not

        if (R1ProgramAttempts[program] == 0)
        {
            cout << "\n-----> Students of Program " << program << " does not found , Enter Valid program and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramWiseData(1, program);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR1, program);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramWiseData(2, program);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR2, program);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramWiseData(3, program);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR3, program);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramWiseData(4, program);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForRound1to4(filepath, HeadR4, program);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramWiseData(5, program);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteProgramWiseSortedDataForFinalRound(filepath, HeadFR, program);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Sort Whole Data Year Wise --------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataYearWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        if (R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Year " << year << " does not found , Enter Valid Year and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayYearWiseData(1, year);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteYearWiseSortedDataForRound1to4(filepath, HeadR1, year);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayYearWiseData(2, year);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteYearWiseSortedDataForRound1to4(filepath, HeadR2, year);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayYearWiseData(3, year);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteYearWiseSortedDataForRound1to4(filepath, HeadR3, year);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayYearWiseData(4, year);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteYearWiseSortedDataForRound1to4(filepath, HeadR4, year);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayYearWiseData(5, year);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteYearWiseSortedDataForFinalRound(filepath, HeadFR, year);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Sort Data Company Wise ------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataCompanyWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company Name : ";
        getline(cin, company);

        // Find Company is in Data or Not

        if (R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Company " << company << " does not found , Enter Valid Company and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayCompanyWiseData(1, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR1, company);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayCompanyWiseData(2, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR2, company);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayCompanyWiseData(3, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR3, company);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayCompanyWiseData(4, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForRound1to4(filepath, HeadR4, company);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayCompanyWiseData(5, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteCompanyWiseSortedDataForFinalRound(filepath, HeadFR, company);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //------------------ Function to Sort Batchwise Data of a Particular Company for Respective Rounds -------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataBatchAndCompanyWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company Name : ";
        getline(cin, company);

        // Find Batch or Company is in Data or Not

        if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
            return;
        }

        // Find Batch And Company is in Data or Not

        if (!IsBatchAndCompanyInData(batch, company))
        {
            cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choise : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayBatchOFCompanyWiseData(1, batch, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR1, batch, company);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayBatchOFCompanyWiseData(2, batch, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR2, batch, company);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayBatchOFCompanyWiseData(3, batch, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR3, batch, company);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayBatchOFCompanyWiseData(4, batch, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchOFCompanyWiseSortedDataForRound1To4(filepath, HeadR4, batch, company);
            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayBatchOFCompanyWiseData(5, batch, company);

            cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
            cin >> filepath;

            WriteBatchOFCompanyWiseSortedDataForFinalRound(filepath, HeadFR, batch, company);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //------------------- Function to Sort Programwise Data of a Particular Batch for Respective Rounds ------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramOFBatchWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // Find Batch or Program is in Data or not

        if (R1BatchAttempts[batch] == 0 || R1ProgramAttempts[program] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
            return;
        }

        // Find Batch and Program is in Data or Not

        if (!IsBatchAndProgramInData(batch, program))
        {
            cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choice : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFBatchWiseData(1, program, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR1, program, batch);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFBatchWiseData(2, program, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR2, program, batch);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFBatchWiseData(3, program, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR3, program, batch);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFBatchWiseData(4, program, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForRound1to4(filepath, HeadR4, program, batch);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFBatchWiseData(5, program, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFBatchWiseSortedDataForFinalRound(filepath, HeadFR, program, batch);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    void SortDataProgramOFCompanyWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        string company;
        cout << "\n#-----> Enter Company Name : ";
        getline(cin, company);

        // To find Program or Company is in the data or not

        if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
            return;
        }

        // To find Program and Company is in the data or not

        if (!IsProgramAndCompanyInData(program, company))
        {
            cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choice : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFCompanyWiseData(1, program, company);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR1, program, company);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFCompanyWiseData(2, program, company);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR2, program, company);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFCompanyWiseData(3, program, company);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR3, program, company);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFCompanyWiseData(4, program, company);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForRound1to4(filepath, HeadR4, program, company);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFCompanyWiseData(5, program, company);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFCompanyWiseSortedDataForFinalRound(filepath, HeadFR, program, company);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //------------ Function to Sort Yearwise Data of a Particular Batch for Respective Rounds ----------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataYearAndBatchWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        // To find Year or Batch is in the data or not

        if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
            return;
        }

        // To Find Year and Batch is in the Data or Not

        if (!IsYearAndBatchInData(year, batch))
        {
            cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choice : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayYearAndBatchWiseData(1, year, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR1, year, batch);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayYearAndBatchWiseData(2, year, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR2, year, batch);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayYearAndBatchWiseData(3, year, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR3, year, batch);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayYearAndBatchWiseData(4, year, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForRound1to4(filepath, HeadR4, year, batch);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayYearAndBatchWiseData(5, year, batch);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteYearAndBatchWiseSortedDataForFinalRound(filepath, HeadFR, year, batch);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //---------------- Function to Sort Programwise Data of a Particular Year for Respective Rounds ----------------------->
    //--------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------------------------------------------------------------------------------------->

    void SortDataProgramOFYearWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // To find Year or Program is in the data or not

        if (R1ProgramAttempts[program] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
            return;
        }

        // To find Year and Program is in the data or not

        if (!IsYearAndProgramInData(year, program))
        {
            cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
            return;
        }

        cout << "\n#-----> To sort data for Round 1, Round 2, Round 3, Round 4, or the Final Round ; Enter 1, 2, 3, 4, or 5 respectively \n ";

        int choice;
        cout << "\n#-----> Enter Choice : ";
        cin >> choice;

        string filepath;

        switch (choice)
        {
        case 1:

            char choice1;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice1;

            if (choice1 == 'Y')
                DisplayProgramOFYearWiseData(1, program, year);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR1, program, year);

            break;

        case 2:

            char choice2;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice2;

            if (choice2 == 'Y')
                DisplayProgramOFYearWiseData(2, program, year);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR2, program, year);

            break;

        case 3:

            char choice3;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice3;

            if (choice3 == 'Y')
                DisplayProgramOFYearWiseData(3, program, year);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR3, program, year);

            break;

        case 4:

            char choice4;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice4;

            if (choice4 == 'Y')
                DisplayProgramOFYearWiseData(4, program, year);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForRound1to4(filepath, HeadR4, program, year);

            break;

        case 5:

            char choice5;
            cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
            cin >> choice5;

            if (choice5 == 'Y')
                DisplayProgramOFYearWiseData(5, program, year);

            cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
            cin >> filepath;

            WriteProgramOFYearWiseSortedDataForFinalRound(filepath, HeadFR, program, year);

            break;

        default:

            cout << "\n<-----------------------> Invalid Choice <----------------------->\n\n";
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<---------------------------------------------------// FUNCTIONS TO Find Placement Statistics //------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

public:
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------- Function to Find Overall Placement Statistics ------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindOverallPlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Overall Placement Statistics : \n";

            cout << "\n# Overall Placement Statistics : \n";
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

            cout << "\nNo. Of Companies Visited : " << CompaniesVisitedOverall.size();
            cout << "\n\nCompanies : \n\n";
            for (int i = 0; i < CompaniesVisitedOverall.size(); i++)
            {
                cout << CompaniesVisitedOverall[i] << " , ";
                if ((i + 1) % 15 == 0)
                    cout << endl;
            }
            cout << endl;
            PrintHorizontalLine(150);
        }
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Find Student's Placement Statistics --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindStudentPlacementDetails()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }

        long long id;
        cout << "\n#-----> Enter Student's ID : ";
        cin >> id;

        if (StudentName[id] == "")
        {
            cout << "\n-----> Invalid ID entered , enter valid ID and Try Agian \nThank You\n\n";
            return;
        }

        else
        {
            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# " << id << "'s Placement Details : \n";

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
            cout << "\nPackages[LPA] : ";
            for (float Package : PackageOfferedStudent[id])
            {
                cout << Package << " , ";
            }

            cout << endl
                 << endl;
            PrintHorizontalLine(100);
        }
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Find Batch Wise Placement Statistics --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindBatchWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            // Find Batch is in Data or Not

            if (R1BatchAttempts[batch] == 0)
            {
                cout << "\n-----> Students of Batch " << batch << " does not found , Enter Valid Batch and Try Again \n\n";
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

                        // Insert company name into set
                        uniqueCompanies.insert(Current->company);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(60);
                cout << "\n# Placement Statistics of Batch " << batch << " : \n";

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

                cout << "\nNo. Of Companies Visited : " << uniqueCompanies.size();
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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------- Function to Find Program Wise Placement Statistics -------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindProgramWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            cin.ignore();

            string program;
            cout << "\n#-----> Enter Program : ";
            getline(cin, program);

            // Find Program is in Data or Not

            if (R1ProgramAttempts[program] == 0)
            {
                cout << "\n-----> Students of Program " << program << " does not found , Enter Valid program and Try Again \n\n";
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
                PrintHorizontalLine(60);
                cout << "\n# Placement Statistics of Program " << program << " : \n";

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
                cout << endl;

                PrintHorizontalLine(50);

                int i = 0;
                cout << "\nNo. Of Companies Visited : " << uniqueCompanies.size();
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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Find Year Wise Placement Statistics --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindYearWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            if (R1YearAttempts[year] == 0)
            {
                cout << "\n-----> Students of Year " << year << " does not found , Enter Valid Year and Try Again \n\n";
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

                        // Insert company name into set
                        uniqueCompanies.insert(Current->company);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(60);
                cout << "\n# Placement Statistics in Year " << year << " : \n";

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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Find Company Wise Placement Statistics ------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindCompanyWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            cin.ignore();

            string company;
            cout << "\n#-----> Enter Company Name : ";
            getline(cin, company);

            // Find Company is in Data or Not
            if (R1CompanyAttempts[company] == 0)
            {
                cout << "\n-----> Students of Company " << company << " does not found , Enter Valid Company and Try Again \n\n";
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

                        // Insert the batch and program into the set
                        uniqueProgramOFBatch.insert(to_string(Current->batch) + " " + Current->program);
                    }

                    Current = Current->next;
                }

                cout << endl;
                PrintHorizontalLine(60);
                cout << "\n# Placement Statistics of Company " << company << " : \n";

                cout << "\nNo. Students Attempted in Round 1 : " << R1CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 2 : " << R1CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 3 : " << R1CompanyAttempts[company];
                cout << "\nNo. Students Attempted in Round 4 : " << R1CompanyAttempts[company];
                cout << "\nNo. Students Got Job Offer        : " << TotalCompanyOffers[company];
                cout << "\nSucceess Rate                     : " << float(TotalCompanyOffers[company]) / R1CompanyAttempts[company] * 100 << "%";
                cout << "\n\nMaximum Package Offered         : " << maxPackage;
                cout << "\nMinimum Package Offered         : " << minPackage;
                cout << "\nAverage Package                 : " << totalPackage / TotalCompanyOffers[company];
                cout << "\nMedian Package                  : " << FindMedianPackage(packages);
                cout << endl
                     << endl;

                PrintHorizontalLine(150);

                cout << "\nPrograms of Batch from " << company << " has hired students : \n\n";

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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------- Function to Find Batch and Company Wise Placement Statistics ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindBatchAndCompanyWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            int batch;
            cout << "\n#-----> Enter batch : ";
            cin >> batch;

            cin.ignore();

            string company;
            cout << "\n#-----> Enter Company Name : ";
            getline(cin, company);

            // Find Batch or Company is in Data or Not

            if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
            {
                cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
                return;
            }

            // Find Batch and Company is in Data or Not

            if (!IsBatchAndCompanyInData(batch, company))
            {
                cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->batch == batch && Temp->company == company)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Batch " << batch << " and Company " << company << " : \n";

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
                if ((i + 1) % 15 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------- Function to Find Program and Batch Wise Placement Statistics ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindProgramAndBatchWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {

            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            cin.ignore();

            string program;
            cout << "\n#-----> Enter Program : ";
            getline(cin, program);

            // Find Batch or Program is in Data or not

            if (R1BatchAttempts[batch] == 0 || R1ProgramAttempts[program] == 0)
            {
                cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
                return;
            }

            // Find Batch and Program is in Data or not

            if (!IsBatchAndProgramInData(batch, program))
            {
                cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->batch == batch)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Batch " << batch << " and Program " << program << " : \n";

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
            cout << "\nNo. Of Companies Visited : " << uniqueCompanies.size();
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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------- Function to Find Program and Company Wise Placement Statistics ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindProgramAndCompanyWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            cin.ignore();

            string program;
            cout << "\n#-----> Enter Program : ";
            getline(cin, program);

            string company;
            cout << "\n#-----> Enter Company Name : ";
            getline(cin, company);

            // To find Program or Company is in the data or not

            if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
            {
                cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
                return;
            }

            // To find Program and Company is in the data or not

            if (!IsProgramAndCompanyInData(program, company))
            {
                cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->program == program && Temp->company == company)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Program " << program << " and Company " << company << " : \n";

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
                if ((i + 1) % 15 == 0)
                    cout << endl;

                i++;
            }
            cout << endl
                 << endl;
            PrintHorizontalLine(150);
        }
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------------- Function to Find Year and Batch Wise Placement Statistics ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindYearAndBatchWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {
            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            int batch;
            cout << "\n#-----> Enter Batch : ";
            cin >> batch;

            // To find Year or Batch is in the data or not

            if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
            {
                cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
                return;
            }

            // To find Year and Batch is in the data or not

            if (!IsYearAndBatchInData(year, batch))
            {
                cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->batch == batch)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Batch " << batch << " in Year " << year << " : \n";

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

            cout << "\nPrograms from which companies has hired Students in " << year << " from Batch " << batch << " : \n\n";

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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------ Function to Find Year and Company Wise Placement Statistics ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindYearAndCompanyWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {

            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            cin.ignore();

            string company;
            cout << "\n#-----> Enter Company Name : ";
            getline(cin, company);

            // To find Year or Company is in the data or not

            if (R1CompanyAttempts[company] == 0 || R1YearAttempts[year] == 0)
            {
                cout << "\n-----> Students of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
                return;
            }

            // To find Year and Company is in the data or not

            if (!IsYearAndCompanyInData(year, company))
            {
                cout << "\n-----> Students of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->company == company)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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

                    // Insert the batch and program name into the set
                    uniqueBatchAndProgram.insert(to_string(Current->batch) + " - " + Current->program);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Company " << company << " in Year " << year << " : \n";

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

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------ Function to Find Year and Program Wise Placement Statistics ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindYearAndProgramWisePlacementStatistics()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , please insert Data and Try agian \n-----> Thank You\n\n";
            return;
        }
        else
        {

            int year;
            cout << "\n#-----> Enter Year : ";
            cin >> year;

            cin.ignore();

            string program;
            cout << "\n#-----> Enter Program : ";
            getline(cin, program);

            // To find Year or Program is in the data or not

            if (R1ProgramAttempts[program] == 0 || R1YearAttempts[year] == 0)
            {
                cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
                return;
            }

            // To find Year and Program is in the data or not

            if (!IsYearAndProgramInData(year, program))
            {
                cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
                return;
            }

            //----> Variables to find attempts and job Offers

            int R1Attempts = 0;
            int R2Attempts = 0;
            int R3Attempts = 0;
            int R4Attempts = 0;
            int TotalOfferes = 0;

            //----> Finding Attempts in Round 1

            Node1 *Temp = HeadR1;
            while (Temp != NULL)
            {
                if (Temp->year == year && Temp->program == program)
                {
                    R1Attempts++;
                }

                Temp = Temp->next;
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

            //---->Finding Attempts in Round 4

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

                    // Insert the company name and batch into the set
                    uniqueBatchAndCompany.insert(to_string(Current->batch) + " - " + Current->company);
                }

                Current = Current->next;
            }

            cout << endl;
            PrintHorizontalLine(60);
            cout << "\n# Placement Statistics of Program " << program << " in Year " << year << " : \n";

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

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<---------------------------------------------------// FUNCTIONS TO Find Not Selected Student //------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

private:
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------------- // Helper Functions for Display and Writing Data Of Not Selected Students //---------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Display Not Selected Students BatchWise -------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedBatchWise(int batch)
    {

        cout << "\n<------------------------------------------------ Displaying Not Selected Students of Batch " << batch << " ----------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && TotalStudnetOffers[Current->id] == 0)
            {
                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);

        cout << "\n<----------------------------------------------- End of Not Selected Students of Batch " << batch << " --------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Write Not Selected Students BatchWise ---------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedBatchWise(const string &filepath, int batch)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        bool Success = false;

        int i = 1;
        Node1 *Current = HeadR1;

        while (Current != NULL)
        {
            if (Current->batch == batch && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Display Not Selected Students ProgramWise ------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedProgramWise(string program)
    {

        cout << "\n<------------------------------------------------ Displaying Not Selected Students of Program " << program << " ----------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<----------------------------------------------- End of Not Selected Students of Program " << program << " --------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Write Not Selected Students ProgramWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedProgramWise(const string &filepath, string program)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Display Not Selected Students CompanyWise ------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedCompanyWise(string company)
    {

        cout << "\n<------------------------------------------------ Displaying Not Selected Students of Company " << company << " ----------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Company " << company << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<----------------------------------------------- End of Not Selected Students of Company " << company << " --------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------------- Function to Write Not Selected Students CompanyWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedCompanyWise(const string &filepath, string company)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Company " << company << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Display Not Selected Students YearWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedYearWise(int year)
    {

        cout << "\n<------------------------------------------------ Displaying Not Selected Students of Year " << year << " ----------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {
                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Year " << year << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);

        cout << "\n<----------------------------------------------- End of Not Selected Students of Year " << year << " --------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------- Function to Write Not Selected Students YearWise ---------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedYearWise(const string &filepath, int year)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        bool Success = false;

        int i = 1;
        Node1 *Current = HeadR1;

        while (Current != NULL)
        {
            if (Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Year " << year << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }

        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------------- Function to Display Not Selected Students Batch and Company Wise --------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedBatchAndCompanyWise(int batch, string company)
    {
        cout << "\n<-------------------------------- Displaying Not Selected Students of Batch " << batch << " and Company " << company << "----------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n--------------------------> Wow !!! All Students of Batch " << batch << " and Company " << company << " are placed <--------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<-------------------------------- End of Not Selected Students of Batch " << batch << " and Company " << company << " ---------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //----------------------------- Function to Write Not Selected Students Batch and Company Wise ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedBatchAndCompanyWise(const string &filepath, int batch, string company)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Company " << company << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully...\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Display Not Selected Students Batch and Program Wise ------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedBatchAndProgramWise(int batch, string program)
    {
        cout << "\n<-------------------------------- Displaying Not Selected Students of Batch " << batch << " and Program " << program << "----------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->program == program && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n--------------------------> Wow !!! All Students of Batch " << batch << " and Program " << program << " are placed <--------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<-------------------------------- End of Not Selected Students of Batch " << batch << " and Program " << program << " ---------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------------- Function to Write Not Selected Students Batch and Program Wise ----------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedBatchAndProgramWise(const string &filepath, int batch, string program)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->program == program && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Program " << program << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Display Not Selected Students ProgramWise of particular Company -------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedCompanyAndProgramWise(string company, string program)
    {
        cout << "\n<-------------------------------------- Displaying Not Selected Students of Program " << program << " and Company " << company << "------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Company " << company << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<----------------------------------- End of Not Selected Students of Program " << program << " and Company " << company << " ------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------- Function to Write Not Selected Students ProgramWise of particular Company ------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedCompanyAndProgramWise(const string &filepath, string company, string program)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Company " << company << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\nData Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Display Not Selected Students BatchWise of particular Year ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedYearAndBatchWise(int year, int batch)
    {
        cout << "\n<-------------------------------------- Displaying Not Selected Students of Batch " << batch << " and Year " << year << "------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Year " << year << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<----------------------------------- End of Not Selected Students of Batch " << batch << " and Year " << year << " ------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------- Function to Write Not Selected Students BatchWise of particulat Year ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedYearAndBatchWise(const string &filepath, int year, int batch)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->batch == batch && Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Batch " << batch << " and Year " << year << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------- Function to Display Not Selected Students Year and Company Wise ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedYearAndCompanyWise(int year, string company)
    {
        cout << "\n<-------------------------------- Displaying Not Selected Students of Year " << year << " and Company " << company << "----------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->year == year && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n--------------------------> Wow !!! All Students of Year " << year << " and Company " << company << " are placed <--------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<-------------------------------- End of Not Selected Students of Year " << year << " and Company " << company << " ---------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------- Function to Write Not Selected Students Year and Company Wise --------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedYearAndCompanyWise(const string &filepath, int year, string company)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->year == year && Current->company == company && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Year " << year << " and Company " << company << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------- Function to Display Not Selected Students ProgramWise of particular Year ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void DisplayNotSelectedYearAndProgramWise(int year, string program)
    {
        cout << "\n<-------------------------------------- Displaying Not Selected Students of Program " << program << " and Year " << year << "------------------------------------->\n";
        cout << endl;
        PrintHorizontalLine(157);
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |   Year   |\n";
        PrintHorizontalLine(157);

        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                     << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                     << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company
                     << "|" << setw(10) << left << Current->year << "|" << endl;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Year " << year << " are placed <---------------------------\n\n";
        }

        PrintHorizontalLine(157);
        cout << "\n<----------------------------------- End of Not Selected Students of Program " << program << " and Year " << year << " ------------------------------------------->\n";
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Write Not Selected Students ProgramWise of particulat Year ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void WriteNotSelectedYearAndProgramWise(const string &filepath, int year, string program)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\n-----> Error in Opening File for Writing Data\n\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company,Year\n";

        int i = 1;
        Node1 *Current = HeadR1;

        bool Success = false;

        while (Current != NULL)
        {
            if (Current->program == program && Current->year == year && TotalStudnetOffers[Current->id] == 0)
            {

                Success = true;

                outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                           << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                           << Current->year << "\n";

                i++;
            }

            Current = Current->next;
        }

        if (!Success)
        {
            cout << "\n---------------------------> Wow !!! All Students of Program " << program << " and Year " << year << " are placed <---------------------------\n\n";
        }
        else
        {
            cout << "\n-----> Data Written Successfully....\n\n";
        }
        outputFile.close();
    }

public:
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //<---------------------------------------------------// FUNCTIONS TO Find Not Selected Student //------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>
    //------------------------------------------------------------------------------------------------------------------------------------------>

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------------------- Function to Find Not Selected Students BatchWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedBatchWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        if (R1BatchAttempts[batch] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " does not found , Enter Valid Batch and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\nDo you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedBatchWise(batch);

        string filepath;
        cout << "\nEnter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedBatchWise(filepath, batch);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Find Not Selected Students ProgramWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedProgramWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        if (R1ProgramAttempts[program] == 0)
        {
            cout << "\n-----> Students of Program " << program << " does not found , Enter Valid program and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedProgramWise(program);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedProgramWise(filepath, program);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------ Function to Find Not Selected Students CompanyWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedCompanyWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        if (R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Company " << company << " does not found , Enter Valid Company and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedCompanyWise(company);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedCompanyWise(filepath, company);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //--------------------------------------- Function to Find Not Selected Students YearWise --------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedYearWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        if (R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Year " << year << " does not found , Enter Valid Year and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedYearWise(year);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedYearWise(filepath, year);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------- Function to Find Not Selected Students Batch and Company Wise --------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedBatchAndCompanyWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        // Find Batch or Company is in Data or Not

        if (R1BatchAttempts[batch] == 0 || R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
            return;
        }

        // Find Batch And Company is in Data or Not

        if (!IsBatchAndCompanyInData(batch, company))
        {
            cout << "\n-----> Students of Batch " << batch << " and Company " << company << " does not found , Enter Valid Batch and Company and Try Again \n\n";
            return;
        }

        char choice;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice;

        if (choice == 'Y')
            DisplayNotSelectedBatchAndCompanyWise(batch, company);

        string filepath;
        cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedBatchAndCompanyWise(filepath, batch, company);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------------- Function to Find Not Selected Students Batch and Program Wise ------------------------------>
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedBatchAndProgramWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int batch;
        cout << "\n#-----> Enter Batch : ";
        cin >> batch;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // Find Batch or Program is in Data or Not

        if (R1BatchAttempts[batch] == 0 || R1ProgramAttempts[program] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
            return;
        }

        // Find Batch And Program is in Data or Not

        if (!IsBatchAndProgramInData(batch, program))
        {
            cout << "\n-----> Students of Batch " << batch << " and Program " << program << " does not found , Enter Valid Batch and Program and Try Again \n\n";
            return;
        }

        char choice;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice;

        if (choice == 'Y')
            DisplayNotSelectedBatchAndProgramWise(batch, program);

        string filepath;
        cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedBatchAndProgramWise(filepath, batch, program);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //---------------------- Function to Find Not Selected Students ProgramWise of particular Company ------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedCompanyAndProgramWise()
    {
        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // Find Program or Company is in Data or Not

        if (R1ProgramAttempts[program] == 0 || R1CompanyAttempts[company] == 0)
        {
            cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
            return;
        }

        // Find Program And Company is in Data or Not

        if (!IsProgramAndCompanyInData(program, company))
        {
            cout << "\n-----> Students of Program " << program << " and Company " << company << " does not found , Enter Valid program and Company Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedCompanyAndProgramWise(company, program);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedCompanyAndProgramWise(filepath, company, program);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //-------------------------- Function to Find Not Selected Students BatchWise of particular Year -------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedYearAndBatchWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int year;
        cout << "\nEnter Year : ";
        cin >> year;

        int batch;
        cout << "\nEnter Batch : ";
        cin >> batch;

        // Find Batch or Year is in Data or Not

        if (R1BatchAttempts[batch] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
            return;
        }

        // Find Batch and Year is in Data or Not

        if (!IsYearAndBatchInData(year, batch))
        {
            cout << "\n-----> Students of Batch " << batch << " and Year " << year << " does not found , Enter Valid Batch and Year and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedYearAndBatchWise(year, batch);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedYearAndBatchWise(filepath, year, batch);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------ Function to Find Not Selected Students ProgramWise of particular Year -------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedYearAndProgramWise()
    {

        if (!IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string program;
        cout << "\n#-----> Enter Program : ";
        getline(cin, program);

        // Find Year or Program is in Data or Not

        if (R1ProgramAttempts[program] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
            return;
        }

        // Find Year and Program is in Data or Not

        if (!IsYearAndProgramInData(year, program))
        {
            cout << "\n-----> Students of Program " << program << " and Year " << year << " does not found , Enter Valid Year and Program and Try Again \n\n";
            return;
        }

        char choice1;
        cout << "\n#-----> Do you to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice1;

        if (choice1 == 'Y')
            DisplayNotSelectedYearAndProgramWise(year, program);

        string filepath;
        cout << "\n#-----> Enter File Path Where you wanted to strore the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedYearAndProgramWise(filepath, year, program);
    }

    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------- Function to Find Not Selected Students Year and Company Wise ---------------------------->
    //------------------------------------------------------------------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------->

    void FindNotSelectedYearAndCompanyWise()
    {
        if (IsDataInserted())
        {
            cout << "\n-----> Insufficient Data Inserted , Insert Data and Try Again \n-----> Thank You \n\n";
            return;
        }

        int year;
        cout << "\n#-----> Enter Year : ";
        cin >> year;

        cin.ignore();

        string company;
        cout << "\n#-----> Enter Company : ";
        getline(cin, company);

        // Find Company or Year is in Data or Not

        if (R1CompanyAttempts[company] == 0 || R1YearAttempts[year] == 0)
        {
            cout << "\n-----> Students of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
            return;
        }

        // Find Year and Company is in Data or Not

        if (!IsYearAndCompanyInData(year, company))
        {
            cout << "\n-----> Students of Company " << company << " and Year " << year << " does not found , Enter Valid Company and Year and Try Again \n\n";
            return;
        }

        char choice;
        cout << "\n#-----> Do you want to Display Data(Y/N) ? \n#-----> Ans : ";
        cin >> choice;

        if (choice == 'Y')
            DisplayNotSelectedYearAndCompanyWise(year, company);

        string filepath;
        cout << "\n#-----> Enter File Path Where you want to store the Sorted Data : ";
        cin >> filepath;

        WriteNotSelectedYearAndCompanyWise(filepath, year, company);
    }
};
