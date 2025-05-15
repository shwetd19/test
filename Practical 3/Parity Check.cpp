#include <iostream>
#include <string>

using namespace std;

int main() {
    string data;
    char parityChoice;
    
    cout << "Enter binary data: ";
    cin >> data;
    
    cout << "Choose parity type (O for Odd Parity, E for Even Parity): ";
    cin >> parityChoice;

    // Count the number of 1s in the input data
    int onesCount = 0;
    for (char bit : data) {
        if (bit == '1') {
            onesCount++;
        }
    }

    // Add the appropriate parity bit (0 or 1) based on user choice
    char parityBit;
    if ((parityChoice == 'O' || parityChoice == 'o') && onesCount % 2 == 0) {
        parityBit = '1'; // Add 1 for Odd Parity
    } else if ((parityChoice == 'E' || parityChoice == 'e') && onesCount % 2 != 0) {
        parityBit = '1'; // Add 1 for Even Parity
    } else {
        parityBit = '0'; // Add 0 for no parity or correct parity
    }

    // Display the data with the parity bit
    string dataWithParity = data + parityBit;
    cout << "Data with parity bit: " << dataWithParity << endl;

    // Simulate an error by flipping one bit
    // For demonstration purposes
    if (dataWithParity.size() >= 2) {
        dataWithParity[dataWithParity.size() - 2] = (dataWithParity[dataWithParity.size() - 2] == '0') ? '1' : '0';
        cout << "Simulated error in received data: " << dataWithParity << endl;
    }

    // Check for errors by counting the number of 1s in the received data
    int receivedOnesCount = 0;
    for (char bit : dataWithParity) {
        if (bit == '1') {
            receivedOnesCount++;
        }
    }

    // If the total number of 1s matches the chosen parity, no error, otherwise, there is an error
    if ((parityChoice == 'O' || parityChoice == 'o') && receivedOnesCount % 2 != 0) {
        cout << "No error detected. Data received successfully with Odd Parity." << endl;
    } else if ((parityChoice == 'E' || parityChoice == 'e') && receivedOnesCount % 2 == 0) {
        cout << "No error detected. Data received successfully with Even Parity." << endl;
    } else {
        cout << "Error detected in received data." << endl;
    }

    return 0;
}
