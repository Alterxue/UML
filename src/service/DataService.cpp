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
#include "../dao/CSVDataManager.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/PrivateUser.h"
#include "../model/GovernmentAgency.h"
#include "../model/TimeRange.h"
#include "../model/AirCleaner.h"
#include "../model/DataContainer.h"
#include "../model/Role.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
// Initialise le membre statique
DataContainer* DataService::dataContainer = nullptr;

//----------------------------------------------------- Méthodes publiques
// ======= Initialisation =======
void DataService::initializeDataContainer(DataContainer* container) 
{
    if (container == nullptr) {
        cout << "ERREUR: DataContainer null" << endl;
        return;
    }
    dataContainer = container;
    cout << "DataService initialized with DataContainer" << endl;
} //----- Fin de initializeDataContainer

DataContainer* DataService::getDataContainer() 
{
    return dataContainer;
} //----- Fin de getDataContainer

// =============== Requête de sur les capteurs ===============
vector<Sensor*> DataService::getAllSensors() 
{
    vector<Sensor*> result;
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    const map<string, Sensor*>& sensors = dataContainer->getAllSensors(); 
    result.reserve(sensors.size()); // Préallouer de la mémoire pour éviter les reallocations
    for (const map<string, Sensor*>::value_type& pair : sensors) {
        Sensor* ptr = pair.second;
        if (ptr != nullptr) result.push_back(ptr);
    }
    return result;
} //----- Fin de getAllSensors

vector<Sensor*> DataService::getSensors(const User& user) 
{
    vector<Sensor*> result;

    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }

    if (user.getRole() == GOVERNMENT_AGENCY) {
        return getAllSensors();
    }

    if (user.getRole() == PRIVATE_USER) {
        return getSensorsByUser(user.getUserID());
    }
    return result;
} //----- Fin de getSensors

vector<Sensor*> DataService::getSensorsByUser(const string& userID)
{
    vector<Sensor*> result;
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }

    PrivateUser* privateUser = dataContainer->getPrivateUserByID(userID);
    if (privateUser == nullptr){
        return result;
    }

    const vector<Sensor*>& sensors = privateUser->getSensorsList();
    result.reserve(sensors.size());
    for (const vector<Sensor*>::value_type& sensorPtr : sensors) {
        if (sensorPtr != nullptr) {
            result.push_back(sensorPtr);
        }
    }

    return result;
} //----- Fin de getSensorsByUser

vector<Sensor*> DataService::getSensorsInArea(double lat, double lon, double radiusKM) 
{
    vector<Sensor*> result;
    vector<Sensor*> allSensors = getAllSensors();
    
    for (const vector<Sensor*>::value_type& sensor : allSensors) {
        double distance = sensor->calculateDistance(lat, lon);
        if (distance <= radiusKM) {
            result.push_back(sensor);
        }
    }
    
    return result;
} //----- Fin de getSensorsInArea

// =============== Requêtes sur les mesures ===============
vector<Measurement*> DataService::getAllMeasurements() 
{
    vector<Measurement*> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    const map<string, vector<Measurement*>>& measurementsBySensor = dataContainer->getAllMeasurementsBySensor();
    for (const map<string, vector<Measurement*>>::value_type& pair : measurementsBySensor) {
        for (Measurement* measurement : pair.second) {
            if (measurement != nullptr) {
                result.push_back(measurement);
            }
        }
    }
    
    return result;
} //----- Fin de getAllMeasurements

vector<Measurement*> DataService::getMeasurements(const User& user) 
{
    vector<Measurement*> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    // Si agence gouvernementale, retourner toutes les mesures
    if (user.getRole() == GOVERNMENT_AGENCY) {
        return getAllMeasurements();
    }
    
    // Si PrivateUser, retourner les mesures de ses capteurs
    if (user.getRole() == PRIVATE_USER) { 
        const vector<Sensor*>& userSensors = getSensorsByUser(user.getUserID());
        for (const vector<Sensor*>::value_type& sensor : userSensors) {
            if (sensor != nullptr) {
                const vector<Measurement*>& sensorMeasurements = sensor->getMeasurements();
                for (const vector<Measurement*>::value_type& measurement : sensorMeasurements) {
                    if (measurement != nullptr) {
                        result.push_back(measurement);
                    }
                }
            }
        }   
    }
    return result;
} //----- Fin de getMeasurements

