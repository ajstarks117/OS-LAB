#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int logicalAddress;
    int pageSize;
    int numPages;

    cout << "Enter logical address: ";
    cin >> logicalAddress;

    cout << "Enter page size: ";
    cin >> pageSize;

    cout << "Enter number of pages in page table: ";
    cin >> numPages;

    int pageTable[numPages];

    cout << "\nEnter frame numbers for each page:\n";
    for(int i = 0; i < numPages; i++) {
        cout << "Page " << i << ": ";
        cin >> pageTable[i];
    }

    cout << "\n===== STEP BY STEP EXECUTION =====\n";

    // Step 1: Offset bits
    int offsetBits = log2(pageSize);
    cout << "\n[Step 1] Offset Bits Calculation:";
    cout << "\nOffset Bits = log2(" << pageSize << ") = " << offsetBits << endl;

    // Step 2: Page bits
    int pageBits = ceil(log2(numPages));
    cout << "\n[Step 2] Page Bits Calculation:";
    cout << "\nPage Bits = log2(" << numPages << ") = " << pageBits << endl;

    // Step 3: Page number
    int pageNumber = logicalAddress / pageSize;
    cout << "\n[Step 3] Page Number Calculation:";
    cout << "\nPage Number = " << logicalAddress << " / " << pageSize 
         << " = " << pageNumber << endl;

    // Step 4: Offset
    int offset = logicalAddress % pageSize;
    cout << "\n[Step 4] Offset Calculation:";
    cout << "\nOffset = " << logicalAddress << " % " << pageSize 
         << " = " << offset << endl;

    // Step 5: Validate page number
    if(pageNumber >= numPages) {
        cout << "\n[Step 5] ERROR: Page number is out of bounds!\n";
        return 0;
    }

    // Step 6: Frame number
    int frameNumber = pageTable[pageNumber];
    cout << "\n[Step 6] Frame Lookup:";
    cout << "\nFrame Number = pageTable[" << pageNumber << "] = " 
         << frameNumber << endl;

    // Step 7: Physical address
    int physicalAddress = (frameNumber * pageSize) + offset;
    cout << "\n[Step 7] Physical Address Calculation:";
    cout << "\nPhysical Address = (" << frameNumber << " * " << pageSize 
         << ") + " << offset;
    cout << "\nPhysical Address = " << physicalAddress << endl;

    cout << "\n===== FINAL OUTPUT =====\n";
    cout << "Page Number: " << pageNumber << endl;
    cout << "Offset: " << offset << endl;
    cout << "Frame Number: " << frameNumber << endl;
    cout << "Physical Address: " << physicalAddress << endl;

    return 0;
}