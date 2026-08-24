#ifndef RECORD_H
#define RECORD_H

#include <string>
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

#endif
