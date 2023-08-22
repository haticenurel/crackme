#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <zlib.h>

void xorEncryptDecrypt(std::vector<uint8_t>& data, char key) {
    for (auto& byte : data) {
        byte ^= key;
    }
}

int main() {
    std::string inputFileName = "../src/text.txt";
    std::string zipFileName = "zipped_text.zip";
    std::string encryptedZipFileName = "encrypted_zipped_text.enc";
    std::string decryptedZipFileName = "decrypted_zipped_text.zip"; // Extra: Decrypted ZIP file name
    char key = 'K'; // XOR encryption key (using 'K' as an example)

    // Open and read the file content
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // Read the file content into a vector
    std::vector<uint8_t> content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Save the content into a ZIP file
    std::ofstream zipFile(zipFileName, std::ios::binary);
    if (!zipFile.is_open()) {
        std::cerr << "Failed to create the ZIP file." << std::endl;
        return 1;
    }

    zipFile.write(reinterpret_cast<char*>(content.data()), content.size());
    zipFile.close();

    std::cout << "ZIP file created." << std::endl;

    // Read the ZIP file
    std::ifstream zipInputFile(zipFileName, std::ios::binary);
    if (!zipInputFile.is_open()) {
        std::cerr << "Failed to open the ZIP file." << std::endl;
        return 1;
    }

    // Read the ZIP file content into a vector
    std::vector<uint8_t> zipContent((std::istreambuf_iterator<char>(zipInputFile)), std::istreambuf_iterator<char>());
    zipInputFile.close();

    // Apply XOR encryption
    xorEncryptDecrypt(zipContent, key);

    // Save the encrypted ZIP content into a file
    std::ofstream encryptedZipFile(encryptedZipFileName, std::ios::binary);
    if (!encryptedZipFile.is_open()) {
        std::cerr << "Failed to create the encrypted ZIP file." << std::endl;
        return 1;
    }

    encryptedZipFile.write(reinterpret_cast<char*>(zipContent.data()), zipContent.size());
    encryptedZipFile.close();

    std::cout << "Encrypted ZIP file created." << std::endl;

    // Decrypt the encrypted ZIP file
    std::ifstream decryptedZipInputFile(encryptedZipFileName, std::ios::binary);
    if (!decryptedZipInputFile.is_open()) {
        std::cerr << "Failed to open the encrypted ZIP file." << std::endl;
        return 1;
    }

    // Read the encrypted ZIP file content into a vector
    std::vector<uint8_t> decryptedZipContent((std::istreambuf_iterator<char>(decryptedZipInputFile)), std::istreambuf_iterator<char>());
    decryptedZipInputFile.close();

    // Apply XOR decryption
    xorEncryptDecrypt(decryptedZipContent, key);

    // Save the decrypted ZIP content into a file
    std::ofstream decryptedZipFile(decryptedZipFileName, std::ios::binary);
    if (!decryptedZipFile.is_open()) {
        std::cerr << "Failed to create the decrypted ZIP file." << std::endl;
        return 1;
    }

    decryptedZipFile.write(reinterpret_cast<char*>(decryptedZipContent.data()), decryptedZipContent.size());
    decryptedZipFile.close();

    std::cout << "Decrypted ZIP file created." << std::endl;

    return 0;
}
