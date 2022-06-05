#include "WriteRead.h"
#include "InfoToSave.h"
#include <ios>
#include <list>

SaveTOFile::SaveTOFile(std::list<InfoToSave> save) {
    ListToSave = save;
    Save.open(src, std::ios::binary); 
    for (InfoToSave i : ListToSave) {
        Save.write((char*) &i, sizeof(i));
    }
}

SaveTOFile::SaveTOFile(InfoToSave save) {
    Save.open(src, std::ios::binary | std::ios::app);
    Save.write((char *) &save, sizeof(InfoToSave));
}

SaveTOFile::~SaveTOFile() {
    Save.close();
}

LoadFromFile::LoadFromFile() {
    Load.open(src,std::ios::binary);
    InfoToSave tmp;
    while (Load.read((char *) &tmp, sizeof(InfoToSave))) {
        LoadList.push_back(tmp);
    }
}

std::list<InfoToSave> LoadFromFile::GetList() {
    return LoadList;
}

LoadFromFile::~LoadFromFile() {
    Load.close();
}