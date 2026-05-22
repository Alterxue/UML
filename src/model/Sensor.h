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

class PrivateUser;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
// Un capteur est un dispositif de mesure qui peut être associé à un 
// utilisateur (son propriétaire) et qui peut prendre des mesures.
//------------------------------------------------------------------------

class Sensor 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    const std::vector<Measurement*>& getMeasurements() const;
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

    void setOwner(PrivateUser* a_owner);
    // Mode d'emploi :
    // Affecte le PrivateUser au capteur

    void addMeasurement(Measurement* measure);
    // Mode d'emploi :
    // Ajoute la measure à la liste des mesures du capteur

    void removeMeasurement(Measurement* measure);
    // Mode d'emploi :
    // Retire une mesure de la liste du capteur sans la détruire

    double calculateDistance(double userLatitude, double userLongitude) const;
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
    // Lien non possédant vers le propriétaire du capteur.
    PrivateUser* owner;
    // Mesures rattachées à ce capteur, mais détruites par DataContainer.
    std::vector<Measurement*> myMeasurements;

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H