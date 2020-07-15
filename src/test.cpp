#include "radical/BasicBinWriter.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cmath>

int main(int argc, char* argv[]) {

    BasicBinWriter bw;
    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::default_random_engine e2(r());
    std::default_random_engine e3(r());
    std::default_random_engine e4(r());

    std::uniform_int_distribution<uint32_t> uniform_dist(1, 6);
    std::uniform_int_distribution<uint16_t> tag1_dist(1, 65535);
    std::uniform_int_distribution<uint16_t> tag2_dist(1, 65535);
    std::uniform_int_distribution<uint32_t> refid_dist(1, 250000);

    constexpr const uint16_t rl{100};
    constexpr const uint8_t fw{0};
    // create some data 
    for (size_t i = 0; i < 500; ++i) {
        // num alignments for this read 
        auto na = uniform_dist(e1);
        auto t1 = tag1_dist(e2);
        auto t2 = tag2_dist(e3);

        bw << na;
        bw << rl;
        // for each alignment
        for (uint32_t j = 0; j < na; ++j) {
            auto rid = refid_dist(e4);
            constexpr const uint32_t p = 0;
            bw << rid;
            // 
            bw << fw;
            bw << p;
        }
        // tags
        bw << t1;
        bw << t2;
    }

    std::cout << bw;
    return 0;
}