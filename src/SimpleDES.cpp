#include <iostream>

#include "../include/DESAlgorithm"
#include "../include/Init_Perm"

int main()
{
    unsigned long long key = 2084160214307458188ll;
    unsigned long long msg = -1410563274867700724ll;
    std::bitset<64> m = msg;
    std::cout << "message: " << m << std::endl;
    ptc::SubKey k[16];
    ptc::SubKeyGen(key, k);
    std::bitset<64> t = ptc::Init_Perm(m);
    std::bitset<32> L, R;
    ptc::Split(t, L, R);
    for (int i = 0; i < 16; i += 1)
        ptc::Round(L, R, k[i]);
    t = ptc::Merge(R, L);
    std::bitset<64> res = ptc::Inv_Init_Perm(t);
    std::cout << "result: " << res << std::endl;
    for (int i = 0; i < 16; i += 1)
        std::cout << "key " << i + 1 << ": " << k[i] << std::endl;
    return 0;
}
