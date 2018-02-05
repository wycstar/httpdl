#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <string.h>

const uint8_t _padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

class MD5
{
#define PUT_64BIT_LE(cp, value) do {					\
	(cp)[7] = (value) >> 56;					\
	(cp)[6] = (value) >> 48;					\
	(cp)[5] = (value) >> 40;					\
	(cp)[4] = (value) >> 32;					\
	(cp)[3] = (value) >> 24;					\
	(cp)[2] = (value) >> 16;					\
	(cp)[1] = (value) >> 8;						\
	(cp)[0] = (value); } while (0)

#define PUT_32BIT_LE(cp, value) do {					\
	(cp)[3] = (value) >> 24;					\
	(cp)[2] = (value) >> 16;					\
	(cp)[1] = (value) >> 8;						\
	(cp)[0] = (value); } while (0)

private:
    static const uint8_t MD5_BLOCK_LENGTH = 64;
    static const uint8_t MD5_DIGEST_LENGTH = 16;
    uint32_t _state[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
    uint8_t _buffer[MD5_BLOCK_LENGTH];
    uint8_t _out[MD5_DIGEST_LENGTH];
    uint64_t _count;
    static uint32_t _f1(uint32_t x, uint32_t y, uint32_t z){
        return z ^ (x & (y ^ z));
    };
    static uint32_t _f2(uint32_t x, uint32_t y, uint32_t z) {
        return _f1(z, x, y);
    };
    static uint32_t _f3(uint32_t x, uint32_t y, uint32_t z) {
        return x ^ y ^ z;
    };
    static uint32_t _f4(uint32_t x, uint32_t y, uint32_t z) {
        return y ^ (x | ~z);
    };
    void _step(const std::function<uint32_t(uint32_t, uint32_t, uint32_t)> &f,
        uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z, uint32_t data, uint32_t s);
    void _update(const uint8_t *input, size_t len);
    void _transform();
    void _pad();
    void _final();

public:
    MD5();
    MD5(const uint8_t *in);
    uint8_t* out();
    ~MD5();
};
