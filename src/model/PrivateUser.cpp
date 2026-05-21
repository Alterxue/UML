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
using namespace std;
#include <iostream>
#include <string>

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
    if (isFraudulent) {
        cout << "Utilisateur frauduleux, les points ne sont pas disponibles." << endl;
        return 0;
    }
    return points;
} //----- Fin de getPoints

const std::vector<Sensor*>& PrivateUser::getSensorsList() const
{
    return mySensors;
} //----- Fin de getSensorsList

bool PrivateUser::getIsFraudulent() const
{
    return isFraudulent;
} //----- Fin de getIsFraudulent

void PrivateUser::setIsFraudulent(bool isFraudulent)
{
    this->isFraudulent = isFraudulent;
} //----- Fin de setIsFraudulent

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