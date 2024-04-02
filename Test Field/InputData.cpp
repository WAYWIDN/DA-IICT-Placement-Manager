#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
// #include "class_PlacementManager.cpp"
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
    Node1 *next;

    Node1(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company)
    {
        this->id = id;
        this->name = name;
        this->batch = batch;
        this->program = program;
        this->email = email;
        this->contactNO = contactNO;
        this->whatsappNO = whatsappNO;
        this->company = company;
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
    float pakage;
    Node2 *next;

    Node2(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, float pakage)
    {
        this->id = id;
        this->name = name;
        this->batch = batch;
        this->program = program;
        this->email = email;
        this->contactNO = contactNO;
        this->whatsappNO = whatsappNO;
        this->company = company;
        this->pakage = pakage;
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

// Variables to keep Track on student's attempt and Job Offers

unordered_map<long long, int> R1Attempts;
unordered_map<long long, int> R2Attempts;
unordered_map<long long, int> R3Attempts;
unordered_map<long long, int> R4Attempts;
unordered_map<long long, int> TotalOffers;

// Variables to keep Track on whole Placement Statics

int NOofStudentR1;
int NOofStudentR2;
int NOofStudentR3;
int NOofStudentR4;
int NOofStudentFR;
float TotalPackage;

//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>
//-------------------------------------------------- Functions to Create list for Respective Round ----------------------------------------->
//------------------------------------------------------------------------------------------------------------------------------------------>
//------------------------------------------------------------------------------------------------------------------------------------------>

//--------------------------------------------------------------------------------------------------------------------->
//------------------------------------------------Function to add Node in Round1's list-------------------------------->

void addToListR1(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company)
{
    Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company);

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

void addToListR2(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company)
{
    Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company);

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

void addToListR3(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company)
{
    Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company);

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

void addToListR4(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company)
{
    Node1 *NewNode = new Node1(id, name, batch, program, email, contactNO, whatsappNO, company);

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

void addToListFR(long long id, string name, int batch, string program, string email, long long contactNO, long long whatsappNO, string company, float pakage)
{
    Node2 *NewNode = new Node2(id, name, batch, program, email, contactNO, whatsappNO, company, pakage);

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

        cout << "\nFatching Data from The Round1's File---->\n";

        string line;

        getline(file, line); // Skip the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            //--->Extract data from each line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str;
            int batch;
            long long id, contactNO, whatsappNO;

            getline(ss, WordToSkip, ','); // Ignore the Sr No.
            getline(ss, id_str, ',');
            id = stoll(id_str);
            batch = stoi(id_str.substr(0, 4)); // First 4 digits are batch
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, WordToSkip, ','); // Ignore Interview Date
            getline(ss, email, ',');
            getline(ss, conatctNO_str, ',');
            contactNO = stoll(conatctNO_str);
            getline(ss, whatsappNO_str, ',');
            whatsappNO = stoll(whatsappNO_str);

            addToListR1(id, name, batch, program, email, contactNO, whatsappNO, CompanyName); // Insert the extracted data into the list

            R1Attempts[id]++; // Increment in Number of Attempts in R1 by student

            NOofStudentR1++; // Increment in Number of student who passed in Round 1
        }

        cout << "<----Successfully Data Fatched From the Round1's File \n";
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

        cout << "\nFatching Data from The Round2's File---->\n";

        string line;

        getline(file, line); // Skip the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            //--->Extract data from each line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str;
            int batch;
            long long id, contactNO, whatsappNO;

            getline(ss, WordToSkip, ','); // Ignore the Sr No.
            getline(ss, id_str, ',');
            id = stoll(id_str);
            batch = stoi(id_str.substr(0, 4)); // First 4 digits are batch
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, WordToSkip, ','); // Ignore Interview Date
            getline(ss, email, ',');
            getline(ss, conatctNO_str, ',');
            contactNO = stoll(conatctNO_str);
            getline(ss, whatsappNO_str, ',');
            whatsappNO = stoll(whatsappNO_str);

            addToListR2(id, name, batch, program, email, contactNO, whatsappNO, CompanyName); // Insert the extracted data into the list

            R2Attempts[id]++; // Increment in Number of Attempts in R1 by student

            NOofStudentR2++; // Increment in Number of student who passed in Round 2
        }

        cout << "<----Successfully Data Fatched From the Round2's File \n";
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

        cout << "\nFatching Data from The Round3's File---->\n";

        string line;

        getline(file, line); // Skip the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            //--->Extract data from each line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str;
            int batch;
            long long id, contactNO, whatsappNO;

            getline(ss, WordToSkip, ','); // Ignore the Sr No.
            getline(ss, id_str, ',');
            id = stoll(id_str);
            batch = stoi(id_str.substr(0, 4)); // First 4 digits are batch
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, WordToSkip, ','); // Ignore Interview Date
            getline(ss, email, ',');
            getline(ss, conatctNO_str, ',');
            contactNO = stoll(conatctNO_str);
            getline(ss, whatsappNO_str, ',');
            whatsappNO = stoll(whatsappNO_str);

            addToListR3(id, name, batch, program, email, contactNO, whatsappNO, CompanyName); // Insert the extracted data into the list

            R3Attempts[id]++; // Increment in Number of Attempts in R1 by student

            NOofStudentR3++; // Increment in Number of student who passed in Round 3
        }

        cout << "<----Successfully Data Fatched From the Round3's File \n";
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

        cout << "\nFatching Data from The Round4's File---->\n";

        string line;

        getline(file, line); // Skip the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            //--->Extract data from each line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str;
            int batch;
            long long id, contactNO, whatsappNO;

            getline(ss, WordToSkip, ','); // Ignore the Sr No.
            getline(ss, id_str, ',');
            id = stoll(id_str);
            batch = stoi(id_str.substr(0, 4)); // First 4 digits are batch
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, WordToSkip, ','); // Ignore Interview Date
            getline(ss, email, ',');
            getline(ss, conatctNO_str, ',');
            contactNO = stoll(conatctNO_str);
            getline(ss, whatsappNO_str, ',');
            whatsappNO = stoll(whatsappNO_str);

            addToListR4(id, name, batch, program, email, contactNO, whatsappNO, CompanyName); // Insert the extracted data into the list

            R4Attempts[id]++; // Increment in Number of Attempts in R1 by student

            NOofStudentR4++; // Increment in Number of student who passed in Round 4
        }

        cout << "<----Successfully Data Fatched From the Round4's File \n";
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

        cout << "\nFatching Data from The Final Round's File---->\n";

        string line;

        getline(file, line); // Skip the first line

        while (getline(file, line))
        {
            stringstream ss(line);

            //--->Extract data from each line

            // Variables to Extact Data

            string WordToSkip; // To Skip Unnecessary data

            string id_str, name, program, email, conatctNO_str, whatsappNO_str, package_str;
            int batch;
            long long id, contactNO, whatsappNO;
            float package;

            getline(ss, WordToSkip, ','); // Ignore the Sr No.
            getline(ss, id_str, ',');
            id = stoll(id_str);
            batch = stoi(id_str.substr(0, 4)); // First 4 digits are batch
            getline(ss, name, ',');
            getline(ss, program, ',');
            getline(ss, WordToSkip, ','); // Ignore Interview Date
            getline(ss, email, ',');
            getline(ss, conatctNO_str, ',');
            contactNO = stoll(conatctNO_str);
            getline(ss, whatsappNO_str, ',');
            whatsappNO = stoll(whatsappNO_str);
            getline(ss, package_str, ',');
            package = stof(package_str);

            addToListFR(id, name, batch, program, email, contactNO, whatsappNO, CompanyName, package); // Insert the extracted data into the list

            TotalOffers[id]++; // Increment in Job Offers Student got

            NOofStudentFR++; // Increment in Number of student who passed in Final Round

            TotalPackage += package; // Increment in Total Amount of Pakage Offered
        }

        cout << "<----Successfully Data Fatched From the Final Round's File \n";
    }
}
 void PrintHorizontalLine(int width, char fillChar = '-')
    {
        cout << setfill(fillChar) << setw(width) << "" << setfill(' ') << endl;
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
  void DisplayRound1to4WholeData(Node1 *Head)
    {
        cout << endl;
        PrintHorizontalLine(147); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |\n";
        PrintHorizontalLine(147); // Printing horizontal line
        Node1 *Current = Head;
        while (Current != NULL)
        {
            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << endl;
            Current = Current->next;
        }
    }

    //---------------------------------------Helper Function to Display Whole Data for Final Round ------------------------------->

    void DisplayFinalRoundWholeData(Node2 *Head)
    {
        cout << endl;
        PrintHorizontalLine(157); // Printing horizontal line
        cout << "|    ID    |        Name        |   Batch  |    Program    |          Email          |   Contact No  |  WhatsApp No  |      Company       |    Package   |\n";
        PrintHorizontalLine(157); // Printing horizontal line
        Node2 *Current = Head;
        while (Current != NULL)
        {
            cout << "|" << setw(10) << left << Current->id << "|" << setw(20) << left << Current->name << "|" << setw(10) << left << Current->batch
                 << "|" << setw(15) << left << Current->program << "|" << setw(25) << left << Current->email << "|" << setw(15) << left << Current->contactNO
                 << "|" << setw(15) << left << Current->whatsappNO << "|" << setw(20) << left << Current->company << "|" << setw(15) << left << Current->pakage << "|" << endl;
            Current = Current->next;
        }
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
    void WriteWholeSortedDataForRound1to4(const string &filepath, Node1 *Head)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\nError in Opening File for Writing Data\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company\n";

        int i = 1;
        Node1 *Current = Head;
        while (Current != nullptr)
        {
            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << "\n";

            Current = Current->next;
            i++;
        }

        outputFile.close();
    }

    //---------------------------------------Helper Function to Write Whole Sorted Data of Final Round ------------------------------->

    void WriteWholeSortedDataForFinalRound(const string &filepath, Node2 *Head)
    {
        ofstream outputFile(filepath);

        if (!outputFile.is_open())
        {
            cerr << "\nError in Opening File for Writing Data\n";
            return;
        }

        outputFile << "Sr.no,ID,Name,Batch,Program,Email,Contact No,WhatsApp No,Company\n";

        int i = 1;
        Node2 *Current = Head;
        while (Current != nullptr)
        {
            outputFile << i << "," << Current->id << "," << Current->name << "," << Current->batch << "," << Current->program << ","
                       << Current->email << "," << Current->contactNO << "," << Current->whatsappNO << "," << Current->company << ","
                       << Current->pakage << "\n";

            Current = Current->next;
            i++;
        }

        outputFile.close();
    }

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

            if (choice2== 'Y')
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
