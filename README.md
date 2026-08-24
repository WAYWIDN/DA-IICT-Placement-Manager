# DA-IICT Placement Manager

A C++ based console application designed to manage, analyze, and organize student placement data efficiently using fundamental data structures and algorithms. This project simulates real-world placement record management by offering interactive sorting, filtering, and statistical tools.

## Features

- **Input Placement Data**  
  Load student placement records from a file (.csv, with specific format), specific to a company.

- **Customizable Sorting**  
  Sort records by batch, company, program, year, or any combination.

- **Placement Statistics**  
  Generate summary statistics based on different filters.

- **Not Selected Student Details**  
  Identify and list students who were not placed, based on custom filters.

## Project Structure

```text
DA-IICT-Placement-Manager/
│
├── include/
│   ├── data/
│   │   └── Repository.h
│   │
│   ├── ds/
│   │   └── AVLTree.h
│   │
│   ├── io/
│   │   ├── CSVService.h
│   │   ├── DisplayService.h
│   │   └── FileService.h
│   │
│   ├── models/
│   │   ├── Query.h
│   │   └── Record.h
│   │
│   ├── services/
│   │   ├── QueryService.h
│   │   └── StatisticsService.h
│   │
│   └── PlacementManager.h
│
├── tests/
│   └── Sample CSV files
│
├── docs/
│   └── architecture.png
│
├── main.cpp
├── .gitignore
└── README.md
```

## Folder Structure

- **models/** — Contains the data models used by the application.
- **ds/** — Contains the AVL Tree implementation.
- **data/** — Contains the Repository and data-related components.
- **io/** — Contains file and console input/output components.
- **services/** — Contains filtering, sorting, and statistics logic.
- **tests/** — Contains sample CSV files for testing.
- **docs/** — Contains project documentation and the architecture diagram.

## Architecture

![System Architecture](docs/architecture.png)

The application follows a modular architecture where each component has a specific responsibility.

- **PlacementManager** — Coordinates the application.
- **FileService** — Manages the placement data file loading.
- **CSVService** — Reads and writes CSV files.
- **QueryService** — Handles filtering, sorting, and not-selected student analysis.
- **StatisticsService** — Calculates placement statistics.
- **DisplayService** — Displays Sorted Data and Not Selected Students on the console.
- **Repository** — Provides access to stored placement data.
- **AVLTree** — Stores student records using a self-balancing binary search tree.
- **Record** — Represents student placement information.
- **Query** — Represents filtering conditions.

## Data Flow

```text
User
  │
  ▼
PlacementManager
  │
  ├── FileService
  │      │
  │      ▼
  │   CSVService
  │      │
  │      ▼
  │   Repository
  │      │
  │      ▼
  │   AVL Trees
  │
  ├── QueryService ────────┐
  │                        │
  └── StatisticsService  ──┤
                           ▼
                     Repository
                           │
                           ▼
                       AVL Trees
                           │
                           ▼
                         Records
                           │
                           ▼
                    DisplayService/CSVService
```

## How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/WAYWIDN/DA-IICT-Placement-Manager.git
cd DA-IICT-Placement-Manager
```

### 2. Compile


```bash
g++ main.cpp -o main
```

### 3. Run

```bash
./main
```

## Running with Sample Data

Sample CSV files are provided in the `tests/` directory.

After starting the application, select the option to load placement data and enter the company name and paths to the CSV files.

Example:

```text
tests/Company1R1.csv
tests/Company1R2.csv
tests/Company1R3.csv
tests/Company1R4.csv
tests/Company1FR.csv
```

Use the actual filenames available in the `tests/` directory.

The application validates all file paths before loading any data. If any required file is invalid, no placement data is inserted.

After successful loading, the application can be used to sort records, view placement statistics, find not-selected students, display filtered results, and export processed data.
