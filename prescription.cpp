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

  cout << "✅ Them don thuoc co ID " << data->data.prescriptionID << " thanh cong.\n";
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
    cout << "⚠️  (Don thuoc nay chua co thuoc)" << endl;
    cout << "=============================" << endl;
    return;
  }

  prescriptionData* tmp;
  tmp = data.header;
  int count = 1;
  float totalPrice = 0.0;
  while (tmp != NULL) {
    cout << "  " << count << ". 🆔 ID:       " << tmp->data.medicID << endl;
    cout << "     🏷️  Ten:      " << tmp->data.medicName << endl;
    cout << "     💲 Gia:      " << tmp->data.price << endl;
    cout << "     🔢 So luong: " << tmp->data.total << endl;
    cout << "     📏 Don vi:   " << tmp->data.unit << endl;
    cout << "     -----" << endl;
  
    totalPrice += tmp->data.total * tmp->data.price;
    count++;
    tmp = tmp->next;
  }

  cout << "-----------------------------" << endl;
  cout << "💰 TONG TIEN: " << totalPrice << endl;
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
  cout << "🆔 Nhap ID don thuoc: ";
  getline(cin, change->data.prescriptionID);
  cout << "🧑‍⚕️ Nhap ten benh nhan: ";
  getline(cin, change->data.patientName);

  _add2List(change);
}

void prescription::printPrescription(std::string ID) {
  prescriptionNode* out;
  out = _find(ID);
  if (out == NULL) {
    cout << "❌ Khong tim thay don thuoc co ID " << ID << endl;
    return;
  }
  cout << "\n--- 📝 THONG TIN DON THUOC ---" << endl;
  cout << "=============================" << endl;
  cout << "🆔 ID Don thuoc: " << out->data.prescriptionID << endl;
  cout << "🧑‍⚕️ Benh nhan:   " << out->data.patientName << endl;
  cout << "--- 💊 Danh sach thuoc: ---" << endl;
  _printMedicList(out->data);
}

void prescription::addMedic2Prescription(std::string ID) {
  prescriptionNode* pres = _find(ID);
  if (pres == NULL) {
    cout << "❌ Khong tim thay don thuoc " << ID << endl;
    return;
  }
  std::string _medicID;
  cout << "🆔 Nhap ID thuoc can them vao don: ";
  cin >> _medicID;

  hashNode* medicNode = mainWareHouse._find(_medicID);
  if (medicNode == NULL) {
    cout << "❌ Kho khong co thuoc voi ID: " << _medicID << endl;
    return;
  }

  medicInfo info = medicNode->data;
  int total;
  cout << "✅ Da tim thay: " << info.medicName << " (" << info.unit << ")" << endl;
  cout << "🔢 Nhap so luong: ";
  cin >> total;

  prescriptionData* newMed = new prescriptionData;
  newMed->data.medicID = info.medicID;
  newMed->data.medicName = info.medicName;
  newMed->data.price = info.price;
  newMed->data.unit = info.unit;
  newMed->data.total = total;

  newMed->next = pres->data.header;
  pres->data.header = newMed;

  cout << "✨ Da them " << total << " " << info.unit << " " << info.medicName << " vao don thuoc." << endl;
}

bool prescription::removeMedic(std::string ID) {
  prescriptionNode* pres = _find(ID);
  if (pres == NULL) {
      cout << "❌ Khong tim thay don thuoc " << ID << endl;
      return false;
  }

  cout << "\n--- ℹ️  THONG TIN DON THUOC (Truoc khi xoa) ---" << endl;
  cout << "🆔 ID Don thuoc: " << pres->data.prescriptionID << endl;
  cout << "🧑‍⚕️ Benh nhan:   " << pres->data.patientName << endl;
  cout << "--- 💊 Danh sach thuoc: ---" << endl;
  _printMedicList(pres->data);

  if (pres->data.header == NULL) {
    cout << "⚠️  Don thuoc rong, khong co gi de xoa." << endl;
    return false;
  }

  std::string delID;
  cout << "🆔 Nhap ID thuoc can xoa: ";
  cin >> delID;
  if (_removeNode(pres->data, delID)) {
    cout << "✅ ==> Da xoa thuoc co ID " << delID << " khoi don." << endl;
    return true;
  }
  else {
    cout << "❌ ==> Khong tim thay thuoc co ID " << delID << " trong don nay." << endl;
    return false;
  }
}

