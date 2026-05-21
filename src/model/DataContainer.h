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
// Contiendra l'ensemble des Attributes, PrivateUSer, Sensors, AirCleaners
// et Providers
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


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    DataContainer();

    ~DataContainer();
    
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








// Contientra les données
// Lui qui fait la construction et la destruction de tout les objets de données

// Colections
// Attribute : map<string, Attribute*> (seulement 4 instances, string : attributeID)
// Sensors   : map<string, Sensor*> (string : sensorID)
// PrivateUsers     : map<string, PrivateUser*> (string : userID)
// AirCleaner: map<string,AirCleaner*> (accès par parcours)
// Provider  : map<string, Provider*> (string : providerID)

// PipeLine de chragement des données
// 1) attributes.csv  : pour les attributs qui dépendent de personne
// 2) sensors.csv     : création des censors, pas encore de mesures ni de proprio
// 3) user.csv        : On créé les privateUser, on cherche le ou les sensors qu'il possède puis user->addSensor(s), s->setOwner(user)
// 4) cleaner.csv     : On crée les aircleaners
// 5) provider.csv    : On créé les provider et on lui ajoute les cleaners qui vont bien

// 7) measurement.csv : pour chaque mesure on récupère le pointeur de l'attribut et du capteur, on crée le mesurement et on l'ajoute au sensore qui va bien

// Pipeline de destruction
// 1) User + Provider
// 2) AirCleaner
// 3) Sensors, les measurement seront détruits avec
// 4) Attribute