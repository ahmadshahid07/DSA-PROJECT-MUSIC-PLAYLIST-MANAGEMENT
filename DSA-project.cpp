#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Song {
    string title;
    string artist;
    int duration; 
    Song* next;
};
class PlaylistManager {
private:
    Song* head; 
public:
    PlaylistManager() {
        head = nullptr;
    }
    void addSong(string title, string artist, int duration) {
        Song* newSong = new Song();
        newSong->title = title;
        newSong->artist = artist;
        newSong->duration = duration;
        newSong->next = nullptr;

        if (head == nullptr) {
            head = newSong;
        } else {
            Song* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newSong;
        }
        cout << "Song added to the playlist." << endl;
    }
    void displayPlaylist() {
        if (head == nullptr) {
            cout << "The playlist is empty." << endl;
            return;
        }
        Song* temp = head;
        cout << "Playlist: " << endl;
        while (temp != nullptr) {
            cout << "Title: " << temp->title << ", Artist: " << temp->artist << ", Duration: " << temp->duration << " seconds" << endl;
            temp = temp->next;
        }
    }
    void deleteSong(string title) {
        if (head == nullptr) {
            cout << "The playlist is empty. Cannot delete." << endl;
            return;
        }

        if (head->title == title) {
            Song* temp = head;
            head = head->next;
            delete temp;
            cout << "Song '" << title << "' deleted." << endl;
            return;
        }

        Song* current = head;
        Song* previous = nullptr;

        while (current != nullptr && current->title != title) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Song not found in the playlist." << endl;
            return;
        }

        previous->next = current->next;
        delete current;
        cout << "Song '" << title << "' deleted." << endl;
    }
    void savePlaylistToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        Song* temp = head;
        while (temp != nullptr) {
            file << temp->title << endl;
            file << temp->artist << endl;
            file << temp->duration << endl;
            temp = temp->next;
        }

        file.close();
        cout << "Playlist saved to file." << endl;
    }
    void loadPlaylistFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string title, artist;
        int duration;

        while (getline(file, title)) {
            getline(file, artist);
            file >> duration;
            file.ignore(); 
            addSong(title, artist, duration);
        }

        file.close();
        cout << "Playlist loaded from file." << endl;
    }
    ~PlaylistManager() {
        Song* current = head;
        while (current != nullptr) {
            Song* next = current->next;
            delete current;
            current = next;
        }
    }
};
int main() {
    PlaylistManager manager;
    int choice;
    string title, artist, filename = "playlist.txt";
    int duration;

    manager.loadPlaylistFromFile(filename);  // Load existing playlist from file

    do {
        cout << "\nMenu:\n1. Add Song\n2. Display Playlist\n3. Delete Song\n4. Save Playlist\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter artist: ";
            getline(cin, artist);
            cout << "Enter duration (in seconds): ";
            cin >> duration;
            manager.addSong(title, artist, duration);
            break;
        case 2:
            manager.displayPlaylist();
            break;
        case 3:
            cout << "Enter song title to delete: ";
            cin.ignore();
            getline(cin, title);
            manager.deleteSong(title);
            break;
        case 4:
            manager.savePlaylistToFile(filename);
            break;
        case 5:
            manager.savePlaylistToFile(filename); 
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
