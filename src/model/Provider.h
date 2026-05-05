/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H



//--------------------------------------------------- Interfaces utilisées
#include "AirCleaner.h"
#include <string>
#include <list>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//
//------------------------------------------------------------------------

class Provider
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    std::list<AirCleaner> getMyCleaners(std::list<AirCleaner> cleaners) const;
//------------------------------------------------- Surcharge d'opérateurs
    Provider & operator = ( const Provider & unProvider );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Provider (std::string providerID);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Provider ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string providerID;

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // PROVIDER_H