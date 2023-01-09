#ifndef ADVANCEDPROGRAMINGPART3_FILEIO_H
#define ADVANCEDPROGRAMINGPART3_FILEIO_H

#include "DefaultIO.h"
#include <fstream>

class FileIO : public DefaultIO {
private:
    string readFilePath;
    string writeFilePath;
public:
    FileIO(string readFilePath, string writeFilePath);
    string readInput();
    void writeInput(string s);
};
#endif //ADVANCEDPROGRAMINGPART3_FILEIO_H
