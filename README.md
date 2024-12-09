# AMS562FinalProject_FinalVersion

## Table of Contents

- [Project Overview](#project-overview)
- [File Structure](#file-structure)
- [Compilation Instructions](#compilation-instructions)
- [Usage Instructions](#usage-instructions)
- [Results](#results)

## Project Overview

This project focuses on optimizing delivery schedules to minimize the total daily distance traveled while addressing load balancing challenges. It implements advanced optimization techniques, including the Lin–Kernighan heuristic, and provides functionality for generating randomized datasets, analyzing results, and exporting data for further analysis.

## File Structure

The project is organized into the following directories and files:

- **`data/`**: Contains randomized delivery data.
  - `randomized_data.csv`: Standard randomized delivery data.
  - `randomized_data_large.csv`: Large-scale randomized delivery data.

- **`results/`**: Contains the output of optimized delivery schedules and analysis.
  - `combined_customers_balanced.csv`: Results for combined regular and Prime customers.
  - `combined_customers_balanced_large.csv`: Results for large combined customers.
  - `regular_customers_balanced.csv`: Results for regular customers.
  - `regular_customers_balanced_large.csv`: Results for large regular customers.
  - `visualization.ipynb`: Notebook for visualizing results.
  - `Data_Analysis.ipynb`: Notebook for analyzing results.
  - `Tunning.ipynb`: Notebook for hyperparameter tuning.

- **`src/`**: Contains source files for implementation.
  - `CMakeLists.txt`: Build configuration for CMake.
  - `Address.hpp`: Defines the `Address` class for geographical coordinates.
  - `DeliveryRequest.hpp`: Defines the `DeliveryRequest` class for customer orders.
  - `Route.hpp`: Defines the `Route` class for managing daily routes.
  - `ScheduleBalanced.hpp`: Defines the `ScheduleBalanced` class for schedule optimization.
  - `randomized_data_exporter.cpp`: Generates standard randomized data.
  - `randomized_data_large_exporter.cpp`: Generates large-scale randomized data.
  - `main_balanced.cpp`: Main file for optimizing schedules.

- **`tests/`**: Contains unit tests for the project.
  - `CMakeLists.txt`: Build configuration for tests.
  - `test_Address.cpp`: Tests for the `Address` class.
  - `test_DeliveryRequest.cpp`: Tests for the `DeliveryRequest` class.
  - `test_Route.cpp`: Tests for the `Route` class.
  - `test_ScheduleBalanced.cpp`: Tests for the `ScheduleBalanced` class.
  - `test_main.cpp`: Integration tests.

- `CMakeLists.txt`: Root-level build configuration for CMake.

---

## Compilation Instructions

1. **Clone the Repository**: Clone the project to your local machine:
   ```bash
   git clone <repository-url>
   cd AMS562FinalProject_FinalVersion
   ```
   
2. **Create a Build Directory**: Create a directory for build files and navigate into it:
  ```bash
  mkdir build
  cd build
  ```

3. **Generate Build System**: Use CMake to generate the build system:
  ```bash
  cmake ..
  ```

4. **Compile the Project**: Compile the project using:
  ```bash
  make
  ```

## Usage Instructions
To generate the randomized datasets, run the following executables:
1. **For standard data**:
  ```bash
  ./randomized_data_exporter
  ```
  Output: data/randomized_data.csv<br>
  
2. **For large-scale data**:
  ```bash
  ./randomized_data_large_exporter
  ```
  Output: data/randomized_data_large.csv<br>

To optimize delivery schedules and export results, run:<br>

  ```bash
  ./delivery_balanced_scheduler
  ```
  Outputs will be saved in the results/ directory:<br>

  combined_customers_balanced.csv<br>
  combined_customers_balanced_large.csv<br>
  regular_customers_balanced.csv<br>
  regular_customers_balanced_large.csv<br>

  ## Results
  **CSV Files**:<br>
  The exported CSV files contain:<br>

  Day: Delivery day.<br>
  NumDeliveries: Number of deliveries on that day.<br>
  TotalDistance: Total distance traveled on that day.<br>

  **Notebooks**:<br>
  visualization.ipynb: Provides visual analysis of results.<br>
  Data_Analysis.ipynb: Detailed analysis and insights from results.<br>
  Tunning.ipynb: Hyperparameter tuning for associated neural network models.<br>

  








  
