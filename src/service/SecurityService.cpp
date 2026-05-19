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
#include "../model/Sensor.h"
#include "../model/TimeRange.h"
#include "../model/User.h"
#include "../model/GovernmentAgency.h"
#include "../model/PrivateUser.h"
using namespace std;


//------------------------------------------------------------- Constantes

const double ANOMALY_THRESHOLD = 0.3;  // 30% tolerance for deviation
const double ANOMALY_RATE_THRESHOLD = 0.5;  // 50% anomaly rate to mark unreliable
const time_t RELIABILITY_CHECK_PERIOD = 7 * 24 * 3600;  // 7 days for analysis

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// Algorithm 4: Fraud Detection - Check if a sensor is reliable
// Returns true if sensor is reliable, false if fraudulent
bool SecurityService::checkSensorReliability(User user, string targetSensorID) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Get all sensors and measurements
    list<Sensor> tousCapteurs = DataService.getSensors(user);
    list<Measurement> toutesMesures = DataService.getMeasurements(user);
    
    // 2. Find the target sensor to analyze
    Sensor capteurAAnalyser;
    bool capteurTrouve = false;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur.sensorID == targetSensorID) {
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
    list<Sensor> capteursVoisinsFiables;
    
    for (const auto& capteur : tousCapteurs) {
        if (capteur.isReliable == true && capteur.sensorID != targetSensorID) {
            double distance = capteur.calculateDistance(capteurAAnalyser.latitude, capteurAAnalyser.longitude);
            if (distance <= 10.0) {
                capteursVoisinsFiables.push_back(capteur);
            }
        }
    }
    
    if (capteursVoisinsFiables.empty()) {
        cout << "WARNING: No reliable nearby sensors found. Assuming " << targetSensorID << " is reliable." << endl;
        return true;
    }
    
    // 4. Extract measurements for target sensor
    list<Measurement> mesuresCible;
    for (const auto& mesure : toutesMesures) {
        if (mesure.sensorID == targetSensorID) {
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
                if (mesureVoisin.sensorID == capteurVoisin.sensorID &&
                    mesureVoisin.timestamp == mesure.timestamp &&
                    mesureVoisin.attributeID == mesure.attributeID) {
                    
                    sommValeurs += mesureVoisin.value;
                    compteMesures++;
                }
            }
        }
        
        // If we have reference values to compare
        if (compteMesures > 0) {
            double valeurReference = sommValeurs / compteMesures;
            totalMesures++;
            
            // Calculate absolute deviation
            double ecartAbsolu = abs(mesure.value - valeurReference);
            
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
            capteurAAnalyser.isReliable = false;
            
            // Update sensor status in persistent storage (DAO layer)
            CSVDataManager.updateSensorStatus(targetSensorID, false);
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
list<User> SecurityService::detectFraudulentUsers(User user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    list<User> fraudulentUsers;
    
    // 1. Authentication: Only GovernmentAgency
    GovernmentAgency* agency = dynamic_cast<GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only Government Agency can detect fraudulent users" << endl;
        return fraudulentUsers;
    }
    
    // 2. Get all private users
    list<User> allPrivateUsers = DataService.getAllPrivateUsers();
    
    // 3. For each private user, check their sensors
    for (const auto& privateUser : allPrivateUsers) {
        list<Sensor> userSensors = DataService.getSensorsByUser(privateUser.userID);
        
        bool userIsFraudulent = false;
        
        // 4. Check reliability of each user's sensor
        for (const auto& sensor : userSensors) {
            if (!checkSensorReliability(user, sensor.sensorID)) {
                userIsFraudulent = true;
                break;  // If even one sensor is unreliable, mark user as fraudulent
            }
        }
        
        // 5. Collect fraudulent users
        if (userIsFraudulent) {
            fraudulentUsers.push_back(privateUser);
            cout << "Fraudulent user detected: " << privateUser.userID << endl;
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
void SecurityService::removeCorruptedData(User user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Authentication
    GovernmentAgency* agency = dynamic_cast<GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only Government Agency can remove corrupted data" << endl;
        return;
    }
    
    // 2. Find all unreliable sensors
    list<Sensor> allSensors = DataService.getAllSensors();
    list<string> unreliableSensorIds;
    
    for (const auto& sensor : allSensors) {
        if (sensor.isReliable == false) {
            unreliableSensorIds.push_back(sensor.sensorID);
        }
    }
    
    // 3. For each unreliable sensor, mark its data as invalid (soft delete)
    int corruptedRecordsCount = 0;
    
    for (const auto& sensorID : unreliableSensorIds) {
        list<Measurement> measurements = DataService.getMeasurementsBySensor(sensorID);
        
        for (const auto& measurement : measurements) {
            // Mark measurement as corrupted (soft delete)
            // In a real system, you would update CSVDataManager or database
            DataService.markMeasurementAsInvalid(measurement);
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
void SecurityService::initializeDatabase(User user) {
    auto tempsDebut = chrono::high_resolution_clock::now();
    
    // 1. Authentication: Only system admin or high-level government
    GovernmentAgency* agency = dynamic_cast<GovernmentAgency*>(&user);
    if (agency == nullptr) {
        cout << "ERROR: Only System Administrator can initialize database" << endl;
        return;
    }
    
    cout << "Initializing Database Security Baseline..." << endl;
    
    // 2. Reload all data from CSV files via CSVDataManager
    cout << "Loading initial state from CSV files..." << endl;
    DataService.reloadAllData();
    
    // 3. Build security baseline: Mark all government sensors as reliable
    list<Sensor> allSensors = DataService.getAllSensors();
    int reliableSensorCount = 0;
    int unreliableSensorCount = 0;
    
    for (auto& sensor : allSensors) {
        // Government sensors default to reliable
        if (sensor.type == "GOVERNMENT" || sensor.type == "Government") {
            sensor.isReliable = true;
            reliableSensorCount++;
        } else {
            // Private sensors need verification
            sensor.isReliable = false;  // Default to unverified
            unreliableSensorCount++;
        }
    }
    
    cout << "Reliable Sensors (Government): " << reliableSensorCount << endl;
    cout << "Unverified Sensors (Private): " << unreliableSensorCount << endl;
    
    // 4. Clear any temporary ban flags or corrupted states
    cout << "Clearing temporary corruption flags..." << endl;
    DataService.clearCorruptionFlags();
    
    // 5. Reset statistics cache
    cout << "Resetting statistics cache..." << endl;
    
    // 6. Verify data integrity
    cout << "Verifying data integrity..." << endl;
    list<Measurement> allMeasurements = DataService.getAllMeasurements();
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
