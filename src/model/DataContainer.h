/*************************************************************************
                           DataContainer  -  description
                             -------------------
    début                : 09/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <DataContainer> (fichier DataContainer.h) ----------------
#if ! defined ( DATACONTAINER_H )
#define DATACONTAINER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <map>

class Attribute;
class Sensor;
class PrivateUser;
class AirCleaner;
class Provider;
class Measurement;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DataContainer> : 
// Permet de stocker toutes les données des fichiers, après leur
// chargement, pendant toute l'execution
// Contiendra l'ensemble des Attributes, PrivateUSer, Sensors, AirCleaners,
// Providers et Measurements
//------------------------------------------------------------------------

class DataContainer
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    void addAttribute(Attribute* ptr_atribute);
    // Mode d'emploi : 
    // Ajoute un attribut de mesure à la collection

    void addSensor(Sensor* ptr_sensor);
    // Mode d'emploi :
    // Ajoute un capteur à la collection

    void addUser(PrivateUser* ptr_privateuser);
    // Mode d'emploi :
    // Ajoute un utilisateur à la collection

    void addAirCleaner(AirCleaner* ptr_aircleaner);
    // Mode d'emploi :
    // Ajoute un air cleaner à la collection

    void addProvider(Provider* ptr_provider);
    // Mode d'emploi :
    // Ajoute un fournisseur à la collection

    void addMeasurement(Measurement* ptr_measurement);
    // Mode d'emploi :
    // Ajoute une mesure à la collection

    const std::map<std::string, Attribute*>& getAllAttributes() const;
    // Mode d'emploi :
    // Renvoie la collection des attributs

    const std::map<std::string, Sensor*>& getAllSensors() const;
    // Mode d'emploi :
    // Renvoie la collection des capteurs

    const std::map<std::string, PrivateUser*>& getAllUsers() const;
    // Mode d'emploi :
    // Renvoie la collection des utilisateurs

    const std::map<std::string, AirCleaner*>& getAllAirCleaners() const;
    // Mode d'emploi :
    // Renvoie la collection des air cleaners

    const std::map<std::string, Provider*>& getAllProviders() const;
    // Mode d'emploi :
    // Renvoie la collection des fournisseurs

    const std::map<std::string, std::vector<Measurement*>>& getAllMeasurementsBySensor() const;
    // Mode d'emploi :
    // Renvoie la collection des mesures, organisées par capteur

    Attribute * getAttributeByID(const std::string& attributeID);
    // Mode d'emploi :
    // Permet de récupérer un attribut à partir de son ID, retourne nullptr si l'attribut n'est pas trouvé

    Sensor * getSensorByID(const std::string& sensorID);
    // Mode d'emploi :
    // Permet de récupérer un capteur à partir de son ID

    PrivateUser* getPrivateUserByID(const std::string& userID);
    // Mode d'emploi :
    // Permet de récupérer un utilisateur à partir de son ID

    AirCleaner * getAirCleanerByID(const std::string& airCleanerID);
    // Mode d'emploi :
    // Permet de récupérer un air cleaner à partir de son ID

    Provider* getProviderByID(const std::string& providerID);
    // Mode d'emploi :
    // Permet de récupérer un fournisseur à partir de son ID

    void removeSensor(const std::string& sensorID);
    // Mode d'emploi :
    // Supprime un capteur de la collection, ainsi que toutes les mesures
    // qui lui sont associées, et libère la mémoire correspondante.

//------------------------------------------------- Surcharge d'opérateurs
    DataContainer& operator=(const DataContainer&) = delete;
    // Mode d'emploi :
    // Empêche l'affectation accidentelle d'un conteneur possédant des pointeurs

//-------------------------------------------- Constructeurs - destructeur
    DataContainer(const DataContainer&) = delete;
    // Mode d'emploi :
    // Empêche la copie accidentelle d'un conteneur possédant des pointeurs

    DataContainer();
    // Mode d'emploi :
    // Constructeur de la classe DataContainer

    ~DataContainer();
    // Mode d'emploi :
    // Destructeur de la classe DataContainer, détruit toutes les données possédées

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::map<std::string, Attribute*> allAttributes;
    std::map<std::string, Sensor*> allSensors;
    std::map<std::string, PrivateUser*> allUsers;
    std::map<std::string, AirCleaner*> allAirCleaners;
    std::map<std::string, Provider*> allProviders; 
    std::map<std::string, std::vector<Measurement*>> measurementsBySensor;
};

#endif // DATACONTAINER_H