#include "rvv_inst_counter.h"

// TODO(gkielian): add to commit reasoning for this
// 1. reuse of the existing tree, speeding up development time and reducing errors
// 2. minimal noise in the translate.c file, allowing ifdefs
// 3. not at the top of the tree, this way we call the function minimally, and do not repeat costlybranching except when wise (see #4).
// decisions
// 4. not too low in the tree, as that would require removing several fallthroughs created, when two operations use teh same gen_helper function.

// 5. put at end of the function, in order to benefit from the instruction
// breaking.

void rvv_opcode_count_v_opivt(DisasContext *dc, uint8_t funct6, int vd, int vs2, TCGv t, uint8_t vm) {
    switch (funct6) {
    // Common for vi and vx
    case RISC_V_FUNCT_ADD:
        env->rvv_opcode_count[VADD_VI] += 1;
        break;
    case RISC_V_FUNCT_RSUB:
        env->rvv_opcode_count[VRSUB_VI] += 1;
        break;
    case RISC_V_FUNCT_AND:
        env->rvv_opcode_count[VAND_VI] += 1;
        break;
    case RISC_V_FUNCT_OR:
        env->rvv_opcode_count[VOR_VI] += 1;
        break;
    case RISC_V_FUNCT_XOR:
        env->rvv_opcode_count[VXOR_VI] += 1;
        break;
    case RISC_V_FUNCT_RGATHER:
        env->rvv_opcode_count[VRGATHER_VI] += 1;
        break;
    case RISC_V_FUNCT_SLIDEUP:
        env->rvv_opcode_count[VSLIDEUP_VI] += 1;
        break;
    case RISC_V_FUNCT_SLIDEDOWN:
        env->rvv_opcode_count[VSLIDEDOWN_VI] += 1;
        break;
    case RISC_V_FUNCT_ADC:
        if (!vm) {
            if (vd) {
              env->rvv_opcode_count[VADC_VIM] += 1;
            }
        }
        break;
    case RISC_V_FUNCT_MADC:
        if (vm) {
            env->rvv_opcode_count[VMADC_VI] += 1;
        } else {
            env->rvv_opcode_count[VMADC_VIM] += 1;
        }
        break;
    case RISC_V_FUNCT_MERGE_MV:
        if (vm) {
            env->rvv_opcode_count[VMV_V_I] += 1;
        } else {
            env->rvv_opcode_count[VMERGE_VIM] += 1;
        }
        break;
    case RISC_V_FUNCT_MSEQ:
        env->rvv_opcode_count[VMSEQ_VI] += 1;
        break;
    case RISC_V_FUNCT_MSNE:
        env->rvv_opcode_count[VMSNE_VI] += 1;
        break;
    case RISC_V_FUNCT_MSLEU:
        env->rvv_opcode_count[VMSLEU_VI] += 1;
        break;
    case RISC_V_FUNCT_MSLE:
        env->rvv_opcode_count[VMSLE_VI] += 1;
        break;
    case RISC_V_FUNCT_MSGTU:
        env->rvv_opcode_count[VMSGTU_VI] += 1;
        break;
    case RISC_V_FUNCT_MSGT:
        env->rvv_opcode_count[VMSGT_VI] += 1;
        break;
    case RISC_V_FUNCT_SADDU:
        env->rvv_opcode_count[VSADDU_VI] += 1;
        break;
    case RISC_V_FUNCT_SADD:
        env->rvv_opcode_count[VSADD_VI] += 1;
        break;
    case RISC_V_FUNCT_SLL:
        env->rvv_opcode_count[VSLL_VI] += 1;
        break;
    case RISC_V_FUNCT_SRL:
        env->rvv_opcode_count[VSRL_VI] += 1;
        break;
    case RISC_V_FUNCT_SRA:
        env->rvv_opcode_count[VSRA_VI] += 1;
        break;
    case RISC_V_FUNCT_SSRL:
        env->rvv_opcode_count[VSSRL_VI] += 1;
        break;
    case RISC_V_FUNCT_SSRA:
        env->rvv_opcode_count[VSSRA_VI] += 1;
        break;
    case RISC_V_FUNCT_NSRL:
        env->rvv_opcode_count[VNSRL_WI] += 1;
        break;
    case RISC_V_FUNCT_NSRA:
        env->rvv_opcode_count[VNSRA_WI] += 1;
        break;
    case RISC_V_FUNCT_NCLIPU:
        env->rvv_opcode_count[VNCLIPU_WI] += 1;
        break;
    case RISC_V_FUNCT_NCLIP:
        env->rvv_opcode_count[VNCLIP_WI] += 1;
        break;
    // defined for vi and reserved for vx
    // reserved for vi and defined for vx
    case RISC_V_FUNCT_SUB:
        env->rvv_opcode_count[VADD_VI] += 1;
        break;
    case RISC_V_FUNCT_MINU:
        env->rvv_opcode_count[VMINU_VX] += 1;
        break;
    case RISC_V_FUNCT_MIN:
        env->rvv_opcode_count[VMIN_VX] += 1;
        break;
    case RISC_V_FUNCT_MAXU:
        env->rvv_opcode_count[VMAXU_VX] += 1;
        break;
    case RISC_V_FUNCT_MAX:
        env->rvv_opcode_count[VMAX_VX] += 1;
        break;
    case RISC_V_FUNCT_SBC:
        if (vm) {
            env->rvv_opcode_count[VSBC_VXM] += 1;
        }
        break;
    case RISC_V_FUNCT_MSBC:
        if (vm) {
            env->rvv_opcode_count[VMSBC_VX] += 1;
        } else {
            env->rvv_opcode_count[VMSBC_VXM] += 1;
        }
        break;
    case RISC_V_FUNCT_MSLTU:
        env->rvv_opcode_count[VMSLTU_VX] += 1;
        break;
    case RISC_V_FUNCT_MSLT:
        env->rvv_opcode_count[VMSLT_VX] += 1;
        break;
    case RISC_V_FUNCT_SSUBU:
        env->rvv_opcode_count[VSSUBU_VX] += 1;
        break;
    case RISC_V_FUNCT_SSUB:
        env->rvv_opcode_count[VSSUB_VX] += 1;
        break;
    default:
        break;
    }

}

