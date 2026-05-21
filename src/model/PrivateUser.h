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
#include <vector>

#include "User.h"

class Sensor;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateUser>
// Cette classe représente un utilisateur privé de l'application, qui peut 
// accumuler des points de récompense et être associé à des capteurs. 
// Elle hérite de la classe User et ajoute des fonctionnalités spécifiques 
// aux utilisateurs privés, telles que la gestion des points et le statut de fraude.
//------------------------------------------------------------------------

class PrivateUser : public User 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    bool incrementPoints(int pointsToAdd);
    // Mode d'emploi :
    // Permet d'ajouter des points à l'utilisateur privé, utilisés pour le système de récompense

    void addSensor(Sensor* sensor);
    // Mode d'emploi :
    // Permet d'associer un capteur à l'utilisateur privé

    int getPoints() const;
    // Mode d'emploi :
    // Permet de récupérer le nombre de points de l'utilisateur privé

    const std::vector<Sensor*>& getSensorsList() const;
    // Mode d'emploi :
    // Permet de récupérer la liste des capteurs associés à l'utilisateur privé

    bool getIsFraudulent() const;
    // Mode d'emploi :
    // Permet de savoir si l'utilisateur est marqué comme frauduleux ou non

    void setIsFraudulent(bool isFraudulent);
    // Mode d'emploi :
    // Permet de marquer l'utilisateur comme frauduleux ou non

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    PrivateUser (std::string userId, Role role);
    // Mode d'emploi :
    // Construction d'un utilisateur privé à partir de son ID et de son rôle, initialise les points à 0 et le statut de fraude à false

    ~PrivateUser ();
    // Mode d'emploi :
    // Destructeur de l'utilisateur privé 

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    int points;
    bool isFraudulent;
    // Capteurs rattachés à cet utilisateur, sans transfert de propriété.
    std::vector<Sensor*> mySensors;
//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // PRIVATEUSER_H