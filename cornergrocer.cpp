#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>  // for std::transform



// Function to read the file and populate frequency map
void readFile(const std::string& filename, std::unordered_map<std::string, int>& frequencyMap) {
    std::ifstream file(filename);
    std::string item;

    if (!file) {
        std::cerr << "Error: File " << filename << " not found." << std::endl;
        return;
    }

    while (file >> item) {
        // Increment the frequency for each item found
        ++frequencyMap[item];
    }

    file.close();
}


// Function to handle menu option 1 (case-insensitive search)
void menuOptionOne(const std::unordered_map<std::string, int>& frequencyMap) {
    std::string item;
    std::cout << "Enter item you're looking for: ";
    std::cin >> item;

    // Convert user input to lowercase
    std::transform(item.begin(), item.end(), item.begin(), ::tolower);

    bool found = false;
    for (const auto& pair : frequencyMap) {
        std::string itemInMap = pair.first;
        // Convert each item in the map to lowercase
        std::transform(itemInMap.begin(), itemInMap.end(), itemInMap.begin(), ::tolower);

        if (itemInMap == item) {
            std::cout << "Frequency of " << pair.first << ": " << pair.second << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Item not found." << std::endl;
    }
}

// Function to handle menu option 2
void menuOptionTwo(const std::unordered_map<std::string, int>& frequencyMap) {
    if (frequencyMap.empty()) {
        std::cout << "No items found." << std::endl;
        return;
    }

    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// Function to handle menu option 3
void menuOptionThree(const std::unordered_map<std::string, int>& frequencyMap) {
    if (frequencyMap.empty()) {
        std::cout << "No items to display in histogram." << std::endl;
        return;
    }

    for (const auto& pair : frequencyMap) {
        std::cout << std::setw(15) << std::left << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::unordered_map<std::string, int> frequencyMap;
    std::string filename = "produceitem.txt";


    // Read file and populate frequency map
    readFile(filename, frequencyMap);

    int option;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Find frequency of an item\n";
        std::cout << "2. Print all items with frequencies\n";
        std::cout << "3. Print histogram of item frequencies\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an option (1/2/3/4): ";
        std::cin >> option;

        switch (option) {
        case 1:
            menuOptionOne(frequencyMap);
            break;
        case 2:
            menuOptionTwo(frequencyMap);
            break;
        case 3:
            menuOptionThree(frequencyMap);
            break;
        case 4:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    } while (option != 4);

    return 0;
}
