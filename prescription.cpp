// prescription.cpp
#include "prescription.h"

void prescription::_add2List(prescriptionNode* data) {
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

prescriptionNode* prescription::_find(std::string ID) {
  prescriptionNode* tmp;
  tmp = first;
  while (tmp != NULL) {
    if (tmp->data.prescriptionID == ID) return tmp;
    tmp = tmp->next;
  }

  return NULL;
}

void prescription::_printMedicList(prescriptionHeader& data) {
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
    cout << "  " << count << ". ID:       " << tmp->data.medicID << endl;
    cout << "     Ten:      " << tmp->data.medicName << endl;
    cout << "     Gia:      " << tmp->data.price << endl;
    cout << "     So luong: " << tmp->data.total << endl;
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

bool prescription::_removeNode(prescriptionHeader& _prescriptionHeader, std::string _medicID) {
  prescriptionData* current = _prescriptionHeader.header;
  if (current == NULL)  return false;
  
  if (current->data.medicID == _medicID) {
    _prescriptionHeader.header = current->next;
    delete current;
    return true;
  }

  while (current->next != NULL) {
    if (current->next->data.medicID == _medicID) {
      prescriptionData* nodeDel = current->next;
      current->next = nodeDel->next;
      delete nodeDel;
      return true;
    }
    current = current->next;
  }
  return false;
}

prescription::prescription(wareHouse& _wareHouse) : mainWareHouse(_wareHouse) {

}

void prescription::newPrescription() {
  prescriptionNode* change = new prescriptionNode;
  cout << "Nhap ID don thuoc: ";
  getline(cin, change->data.prescriptionID);
  cout << "Nhap ten benh nhan: ";
  getline(cin, change->data.patientName);

  _add2List(change);
}

void prescription::printPrescription(std::string ID) {
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

void prescription::addMedic2Prescription(std::string ID) {
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

bool prescription::removeMedic(std::string ID) {
  prescriptionNode* pres = _find(ID);
  if (pres == NULL) {
      cout << "[Loi] Khong tim thay don thuoc " << ID << endl;
      return false;
  }

  cout << "\n--- THONG TIN DON THUOC (Truoc khi xoa) ---" << endl;
  cout << "ID Don thuoc: " << pres->data.prescriptionID << endl;
  cout << "Benh nhan:   " << pres->data.patientName << endl;
  cout << "--- Danh sach thuoc: ---" << endl;
  _printMedicList(pres->data);

  if (pres == NULL) {
    cout << "Don thuoc rong, khong co gi de xoa." << endl;
    return false;
  }

  std::string delID;
  cout << "Nhap ID thuoc can xoa: ";
  cin >> delID;
  if (_removeNode(pres->data, delID)) {
    cout << "==> Da xoa thuoc co ID " << delID << " khoi don." << endl;
    return true;
  }
  else {
    cout << "==> [Loi] Khong tim thay thuoc co ID " << delID << " trong don nay." << endl;
    return false;
  }
}

void prescription::save2File() {
  std::string fileLocation;
  cout << "Nhap dia chi file [./data/presData.txt]: ";
  getline(cin, fileLocation);
  cin.ignore();
  if (fileLocation == "") fileLocation = "data/presData.txt";

  std::ofstream file(fileLocation);
  if (!file.is_open()) {
    cout << "[LOI] Khong mo duoc file!!\n";
    return;
  }

}