#include <stdio.h>

typedef unsigned long long u64;
typedef unsigned char u8;

u8 debug_addcarry_u64(u8 c_in, u64 a, u64 b, u64* out) {
    printf("  Input: c_in=%d, a=0x%016llX, b=0x%016llX\n", c_in, a, b);
    
    u64 sum1 = a + b;
    bool overflow1 = (sum1 < a);  // Overflow if result < first operand.
    printf("  Step 1: a + b = 0x%016llX, overflow1=%d\n", sum1, overflow1);
    
    u64 sum2 = sum1 + c_in;
    bool overflow2 = (sum2 < sum1);  // Overflow if result < previous sum.
    printf("  Step 2: sum1 + c_in = 0x%016llX, overflow2=%d\n", sum2, overflow2);
    
    u8 carry = overflow1 || overflow2;
    printf("  Final: carry = %d || %d = %d\n", overflow1, overflow2, carry);
    
    *out = sum2;
    return carry;
}

int main() {
    printf("Debugging addcarry logic...\n\n");
    
    u64 result;
    u8 carry;
    
    printf("Test 1: _addcarry_u64(0, MAXINT, 1)\n");
    carry = debug_addcarry_u64(0, 0xFFFFFFFFFFFFFFFFULL, 1, &result);
    printf("Result: sum=0x%016llX, carry=%d\n", result, carry);
    printf("Expected: sum=0x0000000000000000, carry=1\n\n");
    
    printf("Test 2: _addcarry_u64(1, MAXINT, 0)\n");
    carry = debug_addcarry_u64(1, 0xFFFFFFFFFFFFFFFFULL, 0, &result);
    printf("Result: sum=0x%016llX, carry=%d\n", result, carry);
    printf("Expected: sum=0x0000000000000000, carry=1\n\n");
    
    printf("Test 3: _addcarry_u64(0, 5, 3)\n");
    carry = debug_addcarry_u64(0, 5, 3, &result);
    printf("Result: sum=0x%016llX, carry=%d\n", result, carry);
    printf("Expected: sum=0x0000000000000008, carry=0\n\n");
    
    return 0;
}
