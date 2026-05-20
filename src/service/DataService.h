/*************************************************************************
                           DataService  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <DataService> (fichier DataService.h) ----------------
#if ! defined ( DATASERVICE_H )
#define DATASERVICE_H

#include <ctime>
#include <string>
#include <list>
#include <map>
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/TimeRange.h"
#include "../model/AirCleaner.h"
#include "../model/DataContainer.h"

using namespace std;

//------------------------------------------------------------------------
// Role de la classe <DataService>
//
// Provides data access layer between Services and DataContainer
// Handles all data queries and updates for the AirWatcher system
//
//------------------------------------------------------------------------

class DataService {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // Sensor queries
    static vector<Sensor*> getSensors(User user);
    
    static vector<Sensor> getSensorsInArea(double lat, double lon, double radius);
    
    static Sensor getSensorById(string sensorID);
    
    static vector<Sensor> getSensorsByUser(string userID);
    
    static vector<Sensor*> getAllSensors();
    
    // Measurement queries
    static vector<Measurement> getMeasurements(User user);
    
    static list<Measurement> getMeasurementsBySensor(string sensorID);
    
    static list<Measurement> getAllMeasurements();
    
    static void addMeasurement(DateTime a_measureDate, Sensor* a_sensor, Attribute* an_attribute, double a_value);
    
    // User queries
    static list<PrivateUser> getAllPrivateUsers();
    
    // Air Cleaner queries
    static AirCleaner getCleanerById(string cleanerID);
    
    // Data management
    static void markMeasurementAsInvalid(Measurement measurement);
    
    static void updateSensorStatus(string sensorID, bool isReliable);
    
    static void clearCorruptionFlags();
    
    static void reloadAllData();
    
    // User history
    static list<Measurement> getUserHistory(User user);

    // Initialization
    static void initializeDataContainer(DataContainer* container);
    
    static DataContainer* getDataContainer();

//-------------------------------------------- Constructeurs - destructeur

    DataService ();
    
    virtual ~DataService ();
    
//------------------------------------------------------------------ PRIVATE

private:
    
    static DataContainer* dataContainer;  // Static reference to global data container
    
};


#endif // DATASERVICE_H
