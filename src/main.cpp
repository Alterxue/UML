#include "dao/CSVDataManager.h"
#include "model/DataContainer.h"
#include "service/AirWatcherSystem.h"
#include "model/Role.h"
#include "model/GovernmentAgency.h"

#include <iostream>
#include <string>




int main(){

    AirWatcherSystem * Application = new AirWatcherSystem();
    DataContainer * dataContainer = new DataContainer();
    CSVDataManager * dataManager = new CSVDataManager();

    bool login = false;
    cout << "Bienvenue dans AirWatcherSystem !" << endl;
    int roleChoice;
    do{
        cout << "Veuillez vous connecter pour accéder au système." << endl;
        cout << "Vous êtes un : " << endl;
        cout << "1. Utilisateur privé" << endl;
        cout << "2. Fournisseur" << endl;
        cout << "3. Agence gouvernementale" << endl;
        cin >> roleChoice;
    
        string userID;
        cout << "Entrez votre ID : ";
        cin >> userID;
        if (roleChoice == 1) {
            login = Application->getAuthenticateService().loginPrivate(userID);
            if (!login) {
                cout << "ID invalide, aucun utilisateur trouvé, veuillez réessayer." << endl;
            }
        } else if (roleChoice == 2) {
            login = Application->getAuthenticateService().loginProvider(userID);
            if (!login) {
                cout << "ID invalide, aucun fournisseur trouvé, veuillez réessayer." << endl;
            }
        } else if (roleChoice == 3) {
            login = Application->getAuthenticateService().loginGovernmentAgency(userID);
            if (!login) {
                cout << "ID invalide, aucune agence gouvernementale trouvée, veuillez réessayer." << endl;
            }
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
                        cout << "6. Consulter mon solde de points" << endl;
                        cout << "7. Calculer la moyenne AQI de ma zone" << endl;
                        cout << "8. Comparer les capteurs du voisinage" << endl;
                        cout << "9. Saisir des mesures de capteur privé" << endl;
                        cout << "10. Voir l'historique de mes contributions" << endl;
                        cout << "11. Retour au menu principal" << endl;

                        switch (particularChoice) {
                            case 6:
                                Application->getPrivateUser()->getPoints();
                                break;
                            case 7:
                                // Logic to calculate average AQI in user's area
                                break;
                            case 8:
                                // Logic to compare sensors in the neighborhood
                                break;
                            case 9:
                                // Logic to input sensor measurements
                                break;
                            case 10:
                                // Logic to consult contribution history
                                break;
                            case 11:
                                break;
                            default:
                                cout << "Choix invalide, veuillez réessayer." << endl;
                            }
                    }while(particularChoice != 11);
                } else if (roleChoice == 2) {
                    int particularChoice;
                    do {
                        cout << "-- MENU FOURNISSEUR --" << endl;
                        cout << "6. Voir l'impact d'un capteur" << endl;
                        cout << "7. Calculer la moyenne AQI d'une zone" << endl;
                        cout << "8. Comparer les capteurs par similarité" << endl;
                        cout << "9. Analyser le rayon de purification" << endl;
                        cout << "10. Consulter les statistiques de zone" << endl;
                        cout << "11. Retour au menu principal" << endl;
                        
                        switch (particularChoice) {
                            case 6:
                                // Logic to display the impact of a sensor
                                break;
                            case 7:
                                // Logic to calculate average AQI in a zone
                                break;
                            case 8:
                                // Logic to compare sensors by similarity
                                break;
                            case 9:
                                // Logic to analyze purification radius
                                break;
                            case 10:
                                // Logic to consult zone statistics
                                break;
                            case 11:
                                break;
                            default:
                                cout << "Choix invalide, veuillez réessayer." << endl;
                            }
                    }while(particularChoice != 11);
                    
                } else if (roleChoice == 3) {
                    int particularChoice;
                    do {
                        cout << "-- MENU AGENCE GOUVERNEMENTALE --" << endl;
                        cout << "6. Initialiser les bases de données" << endl;
                        cout << "7. Vérifier si un capteur est défectueux" << endl;
                        cout << "8. Identifier les comportements frauduleux" << endl;
                        cout << "9. Exclure les données corrompues" << endl;
                        cout << "10. Retour au menu principal" << endl;
                        

                        switch (particularChoice) {
                            case 6:
                                // Logic to display the impact of a sensor
                                break;
                            case 7:
                                // Logic to calculate average AQI in a zone
                                break;
                            case 8:
                                // Logic to compare sensors by similarity
                                break;
                            case 9:
                                // Logic to analyze purification radius
                                break;
                            case 10:
                                break;
                            default:
                                cout << "Choix invalide, veuillez réessayer." << endl;
                            }  
                    } while(particularChoice != 10);
                }
                break; 
            case 6:
                cout << "Merci d'avoir utilisé AirWatcherSystem !" << endl;
                break;
            default:
                cout << "Choix invalide, veuillez réessayer."<<endl;}
    } while (choice != 6);
}