#include "Base64.h"



Base64::Base64()
{
}


Base64::~Base64()
{
}

std::string Base64::decode(std::string in)
{
    const char *cp = nullptr;
    int space_idx = 0;
    int phase = 0;
    int d = 0;
    int prev_d = 0;
    unsigned char c = 0;
    std::string out;

    for (cp = in.c_str(); *cp != '\0'; ++cp) {
        d = B64_DECODE_TABLE[(int)*cp];
        if (d != -1) {
            switch (phase) {
            case 0:
                ++phase;
                break;

            case 1:
                c = ((prev_d << 2) | ((d & 0x30) >> 4));
                out += c;
                ++phase;
                break;

            case 2:
                c = (((prev_d & 0xf) << 4) | ((d & 0x3c) >> 2));
                out += c;
                ++phase;
                break;

            case 3:
                c = (((prev_d & 0x03) << 6) | d);
                out += c;
                phase = 0;
                break;
            }
            prev_d = d;
        }
    }
    return out;
}

std::string Base64::encode(std::string in)
{
    std::string res;
    auto str = in.c_str();
    auto in_len = in.length();
    uint64_t i, j;
    auto out_len = (in_len / 3 + (in_len % 3 != 0)) * 4;
    for (i = 0, j = 0; i < out_len - 2; j += 3, i += 4) {
        res += B64_ENCODE_TABLE[str[j] >> 2];
        res += B64_ENCODE_TABLE[(str[j] & 0x3) << 4 | (str[j + 1] >> 4)];
        res += B64_ENCODE_TABLE[(str[j + 1] & 0xf) << 2 | (str[j + 2] >> 6)];
        res += B64_ENCODE_TABLE[str[j + 2] & 0x3f];
    }
    switch (in_len % 3)
    {
    case 1:
        res[i - 2] = '=';
        res[i - 1] = '=';
        break;
    case 2:
        res[i - 1] = '=';
        break;
    }
    return res;
}
