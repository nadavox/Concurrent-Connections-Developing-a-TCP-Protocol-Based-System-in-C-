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
 * @param dataVector - vector that contain all the string from the file
 */
string UploadCommand::classifiedVector(const vector<char>& dataVector) {
    // the size of the first and the second vector.
    unsigned long sizeFirst, sizeSecond;
    // the row we will add to the vector
    string line;
    // vector that contain all the rows
    vector<std::string> lines;
    // for loop that create the rows
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
    // for loop that go for each row and make it to a vector.
    for (auto l : lines) {
        vector<double> numbers;
        istringstream iss(l);
        string word, typeVector;
        char *charWord;
        // while loop that each iteration will take one word separate by space.
        while (getline(iss, word, ',')) {
            // there is more than one string for the vector
            if (!typeVector.empty()) {
                return "invalid input";
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
            return "invalid input";
        }
        // check that the list is not empty.
        if (!numbers.empty()) {
            // if it is the first value
            if (values->getClassifiedVectorList()->empty()) {
                //save the first size.
                sizeFirst = numbers.size();
                pair<vector<double>, string> tempPair;
                tempPair.first = numbers;
                tempPair.second = typeVector;
                //add him to the vector
                values->setClassifiedVectorList(&tempPair);
            }
                // if it is the second value
            else if (values->getClassifiedVectorList()->size() == 1) {
                //save the second size.
                sizeSecond = numbers.size();
                pair<vector<double>, string> tempPair;
                tempPair.first = numbers;
                tempPair.second = typeVector;
                //add him to the vector
                values->setClassifiedVectorList(&tempPair);
                // if the sizes are not equal not good.
                if (sizeFirst != sizeSecond) {
                    values->getClassifiedVectorList()->clear();
                    return "invalid input";
                }
                // the others vector
            } else {
                // if there is a vector that have different size is not good.
                if (numbers.size() == sizeFirst) {
                    // save the vector
                    pair<vector<double>, string> tempPair;
                    tempPair.first = numbers;
                    tempPair.second = typeVector;
                    //add him to the vector
                    values->setClassifiedVectorList(&tempPair);
                } else {
                    values->getClassifiedVectorList()->clear();
                    return "invalid input";
                }
            }
        }
    }
    return "valid";
}

/**
 * this function save the un classified vector in the unClassifiedVectorList
 * @param dataVector - the string
 */
string UploadCommand::notClassifiedVector(const vector<char>& dataVector) {
    unsigned long size_vector_classfied = values->getClassifiedVectorList()->at(0).first.size();
    // the size of the first and the second vector.
    unsigned long sizeFirst, sizeSecond;
    // the row we will add to the vector
    string line;
    // vector that contain all the rows
    vector<std::string> lines;
    // for loop that create the rows
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
    // for loop that go for each row and make it to a vector.
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
                values->getNotClassifiedVectorList()->clear();
                return "invalid input";
            }
        }
        if (!numbers.empty()) {
            if (size_vector_classfied == numbers.size()) {
                if (values->getNotClassifiedVectorList()->empty()) {
                    sizeFirst = numbers.size();
                } else if (values->getNotClassifiedVectorList()->size() == 1) {
                    sizeSecond = numbers.size();
                    if (sizeSecond != sizeFirst) {
                        values->getNotClassifiedVectorList()->clear();
                        return "invalid input";
                    }
                } else {
                    if (numbers.size() != sizeFirst) {
                        values->getNotClassifiedVectorList()->clear();
                        return "invalid input";
                    }
                }
                values->setNotClassifiedVectorList(&numbers);
            } else {
                values->getNotClassifiedVectorList()->clear();
                return "invalid input";
            }
        }
    }
    return "invalid";
}

/**
 * this function reset all the vectors.
 * @param values - the vector obkect to reset the vectors
 */
void reset_vectors(Values *values) {
    values->getClassifiedVectorList()->clear();
    values->getNotClassifiedVectorList()->clear();
    values->getAfterClassifingList()->clear();
}

/**
 * this function check if the input is valid. true for valid. false for invalid.
 * @param output - the string to check
 * @param values - the vector obkect to reset the vectors
 */
bool UploadCommand::check_input_is_invalid(const string& output, Values *values) {
    if (output == "invalid input") {
        // send the invalid input string to the client
        this->dio->writeInput(output);
        // read from client that finish to write the error message
        this->dio->readInput();
        reset_vectors(values);
        return false;
    }
    return true;
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
    reset_vectors(values);

    // send the train string to the client
    this->dio->writeInput(trainString);

    vector<char> file_data;
    string input;
    while (true) {
        // getting the input from the client
        input = this->dio->readInput();
        // exit the function. the client lost connection
        if (input == "Error") {
            reset_vectors(values);
            return;
        }
        strcpy(buffer, input.c_str());
        if (check_done(buffer, input.size())) {
            // clean the buffer
            memset(buffer, 0, input.size());
            break;
        } else {
            //copy the buffer to the vector
            for (int i = 0; i < input.size(); ++i) {
                file_data.push_back(buffer[i]);
            }
            memset(buffer, 0, input.size());
        }
    }

    // save the classified the vector.
    string output = classifiedVector(file_data);
    // if the input is invalid the file not good.
    if (!check_input_is_invalid(output, values)) {
        return;
    }
    // send the upload complete and the test string to the client
    this->dio->writeInput(uploadComplete1String);
    file_data.clear();
    while (true) {
        // getting the input from the client
        input = this->dio->readInput();
        // exit the function. the client lost connection
        if (input == "Error") {
            reset_vectors(values);
            return;
        }
        strcpy(buffer, input.c_str());
        if (check_done(buffer, input.size())) {
            // clean the buffer
            memset(buffer, 0, input.size());
            break;
        } else {
            //copy the buffer to the vector
            for (int i = 0; i < input.size(); ++i) {
                file_data.push_back(buffer[i]);
            }
            memset(buffer, 0, input.size());
        }
    }

    //put the vectors in the Unclassified vector of values.
    output = notClassifiedVector(file_data);
    // if the input is invalid the file not good.
    if (!check_input_is_invalid(output, values)) {
        return;
    }

    // send the upload complete string to the client
    this->dio->writeInput(uploadComplete2String);
    this->dio->readInput();
    // exit the function. the client lost connection
    if (input == "Error") {
        reset_vectors(values);
        return;
    }
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
    valuesCopy->setClientSocket(socket);
    this->dio = dio;
}