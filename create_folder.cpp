#include <iostream>
#include <filesystem>
using namespace std;
int main() {
    filesystem::path dirPath = "myfolder";  // Specify folder name

    // Check if the folder already exists
    if (!filesystem::exists(dirPath)) {
        // Create the folder
        if (filesystem::create_directory(dirPath)) {
            cout << "Directory created successfully!" << endl;
        } else {
            cout << "Failed to create directory." << endl;
        }
    } else {
        cout << "Directory already exists!" << endl;
    }

    return 0;
}