vector<Measurement*> DataService::getMeasurementsBySensor(const string& sensorID) 
{
    vector<Measurement*> result;
    
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }
    
    const map<string, vector<Measurement*>>& measurementsBySensor = dataContainer->getAllMeasurementsBySensor();
    map<string, vector<Measurement*>>::const_iterator it = measurementsBySensor.find(sensorID);

    if (it != measurementsBySensor.end()) {
        for (Measurement* measurement : it->second) {
            if (measurement != nullptr) {
                result.push_back(measurement);
            }
        }
    } 
    else {
        cout << "AVERTISSEMENT: Capteur " << sensorID << " non trouvé." << endl;
    }
    
    return result;
} //----- Fin de getMeasurementsBySensor

vector<Measurement*> DataService::getUserHistory(const PrivateUser& user)
{
    vector<Measurement*> result;

    if (dataContainer == nullptr) {
        cout << "ERREUR: DataContainer non initialisé" << endl;
        return result;
    }

    const vector<Sensor*>& sensors = user.getSensorsList();
    for (const Sensor* sensor : sensors) {
        if (sensor == nullptr) {
            continue;
        }

        const vector<Measurement*>& measurements = sensor->getMeasurements();
        for (Measurement* measurement : measurements) {
            if (measurement != nullptr) {
                result.push_back(measurement);
            }
        }
    }

    return result;
} //----- Fin de getUserHistory

// Add a new measurement
void DataService::addMeasurement(DateTime measureDate, Sensor* sensor, Attribute* attribute, double value) {
    if (dataContainer == nullptr) {
        cout << "ERREUR: DataContainer non initialisé" << endl;
        return;
    }

    if (sensor == nullptr || attribute == nullptr) {
        cout << "ERREUR: Impossible d'ajouter une mesure avec un capteur ou un attribut nul" << endl;
        return;
    }

    Measurement* measurement = new Measurement(measureDate, sensor, attribute, value);
    sensor->addMeasurement(measurement);
    dataContainer->addMeasurement(measurement);

    cout << "Measurement added for sensor " << sensor->getSensorID() << endl;
} //----- Fin de addMeasurement

// =============== Requêtes sur les utilisateurs ===============
vector<PrivateUser*> DataService::getAllPrivateUsers() {
    vector<PrivateUser*> result;

    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return result;
    }

    const map<string, PrivateUser*>& users = dataContainer->getAllUsers();
    result.reserve(users.size());
    for (const map<string, PrivateUser*>::value_type& pair : users) {
        if (pair.second != nullptr) {
            result.push_back(pair .second);
        }
    }

    return result;
} //----- Fin de getAllPrivateUsers

// =============== Requêtes sur les AirCleaners ===============
AirCleaner* DataService::getCleanerById(const string& cleanerID) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return nullptr;
    }

    return dataContainer->getAirCleanerByID(cleanerID);
}

// =============== Requêtes de maintenance ===============
void DataService::reloadAllData() {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    cout << "Reloading all data from CSV files..." << endl;

    CSVDataManager csvDataManager;
    csvDataManager.loadAttributes(*dataContainer);
    csvDataManager.loadSensors(*dataContainer);
    csvDataManager.loadUsers(*dataContainer);
    csvDataManager.loadCleaners(*dataContainer);
    csvDataManager.loadProviders(*dataContainer);
    csvDataManager.loadMeasurements(*dataContainer);
    
    cout << "Data reload complete" << endl;
}

// Update sensor reliability status
void DataService::updateSensorStatus(const string& sensorID, bool isReliable) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    vector<Sensor*> allSensors = getAllSensors();
    for (const vector<Sensor*>::value_type& sensor : allSensors) {
        if (sensor != nullptr && sensor->getSensorID() == sensorID) {
            sensor->setReliability(isReliable);
            cout << "Updated sensor " << sensorID << " reliability to " << (isReliable ? "RELIABLE" : "UNRELIABLE") << endl;
            return;
        }
    }
    
    cout << "WARNING: Sensor " << sensorID << " not found for status update" << endl;
} //----- Fin de updateSensorStatus

// Mark a measurement as invalid (soft delete)
void DataService::markMeasurementAsInvalid(Measurement& measurement) {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    measurement.setIsValid(false);
    cout << "Marked measurement as invalid for sensor " << measurement.getSensor()->getSensorID() << endl;
} //----- Fin de markMeasurementAsInvalid



// Clear corruption flags
void DataService::clearCorruptionFlags() {
    if (dataContainer == nullptr) {
        cout << "ERROR: DataContainer not initialized" << endl;
        return;
    }

    // Iterate through all sensors and reset corruption flags if they exist
    vector<Sensor*> allSensors = getAllSensors();
    for (const auto& sensor : allSensors) {
        if (sensor != nullptr) {
            // For now, we just set all sensors to reliable
            sensor->setReliability(true);
        }
    }
    
    cout << "Corruption flags cleared for all sensors" << endl;
} //----- Fin de clearCorruptionFlags

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
DataService::DataService () 
{
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
