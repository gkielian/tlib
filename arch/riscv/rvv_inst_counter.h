#ifndef RVV_INSTRUCTION_COUNTER_H_
#define RVV_INSTRUCTION_COUNTER_H_

#include <stdint.h>

#include "arch_callbacks.h"
#include "cpu.h"
#include "debug.h"
#include "instmap.h"
#include "rvv_opcode_map.h"

void rvv_opcode_count_v_opivt(DisasContext *dc, uint8_t funct6, int vd, int vs2,
                              TCGv t, uint8_t vm);

void rvv_opcode_count_v_opivv(DisasContext *dc, uint8_t funct6, uint8_t vm);

void rvv_opcode_count_v_cfg(DisasContext *dc, uint32_t opc);

void rvv_opcode_count_v_load(CPUState *env, DisasContext *dc, uint32_t opc,
                             uint32_t vm, uint32_t mew, uint32_t nf,
                             uint32_t width);

void rvv_opcode_count_v_store(DisasContext *dc, uint32_t opc, uint32_t rest,
                              uint32_t width);

#endif  // RVV_INSTRUCTION_COUNTER_H_
