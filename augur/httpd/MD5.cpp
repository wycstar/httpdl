#include "MD5.h"
#include <iostream>

MD5::MD5()
{
    _update((uint8_t *)"bcd", 3);
    _final();
    std::string s((char *)_out);
    std::cout << s << std::endl;
    for (int i = 0; i < 16; i++) {
        printf("%2x-", _out[i]);
    }
}

MD5::MD5(const uint8_t *in) {
    _update((uint8_t *)"abc", 3);
    _final();
}

MD5::~MD5()
{
}

void MD5::_final() {
    _pad();
    for (uint8_t i = 0; i < 4; i++)
        PUT_32BIT_LE(_out + i * 4, _state[i]);
}

void MD5::_pad()
{
    u_int8_t count[8];
    size_t padlen;

    PUT_64BIT_LE(count, _count);
    padlen = MD5_BLOCK_LENGTH - ((_count >> 3) & (MD5_BLOCK_LENGTH - 1));
    if (padlen < 1 + 8)
        padlen += MD5_BLOCK_LENGTH;
    _update(_padding, padlen - 8);
    _update(count, 8);
}

void MD5::_step(const std::function<uint32_t(uint32_t, uint32_t, uint32_t)> &f,
    uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z, uint32_t data, uint32_t s) {
    w += f(x, y, z) + data;
    w = w << s | w >> (32 - s);
    w += x;
};

void MD5::_update(const uint8_t *input, size_t len) {
    size_t have, need;

    have = (size_t)((_count >> 3) & (MD5_BLOCK_LENGTH - 1));
    need = MD5_BLOCK_LENGTH - have;

    _count += (uint64_t)len << 3;

    if (len >= need) {
        if (have != 0) {
            memcpy(_buffer + have, input, need);
            _transform(_buffer);
            input += need;
            len -= need;
            have = 0;
        }
        while (len >= MD5_BLOCK_LENGTH) {
            _transform(input);
            input += MD5_BLOCK_LENGTH;
            len -= MD5_BLOCK_LENGTH;
        }
    }
    if (len != 0)
        memcpy(_buffer + have, input, len);
}

void MD5::_transform(const uint8_t block[MD5_BLOCK_LENGTH]) {
    u_int32_t a, b, c, d, in[MD5_BLOCK_LENGTH / 4];
    memcpy(in, block, sizeof(in));
    a = _state[0];
    b = _state[1];
    c = _state[2];
    d = _state[3];

    _step(_f1, a, b, c, d, in[0] + 0xd76aa478, 7);
    _step(_f1, d, a, b, c, in[1] + 0xe8c7b756, 12);
    _step(_f1, c, d, a, b, in[2] + 0x242070db, 17);
    _step(_f1, b, c, d, a, in[3] + 0xc1bdceee, 22);
    _step(_f1, a, b, c, d, in[4] + 0xf57c0faf, 7);
    _step(_f1, d, a, b, c, in[5] + 0x4787c62a, 12);
    _step(_f1, c, d, a, b, in[6] + 0xa8304613, 17);
    _step(_f1, b, c, d, a, in[7] + 0xfd469501, 22);
    _step(_f1, a, b, c, d, in[8] + 0x698098d8, 7);
    _step(_f1, d, a, b, c, in[9] + 0x8b44f7af, 12);
    _step(_f1, c, d, a, b, in[10] + 0xffff5bb1, 17);
    _step(_f1, b, c, d, a, in[11] + 0x895cd7be, 22);
    _step(_f1, a, b, c, d, in[12] + 0x6b901122, 7);
    _step(_f1, d, a, b, c, in[13] + 0xfd987193, 12);
    _step(_f1, c, d, a, b, in[14] + 0xa679438e, 17);
    _step(_f1, b, c, d, a, in[15] + 0x49b40821, 22);

    _step(_f2, a, b, c, d, in[1] + 0xf61e2562, 5);
    _step(_f2, d, a, b, c, in[6] + 0xc040b340, 9);
    _step(_f2, c, d, a, b, in[11] + 0x265e5a51, 14);
    _step(_f2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
    _step(_f2, a, b, c, d, in[5] + 0xd62f105d, 5);
    _step(_f2, d, a, b, c, in[10] + 0x02441453, 9);
    _step(_f2, c, d, a, b, in[15] + 0xd8a1e681, 14);
    _step(_f2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
    _step(_f2, a, b, c, d, in[9] + 0x21e1cde6, 5);
    _step(_f2, d, a, b, c, in[14] + 0xc33707d6, 9);
    _step(_f2, c, d, a, b, in[3] + 0xf4d50d87, 14);
    _step(_f2, b, c, d, a, in[8] + 0x455a14ed, 20);
    _step(_f2, a, b, c, d, in[13] + 0xa9e3e905, 5);
    _step(_f2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
    _step(_f2, c, d, a, b, in[7] + 0x676f02d9, 14);
    _step(_f2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

    _step(_f3, a, b, c, d, in[5] + 0xfffa3942, 4);
    _step(_f3, d, a, b, c, in[8] + 0x8771f681, 11);
    _step(_f3, c, d, a, b, in[11] + 0x6d9d6122, 16);
    _step(_f3, b, c, d, a, in[14] + 0xfde5380c, 23);
    _step(_f3, a, b, c, d, in[1] + 0xa4beea44, 4);
    _step(_f3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
    _step(_f3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
    _step(_f3, b, c, d, a, in[10] + 0xbebfbc70, 23);
    _step(_f3, a, b, c, d, in[13] + 0x289b7ec6, 4);
    _step(_f3, d, a, b, c, in[0] + 0xeaa127fa, 11);
    _step(_f3, c, d, a, b, in[3] + 0xd4ef3085, 16);
    _step(_f3, b, c, d, a, in[6] + 0x04881d05, 23);
    _step(_f3, a, b, c, d, in[9] + 0xd9d4d039, 4);
    _step(_f3, d, a, b, c, in[12] + 0xe6db99e5, 11);
    _step(_f3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
    _step(_f3, b, c, d, a, in[2] + 0xc4ac5665, 23);

    _step(_f4, a, b, c, d, in[0] + 0xf4292244, 6);
    _step(_f4, d, a, b, c, in[7] + 0x432aff97, 10);
    _step(_f4, c, d, a, b, in[14] + 0xab9423a7, 15);
    _step(_f4, b, c, d, a, in[5] + 0xfc93a039, 21);
    _step(_f4, a, b, c, d, in[12] + 0x655b59c3, 6);
    _step(_f4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
    _step(_f4, c, d, a, b, in[10] + 0xffeff47d, 15);
    _step(_f4, b, c, d, a, in[1] + 0x85845dd1, 21);
    _step(_f4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
    _step(_f4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
    _step(_f4, c, d, a, b, in[6] + 0xa3014314, 15);
    _step(_f4, b, c, d, a, in[13] + 0x4e0811a1, 21);
    _step(_f4, a, b, c, d, in[4] + 0xf7537e82, 6);
    _step(_f4, d, a, b, c, in[11] + 0xbd3af235, 10);
    _step(_f4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
    _step(_f4, b, c, d, a, in[9] + 0xeb86d391, 21);

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
}

uint8_t* MD5::out() {
    //std::string s((signed)_out);
    //std::cout << s << std::endl;
}
