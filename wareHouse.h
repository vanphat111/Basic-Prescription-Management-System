// wareHouse.h
#pragma once

#include <iostream>
#include <string>
#include <fstream>

#define MAX_HASH_TABLE_SIZE  64

using std::cin;
using std::cout;
using std::endl;

struct medicInfo {
  std::string medicID;
  std::string medicName;
  double price;
  std::string unit;
};

struct hashNode {
  medicInfo data;
  hashNode* next = NULL;
};

// Khai bao ham (chua dinh nghia)
int hashFunc(std::string str);

class wareHouse {
  protected:
    hashNode* medicStorage[MAX_HASH_TABLE_SIZE];

    bool _insert(medicInfo info);
    void _print(hashNode* value);
    
  public:
    hashNode* _find(std::string ID);

    wareHouse();
    void insertMedic();
    void insertMedicFromFile();
    void save2File();
    bool delMedic(std::string ID);
    void findMedic(std::string ID);
    void updateMedic(std::string ID);
    void printTable();
};
