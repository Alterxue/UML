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

//------------------------------------------------------ Include personnel
#include "Sensor.h"
#include "PrivateUser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const std::vector<Measurement*>& Sensor::getMeasurements() const
{
    return this->myMeasurements;
} //----- Fin de getMeasurements

bool Sensor::getReliability() const
{
    return this->isReliable;
} //----- Fin de getReliability

double Sensor::getLattitude() const
{
    return this->lattitude;
} //----- Fin de getLattitude

double Sensor::getLongitude() const
{
    return this->longitude;
} //----- Fin de getLongitude

string Sensor::getSensorID() const
{
    return this->sensorID;
} //----- Fin de getSensorID

void Sensor::setReliability(bool reliability)
{
    this->isReliable = reliability;
} //----- Fin de setReliability

void Sensor::setOwner(PrivateUser* a_owner)
{
    owner = a_owner;
} //----- Fin de setOwner

void Sensor::addMeasurement(Measurement* measure)
{
    if (measure != nullptr) {
        myMeasurements.push_back(measure);
    }
} //----- Fin de addMeasurement

void Sensor::removeMeasurement(Measurement* measure)
{
    for (vector<Measurement*>::iterator it = myMeasurements.begin(); it != myMeasurements.end(); ++it) {
        if (*it == measure) {
            myMeasurements.erase(it);
            break;
        }
    }
} //----- Fin de removeMeasurement

double Sensor::calculateDistance(double userLatitude, double userLongitude) const
{
    // Formule de Haversine (précision sphérique)
    const double PI = acos(-1.0);
    const double EARTH_RADIUS_KM = 6371.0; // Rayon moyen de la Terre
    // 1. Conversion de toutes les coordonnées en radians
    double lat1_rad = this->lattitude * PI / 180.0;
    double lon1_rad = this->longitude * PI / 180.0;
    double lat2_rad = userLatitude * PI / 180.0;
    double lon2_rad = userLongitude * PI / 180.0;
    // 2. Différences en radians
    double dLat = lat2_rad - lat1_rad;
    double dLon = lon2_rad - lon1_rad;
    // 3. Formule trigonométrique de Haversine
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(dLon / 2.0) * sin(dLon / 2.0);
               
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // 4. Distance finale en kilomètres
    return EARTH_RADIUS_KM * c;
} //----- FIn de calculateDistance

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor(string a_sensorID, double a_lattitude, double a_longitude) : sensorID(a_sensorID), lattitude(a_lattitude), longitude(a_longitude)
{
    owner = nullptr;
    isReliable = true;
    #ifdef MAP
        cout << "Appel au constructeur de <Sensor>" << endl;
    #endif
} //----- Fin de Sensor

Sensor::~Sensor ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <Sensor>" << endl;
    #endif
} //----- Fin de ~Sensor

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
