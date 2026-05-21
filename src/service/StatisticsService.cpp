/*************************************************************************
                           Statisticsservice      -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Xxx> (fichier Xxx.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../model/Sensor.h"
#include "../model/TimeRange.h"
#include "DataService.h"
#include "StatisticsService.h"
using namespace std;


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

double StatisticsService::calculateAirQuality(const User& user, double lat, double lon, DateTime time){
    // commencer a compter le temps
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // obtenir les listes de capteurs et mesures
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<Measurement*> toutesMesures = DataService::getMeasurements(user);
    
    map<string, double> sommesPonderees;  
    map<string, double> sommePoids;      
    for (const auto& capteur : tousCapteurs){
        if (capteur == nullptr) {
            continue;
        }
        if (capteur->getReliability() == true){
            double distance = capteur->calculateDistance(lat,lon);
            double poids = (distance < 0.1) ? 100 : 1 / (distance * distance);
            for(const auto& mesure : toutesMesures){
                if(mesure != nullptr && mesure->getSensor()->getSensorID() == capteur->getSensorID() && mesure->getMeasureDate() == time){
                    string attrID = mesure->getAttribute()->getAttributeID();
                    sommesPonderees[attrID] += (mesure->getValue() * poids);
                    sommePoids[attrID] += poids;
                }
            }
        }
    }
    
    map<string, double> moyennesEstimees;
    for (const auto& pair : sommesPonderees) {
        string attributeID = pair.first;
        double sommePonderee = pair.second;
        
        if (sommePoids[attributeID] > 0) {
            moyennesEstimees[attributeID] = sommePonderee / sommePoids[attributeID];
        }
    }

    double indiceGlobal = 0.0;
    indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennesEstimees);
    
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution calculateAirQuality : " << duree.count() << " ms" << endl;
    
    return indiceGlobal;
}

double StatisticsService::calculateAreaMean(const User& user, double lat, double lon, double radius, TimeRange period){
    //le temps de début
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // Récupération de toutes les données via DataService
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<Measurement*> toutesMesures = DataService::getMeasurements(user);
    
    // Filtrage spatial et fiabilité - récupérer les capteurs dans la zone
    vector<Sensor*> capteursZone;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        double distance = capteur->calculateDistance(lat, lon);
        // Vérifier si le capteur est dans le rayon ET est fiable
        if (distance <= radius && capteur->getReliability() == true) {
            capteursZone.push_back(capteur);
        }
    }
    
    //Agrégation des mesures correspondantes
    map<string, double> sommesAttributs;    
    map<string, int> comptesAttributs;      
    
    for (const auto& capteur : capteursZone) {
        for (const auto& mesure : toutesMesures) {
            if (capteur != nullptr && mesure != nullptr && mesure->getSensor()->getSensorID() == capteur->getSensorID() && 
                period.contains(mesure->getMeasureDate())) {

                string attrID = mesure->getAttribute()->getAttributeID();
                sommesAttributs[attrID] += mesure->getValue();
                comptesAttributs[attrID] += 1;

            }
        }
    }
    
    //Calcul des moyennes par attribut
    map<string, double> moyennes;
    
    for (const auto& pair : sommesAttributs) {
        string attributeID = pair.first;
        double sommeAttribut = pair.second;
        
        if (comptesAttributs[attributeID] > 0) {
            moyennes[attributeID] = sommeAttribut / comptesAttributs[attributeID];
        }
    }
    
    double indiceGlobal = 0.0;
    indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennes);

    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution calculateAreaMean : " << duree.count() << " ms" << endl;
    
    // Retourner l'indice global
    return indiceGlobal;
}


vector<Sensor> StatisticsService::compareSensorsBySimilarity(const User& user, string targetSensor, TimeRange period){
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    //Récupération de toutes les données
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<Measurement*> toutesMesures = DataService::getMeasurements(user);
    
    // Extraction des données du capteur cible pour la période
    vector<Measurement*> donneesCible;
    
    for (const auto& mesure : toutesMesures) {
        if (mesure != nullptr && mesure->getSensor()->getSensorID() == targetSensor && period.contains(mesure->getMeasureDate())) {
            donneesCible.push_back(mesure);
        }
    }
    
    //Calcul des scores de similarité pour chaque capteur
    map<string, double> scoresSimilarite;  // {sensorID: écart moyen}
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        // Ignorer le capteur cible et les capteurs non fiables
        if (capteur->getSensorID() == targetSensor || capteur->getReliability() == false) {
            continue;
        }
        
        //Extraction des données du capteur actuel pour la période
        vector<Measurement*> donneesAComparer;
        for (const auto& mesure : toutesMesures) {
            if (mesure != nullptr && mesure->getSensor()->getSensorID() == capteur->getSensorID() && period.contains(mesure->getMeasureDate())) {
                donneesAComparer.push_back(mesure);
            }
        }
        
        // Calcul de l'écart moyen entre le capteur cible et le capteur actuel
        double differenceTotale = 0.0;
        int pointsCommuns = 0;
        
        for (const auto& mesureCible : donneesCible) {
            // Chercher la mesure correspondante (même timestamp et attributeID)
            bool trouve = false;
            
            for (const auto& mesureAComparer : donneesAComparer) {
                if (mesureAComparer != nullptr && mesureCible != nullptr &&
                    mesureAComparer->getMeasureDate() == mesureCible->getMeasureDate() && 
                    mesureAComparer->getAttribute()->getAttributeID() == mesureCible->getAttribute()->getAttributeID()) {
                    
                    // Calculer la différence absolue entre les deux valeurs
                    double difference = abs(mesureCible->getValue() - mesureAComparer->getValue());
                    differenceTotale += difference;
                    pointsCommuns += 1;
                    trouve = true;
                    break;
                }
            }
        }
        
        //Calcul de l'écart moyen et stockage du score
        if (pointsCommuns > 0) {
            double ecartMoyen = differenceTotale / pointsCommuns;
            scoresSimilarite[capteur->getSensorID()] = ecartMoyen;
        }
    }
    
    // Tri des capteurs par ordre croissant d'écart moyen (plus petit = plus similaire)
    // Créer une liste de paires (sensorID, écart) et la trier
    vector<pair<string, double>> scoresVecteur(scoresSimilarite.begin(), scoresSimilarite.end());
    
    sort(scoresVecteur.begin(), scoresVecteur.end(), 
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second < b.second;  // Tri croissant
         });
    
    // Reconstruire la liste de capteurs triée
    vector<Sensor> listeTriee;
    
    for (const auto& pair : scoresVecteur) {
        // Trouver le capteur correspondant dans la liste originale
        for (const auto& capteur : tousCapteurs) {
            if (capteur != nullptr && capteur->getSensorID() == pair.first) {
                listeTriee.push_back(*capteur);
                break;
            }
        }
    }
    // Enregistrer le temps de fin et calculer la durée
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution compareSensorsBySimilarity : " << duree.count() << " ms" << endl;
    
    return listeTriee;
}


double StatisticsService::analyzeCleanerRadius(const User& user, string cleanerID){
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    AirCleaner* cleaner = DataService::getCleanerById(cleanerID);
    if (cleaner == nullptr) {
        cout << "ERROR: Cleaner " << cleanerID << " not found" << endl;
        return 0.0;
    }
    TimeRange workingPeriod = cleaner->getWorkingPeriod();
    DateTime startTime = workingPeriod.getStart();
    DateTime stopTime = workingPeriod.getEnd();
    auto dureeFonctionnement = stopTime - startTime;
    
    TimeRange periodePendant(startTime, stopTime);
    TimeRange periodeAvant(startTime - dureeFonctionnement, startTime);
    
    double rayonImpact = 0.0;
    double meilleureAmelioration = 0.0;
    
    for (double rayon = 1.0; rayon <= 10.0; rayon += 1.0) {
        // la qualite avant activation de aircleaner
        double aqiAvant = calculateAreaMean(user, cleaner->getLattitude(), cleaner->getLongitude(), rayon, periodeAvant);
        double aqiPendant = calculateAreaMean(user, cleaner->getLattitude(), cleaner->getLongitude(), rayon, periodePendant);
        
        if (aqiPendant < aqiAvant) {
            double amelioration = ((aqiAvant - aqiPendant) / aqiAvant) * 100.0;
            
            if (amelioration > 5.0) {
                rayonImpact = rayon;
                
                if (amelioration > meilleureAmelioration) {
                    meilleureAmelioration = amelioration;
                }
            } else {
                break; 
            }
        } else {
            break;
        }
    }
    
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution analyzeCleanerRadius : " << duree.count() << " ms" << endl;
    cout << "Rayon d'impact : " << rayonImpact << " km | Meilleure amélioration : " << meilleureAmelioration << "%" << endl;
    
    //renvoyer le radius utile
    return rayonImpact;
}


string StatisticsService::getZoneStatistic(const User& user, double lat, double lon, double radius, TimeRange period){
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // Get all sensors in the area
    vector<Sensor*> listeCapteurs = DataService::getSensorsInArea(lat, lon, radius);
    vector<Measurement*> toutesMesures = DataService::getMeasurements(user);
    
    // Filter measurements by sensor and time period
    vector<Measurement*> mesuresZone;
    for (const auto& mesure : toutesMesures) {
        if (mesure == nullptr) continue;
        for (const auto& capteur : listeCapteurs) {
            if (capteur != nullptr && mesure->getSensor()->getSensorID() == capteur->getSensorID() && period.contains(mesure->getMeasureDate())) {
                mesuresZone.push_back(mesure);
            }
        }
    }
    
    // If no data available, return error message
    if (mesuresZone.empty()) {
        return "ERROR: No data available for this area and period";
    }
    
    // 1. Calculate global average AQI (reuse calculateAreaMean)
    double moyenneAQI = calculateAreaMean(user, lat, lon, radius, period);
    
    // 2. Find pollution peaks
    double maxAQI = 0.0;
    double minAQI = 10.0;
    
    for (const auto& mesure : mesuresZone) {
        if (mesure == nullptr) continue;
        map<string, double> mesureMap;
        mesureMap[mesure->getAttribute()->getAttributeID()] = mesure->getValue();
        double aqiActuel = StatisticsService::convertirVersIndiceATMO(mesureMap);
        
        if (aqiActuel > maxAQI) {
            maxAQI = aqiActuel;
        }
        if (aqiActuel < minAQI) {
            minAQI = aqiActuel;
        }
    }
    
    // 3. Identify dominant pollutant
    map<string, double> sommesPolluants;
    map<string, int> comptesPolluants;
    
    for (const auto& mesure : mesuresZone) {
        if (mesure == nullptr) continue;
        string attrID = mesure->getAttribute()->getAttributeID();
        sommesPolluants[attrID] += mesure->getValue();
        comptesPolluants[attrID] += 1;
    }
    
    string polluantPrincipal = "";
    double maxValeur = 0.0;
    
    for (const auto& pair : sommesPolluants) {
        double moyenne = pair.second / comptesPolluants[pair.first];
        if (moyenne > maxValeur) {
            maxValeur = moyenne;
            polluantPrincipal = pair.first;
        }
    }
    
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    // Format output string
    string resultat = "Zone Statistics:\n";
    resultat += "Average AQI: " + to_string(moyenneAQI) + "\n";
    resultat += "Pollution Peak: " + to_string(maxAQI) + "\n";
    resultat += "Minimal Index: " + to_string(minAQI) + "\n";
    resultat += "Critical Pollutant: " + polluantPrincipal + "\n";
    resultat += "Execution Time: " + to_string(duree.count()) + " ms";
    
    cout << "Temps d'exécution getZoneStatistic : " << duree.count() << " ms" << endl;
    
    return resultat;
}


double StatisticsService::viewCleanerImpact(const User& user, string cleanerID, TimeRange period){
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    AirCleaner* cleaner = DataService::getCleanerById(cleanerID);
    if (cleaner == nullptr) {
        cout << "ERROR: Cleaner " << cleanerID << " not found" << endl;
        return 0.0;
    }
    double rayonEffet = 5.0;    
    double cleaner_lat = cleaner->getLattitude();     
    double cleaner_lon = cleaner->getLongitude();       
    DateTime cleanerStartTime = cleaner->getWorkingPeriod().getStart();          

    //Identifier les capteurs impactés (dans le rayon d'action du purificateur)
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<string> capteursImpactes;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        double distance = capteur->calculateDistance(cleaner_lat, cleaner_lon);
        if (distance <= rayonEffet) {
            capteursImpactes.push_back(capteur->getSensorID());
        }
    }
    
    //Séparer la période en "Avant" et "Après" activation
    TimeRange periodeAvant(period.getStart(), cleanerStartTime);
    TimeRange periodeApres(cleanerStartTime, period.getEnd());
    
    //Calculer la qualité moyenne pour chaque période
    double qualiteAvant = calculateAreaMean(user, cleaner_lat, cleaner_lon, rayonEffet, periodeAvant);
    double qualiteApres = calculateAreaMean(user, cleaner_lat, cleaner_lon, rayonEffet, periodeApres);
    
    // Calculer l'impact (différence)Sub
    // Impact positif = amélioration (pollution baisse)
    double impactRelatif = qualiteAvant - qualiteApres;
    
    // Enregistrer le temps de fin
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Analyse effectuée en : " << duree.count() << " ms" << endl;
    cout << "Qualité avant: " << qualiteAvant << " | Après: " << qualiteApres << endl;
    
    return impactRelatif;
}


// Estimer la qualité de l'air à une position précise (même sans capteur)
// Utilise l'interpolation spatiale basée sur les capteurs voisins
// Cette fonction est similaire à calculateAirQuality mais sans paramètre User
double StatisticsService::estimateAirQuality(double lat, double lon){
    // Enregistrer le temps de début
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // Récupérer tous les capteurs et mesures (sans filtrage par utilisateur
    vector<Sensor*> tousCapteurs = DataService::getAllSensors();
    vector<Measurement*> toutesMesures = DataService::getAllMeasurements();
    
    // Initialiser les structures pour l'interpolation spatiale (IDW)
    map<string, double> sommesPonderees;  // {attributeID: somme_valeurs_pondérées}
    map<string, double> sommePoids;       // {attributeID: somme_poids}
    
    //Parcourir les capteurs pour l'interpolation
    for (const auto& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        // Utiliser uniquement les capteurs fiables
        if (capteur->getReliability()== true) {
            // Calculer la distance entre le capteur et le point d'intérêt
            double distance = capteur->calculateDistance(lat, lon);
            
            // Calculer le poids (inverse de la distance au carré)
            double poids = (distance < 0.1) ? 100.0 : 1.0 / (distance * distance);
            
            // Chercher les mesures de ce capteur
            for (const auto& mesure : toutesMesures) {
               if (mesure != nullptr && mesure->getSensor()->getSensorID() == capteur->getSensorID()) {
                    string attrID = mesure->getAttribute()->getAttributeID();
                    sommesPonderees[attrID] += (mesure->getValue() * poids);
                    sommePoids[attrID] += poids;
                }
            }
        }
    }
    map<string, double> moyennesEstimees;
    for (const auto& pair : sommesPonderees) {
        string attributeID = pair.first;
        if (sommePoids[attributeID] > 0) {
            moyennesEstimees[attributeID] = pair.second / sommePoids[attributeID];
        }
    }
    
    double indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennesEstimees);

    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution estimateAirQuality : " << duree.count() << " ms" << endl;
    return indiceGlobal;
}


    
double StatisticsService::calculateLocalAQI(const User& user, double lat, double lon, double radius, TimeRange period){
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Récupération du capteur le plus proche (normalement à distance ~0)
    vector<Sensor*> listeCapteurs = DataService::getSensorsInArea(lat, lon, radius);
    
    // Si aucun capteur dans la zone, retourner erreur
    if (listeCapteurs.empty()) {
        cout << "ERROR: No sensor found in this area" << endl;
        return 0.0;
    }
    
    // 2. Récupération des mesures pour ce capteur précis sur la période
    // On prend le capteur le plus proche (le premier de la liste)
    Sensor* capteurLocal = listeCapteurs.front();
    vector<Measurement*> mesures = DataService::getMeasurements(user);
    
    // Filtrer les mesures pour ce capteur spécifique et cette période
    vector<Measurement*> mesuresLocales;
    for (const auto& mesure : mesures) {
        if (mesure != nullptr && capteurLocal != nullptr && mesure->getSensor()->getSensorID() == capteurLocal->getSensorID() && period.contains(mesure->getMeasureDate())) {
            mesuresLocales.push_back(mesure);
        }
    }
    
    // Si pas de mesures pour ce capteur, retourner erreur
    if (mesuresLocales.empty()) {
        cout << "ERROR: No measurements available for this sensor in the given period" << endl;
        return 0.0;
    }
    
    // 3. Calcul des moyennes par polluant pour ce capteur
    map<string, double> sommeAttributs;
    map<string, int> comptesAttributs;
    
    for (const auto& mesure : mesuresLocales) {
        if (mesure != nullptr) {
            string attrID = mesure->getAttribute()->getAttributeID();
            sommeAttributs[attrID] += mesure->getValue();
            comptesAttributs[attrID] += 1;
        }
    }
    
    // Calculer les moyennes simples
    map<string, double> moyennesParAttribut;
    for (const auto& pair : sommeAttributs) {
        string attributeID = pair.first;
        double sommeValue = pair.second;
        
        if (comptesAttributs[attributeID] > 0) {
            moyennesParAttribut[attributeID] = sommeValue / comptesAttributs[attributeID];
        }
    }
    
    // 4. Conversion en indice ATMO final
    double indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennesParAttribut);
    
    // Enregistrer le temps de fin
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution calculateLocalAQI : " << duree.count() << " ms" << endl;
    if (capteurLocal != nullptr) {
        cout << "Local AQI for sensor " << capteurLocal->getSensorID()<< " : " << indiceGlobal << endl;
    }
    
    return indiceGlobal;
}
    


double StatisticsService::convertirVersIndiceATMO(map<string, double> moyennesEstimees) {
    double indiceMax = 0;

    // Pour chaque polluant (O3, NO2, SO2, PM10)
    for (pair<string, double> attr : moyennesEstimees) {
        string attrID = attr.first;
        double valeur = attr.second;
        int indicePolluant = 0;
        
        if (attrID == "O3") {
            if (valeur < 30) {
                indicePolluant = 1;
            } else if (valeur < 55) {
                indicePolluant = 2;
            } else if (valeur < 80) {
                indicePolluant = 3;
            } else if (valeur < 105) {
                indicePolluant = 4;
            } else if (valeur < 130) {
                indicePolluant = 5;
            } else if (valeur < 150) {
                indicePolluant = 6;
            } else if (valeur < 180) {
                indicePolluant = 7;
            } else if (valeur < 210) {
                indicePolluant = 8;
            } else if (valeur < 240) {
                indicePolluant = 9;
            }
            else {
                indicePolluant = 10;
            }
        }
        else if (attrID == "PM10") {
            if (valeur < 7) {
                indicePolluant = 1;
            } else if (valeur < 14) {
                indicePolluant = 2;
            } else if (valeur < 21) {
                indicePolluant = 3;
            } else if (valeur < 28) {
                indicePolluant = 4;
            } else if (valeur < 35) {
                indicePolluant = 5;
            } else if (valeur < 42) {
                indicePolluant = 6;
            } else if (valeur < 50) {
                indicePolluant = 7;
            } else if (valeur < 65) {
                indicePolluant = 8;
            } else if (valeur < 80) {
                indicePolluant = 9;
            }
            else {
                indicePolluant = 10;
            }
        }
        else if (attrID == "SO2") {
            if (valeur < 40) {
                indicePolluant = 1;
            } else if (valeur < 80) {
                indicePolluant = 2;
            } else if (valeur < 120) {
                indicePolluant = 3;
            } else if (valeur < 160) {
                indicePolluant = 4;
            } else if (valeur < 200) {
                indicePolluant = 5;
            } else if (valeur < 250) {
                indicePolluant = 6;
            } else if (valeur < 300) {
                indicePolluant = 7;
            } else if (valeur < 400) {
                indicePolluant = 8;
            } else if (valeur < 500) {
                indicePolluant = 9;
            }
            else {
                indicePolluant = 10;
            }
        }
        else if (attrID == "NO2") {
            if (valeur < 30) {
                indicePolluant = 1;
            } else if (valeur < 55) {
                indicePolluant = 2;
            } else if (valeur < 85) {
                indicePolluant = 3;
            } else if (valeur < 110) {
                indicePolluant = 4;
            } else if (valeur < 135) {
                indicePolluant = 5;
            } else if (valeur < 165) {
                indicePolluant = 6;
            } else if (valeur < 200) {
                indicePolluant = 7;
            } else if (valeur < 275) {
                indicePolluant = 8;
            } else if (valeur < 400) {
                indicePolluant = 9;
            }
            else {
                indicePolluant = 10;
            }
        }
        else {
            continue; // Ignorer les polluants non reconnus
        }

        // On garde le pire indice trouvé
        if (indicePolluant > indiceMax) {
            indiceMax = indicePolluant;
        }
    }

    return indiceMax;
}


//-------------------------------------------- Constructeurs - destructeur
StatisticsService::StatisticsService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Xxx>" << endl;
#endif
} //----- Fin de Xxx


StatisticsService::~StatisticsService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Xxx>" << endl;
#endif
} //----- Fin de ~Xxx


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

