#include <iostream>

using namespace std;

class LFSR {
private:
    uint16_t reg;    // 16-bit shift register
    uint16_t taps;   // feedback taps
public:
    LFSR(uint16_t init, uint16_t tap) {
        reg = init;
        taps = tap;
    }
    uint16_t shift() {
        uint16_t feedback = reg & taps; // calculate feedback
        reg = reg << 1;                 // shift left
        if (feedback & 0x8000) {        // check highest bit of feedback
            reg |= 0x0001;              // set lowest bit of register if feedback is 1
        }
        return reg;
    }
};

int main() {
    // Initialize LFSR with starting value and feedback taps
    LFSR myLFSR(0b1101101010100011, 0b1011010000000000);

    // Shift the LFSR and print the result for 10 iterations
    for (int i = 0; i < 10; i++) {
        cout << bitset<16>(myLFSR.shift()) << endl;
    }

    return 0;
}
