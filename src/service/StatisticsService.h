/*************************************************************************
                           StatisticsService  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#if ! defined ( StatisticsServcie_H )
#define StatisticsService_H
#include <ctime>
#include <string>
#include <list>
#include "Sensor.h"
#include "TimeRange.h"
using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Xxx>
//
//
//------------------------------------------------------------------------

class StatisticsService :
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    static double calculateAirQuality(User user, double lat,double lon,time_t time);

    static double estimateAirQuality(double lat, double long);

    static double viewCleanerImpact(User user, string cleanerID, TimeRange period);

    static list<Sensor> compareSensorsBySimilarity(User user,string targetSensor, TimeRange period);

    static double calculateAreaMean(User user, double lat,double lon,double radius,TimeRange period);

    static double analyzeCleanerRadius(User user,string cleanerID);

    static string getZoneStatistic(User user, double lat, double lon,double radius, TimeRange period);

    static double calculateLocalAQI(User user, double lat, double lon, double radius);

    static double convertirVersIndiceATMO(map<string, double> moyennesEstimees);

//-------------------------------------------- Constructeurs - destructeur

    StatisticsService ( );

    virtual ~StatisticsService ( );
    
};


#endif
