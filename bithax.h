// Welcome to my little collection of bitwise hacks!
// I've put this together because I also wanted to learn more bitwise hacks, so I created a cheat sheet in C!
// Here you will find some common but also some of the most evil and cool bitwise hacks, for integers and floats.
// These should be translateable to any programming language, which has bitwise operations. (I don't know any who is missing them...)
// But some of them depend on the two complement representation and that booleans can be converted to 1 for true and 0 for zero.
// I wish you happy journey! ༼☯﹏☯༽
//
// Kind Regards,
// Mario from KerboGames
// (support@kerbogames.com)
//
// PS: If you encounter any wrong stuff or a typo just submit a PR ^^

// Some good material on the topic:
// https://www.youtube.com/watch?v=ZusiKXcz_ac
// https://graphics.stanford.edu/~seander/bithacks.html

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

// Simple:

// Returns x * 2
uint8_t multiply_by_2(uint8_t x) {
    return x << 1;
}

// Returns x / 2
uint8_t divide_by_2(uint8_t x) {
    return x >> 1;
}

// Returns true if 'x is even, else false.
bool is_event_or_odd(uint8_t x) {
    return !(x & 1);
}

// Returns true if 'x' is a power of 2, else false.
bool is_power_of_2(uint8_t x) {
    return !(x & (x - 1));
}

// More advanced:

// Sets the 'bit' in 'v' to 1. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// v                10100101
// 1 << bit         00010000
// v | (1 << bit)   10110101
uint8_t set_bit(uint8_t x, uint8_t bit) {
    return x | (1 << bit);
}

// Clears the 'bit' in 'v' - setting it to 0. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// v                10110101
// 1 << bit         00010000
// ~(1 << bit)      11101111
// v & ~(1 << bit)  10100101
uint8_t clear_bit(uint8_t x, uint8_t bit) {
    return x & ~(1 << bit);
}

// Flips the 'bit' in 'v' - setting it to 0 if it was 1 - if it was 0 it becomes 1. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// v                10110101
// 1 << bit         00010000
// v ^ (1 << bit)   10100101
uint8_t flip_bit(uint8_t x, uint8_t bit) {
    return x ^ (1 << bit);
}

// Extracts the bitfield from 'v' using a 'mask' and a 'shift'.
// shift                3           // shift = 3 - shift defines how many digits to the right from the latest mask digit - 3 here
// v                    10110101
// mask                 00011000
// v & mask             00010000
// v & mask >> shift    00000011
uint8_t extract_bitfield(uint8_t x, uint8_t mask, uint8_t shift) {
    return (x & mask) >> shift;
}

// Inserts the 'bitfield' from 'v' using a 'mask' and a 'shift'.
// shift                                3           // shift = 3 - shift defines how many digits to the right from the latest mask digit - 3 here
// bitfield                             00000110
// v                                    10110101
// mask                                 00011100
// v & ~mask                            10100001
// (v & ~mask) | (bitfield << shift)    10111001
uint8_t insert_bitfield(uint8_t x, uint8_t bitfield, uint8_t mask, uint8_t shift) {
    return (x & ~mask) | (bitfield << shift);
}

// Swaps both numbers without a temporary value. Note: the asterix '*' if for derefencing the pointer - it is not a bitwise operation. If you use this algorithm with normal variables, just leave it away.
// x        00101010
// y        10101110
// x ^= y   10000100
// y ^= x   00101010
// x ^= y   10101110
void xor_swap(uint8_t *x, uint8_t *y)  {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

// Returns the smaller integer of x and y but without a brach (if/else/ternary, goto etc..)
// Normally min is implemented something like this:
// return x < y ? x : y;
// But we have a branch there so let's do it witout. (The branch free min could be used to merge arrays for example.)
// If x < y, then -(x < y) => -1 => all 1's in two complement representation.
// So we have y ^ (x ^ y) => x
// If x >= y, then -(x < y) => 0 so y ^ 0 is y.
uint8_t min(uint8_t x, uint8_t y) {
    return y ^ ((x ^ y) & -(x < y));
}

// Returns the larger integer of x and y but without a brach (if/else/ternary, goto etc..)
// Normally max is implemented something like this:
// return x > y ? x : y;
// But we have a branch there so let's do it witout. (The branch free min could be used to merge arrays for example.)
// Same tricks as with min() above.
uint8_t max(uint8_t x, uint8_t y) {
    return x ^ ((x ^ y) & -(x < y));
}

// Calculates (x + y) % n assuming 0 <= x <= n && 0 <= y <= n but without a branch (if/else/ternary, goto etc..)
// Normally this could be implemented like:
// return (x + y) % n;
// But division is expensive so or even better:
// uint8_t t = x + y;
// return (t < n) ? t : t - n;
// But not there is a branch, so let's do it without with the same trick used in min() above.
uint8_t modular_addition(uint8_t x, uint8_t y, uint8_t mod) {
    uint8_t t = x + y;
    return t - (mod & - (t >= mod));
}

// Rounds up the number to a power of 2.
uint64_t round_up_to_pow2(uint64_t x) {
    // x 0010000001010000
    --x;                        // 0010000001010000 - flips rightmost 1 bit to zero and fills the right with 1's.
    x |= x >> (1 << 0);         // 0011000001101111 - shift all one bits 1 bit position to the right and OR these together.
    x |= x >> (1 << 1);         // 0011110001111111 - shift all one bits 2 bit positions to the right and OR these together.
    x |= x >> (1 << 2);         // 0011111111111111 - shift all one bits 4 bit positions to the right and OR these together.
    x |= x >> (1 << 3);         // etc              - shift all one bits 8 bit positions to the right and OR these together.
    x |= x >> (1 << 4);         // etc              - shift all one bits 16 bit positions to the right and OR these together.
    x |= x >> (1 << 5);         // 0100000000000000 - shift all one bits 32 bit positions to the right and OR these together. Not is is eactly one bit less than the power of two.
    return ++x;                 // 1000000000000000 - after the increment we get the full power to since increment flips the leftmost bit and clears all others.
}

// Returns the mask of the least-significant 1-bit in x.
// x        00000101
// -x       11111011
// x & -x   00000001
uint8_t least_significat_mask(uint8_t x) {
    return x & -x;
}

// Compute log x, where x is a power of 2.
// A deBrujin sequence s of length 2y is a cyclic 0-1 sequance such that
// each of the 2y 0-1 strings of length y occurs exactly once as a substring of s.
// 00011101 * pow(2, 4) => 11010000
// 11010000 >> 5 => 6
// lookup_table[6] => 4
uint32_t logbase2_of_power2(uint32_t x) {
    const uint64_t de_bruijin = 0x022fdd63cc95386d;
    static const uint32_t lookup_table[64] = {
        0,1,2,53,3,7,54,27,4,38,41,8,34,55,48,28,62,
        5,39,46,44,42,22,9,24,35,59,56,49,18,29,11,63,
        52,6,26,37,40,33,47,61,45,43,21,23,58,17,10,51,
        25,36,32,60,20,57,16,50,31,19,15,30,14,13,12
    };
    return lookup_table[(x * de_bruijin) >> 58];
}
