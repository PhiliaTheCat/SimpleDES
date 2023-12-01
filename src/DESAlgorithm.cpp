#include "../include/DESAlgorithm"
#include "../include/Constant"

namespace ptc
{
    void Split(const std::bitset<64> &src, std::bitset<32> &L, std::bitset<32> &R)
    {
        for (int i = 0; i < 32; i += 1)
            L[i] = src[i];
        for (int i = 32; i < 64; i += 1)
            R[i - 32] = src[i];
        return;
    }

    void Round(std::bitset<32> &L, std::bitset<32> &R, const SubKey &key)
    {
        std::bitset<32> nL =  R;
        std::bitset<32> nR = L ^ f(R, key);
        L = nL;
        R = nR;
        return;
    }

    std::bitset<32> f(const std::bitset<32> &src, const SubKey &key)
    {
        std::bitset<48> t = E(src);
        for (int i = 0; i < 48; i += 1)
            t[i] = t[i] ^ key[i];
        std::bitset<32> res;
        for (int i = 0; i < 8; i += 1)
        {
            std::bitset<4> tmp = S(t[i * 6 + 0], t[i * 6 + 1], t[i * 6 + 2], t[i * 6 + 3], t[i * 6 + 4], t[i * 6 + 5], i);
            res[i * 4 + 0] = tmp[0];
            res[i * 4 + 1] = tmp[1];
            res[i * 4 + 2] = tmp[2];
            res[i * 4 + 3] = tmp[3];
        }
        res = P(res);
        return res;
    }

    std::bitset<48> E(const std::bitset<32> &src)
    {
        int i = 31;
        int p = 0;
        int q = 0;
        std::bitset<48> res;
        while (p < 8)
        {
            res[p * 6 + q] = src[i];
            i = (i + 1) % 32;
            q += 1;
            if (q == 6)
            {
                q = 0;
                p += 1;
                i -= 2;
            }
        }
        return res;
    }

    std::bitset<4> S(const bool &a1, const bool &a2, const bool &a3, const bool &a4, const bool &a5, const bool &a6, const int &index)
    {
        std::bitset<4> res;
        int i = a1 * 2 + a6;
        int j = a2 * 8 + a3 * 4 + a4 * 2 + a5;
        res = S_Mat[index][i][j];
        bool t = res[0];
        res[0] = res[3];
        res[3] = t;
        t = res[1];
        res[1] = res[2];
        res[2] = t;
        return res;
    }

    std::bitset<32> P(const std::bitset<32> &src)
    {
        std::bitset<32> res;
        for (int i = 0; i < 32; i += 1)
            res[i] = src[P_Mat[i] - 1];
        return res;
    }

    std::bitset<64> Merge(const std::bitset<32> &L, const std::bitset<32> &R)
    {
        std::bitset<64> res;
        for (int i = 0; i < 32; i += 1)
            res[i] = L[i];
        for (int i = 32; i < 64; i += 1)
            res[i] = R[i - 32];
        return res;
    }
}
