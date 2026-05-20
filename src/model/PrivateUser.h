/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <PrivateUser> (fichier PrivateUser.h) ----------------
#if ! defined ( PRIVATEUSER_H )
#define PRIVATEUSER_H


//--------------------------------------------------- Interfaces utilisées

#include "User.h"
#include <vector>

class Sensor;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateUser>
//
//
//------------------------------------------------------------------------

class PrivateUser : public User 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void incrementPoints(int pointsToAdd);

    void addSensor(Sensor* sensor);

    int getPoints() const;

    const std::vector<Sensor*>& getSensorsList() const;

//------------------------------------------------- Surcharge d'opérateurs
    PrivateUser & operator = ( const PrivateUser & unPrivateUser );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    PrivateUser (std::string userId, Role role);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateUser ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    int points;
    std::vector<Sensor*> sensorsList; // Liens non possédants vers les capteurs associés à l'utilisateur
//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // PRIVATEUSER_H