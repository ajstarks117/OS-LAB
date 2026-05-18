#include <iostream>
using namespace std;

int main() {
    int logicalAddress;
    int segmentSize;
    int numSegments;

    cout << "Enter logical address: ";
    cin >> logicalAddress;

    cout << "Enter number of segments: ";
    cin >> numSegments;

    int base[numSegments];
    int limit[numSegments];

    cout << "\nEnter base and limit for each segment:\n";
    for(int i = 0; i < numSegments; i++) {
        cout << "Segment " << i << " Base: ";
        cin >> base[i];
        cout << "Segment " << i << " Limit: ";
        cin >> limit[i];
    }

    cout << "\n===== STEP BY STEP EXECUTION =====\n";

    // Step 1: Assume equal segment size (for division)
    segmentSize = logicalAddress / numSegments + 1;

    cout << "\n[Step 1] Segment Size Assumption:";
    cout << "\nSegment Size = " << segmentSize << endl;

    // Step 2: Segment number
    int segmentNumber = logicalAddress / segmentSize;
    cout << "\n[Step 2] Segment Number Calculation:";
    cout << "\nSegment Number = " << logicalAddress << " / " 
         << segmentSize << " = " << segmentNumber << endl;

    // Step 3: Offset
    int offset = logicalAddress % segmentSize;
    cout << "\n[Step 3] Offset Calculation:";
    cout << "\nOffset = " << logicalAddress << " % " 
         << segmentSize << " = " << offset << endl;

    // Step 4: Validate segment number
    if(segmentNumber >= numSegments) {
        cout << "\n[Step 4] ERROR: Segment number out of bounds!\n";
        return 0;
    }

    // Step 5: Check limit
    cout << "\n[Step 5] Limit Check:";
    if(offset >= limit[segmentNumber]) {
        cout << "\nERROR: Offset exceeds segment limit!\n";
        return 0;
    }
    cout << "\nOffset is within limit.\n";

    // Step 6: Physical address
    int physicalAddress = base[segmentNumber] + offset;
    cout << "\n[Step 6] Physical Address Calculation:";
    cout << "\nPhysical Address = base[" << segmentNumber << "] + offset";
    cout << "\nPhysical Address = " << base[segmentNumber] 
         << " + " << offset << " = " << physicalAddress << endl;

    cout << "\n===== FINAL OUTPUT =====\n";
    cout << "Segment Number: " << segmentNumber << endl;
    cout << "Offset: " << offset << endl;
    cout << "Base Address: " << base[segmentNumber] << endl;
    cout << "Limit: " << limit[segmentNumber] << endl;
    cout << "Physical Address: " << physicalAddress << endl;

    return 0;
}