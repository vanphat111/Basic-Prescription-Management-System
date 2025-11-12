// main.cpp
// From gemini with love (and icons)

#include "prescription.h" // File này đã #include "wareHouse.h"
#include <iostream>
#include <string>
#include <stdlib.h> // Để dùng system("clear")

// Dùng hết cho lẹ
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

// === CÁC HÀM TIỆN ÍCH CHO MENU ===

/**
 * @brief Xóa màn hình (clear cho Linux/macOS, cls cho Windows)
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Dọn sạch bộ đệm cin (rất quan trọng)
 */
void clearInputBuffer() {
    cin.ignore(); // <-- Giữ nguyên code gốc của mày
}

/**
 * @brief Dừng màn hình, đợi người dùng bấm Enter
 */
void pauseScreen() {
    cout << "\n\nNhan Enter de tiep tuc...";
    // cin.get() co the bi troi neu con rac
    // Day la cach an toan de "doi" 1 phim Enter moi
    string dummy;
    getline(cin, dummy);
}

// === CÁC MENU CON ===

/**
 * @brief Menu con để quản lý KHO (wareHouse)
 */
void menu_Kho(wareHouse& wh) {
    int choice = -1;
    while(choice != 0) {
        clearScreen();
        cout << "--- 📦 Quan Ly Kho ---" << endl;
        cout << "1. ➕ Them thuoc (thu cong)" << endl;
        cout << "2. ➖ Xoa thuoc" << endl;
        cout << "3. 🔄 Cap nhat thuoc" << endl;
        cout << "4. 🔎 Tim thuoc" << endl;
        cout << "5. 📋 In tat ca thuoc trong kho" << endl;
        cout << "0. ↩️  Quay lai menu chinh" << endl;
        cout << "-------------------------" << endl;
        cout << "Chon: ";
        cin >> choice;
        
        if (cin.fail()) { // Nếu nhập chữ
            cin.clear();
            choice = -1;
        }
        clearInputBuffer(); // Luôn dọn rác sau khi cin >>

        string id;
        switch(choice) {
            case 1: 
                wh.insertMedic(); 
                break;
            case 2: 
                cout << "Nhap ID thuoc can XOA: "; 
                getline(cin, id); 
                wh.delMedic(id); 
                break;
            case 3: 
                cout << "Nhap ID thuoc can CAP NHAT: "; 
                getline(cin, id); 
                wh.updateMedic(id); 
                break;
            case 4: 
                cout << "Nhap ID thuoc can TIM: "; 
                getline(cin, id); 
                wh.findMedic(id); 
                break;
            case 5: 
                wh.printTable(); 
                break;
            case 0: 
                return; // Quay lại
            default: 
                cout << "Lua chon khong hop le!" << endl;
        }
        if(choice != 0) pauseScreen();
    }
}

/**
 * @brief Menu con để quản lý ĐƠN THUỐC (prescription)
 */
void menu_DonThuoc(prescription& pre) {
    int choice = -1;
    while(choice != 0) {
        clearScreen();
        cout << "--- 📝 Quan Ly Don Thuoc ---" << endl;
        cout << "1. 🆕 Tao don thuoc moi" << endl;
        cout << "2. ➕ Them thuoc vao don" << endl;
        cout << "3. ➖ Xoa thuoc khoi don" << endl;
        cout << "4. 🔎 In chi tiet 1 don thuoc" << endl;
        cout << "5. 📋 In TAT CA don thuoc (tom tat)" << endl; // <-- Giữ nguyên thứ tự của mày
        // (Mày thiếu case 6, 7 cho 2 hàm print all)
        cout << "0. ↩️  Quay lai menu chinh" << endl;
        cout << "--------------------------" << endl;
        cout << "Chon: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            choice = -1;
        }
        clearInputBuffer(); // Luôn dọn rác

        string id;
        switch(choice) {
            case 1: 
                pre.newPrescription(); 
                break;
            case 2: 
                cout << "Nhap ID DON THUOC can them vao: "; 
                getline(cin, id); 
                pre.addMedic2Prescription(id); 
                break;
            case 3: 
                cout << "Nhap ID DON THUOC can xoa bot: "; 
                getline(cin, id); 
                pre.removeMedic(id); 
                break;
            case 4: 
                cout << "Nhap ID DON THUOC can in: "; 
                getline(cin, id); 
                pre.printPrescription(id); 
                break;
            case 5:
                pre.printAllPresHeader();
                break;
            case 0: 
                return; // Quay lại
            default: 
                cout << "Lua chon khong hop le!" << endl;
        }
        if(choice != 0) pauseScreen();
    }
}

