//========================================
// Used libraries
#include <iostream>  // Methods used => std::cin, std::cout, std::cerr
#include <string>    // Methods used => std::string, std::stoull (changed from stoi)
#include <bitset>    // Methods used => std::bitset
#include <cassert>   // Methods used => assert()
#include <sstream>   // Methods used => std::stringstream
#include <cctype>    // Methods used => std::isdigit, std::toupper
#include <limits>    // Added for input validation
#include <algorithm> // Added for string operations

//========================================
// Global Variables (made const where possible)
static std::string current_user_input;
static std::string current_selected_user_input;

//========================================
// Constants for better maintainability
const size_t MAX_BINARY_LENGTH = 64; // Increased from 32-bit limitation
const size_t MAX_INPUT_LENGTH = 100; // Prevent extremely long inputs

//========================================
// Function prototypes
void input_binary();
void input_decimal();
void input_hexadecimal();
void select_translation();
void translate_to_binary();
void translate_to_decimal();
void translate_to_hexadecimal();
void convert_bin_to_dec();
void convert_bin_to_hex();
void convert_dec_to_bin();
void convert_dec_to_hex();
void convert_hex_to_bin();
void convert_hex_to_dec();
bool is_valid_binary(const std::string &str);
bool is_valid_decimal(const std::string &str);
bool is_valid_hexadecimal(const std::string &str);

//========================================
// Enhanced Input Clearing Function
void clear_input_stream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//========================================
// Data Validators (Enhanced with length checks and overflow protection)
bool is_valid_binary(const std::string &str)
{
    if (str.empty() || str.length() > MAX_BINARY_LENGTH)
    {
        return false;
    }
    //========================================
    // Remove leading zeros for efficiency, but keep at least one digit
    size_t start = str.find_first_not_of('0');
    if (start == std::string::npos)
    {
        return true; // All zeros is valid
    }

    for (size_t i = start; i < str.length(); ++i)
    {
        if (str[i] != '0' && str[i] != '1')
        {
            return false;
        }
    }
    return true;
}

