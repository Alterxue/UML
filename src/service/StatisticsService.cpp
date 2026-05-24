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
#include <limits>
#include <sstream>
#include "../model/Sensor.h"
#include "../model/TimeRange.h"
#include "DataService.h"
#include "StatisticsService.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string StatisticsService::analyzeSensorData(const string& sensorID, const TimeRange& period)
// Algorithme :
// 1. Récupérer le capteur et ses mesures.
// 2. Conserver uniquement les mesures valides dans la période demandée.
// 3. Calculer les moyennes par attribut.
// 4. Retourner un résumé textuel de l'analyse avec le temps d'exécution.
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();

    // 1. Récupérer le capteur demandé.
    Sensor* sensor = DataService::getDataContainer()->getSensorByID(sensorID);
    if (sensor == nullptr) {
        return "ERREUR: capteur introuvable";
    }

    // 2. Récupérer toutes les mesures associées à ce capteur.
    vector<Measurement*> allMeasurements = DataService::getMeasurementsBySensor(sensorID);

    int totalMeasurements = 0;
    int validMeasurements = 0;
    map<string, double> sumsByAttribute;
    map<string, int> countsByAttribute;

    // 3. Filtrer les mesures par période et garder uniquement les mesures valides.
    for (const Measurement* measurement : allMeasurements) {
        if (measurement == nullptr) {
            continue;
        }
        if (!period.contains(measurement->getMeasureDate())) {
            continue;
        }

        totalMeasurements++;

        if (measurement->getIsValid() == false) {
            continue;
        }

        validMeasurements++;

        if (measurement->getAttribute() != nullptr) {
            string attributeID = measurement->getAttribute()->getAttributeID();
            sumsByAttribute[attributeID] += measurement->getValue();
            countsByAttribute[attributeID] += 1;
        }
    }

    // 4. Calculer les moyennes par attribut.
    ostringstream report;
    report << "Analyse du capteur " << sensorID << '\n';
    report << "Latitude: " << sensor->getLattitude() << '\n';
    report << "Longitude: " << sensor->getLongitude() << '\n';
    report << "Mesures dans la periode: " << totalMeasurements << '\n';
    report << "Mesures valides: " << validMeasurements << '\n';

    for (const map<string, double>::value_type& pair : sumsByAttribute) {
        const string& attributeID = pair.first;
        double average = pair.second / countsByAttribute[attributeID];
        report << "- Moyenne " << attributeID << " = " << average << '\n';
    }

    // 5. Mesurer le temps d'exécution et l'ajouter au rapport.
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);

    report << "Temps d'execution: " << duree.count() << " ms";

    return report.str();
} //----- Fin de analyzeSensorData

double StatisticsService::calculateAreaMean(double lat, double lon, double radius, const TimeRange& period)
// Algorithme :
// 1. Sélectionner les capteurs fiables situés dans le rayon demandé.
// 2. Récupérer les mesures de ces capteurs dans la période fournie.
// 3. Calculer la moyenne de chaque polluant.
// 4. Convertir ces moyennes en indice ATMO final.
{
    //le temps de début
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    // Récupération de toutes les données via DataService
    vector<Sensor*> tousCapteurs = DataService::getAllSensors();
    vector<Measurement*> toutesMesures = DataService::getAllMeasurements();
    
    // Filtrage spatial et fiabilité - récupérer les capteurs dans la zone
    vector<Sensor*> capteursZone;
    for (const vector<Sensor*>::value_type& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        double distance = capteur->calculateDistance(lat, lon);
        // Vérifier si le capteur est dans le rayon ET est fiable
        if (distance <= radius && capteur->getReliability() == true) {
            capteursZone.push_back(capteur);
            User* owner = capteur->getOwner(); 
            PrivateUser* privateOwner = dynamic_cast<PrivateUser*>(owner);
            if (privateOwner != nullptr) {
                privateOwner->incrementPoints(1);
            }
        }
    }
    
    //Agrégation des mesures correspondantes
    map<string, double> sommesAttributs;    
    map<string, int> comptesAttributs;      
    
    for (const vector<Sensor*>::value_type& capteur : capteursZone) {
        for (const vector<Measurement*>::value_type& mesure : toutesMesures) {
            if (capteur != nullptr && 
                mesure != nullptr && 
                mesure->getSensor() != nullptr &&
                mesure->getSensor()->getSensorID() == capteur->getSensorID() && 
                mesure->getIsValid() == true &&
                period.contains(mesure->getMeasureDate())) {

                string attrID = mesure->getAttribute()->getAttributeID();
                sommesAttributs[attrID] += mesure->getValue();
                comptesAttributs[attrID] += 1;
            }
        }
    }
    
    //Calcul des moyennes par attribut
    map<string, double> moyennes;
    
    for (const map<string, double>::value_type& pair : sommesAttributs) {
        const string& attributeID = pair.first;
        double sommeAttribut = pair.second;
        
        if (comptesAttributs[attributeID] > 0) {
            moyennes[attributeID] = sommeAttribut / comptesAttributs[attributeID];
        }
    }
    
    double indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennes);

    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution calculateAreaMean : " << duree.count() << " ms" << endl;
    
    // Retourner l'indice global
    return indiceGlobal;
} //----- Fin de calculateAreaMean

