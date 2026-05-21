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
#include <string>
#include <vector>

#include "User.h"

class AirCleaner;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//------------------------------------------------------------------------
// Rôle de la classe <Provider>
// Un Provider est un utilisateur qui fournit des AirCleaners. 
// Il peut en ajouter à sa liste de Cleaners associés et les consulter.
//------------------------------------------------------------------------

class Provider : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void addCleaners( AirCleaner * cleaner);
    // Mode d'emploi :
    // Ajoute un AirCleaner à la liste des Cleaners associés au Provider.

    const std::vector<AirCleaner*>& getMyCleaners() const;
    // Mode d'emploi :
    // Retourne la liste des AirCleaners associés au Provider.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Provider (std::string userID, Role role);
    // Mode d'emploi :
    // Construit un Provider avec un userID et un rôle.
    
    ~Provider ( );
    // Mode d'emploi :
    // Destructeur de la classe Provider.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    // AirCleaners rattachés au fournisseur, sans transfert de propriété.
    std::vector<AirCleaner*> myCleaners;
};

//-------------------------------- Autres définitions dépendantes de <Provider>

#endif // PROVIDER_H