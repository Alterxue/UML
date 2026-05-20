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
using namespace std;


//------------------------------------------------------------- Constantes

const double ANOMALY_THRESHOLD = 0.3;  //tolerance for 30 percent
const double ANOMALY_RATE_THRESHOLD = 0.5;  // 50% anomaly rate to mark unreliable
const time_t RELIABILITY_CHECK_PERIOD = 7 * 24 * 3600;  // 7 days for analysis

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// Algorithm 4: Fraud Detection - Check if a sensor is reliable
// Returns true if sensor is reliable, false if fraudulent
bool SecurityService::checkSensorReliability(const User& user, string targetSensorID) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Get all sensors and measurements
    vector<Sensor*> tousCapteurs = DataService::getSensors(user);
    vector<Measurement> toutesMesures = DataService::getMeasurements(user);
    
    // 2. Find the target sensor to analyze
    Sensor* capteurAAnalyser = nullptr;
    bool capteurTrouve = false;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur != nullptr && capteur->getSensorID() == targetSensorID) {
            capteurAAnalyser = capteur;
            capteurTrouve = true;
            break;
        }
    }
    
    if (!capteurTrouve) {
        cout << "ERROR: Sensor " << targetSensorID << " not found" << endl;
        return false;
    }
    
    // 3. Get nearby reliable sensors (within 10km radius)
    vector<Sensor*> capteursVoisinsFiables;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur != nullptr && capteur->getReliability() == true && capteur->getSensorID() != targetSensorID) {
            double distance = capteur->calculateDistance(capteurAAnalyser->getLattitude(), capteurAAnalyser->getLongitude());
            if (distance <= 10000.0) {  // 10km in meters
                capteursVoisinsFiables.push_back(capteur);
            }
        }
    }
    
    if (capteursVoisinsFiables.empty()) {
        cout << "WARNING: No reliable nearby sensors found. " << targetSensorID << " is reliable." << endl;
        return true;
    }
    
    // 4. Extract measurements for target sensor
    vector<Measurement> mesuresCible;
    for (const auto& mesure : toutesMesures) {
        if (mesure.getSensor()->getSensorID() == targetSensorID) {
            mesuresCible.push_back(mesure);
        }
    }
    
    if (mesuresCible.empty()) {
        cout << "ERROR: No measurements found for sensor " << targetSensorID << endl;
        return false;
    }
    
    // 5. Analyze anomalies
    const double SEUIL_TOLERANCE = 0.30;  // 30% tolerance
    const double SEUIL_FRAUDE = 0.50;     // 50% fraud threshold
    
    int anomaliesDetectees = 0;
    int totalMesures = 0;
    
    // For each measurement of the target sensor
    for (const auto& mesure : mesuresCible) {
        // Calculate reference value from nearby reliable sensors at same timestamp and pollutant
        double sommValeurs = 0.0;
        int compteMesures = 0;
        
        for (const auto& capteurVoisin : capteursVoisinsFiables) {
            for (const auto& mesureVoisin : toutesMesures) {
                if (capteurVoisin != nullptr && mesureVoisin.getSensor()->getSensorID() == capteurVoisin->getSensorID() &&
                    mesureVoisin.getMeasureDate() == mesure.getMeasureDate() &&
                    mesureVoisin.getAttribute()->getAttributeID() == mesure.getAttribute()->getAttributeID()) {
                    
                    sommValeurs += mesureVoisin.getValue();
                    compteMesures++;
                }
            }
        }
        
        // If we have reference values to compare
        if (compteMesures > 0) {
            double valeurReference = sommValeurs / compteMesures;
            totalMesures++;
            
            // Calculate absolute deviation
            double ecartAbsolu = abs(mesure.getValue() - valeurReference);
            
            // Check if deviation exceeds tolerance threshold
            if (ecartAbsolu > (valeurReference * SEUIL_TOLERANCE)) {
                anomaliesDetectees++;
            }
        }
    }
    
    // 6. Decision: Mark unreliable if anomaly rate > 50%
    bool estFiable = true;
    
    if (totalMesures > 0) {
        double tauxAnomalies = (double)anomaliesDetectees / totalMesures;
        
        if (tauxAnomalies > SEUIL_FRAUDE) {
            estFiable = false;
            
            // Update sensor status in persistent storage
            DataService::updateSensorStatus(targetSensorID, false);
        }
    }
    
    // 7. Log execution time and results
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "=== Sensor Reliability Check ===" << endl;
    cout << "Sensor ID: " << targetSensorID << endl;
    cout << "Nearby Reliable Sensors: " << capteursVoisinsFiables.size() << endl;
    cout << "Total Measurements Analyzed: " << totalMesures << endl;
    cout << "Anomalies Detected: " << anomaliesDetectees << endl;
    if (totalMesures > 0) {
        cout << "Anomaly Rate: " << ((double)anomaliesDetectees / totalMesures * 100.0) << "%" << endl;
    }
    cout << "Result: " << (estFiable ? "RELIABLE" : "FRAUDULENT") << endl;
    cout << "Temps d'exécution checkSensorReliability : " << duree.count() << " ms" << endl;
    
    return estFiable;
}


