#include <iostream>
#include <string>

using namespace std;

const string MEDIA_AUDIO_CASSETTE = "audio cassette";

struct MusicWork {
    string mediaType;
    string title;
    string performerName;
    double playingTime;
    int numberOfTracks;
    double price;
};

struct MusicStackNode {
    MusicWork musicData;
    MusicStackNode *nextNode;
};

void pushToMusicStack(MusicStackNode *&topNode, MusicWork newMusicWork) {
    MusicStackNode *newNode = new MusicStackNode;
    newNode->musicData = newMusicWork;
    newNode->nextNode = topNode;
    topNode = newNode;
}

void printMusicStack(MusicStackNode *topNode) {
    MusicStackNode *currentNode = topNode;

    while (currentNode != nullptr) {
        cout << "Title: " << currentNode->musicData.title << endl;
        cout << "Performer: " << currentNode->musicData.performerName << endl;
        cout << "Media type: " << currentNode->musicData.mediaType << endl;
        cout << "Playing time: " << currentNode->musicData.playingTime << endl;
        cout << "Number of tracks: " << currentNode->musicData.numberOfTracks << endl;
        cout << "Price: " << currentNode->musicData.price << endl;
        cout << endl;

        currentNode = currentNode->nextNode;
    }
}

double calculateTotalPlayingTimeForPerformer(MusicStackNode *topNode, string requiredPerformerName) {
    double totalPlayingTime = 0;
    MusicStackNode *currentNode = topNode;

    while (currentNode != nullptr) {
        if (currentNode->musicData.performerName == requiredPerformerName) {
            totalPlayingTime += currentNode->musicData.playingTime;
        }

        currentNode = currentNode->nextNode;
    }

    return totalPlayingTime;
}

double calculateAveragePriceOfAudioCassettes(MusicStackNode *topNode) {
    double totalPrice = 0;
    int numberOfAudioCassettes = 0;
    MusicStackNode *currentNode = topNode;

    while (currentNode != nullptr) {
        if (currentNode->musicData.mediaType == MEDIA_AUDIO_CASSETTE) {
            totalPrice += currentNode->musicData.price;
            numberOfAudioCassettes++;
        }

        currentNode = currentNode->nextNode;
    }

    if (numberOfAudioCassettes == 0) {
        return 0;
    }

    return totalPrice / numberOfAudioCassettes;
}

void deleteEntireMusicStack(MusicStackNode *&topNode) {
    while (topNode != nullptr) {
        MusicStackNode *nodeToDelete = topNode;
        topNode = topNode->nextNode;
        delete nodeToDelete;
    }
}

int main() {
    MusicStackNode *topNode = nullptr;
    int numberOfMusicWorks;
    string requiredPerformerName;

    cout << "Enter the number of music works: ";
    cin >> numberOfMusicWorks;
    cin.ignore();

    for (int musicWorkIndex = 0; musicWorkIndex < numberOfMusicWorks; musicWorkIndex++) {
        MusicWork newMusicWork;

        cout << "Enter media type: ";
        getline(cin, newMusicWork.mediaType);

        cout << "Enter title: ";
        getline(cin, newMusicWork.title);

        cout << "Enter performer name: ";
        getline(cin, newMusicWork.performerName);

        cout << "Enter playing time: ";
        cin >> newMusicWork.playingTime;

        cout << "Enter number of tracks: ";
        cin >> newMusicWork.numberOfTracks;

        cout << "Enter price: ";
        cin >> newMusicWork.price;
        cin.ignore();

        pushToMusicStack(topNode, newMusicWork);
    }

    cout << endl << "Stack content:" << endl;
    printMusicStack(topNode);

    cout << "Enter performer name for search: ";
    getline(cin, requiredPerformerName);

    cout << "Total playing time for performer: "
            << calculateTotalPlayingTimeForPerformer(topNode, requiredPerformerName) << endl;

    cout << "Average price of audio cassettes: "
            << calculateAveragePriceOfAudioCassettes(topNode) << endl;

    deleteEntireMusicStack(topNode);

    return 0;
}
