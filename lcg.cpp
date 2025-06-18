#include <iostream>

const uint64_t a = 25214903917;
const uint64_t c = 11;
const uint64_t m = (1ULL << 48) - 1;
/*
xn + 1  = (a * xn + c) mod m
xn + 1 = (a * xn + c) & m
*/

int main(int argc , char ** argv)
{
    int32_t output1 = std::stoi(argv[1]); // xn is supposed to be 48 bits , this is 32 
    int32_t output2 = std::stoi(argv[2]); // xn+1

    // we need to find the lower 16 bits
    for (int lower_bits = 0 ; lower_bits < (1 << 16) ; lower_bits++)
    {
        // xN = output1 << 16 | lower_bits
        uint64_t xN = ((uint64_t)(uint32_t)output1 << 16) | lower_bits;
        uint64_t xN_1 = (a * xN + c) & m;
        int32_t next_prediction = (int32_t)(xN_1 >> 16);
        if (next_prediction == output2)
        {
            std::cout << "Seed value found : " << xN << std::endl;
            // print out the next 100 random numbers : 
            for (int i = 0 ; i < 100 ; i++)
            {
                xN = (a * xN + c) & m;
                int32_t predicted_random_number = xN >> 16;
                std::cout << i + 1 << ") " << predicted_random_number << std::endl;
                
            }
        }
    }

    return 0;
    // seed value is 48 bits
    // randInt() returns a random integer : 32 bits
    // 48 - 32 = 16
    // (int32_t) (xn_1 >> 16)
}