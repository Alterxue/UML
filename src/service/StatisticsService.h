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
    static std::string analyzeSensorData(const std::string& sensorID, const TimeRange& period);
    // Mode d'emploi :
    // Analyse les données d'un capteur sur une période donnée et retourne un rapport textuel
    
    static double calculateAreaMean(double lat, double lon, double radius, const TimeRange& period);
    // Mode d'emploi :
    // Calcule l'indice ATMO moyen d'une zone géographique sur une période donnée.

    static double calculateAreaMean(double lat, double lon, double radius, const DateTime& moment);
    // Mode d'emploi :
    // Surcharge de calculateAreaMean pour calculer l'indice à un instant précis.

    static std::vector<Sensor> compareSensorsBySimilarity(std::string targetSensor, TimeRange period);
    // Mode d'emploi :
    // Compare un capteur cible aux autres capteurs fiables et les trie par similarité croissante.

    static std::map<std::string, std::vector<Sensor>> compareNeighborhoodSensors(const User& user, double radius, TimeRange period);
    // Mode d'emploi :
    // Sélectionne les capteurs dans un rayon autour d'une position puis, pour
    // chaque capteur fiable trouvé, appelle `compareSensorsBySimilarity`.
    // Renvoie une map {targetSensorID: liste des capteurs similaires}.

    static double calculateAirQuality(double lat, double lon, const DateTime& time);
    // Mode d'emploi :
    // Calcule l'indice ATMO global à un instant donné sur l'ensemble du système,
    // en pondérant les mesures des capteurs fiables par leur distance.

    static double convertirVersIndiceATMO(std::map<std::string, double> moyennesEstimees);
    // Mode d'emploi :
    // Convertit des moyennes de polluants en indice ATMO final en gardant le pire score.

    static double calculateUserZoneAQI(const User& user, double radius, const TimeRange& period);
    // Mode d'emploi :
    // Calcule l'indice ATMO moyen de la zone autour de l'utilisateur.
    // La position centrale est déterminée à partir des capteurs de l'utilisateur
    // (moyenne des positions). Utilise `calculateAreaMean` en interne.

    static double viewCleanerImpact(const User& user, std::string cleanerID, TimeRange period);
    // Mode d'emploi :
    // Mesure l'amélioration de la qualité de l'air autour d'un purificateur sur une période donnée.

    static double analyzeCleanerRadius(const User& user, std::string cleanerID);
    // Mode d'emploi :
    // Détermine le rayon d'influence utile d'un purificateur en testant plusieurs rayons.
    
    static std::string getZoneStatistic(const User& user, double lat, double lon, double radius, TimeRange period);
    // Mode d'emploi :
    // Produit un résumé textuel d'une zone: moyenne AQI, pics, minimum et polluant dominant.



    

//-------------------------------------------- Constructeurs - destructeur

    StatisticsService ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe StatisticsService.

    ~StatisticsService ( );
    // Mode d'emploi :
    // Destructeur de la classe StatisticsService.
    
};


#endif // STATISTICSSERVICE_H
