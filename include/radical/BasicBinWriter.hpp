#ifndef __BASIC_BIN_WRITER__
#define __BASIC_BIN_WRITER__

#include <vector>
#include <algorithm>
#include <iostream>

/**
 * low-level interface for writing information direclty into a binary 
 * stream (vector of char).
 */
class BasicBinWriter {
private:
  std::vector<char> _bin_data;

public:
  BasicBinWriter(){};
  BasicBinWriter(size_t reserve_size) { _bin_data.reserve(reserve_size); }
  // copy bin data to this record
  BasicBinWriter(const std::vector<char>& bin_data) : _bin_data(bin_data){};
  // or just move if possible
  BasicBinWriter(std::vector<char>&& bin_data) : _bin_data(move(bin_data)){};

  void clear() { _bin_data.clear(); }

  BasicBinWriter& operator<<(const bool& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const uint8_t& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const uint16_t& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const uint32_t& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const uint64_t& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const int32_t& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }

  BasicBinWriter& operator<<(const double& inval) {
    char* inCharPtr = const_cast<char*>(reinterpret_cast<const char*>(&inval));
    std::copy(inCharPtr, inCharPtr + sizeof(inval),
              std::back_inserter(_bin_data));
    return *this;
  }
  BasicBinWriter& operator<<(const std::string& inval) {
    if (inval.size() >= 0x100) {
      std::cerr << "ERROR!! DOESN'T SUPPORT STRING LENGTH LONGER THAN 255. "
                   "String length: "
                << inval.size() << "\n";
      std::exit(1);
    }
    char tmp = static_cast<uint8_t>(inval.size());
    _bin_data.push_back(tmp);
    //(*this) << inval.size();
    // std::cout << inval.size() << " " << inval.c_str()  << " " << inval <<
    // "\n";
    char* inCharPtr = const_cast<char*>(inval.c_str());
    std::copy(inCharPtr, inCharPtr + inval.size(),
              std::back_inserter(_bin_data));
    return *this;
  }
  /*
  BasicBinWriter& operator<<(const stx::string_view& inval) {
    if (inval.size() >= 0x100) {
      std::cerr << "ERROR!! DOESN'T SUPPORT STRING LENGTH LONGER THAN 255. "
                   "String length: "
                << inval.size() << "\n";
      std::exit(1);
    }
    char tmp = static_cast<uint8_t>(inval.size());
    _bin_data.push_back(tmp);
    //(*this) << inval.size();
    // std::cout << inval.size() << " " << inval.data()  << " " << inval <<
    // "\n";
    char* inCharPtr = const_cast<char*>(inval.data());
    std::copy(inCharPtr, inCharPtr + inval.size(),
              std::back_inserter(_bin_data));
    return *this;
  }
  */
 
  uint64_t num_bytes() { return _bin_data.size(); }

  // support for logging directly from spdlog
  template <typename OStream>
  friend OStream& operator<<(OStream& os, const BasicBinWriter& bin_record) {
    std::ostream_iterator<char> out_iter(os);
    std::copy(bin_record._bin_data.begin(), bin_record._bin_data.end(),
              out_iter);
    return os;
  }
};

#endif //__BASIC_BIN_WRITER__