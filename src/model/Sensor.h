/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( SENSOR_H )
#define SENSOR_H



//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>

#include "Measurement.h"
#include "User.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    std::vector<Measurement> getMeasurements() const;
    // Mode d'emploi :
    // Retourne la liste des mesures du capteur

    bool getReliability() const;
    // Mode d'emploi :
    // Retourne la fiabilité du capteur

    double getLattitude() const;
    // Mode d'emploi :
    // Retourne la lattitude du capteur

    double getLongitude() const;
    // Mode d'emploi :
    // Retourne la longitude du capteur

    std::string getSensorID() const;
    // Mode d'emploi :
    // Retourne l'ID du capteur

    void setReliability(bool reliability);
    // Mode d'emploi : 
    // Permet de marquer le capteur comme fiable ou non

    void setOwner(User* a_owner);
    // Mode d'emploi :
    // Affecte le PrivateUser au capteur

    void addMeasurement(const Measurement& measure);
    // Mode d'emploi :
    // Ajoute la maseaure à la liste des mesures du capteur

    int calculateDistance(double userLatitude, double userLongitude) const;
    // Mode d'emploi : 
    // Calcule la distance du capteur à une position donnée


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Sensor (std::string a_sensorId, double a_lattitude, double a_longitude);
    // Mode d'emploi :
    // Construction d'un capteur à partir de son ID et de sa position, met isReliable = true à la construction

    ~Sensor ();
    // Mode d'emploi :
    // Destructeur du capteur

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    std::string sensorID;
    double lattitude;
    double longitude;
    bool isReliable;
    User* owner;
    std::vector<Measurement> measurements;

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // SENSOR_H