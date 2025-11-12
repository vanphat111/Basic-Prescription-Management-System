// prescription.h
#pragma once

#include <iostream>
#include <string>
#include "wareHouse.h"

using std::cin;
using std::cout;
using std::endl;

struct medicTotal : public medicInfo {
  int total = 0;
};

struct prescriptionData {
  medicTotal data;
  prescriptionData* next = NULL;
};

struct prescriptionHeader {
  std::string prescriptionID;
  std::string patientName;
  prescriptionData* header = NULL;
};

struct prescriptionNode {
  prescriptionHeader data;
  prescriptionNode* next = NULL;
};

class prescription {
  protected:
    prescriptionNode* first = NULL;
    prescriptionNode* last = NULL;

    wareHouse& mainWareHouse;

    void _add2List(prescriptionNode* data);
    prescriptionNode* _find(std::string ID);
    void _printMedicList(prescriptionHeader& data);
    bool _removeNode(prescriptionHeader& _prescriptionHeader, std::string _medicID);

  public:
    prescription(wareHouse& _wareHouse);
    void newPrescription();
    void printPrescription(std::string ID);
    void addMedic2Prescription(std::string ID);
    bool removeMedic(std::string ID);
    void save2File();
};