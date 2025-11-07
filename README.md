# Basic Prescription Management System

This is a project for the Data Structures & Algorithms course, written in C++.

The program simulates a system for managing a medicine warehouse and creating patient prescriptions, focusing on the application of efficient data structures (Hash Tables, Linked Lists).

## 🌟 Features

The system includes two main modules:

### 1. Warehouse Management

* **Add Medicine:** Add a new medicine to the warehouse (`newMedic`).
* **Delete Medicine:** Remove a medicine from the warehouse (`delMedic`).
* **Update Medicine:** Edit medicine information (name, price, quantity...) (`updateMedic`).
* **Find Medicine:** Quickly look up medicine by its ID (`findMedic`).

### 2. Prescription Management

* **New Prescription:** Create a new prescription for a patient (`newPrescription`).
* **Add to Prescription:** Add a medicine (from the warehouse) and its quantity to the prescription (`addMedic`).
* **Remove from Prescription:** Remove a selected medicine from the prescription (`removeMedic`).
* **Print Prescription:** Display patient information and the details of all medicines in the prescription (`printPrescription`).

## 🔧 Data Structures & Design

To optimize performance, this project uses the following data structures:

* **Warehouse:** Implemented using a **Hash Table**.
    * **Rationale:** The system requires constant lookups, additions, and deletions. A Hash Table provides O(1) (near-instant) performance for these operations.
    * **Key:** Medicine ID (`medicID`).
    * **Value:** Detailed medicine information (Name, price, ...).

* **Prescription Details:** Implemented using a **Linked List**.
    * **Rationale:** A single prescription can contain an unlimited number of medicines. A Linked List allows for efficient dynamic scaling.

## 🚀 How to Build & Run

### Prerequisites

* A C++ compiler (e.g., `g++` or `clang++`)



### Compiling (Manually)

If you are not using make, you can compile manually:
``` Bash
g++ *.cpp -o main
```

(Assuming your main executable is named main)

Running the Program

```Bash
./main
```

## 👤 Author

* **Ho Van Phat**
* **GitHub:** [@Vanphat111](https://github.com/vanphat111)

## 📄 License

This project is licensed under the **GNU General Public License v3.0**.
See [LICENSE](https://www.gnu.org/licenses/gpl-3.0.html) for full details.