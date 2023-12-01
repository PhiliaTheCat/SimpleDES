#include "../include/Key"
#include "../include/Constant"

namespace ptc
{
    SubKey::SubKey(const unsigned long long &num = 0)
    : b(num)
    {}

    SubKey::SubKey(const SubKey &src)
    : b(src.b)
    {}

    SubKey &SubKey::operator =(const SubKey &src)
    {
        b = src.b;
        return *this;
    }

    void SubKeyGen(const std::bitset<64> &src, SubKey key[16])
    {
        std::bitset<56> temp = KeyInit(src);

        for (int i = 0; i < 16; i += 1)
        {
            switch (i)
            {
                case 0:
                case 1:
                case 8:
                case 15:
                LeftShift(temp, 1);
                break;
                default:
                LeftShift(temp, 2);
                break;
            }

            key[i] = KeyOut(temp);
        }

        return;
    }

    std::bitset<56> KeyInit(const std::bitset<64> &src)
    {
        std::bitset<56> res;
        for (int i = 0, p = 56; i < 28; i += 1, p -= 8)
        {
            if (p < 0)
                p += 65;
            res[i] = src[p];
        }
        for (int i = 0, p = 62; i < 24; i += 1, p -= 8)
        {
            if (p < 0)
                p += 63;
            res[i + 28] = src[p];
        }
        res[52] = src[27];
        res[53] = src[19];
        res[54] = src[11];
        res[55] = src[3];
        return res;
    }

    void LeftShift(std::bitset<56> &base, const int &step)
    {
        int i = 0, p = 27;
        int temp;
        while (i < 27)
        {
            if (i == 0)
                temp = base[27];
            base[p] = base[(p - step + 28) % 28];
        }
        return;
    }

    SubKey KeyOut(const std::bitset<56> &src)
    {
        SubKey res;
        for (int i = 0; i < 48; i += 1)
            res.b[i] = src[Switch2[i] - 1];
        return res;
    }
}
