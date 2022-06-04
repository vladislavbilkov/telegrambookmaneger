#ifndef WRITEREAD
#define WRITEREAD

#include "InfoToSave.h"
#include <fstream>
#include <list>
#include <string>

const std::string src =  "data/data.dat";

class SaveTOFile
{
    std::ofstream Save;
    std::list<InfoToSave> ListToSave;
    public:
    SaveTOFile(std::list<InfoToSave> save);
    SaveTOFile(InfoToSave save);
    ~SaveTOFile();
};

class LoadFromFile
{
    std::ifstream Load;
    std::list<InfoToSave> LoadList;
    public:
    LoadFromFile();
    ~LoadFromFile();
    std::list<InfoToSave> GetList();
};

#endif