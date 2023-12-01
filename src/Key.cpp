#include "../include/Key"
#include "../include/Constant"

#include <iostream>

namespace ptc
{
    SubKey::SubKey()
    : b(0)
    {}

    SubKey::SubKey(const SubKey &src)
    : b(src.b)
    {}

    SubKey &SubKey::operator =(const SubKey &src)
    {
        b = src.b;
        return *this;
    }

    const bool SubKey::operator [](const int &tar) const
    {
        return b[tar];
    }

    void SubKeyGen(const unsigned long long &src, SubKey key[16])
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
                temp = LeftShift(temp, 1);
                break;
                default:
                temp = LeftShift(temp, 2);
                break;
            }

            key[i] = KeyOut(temp);
        }

        return;
    }

    std::bitset<56> KeyInit(const unsigned long long &src)
    {
        std::bitset<64> temp = src;
        std::bitset<56> res;
        for (int i = 0, p = 56; i < 28; i += 1, p -= 8)
        {
            if (p < 0)
                p += 65;
            res[i] = temp[p];
        }
        for (int i = 0, p = 62; i < 24; i += 1, p -= 8)
        {
            if (p < 0)
                p += 63;
            res[i + 28] = temp[p];
        }
        res[52] = temp[27];
        res[53] = temp[19];
        res[54] = temp[11];
        res[55] = temp[3];
        return res;
    }

    std::bitset<56> LeftShift(const std::bitset<56> &base, const int &step)
    {
        std::bitset<56> res;
        for (int i = 0; i < 28; i += 1)
            res[i] = base[(i + step) % 28];
        for (int i = 0; i < 28; i += 1)
            res[i + 28] = base[(i + step) % 28 + 28];
        return res;
    }

    SubKey KeyOut(const std::bitset<56> &src)
    {
        SubKey res;
        for (int i = 0; i < 48; i += 1)
            res.b[i] = src[Perm2_Mat[i] - 1];
        return res;
    }

    std::ostream &operator <<(std::ostream &lhs, const SubKey &rhs)
    {
        lhs << rhs.b;
        return lhs;
    }
}
