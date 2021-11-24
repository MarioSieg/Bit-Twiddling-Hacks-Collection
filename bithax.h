// Welcome to my little collection of bitwise hacks!
// I've put this together because I also wanted to learn more bitwise hacks, so I created a cheat sheet in C!
// Here you will find some common but also some of the most evil and cool bitwise hacks, for integers and floats.
// These should be translateable to any programming language, which has bitwise operations. But some of them depend on the two complement representation and IEEE 754.
// I wish you happy journey! ༼☯﹏☯༽
//
// Kind Regards,
// Mario <pinsrq>
//
// PS: If you encounter any weird stuff or a typo just submit a PR ^^

// Some good material on the topic:
// https://www.youtube.com/watch?v=ZusiKXcz_ac
// https://graphics.stanford.edu/~seander/bithacks.html
// https://www.amazon.de/Hackers-Delight-Henry-S-Warren/dp/0321842685
// https://www.techiedelight.com/bit-hacks-part-4-playing-letters-english-alphabet/
// https://codeforwin.org/2018/05/10-cool-bitwise-operator-hacks-and-tricks.html

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

// Clears all bits, settings the number to zero. 
// Maybe you know it from assembly - setting a register to zero by using:
// xor rax, rax
// for example. It's exactly the same:
void set_x_to_zero(int32_t *const x) {
    *x ^= *x;
}

// Returns x * 2
uint8_t multiply_by_2(const uint8_t x) {
    return x << 1;
}

// Returns x / 2
uint8_t divide_by_2(const uint8_t x) {
    return x >> 1;
}

// Returns true if 'x is even, else false.
bool is_event_or_odd(const uint8_t x) {
    return !(x & 1);
}

// Returns true if 'x' is a power of 2, else false.
bool is_power_of_2(const uint8_t x) {
    return !(x & (x - 1));
}

// Returns x as uppercase letter.
// If we carefully analyze, we will notice that ASCII codes of lowercase and uppercase characters differ only in their third significant bit. 
// For uppercase characters, the bit is 0 and for lowercase characters the bit is 1. We just have toggle that bit on or off!
// ' ' (space) has the ASCII code of 00100000 and _ (underscore) has an ASCII code of 01011111
// If we take OR of an uppercase characters with, the third significant bit will be set and we will get its lowercase equivalent.
// If we take AND of a lowercase character with, the third significant bit will be unset and we will get its uppercase equivalent.
// If we take XOR of an uppercase or lowercase characters with, only its third significant bit will be toggled. i.e. lowercase becomes uppercase and vice versa. 
char to_uppercase(const char x) {
    return x & '_';
}

// Returns x as lowercase letter.
// If we carefully analyze, we will notice that ASCII codes of lowercase and uppercase characters differ only in their third significant bit. 
// For uppercase characters, the bit is 0 and for lowercase characters the bit is 1. We just have toggle that bit on or off!
// ' ' (space) has the ASCII code of 00100000 and _ (underscore) has an ASCII code of 01011111
// If we take OR of an uppercase characters with, the third significant bit will be set and we will get its lowercase equivalent.
// If we take AND of a lowercase character with, the third significant bit will be unset and we will get its uppercase equivalent.
// If we take XOR of an uppercase or lowercase characters with, only its third significant bit will be toggled. i.e. lowercase becomes uppercase and vice versa. 
char to_lowercase(const char x) {
    return x | ' ';
} 


// Returns x as uppercase letter if it was lowercase, if x was lowecase it returns x as uppercase.
// If we carefully analyze, we will notice that ASCII codes of lowercase and uppercase characters differ only in their third significant bit. 
// For uppercase characters, the bit is 0 and for lowercase characters the bit is 1. We just have toggle that bit on or off!
// ' ' (space) has the ASCII code of 00100000 and _ (underscore) has an ASCII code of 01011111
// If we take OR of an uppercase characters with, the third significant bit will be set and we will get its lowercase equivalent.
// If we take AND of a lowercase character with, the third significant bit will be unset and we will get its uppercase equivalent.
// If we take XOR of an uppercase or lowercase characters with, only its third significant bit will be toggled. i.e. lowercase becomes uppercase and vice versa. 
char invert_case(const char x) {
    return x ^ ' ';
}

// Sets the rightmost bit to 1. (Produces all 1's if none)
// x            10100111
// x & (x+1)    10101111
uint8_t set_rightmost_bit(const uint8_t x) {
    return x & (x + 1);
}

// Sets the rightmost bit to 0. (Produces 0 if none)
// x            01011000
// x & (x-1)    01010000
uint8_t clear_rightmost_bit(const uint8_t x) {
    return x & (x - 1);
}

// Sets the 'bit' in 'v' to 1. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// x                10100101
// 1 << bit         00010000
// v | (1 << bit)   10110101
uint8_t set_bit(const uint8_t x, const uint8_t bit) {
    return x | (1 << bit);
}

// Sets the 'bit' in 'v' to 0. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// x                10110101
// 1 << bit         00010000
// ~(1 << bit)      11101111
// x & ~(1 << bit)  10100101
uint8_t clear_bit(const uint8_t x, const uint8_t bit) {
    return x & ~(1 << bit);
}

