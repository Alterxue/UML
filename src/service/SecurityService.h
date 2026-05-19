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

#include <ctime>
#include <list>
#include <string>

#include "../model/User.h"

using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <SecurityService>
//
// Provides core security functions for fraud detection, sensor validation,
// and data integrity management in the AirWatcher system.
//
//------------------------------------------------------------------------


class SecurityService
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // Core Fraud Detection Algorithm
    // Verifies if a specific sensor (usually private) produces reliable data
    // Returns true if sensor is reliable, false if fraudulent/faulty
    static bool checkSensorReliability(User user, string sensorID);

    // Batch Fraud Detection
    // Identifies all malicious private users providing false data
    // Returns list of fraudulent users
    static list<User> detectFraudulentUsers(User user);

    // Data Corruption Removal
    // Marks corrupted data as invalid and excludes from future calculations
    // Prevents pollution of statistical analysis
    static void removeCorruptedData(User user);

    // System Initialization
    // Performs secure database initialization or admin reset
    // Restores security baseline and clears corrupted states
    static void initializeDatabase(User user);

//-------------------------------------------- Constructeurs - destructeur

    SecurityService ( );

    virtual ~SecurityService ( );
    
};


#endif // SECURITYSERVICE_H
