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
using namespace std;
#include <vector>
#include <ctime>
#include <string>
#include <list>
#include <map>
#include "../model/Attribute.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/TimeRange.h"
#include "../model/AirCleaner.h"
#include "../model/PrivateUser.h"
#include "../model/DataContainer.h"

//------------------------------------------------------------------------
// Role de la classe <DataService>
// Fournit une couche d'accès aux données entre les Services et le DataContainer
// Gère toutes les requêtes de données et les mises à jour pour le système AirWatcher
//------------------------------------------------------------------------

class DataService {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // =============== Initialisation ===============  
    static void initializeDataContainer(DataContainer* container);
    // Mode d'emploi :
    // Doit être appelée avant toute utilisation de DataService 
    // pour fournir une référence au DataContainer
    
    static DataContainer* getDataContainer();
    // Mode d'emploi :
    // Permet d'accéder au DataContainer global, utilisé principalement pour les tests unitaires

    // =============== Requête de sur les capteurs ===============
    static vector<Sensor*> getAllSensors();
    // Mode d'emploi :
    // Renvoie tous les capteurs présents dans le DataContainer, sans filtrage.

    static vector<Sensor*> getSensors(const User& user);
    // Mode d'emploi :
    // Renvoie les capteurs visibles pour un utilisateur donné.
    // - Agence gouvernementale : tous les capteurs
    // - Utilisateur privé : ses capteurs
    // - Autre rôle : ensemble vide

    static vector<Sensor*> getSensorsByUser(const std::string& userID);
    // Mode d'emploi :
    // Renvoie les capteurs appartenant à l'utilisateur identifié par userID.
    // Cette méthode effectue un accès direct par identifiant, sans logique de rôle.

    static vector<Sensor*> getSensorsInArea(double lat, double lon, double radiusKM);
    // Mode d'emploi :
    // Renvoie les capteurs situés dans un rayon donné autour d'une position géographique
    
    // =============== Requêtes sur les mesures ===============
    static vector<Measurement*> getAllMeasurements();
    // Mode d'emploi :
    // Renvoie toutes les mesures de tous les capteurs, sans filtrage

    static vector<Measurement*> getMeasurements(const User& user);
    // Mode d'emploi :
    // Renvoie les mesures visibles pour un utilisateur donné, en fonction de ses capteurs accessibles
    
    static vector<Measurement*> getMeasurementsBySensor(const string& sensorID);
    // Mode d'emploi :
    // Renvoie la liste des mesures associées au capteur identifié par sensorID
    
    static void addMeasurement(DateTime measureDate, Sensor* sensor, Attribute* attribute, double value);
    // Mode d'emploi :
    // Permet d'ajouter une nouvelle mesure pour un capteur donné, avec un attribut et une valeur
    
    // =============== Requêtes sur les utilisateurs ===============
    static vector<PrivateUser*> getAllPrivateUsers();
    
    // =============== Requêtes sur les AirCleaners ===============
    static AirCleaner* getCleanerById(const std::string& cleanerID);
    
    // =============== Requêtes de maintenance ===============
    static void loadAllData();
    
    static void updateSensorStatus(const string& sensorID, bool isReliable);
    // Mode d'emploi :
    // Met à jour le statut de fiabilité d'un capteur en base de données
    
    static void markMeasurementAsInvalid(const Measurement& measurement);
    // Mode d'emploi :
    // Marque une mesure comme invalide (soft delete)
    
    static void reloadAllData();
    // Mode d'emploi :
    // Recharge toutes les données depuis les fichiers CSV
    
    static void clearCorruptionFlags();
    // Mode d'emploi :
    // Réinitialise les drapeaux de corruption temporaires

//-------------------------------------------- Constructeurs - destructeur
    DataService ();
    // Mode d'emploi :
    // Constructeur de la classe DataService
    
    ~DataService ();
    // Mode d'emploi :
    // Destructeur de la classe DataService
    
//------------------------------------------------------------------ PRIVATE

private:
    
    static DataContainer* dataContainer;  // Static reference to global data container
    
};


#endif // DATASERVICE_H
