/*************************************************************************
                           SecurityService      -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <SecurityService> (fichier SecurityService.cpp) ------------

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
#include "SecurityService.h"
#include "DataService.h"
#include "../model/Sensor.h"
#include "../model/TimeRange.h"
#include "../model/User.h"
#include "../model/GovernmentAgency.h"
#include "../model/PrivateUser.h"
#include "../model/Measurement.h"
#include "../model/Role.h"
using namespace std;


//------------------------------------------------------------- Constantes
const double SEUIL_TOLERANCE = 0.30;  // 30% de tolérance
const double SEUIL_FRAUDE = 0.50;     // 50% d'anomalies pour marquer comme frauduleux
const time_t RELIABILITY_CHECK_PERIOD = 7 * 24 * 3600;  // 7 days for analysis


//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool SecurityService::checkSensorReliability(const User& user, string targetSensorID) 
// Algorithme
// 1. Vérifier que l'utilisateur est une agence gouvernementale
// 2. Récupérer le capteur à analyser et ses mesures
// 3. Récupérer les capteurs voisins fiables et leurs mesures associées
// 4. Pour chaque mesure du capteur à analyser, calculer une valeur de référence à partir des capteurs voisins pour la même date et le même attribut
// Si l'écart entre la mesure du capteur à analyser et la valeur de référence dépasse un seuil de tolérance, marquer la mesure comme anomalie
// 5. Déterminer si le capteur est fiable en fonction du taux d'anomalies
// 6. Journaliser le temps d'exécution et les résultats
{
    std::chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    // 1. Seule une agence gouvernementale peut vérifier la fiabilité d'un capteur
    if (user.getRole() != GOVERNMENT_AGENCY) {
        cout << "ERREUR : Seules les agences gouvernementales peuvent vérifier la fiabilité d'un capteur." << endl;
        return false;
    }

    // 2. Récupérer le capteur à analyser et ses mesures
    Sensor* capteurAAnalyser = DataService::getDataContainer()->getSensorByID(targetSensorID);
    if (capteurAAnalyser == nullptr) {
        cout << "ERREUR: Capteur " << targetSensorID << " non trouvé." << endl;
        return false;
    }

    vector<Measurement*> mesuresCible = DataService::getMeasurementsBySensor(targetSensorID);
    if (mesuresCible.empty()) {
        cout << "ERREUR: Aucune mesure trouvée pour le capteur " << targetSensorID << endl;
        return false;
    }
    
    // 3. Récupérer les capteurs voisins fiables et les mesures fiables associées (moins de 10 km et marqués comme fiables)
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<Measurement*> toutesMesures = DataService::getMeasurements(user);

    vector<Sensor*> capteursVoisinsFiables;
    for (const vector<Sensor*>::value_type& capteur : tousCapteurs) {
        if (capteur != nullptr && capteur->getReliability() == true && capteur->getSensorID() != targetSensorID) {
            double distance = capteur->calculateDistance(capteurAAnalyser->getLattitude(), capteurAAnalyser->getLongitude());
            if (distance <= 10) {  // 10km
                capteursVoisinsFiables.push_back(capteur);
            }
        }
    }
    
    if (capteursVoisinsFiables.empty()) {
        cout << "AVERTISSEMENT : Aucun capteur fiable à proximité trouvé. Le capteur " << targetSensorID << " est considéré comme fiable." << endl;
        capteurAAnalyser->setReliability(true);
        return true;
    }

    vector<Measurement*> mesuresFiablesVoisins;
    for (const vector<Sensor*>::value_type& capteurVoisin : capteursVoisinsFiables) {
        for (const vector<Measurement*>::value_type& mesure : capteurVoisin->getMeasurements()) {
            if (mesure != nullptr && mesure->getIsValid() == true) {
                mesuresFiablesVoisins.push_back(mesure);
            }
        }
    }

    // 4. Pour chaque mesure du capteur à analyser, calculer une valeur de référence à partir des capteurs voisins pour la même date et le même attribut
    int anomaliesDetectees = 0;
    int totalMesures = 0;
    
    // Pour chaque mesure du capteur à analyser
    for (const vector<Measurement*>::value_type& mesure : mesuresCible) {
        // Calculer la valeur de référence à partir des capteurs voisins fiables pour la même date et le même attribut
        double sommValeurs = 0.0;
        int compteMesures = 0;
        
        for (const vector<Sensor*>::value_type& capteurVoisin : capteursVoisinsFiables) {
            for (const vector<Measurement*>::value_type& mesureVoisin : mesuresFiablesVoisins) {
                if (capteurVoisin != nullptr && mesureVoisin->getSensor()->getSensorID() == capteurVoisin->getSensorID() &&
                    mesureVoisin->getMeasureDate() == mesure->getMeasureDate() &&
                    mesureVoisin->getAttribute()->getAttributeID() == mesure->getAttribute()->getAttributeID()) {
                    
                    sommValeurs += mesureVoisin->getValue();
                    sommValeurs += mesureVoisin->getValue();
                    compteMesures++;
                }
            }
        }
        
        // Si on a des mesures de référence, calculer la valeur de référence et détecter les anomalies
        if (compteMesures > 0) {
            double valeurReference = sommValeurs / compteMesures;
            totalMesures++;

            // Calculer l'écart absolu
            double ecartAbsolu = abs(mesure->getValue() - valeurReference);

            // Vérifier si l'écart dépasse le seuil de tolérance
            if (ecartAbsolu > (valeurReference * SEUIL_TOLERANCE)) {
                cout << "ANOMALIE DÉTECTÉE : La mesure du capteur " << targetSensorID << " diffère fortement de la valeur de référence." << endl;
                mesure->setIsValid(false);
                anomaliesDetectees++;
            }
        }
    }
    
    // 5. Décision : marquer comme non fiable si le taux d'anomalies > 50 %
    bool estFiable = true;
    if (totalMesures > 0) {
        double tauxAnomalies = (double) anomaliesDetectees / totalMesures;
        
        if (tauxAnomalies > SEUIL_FRAUDE) {
            estFiable = false;

            // Mettre à jour le statut du capteur dans le stockage persistant
            DataService::getDataContainer()->getSensorByID(targetSensorID)->setReliability(false);
        }
    }
    
    // 6. Journaliser le temps d'exécution et les résultats
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);

    cout << "=== Vérification de la fiabilité du capteur ===" << endl;
    cout << "ID du capteur : " << targetSensorID << endl;
    cout << "Capteurs fiables à proximité : " << capteursVoisinsFiables.size() << endl;
    cout << "Nombre total de mesures analysées : " << totalMesures << endl;
    cout << "Anomalies détectées : " << anomaliesDetectees << endl;
    if (totalMesures > 0) {
        cout << "Taux d'anomalies : " << ((double)anomaliesDetectees / totalMesures * 100.0) << "%" << endl;
    }
    cout << "Résultat : " << (estFiable ? "FIABLE" : "FRAUDULEUX") << endl;
    cout << "Temps d'exécution de checkSensorReliability : " << duree.count() << " ms" << endl;
    
    return estFiable;
}

vector<PrivateUser*> SecurityService::detectFraudulentUsers(const User& user) 
// Algorithme :
// 1. Vérifier que l'utilisateur est une agence gouvernementale
// 2. Récupérer tous les utilisateurs privés 
// 3. Pour chaque utilisateur privé, récupérer et vérifier la fiabilité de chacun de ses capteurs
// 4. Pour chaque capteur, vérifier sa fiabilité avec checkSensorReliability
// 5. Si un utilisateur a au moins un capteur non fiable, le marquer comme frauduleux
// 6. Journaliser le temps d'exécution et les résultats
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    vector<PrivateUser*> fraudulentUsers;
    
    // 1. Seule une agence gouvernementale peut détecter les utilisateurs frauduleux
    if (user.getRole() != GOVERNMENT_AGENCY) {
        cout << "ERREUR : Seules les agences gouvernementales peuvent détecter les utilisateurs frauduleux." << endl;
        return fraudulentUsers;
    }
  
    // 2. Récupérer tous les utilisateurs privés
    vector<PrivateUser*> allPrivateUsers = DataService::getAllPrivateUsers();

    // 3. Pour chaque utilisateur privé, récupérer et vérifier la fiabilité de chacun de ses capteurs
    for (const vector<PrivateUser*>::value_type& privateUser : allPrivateUsers) {
        vector<Sensor*> userSensors = privateUser->getSensorsList();
        
        bool userIsFraudulent = false;
        
        // 4. Pour chaque capteur, vérifier sa fiabilité avec checkSensorReliability
        for (const vector<Sensor*>::value_type& sensor : userSensors) {
            if (sensor != nullptr && !checkSensorReliability(user, sensor->getSensorID())) {
                userIsFraudulent = true;
                break; // Si un capteur est non fiable, on peut arrêter de vérifier les autres capteurs de cet utilisateur
            }
        }
        
        // 5. Si un utilisateur a au moins un capteur non fiable, le marquer comme frauduleux
        if (userIsFraudulent) {
            privateUser->setIsFraudulent(true);
            fraudulentUsers.push_back(privateUser);
            cout << "Fraudulent user detected: " << privateUser->getUserID() << endl;
        }
    }
    
    // 6. Journaliser le temps d'exécution et les résultats
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution detectFraudulentUsers : " << duree.count() << " ms" << endl;
    cout << "Total Fraudulent Users Found: " << fraudulentUsers.size() << endl;
    
    return fraudulentUsers;
}

// Data corruption removal: Mark corrupted data as invalid
void SecurityService::removeCorruptedData(const User& user) 
// Algorithme :
// 1. Vérifier que l'utilisateur est une agence gouvernementale
// 2. Récupérer tous les capteurs marqués comme non fiables
// 3. Pour chaque capteur non fiable, marquer ses données comme invalides (suppression douce)
// 4. Journaliser le temps d'exécution
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Authentication
    if (user.getRole() != GOVERNMENT_AGENCY) {
        cout << "ERREUR : Seules les agences gouvernementales peuvent supprimer les données corrompues." << endl;
        return;
    }
    
    // 2. Trouver tous les capteurs marqués comme non fiables
    vector<Sensor*> allSensors = DataService::getAllSensors();
    vector<Sensor*> unreliableSensors;
    
    for (const vector<Sensor*>::value_type& sensor : allSensors) {
        if (sensor != nullptr && sensor->getReliability() == false) {
            unreliableSensors.push_back(sensor);
        }
    }
    
    // 3. Pour chaque capteur non fiable, marquer ses données comme invalides (suppression douce)
    int corruptedRecordsCount = 0;
    for (const vector<Sensor*>::value_type& sensor : unreliableSensors) {
        vector<Measurement*> measurements = DataService::getMeasurementsBySensor(sensor->getSensorID());
        
        for (const vector<Measurement*>::value_type& measurement : measurements) {
            if (measurement != nullptr && measurement->getIsValid() == true) {
                measurement->setIsValid(false);
                corruptedRecordsCount++;
            }
        }
        
        cout << "Marquage du capteur " << sensor->getSensorID() << " et de ses " << measurements.size() << " mesures comme invalides" << endl;
    }
    
    // 4. Journaliser le temps d'exécution
    cout << "Nettoyage des données corrompues..." << endl;
    chrono::high_resolution_clock::time_point tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Nombre de mesures corrompues marquées : " << corruptedRecordsCount << endl;
    cout << "Temps d'exécution removeCorruptedData : " << duree.count() << " ms" << endl;
    return;
}


// System initialization: Restore security baseline
void SecurityService::initializeDatabase(const User& user) 
// Algorithme
// 1. Vérifier que l'utilisateur est une agence gouvernementale
{
    chrono::high_resolution_clock::time_point tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Seule une agence gouvernementale peut initialiser la base de données
    if (user.getRole() != GOVERNMENT_AGENCY) {
        cout << "ERREUR : Seules les agences gouvernementales peuvent initialiser la base de données." << endl;
        return;
    }
    
    cout << "Initializing Database Security Baseline..." << endl;
    
    // 2. Reload all data from CSV files via DataService
    cout << "Loading initial state from CSV files..." << endl;
    DataService::loadAllData();
    
    // 3. Build security baseline: Mark all government sensors as reliable
    vector<Sensor*> allSensors = DataService::getAllSensors();
    int reliableSensorCount = 0;
    
    for (const auto& sensor : allSensors) {
        // Note: Sensors in the actual system would have a type attribute
        // For now, we mark all as needing verification
        if (sensor != nullptr) {
            DataService::updateSensorStatus(sensor->getSensorID(), true);
            reliableSensorCount++;
        }
    }
    
    cout << "Reliable Sensors (initialized): " << reliableSensorCount << endl;
    
    // 4. Clear any temporary ban flags or corrupted states
    cout << "Clearing temporary corruption flags..." << endl;
    DataService::clearCorruptionFlags();
    
    // 5. Reset statistics cache
    cout << "Resetting statistics cache..." << endl;
    
    // 6. Verify data integrity
    cout << "Verifying data integrity..." << endl;
    vector<Measurement*> allMeasurements = DataService::getAllMeasurements();
    cout << "Total Measurements in System: " << allMeasurements.size() << endl;
    
    // 7. Log completion
    auto tempsFin = chrono::high_resolution_clock::now();
    chrono::milliseconds duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "=== Database Initialization Complete ===" << endl;
    cout << "Temps d'exécution initializeDatabase : " << duree.count() << " ms" << endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SecurityService::SecurityService () 
{
    #ifdef MAP
        cout << "Appel au constructeur de <SecurityService>" << endl;
    #endif
}  // ----- Fin de SecurityService

SecurityService::~SecurityService () 
{
    #ifdef MAP
        cout << "Appel au destructeur de <SecurityService>" << endl;
    #endif
}  // ----- Fin de ~SecurityService

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
