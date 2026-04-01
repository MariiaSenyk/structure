#include <iostream>
#include <string>

using namespace std;

const int maxOfCities = 100;

struct Team {
    string name;
    string city;
    int score;
};

struct TeamQueue {
    Team teamData;
    TeamQueue *nextNode;
};

void enqueueTeam(TeamQueue *&frontNode, TeamQueue *&rearNode, Team newTeam) {
    TeamQueue *newNode = new TeamQueue;
    newNode->teamData = newTeam;
    newNode->nextNode = nullptr;

    if (rearNode == nullptr) {
        frontNode = newNode;
        rearNode = newNode;
    } else {
        rearNode->nextNode = newNode;
        rearNode = newNode;
    }
}

bool isQueueEmpty(TeamQueue *frontNode) {
    return frontNode == nullptr;
}

Team removeTeam(TeamQueue *&frontNode, TeamQueue *&rearNode) {
    Team emptyTeam;
    emptyTeam.name = "";
    emptyTeam.city = "";
    emptyTeam.score = 0;

    if (isQueueEmpty(frontNode)) {
        return emptyTeam;
    }

    TeamQueue *nodeToDelete = frontNode;
    Team removedTeam = frontNode->teamData;
    frontNode = frontNode->nextNode;

    if (frontNode == nullptr) {
        rearNode = nullptr;
    }

    delete nodeToDelete;
    return removedTeam;
}

bool cityExists(string uniqueCityNames[], int numberOfUniqueCities, string cityNameToCheck) {
    for (int cityIndex = 0; cityIndex < numberOfUniqueCities; cityIndex++) {
        if (uniqueCityNames[cityIndex] == cityNameToCheck) {
            return true;
        }
    }

    return false;
}

void deleteQueue(TeamQueue *&frontNode, TeamQueue *&rearNode) {
    while (!isQueueEmpty(frontNode)) {
        removeTeam(frontNode, rearNode);
    }
}

int main() {
    TeamQueue *frontNode = nullptr;
    TeamQueue *rearNode = nullptr;

    int numberOfTeams;

    cout << "Enter the number of teams: ";
    cin >> numberOfTeams;
    cin.ignore();

    for (int teamIndex = 0; teamIndex < numberOfTeams; teamIndex++) {
        Team newTeam;

        cout << "Enter team name: ";
        getline(cin, newTeam.name);

        cout << "Enter city name: ";
        getline(cin, newTeam.city);

        cout << "Enter score: ";
        cin >> newTeam.score;
        cin.ignore();

        enqueueTeam(frontNode, rearNode, newTeam);
    }

    if (isQueueEmpty(frontNode)) {
        cout << "The queue is empty." << endl;
        return 0;
    }

    string uniqueCityNames[maxOfCities];
    int numberOfUniqueCities = 0;

    Team leaderTeam = frontNode->teamData;
    Team outsiderTeam = frontNode->teamData;

    TeamQueue *currentNode = frontNode;

    while (currentNode != nullptr) {
        Team currentTeam = currentNode->teamData;

        if (!cityExists(uniqueCityNames, numberOfUniqueCities, currentTeam.city)) {
            uniqueCityNames[numberOfUniqueCities] = currentTeam.city;
            numberOfUniqueCities++;
        }

        if (currentTeam.score > leaderTeam.score) {
            leaderTeam = currentTeam;
        }

        if (currentTeam.score < outsiderTeam.score) {
            outsiderTeam = currentTeam;
        }

        currentNode = currentNode->nextNode;
    }

    cout << endl << "List of unique cities:" << endl;
    for (int cityIndex = 0; cityIndex < numberOfUniqueCities; cityIndex++) {
        cout << uniqueCityNames[cityIndex] << endl;
    }

    cout << endl << "Leader of the competition:" << endl;
    cout << "Team name: " << leaderTeam.name << endl;
    cout << "City name: " << leaderTeam.city << endl;
    cout << "Score: " << leaderTeam.score << endl;

    cout << endl << "Outsider of the competition:" << endl;
    cout << "Team name: " << outsiderTeam.name << endl;
    cout << "City name: " << outsiderTeam.city << endl;
    cout << "Score: " << outsiderTeam.score << endl;

    deleteQueue(frontNode, rearNode);

    return 0;
}
