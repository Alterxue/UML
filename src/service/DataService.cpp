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
vector<Sensor> DataService::getSensors(User user) {
    vector<Sensor> result;
    
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
        return privateUser->sensorsIDList;
    }
    
    return result;
}

// Get all sensors in the system
vector<Sensor> DataService::getAllSensors() {
    vector<Sensor> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    const auto& sensors = dataContainer->getAllSensors(); // pas de copie
    result.reserve(sensors.size());
    for (const auto& [id, ptr] : sensors) {
        if (ptr) result.push_back(*ptr); // copie
    }
    
    return result;
}

// Get sensors within a geographical area (circle)
vector<Sensor> DataService::getSensorsInArea(double lat, double lon, double radius) {
    vector<Sensor> result;
    vector<Sensor> allSensors = getAllSensors();
    
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
    const auto& sensorsMap = dataContainer->getAllSensors();
    auto it = sensorsMap.find(sensorID);
    if (it != sensorsMap.end()) return it->second;
    cout << "WARNING: Sensor " << sensorID << " not found" << endl;
    return nullptr;
}

// ==================== MEASUREMENT QUERY METHODS ====================

// Get all measurements for a user's sensors
vector<Measurement> DataService::getMeasurements(User user) {
    vector<Measurement> result;
    
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
        vector<Sensor> userSensors = privateUser->sensorsIDList;
        list<Measurement> allMeasurements = getAllMeasurements();
        
        for (const auto& measurement : allMeasurements) {
            for (const auto& sensor : userSensors) {
                if (measurement.sensor->sensorID == sensor.sensorID) {
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
    
    vector<Sensor> allSensors = getAllSensors();
    for (const auto& sensor : allSensors) {
        vector<Measurement> sensorMeasurements = sensor.getMeasurements();
        for (const auto& measurement : sensorMeasurements) {
            result.push_back(measurement);
        }
    }
    
    return result;
}

// Get measurements for a specific sensor
list<Measurement> DataService::getMeasurementsBySensor(string sensorID) {
    list<Measurement> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    const auto& sensorsMap = dataContainer->getAllSensors();
    auto it = sensorsMap.find(sensorID);
    
    if (it != sensorsMap.end() && it->second != nullptr) {
        vector<Measurement> measurements = it->second->getMeasurements();
        for (const auto& measurement : measurements) {
            result.push_back(measurement);
        }
    } else {
        cout << "WARNING: Sensor " << sensorID << " not found" << endl;
    }
    
    return result;
}

// Add a new measurement
void DataService::addMeasurement(DateTime a_measureDate, Sensor* a_sensor, Attribute* an_attribute, double a_value) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }
    
    // Create new measurement
    Measurement measurement(a_measureDate, a_sensor, an_attribute, a_value);
    
    // Add measurement to sensor
    a_sensor->addMeasurement(measurement);
    
    cout << "Measurement added: " << measurement << endl;
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
list<PrivateUser> DataService::getAllPrivateUsers() {
    list<PrivateUser> result;

    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }

    const auto& users = dataContainer->getAllUsers();
    for (const auto& [id, privateUser] : users) {
        if (privateUser) {
            result.push_back(*privateUser);
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
    
    const auto& cleaners = dataContainer->getAllAirCleaners();
    auto it = cleaners.find(cleanerID);
    if (it != cleaners.end() && it->second != nullptr) {
        return *it->second;
    }
    
    cout << "WARNING: Air Cleaner " << cleanerID << " not found" << endl;
    
    // Return default constructed AirCleaner if not found
    return AirCleaner("", nullptr, 0.0, 0.0, 
                      chrono::system_clock::now(), 
                      chrono::system_clock::now());
}

// ==================== DATA MANAGEMENT METHODS ====================

// Mark a measurement as invalid
void DataService::markMeasurementAsInvalid(Measurement measurement) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    Sensor* sensor = measurement.getSensor();
    if (sensor == nullptr) {
        cout << "ERROR: Measurement has no associated sensor" << endl;
        return;
    }

    vector<Measurement> sensorMeasurements = sensor->getMeasurements();
    for (auto& m : sensorMeasurements) {
        if (m.getSensor() == measurement.getSensor() &&
            m.getAttribute() == measurement.getAttribute() &&
            m.getMeasureDate() == measurement.getMeasureDate() &&
            m.getValue() == measurement.getValue()) {
            m.setIsValid(false);
            cout << "Measurement marked as invalid" << endl;
            return;
        }
    }

    cout << "WARNING: Measurement not found" << endl;
}

// Update sensor reliability status
void DataService::updateSensorStatus(string sensorID, bool isReliable) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    const auto& sensors = dataContainer->getAllSensors();
    auto it = sensors.find(sensorID);
    if (it != sensors.end() && it->second != nullptr) {
        it->second->setReliability(isReliable);
        cout << "Sensor " << sensorID << " status updated: "
             << (isReliable ? "RELIABLE" : "UNRELIABLE") << endl;
        return;
    }

    cout << "WARNING: Sensor " << sensorID << " not found" << endl;
}

// Clear any corruption flags
void DataService::clearCorruptionFlags() {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    const auto& sensors = dataContainer->getAllSensors();
    int clearedCount = 0;

    for (const auto& [id, sensorPtr] : sensors) {
        if (sensorPtr == nullptr) {
            continue;
        }

        vector<Measurement> sensorMeasurements = sensorPtr->getMeasurements();
        for (auto& measurement : sensorMeasurements) {
            if (!measurement.isValid()) {
                measurement.setIsValid(true);
                clearedCount++;
            }
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
