#include "UploadCommand.h"
#include <string>
#include <string.h>

using namespace std;

/**
 * this function checks if the we are done reading from the client
 * @param file_data
 * @param file_size
 * @return true if we are done reading the file, false if not
 */
bool check_done(char* file_data, long int file_size) {
    if (file_size < 4) {
        return false;
    }
    return file_data[file_size - 4] == 'd' && file_data[file_size - 3] == 'o' && file_data[file_size - 2] == 'n' && file_data[file_size - 1] == 'e';
}

/**
 * this function checks if a string is double.
 * @param s - the string
 * @return true if the string is double, false if not
 */
bool isNumber(const string& s)
{
    bool hasDigit = false;
    bool hasE = false;
    bool hasPoint = false;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            hasDigit = true;
        } else if (s[i] == 'e' || s[i] == 'E') {
            if (hasE || !hasDigit || i + 1 == s.size()) {
                return false;
            }
            hasE = true;
        } else if (s[i] == '.') {
            if (hasE || hasPoint) {
                return false;
            }
            hasPoint = true;
        } else if (s[i] == '+' || s[i] == '-') {
            if (i != 0 && s[i-1] != 'e' && s[i-1] != 'E') {
                return false;
            }
        } else {
            return false;
        }
    }
    return hasDigit;
}

/**
 * this function save the classified vector in the classifiedVectorList
 * @param dataVector - the string
 */
void UploadCommand::classifiedVector(const vector<char>& dataVector) {
    string line;
    vector<std::string> lines;
    for (auto c : dataVector) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        } else if (c == '\r'){
            continue;
        } else {
            line += c;
        }
    }
    // add the last line if there's no newline at the end of the file
    if (!line.empty()) {
        lines.push_back(line);
    }
    cout << lines.size() << endl;
    for (auto l : lines) {
        vector<double> numbers;
        istringstream iss(l);
        string word, typeVector;
        char *charWord;
        // while loop that each iteration will take one word separate by space.
        while (getline(iss, word, ',')) {
            // there is more than one string for the vector
            if (!typeVector.empty()) {
                // error
            }
            // char word point to the start of the word.
            charWord = &word[0];
            //check if the word is number.
            if (isNumber(charWord)) {
                //it is number
                numbers.push_back(stod(word));
            } else {
                //the string
                typeVector = word;
            }
        }
        // there is no classified string
        if (typeVector.empty()) {
            // error
        }
        if (!numbers.empty()) {
            pair<vector<double>, string> tempPair;
            tempPair.first = numbers;
            tempPair.second = typeVector;
            values->setClassifiedVectorList(&tempPair);
        }
    }
}

/**
 * this function save the un classified vector in the unClassifiedVectorList
 * @param dataVector - the string
 */
void UploadCommand::notClassifiedVector(const vector<char>& dataVector) {
    string line;
    vector<std::string> lines;
    for (auto c : dataVector) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        } else if (c == '\r'){
            continue;
        } else {
            line += c;
        }
    }
    // add the last line if there's no newline at the end of the file
    if (!line.empty()) {
        lines.push_back(line);
    }
    for (auto l : lines) {
        vector<double> numbers;
        istringstream iss(l);
        string word, typeVector;
        char *charWord;
        // while loop that each iteration will take one word separate by space.
        while (getline(iss, word, ',')) {
            // char word point to the start of the word.
            charWord = &word[0];
            //check if the word is number.
            if (isNumber(charWord)) {
                //it is number
                numbers.push_back(stod(word));
            } else {
                //the string
                typeVector = word;
                // error
            }
        }
        if (!numbers.empty()) {
            values->setNotClassifiedVectorList(&numbers);
        }
    }
}

/**
 * this function sends and receives message from the client.
 * every vector we get, we save.
 */
void UploadCommand::execute() {
    //the client socket
    char buffer[1024];
    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
    string trainString = "Please upload your local train CSV file.\n";
    string uploadComplete1String = "Upload complete.\nPlease upload your local test CSV file.\n";
    string uploadComplete2String = "Upload complete.\n";
    vector<string> classifiedStrings;
    vector<string> unclassifiedStrings;

    // reset vectors in values
    values->getClassifiedVectorList()->clear();
    values->getNotClassifiedVectorList()->clear();
    values->getAfterClassifingList()->clear();

    // send the train string to the client
    this->dio->writeInput(trainString);

    vector<char> file_data;
    string input;
    while (true) {
        // getting the input from the client
        input = this->dio->readInput();
        strcpy(buffer, input.c_str());
        if (check_done(buffer, input.size())) {
            // clean the buffer
            memset(buffer, 0, input.size());
            break;
        } else {
            //copy the buffer to the vector
            for (int i = 0; i < input.size() - 1; ++i) {
                file_data.push_back(buffer[i]);
            }
            memset(buffer, 0, input.size());
        }
    }
    // send the upload complete and the test string to the client
    this->dio->writeInput(uploadComplete1String);

    // save the classified the vector.
    classifiedVector(file_data);
    cout << "----------------------------------classified-----------------------------" << endl;
    for (int i = 0; i < values->getClassifiedVectorList()->size(); ++i) {
        for (int j = 0; j < values->getClassifiedVectorList()->at(i).first.size(); ++j) {
            cout << values->getClassifiedVectorList()->at(i).first.at(j) << " ";
        }
        cout << values->getClassifiedVectorList()->at(i).second << endl;
    }

    file_data.clear();
    while (true) {
        // getting the input from the client
        input = this->dio->readInput();
        strcpy(buffer, input.c_str());
        if (check_done(buffer, input.size())) {
            // clean the buffer
            memset(buffer, 0, input.size());
            break;
        } else {
            //copy the buffer to the vector
            for (int i = 0; i < input.size() - 1; ++i) {
                file_data.push_back(buffer[i]);
            }
            //file_data.insert(file_data.end(), buffer, buffer + input.size() - 1);
            memset(buffer, 0, input.size());
        }
    }
    //put the vectors in the Unclassified vector of values.
    notClassifiedVector(file_data);

    cout << "----------------------------------un classified-----------------------------" << endl;
    for (int i = 0; i < values->getNotClassifiedVectorList()->size(); ++i) {
        for (int j = 0; j < values->getNotClassifiedVectorList()->at(i).size(); ++j) {
            cout << values->getNotClassifiedVectorList()->at(i).at(j) << " ";
        }
        cout << endl;
    }

    // send the upload complete string to the client
    this->dio->writeInput(uploadComplete2String);
}

/**
 * this function returns the description of this command in the menu
 * @return the description of this command in the menu
 */
string UploadCommand::description() {
    return "1. upload an unclassified csv data file\n";
}

/**
 * the constructor of UploadCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 * @param dio - pointer to DefaultIO object
 */
UploadCommand::UploadCommand(int socket, Values *valuesCopy, DefaultIO *dio) {
    values = valuesCopy;
    valuesCopy->setSocket(socket);
    this->dio = dio;
}