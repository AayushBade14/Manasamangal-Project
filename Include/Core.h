#ifndef MANASA_CORE_H
#define MANASA_CORE_H
//--------------------------------------------------------------------
//  
//  Name: Core.h
//
//  Desc: Includes all the common necessary includes for the engine to function
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//--------------------------------------------------------------------

//standard libs
#include <cstdint>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <unordered_map>

//================================[ENGINE-TYPES]========================================
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

using real = f32;

//================================[ERROR-HANDLING]======================================
struct MError{
  bool m_bSuccess;
  std::string m_sMsg;
  
  static MError Ok(const std::string& msg)
  {
    return {true, msg};
  }

  static MError Fail(const std::string& msg)
  {
    return {false, msg};
  }
};

#endif
