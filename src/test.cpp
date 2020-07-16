
#include "radicl/BasicBinWriter.hpp"
#include "radicl/RADHeader.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cmath>

int main(int argc, char* argv[]) {

    BasicBinWriter bw;
    RADHeader rh;

    rh.is_paired(false);
    rh.add_refname("foo");
    rh.add_refname("is");
    rh.add_refname("bar");
    rh.add_refname("ENSMUST00000178348.1");
    rh.add_refname("hey ho");
    rh.add_refname("what do you say");

    rh.dump_to_bin(bw);

    size_t num_chunk_offset = bw.num_bytes() - sizeof(uint64_t);

    // write the header
    std::cout << bw;
    bw.clear();


    // write the tag meta-information section
    uint16_t file_level_tags{2};
    bw << file_level_tags;

    // cblen
    uint8_t type_id{2};
    bw << std::string("cblen");
    bw << type_id;

    bw << std::string("ulen");
    bw << type_id;

    uint16_t read_level_tags{2};
    bw << read_level_tags;
    bw << std::string("b");
    bw << type_id;
    bw << std::string("u");
    bw << type_id;

    uint16_t aln_level_tags{0};
    /*
    bw << aln_level_tags;
    bw << std::string("refid");
    type_id = 
    bw << type_id;
    */

    std::cout << bw;
    bw.clear();

    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(1);//r());
    std::default_random_engine e2(2);//r());
    std::default_random_engine e3(3);//r());
    std::default_random_engine e4(4);//r());

    std::uniform_int_distribution<uint32_t> uniform_dist(1, 6);
    std::uniform_int_distribution<uint16_t> tag1_dist(1, 65535);
    std::uniform_int_distribution<uint16_t> tag2_dist(1, 65535);
    std::uniform_int_distribution<uint32_t> refid_dist(1, 250000);

    constexpr const uint16_t rl{100};
    constexpr const uint8_t fw{0};
   
    uint32_t nr{0};
    uint32_t nb{0};
   
    // reseve space to fill in # of bytes and # of records later.
    bw << nb << nr;

    nr = 0;
    nb = 0;

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
        ++nr;
    }

    nb = static_cast<uint32_t>(bw.num_bytes());
    bw.write_integer_at_offset(0, nb);
    bw.write_integer_at_offset(sizeof(nb), nr);    

    std::cout << bw;
    return 0;
}