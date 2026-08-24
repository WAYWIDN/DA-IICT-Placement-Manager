#ifndef PLACEMENT_MANAGER_H
#define PLACEMENT_MANAGER_H

#include "./io/FileService.h"
#include "./services/QueryService.h"
#include "./services/StatisticsService.h"

using namespace std;

class PlacementManager
{
private:
    Repository repository;
    FileService fileService;
    QueryService queryService;
    StatisticsService statisticsService;

public:
    PlacementManager() : fileService(repository), queryService(repository), statisticsService(repository)
    {
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //----------------------------------------------------> Input Placement Data <-------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void LoadCompanyData()
    {
        fileService.LoadCompanyData();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //----------------------------------------------------> Sorting Functions <----------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void SortWholeData()
    {
        queryService.SortWholeData();
    }

    void SortDataBatchWise()
    {
        queryService.SortDataBatchWise();
    }

    void SortDataProgramWise()
    {
        queryService.SortDataProgramWise();
    }

    void SortDataYearWise()
    {
        queryService.SortDataYearWise();
    }

    void SortDataCompanyWise()
    {
        queryService.SortDataCompanyWise();
    }

    void SortDataBatchAndProgramWise()
    {
        queryService.SortDataBatchAndProgramWise();
    }

    void SortDataBatchAndCompanyWise()
    {
        queryService.SortDataBatchAndCompanyWise();
    }

    void SortDataProgramAndCompanyWise()
    {
        queryService.SortDataProgramAndCompanyWise();
    }

    void SortDataYearAndBatchWise()
    {
        queryService.SortDataYearAndBatchWise();
    }

    void SortDataYearAndProgramWise()
    {
        queryService.SortDataYearAndProgramWise();
    }

    void SortDataYearAndCompanyWise()
    {
        queryService.SortDataYearAndCompanyWise();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //-----------------------------------------------> Placement Statistics Functions <---------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void FindOverallPlacementStatistics()
    {
        statisticsService.FindOverallPlacementStatistics();
    }

    void FindStudentPlacementDetails()
    {
        statisticsService.FindStudentPlacementDetails();
    }

    void FindBatchWisePlacementStatistics()
    {
        statisticsService.FindBatchWisePlacementStatistics();
    }

    void FindProgramWisePlacementStatistics()
    {
        statisticsService.FindProgramWisePlacementStatistics();
    }

    void FindCompanyWisePlacementStatistics()
    {
        statisticsService.FindCompanyWisePlacementStatistics();
    }

    void FindYearWisePlacementStatistics()
    {
        statisticsService.FindYearWisePlacementStatistics();
    }

    void FindBatchAndCompanyWisePlacementStatistics()
    {
        statisticsService.FindBatchAndCompanyWisePlacementStatistics();
    }

    void FindBatchAndProgramWisePlacementStatistics()
    {
        statisticsService.FindBatchAndProgramWisePlacementStatistics();
    }

    void FindProgramAndCompanyWisePlacementStatistics()
    {
        statisticsService.FindProgramAndCompanyWisePlacementStatistics();
    }

    void FindYearAndBatchWisePlacementStatistics()
    {
        statisticsService.FindYearAndBatchWisePlacementStatistics();
    }

    void FindYearAndProgramWisePlacementStatistics()
    {
        statisticsService.FindYearAndProgramWisePlacementStatistics();
    }

    void FindYearAndCompanyWisePlacementStatistics()
    {
        statisticsService.FindYearAndCompanyWisePlacementStatistics();
    }

    //------------------------------------------------------------------------------------------------------------------------------------------>
    //--------------------------------------------> Not-Selected Student Functions <------------------------------------------------------------->
    //------------------------------------------------------------------------------------------------------------------------------------------>

    void FindNotSelectedBatchWise()
    {
        queryService.FindNotSelectedBatchWise();
    }

    void FindNotSelectedProgramWise()
    {
        queryService.FindNotSelectedProgramWise();
    }

    void FindNotSelectedCompanyWise()
    {
        queryService.FindNotSelectedCompanyWise();
    }

    void FindNotSelectedYearWise()
    {
        queryService.FindNotSelectedYearWise();
    }

    void FindNotSelectedBatchAndCompanyWise()
    {
        queryService.FindNotSelectedBatchAndCompanyWise();
    }

    void FindNotSelectedBatchAndProgramWise()
    {
        queryService.FindNotSelectedBatchAndProgramWise();
    }

    void FindNotSelectedCompanyAndProgramWise()
    {
        queryService.FindNotSelectedCompanyAndProgramWise();
    }

    void FindNotSelectedYearAndBatchWise()
    {
        queryService.FindNotSelectedYearAndBatchWise();
    }

    void FindNotSelectedYearAndProgramWise()
    {
        queryService.FindNotSelectedYearAndProgramWise();
    }

    void FindNotSelectedYearAndCompanyWise()
    {
        queryService.FindNotSelectedYearAndCompanyWise();
    }
};

#endif
