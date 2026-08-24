#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <string>

using namespace std;

class Query
{
private:
    long long id = 0;
    string name = "";
    int batch = 0;
    string program = "";
    string email = "";
    long long contactNO = 0;
    long long whatsappNO = 0;
    string company = "";
    int year = 0;
    float package = 0;

public:
    // Setters

    Query &setId(long long id)
    {
        this->id = id;
        return *this;
    }

    Query &setName(string name)
    {
        this->name = name;
        return *this;
    }

    Query &setBatch(int batch)
    {
        this->batch = batch;
        return *this;
    }

    Query &setProgram(string program)
    {
        this->program = program;
        return *this;
    }

    Query &setEmail(string email)
    {
        this->email = email;
        return *this;
    }

    Query &setContactNO(long long contactNO)
    {
        this->contactNO = contactNO;
        return *this;
    }

    Query &setWhatsappNO(long long whatsappNO)
    {
        this->whatsappNO = whatsappNO;
        return *this;
    }

    Query &setCompany(string company)
    {
        this->company = company;
        return *this;
    }

    Query &setYear(int year)
    {
        this->year = year;
        return *this;
    }

    Query &setPackage(float package)
    {
        this->package = package;
        return *this;
    }

    // Getters

    long long getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    int getBatch()
    {
        return batch;
    }

    string getProgram()
    {
        return program;
    }

    string getEmail()
    {
        return email;
    }

    long long getContactNO()
    {
        return contactNO;
    }

    long long getWhatsappNO()
    {
        return whatsappNO;
    }

    string getCompany()
    {
        return company;
    }

    int getYear()
    {
        return year;
    }

    float getPackage()
    {
        return package;
    }

    // Match
    template <typename Record>
    bool matches(Record &record)
    {
        return (id == 0 || record.id == id) &&
               (batch == 0 || record.batch == batch) &&
               (program == "" || record.program == program) &&
               (company == "" || record.company == company) &&
               (year == 0 || record.year == year);
    }
};

#endif
