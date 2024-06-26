#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to check if a user exists in the system and return the user ID
int userExists(string username, string password) {
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);  // Find the second comma after the username
        if (pos1 == string::npos || pos2 == string::npos) {
            continue;  // Skip lines that don't have the correct format
        }
        string storedUsername = line.substr(0, pos1);
        string storedPassword = line.substr(pos1 + 1, pos2 - pos1 - 1);  // Extract password between commas
        string userIdStr = line.substr(pos2 + 1);  // Extract user ID after the second comma
        if (storedUsername == username && storedPassword == password) {
            userFile.close();
            return stoi(userIdStr);  // Convert user ID string to integer and return
        }
    }
    userFile.close();
    return -1;  // Return -1 if user not found
}

// Function to check the Uniqueness of new Username
bool checkUnique(string usernameCheck){
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        string storedUsername = line.substr(0, pos1);
        if (usernameCheck == storedUsername){
            return false;
        }
    }
    return true;
}

//Function to Create User
bool createUser(string username, string password, int userId) {
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        if (checkUnique(username)) {
            userFile << username << "," << password << "," << userId << "\n";
            userFile.close();
            // Create watch history file
            ofstream watchHistoryFile("WatchHistory/User_" + to_string(userId) + ".txt");
            if (watchHistoryFile.is_open()) {
                watchHistoryFile.close();
            } else {
                cerr << "Error: Unable to create watch history file.\n";
                return false;
            }
            // Create user reviews file
            ofstream userReviewsFile("UserReviews/User_" + to_string(userId) + ".txt");
            if (userReviewsFile.is_open()) {
                userReviewsFile.close();
            } else {
                cerr << "Error: Unable to create user reviews file.\n";
                return false;
            }

            return true;
        } else {
            cerr << "Error: Username is not unique.\n";
            userFile.close();
            return false;
        }
    } else {
        cerr << "Error: Unable to create or open users file.\n";
        return false;
    }
}

// Function to get last UserID
int getLastID(){
    string userIdStr = "0";
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);  // Find the second comma after the username
        if (pos1 == string::npos || pos2 == string::npos) {
            continue;  // Skip lines that don't have the correct format
        }
        string storedUsername = line.substr(0, pos1);
        string storedPassword = line.substr(pos1 + 1, pos2 - pos1 - 1);  // Extract password between commas
        userIdStr = line.substr(pos2 + 1);  // Extract user ID after the second comma
    }

    return stoi(userIdStr);
}

#endif
