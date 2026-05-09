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

#include "Attribute.h"
#include "Sensor.h"
#include "User.h"
#include "AirCleaner.h"
#include "Provider.h"
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
    void addAttribute(const Attribute*);
    // Mode d'emploi : 
    // Ajoute un attribut de mesure à la collection

    void addSensor(const Sensor*);
    // Mode d'emploi :
    // Ajoute un capteur à la collection

    void addUser(const User*);
    // Mode d'emploi :
    // Ajoute un utilisateur à la collection

    void addAirCleaner(const AirCleaner*);
    // Mode d'emploi :
    // Ajoute un air cleaner à la collection

    void addProvider(const Provider*);
    // Mode d'emploi :
    // Ajoute un fournisseur à la collection

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    DataContainer();
    
//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::map<std::string, Attribute*> allAttributes;
    std::map<std::string, Sensor*> allSensors;
    std::map<std::string, User*> allUsers;
    std::vector<AirCleaner*> allAirCleaners;
    std::map<std::string, Provider*> allProviders; 
};

#endif // DATACONTAINER_H








// Contientra les données
// Lui qui fait la construction et la destruction de tout les objets de données

// Colections
// Attribute : map<string, Attribute*> (seulement 4 instances, string : attributeID)
// Sensors   : map<string, Sensor*> (string : sensorID)
// Users     : map<string, User*> (string : userID)
// AirCleaner: vector<AirCleaner*> (accès par parcours)
// Provider  : map<string, Provider*> (string : providerID)

// PipeLine de chragement des données
// 1) attributes.csv  : pour les attributs qui dépendent de personne
// 2) sensors.csv     : création des censors, pas encore de mesures ni de proprio
// 3) user.csv        : On créé les privateUser, on cherche le ou les sensors qu'il possède puis user->addSensor(s), s->setOwner(user)
// 4) provider.csv    : On créé les provider
// 5) cleaner.csv     : On crée les aircleaners et on ajoute au provider correspondant
// 7) measurement.csv : pour chaque mesure on récupère le pointeur de l'attribut et du capteur, on crée le mesurement et on l'ajoute au sensore qui va bien

// Pipeline de destruction
// 1) User + Provider
// 2) AirCleaner
// 3) Sensors, les measurement seront détruits avec
// 4) Attribute