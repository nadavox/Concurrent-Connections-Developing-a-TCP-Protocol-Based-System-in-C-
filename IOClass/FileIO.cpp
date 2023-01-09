#include "FileIO.h"

FileIO::FileIO(std::string readFilePath, std::string writeFilePath) {
    this->readFilePath = readFilePath;
    this->writeFilePath = writeFilePath;
}

/**
 * this function reads from file
 */
string FileIO::readInput() {
    string s = "";
    ifstream inputFile;
    // open the file, doesn't matter if it relative or not.
    inputFile.open(readFilePath);
    // could not open the file
    if (!inputFile)
    {
        perror("Error with opening the file");
        return s;
    }
    getline(inputFile, s);
    return s;
}

/**
 * this function writes to file
 * @param s - the string
 */
void FileIO::writeInput(string s) {
    // Open the file
    ofstream outputFile(writeFilePath);

    // Check if the file was opened successfully
    if (!outputFile) {
        perror("Error with opening the file");
        return;
    }

    // Write the string to the file
    outputFile << s;

    // Close the file
    outputFile.close();
}