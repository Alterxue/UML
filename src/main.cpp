#include "dao/CSVDataManager.h"
#include "model/DataContainer.h"
#include "service/AirWatcherSystem.h"
#include "service/DataService.h"
#include "service/StatisticsService.h"
#include "service/SecurityService.h"
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
    bool quitApplication = false;

    // Charger toutes les données du CSV data manager avant tout test de connexion
    DataService::initializeDataContainer(&dataContainer);
    DataService::reloadAllData();

    cout << "Données chargées depuis les fichiers CSV." << endl;
    cout << dataContainer.getAllSensors().size() << " capteurs chargés." << endl;
    cout << dataContainer.getAllUsers().size() << " utilisateurs chargés." << endl;
    cout << dataContainer.getAllAirCleaners().size() << " air cleaners chargés." << endl;
    cout << dataContainer.getAllProviders().size() << " fournisseurs chargés." << endl;
    cout << DataService::getAllMeasurements().size() << " mesures chargées." << endl;

    cout << "Bienvenue dans AirWatcherSystem !" << endl;
    cout << endl;

    while (!quitApplication) {
        bool login = false;
        int roleChoice;
        do {
            cout << "Veuillez vous connecter pour accéder au système." << endl;
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
                    cout << "ID invalide pour l'agence gouvernementale, veuillez réessayer." << endl;
                }
            }
        } while(!login && !quitApplication);

        if (quitApplication) {
            break;
        }

        bool logoutRequested = false;
        int choice;
        do {
            cout << "-- Menu principal AirWatcher --" << endl;
            cout << "1. Analyser un capteur" << endl;
            cout << "2. Calculer la qualité de l'air dans une zone à un instant donné" << endl;
            cout << "3. Calculer la qualité de l'air dans une zone sur une période donnée" << endl;
            cout << "4. Comparer des capteurs par similarité" << endl;
            cout << "5. Calculer la qualité de l'air globale à une position et date données" << endl;
            cout << "6. Consulter les purificateurs" << endl;
            cout << "7. Menu spécial" << endl;
            cout << "8. Se déconnecter" << endl;
            cout << "9. Quitter" << endl;
            cout << "Votre choix : ";
            cin >> choice;

        switch (choice) {
            case 1:
            {
                cout << "Choisissez un capteur a analyser (ID) : ";
                string sensorID;
                cin >> sensorID;

                DateTime startTime;
                DateTime endTime;
                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                    break;
                }
                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                    break;
                }

                TimeRange period(startTime, endTime);
                string report = StatisticsService::analyzeSensorData(sensorID, period);
                cout << report << endl;
                break;
            }
            case 2:
            {
                User* currentUser = Application.getCurrentUser();
                if (currentUser == nullptr) {
                    cout << "Utilisateur non initialise." << endl;
                    break;
                }

                double lat = 0.0;
                double lon = 0.0;
                double radius = 0.0;
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> lon;
                cout << "Rayon (km): ";
                cin >> radius;

                DateTime time;
                if (!readDateTime("Date (YYYY-MM-DD HH:MM:SS): ", time)) {
                    break;
                }

                double aqi = StatisticsService::calculateAreaMean(lat, lon, radius, time);
                cout << "index ATMO calculé: " << aqi << endl;
                break;
            }
            case 3:
            {
                User* currentUser = Application.getCurrentUser();
                if (currentUser == nullptr) {
                    cout << "Utilisateur non initialise." << endl;
                    break;
                }

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
                double aqi = StatisticsService::calculateAreaMean(lat, lon, radius, period);
                cout << "index ATMO moyen sur la periode: " << aqi << endl;
                break;
            }
            case 4:
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
                vector<Sensor> similaires = StatisticsService::compareSensorsBySimilarity(targetSensorID, period);
                if (similaires.empty()) {
                    cout << "Aucun capteur similaire trouve." << endl;
                } else {
                    cout << "Top 3 capteurs les plus similaires:" << endl;
                    for (size_t i = 0; i < similaires.size() && i < 3; ++i) {
                        cout << i+1 << ". " << similaires[i].getSensorID() << endl;
                    }
                }
                break;
            }
            case 5:
            {
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

                double aqi = StatisticsService::calculateAirQuality(lat, lon, time);
                cout << "index ATMO global: " << aqi << endl;
                break;
            }
            case 6:
            {
                vector<AirCleaner*> cleaners = DataService::getAllAirCleaners();
                if (cleaners.empty()) {
                    cout << "Aucun purificateur disponible." << endl;
                    break;
                }

                cout << "Liste des purificateurs :" << endl;
                for (const auto* cleaner : cleaners) {
                    if (cleaner == nullptr) {
                        continue;
                    }

                    Provider* provider = cleaner->getProvider();
                    TimeRange workingPeriod = cleaner->getWorkingPeriod();

                    cout << "- " << cleaner->getAirCleanerID()
                         << " | position=(" << cleaner->getLattitude() << ", " << cleaner->getLongitude() << ")"
                         << " | debut=" << formatDateTime(workingPeriod.getStart())
                         << " | fin=" << formatDateTime(workingPeriod.getEnd())
                         << " | fournisseur=";

                    if (provider != nullptr) {
                        cout << provider->getUserID();
                    } else {
                        cout << "non renseigne";
                    }
                    cout << endl;
                }
                break;
            }
            case 7:
            {
                User* currentUser = Application.getCurrentUser();
                if (currentUser == nullptr) {
                    cout << "Utilisateur non initialise." << endl;
                    break;
                }

                if (currentUser->getRole() == PRIVATE_USER) {
                    PrivateUser* privateUser = dataContainer.getPrivateUserByID(currentUser->getUserID());
                    if (privateUser == nullptr) {
                        cout << "Utilisateur prive non trouve dans le DataContainer." << endl;
                        break;
                    }

                    int particularChoice;
                    do {
                        cout << "-- MENU PARTICULIER --" << endl;
                        cout << "6. Consulter mon solde de points" << endl;
                        cout << "7. Calculer la moyenne AQI de ma zone" << endl;
                        cout << "8. Comparer les capteurs du voisinage" << endl;
                        cout << "9. Saisir des mesures de capteur privé" << endl;
                        cout << "10. Voir l'historique de mes contributions" << endl;
                        cout << "11. Retour au menu principal" << endl;
                        cout << "Votre choix : ";
                        cin >> particularChoice;

                        switch (particularChoice) {
                            case 6:
                            {
                                if (privateUser->getIsFraudulent() == true) {
                                    cout << "ATTENTION : Vous êtes identifié comme un utilisateur frauduleux." << endl;
                                }
                                cout << "Votre solde de points : "
                                     << privateUser->getPoints() << " points" << endl;
                                break;
                            }
                            case 7:
                            {
                                double radius = 0.0;
                                cout << "Rayon (km) autour de votre position (ex: 5.0): ";
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
                                double aqi = StatisticsService::calculateUserZoneAQI(*currentUser, radius, period);
                                cout << "AQI moyen de votre zone: " << aqi << endl;
                                break;
                            }
                            case 8:
                            {
                                double radius = 0.0;
                                cout << "Rayon (km) autour de votre position (ex: 5.0): ";
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
                                map<string, vector<Sensor>> results = StatisticsService::compareNeighborhoodSensors(*currentUser, radius, period);
                                if (results.empty()) {
                                    cout << "Aucun capteur trouve dans le voisinage." << endl;
                                } else {
                                    cout << "Resultats de comparaison du voisinage :" << endl;
                                    for (const auto& entry : results) {
                                        cout << "Capteur cible: " << entry.first << endl;
                                        const auto& simil = entry.second;
                                        if (simil.empty()) {
                                            cout << "  Aucun capteur similaire trouve." << endl;
                                        } else {
                                            cout << "  Capteurs similaires :" << endl;
                                            for (const auto& s : simil) {
                                                cout << "   - " << s.getSensorID() << endl;
                                            }
                                        }
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

                                // Vérifier que le capteur appartient à l'utilisateur privé courant
                                bool belongsToUser = false;
                                const vector<Sensor*>& userSensors = privateUser->getSensorsList();
                                for (Sensor* s : userSensors) {
                                    if (s != nullptr && s->getSensorID() == sensor->getSensorID()) {
                                        belongsToUser = true;
                                        break;
                                    }
                                }

                                if (!belongsToUser) {
                                    cout << "Erreur: ce capteur n'appartient pas a votre compte." << endl;
                                    break;
                                }

                                DataService::addMeasurement(measureTime, sensor, attribute, value);
                                cout << "Mesure ajoutee." << endl;
                                break;
                            }
                            case 10:
                            {
                                cout << "Affichage de l'historique de vos contributions..." << endl;
                                vector<Measurement*> userHistory = DataService::getUserHistory(*privateUser);
                                if (userHistory.empty()) {
                                    cout << "Aucune contribution." << endl;
                                    break;
                                }
                                for (const auto& measurement : userHistory) {
                                    cout << "- " << measurement->getSensor()->getSensorID()
                                         << " | " << measurement->getAttribute()->getAttributeID()
                                         << " | " << measurement->getValue()
                                         << " | " << formatDateTime(measurement->getMeasureDate())
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
                } else if (currentUser->getRole() == PROVIDER) {
                    Provider* currentProvider = dataContainer.getProviderByID(currentUser->getUserID());
                    if (currentProvider == nullptr) {
                        cout << "Fournisseur non trouve dans le DataContainer." << endl;
                        break;
                    }

                    int particularChoice;
                    do {
                        cout << "-- MENU FOURNISSEUR --" << endl;
                        cout << "6. Voir l'impact d'un cleaner" << endl;
                        cout << "7. Comparer les capteurs par similarité" << endl;
                        cout << "8. Analyser le rayon de purification" << endl;
                        cout << "9. Consulter les statistiques de zone" << endl;
                        cout << "10. Retour au menu principal" << endl;  
                        cout << "Votre choix : ";
                        cin >> particularChoice;                      
                        switch (particularChoice) {
                            case 6:
                            {
                                const vector<AirCleaner*>& cleaners = currentProvider->getMyCleaners();
                                if (cleaners.empty()) {
                                    cout << "Aucun cleaner associe a votre compte." << endl;
                                    break;
                                }

                                cout << "Vos cleaners :" << endl;
                                for (const auto* cleaner : cleaners) {
                                    if (cleaner != nullptr) {
                                        cout << "- " << cleaner->getAirCleanerID() << endl;
                                    }
                                }

                                string cleanerID;
                                cout << "ID du cleaner a analyser : ";
                                cin >> cleanerID;

                                DateTime startTime;
                                DateTime endTime;
                                if (!readDateTime("Debut (YYYY-MM-DD HH:MM:SS): ", startTime)) {
                                    break;
                                }
                                if (!readDateTime("Fin (YYYY-MM-DD HH:MM:SS): ", endTime)) {
                                    break;
                                }

                                TimeRange period(startTime, endTime);
                                double impact = StatisticsService::viewCleanerImpact(*currentProvider, cleanerID, period);
                                cout << "Impact du cleaner : " << impact << endl;
                                break;
                            }
                            case 7:
                            {
                                string targetSensorID;
                                cout << "ID du capteur cible : ";
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
                                vector<Sensor> similaires = StatisticsService::compareSensorsBySimilarity(targetSensorID, period);
                                if (similaires.empty()) {
                                    cout << "Aucun capteur similaire trouve." << endl;
                                } else {
                                    cout << "Capteurs similaires :" << endl;
                                    for (const auto& sensor : similaires) {
                                        cout << "- " << sensor.getSensorID() << endl;
                                    }
                                }
                                break;
                            }
                            case 8:
                            {
                                string cleanerID;
                                cout << "ID du cleaner a analyser : ";
                                cin >> cleanerID;

                                double rayon = StatisticsService::analyzeCleanerRadius(*currentUser, cleanerID);
                                cout << "Rayon de purification utile : " << rayon << " km" << endl;
                                break;
                            }
                            case 9:
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
                                string statistics = StatisticsService::getZoneStatistic(*currentUser, lat, lon, radius, period);
                                cout << statistics << endl;
                                break;
                            }
                            case 10:
                                break;
                            default:
                                cout << "Choix invalide, veuillez réessayer." << endl;
                            }
                    }while(particularChoice != 10);
                    
                } else if (currentUser->getRole() == GOVERNMENT_AGENCY) {
                    int particularChoice;
                    do {
                        cout << "-- MENU AGENCE GOUVERNEMENTALE --" << endl;
                        cout << "6. Vérifier si un capteur est défectueux" << endl;
                        cout << "7. Identifier les comportements frauduleux" << endl;
                        cout << "8. Recensement des capteurs et mesure des données corrompues" << endl;
                        cout << "9. Supprimer les données corrompues" << endl;
                        cout << "10. Retour au menu principal" << endl;
                        cout << "Votre choix : ";
                        cin >> particularChoice;
                        

                        switch (particularChoice) {
                            case 6:{
                                vector<Sensor*> allSensors = DataService::getAllSensors();
                                cout << "Capteurs disponibles :" << endl;
                                if (allSensors.empty()) {
                                    cout << "Aucun capteur trouvé." << endl;
                                } else {
                                    for (const auto& sensor : allSensors) {
                                        if (sensor == nullptr) {
                                            continue;
                                        }

                                        cout << "- " << sensor->getSensorID();
                                        PrivateUser* owner = sensor->getOwner();
                                        if (owner != nullptr) {
                                            cout << " (propriétaire : " << owner->getUserID() << ")";
                                        } else {
                                            cout << " (sans propriétaire)";
                                        }
                                        cout << endl;
                                    }
                                }

                                string targetSensorID;
                                cout << "ID du capteur à vérifier: ";
                                cin >> targetSensorID;
                                SecurityService::checkSensorReliability(*currentUser, targetSensorID);
                                break;}
                            case 7:{
                                vector<PrivateUser*> fraudulentUsers = SecurityService::detectFraudulentUsers(*currentUser);
                                if (fraudulentUsers.empty()) {
                                    cout << "Aucun utilisateur frauduleux détecté." << endl;
                                } else {
                                    cout << "Utilisateurs frauduleux détectés:" << endl;
                                    for (const auto& user : fraudulentUsers) {
                                        cout << "- " << user->getUserID() << endl;
                                    }
                                }
                                break;}
                            case 8:
                                SecurityService::showCorruptedData(*currentUser);
                                break;
                            case 9:
                                SecurityService::initializeDatabase(*currentUser);
                                break;
                            case 10:
                                break;
                            default:
                                cout << "Choix invalide, veuillez réessayer." << endl;
                            }  
                    } while(particularChoice != 10);
                }
                break;
            }
            case 8:
                Application.logout();
                logoutRequested = true;
                break;
            case 9:
                cout << "Merci d'avoir utilisé AirWatcherSystem !" << endl;
                quitApplication = true;
                break;
            default:
                cout << "Choix invalide, veuillez réessayer."<<endl;}
        } while (choice != 9 && !logoutRequested && !quitApplication);
    }

    DataService::saveAllData();
    
    return 0;
}