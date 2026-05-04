#include <iostream>

int main() {
    int var1, var2, var3;

    std::cout << "Enter three integer values: ";
    std::cin >> var1 >> var2 >> var3;

    // Allocate dynamic memory for each pointer using new
    int* ptr1 = new int;
    int* ptr2 = new int;
    int* ptr3 = new int;

    // Store the variable values in the dynamically allocated memory
    *ptr1 = var1;
    *ptr2 = var2;
    *ptr3 = var3;

    // Display the original variables
    std::cout << "\n--- Variables ---" << std::endl;
    std::cout << "var1 = " << var1 << std::endl;
    std::cout << "var2 = " << var2 << std::endl;
    std::cout << "var3 = " << var3 << std::endl;

    // Display pointer contents and addresses
    std::cout << "\n--- Pointers (dynamic memory) ---" << std::endl;
    std::cout << " *ptr1 = " << *ptr1 
              << " (value) at address " << ptr1 << std::endl;
    std::cout << " *ptr2 = " << *ptr2 
              << " (value) at address " << ptr2 << std::endl;
    std::cout << " *ptr3 = " << *ptr3 
              << " (value) at address " << ptr3 << std::endl;

    // Free the dynamically allocated memory
    delete ptr1;
    delete ptr2;
    delete ptr3;

    // Prevent dangling pointers
    ptr1 = nullptr;
    ptr2 = nullptr;
    ptr3 = nullptr;

    std::cout << "\nMemory has been deallocated." << std::endl;

    return 0;
}
