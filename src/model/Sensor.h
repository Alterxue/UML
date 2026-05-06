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
    std::string getSensorID() const;

    void setReliability(bool reliability);

    int calculateDistance(double userLatitude, double userLongitude) const;


//------------------------------------------------- Surcharge d'opérateurs
    Sensor & operator = ( const Sensor & unSensor );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Sensor (const Sensor & unSensor);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Sensor (std::string sensorId, std::string lattitude, std::string longitude, bool isReliable);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    std::string sensorID;
    double lattitude;
    double longitude;
    bool isReliable;
    vector<Measurement> measurements;

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // SENSOR_H