#include <iostream>
#include <string>
using namespace std;


struct StudySpot {
    string location;
    int timeLeft; 
    bool hasPower;
    string noiseLevel;
    string sharedBy;
    bool isClaimed;
};


struct User {
    string username;
    int karmaPoints;
};


const int MAX_SPOTS = 500;
StudySpot spots[MAX_SPOTS];
int spotCount = 0;
User currentUser;


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void showMenu() {
    cout << "\n=== StudySwap ===\n";
    cout << "1. Find a spot\n";
    cout << "2. Share your spot\n";
    cout << "3. View your karma\n";
    cout << "4. Exit\n";
    cout << "Choose option (1-4): ";
}


void shareSpot() {
    clearScreen();
    if (spotCount >= MAX_SPOTS) {
        cout << "No more spots can be added!\n";
        return;
    }
    
    StudySpot newSpot;
    
    cout << "\n=== Share Your Study Spot ===\n";
    cout << "Choose location:\n";
    cout << "1. Library Floor 1\n";
    cout << "2. Library Floor 2\n";
    cout << "3. Study Room 1 (right next to reception desk)\n";
    cout << "4.Study room 2(right next to  water dispenser)\n";
    
    int choice;
    cout << "Enter choice (1-4): ";
    cin >> choice;
    
    switch(choice) {
        case 1:
		newSpot.location = "Library Floor 1"; 
		break;
        case 2:
        		 newSpot.location = "Library Floor 2"; 
		break;
        case 3:
        		 newSpot.location = "Study Room 1 (right next to reception desk)";
		break;
        case 4: 
        		newSpot.location = "Study room 2(right next to  water dispenser)";
		break;
        default:
        		 newSpot.location = "Any group study table";
    }
    
    cout << "How many minutes until you leave? ";
    cin >> newSpot.timeLeft;
    
    cout << "Does spot have power outlet? (1 for Yes, 0 for No): ";
    cin >> newSpot.hasPower;
    
    cout << "Noise Level (1-Quiet, 2-Moderate, 3-Busy): ";
    cin >> choice;
    switch(choice) {
        case 1: 
        		newSpot.noiseLevel = "Quiet"; 
		break;
        case 2: 
        		newSpot.noiseLevel = "Moderate"; 
		break;
        case 3: 
        		newSpot.noiseLevel = "Busy";
		break;
        default:
        		 newSpot.noiseLevel = "Unknown";
    }
    
    newSpot.sharedBy = currentUser.username;
    newSpot.isClaimed = false;
    
    spots[spotCount++] = newSpot;
    currentUser.karmaPoints += 10;
    
    cout << "\nSpot shared successfully! +10 karma points!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


void findSpot() {
    clearScreen();
    cout << "\n=== Available Study Spots ===\n";
    
    if (spotCount == 0) {
        cout << "No spots available right now!\n";
    } else {
        for (int i = 0; i < spotCount; i++) {
            if (!spots[i].isClaimed) {
                cout << "\nSpot " << i + 1 << ":\n";
                cout << "Location: " << spots[i].location << "\n";
                cout << "Time left: " << spots[i].timeLeft << " minutes\n";
                cout << "Power outlet: " << (spots[i].hasPower ? "Yes" : "No") << "\n";
                cout << "Noise level: " << spots[i].noiseLevel << "\n";
                cout << "Shared by: " << spots[i].sharedBy << "\n";
            }
        }
        
        cout << "\nWould you like to claim a spot? (Enter spot number or 0 to go back): ";
        int choice;
        cin >> choice;
        
        if (choice > 0 && choice <= spotCount) {
            spots[choice-1].isClaimed = true;
            cout << "\nSpot claimed successfully! Head over there now!\n";
            currentUser.karmaPoints += 2;
        }
    }
    
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


void viewKarma() {
    clearScreen();
    cout << "\n=== Your Karma Status ===\n";
    cout << "Username: " << currentUser.username << "\n";
    cout << "Karma Points: " << currentUser.karmaPoints << "\n";
    
    string status;
    if (currentUser.karmaPoints < 50) {
        status = "Rookie Sharer";
    } else if (currentUser.karmaPoints < 200) {
        status = "Helpful Hunter";
    } else {
        status = "Spot Master";
    }
    
    cout << "Current Status: " << status << "\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    cout << "Welcome to StudySwap!\n";
    cout << "Enter your username: ";
    getline(cin, currentUser.username);
    currentUser.karmaPoints = 0;
    
    int choice;
    bool running = true;
    
    while (running) {
        clearScreen();
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                findSpot();
                break;
            case 2:
                shareSpot();
                break;
            case 3:
                viewKarma();
                break;
            case 4:
                running = false;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    
    cout << "\nThanks for using StudySwap!\n";
    return 0;
}