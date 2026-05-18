#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Reads the entire contents of a file into a string.
// Returns false if the file could not be opened.
bool read_file(const std::string& filename, std::string& contents) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: could not open " << filename << " for reading.\n";
        return false;
    }
    contents.assign(std::istreambuf_iterator<char>(in),
                    std::istreambuf_iterator<char>());
    return true;
}

// Appends user-supplied text to the given file.
// Returns false if the file could not be opened.
bool append_to_file(const std::string& filename, const std::string& text) {
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Error: could not open " << filename << " for appending.\n";
        return false;
    }
    out << text << "\n";
    return true;
}

// Reverses all characters in src_file and writes the result to dst_file.
// Returns false if either file could not be opened.
bool reverse_file(const std::string& src_file, const std::string& dst_file) {
    std::string contents;
    if (!read_file(src_file, contents)) return false;

    std::reverse(contents.begin(), contents.end());

    std::ofstream out(dst_file);
    if (!out.is_open()) {
        std::cerr << "Error: could not open " << dst_file << " for writing.\n";
        return false;
    }
    out << contents;
    return true;
}

int main() {
    const std::string input_file   = "CSC450_CT5_mod5.txt";
    const std::string reverse_file_out = "CSC450-mod5-reverse.txt";

    // --- Get user input ---
    std::cout << "Enter text to append to " << input_file << ":\n> ";
    std::string user_text;
    std::getline(std::cin, user_text);

    // --- Append to source file ---
    if (!append_to_file(input_file, user_text)) return 1;
    std::cout << "Text appended to " << input_file << " successfully.\n";

    // --- Reverse and write to new file ---
    if (!reverse_file(input_file, reverse_file_out)) return 1;
    std::cout << "Reversed content written to " << reverse_file_out << " successfully.\n";

    // --- Display both files ---
    std::string original, reversed;
    read_file(input_file, original);
    read_file(reverse_file_out, reversed);

    std::cout << "\n--- Contents of " << input_file << " ---\n" << original;
    std::cout << "\n--- Contents of " << reverse_file_out << " ---\n" << reversed << "\n";

    return 0;
}