void rvv_opcode_count_v_opivv(DisasContext *dc, uint8_t funct6, uint8_t vm) {

        switch (funct6) {
        case RISC_V_FUNCT_ADD:
            env->rvv_opcode_count[VADD_VV] += 1;
            break;
        case RISC_V_FUNCT_SUB:
            env->rvv_opcode_count[VSUB_VV] += 1;
            break;
        case RISC_V_FUNCT_MINU:
            env->rvv_opcode_count[VMINU_VV] += 1;
            break;
        case RISC_V_FUNCT_MIN:
            env->rvv_opcode_count[VMIN_VV] += 1;
            break;
        case RISC_V_FUNCT_MAXU:
            env->rvv_opcode_count[VMAXU_VV] += 1;
            break;
        case RISC_V_FUNCT_MAX:
            env->rvv_opcode_count[VMAX_VV] += 1;
            break;
        case RISC_V_FUNCT_AND:
            env->rvv_opcode_count[VAND_VV] += 1;
            break;
        case RISC_V_FUNCT_OR:
            env->rvv_opcode_count[VOR_VV] += 1;
            break;
        case RISC_V_FUNCT_XOR:
            env->rvv_opcode_count[VXOR_VV] += 1;
            break;
        case RISC_V_FUNCT_RGATHER:
            env->rvv_opcode_count[VRGATHER_VV] += 1;
            break;
        case RISC_V_FUNCT_RGATHEREI16:
            env->rvv_opcode_count[VRGATHEREI16_VV] += 1;
            break;
        case RISC_V_FUNCT_ADC:
            env->rvv_opcode_count[VADC_VVM] += 1;
            break;
        case RISC_V_FUNCT_MADC:
            if (vm) {
                env->rvv_opcode_count[VMADC_VV] += 1;
            } else {
                env->rvv_opcode_count[VMADC_VVM] += 1;
            }
        break;
    case RISC_V_FUNCT_SBC:
        if (vm) {
            env->rvv_opcode_count[VSBC_VVM] += 1;
        }
        break;
    case RISC_V_FUNCT_MSBC:
        if (vm) {
            env->rvv_opcode_count[VMSBC_VV] += 1;
        } else {
            env->rvv_opcode_count[VMSBC_VVM] += 1;
        }
        break;
    case RISC_V_FUNCT_MERGE_MV:
        if (vm) {
            env->rvv_opcode_count[VMV_V_V] += 1;
        } else {
            env->rvv_opcode_count[VMERGE_VVM] += 1;
        }
        break;
    case RISC_V_FUNCT_MSEQ:
        env->rvv_opcode_count[VMSEQ_VV] += 1;
        break;
    case RISC_V_FUNCT_MSNE:
        env->rvv_opcode_count[VMSNE_VV] += 1;
        break;
    case RISC_V_FUNCT_MSLTU:
        env->rvv_opcode_count[VMSLTU_VV] += 1;
        break;
    case RISC_V_FUNCT_MSLT:
        env->rvv_opcode_count[VMSLT_VV] += 1;
        break;
    case RISC_V_FUNCT_MSLEU:
        env->rvv_opcode_count[VMSLEU_VV] += 1;
        break;
    case RISC_V_FUNCT_MSLE:
        env->rvv_opcode_count[VMSLE_VV] += 1;
        break;
    case RISC_V_FUNCT_SADDU:
        env->rvv_opcode_count[VSADDU_VV] += 1;
        break;
    case RISC_V_FUNCT_SADD:
        env->rvv_opcode_count[VSADD_VV] += 1;
        break;
    case RISC_V_FUNCT_SSUBU:
        env->rvv_opcode_count[VSSUBU_VV] += 1;
        break;
    case RISC_V_FUNCT_SSUB:
        env->rvv_opcode_count[VSSUB_VV] += 1;
        break;
    case RISC_V_FUNCT_SLL:
        env->rvv_opcode_count[VSLL_VV] += 1;
        break;
    case RISC_V_FUNCT_SMUL:
        env->rvv_opcode_count[VSMUL_VV] += 1;
        break;
    case RISC_V_FUNCT_SRL:
        env->rvv_opcode_count[VSRL_VV] += 1;
        break;
    case RISC_V_FUNCT_SRA:
        env->rvv_opcode_count[VSRA_VV] += 1;
        break;
    case RISC_V_FUNCT_SSRL:
        env->rvv_opcode_count[VSSRL_VV] += 1;
        break;
    case RISC_V_FUNCT_SSRA:
        env->rvv_opcode_count[VSSRA_VV] += 1;
        break;
    case RISC_V_FUNCT_NSRL:
        env->rvv_opcode_count[VNSRL_WV] += 1;
        break;
    case RISC_V_FUNCT_NSRA:
        env->rvv_opcode_count[VNSRA_WV] += 1;
        break;
    case RISC_V_FUNCT_NCLIPU:
        env->rvv_opcode_count[VNCLIPU_WV] += 1;
        break;
    case RISC_V_FUNCT_NCLIP:
        env->rvv_opcode_count[VNCLIP_WV] += 1;
        break;
    case RISC_V_FUNCT_WREDSUMU:
        env->rvv_opcode_count[VWREDSUMU_VS] += 1;
        break;
    case RISC_V_FUNCT_WREDSUM:
        env->rvv_opcode_count[VWREDSUM_VS] += 1;
        break;
    default:
        break;
    }
}