void prescription::save2File() {
  std::string fileLocation;
  cout << "📂 Nhap dia chi file [./data/presData.txt]: ";
  getline(cin, fileLocation);

  if (fileLocation == "") fileLocation = "data/presData.txt";

  std::ofstream file(fileLocation);
  if (!file.is_open()) {
    cout << "❌ Khong mo duoc file!!\n";
    return;
  }
  
  cout << "📤 Bat dau luu..." << endl;
  int presCount = 0;
  int medCount = 0;

  prescriptionNode* pres_node = first;
  while (pres_node != NULL) {
    
    file << pres_node->data.prescriptionID << endl;
    file << pres_node->data.patientName << endl;
    
    prescriptionData* med_node = pres_node->data.header;
    while (med_node != NULL) {
      file << med_node->data.medicID << " " << med_node->data.total << endl;
      medCount++;
      med_node = med_node->next;
    }
    
    file << "END_MEDICS" << endl;
    
    presCount++;
    pres_node = pres_node->next;
  }
  
  file.close();
  cout << "🎉 Hoan tat! Da luu " << presCount << " don thuoc (" << medCount << " loai thuoc) vao file: ./" << fileLocation << endl;
}

void prescription::insertFromFile() {
  std::string fileLocation;
  cout << "📂 Nhap dia chi file de LOAD [./data/presData.txt]: ";


  getline(cin, fileLocation);

  if (fileLocation == "") fileLocation = "data/presData.txt";

  std::ifstream file(fileLocation);
  if (!file.is_open()) {
    cout << "❌ Khong mo duoc file de LOAD: " << fileLocation << endl;
    return;
  }

  cout << "📥 Bat dau load du lieu tu file..." << endl;
  int presCount = 0;
  int medCount = 0;

  std::string presID;
  while (getline(file, presID)) {
    if (presID.empty()) continue;
    prescriptionNode* pres_node = new prescriptionNode;
    pres_node->data.prescriptionID = presID;
    getline(file, pres_node->data.patientName);

    prescriptionData* last_med_node = NULL; 

    std::string medID;
    int total;
      while (file >> medID && medID != "END_MEDICS") {
        file >> total;
        hashNode* medicNode = mainWareHouse._find(medID);
          
        if (medicNode == NULL) {
          cout << "  ⚠️ Thuoc " << medID << " trong don " << presID << " khong con ton tai trong kho! Bo qua..." << endl;
          continue;
        }
        medicInfo info = medicNode->data;
        prescriptionData* med_node = new prescriptionData;

        med_node->data.medicID = info.medicID;
        med_node->data.medicName = info.medicName;
        med_node->data.price = info.price;
        med_node->data.unit = info.unit;
        med_node->data.total = total;

        if (pres_node->data.header == NULL) {
          pres_node->data.header = med_node;
        }
        else {
          last_med_node->next = med_node;
        }
        last_med_node = med_node; 
        medCount++;
      }
      _add2List(pres_node);
      presCount++;
  }
      
  file.close();
  cout << "🎉 Hoan tat! Da load " << presCount << " don thuoc (" << medCount << " loai thuoc) tu file: " << fileLocation << endl;
}

void prescription::printAllPresHeader() {
  cout << "\n--- 🧾 DANH SACH DON THUOC (TOM TAT) ---" << endl;
    cout << "========================================\n" << endl;


    prescriptionNode* pres_node = first;
    
    if (pres_node == NULL) {
        cout << "⚠️  He thong chua co don thuoc nao." << endl;
        cout << "========================================" << endl;
        return;
    }

    int presCount = 0;

    while (pres_node != NULL) {
        presCount++;
        cout << "  " << presCount << ". 🆔 ID: " << pres_node->data.prescriptionID << endl;
        cout << "     🧑‍⚕️ Benh nhan: " << pres_node->data.patientName << endl;
        cout << "     -----" << endl;
        pres_node = pres_node->next;
    }
    
    cout << "\n========================================" << endl;
    cout << "ℹ️  Tong cong: " << presCount << " don thuoc trong he thong." << endl;
}