#include <iostream>
#include <bitset>
#include <cstdint>

template <size_t N>
class LFSR {
private:
    uint_fast64_t reg;      // shift register
    uint_fast64_t taps;     // feedback taps
    uint_fast64_t mask;     // mask for truncating register to N bits
public:
    LFSR(uint_fast64_t init, uint_fast64_t tap) {
        reg = init;
        taps = tap;
        mask = (1ull << N) - 1; // create mask for truncating register to N bits
    }
    uint_fast64_t shift() {
        uint_fast64_t feedback = reg & taps;   // calculate feedback
        reg = (reg << 1) | (feedback >> (N-1)); // shift left and insert feedback bit
        reg &= mask;                           // truncate to N bits
        return reg;
    }
};

int main() {
    // Example usage of 8-bit LFSR
    LFSR<8> myLFSR8(0b11001001, 0b10000110);

    // Shift the LFSR and print the result for 10 iterations
    for (int i = 0; i < 10; i++) {
        std::cout << std::bitset<8>(myLFSR8.shift()) << std::endl;
    }

    // Example usage of 16-bit LFSR
    LFSR<16> myLFSR16(0b1101101010100011, 0b1011010000000000);

    // Shift the LFSR and print the result for 10 iterations
    for (int i = 0; i < 10; i++) {
        std::cout << std::bitset<16>(myLFSR16.shift()) << std::endl;
    }

    // Example usage of 32-bit LFSR
    LFSR<32> myLFSR32(0x87654321, 0x80000057);

    // Shift the LFSR and print the result for 10 iterations
    for (int i = 0; i < 10; i++) {
        std::cout << std::bitset<32>(myLFSR32.shift()) << std::endl;
    }

    return 0;
}
