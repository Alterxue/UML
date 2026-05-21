/*************************************************************************
                           User  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <PrivateUser> (fichier PrivateUser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "PrivateUser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void PrivateUser::incrementPoints(int pointsToAdd)
{
    if (isFraudulent) {
        cout << "Utilisateur frauduleux, les points ne peuvent pas être incrémentés." << endl;
        return;
    }
    points += pointsToAdd;
} //----- Fin de incrementPoints

void PrivateUser::addSensor(Sensor* sensor)
{
    mySensors.push_back(sensor);
} //----- Fin de addSensor

int PrivateUser::getPoints() const
{
    return points;
} //----- Fin de getPoints

bool PrivateUser::getIsFraudulent() const
{
    return isFraudulent;
} //----- Fin de getIsFraudulent

void PrivateUser::setIsFraudulent(bool isFraudulent)
{
    this->isFraudulent = isFraudulent;
} //----- Fin de setIsFraudulent

const std::vector<Sensor*>& PrivateUser::getSensorsList() const
{
    return mySensors;
} //----- Fin de getSensorsList

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
PrivateUser::PrivateUser (string userID, Role role) : User(userID, role), points(0), isFraudulent(false)
{
    #ifdef MAP
        cout << "Appel au constructeur de <PrivateUser>" << endl;
    #endif
}

PrivateUser::~PrivateUser ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <PrivateUser>" << endl;
    #endif
} //----- Fin de ~PrivateUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées