#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
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
            R4BatchAttempts[batch]++;                   // Increment in Number of Student of particular Batch who had attempted in Round 4
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

void InputPlacementData()
{
    string CompanyName;
    cout << "\nEnter Company's Name : ";
    cin >> CompanyName;

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
//--------------------------------------- Function to Find Median Package --------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->
//--------------------------------------------------------------------------------------------------------------------->

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

//--->Helper function to print a horizontal line

void PrintHorizontalLine(int width, char fillChar = '-')
{
    cout << setfill(fillChar) << setw(width) << "" << setfill(' ') << endl;
}
