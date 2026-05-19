/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<Measurement> Sensor::getMeasurements() const
{
    return this->measurements;
} //----- Fin de getMeasurements

string Sensor::getSensorID() const
{
    return this->sensorID;
} //----- Fin de getSensorID

void Sensor::setReliability(bool reliability)
{
    this->isReliable = reliability;
} //----- Fin de setReliability

void Sensor::setOwner(User* a_owner)
{
    owner = a_owner;
} //----- Fin de setOwner

void Sensor::addMeasurement(const Measurement& measure)
{
    measurements.push_back(measure);
} //----- Fin de addMeasurement

int Sensor::calculateDistance(double userLatitude, double userLongitude) const
{
    double latDiff = userLatitude - this->lattitude;
    double lonDiff = userLongitude - this->longitude;
    return static_cast<int>(sqrt(latDiff * latDiff + lonDiff * lonDiff) * 111000); 
} //----- FIn de calculateDistance

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor (const Sensor & unSensor)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Sensor>" << endl;
#endif
} //----- Fin de Sensor (constructeur de copie)


Sensor::Sensor(string a_sensorID, double a_lattitude, double a_longitude) : sensorID(a_sensorID), lattitude(a_lattitude), longitude(a_longitude)
// Algorithme
{
    owner = nullptr;
    isReliable = true;
    #ifdef MAP
        cout << "Appel au constructeur de <Sensor>" << endl;
    #endif
} //----- Fin de Sensor


Sensor::~Sensor ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
