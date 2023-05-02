#ifndef BENCHMARKING_TOY_CODES_MY_CPUID_H
#define BENCHMARKING_TOY_CODES_MY_CPUID_H
#include <iostream>
#include <string>

// NIKOS from https://stackoverflow.com/questions/1666093/cpuid-implementations-in-c
#ifdef _WIN32
#include <intrin.h>
#include <limits.h>
typedef unsigned __int32 uint32_t;
#else
#include <cstdint>
#endif
class MY_CPUID {
  uint32_t regs[4] = {0};

  public:
  explicit MY_CPUID(unsigned i) {
#ifdef _WIN32
    __cpuid((int *)regs, (int)i);
//                _asm
//                {
//                  cpuid;
//                  mov regs[0], ebx;
//                  mov regs[4], edx;
//                  mov regs[8], ecx;
//                }
//                return string((const char*)data);
#else
    asm volatile("cpuid" : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3]) : "a"(i), "c"(0));
    // ECX is set to zero for MY_CPUID function 4
#endif
  }
  const uint32_t &EAX() const { return regs[0]; }
  const uint32_t &EBX() const { return regs[1]; }
  const uint32_t &ECX() const { return regs[2]; }
  const uint32_t &EDX() const { return regs[3]; }
};
#endif