void rvv_opcode_count_v_cfg(DisasContext *dc, uint32_t opc) {
    switch (opc) {
        case OPC_RISC_VSETVL:
            env->rvv_opcode_count[VSETVL] += 1;
            break;
        case OPC_RISC_VSETVLI_0:
            env->rvv_opcode_count[VSETVLI] += 1;
            break;
        case OPC_RISC_VSETVLI_1:
            env->rvv_opcode_count[VSETVLI] += 1;
            break;
        case OPC_RISC_VSETIVLI:
            env->rvv_opcode_count[VSETIVLI] += 1;
            break;
        default:
            break;
    }
}

void rvv_opcode_count_v_load(CPUState* env, DisasContext *dc, uint32_t opc, uint32_t vm, uint32_t mew, uint32_t nf, uint32_t width) {

  switch(opc) {
    case OPC_RISC_VL_US: // unit-stride
        switch (MASK_OP_V_LOAD_US(dc->opcode)) {
        case OPC_RISC_VL_US:
            switch (width & 0x3) {
            case 0:
                env->rvv_opcode_count[VLE8_V] += 1;
                break;
            case 1:
                env->rvv_opcode_count[VLE16_V] += 1;
                break;
            case 2:
                env->rvv_opcode_count[VLE32_V] += 1;
                break;
            case 3:
                env->rvv_opcode_count[VLE64_V] += 1;
                break;
            }
            break;
        case OPC_RISC_VL_US_FOF:
            switch (width & 0x3) {
            case 0:
                env->rvv_opcode_count[VLE8FF_V] += 1;
                break;
            case 1:
                env->rvv_opcode_count[VLE16FF_V] += 1;
                break;
            case 2:
                env->rvv_opcode_count[VLE32FF_V] += 1;
                break;
            case 3:
                env->rvv_opcode_count[VLE64FF_V] += 1;
                break;
            }
            break;
        }
        break;
    case OPC_RISC_VL_VS: // vector-strided
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VLSE8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VLSE16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VLSE32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VLSE64_V] += 1;
            break;
        }
        break;
    case OPC_RISC_VL_UVI: // unordered vector-indexed
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VLUXEI8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VLUXEI16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VLUXEI32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VLUXEI64_V] += 1;
            break;
        }
        break;
    case OPC_RISC_VL_OVI: // ordered vector-indexed
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VLOXEI8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VLOXEI16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VLOXEI32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VLOXEI64_V] += 1;
            break;
        }
        break;
    default:
        break;
  }
}

