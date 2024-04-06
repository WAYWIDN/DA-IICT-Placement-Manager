
///////////////////////////////////////////////////////////////////////////////////////////////
////////////// Testing Function to Sort Student Data Batch and Company Wise  //////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "All Functions\SortBatchAndCompanyWise.cpp"
using namespace std;

int main()
{
    ReadFileForRound1("Input Files/Company1R1.csv", "Apple");
    ReadFileForRound2("Input Files/Company1R2.csv", "Apple");
    ReadFileForRound3("Input Files/Company1R3.csv", "Apple");
    ReadFileForRound4("Input Files/Company1R4.csv", "Apple");
    ReadFileForFinalRound("Input Files/Company1FR.csv", "Apple");

    ReadFileForRound1("Input Files/Company2R1.csv", "Amazon");
    ReadFileForRound2("Input Files/Company2R2.csv", "Amazon");
    ReadFileForRound3("Input Files/Company2R3.csv", "Amazon");
    ReadFileForRound4("Input Files/Company2R4.csv", "Amazon");
    ReadFileForFinalRound("Input Files/Company2FR.csv", "Amazon");

    ReadFileForRound1("Input Files/Company3R1.csv", "Google");
    ReadFileForRound2("Input Files/Company3R2.csv", "Google");
    ReadFileForRound3("Input Files/Company3R3.csv", "Google");
    ReadFileForRound4("Input Files/Company3R4.csv", "Google");
    ReadFileForFinalRound("Input Files/Company3FR.csv", "Google");

    ReadFileForRound1("Input Files/Company4R1.csv", "Microsoft");
    ReadFileForRound2("Input Files/Company4R2.csv", "Microsoft");
    ReadFileForRound3("Input Files/Company4R3.csv", "Microsoft");
    ReadFileForRound4("Input Files/Company4R4.csv", "Microsoft");
    ReadFileForFinalRound("Input Files/Company4FR.csv", "Microsoft");

    ReadFileForRound1("Input Files/Company5R1.csv", "D.E. Shaw");
    ReadFileForRound2("Input Files/Company5R2.csv", "D.E. Shaw");
    ReadFileForRound3("Input Files/Company5R3.csv", "D.E. Shaw");
    ReadFileForRound4("Input Files/Company5R4.csv", "D.E. Shaw");
    ReadFileForFinalRound("Input Files/Company5FR.csv", "D.E. Shaw");

    SortDataBatchAndCompanyWise() ;

    return 0;
}