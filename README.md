# Project Name: Basic Data Translator Version 1

## Description
I was inspired to do this project during my first semester at university, where I learned the basics of **binary, decimal, and hexadecimal** number systems.  
I wanted to create a **console application** to translate between these three fundamental data types and practice implementing input validation, error handling, and number conversions in C++.  

This project demonstrates:
- Handling user input and validating data types
- Converting between number bases using standard C++ libraries
- Error handling for invalid input or overflow
- A modular structure with reusable functions

## Features
- Input validation for **binary**, **decimal**, and **hexadecimal** numbers
- Support for 64-bit numbers (Binary up to 64 digits, Decimal up to 20 digits, Hexadecimal up to 16 digits)
- Conversion between:
  - Binary ↔ Decimal
  - Binary ↔ Hexadecimal
  - Decimal ↔ Hexadecimal
- Clear and informative console interface
- Robust error handling using exceptions and `assert()`

## Tech Stack / Libraries
- **Language:** C++17 or later  
- **Standard Libraries Used:**
  - `<iostream>` – for console I/O  
  - `<string>` – for string manipulation  
  - `<bitset>` – for binary representation  
  - `<sstream>` – for string conversions  
  - `<cctype>` – for character validation  
  - `<limits>` – for input validation  
  - `<algorithm>` – for string transformations  
  - `<cassert>` – for internal sanity checks  


### 1. Clone the Repository (bash or zsh)
- git clone https://github.com/your-username/your-repo.git
- cd your-repo
- g++ -std=c++17 -o <output-name> main.cpp
- ./<output-name>
