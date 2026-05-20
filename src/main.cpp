#include "dao/CSVDataManager.h"
#include "model/DataContainer.h"
#include "service/AirWatcherSystem.h"
#include "service/DataService.h"
#include "model/Role.h"
#include "model/GovernmentAgency.h"

using namespace std;
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>

using DateTime = std::chrono::system_clock::time_point;

static bool parseDateTime(const string& input, DateTime& output)
{
    std::tm tm = {};
    std::istringstream stream(input);
    stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (stream.fail()) {
        return false;
    }
    output = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return true;
}

static bool readDateTime(const string& prompt, DateTime& output)
{
    cout << prompt;
    string input;
    getline(cin >> std::ws, input);
    if (!parseDateTime(input, output)) {
        cout << "Format invalide. Utilisez YYYY-MM-DD HH:MM:SS" << endl;
        return false;
    }
    return true;
}

static string formatDateTime(const DateTime& value)
{
    std::time_t t = std::chrono::system_clock::to_time_t(value);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int main(){
    AirWatcherSystem Application;
    DataContainer dataContainer;
    CSVDataManager dataManager;

    // Charger toutes les données du CSV data manager avant tout test de connexion
    dataManager.loadAttributes(dataContainer);
    dataManager.loadSensors(dataContainer);
    dataManager.loadUsers(dataContainer);
    dataManager.loadCleaners(dataContainer);
    dataManager.loadProviders(dataContainer);

    DataService::initializeDataContainer(&dataContainer);

    cout << "Données chargées depuis les fichiers CSV." << endl;
    cout << dataContainer.getAllSensors().size() << " capteurs chargés." << endl;
    cout << dataContainer.getAllUsers().size() << " utilisateurs chargés." << endl;
    cout << dataContainer.getAllAirCleaners().size() << " air cleaners chargés." << endl;
    cout << dataContainer.getAllProviders().size() << " fournisseurs chargés." << endl;



    cout << "" << endl;
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
            login = Application.setPrivateUser(dataContainer,userID);
            if (!login) {
                cout << "ID invalide, aucun utilisateur trouvé, veuillez réessayer." << endl;
            }
        } else if (roleChoice == 2) {
            login = Application.setProvider(dataContainer,userID);
            if (!login) {
                cout << "ID invalide, aucun fournisseur trouvé, veuillez réessayer." << endl;
            }
        } else if (roleChoice == 3) {
            login = Application.setGovernmentAgency(userID);
            if (!login){
                cout << "ID invalide, aucun agent gouvernemental trouvé, veuillez réessayer." << endl;
            }
        }
    } while(!login);

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
            {
                cout << "Choisissez un capteur a analyser (ID) : " << endl;
                string sensorID;
                cin >> sensorID;

                Sensor* sensor = dataContainer.getSensorByID(sensorID);
                User* currentUser = Application.getCurrentUser();
                if (sensor == nullptr) {
                    cout << "Capteur non trouve, veuillez reessayer." << endl;
                    break;
                }
                DateTime startTime;
                DateTime endTime;
                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                    break;
                }
                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                    break;
                }

                double radiusKm = 0.0;
                cout << "Rayon (km): ";
                cin >> radiusKm;

                double radiusMeters = radiusKm * 1000.0;
                TimeRange period(startTime, endTime);
                double aqi = StatisticsService::calculateLocalAQI(*currentUser, sensor->getLattitude(), sensor->getLongitude(), radiusMeters, period);
                cout << "AQI local: " << aqi << endl;
                break;
            }
            case 2:
            {
                User* currentUser = Application.getCurrentUser();
                double lat = 0.0;
                double lon = 0.0;
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> lon;

                DateTime time;
                if (!readDateTime("Date (YYYY-MM-DD HH:MM:SS): ", time)) {
                    break;
                }

                double aqi = StatisticsService::calculateAirQuality(*currentUser, lat, lon, time);
                cout << "AQI calcule: " << aqi << endl;
                break;
            }
            case 3:
            {
                User* currentUser = Application.getCurrentUser();
                if (currentUser == nullptr) {
                    cout << "Utilisateur non initialise." << endl;
                    break;
                }

                string targetSensorID;
                cout << "ID du capteur cible: ";
                cin >> targetSensorID;

                DateTime startTime;
                DateTime endTime;
                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                    break;
                }
                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                    break;
                }

                TimeRange period(startTime, endTime);
                vector<Sensor> similaires = StatisticsService::compareSensorsBySimilarity(*currentUser, targetSensorID, period);
                if (similaires.empty()) {
                    cout << "Aucun capteur similaire trouve." << endl;
                } else {
                    cout << "Capteurs similaires:" << endl;
                    for (const auto& sensor : similaires) {
                        cout << "- " << sensor.getSensorID() << endl;
                    }
                }
                break;
            }
            case 4:
            {
                double lat = 0.0;
                double lon = 0.0;
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> lon;

                double aqi = StatisticsService::estimateAirQuality(lat, lon);
                cout << "AQI estime: " << aqi << endl;
                break;
            }
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
                        cin >> particularChoice;

                        switch (particularChoice) {
                            case 6:
                                cout << "Votre solde de points : "
                                     << Application.getCurrentPrivateUser()->getPoints() << " points" << endl;
                                break;
                            case 7:
                            {
                                double lat = 0.0;
                                double lon = 0.0;
                                double radius = 0.0;
                                cout << "Latitude: ";
                                cin >> lat;
                                cout << "Longitude: ";
                                cin >> lon;
                                cout << "Rayon (km): ";
                                cin >> radius;

                                DateTime startTime;
                                DateTime endTime;
                                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                                    break;
                                }
                                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                                    break;
                                }

                                TimeRange period(startTime, endTime);
                                double aqi = StatisticsService::calculateAreaMean(*Application.getCurrentPrivateUser(), lat, lon, radius, period);
                                cout << "AQI moyen: " << aqi << endl;
                                break;
                            }
                            case 8:
                            {
                                string targetSensorID;
                                cout << "ID du capteur cible: ";
                                cin >> targetSensorID;

                                DateTime startTime;
                                DateTime endTime;
                                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                                    break;
                                }
                                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                                    break;
                                }

                                TimeRange period(startTime, endTime);
                                vector<Sensor> similaires = StatisticsService::compareSensorsBySimilarity(*Application.getCurrentPrivateUser(), targetSensorID, period);
                                if (similaires.empty()) {
                                    cout << "Aucun capteur similaire trouve." << endl;
                                } else {
                                    cout << "Capteurs similaires:" << endl;
                                    for (const auto& sensor : similaires) {
                                        cout << "- " << sensor.getSensorID() << endl;
                                    }
                                }
                                break;
                            }
                            case 9:
                            {
                                string sensorID;
                                string attributeID;
                                double value = 0.0;

                                cout << "ID du capteur: ";
                                cin >> sensorID;
                                cout << "ID de l'attribut (ex: O3, NO2, SO2, PM10): ";
                                cin >> attributeID;
                                cout << "Valeur: ";
                                cin >> value;

                                DateTime measureTime;
                                if (!readDateTime("Date (YYYY-MM-DD HH:MM:SS): ", measureTime)) {
                                    break;
                                }

                                Sensor* sensor = dataContainer.getSensorByID(sensorID);
                                Attribute* attribute = dataContainer.getAttributeByID(attributeID);
                                if (sensor == nullptr || attribute == nullptr) {
                                    cout << "Capteur ou attribut invalide." << endl;
                                    break;
                                }

                                DataService::addMeasurement(measureTime, sensor, attribute, value);
                                cout << "Mesure ajoutee." << endl;
                                break;
                            }
                            case 10:
                            {
                                cout << "Affichage de l'historique de vos contributions..." << endl;
                                list<Measurement> userHistory = DataService::getUserHistory(*Application.getCurrentPrivateUser());
                                if (userHistory.empty()) {
                                    cout << "Aucune contribution." << endl;
                                    break;
                                }
                                for (const auto& measurement : userHistory) {
                                    cout << "- " << measurement.getSensor()->getSensorID()
                                         << " | " << measurement.getAttribute()->getAttributeID()
                                         << " | " << measurement.getValue()
                                         << " | " << formatDateTime(measurement.getMeasureDate())
                                         << endl;
                                }
                                break;
                            }
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
                        cin >> particularChoice;
                        

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
    
    return 0;
}