#include "../include/Init_Perm"
#include "../include/Constant"

namespace ptc
{
    std::bitset<64> Init_Perm(const std::bitset<64> &src)
    {
        std::bitset<64> res;
        for (int i = 0; i < 64; i += 1)
            res[i] = src[Init_Perm_Mat[i] - 1];
        return res;
    }
    
    std::bitset<64> Inv_Init_Perm(const std::bitset<64> &src)
    {
        std::bitset<64> res;
        for (int i = 0; i < 64; i += 1)
            res[i] = src[Inv_Init_Perm_Mat[i] - 1];
        return res;
    }
}
