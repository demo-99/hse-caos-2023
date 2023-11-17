#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define EXPONENT_BIT 8
#define SIGNIFICANT_BIT 32 - 1 - EXPONENT_BIT

typedef struct {
    uint32_t significant : SIGNIFICANT_BIT;
    uint32_t exponent : EXPONENT_BIT;
    uint32_t sign : 1;
} CustomFloat;

union RawFloat {
    float a;
    CustomFloat b;
};

typedef struct {
    char c;
    int b;
    char d;
} __attribute__((packed)) Packed;

typedef struct {
    char c;
    int b;
    char d;
} Default;

float custom_to_float(CustomFloat cf) {
    int32_t exp_bias = (1 << (EXPONENT_BIT - 1)) - 1;
    float significand = 1.0 + (float)(cf.significant) / (1 << SIGNIFICANT_BIT);
    float exponent = powf(2.0, (float)((int32_t)cf.exponent - exp_bias));
    return (cf.sign ? -1.0 : 1.0) * significand * exponent;
}

float custom_float_add(CustomFloat cf1, CustomFloat cf2) {
    if (cf1.exponent < cf2.exponent) {
        CustomFloat tmp = cf1;
        cf1 = cf2;
        cf2 = tmp;
    } // cf1> cf2
    uint32_t max_exponent = cf1.exponent;
    uint32_t alligned_significant_2 = cf2.significant >> (max_exponent - cf2.exponent);
}

int main() {
    // printf("sizeof(CustomFloat) = %ld\n", sizeof(CustomFloat));
    // printf("sizeof(Packed) = %ld\n", sizeof(Packed));
    // printf("sizeof(Default) = %ld\n", sizeof(Default));
    CustomFloat cf;
    cf.significant = 1u << 22;
    cf.exponent = 127;
    printf("%f\n", custom_to_float(cf));
}