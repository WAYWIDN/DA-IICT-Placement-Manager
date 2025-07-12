# 🎓 DA-IICT Placement Manager

A C++ based console application designed to manage, analyze, and organize student placement data efficiently using fundamental data structures and algorithms. This project simulates real-world placement record management by offering interactive sorting, filtering, and statistical tools.

---

## 📌 Features

1. **Input Placement Data**

   * Load student placement records from a file(.csv, with specific format), specific to a company.
2. **Customizable Sorting**

   * Sort records by batch, company, program, year, or any combination.
3. **Placement Statistics**

   * Generate summary statistics based on different filters.
4. **Not Selected Student Details**

   * Identify and list students who were not placed, based on custom filters.

---

## ⚙️ Technologies Used

* **Language:** C++
* **Data Structures:**

  * `Linked List` for managing dynamic student records.
  * `Maps` for quick lookups and classification.
  * `Sets` for handling unique records.
* **Concepts Applied:**

  * File I/O
  * OOPs

---

## 📁 Project Structure

```
DA-IICT-Placement-Manager/
├── Classes/                              # Core class definitions and logic
│   └── class_PlacementManager.cpp
├── Functions/
│   ├── Not Selected/                     # Functions to filter and display unplaced students
│   ├── Placement Statistics/             # Functions to compute placement stats (batch, year, program, etc.)
│   └── Sorting Data/                     # Functions to sort data by various criteria
├── Test Field/                           # Contains sample data, test drivers to validate functionalities, and results
├── main.cpp                              # Main program entry point
└── README.md                             # Project documentation

```

---

## ▶️ How to Run

1. **Clone the repository**

   ```bash
   git clone https://github.com/WAYWIDN/DA-IICT-Placement-Manager.git
   cd DA-IICT-Placement-Manager
   ```

2. **Compile the code**

   ```bash
   g++ main.cpp Classes/class_PlacementManager.cpp -o PlacementManager
   ```

3. **Run the executable**

   ```bash
   ./PlacementManager
   ```

4. **Follow on-screen prompts**

   * Enter the path to the CSV file (e.g., `sample_data/placements.csv`)
   * Enter the company name to analyze

