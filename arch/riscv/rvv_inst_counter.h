#ifndef RVV_INST_COUNTER_H_
#define RVV_INST_COUNTER_H_

#include "cpu.h"
#include "rvv_opcode_map.h"
#include "instmap.h"

void rvv_opcode_sieve(CPUState *env, uint32_t full_opcode, uint32_t op, uint32_t rm);
void rvv_opcode_counter(CPUState *env, uint32_t opcode);

#endif  // RVV_INST_COUNTER_H_
