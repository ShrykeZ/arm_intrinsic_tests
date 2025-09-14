#include <stdio.h>

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned char u8;

extern "C" {
    u64 _umul128(u64 m1, u64 m2, u64* hi);
    u8 _addcarry_u64(u8 c_in, u64 a, u64 b, u64* out);
    u8 _subborrow_u64(u8 b_in, u64 a, u64 b, u64* out);
    u64 __shiftright128(u64 LowPart, u64 HighPart, u8 Shift);
    u64 __shiftleft128(u64 LowPart, u64 HighPart, u8 Shift);
    void _BitScanReverse64(u32* index, u64 msk);
    void _BitScanForward64(u32* index, u64 msk);
}

int main() {
    printf("Testing.\n");

    u64 high;
    u64 result = _umul128(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL, &high);
    printf("_umul128: low=0x%016llX, high=0x%016llX\n", result, high);

    u64 sum;
    u8 carry = _addcarry_u64(0, 0xFFFFFFFFFFFFFFFFULL, 1, &sum);
    printf("_addcarry_u64(0, MAXINT, 1): sum=0x%016llX, carry=%d (expected: 0x0000000000000000, 1)\n", sum, carry);

    carry = _addcarry_u64(1, 0xFFFFFFFFFFFFFFFFULL, 0, &sum);
    printf("_addcarry_u64(1, MAXINT, 0): sum=0x%016llX, carry=%d (expected: 0x0000000000000000, 1)\n", sum, carry);

    carry = _addcarry_u64(0, 5, 3, &sum);
    printf("_addcarry_u64(0, 5, 3): sum=0x%016llX, carry=%d (expected: 0x0000000000000008, 0)\n", sum, carry);

    u64 diff;
    u8 borrow = _subborrow_u64(0, 0, 1, &diff);
    printf("_subborrow_u64(0, 0, 1): diff=0x%016llX, borrow=%d (expected: 0xFFFFFFFFFFFFFFFF, 1)\n", diff, borrow);

    borrow = _subborrow_u64(1, 1, 0, &diff);
    printf("_subborrow_u64(1, 1, 0): diff=0x%016llX, borrow=%d (expected: 0x0000000000000000, 0)\n", diff, borrow);

    u64 shifted = __shiftleft128(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL, 4);
    printf("__shiftleft128(..., 4): 0x%016llX\n", shifted);

    shifted = __shiftright128(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL, 4);
    printf("__shiftright128(..., 4): 0x%016llX\n", shifted);

    u32 index;
    _BitScanReverse64(&index, 0x8000000000000000ULL);
    printf("_BitScanReverse64(0x8000000000000000): %d (expected: 63)\n", index);

    _BitScanForward64(&index, 0x8000000000000000ULL);
    printf("_BitScanForward64(0x8000000000000000): %d (expected: 63)\n", index);

    _BitScanForward64(&index, 0x0000000000000001ULL);
    printf("_BitScanForward64(0x0000000000000001): %d (expected: 0)\n", index);

    printf("Intrinsic tests completed.\n");
    return 0;
}
