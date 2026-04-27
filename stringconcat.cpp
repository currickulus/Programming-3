/**
 * string_concat.cpp
 * CSC450 - Module 2 Critical Thinking Assignment
 * Author: Thomas Dewing
 *
 * Description:
 *   Prompts the user for two strings, concatenates them, and prints the
 *   result. This process repeats three times so the user can observe
 *   behavior across varying string lengths. The program uses std::string
 *   throughout to avoid the buffer-overflow vulnerabilities inherent in
 *   C-style character arrays.
 *
 * Compile: g++ -std=c++17 -Wall -Wextra -o string_concat string_concat.cpp
 * Run:     ./string_concat
 */
 
#include <iostream>
#include <string>
#include <limits>
 
// ---------------------------------------------------------------------------
// printDivider
// Prints a simple visual separator to improve readability between rounds.
// ---------------------------------------------------------------------------
void printDivider(int round)
{
    std::cout << "\n--- Round " << round << " ---\n";
}
 
// ---------------------------------------------------------------------------
// getStringInput
// Reads a full line of text from stdin (supports spaces) and returns it.
// Prompts the user with the supplied label.
// ---------------------------------------------------------------------------
std::string getStringInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}
 
// ---------------------------------------------------------------------------
// concatenateAndDisplay
// Concatenates two strings and prints the result with diagnostic info.
// ---------------------------------------------------------------------------
void concatenateAndDisplay(const std::string& first, const std::string& second)
{
    std::string result = first + second;
 
    std::cout << "\nConcatenation result : \"" << result << "\"\n";
    std::cout << "Result length        : " << result.length() << " character(s)\n";
}
 
// ---------------------------------------------------------------------------
// main
// Entry point. Runs the input / concatenation / display loop three times.
// ---------------------------------------------------------------------------
int main()
{
    const int NUM_ROUNDS = 3;
 
    std::cout << "=== String Concatenation Demo ===\n";
    std::cout << "Enter two strings each round; the program will concatenate them.\n";
 
    for (int round = 1; round <= NUM_ROUNDS; ++round)
    {
        printDivider(round);
 
        std::string first  = getStringInput("Enter first string  : ");
        std::string second = getStringInput("Enter second string : ");
 
        concatenateAndDisplay(first, second);
    }
 
    std::cout << "\n=== Done. Thank you! ===\n";
    return 0;
}
