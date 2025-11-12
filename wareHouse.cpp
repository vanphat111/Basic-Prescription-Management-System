// wareHouse.cpp
#include "wareHouse.h"

int hashFunc(std::string str) {
  int hash = 0;
  for (int i = 0; i < str.length(); i++) {
    hash += str[i];
  }

  while (hash >= MAX_HASH_TABLE_SIZE) {
    hash = hash / 2 + hash % 10;
  }
  return hash;
}

bool wareHouse::_insert(medicInfo info) {
  if (_find(info.medicID) != NULL) return false;

  int idx = hashFunc(info.medicID);
  hashNode* node = new hashNode;
  node->data = info;
  node->next = NULL;

  if (medicStorage[idx] == NULL) {
    medicStorage[idx] = node;
  }
  else {
    node->next = medicStorage[idx];
    medicStorage[idx] = node;
  }
return true;
}

void wareHouse::_print(hashNode* value) {
  cout << "🆔 ID thuoc: " << value->data.medicID << endl;
  cout << "🏷️  Ten thuoc: " << value->data.medicName << endl;
  cout << "💲 Gia thuoc: " << value->data.price << endl;
  cout << "📏 Don vi: " << value->data.unit << endl;
  return;
}

hashNode* wareHouse::_find(std::string ID) {
  int idx = hashFunc(ID);

  if (medicStorage[idx] == NULL) return NULL;

  hashNode* tmp;
  tmp = medicStorage[idx];
  while (tmp != NULL) {
    if (tmp->data.medicID == ID) return tmp;
    tmp = tmp->next;
  }
  return NULL;
}

wareHouse::wareHouse() {
  for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) {
    medicStorage[i] = NULL;
  }
}

void wareHouse::insertMedic() {
    medicInfo change;
    
    cout << "🆔 Nhap ID thuoc: ";
    cin >> change.medicID;

    cout << "🏷️  Nhap ten thuoc: ";
    cin >> change.medicName;
    
    cout << "💲 Nhap gia thuoc: ";
    cin >> change.price;

    cout << "📏 Nhap don vi: ";
    cin >> change.unit;

    cout << (_insert(change) ? "✅ Nhap thuoc co ID " + change.medicID + " vao CSDL thanh cong.\n" :  "❌ Nhap thuoc co ID " + change.medicID + " vao CSDL khong thanh cong.\n");
  }


void wareHouse::insertMedicFromFile() {
    std::string fileLocation;
    cout << "📂 Nhap dia chi file [./data/whData.txt]: ";
    getline(cin, fileLocation);
    if (fileLocation == "") fileLocation = "data/whData.txt";

    std::ifstream file(fileLocation);
    if (!file.is_open()) {
      cout << "❌ Khong mo duoc file!!\n";
      return;
    }

    medicInfo change;
    int count = 0;
    while (file >> change.medicID >> change.medicName >> change.price >> change.unit) {
      cout << (_insert(change) ? "  ✅ Nhap thuoc co ID " + change.medicID + " thanh cong.\n" :  "  ❌ Nhap thuoc co ID " + change.medicID + " khong thanh cong.\n");
      count++;
    }
    file.close();
    cout << "🎉 Da them " << count << " loai thuoc tu file.\n";
}

void wareHouse::save2File() {
  std::string fileLocation;
    cout << "📂 Nhap dia chi file [./data/whData.txt]: ";
    getline(cin, fileLocation);
    if (fileLocation == "") fileLocation = "data/whData.txt";

    std::ofstream file(fileLocation);
    if (!file.is_open()) {
      cout << "❌ Khong mo duoc file!!\n";
      return;
    }

    int count = 0;
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) {
      hashNode* tmp = medicStorage[i];
      while (tmp != NULL) {
        file << tmp->data.medicID << ' ' << tmp->data.medicName << ' ' << tmp->data.price << endl;
        count++;
        tmp = tmp->next;
      }
    }

    file.close();
    cout << "🎉 Hoan tat! Da luu " << count << " loai thuoc vao file\n";
}

bool wareHouse::delMedic(std::string ID) {
  hashNode* delNode;
  delNode = _find(ID);

  if (delNode == NULL) {
    cout << "❌ Khong co thuoc co ID " << ID << " trong kho thuoc!!\n";
    return false;
  }

  hashNode* tmp;
  int idx = hashFunc(ID);
  tmp = medicStorage[idx];

  if (medicStorage[idx] == delNode) {
    medicStorage[idx] = delNode->next;
    delete delNode;
    cout << "✅ ==> Da xoa thuoc co ID " << ID << " khoi don." << endl;
    return true;
  }

  while (tmp != NULL) {
    if (tmp->next == delNode) {
      tmp->next = delNode->next;
      delete delNode;
    cout << "✅ ==> Da xoa thuoc co ID " << ID << " khoi don." << endl;
      return true;
    }
  tmp = tmp->next;
  }
  return false;
}

void wareHouse::findMedic(std::string ID) {
  hashNode* out;
  out = _find(ID);
  
  if (out != NULL) {
    _print(out);
    return;
  }
  cout << "❌ Khong co thuoc co ID " << ID << " trong kho thuoc!!\n";
  return;
}

void wareHouse::updateMedic(std::string ID) {
  if (_find(ID) == NULL) {
    cout << "❌ Khong co thuoc co ID " << ID << " trong kho thuoc!!\n";
    return;
  }

  cout << "--- ℹ️  Thong tin thuoc truoc khi thay doi ---" << endl;
  cout << "==========================================" << endl;
  findMedic(ID);
  cout << "========================================" << endl;
  delMedic(ID);

  insertMedic();
}

void wareHouse::printTable() {
  cout << "--- 📋 DANH SACH THUOC TRONG KHO ---" << endl;
  cout << "=================================" << endl;
  
  int total = 0;

  for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) {
    
    hashNode* temp = medicStorage[i];

    if (temp != nullptr) {
      cout << "🪣 Bucket " << i << ":" << endl;

      while (temp != nullptr) {
        cout << "  -> 🆔 ID:     " << temp->data.medicID << endl;
        cout << "     🏷️  Ten:    " << temp->data.medicName << endl;
        cout << "     💲 Gia:    " << temp->data.price << endl;
        cout << "     📏 Don vi: " << temp->data.unit << endl;
        cout << "     -----" << endl;
        
        total++;
        temp = temp->next;
      }
    }
  }

  cout << "========================================" << endl;
  if (total == 0) {
    cout << "⚠️  Kho thuoc rong!" << endl;
  } else {
    cout << "ℹ️  Tong cong co: " << total << " loai thuoc." << endl;
  }
}