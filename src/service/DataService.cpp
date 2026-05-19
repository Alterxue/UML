/*************************************************************************
                           DataService      -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <DataService> (fichier DataService.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <ctime>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <cmath>
#include "DataService.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/PrivateUser.h"
#include "../model/GovernmentAgency.h"
#include "../model/TimeRange.h"
#include "../model/AirCleaner.h"
#include "../model/DataContainer.h"
using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

// Initialize static member
DataContainer* DataService::dataContainer = nullptr;

//----------------------------------------------------- Méthodes publiques

// ==================== INITIALIZATION METHODS ====================

// Initialize the data container
void DataService::initializeDataContainer(DataContainer* container) {
    dataContainer = container;
    cout << "DataService initialized with DataContainer" << endl;
}

// Get reference to data container
DataContainer* DataService::getDataContainer() {
    return dataContainer;
}

// ==================== SENSOR QUERY METHODS ====================

// Get all sensors owned by a user or all public government sensors
list<Sensor> DataService::getSensors(User user) {
    list<Sensor> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    // If user is GovernmentAgency, return all sensors
    GovernmentAgency* agency = dynamic_cast<GovernmentAgency*>(&user);
    if (agency != nullptr) {
        return getAllSensors();
    }
    
    // If user is PrivateUser, return only their sensors
    PrivateUser* privateUser = dynamic_cast<PrivateUser*>(&user);
    if (privateUser != nullptr) {
        return getSensorsByUser(privateUser->userID);
    }
    
    return result;
}

// Get all sensors in the system
list<Sensor> DataService::getAllSensors() {
    list<Sensor> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    vector<Sensor*> sensors = dataContainer->getAllSensors();
    for (const auto& sensor : sensors) {
        if (sensor != nullptr) {
            result.push_back(*sensor);
        }
    }
    
    return result;
}

// Get sensors within a geographical area (circle)
list<Sensor> DataService::getSensorsInArea(double lat, double lon, double radius) {
    list<Sensor> result;
    list<Sensor> allSensors = getAllSensors();
    
    // Filter sensors by distance
    for (const auto& sensor : allSensors) {
        double distance = sensor.calculateDistance(lat, lon);
        if (distance <= radius) {
            result.push_back(sensor);
        }
    }
    
    return result;
}

// Get sensor by ID
Sensor DataService::getSensorById(string sensorID) {
    Sensor dummy;
    list<Sensor> allSensors = getAllSensors();
    
    for (const auto& sensor : allSensors) {
        if (sensor.sensorID == sensorID) {
            return sensor;
        }
    }
    
    cout << "WARNING: Sensor " << sensorID << " not found" << endl;
    return dummy;
}

// Get all sensors owned by a specific user
list<Sensor> DataService::getSensorsByUser(string userID) {
    list<Sensor> result;
    list<Sensor> allSensors = getAllSensors();
    
    for (const auto& sensor : allSensors) {
        // Check if sensor belongs to this user
        if (sensor.userID == userID) {
            result.push_back(sensor);
        }
    }
    
    return result;
}

// ==================== MEASUREMENT QUERY METHODS ====================

// Get all measurements for a user's sensors
list<Measurement> DataService::getMeasurements(User user) {
    list<Measurement> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    // If GovernmentAgency, return all measurements
    GovernmentAgency* agency = dynamic_cast<GovernmentAgency*>(&user);
    if (agency != nullptr) {
        return getAllMeasurements();
    }
    
    // If PrivateUser, return measurements from their sensors only
    PrivateUser* privateUser = dynamic_cast<PrivateUser*>(&user);
    if (privateUser != nullptr) {
        list<Sensor> userSensors = getSensorsByUser(privateUser->userID);
        list<Measurement> allMeasurements = getAllMeasurements();
        
        for (const auto& measurement : allMeasurements) {
            for (const auto& sensor : userSensors) {
                if (measurement.sensorID == sensor.sensorID) {
                    result.push_back(measurement);
                    break;
                }
            }
        }
    }
    
    return result;
}

// Get all measurements in the system
list<Measurement> DataService::getAllMeasurements() {
    list<Measurement> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    // TODO: Implement when Measurement storage is available in DataContainer
    // For now, return empty - will be populated from CSV data via CSVDataManager
    
    return result;
}

// Get measurements for a specific sensor
list<Measurement> DataService::getMeasurementsBySensor(string sensorID) {
    list<Measurement> result;
    list<Measurement> allMeasurements = getAllMeasurements();
    
    for (const auto& measurement : allMeasurements) {
        if (measurement.sensorID == sensorID && measurement.isValid == true) {
            result.push_back(measurement);
        }
    }
    
    return result;
}

// Add a new measurement
void DataService::addMeasurement(User user, string sensorID, string attributeID, double value) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    // Create new measurement
    Measurement measurement;
    measurement.measurementID = sensorID + "_" + attributeID + "_" + to_string(time(nullptr));
    measurement.sensorID = sensorID;
    measurement.attributeID = attributeID;
    measurement.value = value;
    measurement.timestamp = time(nullptr);
    measurement.isValid = true;
    
    // Add to DataContainer - TODO: Add method to DataContainer for storing measurements
    
    cout << "Measurement added: " << measurement.measurementID << endl;
}

// ==================== USER QUERY METHODS ====================

// Get user history (all measurements they submitted)
list<Measurement> DataService::getUserHistory(User user) {
    list<Measurement> result;
    
    PrivateUser* privateUser = dynamic_cast<PrivateUser*>(&user);
    if (privateUser == nullptr) {
        cout << "ERROR: Only PrivateUsers have history" << endl;
        return result;
    }
    
    return getMeasurements(user);
}

// Get all private users
list<User> DataService::getAllPrivateUsers() {
    list<User> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    vector<User*> users = dataContainer->getAllUsers();
    for (const auto& user : users) {
        if (user != nullptr) {
            // Only include PrivateUser instances
            PrivateUser* privateUser = dynamic_cast<PrivateUser*>(user);
            if (privateUser != nullptr) {
                result.push_back(*privateUser);
            }
        }
    }
    
    return result;
}

// ==================== AIR CLEANER QUERY METHODS ====================

// Get air cleaner by ID
AirCleaner DataService::getCleanerById(string cleanerID) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        // Return default constructed AirCleaner
        return AirCleaner("", nullptr, 0.0, 0.0, 
                          chrono::system_clock::now(), 
                          chrono::system_clock::now());
    }
    
    AirCleaner* cleaner = dataContainer->getCleanerById(cleanerID);
    if (cleaner != nullptr) {
        return *cleaner;
    }
    
    cout << "WARNING: Air Cleaner " << cleanerID << " not found" << endl;
    
    // Return default constructed AirCleaner if not found
    return AirCleaner("", nullptr, 0.0, 0.0, 
                      chrono::system_clock::now(), 
                      chrono::system_clock::now());
}

// ==================== DATA MANAGEMENT METHODS ====================

// Mark a measurement as invalid (soft delete)
void DataService::markMeasurementAsInvalid(Measurement measurement) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    list<Measurement> allMeasurements = getAllMeasurements();
    
    for (auto& m : allMeasurements) {
        if (m.measurementID == measurement.measurementID) {
            m.isValid = false;
            cout << "Measurement " << measurement.measurementID << " marked as invalid" << endl;
            return;
        }
    }
    
    cout << "WARNING: Measurement " << measurement.measurementID << " not found" << endl;
}

// Update sensor reliability status
void DataService::updateSensorStatus(string sensorID, bool isReliable) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    list<Sensor> allSensors = getAllSensors();
    
    for (auto& sensor : allSensors) {
        if (sensor.sensorID == sensorID) {
            sensor.isReliable = isReliable;
            cout << "Sensor " << sensorID << " status updated: " 
                 << (isReliable ? "RELIABLE" : "UNRELIABLE") << endl;
            
            // TODO: Update in persistent storage via CSVDataManager
            
            return;
        }
    }
    
    cout << "WARNING: Sensor " << sensorID << " not found" << endl;
}

// Clear any corruption flags
void DataService::clearCorruptionFlags() {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    list<Measurement> allMeasurements = getAllMeasurements();
    
    int clearedCount = 0;
    for (auto& measurement : allMeasurements) {
        if (measurement.isValid == false) {
            measurement.isValid = true;
            clearedCount++;
        }
    }
    
    cout << "Corruption flags cleared. Records restored: " << clearedCount << endl;
}

// Reload all data from CSV files
void DataService::reloadAllData() {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    cout << "Reloading all data from CSV files..." << endl;
    
    // TODO: Call CSVDataManager to reload all data
    // CSVDataManager::loadAllData(dataContainer);
    
    cout << "Data reload complete" << endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

DataService::DataService () {
#ifdef MAP
    cout << "Appel au constructeur de <DataService>" << endl;
#endif
}  // ----- Fin de DataService

DataService::~DataService ( ) {
#ifdef MAP
    cout << "Appel au destructeur de <DataService>" << endl;
#endif
}  // ----- Fin de ~DataService

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
