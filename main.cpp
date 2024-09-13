#include <iostream>

/*
 * mod function to handle negative numbers
 * pre: a is an integer, b is an integer
 * post: returns a mod b
 */
int mod(int a, int b) {
    return (a % b + b) % b;
}

/*
 * Processes the key to remove any non-letter characters and convert uppercase to lowercase
 * Use this function to process the key before using it in the Vigenere cipher
 * pre: key is a string
 * post: returns key with only lowercase letters without any non-letter characters
 */
std::string processKey(std::string key) {

    std::string processedKey;

    for (char i : key) {
        if (i >= 'a' && i <= 'z') {
            processedKey += i;
        } else if (i >= 'A' && i <= 'Z') {
            processedKey += char(i + 32); // convert to lowercase
        }
    }
    return processedKey;
}

/*
 * Encrypts the plaintext using the key using the Vigenere cipher
 * pre: plaintext is a string, key is a string
 * post: returns the encrypted text
 */
std::string encrypt(std::string plaintext, std::string key){

    std::string processedKey = processKey(key);

    std::string cipherText;
    int j = 0; // index for the key. Can't use i % processedKey.size() because we need to skip non-letter characters in the plaintext

    for (char i : plaintext) {
        // if it's lowercase
        if (i >= 'a' && i <= 'z') {
            // i - 97 gives the position of the letter in the alphabet
            // processedKey[j % processedKey.size()] - 97 gives the position of the letter in the key in the alphabet
            // (i - 97) + (processedKey[j % processedKey.size()] - 97) = (i + processedKey[j % processedKey.size()] - 194)
            // (i + processedKey[j % processedKey.size()] - 194) % 26 to ensure it stays within the rage of the alphabet. (26 letters)
            // + 97 to convert it back to ASCII
            cipherText += char(mod((i + processedKey[j % processedKey.size()] - 194), 26) + 97);
            j++;    // Consume a letter from the key
            continue;
        }

        // if it's uppercase
        else if (i >= 'A' && i <= 'Z') {
            // i - 65 gives the position of the letter in the alphabet
            // key[j % key.size()] - 97 gives the position of the letter in the key in the alphabet (key is lowercase)
            // (i - 65) + (key[i % key.size()] - 97) = (plaintext[i] + key[i % key.size()] - 162)
            // (i + key[j % key.size()] - 194) % 26 to ensure it stays within the rage of the alphabet. (26 letters)
            // + 65 to convert it back to ASCII
            cipherText += char(mod((i + processedKey[j % processedKey.size()] - 162), 26) + 65);
            j++;    // Consume a letter from the key
            continue;
        }

        // if it's not a letter
        else {
            cipherText += i;
            // don't "consume" a letter from the key
        }
    }

    return cipherText;
}

/*
 * Decrypts the ciphertext using the key using the Vigenere cipher
 * pre: cipherText is a string, key is a string
 * post: returns the decrypted text
 */
 std::string decrypt(std::string cipherText, std::string key){

    std::string processedKey = processKey(key);

    std::string plaintext;
    int j = 0; // index for the key. Can't use i % processedKey.size() because we need to skip non-letter characters in the plaintext

    for (char i : cipherText) {
        // if it's lowercase
        if (i >= 'a' && i <= 'z') {
            // i - 97 gives the position of the letter in the alphabet
            // processedKey[j % processedKey.size()] - 97 gives the position of the letter in the key in the alphabet
            // (i - 97) - (processedKey[j % processedKey.size()] - 97) = (i - processedKey[j % processedKey.size()])
            // (i - processedKey[j % processedKey.size()]) % 26 to ensure it stays within the rage of the alphabet. (26 letters)
            // + 97 to convert it back to ASCII
            plaintext += char(mod((i - processedKey[j % processedKey.size()]), 26) + 97);
            j++;    // Consume a letter from the key
            continue;
        }

        // if it's uppercase
        else if (i >= 'A' && i <= 'Z') {
            // i - 65 gives the position of the letter in the alphabet
            // processedKey[j % processedKey.size()] - 97 gives the position of the letter in the key in the alphabet
            // (i - 65) - (processedKey[j % processedKey.size()] - 97) = (i - processedKey[j % processedKey.size()] + 32)
            // (i - processedKey[j % processedKey.size()] + 32) % 26 to ensure it stays within the rage of the alphabet. (26 letters)
            // + 65 to convert it back to ASCII
            plaintext += char(mod((i - processedKey[j % processedKey.size()] + 32), 26) + 65);
            j++;    // Consume a letter from the key
            continue;
        }

        // if it's not a letter
        else {
            plaintext += i;
            // don't "consume" a letter from the key
        }
    }

    return plaintext;
}

int main() {

    char choice;
    std::string key;
    std::string text;

    // Ask user for information
    std::cout << "Encrypt (e)/ Decrypt (d): " << std::endl;
    std::cin >> choice;
    if (choice != 'e' && choice != 'd') {
        std::cout << "Invalid choice" << std::endl;
        return 0;
    }
    std::cout << "Enter the key: " << std::endl;
    std::cin >> key;

    if (choice == 'e') {    // Encrypt
        std::cout << "Enter the plaintext: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, text);
        std::cout << "Encrypted text: " << encrypt(text, key) << std::endl;

    } else {    // Decrypt
        std::cout << "Enter the ciphertext: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, text);
        std::cout << "Decrypted text: " << decrypt(text, key) << std::endl;

    }

    return 0;
}
