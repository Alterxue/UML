#include "dao/CSVDataManager.h"
#include "model/DataContainer.h"
#include "service/AirWatcherSystem.h"
#include "model/Role.h"
#include "model/GovernmentAgency.h"

#include <iostream>
#include <string>




int main(){

    AirWatcherSystem Application = new AirWatcherSystem();
    DataContainer dataContainer = new DataContainer();
    CSVDataManager dataManager = new CSVDataManager();

    bool login = false;
    do{
    cout << "Bienvenue dans AirWatcherSystem !" << endl;
    cout << "Veuillez vous connecter pour accéder au système." << endl;
    cout << "Vous êtes un : " << endl;
    cout << "1. Utilisateur privé" << endl;
    cout << "2. Fournisseur" << endl;
    cout << "3. Agence gouvernementale" << endl;
    
    int roleChoice;
    cin >> roleChoice;
    
    string userID;
    cout << "Entrez votre ID : ";
    cin >> userID;

    if (roleChoice == 1) {
        PrivateUser privateUser = Application.getAuthenticateService().loginPrivate(userID);
    } else if (roleChoice == 2) {
        Provider provider = Application.getAuthenticateService().loginProvider(userID);
    } else if (roleChoice == 3) {
        GovernmentAgency governmentAgency = Application.getAuthenticateService().loginGovernmentAgency(userID);
    }
    }while(!login);



    int choice;
    do {
        cout << "-- Menu principal AirWatcher --" << endl;
        cout << "1. Analyser un capteur" << endl;
        cout << "2. Calculer la qualité de l'air" << endl;
        cout << "3. Comparer des capteurs" << endl;
        cout << "4. Estimer la qualité de l'air" << endl;
        cout << "5. Menu spécial" << endl;
        cout << "6. Quitter" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                // Logic to display nearby sensors
                break;
            case 2:
                // Logic to display measurements of a sensor
                break;
            case 3:
                // Logic for provider to manage sensors
                break;
            case 4:
                // Logic for government agency to manage the system
                break;
            case 5:
                if (roleChoice == 1) {
                    int particularChoice;
                    do {
                    cout << "-- MENU PARTICULIER --" << endl;
                    cout << "6. Voir mes points" << endl;
                    cout << "7. Voir mes capteurs" << endl;
                    cout << "8. Ajouter un capteur" << endl;
                    cout << "11. Retour au menu principal" << endl;
                    } while(particularChoice != 11);
                } else if (roleChoice == 2) {
                    // Logic for provider menu
                } else if (roleChoice == 3) {
                    
                }
                break;
            case 6:
                cout << "Merci d'avoir utilisé AirWatcherSystem !" << endl;
                break;
            default:
                cout << "Choix invalide, veuillez réessayer."<<endl;}
    } while (choice != 6);

}