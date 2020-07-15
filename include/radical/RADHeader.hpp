#ifndef __RAD_HEADER__
#define __RAD_HEADER__

#include <cinttypes>

class RADHeader {
    private:

        bool is_paired_{false};
        uint64_t ref_count_{0};
        std::vector<std::string> ref_names;
        uint64_t num_chunks{0};

    public:

        //bool from_file();

        // adds n to the list of reference names and 
        // returns the total number of reference names
        uint64_t add_refname(const std::string& n) {
            ref_names.emplace_back(n);
            ++ref_count_;
            return ref_count_;
        }
        
        
};

#endif // __RAD_HEADER__