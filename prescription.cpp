// prescription.cpp

#pragma once

#include <iostream>
#include <string>
#include "wareHouse.cpp"

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

    void _add2List(prescriptionNode* data) {
      if (first == NULL and last == NULL) {
        first = data;
        last = data;
        last->next = NULL;
      }

      else {
        data->next = first;
        first = data;
      }

      cout << "Them don thuoc co ID " << data->data.prescriptionID << " thanh cong.\n";
    } 

    prescriptionNode* _find(std::string ID) {
      prescriptionNode* tmp;
      tmp = first;
      while (tmp != NULL) {
        if (tmp->data.prescriptionID == ID) return tmp;
        tmp = tmp->next;
      }

      return NULL;
    }

    void _printMedicList(prescriptionHeader& data) {
      if (data.header == NULL) {
        cout << "(Don thuoc nay chua co thuoc)" << endl;
        cout << "=============================" << endl;
        return;
      }

      prescriptionData* tmp;
      tmp = data.header;
      int count = 1;
      float totalPrice = 0.0;
      while (tmp != NULL) {
        cout << "  " << count << ". ID:    " << tmp->data.medicID << endl;
        cout << "     Ten:   " << tmp->data.medicName << endl;
        cout << "     Gia:   " << tmp->data.price << endl;
        cout << "     So luong:   " << tmp->data.total << endl;
        cout << "     Don vi:   " << tmp->data.unit << endl;
        cout << "     -----" << endl;
      
        totalPrice += tmp->data.total * tmp->data.price;
        count++;
        tmp = tmp->next;
      }

      cout << "-----------------------------" << endl;
      cout << "TONG TIEN: " << totalPrice << endl;
      cout << "=============================" << endl;
    }

    bool _removeNode(prescriptionHeader& _prescriptionHeader, std::string _medicID) {
      prescriptionData* tmp;
      if (_prescriptionHeader.header->data.medicID == _medicID) {
        tmp = _prescriptionHeader.header;
        
      }
      tmp = _prescriptionHeader.header;
      while (tmp != NULL) {
        if (tmp->data.medicID == _medicID) {

        }
      }

    }

  public:
    prescription(wareHouse& _wareHouse) : mainWareHouse(_wareHouse) {

    }

    void newPrescription() {
      prescriptionNode* change = new prescriptionNode;
      cout << "Nhap ID don thuoc: ";
      getline(cin, change->data.prescriptionID);
      cout << "Nhap ten benh nhan: ";
      getline(cin, change->data.patientName);

      _add2List(change);
    }

    void printPrescription(std::string ID) {
      prescriptionNode* out;
      out = _find(ID);
      if (out == NULL) {
        cout << "[Loi] Khong tim thay don thuoc co ID " << ID << endl;
        return;
      }
      cout << "\n--- THONG TIN DON THUOC ---" << endl;
      cout << "=============================" << endl;
      cout << "ID Don thuoc: " << out->data.prescriptionID << endl;
      cout << "Benh nhan:   " << out->data.patientName << endl;
      cout << "--- Danh sach thuoc: ---" << endl;
      _printMedicList(out->data);
    }

    void addMedic2Prescription(std::string ID) {
      prescriptionNode* pres = _find(ID);
      if (pres == NULL) {
        cout << "[Loi] Khong tim thay don thuoc " << ID << endl;
        return;
      }
      std::string _medicID;
      cout << "Nhap ID thuoc can them vao don: ";
      cin >> _medicID;

      hashNode* medicNode = mainWareHouse._find(_medicID);
      if (medicNode == NULL) {
        cout << "[Loi] Kho khong co thuoc voi ID: " << _medicID << endl;
        return;
      }

      medicInfo info = medicNode->data;
      int total;
      cout << "Da tim thay: " << info.medicName << " (" << info.unit << ")" << endl;
      cout << "Nhap so luong: ";
      cin >> total;
      cin.ignore();

      prescriptionData* newMed = new prescriptionData;
      newMed->data.medicID = info.medicID;
      newMed->data.medicName = info.medicName;
      newMed->data.price = info.price;
      newMed->data.unit = info.unit;
      newMed->data.total = total;

      newMed->next = pres->data.header;
      pres->data.header = newMed;

      cout << "Da them " << total << " " << info.unit << " " << info.medicName << " vao don thuoc." << endl;
    }

    void removeMedic(std::string ID) {
      printPrescription(ID);
      std::string delID;
      cout << "\nChon ID thuoc can xoa: ";
      cin >> delID;

    } 
};

int main() {
  wareHouse wh;
  wh.insertMedicFromFile();
  wh.printTable();
  prescription pre1(wh);
  pre1.newPrescription();
  pre1.addMedic2Prescription("1");
  pre1.printPrescription("1");
}