bool is_valid_decimal(const std::string &str)
{
    if (str.empty() || str.length() > 20) // 64-bit max is ~19 digits
    {
        return false;
    }
    //========================================
    // Check for leading zeros (except single zero)
    if (str.length() > 1 && str[0] == '0')
    {
        return false;
    }

    for (char c : str) // Use range-based for loop
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    //========================================
    // Check for overflow by comparing with max value
    try
    {
        std::stoull(str); // This will throw if out of range
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool is_valid_hexadecimal(const std::string &str)
{
    if (str.empty() || str.length() > 16) // 64-bit hex is max 16 chars
        return false;

    for (char c : str) // Use range-based for loop
    {
        if (!std::isdigit(c) && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F'))
        {
            return false;
        }
    }
    return true;
}

//========================================
// Input mechanisms (Enhanced with better error handling)
void input_binary()
{
    std::cout << "==================================" << std::endl;
    std::cout << "Input Binary below (max " << MAX_BINARY_LENGTH << " digits)" << std::endl;
    std::cout << "==================================" << std::endl;

    do
    {
        std::cout << ">>> ";
        if (!(std::cin >> current_user_input))
        {
            std::cerr << "Input error occurred!" << std::endl;
            clear_input_stream();
            continue;
        }

        if (current_user_input.length() > MAX_INPUT_LENGTH)
        {
            std::cout << "Input too long! Maximum " << MAX_INPUT_LENGTH << " characters allowed." << std::endl;
            continue;
        }

        if (!is_valid_binary(current_user_input))
        {
            std::cout << "Invalid binary input! Please enter only 0s and 1s." << std::endl;
        }
    } while (!is_valid_binary(current_user_input));

    current_selected_user_input = "[Base 2] | Binary";
    assert(current_selected_user_input != "[Base 10] | Decimal" && current_selected_user_input != "[Base 16] | Hexadecimal");
}

void input_decimal()
{
    std::cout << "==================================" << std::endl;
    std::cout << "Input Decimal below (max 20 digits)" << std::endl;
    std::cout << "==================================" << std::endl;

    do
    {
        std::cout << ">>> ";
        if (!(std::cin >> current_user_input))
        {
            std::cerr << "Input error occurred!" << std::endl;
            clear_input_stream();
            continue;
        }

        if (current_user_input.length() > MAX_INPUT_LENGTH)
        {
            std::cout << "Input too long! Maximum " << MAX_INPUT_LENGTH << " characters allowed." << std::endl;
            continue;
        }

        if (!is_valid_decimal(current_user_input))
        {
            std::cout << "Invalid decimal input! Please enter only digits 0-9." << std::endl;
        }
    } while (!is_valid_decimal(current_user_input));

    current_selected_user_input = "[Base 10] | Decimal";
    assert(current_selected_user_input != "[Base 2] | Binary" && current_selected_user_input != "[Base 16] | Hexadecimal");
}

void input_hexadecimal()
{
    std::cout << "==================================" << std::endl;
    std::cout << "Input Hexadecimal (max 16 digits)" << std::endl;
    std::cout << "==================================" << std::endl;

    do
    {
        std::cout << ">>> ";
        if (!(std::cin >> current_user_input))
        {
            std::cerr << "Input error occurred!" << std::endl;
            clear_input_stream();
            continue;
        }

        if (current_user_input.length() > MAX_INPUT_LENGTH)
        {
            std::cout << "Input too long! Maximum " << MAX_INPUT_LENGTH << " characters allowed." << std::endl;
            continue;
        }

        if (!is_valid_hexadecimal(current_user_input))
        {
            std::cout << "Invalid hexadecimal input! Please enter only digits 0-9 and letters A-F." << std::endl;
        }
        else
        {
            //========================================
            // Convert input to uppercase using standard algorithm
            std::transform(current_user_input.begin(), current_user_input.end(),
                           current_user_input.begin(), ::toupper);
        }
    } while (!is_valid_hexadecimal(current_user_input));

    current_selected_user_input = "[Base 16] | Hexadecimal";
    assert(current_selected_user_input != "[Base 2] | Binary" && current_selected_user_input != "[Base 10] | Decimal");
}

void select_translation()
{
    std::cout << "==================================" << std::endl;
    std::cout << "Current Data used => " << current_selected_user_input << std::endl;
    std::cout << "Choose translation protocol below" << std::endl;
    std::cout << "==================================" << std::endl;

    char data_key;

    if (current_selected_user_input == "[Base 2] | Binary")
    {
        std::cout << "a. Decimal" << std::endl;
        std::cout << "b. Hexadecimal" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << ">>> ";

        if (!(std::cin >> data_key))
        {
            std::cerr << "Input error occurred!" << std::endl;
            return;
        }
        //========================================
        // Convert to lowercase for consistent comparison
        data_key = std::tolower(data_key);

        switch (data_key)
        {
        case 'a':
            translate_to_decimal();
            break;
        case 'b':
            translate_to_hexadecimal();
            break;
        default:
            std::cout << "Invalid choice! Please select 'a' or 'b'." << std::endl;
            break;
        }
    }
    else if (current_selected_user_input == "[Base 10] | Decimal")
    {
        std::cout << "a. Binary" << std::endl;
        std::cout << "b. Hexadecimal" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << ">>> ";

        if (!(std::cin >> data_key))
        {
            std::cerr << "Input error occurred!" << std::endl;
            return;
        }

        data_key = std::tolower(data_key);

        switch (data_key)
        {
        case 'a':
            translate_to_binary();
            break;
        case 'b':
            translate_to_hexadecimal();
            break;
        default:
            std::cout << "Invalid choice! Please select 'a' or 'b'." << std::endl;
            break;
        }
    }
    else if (current_selected_user_input == "[Base 16] | Hexadecimal")
    {
        std::cout << "a. Binary" << std::endl;
        std::cout << "b. Decimal" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << ">>> ";

        if (!(std::cin >> data_key))
        {
            std::cerr << "Input error occurred!" << std::endl;
            return;
        }

        data_key = std::tolower(data_key);

        switch (data_key)
        {
        case 'a':
            translate_to_binary();
            break;
        case 'b':
            translate_to_decimal();
            break;
        default:
            std::cout << "Invalid choice! Please select 'a' or 'b'." << std::endl;
            break;
        }
    }
}

//========================================
// Flexible Caller for binary Translators
void translate_to_binary()
{
    if (current_selected_user_input == "[Base 10] | Decimal")
    {
        convert_dec_to_bin();
    }
    else if (current_selected_user_input == "[Base 16] | Hexadecimal")
    {
        convert_hex_to_bin();
    }
    else
    {
        std::cerr << "Already in Binary!" << std::endl;
    }
}

//========================================
// Flexible Caller for Decimal Translators
void translate_to_decimal()
{
    if (current_selected_user_input == "[Base 2] | Binary")
    {
        convert_bin_to_dec();
    }
    else if (current_selected_user_input == "[Base 16] | Hexadecimal")
    {
        convert_hex_to_dec();
    }
    else
    {
        std::cerr << "Already in Decimal!" << std::endl;
    }
}

//========================================
// Flexible Caller for Hexadecimal Translators
void translate_to_hexadecimal()
{
    if (current_selected_user_input == "[Base 2] | Binary")
    {
        convert_bin_to_hex();
    }
    else if (current_selected_user_input == "[Base 10] | Decimal")
    {
        convert_dec_to_hex();
    }
    else
    {
        std::cerr << "Already in Hexadecimal!" << std::endl;
    }
}

//========================================
// Tools for translating Binary input (Enhanced with 64-bit support)
void convert_bin_to_dec()
{
    try
    {
        unsigned long long bin_converter = std::stoull(current_user_input, nullptr, 2);
        std::cout << "Decimal result equals: " << bin_converter << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid binary format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Binary number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting binary to decimal: " << e.what() << std::endl;
    }
}

void convert_bin_to_hex()
{
    try
    {
        unsigned long long bin_converter = std::stoull(current_user_input, nullptr, 2);
        std::stringstream ss;
        ss << std::hex << std::uppercase << bin_converter;
        std::cout << "Hexadecimal result equals: " << ss.str() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid binary format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Binary number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting binary to hexadecimal: " << e.what() << std::endl;
    }
}

//========================================
// Tools for interpreting Decimal input (Enhanced with 64-bit support)
void convert_dec_to_bin()
{
    try
    {
        unsigned long long dec_converter = std::stoull(current_user_input);
        std::cout << "Binary result equals: " << std::bitset<64>(dec_converter).to_string() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid decimal format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Decimal number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting decimal to binary: " << e.what() << std::endl;
    }
}

void convert_dec_to_hex()
{
    try
    {
        unsigned long long dec_converter = std::stoull(current_user_input);
        std::stringstream ss;
        ss << std::hex << std::uppercase << dec_converter;
        std::cout << "Hexadecimal result equals: " << ss.str() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid decimal format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Decimal number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting decimal to hexadecimal: " << e.what() << std::endl;
    }
}

//========================================
// Tools for interpreting Hexadecimal input (Enhanced with 64-bit support)
void convert_hex_to_bin()
{
    try
    {
        unsigned long long hex_converter = std::stoull(current_user_input, nullptr, 16);
        std::cout << "Binary result equals: " << std::bitset<64>(hex_converter).to_string() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid hexadecimal format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Hexadecimal number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting hexadecimal to binary: " << e.what() << std::endl;
    }
}

void convert_hex_to_dec()
{
    try
    {
        unsigned long long hex_converter = std::stoull(current_user_input, nullptr, 16);
        std::cout << "Decimal result equals: " << hex_converter << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid hexadecimal format - " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Hexadecimal number too large - " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error converting hexadecimal to decimal: " << e.what() << std::endl;
    }
}

//========================================
// main section (Enhanced with better error handling)
int main()
{
    try
    {
        //========================================
        // Step 1: output Menu and list of available data types
        std::cout << "==================================" << std::endl;
        std::cout << "Welcome to Number Base Converter" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << "Please choose user input" << std::endl;
        std::cout << "1. Binary (eg 101011101)" << std::endl;
        std::cout << "2. Decimal (eg 12345678)" << std::endl;
        std::cout << "3. Hexadecimal (eg 123AFCB)" << std::endl;
        std::cout << ">>> ";

        int user_input_selection;

        //========================================
        // Step 2: select user input with enhanced error handling
        if (!(std::cin >> user_input_selection))
        {
            std::cerr << "Error: Invalid input! Please enter a number 1-3." << std::endl;
            return 1;
        }

        switch (user_input_selection)
        {
        case 1:
            input_binary();
            break;
        case 2:
            input_decimal();
            break;
        case 3:
            input_hexadecimal();
            break;
        default:
            std::cout << "Invalid selection! Please choose 1, 2, or 3." << std::endl;
            return 1;
        }

        //========================================
        // Step 3: Select valid interpreters
        select_translation();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