/**
 * @brief Menu con để Tải/Lưu file
 */
void menu_LoadSave(wareHouse& wh, prescription& pre) {
    clearScreen();
    cout << "--- 💾 Tai / Luu Du Lieu ---" << endl;
    cout << "1. 📥 Tai KHO tu file" << endl;
    cout << "2. 📤 Luu KHO vao file" << endl;
    cout << "3. 📥 Tai DON THUOC tu file" << endl;
    cout << "4. 📤 Luu DON THUOC vao file" << endl;
    cout << "0. ↩️  Quay lai" << endl;
    cout << "--------------------------" << endl;
    cout << "Chon: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        choice = -1;
    }
    clearInputBuffer(); // <-- Giữ nguyên code gốc của mày

    switch(choice) {
        case 1: 
            wh.insertMedicFromFile(); 
            break;
        case 2: 
            wh.save2File(); 
            break;
        case 3: 
            pre.insertFromFile(); 
            break;
        case 4: 
            pre.save2File(); 
            break;
        case 0: 
            return; // Quay lại
        default: 
            cout << "Lua chon khong hop le!" << endl;
    }
    pauseScreen();
}

// === HÀM MAIN CHÍNH ===

int main() {
    // 1. Khởi tạo
    wareHouse wh;
    prescription pre(wh); // "Bơm" kho vào đơn thuốc

    // 2. Tải dữ liệu cũ (Nếu muốn)
    clearScreen();
    cout << "CHAO MUNG DEN VOI CHUONG TRINH QUAN LY KHO VA DON THUOC" << endl;
    cout << "======================================================" << endl;
    cout << "💾 Ban co muon TAI DU LIEU CU tu file? (y/n): "; // <-- Thêm icon
    char load;
    cin >> load;
    clearInputBuffer();
    
    if (load == 'y' || load == 'Y') {
        cout << "--- 📥 Tai du lieu KHO ---" << endl; // <-- Thêm icon
        wh.insertMedicFromFile(); // Gọi hàm của mày
        cout << "\n--- 📥 Tai du lieu DON THUOC ---" << endl; // <-- Thêm icon
        pre.insertFromFile(); // Gọi hàm của mày
        pauseScreen();
    }

    // 3. Vòng lặp menu chính
    int mainChoice = -1;
    while (mainChoice != 0) {
        clearScreen();
        cout << "--- 🏠 MENU CHINH ---" << endl;
        cout << "1. 📦 Quan ly KHO" << endl;
        cout << "2. 📝 Quan ly DON THUOC" << endl;
        cout << "3. 💾 TAI / LUU du lieu" << endl;
        cout << "0. ❌ Thoat" << endl;        
        cout << "------------------" << endl;
        cout << "Chon: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear();
            mainChoice = -1;
        }
        clearInputBuffer(); // Luôn dọn rác

        switch (mainChoice) {
            case 1:
                menu_Kho(wh);
                break;
            case 2:
                menu_DonThuoc(pre);
                break;
            case 3:
                menu_LoadSave(wh, pre);
                break;
            case 0:
                break; // Thoát vòng lặp
            default:
                cout << "Lua chon khong hop le!" << endl;
                pauseScreen();
        }
    }

    // 4. Lưu trước khi thoát (Nếu muốn)
    clearScreen();
    cout << "💾 Ban co muon LUU DU LIEU truoc khi thoat? (y/n): "; // <-- Thêm icon
    char save;
    cin >> save;
    clearInputBuffer();
    
    if (save == 'y' || save == 'Y') {
        cout << "--- 📤 Luu du lieu KHO ---" << endl; // <-- Thêm icon
        wh.save2File();
        cout << "\n--- 📤 Luu du lieu DON THUOC ---" << endl; // <-- Thêm icon
        pre.save2File();
        pauseScreen();
    }

    cout << "\n👋 Cam on da su dung! Tam biet." << endl; // <-- Thêm icon
    return 0;
}