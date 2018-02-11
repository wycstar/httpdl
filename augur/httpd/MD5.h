#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>

class MD5
{
private:
    static const uint8_t MD5_BLOCK_LENGTH = 64;
    static const uint8_t MD5_DIGEST_LENGTH = 16;
    uint32_t _state[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
    const uint8_t _padding[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t _buffer[MD5_BLOCK_LENGTH];
    uint8_t _out[MD5_DIGEST_LENGTH];
    uint64_t _count;
    std::string _in;
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
    void char_to_int(uint8_t bit8[4], uint32_t bit32) {
        bit8[3] = bit32 >> 24;
        bit8[2] = bit32 >> 16;
        bit8[1] = bit32 >> 8;
        bit8[0] = bit32;
    };
    void char_to_long(uint8_t bit8[4], uint64_t bit32) {
        bit8[7] = bit32 >> 56;
        bit8[6] = bit32 >> 48;
        bit8[5] = bit32 >> 40;
        bit8[4] = bit32 >> 32;
        bit8[3] = bit32 >> 24;
        bit8[2] = bit32 >> 16;
        bit8[1] = bit32 >> 8;
        bit8[0] = bit32;
    };
    void _step(const std::function<uint32_t(uint32_t, uint32_t, uint32_t)> &f,
        uint32_t &w, uint32_t x, uint32_t y, uint32_t z, uint32_t data, uint32_t s);
    void _update(const uint8_t *input, size_t len);
    void _transform(const uint8_t block[MD5_BLOCK_LENGTH]);
    void _pad();
    void _final();

public:
    MD5();
    MD5(std::string s);
    friend std::ostream& operator<<(std::ostream &out, MD5 &m) {
        out << m.to_hex();
        return out;
    };
    friend std::istream& operator>>(std::istream &in, MD5 &m) {
        in >> m._in;
        return in;
    };
    std::string to_hex();
    ~MD5();
};