double StatisticsService::calculateAreaMean(double lat, double lon, double radius, const DateTime& moment) 
// Algorithme :
// 1. Surcharge de calculateAreaMean pour calculer l'indice d'une zone à un instant précis
{
    TimeRange instant(moment, moment);
    return calculateAreaMean(lat, lon, radius, instant);
} //----- Fin de calculateAreaMean (surcharge)

vector<Sensor> StatisticsService::compareSensorsBySimilarity(string targetSensor, TimeRange period)
// Algorithme :
// 1. Extraire les mesures du capteur cible sur la période.
// 2. Comparer chaque autre capteur fiable sur les mêmes horodatages et attributs.
// 3. Calculer un écart moyen par capteur.
// 4. Trier les capteurs par écart croissant pour obtenir les plus similaires.
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    //Récupération de toutes les données
    vector<Sensor*> tousCapteurs = DataService::getAllSensors();
    vector<Measurement*> toutesMesures = DataService::getAllMeasurements();
    
    // Extraction des données du capteur cible pour la période
    vector<Measurement*> donneesCible;
    for (const vector<Measurement*>::value_type& mesure : toutesMesures) {
        if (mesure != nullptr && 
            mesure->getSensor() != nullptr &&
            mesure->getSensor()->getSensorID() == targetSensor && 
            period.contains(mesure->getMeasureDate())) {

            donneesCible.push_back(mesure);
        }
    }
    
    //Calcul des scores de similarité pour chaque capteur
    map<string, double> scoresSimilarite;  // {sensorID: écart moyen}
    for (const vector<Sensor*>::value_type& capteur : tousCapteurs) {
        if (capteur == nullptr) {
            continue;
        }
        // Ignorer le capteur cible et les capteurs non fiables
        if (capteur->getSensorID() == targetSensor || capteur->getReliability() == false) {
            continue;
        }
        //Extraction des données du capteur actuel pour la période
        vector<Measurement*> donneesAComparer;
        for (const vector<Measurement*>::value_type& mesure : toutesMesures) {
            if (mesure != nullptr && 
                mesure->getSensor() != nullptr &&
                mesure->getSensor()->getSensorID() == capteur->getSensorID() && 
                period.contains(mesure->getMeasureDate())) {
                donneesAComparer.push_back(mesure);
            }
        }
        
        // Calcul de l'écart moyen entre le capteur cible et le capteur actuel
        double differenceTotale = 0.0;
        int pointsCommuns = 0;
        
        for (const vector<Measurement*>::value_type& mesureCible : donneesCible) {
            // Chercher la mesure correspondante (même timestamp et attributeID)
            for (const vector<Measurement*>::value_type& mesureAComparer : donneesAComparer) {
                if (mesureAComparer != nullptr && mesureCible != nullptr &&
                    mesureAComparer->getMeasureDate() == mesureCible->getMeasureDate() && 
                    mesureAComparer->getAttribute() != nullptr &&
                    mesureCible->getAttribute() != nullptr &&
                    mesureAComparer->getAttribute()->getAttributeID() == mesureCible->getAttribute()->getAttributeID()) {
                    
                    // Calculer la différence absolue entre les deux valeurs
                    double difference = abs(mesureCible->getValue() - mesureAComparer->getValue());
                    differenceTotale += difference;
                    pointsCommuns += 1;
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
    
    for (const vector<pair<string, double>>::value_type& pair : scoresVecteur) {
        // Trouver le capteur correspondant dans la liste originale
        for (const vector<Sensor*>::value_type& capteur : tousCapteurs) {
            if (capteur != nullptr && capteur->getSensorID() == pair.first) {
                listeTriee.push_back(*capteur);
                break;
            }
        }
    }
    // Enregistrer le temps de fin et calculer la durée
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution compareSensorsBySimilarity : " << duree.count() << " ms" << endl;
    
    return listeTriee;
} //----- Fin de compareSensorsBySimilarity

map<string, vector<Sensor>> StatisticsService::compareNeighborhoodSensors(const User& user, double radius, TimeRange period)
// Algorithme :
// 1. Récupérer les capteurs dans la zone via DataService::getSensorsInArea.
// 2. Pour chaque capteur fiable trouvé, appeler compareSensorsBySimilarity(user, sensorID, period).
// 3. Retourner une map associant chaque capteur cible à sa liste de capteurs similaires.
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();

    if (user.getRole() != Role::PRIVATE_USER) { 
        cout << "ERREUR: Seuls les utilisateurs privés peuvent comparer leurs capteurs de leur voisinage." << endl;
        return {};
    }

    std::map<std::string, std::vector<Sensor>> result;
    // Calculer le centre à partir des capteurs de l'utilisateur (même logique que calculateUserZoneAQI)
    vector<Sensor*> userSensors = DataService::getSensors(user);
    if (userSensors.empty()) {
        return result;
    }
    double sumLat = 0.0;
    double sumLon = 0.0;
    int count = 0;
    for (Sensor* s : userSensors) {
        if (s != nullptr) {
            sumLat += s->getLattitude();
            sumLon += s->getLongitude();
            ++count;
        }
    }
    if (count == 0) return result;
    double centerLat = sumLat / count;
    double centerLon = sumLon / count;

    vector<Sensor*> liste = DataService::getSensorsInArea(centerLat, centerLon, radius);
    if (liste.empty()) {
        return result;
    }

    for (Sensor* s : liste) {
        if (s == nullptr) continue;
        if (s->getReliability() == false) continue; // ignorer les capteurs non fiables

        std::string targetID = s->getSensorID();
        std::vector<Sensor> similaires = compareSensorsBySimilarity(targetID, period);
        result[targetID] = similaires;
    }

    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    cout << "Temps d'exécution compareNeighborhoodSensors : " << duree.count() << " ms" << endl;

    return result;
} //----- Fin de compareNeighborhoodSensors

double StatisticsService::calculateAirQuality(double lat, double lon, const DateTime& time)
// Algorithme :
// 1. Récupérer tous les capteurs et toutes les mesures du système.
// 2. Garder uniquement les capteurs fiables et les mesures à l'instant demandé.
// 3. Pondérer chaque mesure par la distance du capteur au point étudié.
// 4. Calculer une moyenne par polluant puis la convertir en indice ATMO global.
{
    // commencer a compter le temps
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    // obtenir les listes de capteurs et mesures
    vector<Sensor*> tousCapteurs = DataService::getAllSensors();
    vector<Measurement*> toutesMesures = DataService::getAllMeasurements();
    
    map<string, double> sommesPonderees;  
    map<string, double> sommePoids;      
    for (const vector<Sensor*>::value_type& capteur : tousCapteurs){
        if (capteur == nullptr) {
            continue;
        }
        if (capteur->getReliability() == true){
            User* owner = capteur->getOwner(); 
            PrivateUser* privateOwner = dynamic_cast<PrivateUser*>(owner);
            if (privateOwner != nullptr) {
                privateOwner->incrementPoints(1);
            }
            double distance = capteur->calculateDistance(lat,lon);
            double poids = (distance < 0.1) ? 100 : (1.0 / (distance * distance));
            for(const vector<Measurement*>::value_type& mesure : toutesMesures){
                if(mesure != nullptr && 
                    mesure->getSensor() != nullptr &&
                    mesure->getSensor()->getSensorID() == capteur->getSensorID() && 
                    mesure->getIsValid() == true &&
                    mesure->getMeasureDate() == time) {

                    string attrID = mesure->getAttribute()->getAttributeID();
                    sommesPonderees[attrID] += (mesure->getValue() * poids);
                    sommePoids[attrID] += poids;
                }
            }
        }
    }
    
    map<string, double> moyennesEstimees;
    for (const map<string, double>::value_type& pair : sommesPonderees) {
        const string& attributeID = pair.first;
        double sommePonderee = pair.second;
        
        if (sommePoids[attributeID] > 0) {
            moyennesEstimees[attributeID] = sommePonderee / sommePoids[attributeID];
        }
    }

    double indiceGlobal = StatisticsService::convertirVersIndiceATMO(moyennesEstimees);
    
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution calculateAirQuality : " << duree.count() << " ms" << endl;
    
    return indiceGlobal;
} //----- Fin de calculateAirQuality

double StatisticsService::convertirVersIndiceATMO(map<string, double> moyennesEstimees) 
// Algorithme :
// 1. Convertir chaque polluant reconnu en indice ATMO élémentaire via ses seuils.
// 2. Conserver le score le plus défavorable.
// 3. Retourner l'indice global correspondant au pire polluant.
{
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
} //----- Fin de convertirVersIndiceATMO

double StatisticsService::calculateUserZoneAQI(const User& user, double radius, const TimeRange& period)
// Algorithme :
// 1. Récupérer la liste des capteurs appartenant à l'utilisateur.
// 2. Calculer un centre approximatif (moyenne des lat/lon des capteurs).
// 3. Appeler `calculateAreaMean` avec ce centre et le rayon fourni.
{
    // Récupération des capteurs de l'utilisateur
    vector<Sensor*> userSensors = DataService::getSensors(user);
    if (userSensors.empty()) {
        return 0.0;
    }

    double sumLat = 0.0;
    double sumLon = 0.0;
    int count = 0;
    for (Sensor* s : userSensors) {
        if (s != nullptr) {
            sumLat += s->getLattitude();
            sumLon += s->getLongitude();
            ++count;
        }
    }
    if (count == 0) return 0.0;

    double centerLat = sumLat / count;
    double centerLon = sumLon / count;

    return calculateAreaMean(centerLat, centerLon, radius, period);
} //----- Fin de calculateUserZoneAQI

double StatisticsService::viewCleanerImpact(const User& user, std::string cleanerID, TimeRange period)
// Algorithme :
// 1. Localiser le purificateur et définir un rayon d'effet par défaut.
// 2. Séparer la période en avant et après activation.
// 3. Calculer la qualité moyenne de l'air sur chaque sous-période.
// 4. Retourner la différence d'impact entre avant et après.
{

    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
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
    double qualiteAvant = calculateAreaMean(cleaner_lat, cleaner_lon, rayonEffet, periodeAvant);
    double qualiteApres = calculateAreaMean(cleaner_lat, cleaner_lon, rayonEffet, periodeApres);
    
    // Calculer l'impact (différence)Sub
    // Impact positif = amélioration (pollution baisse)
    double impactRelatif = qualiteAvant - qualiteApres;
    
    // Enregistrer le temps de fin
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Analyse effectuée en : " << duree.count() << " ms" << endl;
    cout << "Qualité avant: " << qualiteAvant << " | Après: " << qualiteApres << endl;
    
    return impactRelatif;
} //----- Fin de viewCleanerImpact

double StatisticsService::analyzeCleanerRadius(const User& user, string cleanerID)
// Algorithme :
// 1. Récupérer le purificateur et sa période de fonctionnement.
// 2. Comparer la qualité de l'air avant et pendant l'activité pour des rayons croissants.
// 3. Conserver le plus grand rayon dont l'amélioration reste supérieure au seuil choisi.
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    if (user.getRole() != Role::PROVIDER) {
        cout << "ERREUR: Seuls les fournisseurs peuvent analyser l'impact de leurs purificateurs." << endl;
        return 0.0;
    }
    
    AirCleaner* cleaner = DataService::getCleanerById(cleanerID);
    if (cleaner == nullptr) {
        cout << "ERREUR : Purificateur " << cleanerID << " non trouvé" << endl;
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
        double aqiAvant = calculateAreaMean(cleaner->getLattitude(), cleaner->getLongitude(), rayon, periodeAvant);
        double aqiPendant = calculateAreaMean(cleaner->getLattitude(), cleaner->getLongitude(), rayon, periodePendant);
        
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
    
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution analyzeCleanerRadius : " << duree.count() << " ms" << endl;
    cout << "Rayon d'impact : " << rayonImpact << " km | Meilleure amélioration : " << meilleureAmelioration << "%" << endl;
    
    //renvoyer le radius utile
    return rayonImpact;
} //----- Fin de analyzeCleanerRadius

string StatisticsService::getZoneStatistic(double lat, double lon, double radius, TimeRange period)
// Algorithme :
// 1. Récupérer les capteurs de la zone et les mesures de la période.
// 2. Calculer une moyenne AQI globale et identifier les extrêmes.
// 3. Déterminer le polluant dominant par moyenne.
// 4. Renvoyer un résumé textuel complet de la zone.
{
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // Get all sensors in the area
    vector<Sensor*> listeCapteurs = DataService::getSensorsInArea(lat, lon, radius);
    vector<Measurement*> mesuresZone;

    // Filter measurements by sensor and time period
    for (auto* capteur : listeCapteurs) {
        if (capteur == nullptr) continue;

        vector<Measurement*> mesuresDuCapteur = DataService::getMeasurementsBySensor(capteur->getSensorID());
        
        for (auto* mesure : mesuresDuCapteur) {
            if (mesure != nullptr && 
                mesure->getIsValid() == true && 
                period.contains(mesure->getMeasureDate())) {
                
                mesuresZone.push_back(mesure);
            }
        }
    }
    
    // If no data available, return error message
    if (mesuresZone.empty()) {
        return "ERROR: No data available for this area and period";
    }
    
    // 1. Calculate global average AQI (reuse calculateAreaMean)
    double moyenneAQI = calculateAreaMean(lat, lon, radius, period);
    
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
} //----- Fin de getZoneStatistic

//-------------------------------------------- Constructeurs - destructeur
StatisticsService::StatisticsService ( )
{
    #ifdef MAP
        cout << "Appel au constructeur de <Xxx>" << endl;
    #endif
} //----- Fin de StatisticsService


StatisticsService::~StatisticsService ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <Xxx>" << endl;
    #endif
} //----- Fin de ~StatisticsService


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