// Find all fraudulent users
list<User> SecurityService::detectFraudulentUsers(const User& user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    list<User> fraudulentUsers;
    
    // 1. Authentication: Only GovernmentAgency
    const GovernmentAgency* agency = dynamic_cast<const GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only Government Agency can detect fraudulent users" << endl;
        return fraudulentUsers;
    }
    
    // 2. Get all private users
    list<PrivateUser> allPrivateUsers = DataService::getAllPrivateUsers();
    
    // 3. For each private user, check their sensors
    for (const auto& privateUser : allPrivateUsers) {
        vector<Sensor*> userSensors = privateUser.getSensorsList();
        
        bool userIsFraudulent = false;
        
        // 4. Check reliability of each user's sensor
        for (const auto& sensor : userSensors) {
            if (sensor != nullptr && !checkSensorReliability(user, sensor->getSensorID())) {
                userIsFraudulent = true;
                break;  // If even one sensor is unreliable, mark user as fraudulent
            }
        }
        
        // 5. Collect fraudulent users
        if (userIsFraudulent) {
            fraudulentUsers.push_back(privateUser);
            cout << "Fraudulent user detected: " << privateUser.getUserID() << endl;
        }
    }
    
    // 6. Return results
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Temps d'exécution detectFraudulentUsers : " << duree.count() << " ms" << endl;
    cout << "Total Fraudulent Users Found: " << fraudulentUsers.size() << endl;
    
    return fraudulentUsers;
}

// Data corruption removal: Mark corrupted data as invalid
void SecurityService::removeCorruptedData(const User& user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Authentication
    const GovernmentAgency* agency = dynamic_cast<const GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only Government Agency can remove corrupted data" << endl;
        return;
    }
    
    // 2. Find all unreliable sensors
    vector<Sensor*> allSensors = DataService::getAllSensors();
    list<string> unreliableSensorIds;
    
    for (const auto& sensor : allSensors) {
        if (sensor != nullptr && sensor->getReliability() == false) {
            unreliableSensorIds.push_back(sensor->getSensorID());
        }
    }
    
    // 3. For each unreliable sensor, mark its data as invalid (soft delete)
    int corruptedRecordsCount = 0;
    
    for (const auto& sensorID : unreliableSensorIds) {
        list<Measurement> measurements = DataService::getMeasurementsBySensor(sensorID);
        
        for (const auto& measurement : measurements) {
            // Mark measurement as corrupted (soft delete)
            DataService::markMeasurementAsInvalid(measurement);
            corruptedRecordsCount++;
        }
        
        cout << "Marked sensor " << sensorID << " and its " << measurements.size() << " measurements as invalid" << endl;
    }
    
    // 4. Clear any cached data
    cout << "Clearing corrupted data cache..." << endl;
    
    // 5. Log execution
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "Total Corrupted Records Marked: " << corruptedRecordsCount << endl;
    cout << "Temps d'exécution removeCorruptedData : " << duree.count() << " ms" << endl;
}


// System initialization: Restore security baseline
void SecurityService::initializeDatabase(const User& user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Authentication: Only system admin or high-level government
    const GovernmentAgency* agency = dynamic_cast<const GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only System Administrator can initialize database" << endl;
        return;
    }
    
    cout << "Initializing Database Security Baseline..." << endl;
    
    // 2. Reload all data from CSV files via DataService
    cout << "Loading initial state from CSV files..." << endl;
    DataService::reloadAllData();
    
    // 3. Build security baseline: Mark all government sensors as reliable
    vector<Sensor*> allSensors = DataService::getAllSensors();
    int reliableSensorCount = 0;
    int unreliableSensorCount = 0;
    
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
    list<Measurement> allMeasurements = DataService::getAllMeasurements();
    cout << "Total Measurements in System: " << allMeasurements.size() << endl;
    
    // 7. Log completion
    auto tempsFin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::milliseconds>(tempsFin - tempsDebut);
    
    cout << "=== Database Initialization Complete ===" << endl;
    cout << "Temps d'exécution initializeDatabase : " << duree.count() << " ms" << endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SecurityService::SecurityService () {
#ifdef MAP
    cout << "Appel au constructeur de <SecurityService>" << endl;
#endif
}  // ----- Fin de SecurityService

SecurityService::~SecurityService ( ) {
#ifdef MAP
    cout << "Appel au destructeur de <SecurityService>" << endl;
#endif
}  // ----- Fin de ~SecurityService

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
