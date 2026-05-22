/*************************************************************************
                           StatisticsService  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <SecurityService> (fichier SecurityService.h) ----------------
#if ! defined ( SECURITYSERVICE_H )
#define SECURITYSERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include <list>
#include <string>

#include "../model/User.h"
#include "../model/PrivateUser.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <SecurityService>
// Apporte des fonctions de sécurité pour la détection de fraudes, la validation des capteurs,
// et la gestion de l'intégrité des données dans le système AirWatcher
//------------------------------------------------------------------------

class SecurityService
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    static bool checkSensorReliability(const User& user, string sensorID);
    // Mode d'emploi :
    // - Seule une agence gouvernementale peut vérifier la fiabilité d'un capteur
    // - Analyse les mesures du capteur sur une période donnée pour détecter des anomalies
    // - Compare les mesures du capteur avec des les mesures de capteurs fiables voisins
    // - Si trop de mesures sont considérées comme anormales, marque le capteur non fiable
    
    static vector<PrivateUser*> detectFraudulentUsers(const User& user);
    // Mode d'emploi :
    // - Seule une agence gouvernementale peut détecter les utilisateurs frauduleux
    // - Renvoie un vecteur de pointeurs vers les utilisateurs privés marqués comme frauduleux, 
    // basé sur la fiabilité de leurs capteurs associés

    static void showCorruptedData(const User& user);
    // Mode d'emploi :
    // - Seule une agence gouvernementale peut supprimer les données corrompues
    // - Récupère tous les capteurs marqués comme non fiables et marque leurs mesures comme invalides
    // - suppression douce : les données restent dans le système mais sont exclues des calculs et analyses futures


    // System Initialization
    // Performs secure database initialization or admin reset
    // Restores security baseline and clears corrupted states
    static void initializeDatabase(const User& user);

//-------------------------------------------- Constructeurs - destructeur

    SecurityService ( );

    virtual ~SecurityService ( );
    
};


#endif // SECURITYSERVICE_H