// Flips the 'bit' in 'v' - setting it to 0 if it was 1 - if it was 0 it becomes 1. (The 'bit' is like an index of an array from 0-7 in an 8-bit integer.)
// bit              5           // so the 5th bit
// x                10110101
// 1 << bit         00010000
// x ^ (1 << bit)   10100101
uint8_t flip_bit(const uint8_t x, const uint8_t bit) {
    return x ^ (1 << bit);
}

// Extracts the bitfield from 'v' using a 'mask' and a 'shift'.
// shift                3           // shift = 3 - shift defines how many digits to the right from the latest mask digit - 3 here
// x                    10110101
// mask                 00011000
// x & mask             00010000
// x & mask >> shift    00000011
uint8_t extract_bitfield(const uint8_t x, const uint8_t mask, const uint8_t shift) {
    return (x & mask) >> shift;
}

// Inserts the 'bitfield' from 'v' using a 'mask' and a 'shift'.
// shift                                3           // shift = 3 - shift defines how many digits to the right from the latest mask digit - 3 here
// bitfield                             00000110
// x                                    10110101
// mask                                 00011100
// x & ~mask                            10100001
// (x & ~mask) | (bitfield << shift)    10111001
uint8_t insert_bitfield(const uint8_t x, const uint8_t bitfield, const uint8_t mask, const uint8_t shift) {
    return (x & ~mask) | (bitfield << shift);
}

// Swaps both numbers without a temporary value. Note: the asterix '*' if for derefencing the pointer - it is not a bitwise operation. If you use this algorithm with normal variables, just leave it away.
// x        00101010
// y        10101110
// x ^= y   10000100
// y ^= x   00101010
// x ^= y   10101110
void xor_swap(uint8_t *const x, uint8_t *const y)  {
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
uint8_t min(const uint8_t x, const uint8_t y) {
    return y ^ ((x ^ y) & -(x < y));
}

// Returns the larger integer of x and y but without a brach (if/else/ternary, goto etc..)
// Normally max is implemented something like this:
// return x > y ? x : y;
// But we have a branch there so let's do it witout. (The branch free min could be used to merge arrays for example.)
// Same tricks as with min() above.
uint8_t max(const uint8_t x, const uint8_t y) {
    return x ^ ((x ^ y) & -(x < y));
}

// Calculates (x + y) % n assuming 0 <= x <= n && 0 <= y <= n but without a branch (if/else/ternary, goto etc..)
// Normally this could be implemented like:
// return (x + y) % n;
// But division is expensive so or even better:
// uint8_t t = x + y;
// return (t < n) ? t : t - n;
// Let's do it without with the same trick used in min() above:
uint8_t modular_addition(const uint8_t x, const uint8_t y, const uint8_t mod) {
    uint8_t t = x + y;
    return t - (mod & - (t >= mod));
}

// Returns the mask of the least-significant 1-bit in x.
// x        00000101
// -x       11111011
// x & -x   00000001
uint8_t least_significat_mask(const uint8_t x) {
    return x & -x;
}

// Compute log x, where x is a power of 2.
// A deBrujin sequence s of length 2y is a cyclic 0-1 sequence such that
// each of the 2y 0-1 strings of length y occurs exactly once as a substring of s.
// 00011101 * pow(2, 4) => 11010000
// 11010000 >> 5 => 6
// lookup_table[6] => 4
uint32_t logbase2_of_power2(const uint32_t x) {
    const uint64_t de_bruijin = 0x022fdd63cc95386d;
    static const uint32_t lookup_table[64] = {
        0,1,2,53,3,7,54,27,4,38,41,8,34,55,48,28,62,
        5,39,46,44,42,22,9,24,35,59,56,49,18,29,11,63,
        52,6,26,37,40,33,47,61,45,43,21,23,58,17,10,51,
        25,36,32,60,20,57,16,50,31,19,15,30,14,13,12
    };
    return lookup_table[(x * de_bruijin) >> 58];
}

// Rounds up the number to a power of 2.
uint64_t round_up_to_pow2(register uint64_t x) {
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

// Fast method to calculate the inver square root (modified quake version.)
// Used an approximation constant and newton's method to calculate it via a the magic number.
// See https://en.wikipedia.org/wiki/Fast_inverse_square_root
float fast_inversed_sqrt(const float x) {
    const float x2 = x * .5f;
    const uint32_t i = 0x5f3759df - (*(const uint32_t *const)&x >> 1);
    const float y = *(const float *const)&i;
    return y * (1.5f - (x2 * y * y));
}

// Reverses the bits of the integer.
// See https://stackoverflow.com/questions/178265/what-is-the-most-hard-to-understand-piece-of-c-code-you-know
uint32_t reverse_bits(register uint32_t x) {
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}

// XOR if assignment branch:
// if (x == a)
//  x = b;
// if (x == b)
//  x = a;
void if_x_equals_a(int32_t *const x, const int32_t a, const int32_t b) {
    *x = a ^ b ^ *x; //if (x == a) x = b
}

// XOR encryption (!!NOT CRYPTOGRAPHICALLY SECURE!!):
void encrypt_decrypt(register char *c, const register uint8_t key) {
    for(; *c; ++c) {
        *c ^= key;
    }
}


// multiplicate with 10
void mul10(int32_t *x){
	*x += *x + ( *x << 3 );
}

// divide by 10. needs 64bit integers for the calculation
void div10(uint32_t *x){
	*x = ( (int64_t)*x *0xcccccccd ) >> 35;
}