void rvv_opcode_count_v_store(DisasContext *dc, uint32_t opc, uint32_t rest, uint32_t width) {

    switch (opc) {
    case OPC_RISC_VS_US: // unit-stride
        switch (MASK_OP_V_STORE_US(dc->opcode)) {
        case OPC_RISC_VS_US:
            switch (width & 0x3) {
            case 0:
                env->rvv_opcode_count[VSE8_V] += 1;
                break;
            case 1:
                env->rvv_opcode_count[VSE16_V] += 1;
                break;
            case 2:
                env->rvv_opcode_count[VSE32_V] += 1;
                break;
            case 3:
                env->rvv_opcode_count[VSE64_V] += 1;
                break;
            }
            break;
        default:
            break;
        }
        break;
    case OPC_RISC_VS_VS: // vector-strided
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VSSE8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VSSE16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VSSE32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VSSE64_V] += 1;
            break;
        }
        break;
    case OPC_RISC_VS_UVI: // unordered vector-indexed
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VSUXEI8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VSUXEI16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VSUXEI32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VSUXEI64_V] += 1;
            break;
        }
        break;
    case OPC_RISC_VS_OVI: // ordered vector-indexed
        switch (width & 0x3) {
        case 0:
            env->rvv_opcode_count[VSOXEI8_V] += 1;
            break;
        case 1:
            env->rvv_opcode_count[VSOXEI16_V] += 1;
            break;
        case 2:
            env->rvv_opcode_count[VSOXEI32_V] += 1;
            break;
        case 3:
            env->rvv_opcode_count[VSOXEI64_V] += 1;
            break;
        }
        break;
    default:
        break;
    }
}
