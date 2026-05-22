/*************************************************************************
                           StatisticsService  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Statistics> (fichier Xxx.h) ----------------
#if ! defined ( STATISTICSSERVICE_H )
#define STATISTICSSERVICE_H

#include <ctime>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "../model/Sensor.h"
#include "../model/TimeRange.h"
#include "../model/User.h"

using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <StatisticsService>
// Fournit les calculs statistiques et indicateurs de qualité de l'air
// à partir des capteurs, mesures et périodes d'observation.
//------------------------------------------------------------------------

class StatisticsService
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    static double calculateAirQuality(double lat, double lon, DateTime time);
    // Mode d'emploi :
    // Calcule l'indice ATMO global à un instant donné sur l'ensemble du système,
    // en pondérant les mesures des capteurs fiables par leur distance.

    static double estimateAirQuality(double lat, double lon);
    // Mode d'emploi :
    // Estime la qualité de l'air à une position géographique sans filtrage par utilisateur.

    static double viewCleanerImpact(const User& user, string cleanerID, TimeRange period);
    // Mode d'emploi :
    // Mesure l'amélioration de la qualité de l'air autour d'un purificateur sur une période donnée.

    static vector<Sensor> compareSensorsBySimilarity(const User& user, string targetSensor, TimeRange period);
    // Mode d'emploi :
    // Compare un capteur cible aux autres capteurs fiables et les trie par similarité croissante.

    static double calculateAreaMean(const User& user, double lat, double lon, double radius, TimeRange period);
    // Mode d'emploi :
    // Calcule l'indice ATMO moyen d'une zone géographique sur une période donnée.

    static double analyzeCleanerRadius(const User& user, string cleanerID);
    // Mode d'emploi :
    // Détermine le rayon d'influence utile d'un purificateur en testant plusieurs rayons.

    static string getZoneStatistic(const User& user, double lat, double lon, double radius, TimeRange period);
    // Mode d'emploi :
    // Produit un résumé textuel d'une zone: moyenne AQI, pics, minimum et polluant dominant.

    static double calculateLocalAQI(const User& user, double lat, double lon, double radius, TimeRange period);
    // Mode d'emploi :
    // Calcule l'indice ATMO local à partir du capteur le plus proche dans la zone.

    static double convertirVersIndiceATMO(map<string, double> moyennesEstimees);
    // Mode d'emploi :
    // Convertit des moyennes de polluants en indice ATMO final en gardant le pire score.

//-------------------------------------------- Constructeurs - destructeur

    StatisticsService ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe StatisticsService.

    ~StatisticsService ( );
    // Mode d'emploi :
    // Destructeur de la classe StatisticsService.
    
};


#endif // STATISTICSSERVICE_H
