#pragma once

#include "sail.h"
#include "sail_config.h"
#include "rts.h"
#include "elf.h"
#include "riscv_platform_if.h"
extern void (*sail_rts_set_coverage_file)(const char *);

namespace hart {
// enum zvk_vsm4r_funct6
enum zzzvk_vsm4r_funct6 : int { zZVK_VSM4R_VV, zZVK_VSM4R_VS };

// enum zvk_vsha2_funct6
enum zzzvk_vsha2_funct6 : int { zZVK_VSHA2CH_VV, zZVK_VSHA2CL_VV };

// enum zvk_vaesem_funct6
enum zzzvk_vaesem_funct6 : int { zZVK_VAESEM_VV, zZVK_VAESEM_VS };

// enum zvk_vaesef_funct6
enum zzzvk_vaesef_funct6 : int { zZVK_VAESEF_VV, zZVK_VAESEF_VS };

// enum zvk_vaesdm_funct6
enum zzzvk_vaesdm_funct6 : int { zZVK_VAESDM_VV, zZVK_VAESDM_VS };

// enum zvk_vaesdf_funct6
enum zzzvk_vaesdf_funct6 : int { zZVK_VAESDF_VV, zZVK_VAESDF_VS };

// enum zvabd_vwabda_func6
enum zzzvabd_vwabda_func6 : int { zVWABDA, zVWABDAU };

// enum zvabd_vabd_func6
enum zzzvabd_vabd_func6 : int { zVABD, zVABDU };

// enum zilx_mode
enum zzzilx_mode : int { zZILX_UNSCALED, zZILX_SCALED, zZILX_SCALED_UW };

// enum zicondop
enum zzzicondop : int { zCZERO_EQZ, zCZERO_NEZ };

// type abbreviation xlenbits
typedef sbits zxlenbits;

// enum xRET_type
enum zxRET_type : int { zmRET, zsRET };

// enum wxfunct6
enum zwxfunct6 : int { zWX_VADD, zWX_VSUB, zWX_VADDU, zWX_VSUBU };

// enum wvxfunct6
enum zwvxfunct6 : int { zWVX_VADD, zWVX_VSUB, zWVX_VADDU, zWVX_VSUBU, zWVX_VWMUL, zWVX_VWMULU, zWVX_VWMULSU };

// enum wvvfunct6
enum zwvvfunct6 : int { zWVV_VADD, zWVV_VSUB, zWVV_VADDU, zWVV_VSUBU, zWVV_VWMUL, zWVV_VWMULU, zWVV_VWMULSU };

// enum wvfunct6
enum zwvfunct6 : int { zWV_VADD, zWV_VSUB, zWV_VADDU, zWV_VSUBU };

// enum wrsop
enum zwrsop : int { zWRS_STO, zWRS_NTO };

// enum write_kind
enum zwrite_kind : int { zWrite_plain, zWrite_RISCV_release, zWrite_RISCV_strong_release, zWrite_RISCV_conditional, zWrite_RISCV_conditional_release, zWrite_RISCV_conditional_strong_release };

// type abbreviation word_width_wide
typedef int64_t zword_width_wide;

// type abbreviation word_width
typedef int64_t zword_width;

// type abbreviation word
typedef uint64_t zword;

// enum wmvxfunct6
enum zwmvxfunct6 : int { zWMVX_VWMACCU, zWMVX_VWMACC, zWMVX_VWMACCUS, zWMVX_VWMACCSU };

// enum wmvvfunct6
enum zwmvvfunct6 : int { zWMVV_VWMACCU, zWMVV_VWMACC, zWMVV_VWMACCSU };

// enum vxsgfunct6
enum zvxsgfunct6 : int { zVX_VSLIDEUP, zVX_VSLIDEDOWN, zVX_VRGATHER };

// enum vxmsfunct6
enum zvxmsfunct6 : int { zVXMS_VADC, zVXMS_VSBC };

// enum vxmfunct6
enum zvxmfunct6 : int { zVXM_VMADC, zVXM_VMSBC };

// enum vxmcfunct6
enum zvxmcfunct6 : int { zVXMC_VMADC, zVXMC_VMSBC };

// enum vxfunct6
enum zvxfunct6 : int { zVX_VADD, zVX_VSUB, zVX_VRSUB, zVX_VMINU, zVX_VMIN, zVX_VMAXU, zVX_VMAX, zVX_VAND, zVX_VOR, zVX_VXOR, zVX_VSADDU, zVX_VSADD, zVX_VSSUBU, zVX_VSSUB, zVX_VSLL, zVX_VSMUL, zVX_VSRL, zVX_VSRA, zVX_VSSRL, zVX_VSSRA };

// enum vxcmpfunct6
enum zvxcmpfunct6 : int { zVXCMP_VMSEQ, zVXCMP_VMSNE, zVXCMP_VMSLTU, zVXCMP_VMSLT, zVXCMP_VMSLEU, zVXCMP_VMSLE, zVXCMP_VMSGTU, zVXCMP_VMSGT };

// enum vvmsfunct6
enum zvvmsfunct6 : int { zVVMS_VADC, zVVMS_VSBC };

// enum vvmfunct6
enum zvvmfunct6 : int { zVVM_VMADC, zVVM_VMSBC };

// enum vvmcfunct6
enum zvvmcfunct6 : int { zVVMC_VMADC, zVVMC_VMSBC };

// enum vvfunct6
enum zvvfunct6 : int { zVV_VADD, zVV_VSUB, zVV_VMINU, zVV_VMIN, zVV_VMAXU, zVV_VMAX, zVV_VAND, zVV_VOR, zVV_VXOR, zVV_VRGATHER, zVV_VRGATHEREI16, zVV_VSADDU, zVV_VSADD, zVV_VSSUBU, zVV_VSSUB, zVV_VSLL, zVV_VSMUL, zVV_VSRL, zVV_VSRA, zVV_VSSRL, zVV_VSSRA };

// enum vvcmpfunct6
enum zvvcmpfunct6 : int { zVVCMP_VMSEQ, zVVCMP_VMSNE, zVVCMP_VMSLTU, zVVCMP_VMSLT, zVVCMP_VMSLEU, zVVCMP_VMSLE };

// enum vstart_class
enum zvstart_class : int { zVSTART_ARITH, zVSTART_LOAD_STORE, zVSTART_SCALAR_MOVE, zVSTART_MANDATORY };

// union vregno
enum kind_zvregno { Kind_zVregno };

struct zvregno {
  enum kind_zvregno kind;
  union {struct { int64_t zVregno; };} variants;
};

// union vregidx
enum kind_zvregidx { Kind_zVregidx };

struct zvregidx {
  enum kind_zvregidx kind;
  union {struct { uint64_t zVregidx; };} variants;
};

// type abbreviation vpn_bits
typedef sbits zvpn_bits;

// enum vmlsop
enum zvmlsop : int { zVLM, zVSM };

// type abbreviation vmidbits
typedef sbits zvmidbits;

// enum vlewidth
enum zvlewidth : int { zVLE8, zVLE16, zVLE32, zVLE64 };

// type abbreviation vlenbits
typedef lbits zvlenbits;

// enum visgfunct6
enum zvisgfunct6 : int { zVI_VSLIDEUP, zVI_VSLIDEDOWN, zVI_VRGATHER };

// union virtaddr
enum kind_zvirtaddr { Kind_zVirtaddr };

struct zvirtaddr {
  enum kind_zvirtaddr kind;
  union {struct { sbits zVirtaddr; };} variants;
};

// enum vimsfunct6
enum zvimsfunct6 : int { zVIMS_VADC };

// enum vimfunct6
enum zvimfunct6 : int { zVIM_VMADC };

// enum vimcfunct6
enum zvimcfunct6 : int { zVIMC_VMADC };

// enum vifunct6
enum zvifunct6 : int { zVI_VADD, zVI_VRSUB, zVI_VAND, zVI_VOR, zVI_VXOR, zVI_VSADDU, zVI_VSADD, zVI_VSLL, zVI_VSRL, zVI_VSRA, zVI_VSSRL, zVI_VSSRA };

// enum vicmpfunct6
enum zvicmpfunct6 : int { zVICMP_VMSEQ, zVICMP_VMSNE, zVICMP_VMSLEU, zVICMP_VMSLE, zVICMP_VMSGTU, zVICMP_VMSGT };

// enum vfwunary0
enum zvfwunary0 : int { zFWV_CVT_XU_F, zFWV_CVT_X_F, zFWV_CVT_F_XU, zFWV_CVT_F_X, zFWV_CVT_F_F, zFWV_CVT_RTZ_XU_F, zFWV_CVT_RTZ_X_F };

// enum vfunary1
enum zvfunary1 : int { zFVV_VSQRT, zFVV_VRSQRT7, zFVV_VREC7, zFVV_VCLASS };

// enum vfunary0
enum zvfunary0 : int { zFV_CVT_XU_F, zFV_CVT_X_F, zFV_CVT_F_XU, zFV_CVT_F_X, zFV_CVT_RTZ_XU_F, zFV_CVT_RTZ_X_F };

// enum vfnunary0
enum zvfnunary0 : int { zFNV_CVT_XU_F, zFNV_CVT_X_F, zFNV_CVT_F_XU, zFNV_CVT_F_X, zFNV_CVT_F_F, zFNV_CVT_ROD_F_F, zFNV_CVT_RTZ_XU_F, zFNV_CVT_RTZ_X_F };

// enum vextfunct6
enum zvextfunct6 : int { zVEXT2_ZVF2, zVEXT2_SVF2, zVEXT4_ZVF4, zVEXT4_SVF4, zVEXT8_ZVF8, zVEXT8_SVF8 };

// enum vector_support
enum zvector_support : int { zDisabled, zInteger, zFloat_single, zFloat_double, zFull };

// enum uop
enum zuop : int { zLUI, zAUIPC };

// type abbreviation tvec_alignment
typedef int64_t ztvec_alignment;

// type abbreviation trigger_index
typedef int64_t ztrigger_index;

// enum trigger_addr_type
enum ztrigger_addr_type : int { zTriggerAddress_Load, zTriggerAddress_Store, zTriggerAddress_AMO };

// type abbreviation tlb_index_range
typedef int64_t ztlb_index_range;

// enum tdata
enum ztdata : int { zTDATA1, zTDATA2, zTDATA3 };

// enum stateen_bit
enum zstateen_bit : int { zSTATEEN_FCSR, zSTATEEN_SRMCFG, zSTATEEN_P1P13, zSTATEEN_CONTEXT, zSTATEEN_ENVCFG, zSTATEEN_SE };

// enum sopw
enum zsopw : int { zSLLIW, zSRLIW, zSRAIW };

// enum sop
enum zsop : int { zSLLI, zSRLI, zSRAI };

// type abbreviation shamt_zba
typedef uint64_t zshamt_zzba;

// type abbreviation sew_bitsize
typedef int64_t zsew_bitsizze;

// enum seed_opst
enum zseed_opst : int { zBIST, zES16, zWAIT, zDEAD };

// type abbreviation satp_mode
typedef uint64_t zsatp_mode;

// enum rounding_mode
enum zrounding_mode : int { zRM_RNE, zRM_RTZ, zRM_RDN, zRM_RUP, zRM_RMM, zRM_DYN };

// enum ropw
enum zropw : int { zADDW, zSUBW, zSLLW, zSRLW, zSRAW };

// enum rop
enum zrop : int { zADD, zSUB, zSLL, zSLT, zSLTU, zXOR, zSRL, zSRA, zOR, zAND };

// enum rmvvfunct6
enum zrmvvfunct6 : int { zMVV_VREDSUM, zMVV_VREDAND, zMVV_VREDOR, zMVV_VREDXOR, zMVV_VREDMINU, zMVV_VREDMIN, zMVV_VREDMAXU, zMVV_VREDMAX };

// enum rivvfunct6
enum zrivvfunct6 : int { zIVV_VWREDSUMU, zIVV_VWREDSUM };

// enum rfwvvfunct6
enum zrfwvvfunct6 : int { zFVV_VFWREDOSUM, zFVV_VFWREDUSUM };

// enum rfvvfunct6
enum zrfvvfunct6 : int { zFVV_VFREDOSUM, zFVV_VFREDUSUM, zFVV_VFREDMAX, zFVV_VFREDMIN };

// union result<u,u>
enum kind_zresultzIuzCuzK { Kind_zErrzIuzCuzK, Kind_zOkzIuzCuzK };

struct zresultzIuzCuzK {
  enum kind_zresultzIuzCuzK kind;
  union {
    struct { unit zErrzIuzCuzK; };
    struct { unit zOkzIuzCuzK; };
  } variants;
};

// union result<b,u>
enum kind_zresultzIbzCuzK { Kind_zErrzIbzCuzK, Kind_zOkzIbzCuzK };

struct zresultzIbzCuzK {
  enum kind_zresultzIbzCuzK kind;
  union {
    struct { unit zErrzIbzCuzK; };
    struct { lbits zOkzIbzCuzK; };
  } variants;
};

struct zz5vecz8z5bvz9 {
  size_t len;
  lbits *data;
};
typedef struct zz5vecz8z5bvz9 zz5vecz8z5bvz9;

struct zz5vecz8z5boolz9 {
  size_t len;
  bool *data;
};
typedef struct zz5vecz8z5boolz9 zz5vecz8z5boolz9;

// struct tuple_(%vec(%bv), %vec(%bool))
struct ztuple_z8z5vecz8z5bvz9zCz0z5vecz8z5boolz9z9 {
  zz5vecz8z5bvz9 ztup0;
  zz5vecz8z5boolz9 ztup1;
};

// union result<(Vb,Vo),u>
enum kind_zresultzIz8VbzCVoz9zCuzK { Kind_zErrzIz8VbzCVoz9zCuzK, Kind_zOkzIz8VbzCVoz9zCuzK };

struct zresultzIz8VbzCVoz9zCuzK {
  enum kind_zresultzIz8VbzCVoz9zCuzK kind;
  union {
    struct { unit zErrzIz8VbzCVoz9zCuzK; };
    struct { struct ztuple_z8z5vecz8z5bvz9zCz0z5vecz8z5boolz9z9 zOkzIz8VbzCVoz9zCuzK; };
  } variants;
};

// type abbreviation regtype
typedef sbits zregtype;

// union regno
enum kind_zregno { Kind_zRegno };

struct zregno {
  enum kind_zregno kind;
  union {struct { int64_t zRegno; };} variants;
};

// union regidx
enum kind_zregidx { Kind_zRegidx };

struct zregidx {
  enum kind_zregidx kind;
  union {struct { sbits zRegidx; };} variants;
};

// enum read_kind
enum zread_kind : int { zRead_plain, zRead_ifetch, zRead_RISCV_acquire, zRead_RISCV_strong_acquire, zRead_RISCV_reserved, zRead_RISCV_reserved_acquire, zRead_RISCV_reserved_strong_acquire };

// type abbreviation pte_ext_bits
typedef uint64_t zpte_ext_bits;

// union pte_check_failure
enum kind_zpte_check_failure { Kind_zPTE_Ext_Failure, Kind_zPTE_No_Access, Kind_zPTE_No_Permission };

struct zpte_check_failure {
  enum kind_zpte_check_failure kind;
  union {
    struct { unit zPTE_Ext_Failure; };
    struct { unit zPTE_No_Access; };
    struct { unit zPTE_No_Permission; };
  } variants;
};

// type abbreviation pte_bits
typedef sbits zpte_bits;

// type abbreviation ppn_bits
typedef sbits zppn_bits;

// enum pmpAddrMatch
enum zpmpAddrMatch : int { zPMP_NoMatch, zPMP_PartialMatch, zPMP_Match };

// struct pma_check_opts
struct zpma_check_opts {
  bool zssccptr;
  bool zsvadu;
  bool zzzama16b;
  bool zzziccamoa;
  bool zzziccamoc;
  bool zzziccif;
  bool zzzicclsm;
  bool zzziccrse;
};

// type abbreviation pm_len
typedef int64_t zpm_len;

// type abbreviation physaddrbits
typedef sbits zphysaddrbits;

// union physaddr
enum kind_zphysaddr { Kind_zPhysaddr };

struct zphysaddr {
  enum kind_zphysaddr kind;
  union {struct { sbits zPhysaddr; };} variants;
};

// enum page_based_mem_type
enum zpage_based_mem_type : int { zPBMT_PMA, zPBMT_NC, zPBMT_IO };

// union option<u>
enum kind_zoptionzIuzK { Kind_zNonezIuzK, Kind_zSomezIuzK };

struct zoptionzIuzK {
  enum kind_zoptionzIuzK kind;
  union {
    struct { unit zNonezIuzK; };
    struct { unit zSomezIuzK; };
  } variants;
};

// union option<s>
enum kind_zoptionzIszK { Kind_zNonezIszK, Kind_zSomezIszK };

struct zoptionzIszK {
  enum kind_zoptionzIszK kind;
  union {
    struct { unit zNonezIszK; };
    struct { sail_string zSomezIszK; };
  } variants;
};

// union option<o>
enum kind_zoptionzIozK { Kind_zNonezIozK, Kind_zSomezIozK };

struct zoptionzIozK {
  enum kind_zoptionzIozK kind;
  union {
    struct { unit zNonezIozK; };
    struct { bool zSomezIozK; };
  } variants;
};

// union option<i>
enum kind_zoptionzIizK { Kind_zNonezIizK, Kind_zSomezIizK };

struct zoptionzIizK {
  enum kind_zoptionzIizK kind;
  union {
    struct { unit zNonezIizK; };
    struct { sail_int zSomezIizK; };
  } variants;
};

// union option<b>
enum kind_zoptionzIbzK { Kind_zNonezIbzK, Kind_zSomezIbzK };

struct zoptionzIbzK {
  enum kind_zoptionzIbzK kind;
  union {
    struct { unit zNonezIbzK; };
    struct { lbits zSomezIbzK; };
  } variants;
};

// union option<Erounding_mode%>
enum kind_zoptionzIErounding_modez5zK { Kind_zNonezIErounding_modez5zK, Kind_zSomezIErounding_modez5zK };

struct zoptionzIErounding_modez5zK {
  enum kind_zoptionzIErounding_modez5zK kind;
  union {
    struct { unit zNonezIErounding_modez5zK; };
    struct { enum zrounding_mode zSomezIErounding_modez5zK; };
  } variants;
};

// struct tuple_(%i, %enum ztdata)
struct ztuple_z8z5izCz0z5enumz0zztdataz9 {
  sail_int ztup0;
  enum ztdata ztup1;
};

// union option<(i,Etdata%)>
enum kind_zoptionzIz8izCEtdataz5z9zK { Kind_zNonezIz8izCEtdataz5z9zK, Kind_zSomezIz8izCEtdataz5z9zK };

struct zoptionzIz8izCEtdataz5z9zK {
  enum kind_zoptionzIz8izCEtdataz5z9zK kind;
  union {
    struct { unit zNonezIz8izCEtdataz5z9zK; };
    struct { struct ztuple_z8z5izCz0z5enumz0zztdataz9 zSomezIz8izCEtdataz5z9zK; };
  } variants;
};

// enum nxsfunct6
enum znxsfunct6 : int { zNXS_VNSRL, zNXS_VNSRA };

// enum nxfunct6
enum znxfunct6 : int { zNX_VNCLIPU, zNX_VNCLIP };

// enum nvsfunct6
enum znvsfunct6 : int { zNVS_VNSRL, zNVS_VNSRA };

// enum nvfunct6
enum znvfunct6 : int { zNV_VNCLIPU, zNV_VNCLIP };

// enum ntl_type
enum zntl_type : int { zNTL_P1, zNTL_PALL, zNTL_S1, zNTL_ALL };

// type abbreviation nom_priv_bits
typedef uint64_t znom_priv_bits;

// enum nisfunct6
enum znisfunct6 : int { zNIS_VNSRL, zNIS_VNSRA };

// enum nifunct6
enum znifunct6 : int { zNI_VNCLIPU, zNI_VNCLIP };

// type abbreviation nfields_pow2
typedef int64_t znfields_pow2;

// type abbreviation nfields
typedef int64_t znfields;

// type abbreviation nat1
typedef sail_int znat1;

// enum mvxmafunct6
enum zmvxmafunct6 : int { zMVX_VMACC, zMVX_VNMSAC, zMVX_VMADD, zMVX_VNMSUB };

// enum mvxfunct6
enum zmvxfunct6 : int { zMVX_VAADDU, zMVX_VAADD, zMVX_VASUBU, zMVX_VASUB, zMVX_VSLIDE1UP, zMVX_VSLIDE1DOWN, zMVX_VMUL, zMVX_VMULH, zMVX_VMULHU, zMVX_VMULHSU, zMVX_VDIVU, zMVX_VDIV, zMVX_VREMU, zMVX_VREM };

// enum mvvmafunct6
enum zmvvmafunct6 : int { zMVV_VMACC, zMVV_VNMSAC, zMVV_VMADD, zMVV_VNMSUB };

// enum mvvfunct6
enum zmvvfunct6 : int { zMVV_VAADDU, zMVV_VAADD, zMVV_VASUBU, zMVV_VASUB, zMVV_VMUL, zMVV_VMULH, zMVV_VMULHU, zMVV_VMULHSU, zMVV_VDIVU, zMVV_VDIV, zMVV_VREMU, zMVV_VREM };

// enum mmfunct6
enum zmmfunct6 : int { zMM_VMAND, zMM_VMNAND, zMM_VMANDN, zMM_VMXOR, zMM_VMOR, zMM_VMNOR, zMM_VMORN, zMM_VMXNOR };

// enum misaligned_exception
enum zmisaligned_exception : int { zAccessFault, zAlignmentException };

// union option<Emisaligned_exception%>
enum kind_zoptionzIEmisaligned_exceptionz5zK { Kind_zNonezIEmisaligned_exceptionz5zK, Kind_zSomezIEmisaligned_exceptionz5zK };

struct zoptionzIEmisaligned_exceptionz5zK {
  enum kind_zoptionzIEmisaligned_exceptionz5zK kind;
  union {
    struct { unit zNonezIEmisaligned_exceptionz5zK; };
    struct { enum zmisaligned_exception zSomezIEmisaligned_exceptionz5zK; };
  } variants;
};

// enum mem_payload
enum zmem_payload : int { zData, zVector, zPageTableEntry, zShadowStack };

// type abbreviation mem_meta
typedef unit zmem_meta;

// type abbreviation mem_access_width
typedef int64_t zmem_access_width;

// enum maskfunct3
enum zmaskfunct3 : int { zVV_VMERGE, zVI_VMERGE, zVX_VMERGE };

// enum mask_type
enum zmask_type : int { zMASK_LO, zMASK_HI };

// type abbreviation mag_size_exp
typedef int64_t zmag_sizze_exp;

// enum loop_chain_state
enum zloop_chain_state : int { zNotInChain, zInChainWithMatch, zInChainWithoutMatch };

// type abbreviation level_range
typedef int64_t zlevel_range;

// type abbreviation landing_pad_label
typedef uint64_t zlanding_pad_label;

// enum landing_pad_expectation
enum zlanding_pad_expectation : int { zNO_LP_EXPECTED, zLP_EXPECTED };

// enum iop
enum ziop : int { zADDI, zSLTI, zSLTIU, zXORI, zORI, zANDI };

// type abbreviation instbits
typedef uint64_t zinstbits;

// enum indexed_mop
enum zindexed_mop : int { zINDEXED_UNORDERED, zINDEXED_ORDERED };

// struct htif_cmd
struct zhtif_cmd {uint64_t zbits;};

// type abbreviation hpmidx
typedef int64_t zhpmidx;

// enum hlvop
enum zhlvop : int { zHLV, zHLVX };

// type abbreviation hgatp_mode
typedef uint64_t zhgatp_mode;

// type abbreviation half
typedef uint64_t zhalf;

// type abbreviation gpabits
typedef sbits zgpabits;

// enum fwvvmafunct6
enum zfwvvmafunct6 : int { zFWVV_VMACC, zFWVV_VNMACC, zFWVV_VMSAC, zFWVV_VNMSAC };

// enum fwvvfunct6
enum zfwvvfunct6 : int { zFWVV_VADD, zFWVV_VSUB, zFWVV_VMUL };

// enum fwvfunct6
enum zfwvfunct6 : int { zFWV_VADD, zFWV_VSUB };

// enum fwvfmafunct6
enum zfwvfmafunct6 : int { zFWVF_VMACC, zFWVF_VNMACC, zFWVF_VMSAC, zFWVF_VNMSAC };

// enum fwvffunct6
enum zfwvffunct6 : int { zFWVF_VADD, zFWVF_VSUB, zFWVF_VMUL };

// enum fwffunct6
enum zfwffunct6 : int { zFWF_VADD, zFWF_VSUB };

// enum fvvmfunct6
enum zfvvmfunct6 : int { zFVVM_VMFEQ, zFVVM_VMFLE, zFVVM_VMFLT, zFVVM_VMFNE };

// enum fvvmafunct6
enum zfvvmafunct6 : int { zFVV_VMADD, zFVV_VNMADD, zFVV_VMSUB, zFVV_VNMSUB, zFVV_VMACC, zFVV_VNMACC, zFVV_VMSAC, zFVV_VNMSAC };

// enum fvvfunct6
enum zfvvfunct6 : int { zFVV_VADD, zFVV_VSUB, zFVV_VMIN, zFVV_VMAX, zFVV_VSGNJ, zFVV_VSGNJN, zFVV_VSGNJX, zFVV_VDIV, zFVV_VMUL };

// enum fvfmfunct6
enum zfvfmfunct6 : int { zVFM_VMFEQ, zVFM_VMFLE, zVFM_VMFLT, zVFM_VMFNE, zVFM_VMFGT, zVFM_VMFGE };

// enum fvfmafunct6
enum zfvfmafunct6 : int { zVF_VMADD, zVF_VNMADD, zVF_VMSUB, zVF_VNMSUB, zVF_VMACC, zVF_VNMACC, zVF_VMSAC, zVF_VNMSAC };

// enum fvffunct6
enum zfvffunct6 : int { zVF_VADD, zVF_VSUB, zVF_VMIN, zVF_VMAX, zVF_VSGNJ, zVF_VSGNJN, zVF_VSGNJX, zVF_VDIV, zVF_VRDIV, zVF_VMUL, zVF_VRSUB, zVF_VSLIDE1UP, zVF_VSLIDE1DOWN };

// type abbreviation fregtype
typedef sbits zfregtype;

// union fregno
enum kind_zfregno { Kind_zFregno };

struct zfregno {
  enum kind_zfregno kind;
  union {struct { int64_t zFregno; };} variants;
};

// union fregidx
enum kind_zfregidx { Kind_zFregidx };

struct zfregidx {
  enum kind_zfregidx kind;
  union {struct { uint64_t zFregidx; };} variants;
};

// type abbreviation fp_rounding_modes
typedef uint64_t zfp_rounding_modes;

// type abbreviation fp_exception_flags
typedef uint64_t zfp_exception_flags;

// type abbreviation fp_bits
typedef lbits zfp_bits;

// enum float_class
enum zfloat_class : int { zfloat_class_negative_inf, zfloat_class_negative_normal, zfloat_class_negative_subnormal, zfloat_class_negative_zzero, zfloat_class_positive_zzero, zfloat_class_positive_subnormal, zfloat_class_positive_normal, zfloat_class_positive_inf, zfloat_class_snan, zfloat_class_qnan };

// struct float_bits
struct zfloat_bits {
  sbits zexp;
  lbits zmantissa;
  uint64_t zsign;
};

// type abbreviation flenbits
typedef sbits zflenbits;

// enum f_un_x_op_H
enum zf_un_x_op_H : int { zFCLASS_H, zFMV_X_H };

// enum f_un_x_op_D
enum zf_un_x_op_D : int { zFCLASS_D, zFMV_X_D };

// enum f_un_rm_xf_op_S
enum zf_un_rm_xf_op_S : int { zFCVT_S_W, zFCVT_S_WU, zFCVT_S_L, zFCVT_S_LU };

// enum f_un_rm_xf_op_H
enum zf_un_rm_xf_op_H : int { zFCVT_H_W, zFCVT_H_WU, zFCVT_H_L, zFCVT_H_LU };

// enum f_un_rm_xf_op_D
enum zf_un_rm_xf_op_D : int { zFCVT_D_W, zFCVT_D_WU, zFCVT_D_L, zFCVT_D_LU };

// enum f_un_rm_fx_op_S
enum zf_un_rm_fx_op_S : int { zFCVT_W_S, zFCVT_WU_S, zFCVT_L_S, zFCVT_LU_S };

// enum f_un_rm_fx_op_H
enum zf_un_rm_fx_op_H : int { zFCVT_W_H, zFCVT_WU_H, zFCVT_L_H, zFCVT_LU_H };

// enum f_un_rm_fx_op_D
enum zf_un_rm_fx_op_D : int { zFCVT_W_D, zFCVT_WU_D, zFCVT_L_D, zFCVT_LU_D };

// enum f_un_rm_ff_op_S
enum zf_un_rm_ff_op_S : int { zFSQRT_S };

// enum f_un_rm_ff_op_H
enum zf_un_rm_ff_op_H : int { zFSQRT_H, zFCVT_H_S, zFCVT_H_D, zFCVT_S_H, zFCVT_D_H };

// enum f_un_rm_ff_op_D
enum zf_un_rm_ff_op_D : int { zFSQRT_D, zFCVT_S_D, zFCVT_D_S };

// enum f_un_op_x_S
enum zf_un_op_x_S : int { zFCLASS_S, zFMV_X_W };

// enum f_un_op_f_S
enum zf_un_op_f_S : int { zFMV_W_X };

// enum f_un_f_op_H
enum zf_un_f_op_H : int { zFMV_H_X };

// enum f_un_f_op_D
enum zf_un_f_op_D : int { zFMV_D_X };

// enum f_madd_op_S
enum zf_madd_op_S : int { zFMADD_S, zFMSUB_S, zFNMSUB_S, zFNMADD_S };

// enum f_madd_op_H
enum zf_madd_op_H : int { zFMADD_H, zFMSUB_H, zFNMSUB_H, zFNMADD_H };

// enum f_madd_op_D
enum zf_madd_op_D : int { zFMADD_D, zFMSUB_D, zFNMSUB_D, zFNMADD_D };

// enum f_bin_x_op_H
enum zf_bin_x_op_H : int { zFEQ_H, zFLT_H, zFLE_H };

// enum f_bin_x_op_D
enum zf_bin_x_op_D : int { zFEQ_D, zFLT_D, zFLE_D };

// enum f_bin_rm_op_S
enum zf_bin_rm_op_S : int { zFADD_S, zFSUB_S, zFMUL_S, zFDIV_S };

// enum f_bin_rm_op_H
enum zf_bin_rm_op_H : int { zFADD_H, zFSUB_H, zFMUL_H, zFDIV_H };

// enum f_bin_rm_op_D
enum zf_bin_rm_op_D : int { zFADD_D, zFSUB_D, zFMUL_D, zFDIV_D };

// enum f_bin_op_x_S
enum zf_bin_op_x_S : int { zFEQ_S, zFLT_S, zFLE_S };

// enum f_bin_op_f_S
enum zf_bin_op_f_S : int { zFSGNJ_S, zFSGNJN_S, zFSGNJX_S, zFMIN_S, zFMAX_S };

// enum f_bin_f_op_H
enum zf_bin_f_op_H : int { zFSGNJ_H, zFSGNJN_H, zFSGNJX_H, zFMIN_H, zFMAX_H };

// enum f_bin_f_op_D
enum zf_bin_f_op_D : int { zFSGNJ_D, zFSGNJN_D, zFSGNJX_D, zFMIN_D, zFMAX_D };

// enum extop_zbb
enum zextop_zzbb : int { zSEXTB, zSEXTH, zZEXTH };

// enum extension
enum zextension : int { zExt_M, zExt_A, zExt_F, zExt_D, zExt_B, zExt_V, zExt_S, zExt_U, zExt_H, zExt_Sha, zExt_Shcounterenw, zExt_Shgatpa, zExt_Shtvala, zExt_Shvsatpa, zExt_Shvstvala, zExt_Shvstvecd, zExt_Zibi, zExt_Zic64b, zExt_Zicbom, zExt_Zicbop, zExt_Zicbozz, zExt_Zicfilp, zExt_Zicfiss, zExt_Zicntr, zExt_Zicond, zExt_Zicsr, zExt_Zifencei, zExt_Zihintntl, zExt_Zihintpause, zExt_Zihpm, zExt_Zilx, zExt_Zimop, zExt_Zmmul, zExt_Zaamo, zExt_Zabha, zExt_Zacas, zExt_Zalrsc, zExt_Zama16b, zExt_Zawrs, zExt_Za64rs, zExt_Za128rs, zExt_Zfa, zExt_Zfbfmin, zExt_Zfh, zExt_Zfhmin, zExt_Zfinx, zExt_Zdinx, zExt_Zca, zExt_Zcb, zExt_Zcd, zExt_Zcf, zExt_Zcmop, zExt_C, zExt_Zba, zExt_Zbb, zExt_Zbc, zExt_Zbkb, zExt_Zbkc, zExt_Zbkx, zExt_Zbs, zExt_Ziccamoa, zExt_Ziccamoc, zExt_Ziccif, zExt_Zicclsm, zExt_Ziccrse, zExt_Zknd, zExt_Zkne, zExt_Zknh, zExt_Zkr, zExt_Zksed, zExt_Zksh, zExt_Zkt, zExt_Zhinx, zExt_Zhinxmin, zExt_Zvl32b, zExt_Zvl64b, zExt_Zvl128b, zExt_Zvl256b, zExt_Zvl512b, zExt_Zvl1024b, zExt_Zve32f, zExt_Zve32x, zExt_Zve64d, zExt_Zve64f, zExt_Zve64x, zExt_Zvabd, zExt_Zvfbfmin, zExt_Zvfbfwma, zExt_Zvfh, zExt_Zvfhmin, zExt_Zvbb, zExt_Zvbc, zExt_Zvkb, zExt_Zvkg, zExt_Zvkned, zExt_Zvknha, zExt_Zvknhb, zExt_Zvksed, zExt_Zvksh, zExt_Zvkt, zExt_Zvkn, zExt_Zvknc, zExt_Zvkng, zExt_Zvks, zExt_Zvksc, zExt_Zvksg, zExt_Ssccptr, zExt_Sscofpmf, zExt_Sscounterenw, zExt_Ssdbltrp, zExt_Ssnpm, zExt_Ssstateen, zExt_Ssstrict, zExt_Sdtrig, zExt_Sstc, zExt_Sstvala, zExt_Sstvecd, zExt_Ssu64xl, zExt_Svbare, zExt_Sv32, zExt_Sv39, zExt_Sv48, zExt_Sv57, zExt_Svade, zExt_Svadu, zExt_Svinval, zExt_Svnapot, zExt_Svpbmt, zExt_Svrsw60t59b, zExt_Svukte, zExt_Svvptc, zExt_Smcntrpmf, zExt_Smdbltrp, zExt_Smmpm, zExt_Smnpm, zExt_Smstateen, zExt_Ssqosid, zExt_Sspm, zExt_Supm };

// type abbreviation ext_status
typedef uint64_t zext_status;

// type abbreviation ext_ptw_fail
typedef unit zext_ptw_fail;

// type abbreviation ext_ptw_error
typedef unit zext_ptw_error;

// type abbreviation ext_ptw
typedef unit zext_ptw;

// type abbreviation ext_fetch_addr_error
typedef unit zext_fetch_addr_error;

// type abbreviation ext_exception
typedef unit zext_exception;

// type abbreviation ext_exc_type
typedef unit zext_exc_type;

// type abbreviation ext_data_addr_error
typedef unit zext_data_addr_error;

// type abbreviation ext_control_addr_error
typedef unit zext_control_addr_error;

// union exception
enum kind_zexception { Kind_zError_internal_error, Kind_zError_not_implemented, Kind_zError_reserved_behavior };

struct zexception {
  enum kind_zexception kind;
  union {
    struct { sail_string zError_internal_error; };
    struct { sail_string zError_not_implemented; };
    struct { sail_string zError_reserved_behavior; };
  } variants;
};

// type abbreviation exc_code
typedef uint64_t zexc_code;

// enum event_csr
enum zevent_csr : int { zEV_EVENT, zEV_COUNTER };

// struct tuple_(%i, %enum zevent_csr)
struct ztuple_z8z5izCz0z5enumz0zzevent_csrz9 {
  sail_int ztup0;
  enum zevent_csr ztup1;
};

// union option<(i,Eevent_csr%)>
enum kind_zoptionzIz8izCEevent_csrz5z9zK { Kind_zNonezIz8izCEevent_csrz5z9zK, Kind_zSomezIz8izCEevent_csrz5z9zK };

struct zoptionzIz8izCEevent_csrz5z9zK {
  enum kind_zoptionzIz8izCEevent_csrz5z9zK kind;
  union {
    struct { unit zNonezIz8izCEevent_csrz5z9zK; };
    struct { struct ztuple_z8z5izCz0z5enumz0zzevent_csrz9 zSomezIz8izCEevent_csrz5z9zK; };
  } variants;
};

// enum csrop
enum zcsrop : int { zCSRRW, zCSRRS, zCSRRC };

// type abbreviation csreg
typedef uint64_t zcsreg;

// union cregidx
enum kind_zcregidx { Kind_zCregidx };

struct zcregidx {
  enum kind_zcregidx kind;
  union {struct { uint64_t zCregidx; };} variants;
};

// enum checked_cbop
enum zchecked_cbop : int { zCBOP_ILLEGAL, zCBOP_ILLEGAL_VIRTUAL, zCBOP_INVAL_FLUSH, zCBOP_INVAL_INVAL };

// union cfregidx
enum kind_zcfregidx { Kind_zCfregidx };

struct zcfregidx {
  enum kind_zcfregidx kind;
  union {struct { uint64_t zCfregidx; };} variants;
};

// enum cbop_zicbop
enum zcbop_zzicbop : int { zPREFETCH_I, zPREFETCH_R, zPREFETCH_W };

// enum cbop_zicbom
enum zcbop_zzicbom : int { zCBO_CLEAN, zCBO_FLUSH, zCBO_INVAL };

// enum cbie
enum zcbie : int { zCBIE_ILLEGAL, zCBIE_EXEC_FLUSH, zCBIE_EXEC_INVAL };

// union cacheop
enum kind_zcacheop { Kind_zCB_manage, Kind_zCB_prefetch, Kind_zCB_zzero };

struct zcacheop {
  enum kind_zcacheop kind;
  union {
    struct { enum zcbop_zzicbom zCB_manage; };
    struct { enum zcbop_zzicbop zCB_prefetch; };
    struct { unit zCB_zzero; };
  } variants;
};

// enum bropw_zbb
enum zbropw_zzbb : int { zROLW, zRORW };

// enum brop_zbs
enum zbrop_zzbs : int { zBCLR, zBEXT, zBINV, zBSET };

// enum brop_zbkb
enum zbrop_zzbkb : int { zPACK, zPACKH };

// enum brop_zbb
enum zbrop_zzbb : int { zANDN, zORN, zXNOR, zMAX, zMAXU, zMIN, zMINU, zROL, zROR };

// enum breakpoint_cause
enum zbreakpoint_cause : int { zBrk_Software, zBrk_Hardware };

// enum bop
enum zbop : int { zBEQ, zBNE, zBLT, zBGE, zBLTU, zBGEU };

// type abbreviation bits_rm
typedef uint64_t zbits_rm;

// type abbreviation bits_fflags
typedef uint64_t zbits_fflags;

// type abbreviation bits_S
typedef uint64_t zbits_S;

// type abbreviation bits_H
typedef uint64_t zbits_H;

// type abbreviation bits_D
typedef uint64_t zbits_D;

// enum biop_zbs
enum zbiop_zzbs : int { zBCLRI, zBEXTI, zBINVI, zBSETI };

// enum biop
enum zbiop : int { zBEQI, zBNEI };

// enum barrier_kind
enum zbarrier_kind : int { zBarrier_RISCV_rw_rw, zBarrier_RISCV_r_rw, zBarrier_RISCV_r_r, zBarrier_RISCV_rw_w, zBarrier_RISCV_w_w, zBarrier_RISCV_w_rw, zBarrier_RISCV_rw_r, zBarrier_RISCV_r_w, zBarrier_RISCV_w_r, zBarrier_RISCV_tso, zBarrier_RISCV_i };

// type abbreviation asidbits
typedef sbits zasidbits;

// enum amoop
enum zamoop : int { zAMOSWAP, zAMOAND, zAMOOR, zAMOXOR, zAMOADD, zAMOMIN, zAMOMAX, zAMOMINU, zAMOMAXU, zAMOCAS };

// enum agtype
enum zagtype : int { zUNDISTURBED, zAGNOSTIC };

// enum XtvecModeReservedBehavior
enum zXtvecModeReservedBehavior : int { zXtvec_Fatal, zXtvec_Ignore };

// enum XipReadType
enum zXipReadType : int { zIncludePlatformInterrupts, zExcludePlatformInterrupts };

// enum XenvcfgCbieReservedBehavior
enum zXenvcfgCbieReservedBehavior : int { zXenvcfg_Fatal, zXenvcfg_ClearPermissions, zXenvcfg_Ignore };

// enum WaitReason
enum zWaitReason : int { zWAIT_WFI, zWAIT_WRS_STO, zWAIT_WRS_NTO };

// struct Vtype
struct zVtype {sbits zbits;};

// enum VectorHalf
enum zVectorHalf : int { zHigh, zLow };

// struct Vcsr
struct zVcsr {uint64_t zbits;};

// struct Trigger_Extra_RV64
struct zTrigger_Extra_RV64 {uint64_t zbits;};

// struct Trigger_Extra_RV32
struct zTrigger_Extra_RV32 {uint64_t zbits;};

// enum Trig_Type
enum zTrig_Type : int { zTT_none, zTT_legacy, zTT_mcontrol, zTT_icount, zTT_itrigger, zTT_etrigger, zTT_mcontrol6, zTT_tmexttrigger, zTT_custom, zTT_disabled, zTT_reserved };

// type abbreviation Trig_Match_Size
typedef int64_t zTrig_Match_Sizze;

// enum Trig_Match
enum zTrig_Match : int { zTM_EQ, zTM_NAPOT, zTM_GE, zTM_LT, zTM_MASK_LO, zTM_MASK_HI, zTM_NEQ, zTM_NOT_NAPOT, zTM_NOT_MASK_LO, zTM_NOT_MASK_HI };

// enum Trig_Action
enum zTrig_Action : int { zTA_Breakpoint, zTA_Enter_Debug, zTA_Trace_On, zTA_Trace_Off, zTA_Trace_Notify, zTA_Ext_Trigger_0, zTA_Ext_Trigger_1 };

// struct tuple_(%enum zTrig_Action, %i64, %sbv64)
struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9 {
  enum zTrig_Action ztup0;
  int64_t ztup1;
  sbits ztup2;
};

// type abbreviation pending_trigger_info
typedef struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9 zpending_trigger_info;

// struct tuple_(%enum zTrig_Action, %i, %bv)
struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5izCz0z5bvz9 {
  enum zTrig_Action ztup0;
  sail_int ztup1;
  lbits ztup2;
};

// union option<(ETrig_Action%,i,b)>
enum kind_zoptionzIz8ETrig_Actionz5zCizCbz9zK { Kind_zNonezIz8ETrig_Actionz5zCizCbz9zK, Kind_zSomezIz8ETrig_Actionz5zCizCbz9zK };

struct zoptionzIz8ETrig_Actionz5zCizCbz9zK {
  enum kind_zoptionzIz8ETrig_Actionz5zCizCbz9zK kind;
  union {
    struct { unit zNonezIz8ETrig_Actionz5zCizCbz9zK; };
    struct { struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5izCz0z5bvz9 zSomezIz8ETrig_Actionz5zCizCbz9zK; };
  } variants;
};

// enum TrapVectorMode
enum zTrapVectorMode : int { zTV_Direct, zTV_Vector, zTV_Reserved };

// enum TranslationStage
enum zTranslationStage : int { zS_Stage, zVS_Stage, zG_Stage };

// struct TLB_Entry
struct zTLB_Entry {
  sbits zasid;
  bool zglobal;
  uint64_t zlevelMask;
  uint64_t zppn;
  uint64_t zpte;
  sbits zpteAddr;
  enum zTranslationStage zstage;
  sbits zvmid;
  uint64_t zvpn;
};

// union option<RTLB_Entry>
enum kind_zoptionzIRTLB_EntryzK { Kind_zNonezIRTLB_EntryzK, Kind_zSomezIRTLB_EntryzK };

struct zoptionzIRTLB_EntryzK {
  enum kind_zoptionzIRTLB_EntryzK kind;
  union {
    struct { unit zNonezIRTLB_EntryzK; };
    struct { struct zTLB_Entry zSomezIRTLB_EntryzK; };
  } variants;
};

// struct tuple_(%i, %struct zTLB_Entry)
struct ztuple_z8z5izCz0z5structz0zzTLB_Entryz9 {
  sail_int ztup0;
  struct zTLB_Entry ztup1;
};

// union option<(i,RTLB_Entry)>
enum kind_zoptionzIz8izCRTLB_Entryz9zK { Kind_zNonezIz8izCRTLB_Entryz9zK, Kind_zSomezIz8izCRTLB_Entryz9zK };

struct zoptionzIz8izCRTLB_Entryz9zK {
  enum kind_zoptionzIz8izCRTLB_Entryz9zK kind;
  union {
    struct { unit zNonezIz8izCRTLB_Entryz9zK; };
    struct { struct ztuple_z8z5izCz0z5structz0zzTLB_Entryz9 zSomezIz8izCRTLB_Entryz9zK; };
  } variants;
};

// struct TInfo
struct zTInfo {sbits zbits;};

// struct TExtra
struct zTExtra {
  uint64_t zmhselect;
  uint64_t zmhvalue;
  uint64_t zsbytemask;
  uint64_t zsselect;
  uint64_t zsvalue;
};

// struct TDisabled_bits
struct zTDisabled_bits {sbits zbits;};

// struct TDisabled
struct zTDisabled {
  sbits zdata;
  bool zdmode;
  sbits ztdata2;
  struct zTExtra ztextra;
};

// struct TData1
struct zTData1 {sbits zbits;};

// struct TControl
struct zTControl {sbits zbits;};

// struct Sstatus
struct zSstatus {uint64_t zbits;};

// struct Sstateen3
struct zSstateen3 {uint64_t zbits;};

// struct Sstateen2
struct zSstateen2 {uint64_t zbits;};

// struct Sstateen1
struct zSstateen1 {uint64_t zbits;};

// struct Sstateen0
struct zSstateen0 {uint64_t zbits;};

// struct Srmcfg
struct zSrmcfg {sbits zbits;};

// enum Splittability
enum zSplittability : int { zCanSplit, zCannotSplit };

// struct tuple_(%enum zSplittability, %i)
struct ztuple_z8z5enumz0zzSplittabilityzCz0z5iz9 {
  enum zSplittability ztup0;
  sail_int ztup1;
};

// union result<(ESplittability%,i),Emisaligned_exception%>
enum kind_zresultzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK { Kind_zErrzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK, Kind_zOkzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK };

struct zresultzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK {
  enum kind_zresultzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK kind;
  union {
    struct { enum zmisaligned_exception zErrzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK; };
    struct { struct ztuple_z8z5enumz0zzSplittabilityzCz0z5iz9 zOkzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK; };
  } variants;
};

// enum Software_Check_Code
enum zSoftware_Check_Code : int { zSWC_NO_INFO, zSWC_LANDING_PAD_FAULT, zSWC_SHADOW_STACK_FAULT };

// struct Sinterrupts
struct zSinterrupts {sbits zbits;};

// enum Signedness
enum zSignedness : int { zSigned, zUnsigned };

// struct mul_op
struct zmul_op {
  enum zVectorHalf zresult_part;
  enum zSignedness zsigned_rs1;
  enum zSignedness zsigned_rs2;
};

// struct tuple_(%enum zcbop_zzicbom, %sbv64)
struct ztuple_z8z5enumz0zzcbop_zzzzicbomzCz0z5sbv64z9 {
  enum zcbop_zzicbom ztup0;
  sbits ztup1;
};

// struct tuple_(%sbv64, %sbv64)
struct ztuple_z8z5sbv64zCz0z5sbv64z9 {
  sbits ztup0;
  sbits ztup1;
};

// struct tuple_(%sbv64, %bv5)
struct ztuple_z8z5sbv64zCz0z5bv5z9 {
  sbits ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv1, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv3, %bv3)
struct ztuple_z8z5bv3zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv3, %bv8)
struct ztuple_z8z5bv3zCz0z5bv8z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv5, %sbv64)
struct ztuple_z8z5bv5zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
};

// struct tuple_(%bv5, %bv5)
struct ztuple_z8z5bv5zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv6, %sbv64)
struct ztuple_z8z5bv6zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
};

// struct tuple_(%bv6, %bv3)
struct ztuple_z8z5bv6zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv6, %bv5)
struct ztuple_z8z5bv6zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv8, %bv3)
struct ztuple_z8z5bv8zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv21, %sbv64)
struct ztuple_z8z5bv21zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
};

// struct tuple_(%enum zcbop_zzicbop, %sbv64, %bv12)
struct ztuple_z8z5enumz0zzcbop_zzzzicbopzCz0z5sbv64zCz0z5bv12z9 {
  enum zcbop_zzicbop ztup0;
  sbits ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zzzvk_vaesdf_funct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vaesdf_funct6zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vaesdf_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zzzvk_vaesdm_funct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vaesdm_funct6zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vaesdm_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zzzvk_vaesef_funct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vaesef_funct6zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vaesef_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zzzvk_vaesem_funct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vaesem_funct6zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vaesem_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zzzvk_vsm4r_funct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vsm4r_funct6zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vsm4r_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%sbv64, %sbv64, %enum zextop_zzbb)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5enumz0zzextop_zzzzbbz9 {
  sbits ztup0;
  sbits ztup1;
  enum zextop_zzbb ztup2;
};

// struct tuple_(%sbv64, %sbv64, %sbv64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%sbv64, %sbv64, %bv5)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5bv5z9 {
  sbits ztup0;
  sbits ztup1;
  uint64_t ztup2;
};

// struct tuple_(%sbv64, %bv5, %enum zf_un_f_op_D)
struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_f_op_Dz9 {
  sbits ztup0;
  uint64_t ztup1;
  enum zf_un_f_op_D ztup2;
};

// struct tuple_(%sbv64, %bv5, %enum zf_un_f_op_H)
struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_f_op_Hz9 {
  sbits ztup0;
  uint64_t ztup1;
  enum zf_un_f_op_H ztup2;
};

// struct tuple_(%sbv64, %bv5, %enum zf_un_op_f_S)
struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_op_f_Sz9 {
  sbits ztup0;
  uint64_t ztup1;
  enum zf_un_op_f_S ztup2;
};

// struct tuple_(%sbv64, %bv5, %enum zvmlsop)
struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzvmlsopz9 {
  sbits ztup0;
  uint64_t ztup1;
  enum zvmlsop ztup2;
};

// struct tuple_(%bv1, %bv5, %sbv64)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
};

// struct tuple_(%bv1, %bv5, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv2, %bv3, %bv3)
struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv4, %sbv64, %sbv64)
struct ztuple_z8z5bv4zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%bv5, %enum zrounding_mode, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %sbv64, %enum zf_un_op_x_S)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_op_x_Sz9 {
  uint64_t ztup0;
  sbits ztup1;
  enum zf_un_op_x_S ztup2;
};

// struct tuple_(%bv5, %sbv64, %enum zf_un_x_op_D)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_x_op_Dz9 {
  uint64_t ztup0;
  sbits ztup1;
  enum zf_un_x_op_D ztup2;
};

// struct tuple_(%bv5, %sbv64, %enum zf_un_x_op_H)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_x_op_Hz9 {
  uint64_t ztup0;
  sbits ztup1;
  enum zf_un_x_op_H ztup2;
};

// struct tuple_(%bv5, %sbv64, %sbv64)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%bv5, %sbv64, %bv5)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  uint64_t ztup0;
  sbits ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %bv3, %bv3)
struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %bv5, %sbv64)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
};

// struct tuple_(%bv5, %bv5, %bv5)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %i64, %bv5)
struct ztuple_z8z5bv5zCz0z5i64zCz0z5bv5z9 {
  uint64_t ztup0;
  int64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv6, %sbv64, %sbv64)
struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%bv12, %sbv64, %sbv64)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%bv20, %sbv64, %enum zuop)
struct ztuple_z8z5bv20zCz0z5sbv64zCz0z5enumz0zzuopz9 {
  uint64_t ztup0;
  sbits ztup1;
  enum zuop ztup2;
};

// struct tuple_(%i64, %sbv64, %sbv64)
struct ztuple_z8z5i64zCz0z5sbv64zCz0z5sbv64z9 {
  int64_t ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%i64, %sbv64, %bv5)
struct ztuple_z8z5i64zCz0z5sbv64zCz0z5bv5z9 {
  int64_t ztup0;
  sbits ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zmmfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzmmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zmmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvextfunct6, %bv1, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvextfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5z9 {
  enum zvextfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvimcfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimcfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvimcfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvimfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvimfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvimsfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimsfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvimsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvvmcfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvmcfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvmcfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvvmfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvvmsfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvmsfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvmsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxmcfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxmcfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxmcfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxmfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxmfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxmfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxmsfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxmsfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxmsfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zzzvk_vsha2_funct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvk_vsha2_funct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvk_vsha2_funct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%sbv64, %enum zrounding_mode, %bv5, %enum zf_un_rm_xf_op_D)
struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Dz9 {
  sbits ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_xf_op_D ztup3;
};

// struct tuple_(%sbv64, %enum zrounding_mode, %bv5, %enum zf_un_rm_xf_op_H)
struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Hz9 {
  sbits ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_xf_op_H ztup3;
};

// struct tuple_(%sbv64, %enum zrounding_mode, %bv5, %enum zf_un_rm_xf_op_S)
struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Sz9 {
  sbits ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_xf_op_S ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zbrop_zzbb)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbbz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbrop_zzbb ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zbrop_zzbkb)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbkbz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbrop_zzbkb ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zbrop_zzbs)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbsz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbrop_zzbs ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zbropw_zzbb)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbropw_zzzzbbz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbropw_zzbb ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zrop)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzropz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zrop ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zropw)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzropwz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zropw ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %enum zzzicondop)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzzzzzicondopz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zzzicondop ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %struct zmul_op)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5structz0zzmul_opz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  struct zmul_op ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %bool)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5boolz9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  bool ztup3;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %bv2)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5bv2z9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %enum zvfnunary0, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfnunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zvfnunary0 ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %enum zvfunary0, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zvfunary0 ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %enum zvfunary1, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfunary1zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zvfunary1 ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %enum zvfwunary0, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfwunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zvfwunary0 ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv1, %bv5, %bv6, %bv5)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv6zCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%bv2, %sbv64, %sbv64, %sbv64)
struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  sbits ztup3;
};

// struct tuple_(%bv3, %sbv64, %sbv64, %sbv64)
struct ztuple_z8z5bv3zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  sbits ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %sbv64, %enum zf_un_rm_fx_op_D)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Dz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  sbits ztup2;
  enum zf_un_rm_fx_op_D ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %sbv64, %enum zf_un_rm_fx_op_H)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Hz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  sbits ztup2;
  enum zf_un_rm_fx_op_H ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %sbv64, %enum zf_un_rm_fx_op_S)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Sz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  sbits ztup2;
  enum zf_un_rm_fx_op_S ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %bv5, %enum zf_un_rm_ff_op_D)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Dz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_ff_op_D ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %bv5, %enum zf_un_rm_ff_op_H)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Hz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_ff_op_H ztup3;
};

// struct tuple_(%bv5, %enum zrounding_mode, %bv5, %enum zf_un_rm_ff_op_S)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Sz9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
  enum zf_un_rm_ff_op_S ztup3;
};

// struct tuple_(%bv5, %sbv64, %sbv64, %enum zsopw)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzsopwz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zsopw ztup3;
};

// struct tuple_(%bv5, %bv5, %sbv64, %enum zf_bin_op_x_S)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_op_x_Sz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zf_bin_op_x_S ztup3;
};

// struct tuple_(%bv5, %bv5, %sbv64, %enum zf_bin_x_op_D)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_x_op_Dz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zf_bin_x_op_D ztup3;
};

// struct tuple_(%bv5, %bv5, %sbv64, %enum zf_bin_x_op_H)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_x_op_Hz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zf_bin_x_op_H ztup3;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zf_bin_f_op_D)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_f_op_Dz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zf_bin_f_op_D ztup3;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zf_bin_f_op_H)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_f_op_Hz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zf_bin_f_op_H ztup3;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zf_bin_op_f_S)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_op_f_Sz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zf_bin_op_f_S ztup3;
};

// struct tuple_(%bv6, %sbv64, %sbv64, %enum zbiop_zzbs)
struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbiop_zzzzbsz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbiop_zzbs ztup3;
};

// struct tuple_(%bv6, %sbv64, %sbv64, %enum zsop)
struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzsopz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zsop ztup3;
};

// struct tuple_(%bv12, %sbv64, %sbv64, %enum zcsrop)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzcsropz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zcsrop ztup3;
};

// struct tuple_(%bv12, %sbv64, %sbv64, %enum ziop)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zziopz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum ziop ztup3;
};

// struct tuple_(%bv12, %sbv64, %sbv64, %i64)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5i64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  int64_t ztup3;
};

// struct tuple_(%bv12, %sbv64, %bv5, %i64)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5bv5zCz0z5i64z9 {
  uint64_t ztup0;
  sbits ztup1;
  uint64_t ztup2;
  int64_t ztup3;
};

// struct tuple_(%bv12, %bv5, %sbv64, %enum zcsrop)
struct ztuple_z8z5bv12zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzcsropz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zcsrop ztup3;
};

// struct tuple_(%bv12, %bv5, %sbv64, %i64)
struct ztuple_z8z5bv12zCz0z5bv5zCz0z5sbv64zCz0z5i64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  int64_t ztup3;
};

// struct tuple_(%bv13, %sbv64, %sbv64, %enum zbop)
struct ztuple_z8z5bv13zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbopz9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zbop ztup3;
};

// struct tuple_(%bv13, %bv5, %sbv64, %enum zbiop)
struct ztuple_z8z5bv13zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzbiopz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zbiop ztup3;
};

// struct tuple_(%i64, %sbv64, %enum zvlewidth, %bv5)
struct ztuple_z8z5i64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 {
  int64_t ztup0;
  sbits ztup1;
  enum zvlewidth ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvffunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfvfmafunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvfmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvfmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfvfmfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvfmfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvfmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfvvmafunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfvvmfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvmfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwffunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwvffunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwvfmafunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvfmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvfmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zfwvvmafunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zmvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zmvvmafunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzmvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zmvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zmvxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzmvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zmvxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zmvxmafunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzmvxmafunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zmvxmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znifunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznifunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znifunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znisfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznisfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znisfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znvsfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznvsfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znvsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zznxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum znxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum znxsfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zznxsfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum znxsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zrfvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrfvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrfvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zrfwvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrfwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrfwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zrivvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrivvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrivvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zrmvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvicmpfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvicmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvicmpfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvifunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvifunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvifunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvisgfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvisgfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvisgfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvvcmpfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvcmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvcmpfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvxcmpfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxcmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxcmpfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zvxsgfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxsgfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxsgfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwmvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwmvxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwmvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwmvxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwvvfunct6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwvxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwvxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zwxfunct6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwxfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zzzvabd_vabd_func6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zzzvabd_vabd_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zzzvabd_vabd_func6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvabd_vabd_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zzzvabd_vwabda_func6, %bv1, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zzzvabd_vwabda_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zzzvabd_vwabda_func6, %bv1, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvabd_vwabda_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%bool, %bool, %sbv64, %i64, %sbv64)
struct ztuple_z8z5boolzCz0z5boolzCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 {
  bool ztup0;
  bool ztup1;
  sbits ztup2;
  int64_t ztup3;
  sbits ztup4;
};

// struct tuple_(%bv4, %bv4, %bv4, %sbv64, %sbv64)
struct ztuple_z8z5bv4zCz0z5bv4zCz0z5bv4zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  sbits ztup4;
};

// struct tuple_(%bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_bin_rm_op_D)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Dz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zrounding_mode ztup2;
  uint64_t ztup3;
  enum zf_bin_rm_op_D ztup4;
};

// struct tuple_(%bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_bin_rm_op_H)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Hz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zrounding_mode ztup2;
  uint64_t ztup3;
  enum zf_bin_rm_op_H ztup4;
};

// struct tuple_(%bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_bin_rm_op_S)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Sz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zrounding_mode ztup2;
  uint64_t ztup3;
  enum zf_bin_rm_op_S ztup4;
};

// struct tuple_(%bv12, %sbv64, %sbv64, %bool, %i64)
struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5boolzCz0z5i64z9 {
  uint64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  bool ztup3;
  int64_t ztup4;
};

// struct tuple_(%i64, %enum zhlvop, %bool, %sbv64, %sbv64)
struct ztuple_z8z5i64zCz0z5enumz0zzhlvopzCz0z5boolzCz0z5sbv64zCz0z5sbv64z9 {
  int64_t ztup0;
  enum zhlvop ztup1;
  bool ztup2;
  sbits ztup3;
  sbits ztup4;
};

// struct tuple_(%i64, %bv1, %sbv64, %enum zvlewidth, %bv5)
struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 {
  int64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  enum zvlewidth ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zzzilx_mode, %sbv64, %sbv64, %bool, %i64, %sbv64)
struct ztuple_z8z5enumz0zzzzzzilx_modezCz0z5sbv64zCz0z5sbv64zCz0z5boolzCz0z5i64zCz0z5sbv64z9 {
  enum zzzilx_mode ztup0;
  sbits ztup1;
  sbits ztup2;
  bool ztup3;
  int64_t ztup4;
  sbits ztup5;
};

// struct tuple_(%bool, %bool, %sbv64, %sbv64, %i64, %sbv64)
struct ztuple_z8z5boolzCz0z5boolzCz0z5sbv64zCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 {
  bool ztup0;
  bool ztup1;
  sbits ztup2;
  sbits ztup3;
  int64_t ztup4;
  sbits ztup5;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_madd_op_D)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Dz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zrounding_mode ztup3;
  uint64_t ztup4;
  enum zf_madd_op_D ztup5;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_madd_op_H)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Hz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zrounding_mode ztup3;
  uint64_t ztup4;
  enum zf_madd_op_H ztup5;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zrounding_mode, %bv5, %enum zf_madd_op_S)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Sz9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zrounding_mode ztup3;
  uint64_t ztup4;
  enum zf_madd_op_S ztup5;
};

// struct tuple_(%i64, %bv1, %sbv64, %sbv64, %enum zvlewidth, %bv5)
struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 {
  int64_t ztup0;
  uint64_t ztup1;
  sbits ztup2;
  sbits ztup3;
  enum zvlewidth ztup4;
  uint64_t ztup5;
};

// struct tuple_(%enum zamoop, %bool, %bool, %sbv64, %sbv64, %i64, %sbv64)
struct ztuple_z8z5enumz0zzamoopzCz0z5boolzCz0z5boolzCz0z5sbv64zCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 {
  enum zamoop ztup0;
  bool ztup1;
  bool ztup2;
  sbits ztup3;
  sbits ztup4;
  int64_t ztup5;
  sbits ztup6;
};

// struct tuple_(%bv3, %bv1, %bv1, %bv3, %bv3, %sbv64, %sbv64)
struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3zCz0z5sbv64zCz0z5sbv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
  sbits ztup5;
  sbits ztup6;
};

// struct tuple_(%bv3, %bv1, %bv1, %bv3, %bv3, %bv5, %sbv64)
struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3zCz0z5bv5zCz0z5sbv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
  uint64_t ztup5;
  sbits ztup6;
};

// struct tuple_(%i64, %bv1, %bv5, %sbv64, %enum zvlewidth, %bv5, %enum zindexed_mop)
struct ztuple_z8z5i64zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5zCz0z5enumz0zzindexed_mopz9 {
  int64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  sbits ztup3;
  enum zvlewidth ztup4;
  uint64_t ztup5;
  enum zindexed_mop ztup6;
};

// union instruction
enum kind_zinstruction { Kind_zADDIW, Kind_zAES32DSI, Kind_zAES32DSMI, Kind_zAES32ESI, Kind_zAES32ESMI, Kind_zAES64DS, Kind_zAES64DSM, Kind_zAES64ES, Kind_zAES64ESM, Kind_zAES64IM, Kind_zAES64KS1I, Kind_zAES64KS2, Kind_zAMO, Kind_zBITYPE, Kind_zBREV8, Kind_zBTYPE, Kind_zCLMUL, Kind_zCLMULH, Kind_zCLMULR, Kind_zCLZ, Kind_zCLZW, Kind_zCPOP, Kind_zCPOPW, Kind_zCSRImm, Kind_zCSRReg, Kind_zCTZ, Kind_zCTZW, Kind_zC_ADD, Kind_zC_ADDI, Kind_zC_ADDI16SP, Kind_zC_ADDI4SPN, Kind_zC_ADDIW, Kind_zC_ADDW, Kind_zC_AND, Kind_zC_ANDI, Kind_zC_BEQZ, Kind_zC_BNEZ, Kind_zC_EBREAK, Kind_zC_FLD, Kind_zC_FLDSP, Kind_zC_FLW, Kind_zC_FLWSP, Kind_zC_FSD, Kind_zC_FSDSP, Kind_zC_FSW, Kind_zC_FSWSP, Kind_zC_ILLEGAL, Kind_zC_J, Kind_zC_JAL, Kind_zC_JALR, Kind_zC_JR, Kind_zC_LBU, Kind_zC_LD, Kind_zC_LDSP, Kind_zC_LH, Kind_zC_LHU, Kind_zC_LI, Kind_zC_LUI, Kind_zC_LW, Kind_zC_LWSP, Kind_zC_MUL, Kind_zC_MV, Kind_zC_NOP, Kind_zC_NOT, Kind_zC_NTL, Kind_zC_OR, Kind_zC_SB, Kind_zC_SD, Kind_zC_SDSP, Kind_zC_SEXT_B, Kind_zC_SEXT_H, Kind_zC_SH, Kind_zC_SLLI, Kind_zC_SRAI, Kind_zC_SRLI, Kind_zC_SSPOPCHK, Kind_zC_SSPUSH, Kind_zC_SUB, Kind_zC_SUBW, Kind_zC_SW, Kind_zC_SWSP, Kind_zC_XOR, Kind_zC_ZEXT_B, Kind_zC_ZEXT_H, Kind_zC_ZEXT_W, Kind_zDIV, Kind_zDIVW, Kind_zEBREAK, Kind_zECALL, Kind_zFCVTMOD_W_D, Kind_zFCVT_BF16_S, Kind_zFCVT_S_BF16, Kind_zFENCE, Kind_zFENCEI, Kind_zFENCE_TSO, Kind_zFLEQ_D, Kind_zFLEQ_H, Kind_zFLEQ_S, Kind_zFLI_D, Kind_zFLI_H, Kind_zFLI_S, Kind_zFLTQ_D, Kind_zFLTQ_H, Kind_zFLTQ_S, Kind_zFMAXM_D, Kind_zFMAXM_H, Kind_zFMAXM_S, Kind_zFMINM_D, Kind_zFMINM_H, Kind_zFMINM_S, Kind_zFMVH_X_D, Kind_zFMVP_D_X, Kind_zFROUNDNX_D, Kind_zFROUNDNX_H, Kind_zFROUNDNX_S, Kind_zFROUND_D, Kind_zFROUND_H, Kind_zFROUND_S, Kind_zFVFMATYPE, Kind_zFVFMTYPE, Kind_zFVFTYPE, Kind_zFVVMATYPE, Kind_zFVVMTYPE, Kind_zFVVTYPE, Kind_zFWFTYPE, Kind_zFWVFMATYPE, Kind_zFWVFTYPE, Kind_zFWVTYPE, Kind_zFWVVMATYPE, Kind_zFWVVTYPE, Kind_zF_BIN_F_TYPE_D, Kind_zF_BIN_F_TYPE_H, Kind_zF_BIN_RM_TYPE_D, Kind_zF_BIN_RM_TYPE_H, Kind_zF_BIN_RM_TYPE_S, Kind_zF_BIN_TYPE_F_S, Kind_zF_BIN_TYPE_X_S, Kind_zF_BIN_X_TYPE_D, Kind_zF_BIN_X_TYPE_H, Kind_zF_MADD_TYPE_D, Kind_zF_MADD_TYPE_H, Kind_zF_MADD_TYPE_S, Kind_zF_UN_F_TYPE_D, Kind_zF_UN_F_TYPE_H, Kind_zF_UN_RM_FF_TYPE_D, Kind_zF_UN_RM_FF_TYPE_H, Kind_zF_UN_RM_FF_TYPE_S, Kind_zF_UN_RM_FX_TYPE_D, Kind_zF_UN_RM_FX_TYPE_H, Kind_zF_UN_RM_FX_TYPE_S, Kind_zF_UN_RM_XF_TYPE_D, Kind_zF_UN_RM_XF_TYPE_H, Kind_zF_UN_RM_XF_TYPE_S, Kind_zF_UN_TYPE_F_S, Kind_zF_UN_TYPE_X_S, Kind_zF_UN_X_TYPE_D, Kind_zF_UN_X_TYPE_H, Kind_zHFENCE_GVMA, Kind_zHFENCE_VVMA, Kind_zHINVAL_GVMA, Kind_zHINVAL_VVMA, Kind_zHLVTYPE, Kind_zHSV, Kind_zILLEGAL, Kind_zITYPE, Kind_zJAL, Kind_zJALR, Kind_zLOAD, Kind_zLOADRES, Kind_zLOAD_FP, Kind_zLPAD, Kind_zMASKTYPEI, Kind_zMASKTYPEV, Kind_zMASKTYPEX, Kind_zMMTYPE, Kind_zMOVETYPEI, Kind_zMOVETYPEV, Kind_zMOVETYPEX, Kind_zMRET, Kind_zMUL, Kind_zMULW, Kind_zMVVCOMPRESS, Kind_zMVVMATYPE, Kind_zMVVTYPE, Kind_zMVXMATYPE, Kind_zMVXTYPE, Kind_zNISTYPE, Kind_zNITYPE, Kind_zNTL, Kind_zNVSTYPE, Kind_zNVTYPE, Kind_zNXSTYPE, Kind_zNXTYPE, Kind_zORCB, Kind_zPAUSE, Kind_zREM, Kind_zREMW, Kind_zREV8, Kind_zRFVVTYPE, Kind_zRFWVVTYPE, Kind_zRIVVTYPE, Kind_zRMVVTYPE, Kind_zRORI, Kind_zRORIW, Kind_zRTYPE, Kind_zRTYPEW, Kind_zSFENCE_INVAL_IR, Kind_zSFENCE_VMA, Kind_zSFENCE_W_INVAL, Kind_zSHA256SIG0, Kind_zSHA256SIG1, Kind_zSHA256SUM0, Kind_zSHA256SUM1, Kind_zSHA512SIG0, Kind_zSHA512SIG0H, Kind_zSHA512SIG0L, Kind_zSHA512SIG1, Kind_zSHA512SIG1H, Kind_zSHA512SIG1L, Kind_zSHA512SUM0, Kind_zSHA512SUM0R, Kind_zSHA512SUM1, Kind_zSHA512SUM1R, Kind_zSHIFTIOP, Kind_zSHIFTIWOP, Kind_zSINVAL_VMA, Kind_zSLLIUW, Kind_zSM3P0, Kind_zSM3P1, Kind_zSM4ED, Kind_zSM4KS, Kind_zSRET, Kind_zSSAMOSWAP, Kind_zSSPOPCHK, Kind_zSSPUSH, Kind_zSSRDP, Kind_zSTORE, Kind_zSTORECON, Kind_zSTORE_FP, Kind_zUNZIP, Kind_zUTYPE, Kind_zVAESDF, Kind_zVAESDM, Kind_zVAESEF, Kind_zVAESEM, Kind_zVAESKF1_VI, Kind_zVAESKF2_VI, Kind_zVAESZ_VS, Kind_zVANDN_VV, Kind_zVANDN_VX, Kind_zVBREV8_V, Kind_zVBREV_V, Kind_zVCLMULH_VV, Kind_zVCLMULH_VX, Kind_zVCLMUL_VV, Kind_zVCLMUL_VX, Kind_zVCLZ_V, Kind_zVCPOP_M, Kind_zVCPOP_V, Kind_zVCTZ_V, Kind_zVEXTTYPE, Kind_zVFIRST_M, Kind_zVFMERGE, Kind_zVFMV, Kind_zVFMVFS, Kind_zVFMVSF, Kind_zVFNCVTBF16_F_F_W, Kind_zVFNUNARY0, Kind_zVFUNARY0, Kind_zVFUNARY1, Kind_zVFWCVTBF16_F_F_V, Kind_zVFWMACCBF16_VF, Kind_zVFWMACCBF16_VV, Kind_zVFWUNARY0, Kind_zVGHSH_VV, Kind_zVGMUL_VV, Kind_zVICMPTYPE, Kind_zVID_V, Kind_zVIMCTYPE, Kind_zVIMSTYPE, Kind_zVIMTYPE, Kind_zVIOTA_M, Kind_zVISG, Kind_zVITYPE, Kind_zVLRETYPE, Kind_zVLSEGFFTYPE, Kind_zVLSEGTYPE, Kind_zVLSSEGTYPE, Kind_zVLXSEGTYPE, Kind_zVMSBF_M, Kind_zVMSIF_M, Kind_zVMSOF_M, Kind_zVMTYPE, Kind_zVMVRTYPE, Kind_zVMVSX, Kind_zVMVXS, Kind_zVREV8_V, Kind_zVROL_VV, Kind_zVROL_VX, Kind_zVROR_VI, Kind_zVROR_VV, Kind_zVROR_VX, Kind_zVSETIVLI, Kind_zVSETVL, Kind_zVSETVLI, Kind_zVSHA2MS_VV, Kind_zVSM3C_VI, Kind_zVSM3ME_VV, Kind_zVSM4K_VI, Kind_zVSRETYPE, Kind_zVSSEGTYPE, Kind_zVSSSEGTYPE, Kind_zVSXSEGTYPE, Kind_zVVCMPTYPE, Kind_zVVMCTYPE, Kind_zVVMSTYPE, Kind_zVVMTYPE, Kind_zVVTYPE, Kind_zVWSLL_VI, Kind_zVWSLL_VV, Kind_zVWSLL_VX, Kind_zVXCMPTYPE, Kind_zVXMCTYPE, Kind_zVXMSTYPE, Kind_zVXMTYPE, Kind_zVXSG, Kind_zVXTYPE, Kind_zWFI, Kind_zWMVVTYPE, Kind_zWMVXTYPE, Kind_zWRS, Kind_zWVTYPE, Kind_zWVVTYPE, Kind_zWVXTYPE, Kind_zWXTYPE, Kind_zXPERM4, Kind_zXPERM8, Kind_zZBA_RTYPE, Kind_zZBA_RTYPEUW, Kind_zZBB_EXTOP, Kind_zZBB_RTYPE, Kind_zZBB_RTYPEW, Kind_zZBKB_PACKW, Kind_zZBKB_RTYPE, Kind_zZBS_IOP, Kind_zZBS_RTYPE, Kind_zZCMOP, Kind_zZICBOM, Kind_zZICBOP, Kind_zZICBOZ, Kind_zZICOND_RTYPE, Kind_zZILX_LOAD, Kind_zZIMOP_MOP_R, Kind_zZIMOP_MOP_RR, Kind_zZIP, Kind_zZVABD_VV, Kind_zZVABD_VX, Kind_zZVKSHA2TYPE, Kind_zZVKSM4RTYPE, Kind_zZVWABDA_VV, Kind_zZVWABDA_VX };

struct zinstruction {
  enum kind_zinstruction kind;
  union {
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64z9 zADDIW; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES32DSI; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES32DSMI; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES32ESI; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES32ESMI; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES64DS; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES64DSM; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES64ES; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES64ESM; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zAES64IM; };
    struct { struct ztuple_z8z5bv4zCz0z5sbv64zCz0z5sbv64z9 zAES64KS1I; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zAES64KS2; };
    struct { struct ztuple_z8z5enumz0zzamoopzCz0z5boolzCz0z5boolzCz0z5sbv64zCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 zAMO; };
    struct { struct ztuple_z8z5bv13zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzbiopz9 zBITYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zBREV8; };
    struct { struct ztuple_z8z5bv13zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbopz9 zBTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zCLMUL; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zCLMULH; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zCLMULR; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCLZ; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCLZW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCPOP; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCPOPW; };
    struct { struct ztuple_z8z5bv12zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzcsropz9 zCSRImm; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzcsropz9 zCSRReg; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCTZ; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zCTZW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zC_ADD; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_ADDI; };
    struct { uint64_t zC_ADDI16SP; };
    struct { struct ztuple_z8z5bv3zCz0z5bv8z9 zC_ADDI4SPN; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_ADDIW; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_ADDW; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_AND; };
    struct { struct ztuple_z8z5bv6zCz0z5bv3z9 zC_ANDI; };
    struct { struct ztuple_z8z5bv8zCz0z5bv3z9 zC_BEQZ; };
    struct { struct ztuple_z8z5bv8zCz0z5bv3z9 zC_BNEZ; };
    struct { unit zC_EBREAK; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_FLD; };
    struct { struct ztuple_z8z5bv6zCz0z5bv5z9 zC_FLDSP; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_FLW; };
    struct { struct ztuple_z8z5bv6zCz0z5bv5z9 zC_FLWSP; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_FSD; };
    struct { struct ztuple_z8z5bv6zCz0z5bv5z9 zC_FSDSP; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_FSW; };
    struct { struct ztuple_z8z5bv6zCz0z5bv5z9 zC_FSWSP; };
    struct { uint64_t zC_ILLEGAL; };
    struct { uint64_t zC_J; };
    struct { uint64_t zC_JAL; };
    struct { sbits zC_JALR; };
    struct { sbits zC_JR; };
    struct { struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 zC_LBU; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_LD; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_LDSP; };
    struct { struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 zC_LH; };
    struct { struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 zC_LHU; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_LI; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_LUI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_LW; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_LWSP; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_MUL; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zC_MV; };
    struct { uint64_t zC_NOP; };
    struct { uint64_t zC_NOT; };
    struct { enum zntl_type zC_NTL; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_OR; };
    struct { struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 zC_SB; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_SD; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_SDSP; };
    struct { uint64_t zC_SEXT_B; };
    struct { uint64_t zC_SEXT_H; };
    struct { struct ztuple_z8z5bv2zCz0z5bv3zCz0z5bv3z9 zC_SH; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_SLLI; };
    struct { struct ztuple_z8z5bv6zCz0z5bv3z9 zC_SRAI; };
    struct { struct ztuple_z8z5bv6zCz0z5bv3z9 zC_SRLI; };
    struct { unit zC_SSPOPCHK; };
    struct { unit zC_SSPUSH; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_SUB; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_SUBW; };
    struct { struct ztuple_z8z5bv5zCz0z5bv3zCz0z5bv3z9 zC_SW; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64z9 zC_SWSP; };
    struct { struct ztuple_z8z5bv3zCz0z5bv3z9 zC_XOR; };
    struct { uint64_t zC_ZEXT_B; };
    struct { uint64_t zC_ZEXT_H; };
    struct { uint64_t zC_ZEXT_W; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5boolz9 zDIV; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5boolz9 zDIVW; };
    struct { unit zEBREAK; };
    struct { unit zECALL; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64z9 zFCVTMOD_W_D; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFCVT_BF16_S; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFCVT_S_BF16; };
    struct { struct ztuple_z8z5bv4zCz0z5bv4zCz0z5bv4zCz0z5sbv64zCz0z5sbv64z9 zFENCE; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64z9 zFENCEI; };
    struct { unit zFENCE_TSO; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLEQ_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLEQ_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLEQ_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zFLI_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zFLI_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zFLI_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLTQ_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLTQ_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64z9 zFLTQ_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMAXM_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMAXM_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMAXM_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMINM_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMINM_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zFMINM_S; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64z9 zFMVH_X_D; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5bv5z9 zFMVP_D_X; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUNDNX_D; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUNDNX_H; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUNDNX_S; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUND_D; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUND_H; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 zFROUND_S; };
    struct { struct ztuple_z8z5enumz0zzfvfmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVFMATYPE; };
    struct { struct ztuple_z8z5enumz0zzfvfmfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVFMTYPE; };
    struct { struct ztuple_z8z5enumz0zzfvffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVFTYPE; };
    struct { struct ztuple_z8z5enumz0zzfvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVVMATYPE; };
    struct { struct ztuple_z8z5enumz0zzfvvmfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVVMTYPE; };
    struct { struct ztuple_z8z5enumz0zzfvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzfwffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWFTYPE; };
    struct { struct ztuple_z8z5enumz0zzfwvfmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWVFMATYPE; };
    struct { struct ztuple_z8z5enumz0zzfwvffunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWVFTYPE; };
    struct { struct ztuple_z8z5enumz0zzfwvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWVTYPE; };
    struct { struct ztuple_z8z5enumz0zzfwvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWVVMATYPE; };
    struct { struct ztuple_z8z5enumz0zzfwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zFWVVTYPE; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_f_op_Dz9 zF_BIN_F_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_f_op_Hz9 zF_BIN_F_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Dz9 zF_BIN_RM_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Hz9 zF_BIN_RM_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_bin_rm_op_Sz9 zF_BIN_RM_TYPE_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzf_bin_op_f_Sz9 zF_BIN_TYPE_F_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_op_x_Sz9 zF_BIN_TYPE_X_S; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_x_op_Dz9 zF_BIN_X_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzf_bin_x_op_Hz9 zF_BIN_X_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Dz9 zF_MADD_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Hz9 zF_MADD_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_madd_op_Sz9 zF_MADD_TYPE_S; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_f_op_Dz9 zF_UN_F_TYPE_D; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_f_op_Hz9 zF_UN_F_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Dz9 zF_UN_RM_FF_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Hz9 zF_UN_RM_FF_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_ff_op_Sz9 zF_UN_RM_FF_TYPE_S; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Dz9 zF_UN_RM_FX_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Hz9 zF_UN_RM_FX_TYPE_H; };
    struct { struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64zCz0z5enumz0zzf_un_rm_fx_op_Sz9 zF_UN_RM_FX_TYPE_S; };
    struct { struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Dz9 zF_UN_RM_XF_TYPE_D; };
    struct { struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Hz9 zF_UN_RM_XF_TYPE_H; };
    struct { struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5zCz0z5enumz0zzf_un_rm_xf_op_Sz9 zF_UN_RM_XF_TYPE_S; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzf_un_op_f_Sz9 zF_UN_TYPE_F_S; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_op_x_Sz9 zF_UN_TYPE_X_S; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_x_op_Dz9 zF_UN_X_TYPE_D; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5enumz0zzf_un_x_op_Hz9 zF_UN_X_TYPE_H; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zHFENCE_GVMA; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zHFENCE_VVMA; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zHINVAL_GVMA; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zHINVAL_VVMA; };
    struct { struct ztuple_z8z5i64zCz0z5enumz0zzhlvopzCz0z5boolzCz0z5sbv64zCz0z5sbv64z9 zHLVTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5sbv64zCz0z5sbv64z9 zHSV; };
    struct { uint64_t zILLEGAL; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zziopz9 zITYPE; };
    struct { struct ztuple_z8z5bv21zCz0z5sbv64z9 zJAL; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64z9 zJALR; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5boolzCz0z5i64z9 zLOAD; };
    struct { struct ztuple_z8z5boolzCz0z5boolzCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 zLOADRES; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5bv5zCz0z5i64z9 zLOAD_FP; };
    struct { uint64_t zLPAD; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zMASKTYPEI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zMASKTYPEV; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5bv5z9 zMASKTYPEX; };
    struct { struct ztuple_z8z5enumz0zzmmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zMMTYPE; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zMOVETYPEI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zMOVETYPEV; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5z9 zMOVETYPEX; };
    struct { unit zMRET; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5structz0zzmul_opz9 zMUL; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zMULW; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zMVVCOMPRESS; };
    struct { struct ztuple_z8z5enumz0zzmvvmafunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zMVVMATYPE; };
    struct { struct ztuple_z8z5enumz0zzmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zMVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzmvxmafunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zMVXMATYPE; };
    struct { struct ztuple_z8z5enumz0zzmvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zMVXTYPE; };
    struct { struct ztuple_z8z5enumz0zznisfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zNISTYPE; };
    struct { struct ztuple_z8z5enumz0zznifunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zNITYPE; };
    struct { enum zntl_type zNTL; };
    struct { struct ztuple_z8z5enumz0zznvsfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zNVSTYPE; };
    struct { struct ztuple_z8z5enumz0zznvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zNVTYPE; };
    struct { struct ztuple_z8z5enumz0zznxsfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zNXSTYPE; };
    struct { struct ztuple_z8z5enumz0zznxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zNXTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zORCB; };
    struct { unit zPAUSE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5boolz9 zREM; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5boolz9 zREMW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zREV8; };
    struct { struct ztuple_z8z5enumz0zzrfvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zRFVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzrfwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zRFWVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzrivvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zRIVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzrmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zRMVVTYPE; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64z9 zRORI; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5sbv64z9 zRORIW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzropz9 zRTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzropwz9 zRTYPEW; };
    struct { unit zSFENCE_INVAL_IR; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSFENCE_VMA; };
    struct { unit zSFENCE_W_INVAL; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA256SIG0; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA256SIG1; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA256SUM0; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA256SUM1; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA512SIG0; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SIG0H; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SIG0L; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA512SIG1; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SIG1H; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SIG1L; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA512SUM0; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SUM0R; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSHA512SUM1; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSHA512SUM1R; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzsopz9 zSHIFTIOP; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzsopwz9 zSHIFTIWOP; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSINVAL_VMA; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64z9 zSLLIUW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSM3P0; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zSM3P1; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSM4ED; };
    struct { struct ztuple_z8z5bv2zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zSM4KS; };
    struct { unit zSRET; };
    struct { struct ztuple_z8z5boolzCz0z5boolzCz0z5sbv64zCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 zSSAMOSWAP; };
    struct { sbits zSSPOPCHK; };
    struct { sbits zSSPUSH; };
    struct { sbits zSSRDP; };
    struct { struct ztuple_z8z5bv12zCz0z5sbv64zCz0z5sbv64zCz0z5i64z9 zSTORE; };
    struct { struct ztuple_z8z5boolzCz0z5boolzCz0z5sbv64zCz0z5sbv64zCz0z5i64zCz0z5sbv64z9 zSTORECON; };
    struct { struct ztuple_z8z5bv12zCz0z5bv5zCz0z5sbv64zCz0z5i64z9 zSTORE_FP; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zUNZIP; };
    struct { struct ztuple_z8z5bv20zCz0z5sbv64zCz0z5enumz0zzuopz9 zUTYPE; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vaesdf_funct6zCz0z5bv5zCz0z5bv5z9 zVAESDF; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vaesdm_funct6zCz0z5bv5zCz0z5bv5z9 zVAESDM; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vaesef_funct6zCz0z5bv5zCz0z5bv5z9 zVAESEF; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vaesem_funct6zCz0z5bv5zCz0z5bv5z9 zVAESEM; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVAESKF1_VI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVAESKF2_VI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zVAESZ_VS; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVANDN_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVANDN_VX; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVBREV8_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVBREV_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVCLMULH_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVCLMULH_VX; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVCLMUL_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVCLMUL_VX; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVCLZ_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64z9 zVCPOP_M; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVCPOP_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVCTZ_V; };
    struct { struct ztuple_z8z5enumz0zzvextfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5z9 zVEXTTYPE; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64z9 zVFIRST_M; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVFMERGE; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zVFMV; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zVFMVFS; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zVFMVSF; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVFNCVTBF16_F_F_W; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfnunary0zCz0z5bv5z9 zVFNUNARY0; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfunary0zCz0z5bv5z9 zVFUNARY0; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfunary1zCz0z5bv5z9 zVFUNARY1; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVFWCVTBF16_F_F_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVFWMACCBF16_VF; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVFWMACCBF16_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5enumz0zzvfwunary0zCz0z5bv5z9 zVFWUNARY0; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVGHSH_VV; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5z9 zVGMUL_VV; };
    struct { struct ztuple_z8z5enumz0zzvicmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVICMPTYPE; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5z9 zVID_V; };
    struct { struct ztuple_z8z5enumz0zzvimcfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVIMCTYPE; };
    struct { struct ztuple_z8z5enumz0zzvimsfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVIMSTYPE; };
    struct { struct ztuple_z8z5enumz0zzvimfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVIMTYPE; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVIOTA_M; };
    struct { struct ztuple_z8z5enumz0zzvisgfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVISG; };
    struct { struct ztuple_z8z5enumz0zzvifunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVITYPE; };
    struct { struct ztuple_z8z5i64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVLRETYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVLSEGFFTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVLSEGTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVLSSEGTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5zCz0z5enumz0zzindexed_mopz9 zVLXSEGTYPE; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVMSBF_M; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVMSIF_M; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVMSOF_M; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5zCz0z5enumz0zzvmlsopz9 zVMTYPE; };
    struct { struct ztuple_z8z5bv5zCz0z5i64zCz0z5bv5z9 zVMVRTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5bv5z9 zVMVSX; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64z9 zVMVXS; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5z9 zVREV8_V; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVROL_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVROL_VX; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv6zCz0z5bv5z9 zVROR_VI; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVROR_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVROR_VX; };
    struct { struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3zCz0z5bv5zCz0z5sbv64z9 zVSETIVLI; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zVSETVL; };
    struct { struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3zCz0z5sbv64zCz0z5sbv64z9 zVSETVLI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVSHA2MS_VV; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVSM3C_VI; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVSM3ME_VV; };
    struct { struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5z9 zVSM4K_VI; };
    struct { struct ztuple_z8z5i64zCz0z5sbv64zCz0z5bv5z9 zVSRETYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVSSEGTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 zVSSSEGTYPE; };
    struct { struct ztuple_z8z5i64zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5zCz0z5enumz0zzindexed_mopz9 zVSXSEGTYPE; };
    struct { struct ztuple_z8z5enumz0zzvvcmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVVCMPTYPE; };
    struct { struct ztuple_z8z5enumz0zzvvmcfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVVMCTYPE; };
    struct { struct ztuple_z8z5enumz0zzvvmsfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVVMSTYPE; };
    struct { struct ztuple_z8z5enumz0zzvvmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVVMTYPE; };
    struct { struct ztuple_z8z5enumz0zzvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVVTYPE; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVWSLL_VI; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zVWSLL_VV; };
    struct { struct ztuple_z8z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVWSLL_VX; };
    struct { struct ztuple_z8z5enumz0zzvxcmpfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXCMPTYPE; };
    struct { struct ztuple_z8z5enumz0zzvxmcfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXMCTYPE; };
    struct { struct ztuple_z8z5enumz0zzvxmsfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXMSTYPE; };
    struct { struct ztuple_z8z5enumz0zzvxmfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXMTYPE; };
    struct { struct ztuple_z8z5enumz0zzvxsgfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXSG; };
    struct { struct ztuple_z8z5enumz0zzvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zVXTYPE; };
    struct { unit zWFI; };
    struct { struct ztuple_z8z5enumz0zzwmvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zWMVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzwmvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zWMVXTYPE; };
    struct { enum zwrsop zWRS; };
    struct { struct ztuple_z8z5enumz0zzwvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zWVTYPE; };
    struct { struct ztuple_z8z5enumz0zzwvvfunct6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zWVVTYPE; };
    struct { struct ztuple_z8z5enumz0zzwvxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zWVXTYPE; };
    struct { struct ztuple_z8z5enumz0zzwxfunct6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zWXTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zXPERM4; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zXPERM8; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5bv2z9 zZBA_RTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5bv2z9 zZBA_RTYPEUW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5enumz0zzextop_zzzzbbz9 zZBB_EXTOP; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbbz9 zZBB_RTYPE; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbropw_zzzzbbz9 zZBB_RTYPEW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zZBKB_PACKW; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbkbz9 zZBKB_RTYPE; };
    struct { struct ztuple_z8z5bv6zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbiop_zzzzbsz9 zZBS_IOP; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzbrop_zzzzbsz9 zZBS_RTYPE; };
    struct { uint64_t zZCMOP; };
    struct { struct ztuple_z8z5enumz0zzcbop_zzzzicbomzCz0z5sbv64z9 zZICBOM; };
    struct { struct ztuple_z8z5enumz0zzcbop_zzzzicbopzCz0z5sbv64zCz0z5bv12z9 zZICBOP; };
    struct { sbits zZICBOZ; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzzzzzicondopz9 zZICOND_RTYPE; };
    struct { struct ztuple_z8z5enumz0zzzzzzilx_modezCz0z5sbv64zCz0z5sbv64zCz0z5boolzCz0z5i64zCz0z5sbv64z9 zZILX_LOAD; };
    struct { struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5sbv64z9 zZIMOP_MOP_R; };
    struct { struct ztuple_z8z5bv3zCz0z5sbv64zCz0z5sbv64zCz0z5sbv64z9 zZIMOP_MOP_RR; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64z9 zZIP; };
    struct { struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zZVABD_VV; };
    struct { struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zZVABD_VX; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vsha2_funct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zZVKSHA2TYPE; };
    struct { struct ztuple_z8z5enumz0zzzzzzvk_vsm4r_funct6zCz0z5bv5zCz0z5bv5z9 zZVKSM4RTYPE; };
    struct { struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv1zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 zZVWABDA_VV; };
    struct { struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv1zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 zZVWABDA_VX; };
  } variants;
};

// union option<Uinstruction>
enum kind_zoptionzIUinstructionzK { Kind_zNonezIUinstructionzK, Kind_zSomezIUinstructionzK };

struct zoptionzIUinstructionzK {
  enum kind_zoptionzIUinstructionzK kind;
  union {
    struct { unit zNonezIUinstructionzK; };
    struct { struct zinstruction zSomezIUinstructionzK; };
  } variants;
};

// struct Seccfg
struct zSeccfg {uint64_t zbits;};

// enum Sdtrig_breakpoint_reentrancy
enum zSdtrig_breakpoint_reentrancy : int { zUse_tcontrol, zUse_interrupt_enables, zNo_reentrancy_support };

// struct Satp64
struct zSatp64 {uint64_t zbits;};

// struct Satp32
struct zSatp32 {uint64_t zbits;};

// enum SWCheckCodes
enum zSWCheckCodes : int { zLANDING_PAD_FAULT };

// struct SEnvcfg
struct zSEnvcfg {uint64_t zbits;};

// struct SContext
struct zSContext {sbits zbits;};

// enum SATPMode
enum zSATPMode : int { zBare, zSv32, zSv39, zSv48, zSv57 };

// union option<ESATPMode%>
enum kind_zoptionzIESATPModez5zK { Kind_zNonezIESATPModez5zK, Kind_zSomezIESATPModez5zK };

struct zoptionzIESATPModez5zK {
  enum kind_zoptionzIESATPModez5zK kind;
  union {
    struct { unit zNonezIESATPModez5zK; };
    struct { enum zSATPMode zSomezIESATPModez5zK; };
  } variants;
};

// enum Reservability
enum zReservability : int { zRsrvNone, zRsrvNonEventual, zRsrvEventual };

// struct RVFI_DII_Instruction_Packet
struct zRVFI_DII_Instruction_Packet {uint64_t zbits;};

// struct RVFI_DII_Execution_Packet_PC
struct zRVFI_DII_Execution_Packet_PC {lbits zbits;};

// struct RVFI_DII_Execution_Packet_InstMetaData
struct zRVFI_DII_Execution_Packet_InstMetaData {lbits zbits;};

// struct RVFI_DII_Execution_Packet_Ext_MemAccess
struct zRVFI_DII_Execution_Packet_Ext_MemAccess {lbits zbits;};

// struct RVFI_DII_Execution_Packet_Ext_Integer
struct zRVFI_DII_Execution_Packet_Ext_Integer {lbits zbits;};

// enum RV32ZdinxOddRegisterReservedBehavior
enum zRV32ZdinxOddRegisterReservedBehavior : int { zZdinx_Fatal, zZdinx_Illegal };

// enum Privileged_ISA_Version
enum zPrivileged_ISA_Version : int { zPrivileged_ISA_1_11, zPrivileged_ISA_1_12, zPrivileged_ISA_1_13 };

// enum Privilege
enum zPrivilege : int { zUser, zVirtualUser, zSupervisor, zVirtualSupervisor, zMachine };

// struct tuple_(%bv, %enum zPrivilege)
struct ztuple_z8z5bvzCz0z5enumz0zzPrivilegez9 {
  lbits ztup0;
  enum zPrivilege ztup1;
};

// union option<(b,EPrivilege%)>
enum kind_zoptionzIz8bzCEPrivilegez5z9zK { Kind_zNonezIz8bzCEPrivilegez5z9zK, Kind_zSomezIz8bzCEPrivilegez5z9zK };

struct zoptionzIz8bzCEPrivilegez5z9zK {
  enum kind_zoptionzIz8bzCEPrivilegez5z9zK kind;
  union {
    struct { unit zNonezIz8bzCEPrivilegez5z9zK; };
    struct { struct ztuple_z8z5bvzCz0z5enumz0zzPrivilegez9 zSomezIz8bzCEPrivilegez5z9zK; };
  } variants;
};

// struct instr_info
struct zinstr_info {
  bool zcompressed;
  struct zoptionzIUinstructionzK zexecuted_instruction;
  enum zPrivilege zfetch_privilege;
  bool zfetch_trigger_reentrance;
  struct zinstruction zfetched_instruction;
  uint64_t zinstbits;
};

// enum PointerMaskingMode
enum zPointerMaskingMode : int { zPMM_Disabled, zPMM_Reserved, zPMM_PMLEN_7, zPMM_PMLEN_16 };

// struct Pmpcfg_ent
struct zPmpcfg_ent {uint64_t zbits;};

// enum PmpWriteOnlyReservedBehavior
enum zPmpWriteOnlyReservedBehavior : int { zPMP_Fatal, zPMP_ClearPermissions, zPMP_Ignore };

// enum PmpAddrMatchType
enum zPmpAddrMatchType : int { zOFF, zTOR, zNA4, zNAPOT };

// struct Phys_Mem_Access_Info
struct zPhys_Mem_Access_Info {
  int64_t zgranule_sizze_exp;
  enum zSplittability zsplittable;
};

// struct PTW_Output
struct zPTW_Output {
  bool zglobal;
  int64_t zlevel;
  enum zpage_based_mem_type zpbmt;
  sbits zppn;
  sbits zpte;
  sbits zpteAddr;
};

// struct PTE_Flags
struct zPTE_Flags {uint64_t zbits;};

// struct PTE_Ext
struct zPTE_Ext {uint64_t zbits;};

// struct tuple_(%unit, %union zpte_check_failure)
struct ztuple_z8z5unitzCz0z5unionz0zzpte_check_failurez9 {
  unit ztup0;
  struct zpte_check_failure ztup1;
};

// union PTE_Check
enum kind_zPTE_Check { Kind_zPTE_Check_Failure, Kind_zPTE_Check_Success };

struct zPTE_Check {
  enum kind_zPTE_Check kind;
  union {
    struct { struct ztuple_z8z5unitzCz0z5unionz0zzpte_check_failurez9 zPTE_Check_Failure; };
    struct { unit zPTE_Check_Success; };
  } variants;
};

// enum PM_Ext
enum zPM_Ext : int { zPM_SSNPM, zPM_SMNPM, zPM_SMMPM };

// struct PMAMisalignedExceptions
struct zPMAMisalignedExceptions {
  enum zmisaligned_exception zamo;
  struct zoptionzIEmisaligned_exceptionz5zK zload_store;
  enum zmisaligned_exception zlrsc;
  struct zoptionzIEmisaligned_exceptionz5zK zvector;
};

// enum OOBVstartReservedBehavior
enum zOOBVstartReservedBehavior : int { zVstart_Illegal, zVstart_Ignore };

// struct Mtvec
struct zMtvec {sbits zbits;};

// struct Mstatus
struct zMstatus {uint64_t zbits;};

// struct Mstateen3
struct zMstateen3 {uint64_t zbits;};

// struct Mstateen2
struct zMstateen2 {uint64_t zbits;};

// struct Mstateen1
struct zMstateen1 {uint64_t zbits;};

// struct Mstateen0
struct zMstateen0 {uint64_t zbits;};

// struct Misa
struct zMisa {sbits zbits;};

// struct Minterrupts
struct zMinterrupts {sbits zbits;};

// struct tuple_(%enum ztrigger_addr_type, %sbv64, %i64)
struct ztuple_z8z5enumz0zztrigger_addr_typezCz0z5sbv64zCz0z5i64z9 {
  enum ztrigger_addr_type ztup0;
  sbits ztup1;
  int64_t ztup2;
};

// struct tuple_(%sbv64, %bv, %i64)
struct ztuple_z8z5sbv64zCz0z5bvzCz0z5i64z9 {
  sbits ztup0;
  lbits ztup1;
  int64_t ztup2;
};

// struct tuple_(%sbv64, %sbv64, %i64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5i64z9 {
  sbits ztup0;
  sbits ztup1;
  int64_t ztup2;
};

// struct tuple_(%sbv64, %bv, %bv, %i64)
struct ztuple_z8z5sbv64zCz0z5bvzCz0z5bvzCz0z5i64z9 {
  sbits ztup0;
  lbits ztup1;
  lbits ztup2;
  int64_t ztup3;
};

// union MemoryTriggerPayload
enum kind_zMemoryTriggerPayload { Kind_zTriggerAMOData, Kind_zTriggerAddress, Kind_zTriggerFetchAddr, Kind_zTriggerFetchInstr, Kind_zTriggerLoadData, Kind_zTriggerStore };

struct zMemoryTriggerPayload {
  enum kind_zMemoryTriggerPayload kind;
  union {
    struct { struct ztuple_z8z5sbv64zCz0z5bvzCz0z5bvzCz0z5i64z9 zTriggerAMOData; };
    struct { struct ztuple_z8z5enumz0zztrigger_addr_typezCz0z5sbv64zCz0z5i64z9 zTriggerAddress; };
    struct { sbits zTriggerFetchAddr; };
    struct { struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5i64z9 zTriggerFetchInstr; };
    struct { struct ztuple_z8z5sbv64zCz0z5bvzCz0z5i64z9 zTriggerLoadData; };
    struct { struct ztuple_z8z5sbv64zCz0z5bvzCz0z5i64z9 zTriggerStore; };
  } variants;
};

// enum MemoryRegionType
enum zMemoryRegionType : int { zMainMemory, zIOMemory };

// union option<EMemoryRegionType%>
enum kind_zoptionzIEMemoryRegionTypez5zK { Kind_zNonezIEMemoryRegionTypez5zK, Kind_zSomezIEMemoryRegionTypez5zK };

struct zoptionzIEMemoryRegionTypez5zK {
  enum kind_zoptionzIEMemoryRegionTypez5zK kind;
  union {
    struct { unit zNonezIEMemoryRegionTypez5zK; };
    struct { enum zMemoryRegionType zSomezIEMemoryRegionTypez5zK; };
  } variants;
};

// struct tuple_(%bool, %bool, %enum zmem_payload)
struct ztuple_z8z5boolzCz0z5boolzCz0z5enumz0zzmem_payloadz9 {
  bool ztup0;
  bool ztup1;
  enum zmem_payload ztup2;
};

// struct tuple_(%enum zamoop, %bool, %bool, %enum zmem_payload, %enum zmem_payload)
struct ztuple_z8z5enumz0zzamoopzCz0z5boolzCz0z5boolzCz0z5enumz0zzmem_payloadzCz0z5enumz0zzmem_payloadz9 {
  enum zamoop ztup0;
  bool ztup1;
  bool ztup2;
  enum zmem_payload ztup3;
  enum zmem_payload ztup4;
};

// union MemoryAccessType<Emem_payload%>
enum kind_zMemoryAccessTypezIEmem_payloadz5zK { Kind_zAtomiczIEmem_payloadz5zK, Kind_zCacheAccesszIEmem_payloadz5zK, Kind_zInstructionFetchzIEmem_payloadz5zK, Kind_zLoadzIEmem_payloadz5zK, Kind_zLoadExecutezIEmem_payloadz5zK, Kind_zLoadReservedzIEmem_payloadz5zK, Kind_zStorezIEmem_payloadz5zK, Kind_zStoreConditionalzIEmem_payloadz5zK };

struct zMemoryAccessTypezIEmem_payloadz5zK {
  enum kind_zMemoryAccessTypezIEmem_payloadz5zK kind;
  union {
    struct { struct ztuple_z8z5enumz0zzamoopzCz0z5boolzCz0z5boolzCz0z5enumz0zzmem_payloadzCz0z5enumz0zzmem_payloadz9 zAtomiczIEmem_payloadz5zK; };
    struct { struct zcacheop zCacheAccesszIEmem_payloadz5zK; };
    struct { unit zInstructionFetchzIEmem_payloadz5zK; };
    struct { enum zmem_payload zLoadzIEmem_payloadz5zK; };
    struct { enum zmem_payload zLoadExecutezIEmem_payloadz5zK; };
    struct { struct ztuple_z8z5boolzCz0z5boolzCz0z5enumz0zzmem_payloadz9 zLoadReservedzIEmem_payloadz5zK; };
    struct { enum zmem_payload zStorezIEmem_payloadz5zK; };
    struct { struct ztuple_z8z5boolzCz0z5boolzCz0z5enumz0zzmem_payloadz9 zStoreConditionalzIEmem_payloadz5zK; };
  } variants;
};

// struct tuple_(%enum zread_kind, %union zMemoryAccessTypezIEmem_payloadz5zK)
struct ztuple_z8z5enumz0zzread_kindzCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 {
  enum zread_kind ztup0;
  struct zMemoryAccessTypezIEmem_payloadz5zK ztup1;
};

// struct tuple_(%enum zwrite_kind, %union zMemoryAccessTypezIEmem_payloadz5zK)
struct ztuple_z8z5enumz0zzwrite_kindzCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 {
  enum zwrite_kind ztup0;
  struct zMemoryAccessTypezIEmem_payloadz5zK ztup1;
};

// union access_kind
enum kind_zaccess_kind { Kind_zAK_Read, Kind_zAK_Write };

struct zaccess_kind {
  enum kind_zaccess_kind kind;
  union {
    struct { struct ztuple_z8z5enumz0zzread_kindzCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 zAK_Read; };
    struct { struct ztuple_z8z5enumz0zzwrite_kindzCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 zAK_Write; };
  } variants;
};

// struct Mem_request<u,Uaccess_kind>
struct zMem_requestzIuzCUaccess_kindzK {
  struct zaccess_kind zaccess_kind;
  lbits zaddress;
  unit zaddress_space;
  sail_int znum_tag;
  sail_int zsizze;
};

// struct Medeleg
struct zMedeleg {uint64_t zbits;};

// struct Mcause
struct zMcause {sbits zbits;};

// struct MEnvcfg
struct zMEnvcfg {uint64_t zbits;};

// struct MControl6_bits
struct zMControl6_bits {sbits zbits;};

// struct MContext
struct zMContext {sbits zbits;};

// type abbreviation LMUL_pow
typedef int64_t zLMUL_pow;

// enum InterruptType
enum zInterruptType : int { zI_Reserved_0, zI_S_Software, zI_VS_Software, zI_M_Software, zI_Reserved_4, zI_S_Timer, zI_VS_Timer, zI_M_Timer, zI_Reserved_8, zI_S_External, zI_VS_External, zI_M_External, zI_SG_External, zI_COF, zI_Reserved_14, zI_Reserved_15 };

// union option<EInterruptType%>
enum kind_zoptionzIEInterruptTypez5zK { Kind_zNonezIEInterruptTypez5zK, Kind_zSomezIEInterruptTypez5zK };

struct zoptionzIEInterruptTypez5zK {
  enum kind_zoptionzIEInterruptTypez5zK kind;
  union {
    struct { unit zNonezIEInterruptTypez5zK; };
    struct { enum zInterruptType zSomezIEInterruptTypez5zK; };
  } variants;
};

// struct tuple_(%enum zInterruptType, %enum zPrivilege)
struct ztuple_z8z5enumz0zzInterruptTypezCz0z5enumz0zzPrivilegez9 {
  enum zInterruptType ztup0;
  enum zPrivilege ztup1;
};

// union option<(EInterruptType%,EPrivilege%)>
enum kind_zoptionzIz8EInterruptTypez5zCEPrivilegez5z9zK { Kind_zNonezIz8EInterruptTypez5zCEPrivilegez5z9zK, Kind_zSomezIz8EInterruptTypez5zCEPrivilegez5z9zK };

struct zoptionzIz8EInterruptTypez5zCEPrivilegez5z9zK {
  enum kind_zoptionzIz8EInterruptTypez5zCEPrivilegez5z9zK kind;
  union {
    struct { unit zNonezIz8EInterruptTypez5zCEPrivilegez5z9zK; };
    struct { struct ztuple_z8z5enumz0zzInterruptTypezCz0z5enumz0zzPrivilegez9 zSomezIz8EInterruptTypez5zCEPrivilegez5z9zK; };
  } variants;
};

// enum IllegalVtypeReservedBehavior
enum zIllegalVtypeReservedBehavior : int { zIllegalVtype_SetVill, zIllegalVtype_Illegal, zIllegalVtype_Fatal };

// struct ITrigger
struct zITrigger {
  enum zTrig_Action zaction;
  bool zdmode;
  bool zhit;
  bool zm;
  bool znmi;
  bool zpending;
  bool zs;
  sbits ztdata2;
  struct zTExtra ztextra;
  bool zu;
  bool zvs;
  bool zvu;
};

// enum ISA_Format
enum zISA_Format : int { zCanonical_Lowercase, zDeviceTree_ISA_Extensions };

// struct IETrigger_bits
struct zIETrigger_bits {sbits zbits;};

// struct ICount_bits
struct zICount_bits {sbits zbits;};

// struct ICount
struct zICount {
  enum zTrig_Action zaction;
  bool zactive;
  uint64_t zcount;
  bool zdmode;
  bool zhit;
  bool zm;
  struct zoptionzIbzK znew_count;
  bool zpending;
  bool zs;
  sbits ztdata2;
  struct zTExtra ztextra;
  bool zu;
  bool zvs;
  bool zvu;
};

// struct Hstatus
struct zHstatus {uint64_t zbits;};

// struct Hstateen3
struct zHstateen3 {uint64_t zbits;};

// struct Hstateen2
struct zHstateen2 {uint64_t zbits;};

// struct Hstateen1
struct zHstateen1 {uint64_t zbits;};

// struct Hstateen0
struct zHstateen0 {uint64_t zbits;};

// struct HpmEvent
struct zHpmEvent {uint64_t zbits;};

// enum Hit
enum zHit : int { zHit_false, zHit_before, zHit_after, zHit_imm_after };

// struct tuple_(%bv, %enum zHit)
struct ztuple_z8z5bvzCz0z5enumz0zzHitz9 {
  lbits ztup0;
  enum zHit ztup1;
};

// union option<(b,EHit%)>
enum kind_zoptionzIz8bzCEHitz5z9zK { Kind_zNonezIz8bzCEHitz5z9zK, Kind_zSomezIz8bzCEHitz5z9zK };

struct zoptionzIz8bzCEHitz5z9zK {
  enum kind_zoptionzIz8bzCEHitz5z9zK kind;
  union {
    struct { unit zNonezIz8bzCEHitz5z9zK; };
    struct { struct ztuple_z8z5bvzCz0z5enumz0zzHitz9 zSomezIz8bzCEHitz5z9zK; };
  } variants;
};

// struct Hgatp64
struct zHgatp64 {uint64_t zbits;};

// struct Hgatp32
struct zHgatp32 {uint64_t zbits;};

// struct tuple_(%enum zWaitReason, %struct zinstr_info)
struct ztuple_z8z5enumz0zzWaitReasonzCz0z5structz0zzinstr_infoz9 {
  enum zWaitReason ztup0;
  struct zinstr_info ztup1;
};

// union HartState
enum kind_zHartState { Kind_zHART_ACTIVE, Kind_zHART_WAITING };

struct zHartState {
  enum kind_zHartState kind;
  union {
    struct { unit zHART_ACTIVE; };
    struct { struct ztuple_z8z5enumz0zzWaitReasonzCz0z5structz0zzinstr_infoz9 zHART_WAITING; };
  } variants;
};

// enum HGATPMode
enum zHGATPMode : int { zHBare, zSv32x4, zSv39x4, zSv48x4, zSv57x4 };

// union option<EHGATPMode%>
enum kind_zoptionzIEHGATPModez5zK { Kind_zNonezIEHGATPModez5zK, Kind_zSomezIEHGATPModez5zK };

struct zoptionzIEHGATPModez5zK {
  enum kind_zoptionzIEHGATPModez5zK kind;
  union {
    struct { unit zNonezIEHGATPModez5zK; };
    struct { enum zHGATPMode zSomezIEHGATPModez5zK; };
  } variants;
};

// struct HEnvcfg
struct zHEnvcfg {uint64_t zbits;};

// struct GlobalMisalignedExceptions
struct zGlobalMisalignedExceptions {
  struct zoptionzIEmisaligned_exceptionz5zK zamo;
  struct zoptionzIEmisaligned_exceptionz5zK zload_store;
  struct zoptionzIEmisaligned_exceptionz5zK zlrsc;
  struct zoptionzIEmisaligned_exceptionz5zK zvector;
};

// enum FflagsDirtyPolicy
enum zFflagsDirtyPolicy : int { zFflags_Dirty_Precise, zFflags_Dirty_Flag, zFflags_Dirty_Instruction };

// enum FeatureEnabledResult
enum zFeatureEnabledResult : int { zFEATURE_ENABLED, zFEATURE_ILLEGAL, zFEATURE_VIRTUAL };

// enum FcsrRmReservedBehavior
enum zFcsrRmReservedBehavior : int { zFcsr_RM_Fatal, zFcsr_RM_Illegal };

// struct Fcsr
struct zFcsr {uint64_t zbits;};

// union Ext_DataAddr_Check<u>
enum kind_zExt_DataAddr_CheckzIuzK { Kind_zExt_DataAddr_ErrorzIuzK, Kind_zExt_DataAddr_OKzIuzK };

struct zExt_DataAddr_CheckzIuzK {
  enum kind_zExt_DataAddr_CheckzIuzK kind;
  union {
    struct { unit zExt_DataAddr_ErrorzIuzK; };
    struct { sbits zExt_DataAddr_OKzIuzK; };
  } variants;
};

// enum ExtStatus
enum zExtStatus : int { zOff, zInitial, zClean, zDirty };

// enum ExtContextPolicy
enum zExtContextPolicy : int { zExtContext_Off, zExtContext_TwoState, zExtContext_FourState };

// union ExceptionType
enum kind_zExceptionType { Kind_zE_Breakpoint, Kind_zE_Double_Trap, Kind_zE_Extension, Kind_zE_Fetch_Access_Fault, Kind_zE_Fetch_Addr_Align, Kind_zE_Fetch_GPage_Fault, Kind_zE_Fetch_Page_Fault, Kind_zE_Hardware_Error, Kind_zE_Illegal_Instr, Kind_zE_Load_Access_Fault, Kind_zE_Load_Addr_Align, Kind_zE_Load_GPage_Fault, Kind_zE_Load_Page_Fault, Kind_zE_M_EnvCall, Kind_zE_Reserved_14, Kind_zE_Reserved_17, Kind_zE_SAMO_Access_Fault, Kind_zE_SAMO_Addr_Align, Kind_zE_SAMO_GPage_Fault, Kind_zE_SAMO_Page_Fault, Kind_zE_S_EnvCall, Kind_zE_Software_Check, Kind_zE_U_EnvCall, Kind_zE_VS_EnvCall, Kind_zE_Virtual_Instr };

struct zExceptionType {
  enum kind_zExceptionType kind;
  union {
    struct { enum zbreakpoint_cause zE_Breakpoint; };
    struct { unit zE_Double_Trap; };
    struct { unit zE_Extension; };
    struct { unit zE_Fetch_Access_Fault; };
    struct { unit zE_Fetch_Addr_Align; };
    struct { unit zE_Fetch_GPage_Fault; };
    struct { unit zE_Fetch_Page_Fault; };
    struct { unit zE_Hardware_Error; };
    struct { unit zE_Illegal_Instr; };
    struct { unit zE_Load_Access_Fault; };
    struct { unit zE_Load_Addr_Align; };
    struct { unit zE_Load_GPage_Fault; };
    struct { unit zE_Load_Page_Fault; };
    struct { unit zE_M_EnvCall; };
    struct { unit zE_Reserved_14; };
    struct { unit zE_Reserved_17; };
    struct { unit zE_SAMO_Access_Fault; };
    struct { unit zE_SAMO_Addr_Align; };
    struct { unit zE_SAMO_GPage_Fault; };
    struct { unit zE_SAMO_Page_Fault; };
    struct { unit zE_S_EnvCall; };
    struct { unit zE_Software_Check; };
    struct { unit zE_U_EnvCall; };
    struct { unit zE_VS_EnvCall; };
    struct { unit zE_Virtual_Instr; };
  } variants;
};

// struct tuple_(%bv, %union zExceptionType)
struct ztuple_z8z5bvzCz0z5unionz0zzExceptionTypez9 {
  lbits ztup0;
  struct zExceptionType ztup1;
};

// union result<u,(b,UExceptionType)>
enum kind_zresultzIuzCz8bzCUExceptionTypez9zK { Kind_zErrzIuzCz8bzCUExceptionTypez9zK, Kind_zOkzIuzCz8bzCUExceptionTypez9zK };

struct zresultzIuzCz8bzCUExceptionTypez9zK {
  enum kind_zresultzIuzCz8bzCUExceptionTypez9zK kind;
  union {
    struct { struct ztuple_z8z5bvzCz0z5unionz0zzExceptionTypez9 zErrzIuzCz8bzCUExceptionTypez9zK; };
    struct { unit zOkzIuzCz8bzCUExceptionTypez9zK; };
  } variants;
};

// union result<o,(b,UExceptionType)>
enum kind_zresultzIozCz8bzCUExceptionTypez9zK { Kind_zErrzIozCz8bzCUExceptionTypez9zK, Kind_zOkzIozCz8bzCUExceptionTypez9zK };

struct zresultzIozCz8bzCUExceptionTypez9zK {
  enum kind_zresultzIozCz8bzCUExceptionTypez9zK kind;
  union {
    struct { struct ztuple_z8z5bvzCz0z5unionz0zzExceptionTypez9 zErrzIozCz8bzCUExceptionTypez9zK; };
    struct { bool zOkzIozCz8bzCUExceptionTypez9zK; };
  } variants;
};

// union result<b,(b,UExceptionType)>
enum kind_zresultzIbzCz8bzCUExceptionTypez9zK { Kind_zErrzIbzCz8bzCUExceptionTypez9zK, Kind_zOkzIbzCz8bzCUExceptionTypez9zK };

struct zresultzIbzCz8bzCUExceptionTypez9zK {
  enum kind_zresultzIbzCz8bzCUExceptionTypez9zK kind;
  union {
    struct { struct ztuple_z8z5bvzCz0z5unionz0zzExceptionTypez9 zErrzIbzCz8bzCUExceptionTypez9zK; };
    struct { lbits zOkzIbzCz8bzCUExceptionTypez9zK; };
  } variants;
};

// union result<RPhys_Mem_Access_Info,UExceptionType>
enum kind_zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK { Kind_zErrzIRPhys_Mem_Access_InfozCUExceptionTypezK, Kind_zOkzIRPhys_Mem_Access_InfozCUExceptionTypezK };

struct zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK {
  enum kind_zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK kind;
  union {
    struct { struct zExceptionType zErrzIRPhys_Mem_Access_InfozCUExceptionTypezK; };
    struct { struct zPhys_Mem_Access_Info zOkzIRPhys_Mem_Access_InfozCUExceptionTypezK; };
  } variants;
};

// struct tuple_(%bv, %unit)
struct ztuple_z8z5bvzCz0z5unitz9 {
  lbits ztup0;
  unit ztup1;
};

// union result<(b,u),(b,UExceptionType)>
enum kind_zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK { Kind_zErrzIz8bzCuz9zCz8bzCUExceptionTypez9zK, Kind_zOkzIz8bzCuz9zCz8bzCUExceptionTypez9zK };

struct zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK {
  enum kind_zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK kind;
  union {
    struct { struct ztuple_z8z5bvzCz0z5unionz0zzExceptionTypez9 zErrzIz8bzCuz9zCz8bzCUExceptionTypez9zK; };
    struct { struct ztuple_z8z5bvzCz0z5unitz9 zOkzIz8bzCuz9zCz8bzCUExceptionTypez9zK; };
  } variants;
};

// union option<UExceptionType>
enum kind_zoptionzIUExceptionTypezK { Kind_zNonezIUExceptionTypezK, Kind_zSomezIUExceptionTypezK };

struct zoptionzIUExceptionTypezK {
  enum kind_zoptionzIUExceptionTypezK kind;
  union {
    struct { unit zNonezIUExceptionTypezK; };
    struct { struct zExceptionType zSomezIUExceptionTypezK; };
  } variants;
};

// struct tuple_(%union zExceptionType, %sbv64, %union zMemoryAccessTypezIEmem_payloadz5zK)
struct ztuple_z8z5unionz0zzExceptionTypezCz0z5sbv64zCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 {
  struct zExceptionType ztup0;
  sbits ztup1;
  struct zMemoryAccessTypezIEmem_payloadz5zK ztup2;
};

// union PTW_Error
enum kind_zPTW_Error { Kind_zPTW_Ext_Error, Kind_zPTW_Implicit_Error, Kind_zPTW_Invalid_Addr, Kind_zPTW_Invalid_PTE, Kind_zPTW_Misaligned, Kind_zPTW_No_Access, Kind_zPTW_No_Permission, Kind_zPTW_PTE_Needs_Update };

struct zPTW_Error {
  enum kind_zPTW_Error kind;
  union {
    struct { unit zPTW_Ext_Error; };
    struct { struct ztuple_z8z5unionz0zzExceptionTypezCz0z5sbv64zCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKz9 zPTW_Implicit_Error; };
    struct { unit zPTW_Invalid_Addr; };
    struct { unit zPTW_Invalid_PTE; };
    struct { unit zPTW_Misaligned; };
    struct { unit zPTW_No_Access; };
    struct { unit zPTW_No_Permission; };
    struct { unit zPTW_PTE_Needs_Update; };
  } variants;
};

// union result<b,UPTW_Error>
enum kind_zresultzIbzCUPTW_ErrorzK { Kind_zErrzIbzCUPTW_ErrorzK, Kind_zOkzIbzCUPTW_ErrorzK };

struct zresultzIbzCUPTW_ErrorzK {
  enum kind_zresultzIbzCUPTW_ErrorzK kind;
  union {
    struct { struct zPTW_Error zErrzIbzCUPTW_ErrorzK; };
    struct { lbits zOkzIbzCUPTW_ErrorzK; };
  } variants;
};

// union result<Uoption<b>,UPTW_Error>
enum kind_zresultzIUoptionzIbzKzCUPTW_ErrorzK { Kind_zErrzIUoptionzIbzKzCUPTW_ErrorzK, Kind_zOkzIUoptionzIbzKzCUPTW_ErrorzK };

struct zresultzIUoptionzIbzKzCUPTW_ErrorzK {
  enum kind_zresultzIUoptionzIbzKzCUPTW_ErrorzK kind;
  union {
    struct { struct zPTW_Error zErrzIUoptionzIbzKzCUPTW_ErrorzK; };
    struct { struct zoptionzIbzK zOkzIUoptionzIbzKzCUPTW_ErrorzK; };
  } variants;
};

// struct tuple_(%union zPTW_Error, %unit)
struct ztuple_z8z5unionz0zzPTW_ErrorzCz0z5unitz9 {
  struct zPTW_Error ztup0;
  unit ztup1;
};

// struct tuple_(%bv, %enum zpage_based_mem_type, %unit)
struct ztuple_z8z5bvzCz0z5enumz0zzpage_based_mem_typezCz0z5unitz9 {
  lbits ztup0;
  enum zpage_based_mem_type ztup1;
  unit ztup2;
};

// union result<(b,Epage_based_mem_type%,u),(UPTW_Error,u)>
enum kind_zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK { Kind_zErrzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK, Kind_zOkzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK };

struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK {
  enum kind_zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK kind;
  union {
    struct { struct ztuple_z8z5unionz0zzPTW_ErrorzCz0z5unitz9 zErrzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK; };
    struct { struct ztuple_z8z5bvzCz0z5enumz0zzpage_based_mem_typezCz0z5unitz9 zOkzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK; };
  } variants;
};

// struct tuple_(%struct zPTW_Output, %unit)
struct ztuple_z8z5structz0zzPTW_OutputzCz0z5unitz9 {
  struct zPTW_Output ztup0;
  unit ztup1;
};

// union result<(RPTW_Output,u),(UPTW_Error,u)>
enum kind_zresultzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK { Kind_zErrzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK, Kind_zOkzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK };

struct zresultzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK {
  enum kind_zresultzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK kind;
  union {
    struct { struct ztuple_z8z5unionz0zzPTW_ErrorzCz0z5unitz9 zErrzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK; };
    struct { struct ztuple_z8z5structz0zzPTW_OutputzCz0z5unitz9 zOkzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK; };
  } variants;
};

// struct ExceptionContext
struct zExceptionContext {
  sbits zexcinfo;
  struct zoptionzIbzK zexcinfo2;
  bool zexcinfo_is_gva;
  struct zoptionzIbzK zexcinst;
  uint64_t zexcinst_offset;
  struct zoptionzIuzK zext;
  struct zExceptionType ztrap;
};

// struct tuple_(%struct zExceptionContext, %unit)
struct ztuple_z8z5structz0zzExceptionContextzCz0z5unitz9 {
  struct zExceptionContext ztup0;
  unit ztup1;
};

// union result<(b,Epage_based_mem_type%,u),(RExceptionContext,u)>
enum kind_zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK { Kind_zErrzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK, Kind_zOkzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK };

struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK {
  enum kind_zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK kind;
  union {
    struct { struct ztuple_z8z5structz0zzExceptionContextzCz0z5unitz9 zErrzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK; };
    struct { struct ztuple_z8z5bvzCz0z5enumz0zzpage_based_mem_typezCz0z5unitz9 zOkzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK; };
  } variants;
};

// union TrapCause
enum kind_zTrapCause { Kind_zException, Kind_zInterrupt };

struct zTrapCause {
  enum kind_zTrapCause kind;
  union {
    struct { struct zExceptionContext zException; };
    struct { enum zInterruptType zInterrupt; };
  } variants;
};

// union FetchResult
enum kind_zFetchResult { Kind_zF_Base, Kind_zF_Error, Kind_zF_Ext_Error, Kind_zF_RVC };

struct zFetchResult {
  enum kind_zFetchResult kind;
  union {
    struct { uint64_t zF_Base; };
    struct { struct zExceptionContext zF_Error; };
    struct { unit zF_Ext_Error; };
    struct { uint64_t zF_RVC; };
  } variants;
};

// union FetchBytes_Result
enum kind_zFetchBytes_Result { Kind_zFetchBytes_Exception, Kind_zFetchBytes_Ext_Error, Kind_zFetchBytes_Success };

struct zFetchBytes_Result {
  enum kind_zFetchBytes_Result kind;
  union {
    struct { struct zExceptionContext zFetchBytes_Exception; };
    struct { unit zFetchBytes_Ext_Error; };
    struct { lbits zFetchBytes_Success; };
  } variants;
};

// struct tuple_(%enum zPrivilege, %struct zExceptionContext, %sbv64)
struct ztuple_z8z5enumz0zzPrivilegezCz0z5structz0zzExceptionContextzCz0z5sbv64z9 {
  enum zPrivilege ztup0;
  struct zExceptionContext ztup1;
  sbits ztup2;
};

// union ExecutionResult
enum kind_zExecutionResult { Kind_zEnter_Wait, Kind_zExecuteAs, Kind_zExt_CSR_Check_Failure, Kind_zExt_ControlAddr_Check_Failure, Kind_zExt_DataAddr_Check_Failure, Kind_zExt_XRET_Priv_Failure, Kind_zIllegal_Instruction, Kind_zPendingTrigger, Kind_zRetire_Success, Kind_zTrap, Kind_zVirtual_Instruction };

struct zExecutionResult {
  enum kind_zExecutionResult kind;
  union {
    struct { enum zWaitReason zEnter_Wait; };
    struct { struct zinstruction zExecuteAs; };
    struct { unit zExt_CSR_Check_Failure; };
    struct { unit zExt_ControlAddr_Check_Failure; };
    struct { unit zExt_DataAddr_Check_Failure; };
    struct { unit zExt_XRET_Priv_Failure; };
    struct { unit zIllegal_Instruction; };
    struct { struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9 zPendingTrigger; };
    struct { unit zRetire_Success; };
    struct { struct ztuple_z8z5enumz0zzPrivilegezCz0z5structz0zzExceptionContextzCz0z5sbv64z9 zTrap; };
    struct { unit zVirtual_Instruction; };
  } variants;
};

// union result<o,UExecutionResult>
enum kind_zresultzIozCUExecutionResultzK { Kind_zErrzIozCUExecutionResultzK, Kind_zOkzIozCUExecutionResultzK };

struct zresultzIozCUExecutionResultzK {
  enum kind_zresultzIozCUExecutionResultzK kind;
  union {
    struct { struct zExecutionResult zErrzIozCUExecutionResultzK; };
    struct { bool zOkzIozCUExecutionResultzK; };
  } variants;
};

// union result<b,UExecutionResult>
enum kind_zresultzIbzCUExecutionResultzK { Kind_zErrzIbzCUExecutionResultzK, Kind_zOkzIbzCUExecutionResultzK };

struct zresultzIbzCUExecutionResultzK {
  enum kind_zresultzIbzCUExecutionResultzK kind;
  union {
    struct { struct zExecutionResult zErrzIbzCUExecutionResultzK; };
    struct { lbits zOkzIbzCUExecutionResultzK; };
  } variants;
};

// struct tuple_(%bv, %bv)
struct ztuple_z8z5bvzCz0z5bvz9 {
  lbits ztup0;
  lbits ztup1;
};

// union result<(b,b),UExecutionResult>
enum kind_zresultzIz8bzCbz9zCUExecutionResultzK { Kind_zErrzIz8bzCbz9zCUExecutionResultzK, Kind_zOkzIz8bzCbz9zCUExecutionResultzK };

struct zresultzIz8bzCbz9zCUExecutionResultzK {
  enum kind_zresultzIz8bzCbz9zCUExecutionResultzK kind;
  union {
    struct { struct zExecutionResult zErrzIz8bzCbz9zCUExecutionResultzK; };
    struct { struct ztuple_z8z5bvzCz0z5bvz9 zOkzIz8bzCbz9zCUExecutionResultzK; };
  } variants;
};

// struct tuple_(%union zExecutionResult, %struct zinstr_info)
struct ztuple_z8z5unionz0zzExecutionResultzCz0z5structz0zzinstr_infoz9 {
  struct zExecutionResult ztup0;
  struct zinstr_info ztup1;
};

// union Step
enum kind_zStep { Kind_zStep_Execute, Kind_zStep_Ext_Fetch_Failure, Kind_zStep_Fetch_Failure, Kind_zStep_Fetch_Trigger, Kind_zStep_Pending_Interrupt, Kind_zStep_Pending_Trigger, Kind_zStep_Waiting };

struct zStep {
  enum kind_zStep kind;
  union {
    struct { struct ztuple_z8z5unionz0zzExecutionResultzCz0z5structz0zzinstr_infoz9 zStep_Execute; };
    struct { unit zStep_Ext_Fetch_Failure; };
    struct { struct zExceptionContext zStep_Fetch_Failure; };
    struct { struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9 zStep_Fetch_Trigger; };
    struct { struct ztuple_z8z5enumz0zzInterruptTypezCz0z5enumz0zzPrivilegez9 zStep_Pending_Interrupt; };
    struct { struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9 zStep_Pending_Trigger; };
    struct { enum zWaitReason zStep_Waiting; };
  } variants;
};

// enum Event
enum zEvent : int { zEV_FENCE, zEV_TLB_MISS, zEV_MISALIGNED_LOAD_EXCEPTION, zEV_MISALIGNED_STORE_EXCEPTION };

// struct event_selector
struct zevent_selector {
  enum zEvent zevent;
  uint64_t zselector;
};

// struct ETrigger
struct zETrigger {
  enum zTrig_Action zaction;
  bool zdmode;
  bool zhit;
  bool zm;
  bool zpending;
  bool zs;
  sbits ztdata2;
  struct zTExtra ztextra;
  bool zu;
  bool zvs;
  bool zvu;
};

// struct Counterin
struct zCounterin {uint64_t zbits;};

// struct Counteren
struct zCounteren {uint64_t zbits;};

// struct CountSmcntrpmf
struct zCountSmcntrpmf {uint64_t zbits;};

// enum Compare_Selection
enum zCompare_Selection : int { zCompare_Address, zCompare_Data };

// struct MControl6
struct zMControl6 {
  enum zTrig_Action zaction;
  bool zchain;
  bool zdmode;
  bool zexecute;
  enum zHit zhit;
  bool zload;
  bool zm;
  struct zoptionzIz8bzCEHitz5z9zK zmatch_info;
  bool zs;
  enum zCompare_Selection zselect;
  int64_t zsizze;
  bool zstore;
  enum zTrig_Match zt_match;
  sbits ztdata2;
  struct zTExtra ztextra;
  bool zu;
  bool zuncertain;
  bool zuncertainen;
  bool zvs;
  bool zvu;
};

// union Trigger
enum kind_zTrigger { Kind_zT_disabled, Kind_zT_etrigger, Kind_zT_icount, Kind_zT_itrigger, Kind_zT_mcontrol6 };

struct zTrigger {
  enum kind_zTrigger kind;
  union {
    struct { struct zTDisabled zT_disabled; };
    struct { struct zETrigger zT_etrigger; };
    struct { struct zICount zT_icount; };
    struct { struct zITrigger zT_itrigger; };
    struct { struct zMControl6 zT_mcontrol6; };
  } variants;
};

// union CSRCheckResult
enum kind_zCSRCheckResult { Kind_zCSR_Check_OK, Kind_zCSR_Illegal, Kind_zCSR_Virtual };

struct zCSRCheckResult {
  enum kind_zCSRCheckResult kind;
  union {
    struct { unit zCSR_Check_OK; };
    struct { unit zCSR_Illegal; };
    struct { unit zCSR_Virtual; };
  } variants;
};

// enum CSRBitConfig
enum zCSRBitConfig : int { zCSRBit_Writable, zCSRBit_ReadOnlyZero, zCSRBit_ReadOnlyOne };

// enum CSRAccessType
enum zCSRAccessType : int { zCSRRead, zCSRWrite, zCSRReadWrite };

// enum AtomicSupport
enum zAtomicSupport : int { zAMONone, zAMOSwap, zAMOLogical, zAMOArithmetic, zAMOCASW, zAMOCASD, zAMOCASQ };

// struct PMA
struct zPMA {
  enum zAtomicSupport zatomic_support;
  bool zcacheable;
  bool zcoherent;
  bool zexecutable;
  enum zMemoryRegionType zmem_type;
  int64_t zmisaligned_atomicity_granule_sizze_exp;
  struct zPMAMisalignedExceptions zmisaligned_exceptions;
  bool zread_idempotent;
  bool zreadable;
  enum zReservability zreservability;
  bool zsupports_cbo_zzero;
  bool zsupports_pte_read;
  bool zsupports_pte_write;
  int64_t zvector_misaligned_atomicity_granule_sizze_exp;
  bool zwritable;
  bool zwrite_idempotent;
};

// struct PMA_Region
struct zPMA_Region {
  struct zPMA zattributes;
  uint64_t zbase;
  bool zinclude_in_device_tree;
  uint64_t zsizze;
};

// union option<RPMA_Region>
enum kind_zoptionzIRPMA_RegionzK { Kind_zNonezIRPMA_RegionzK, Kind_zSomezIRPMA_RegionzK };

struct zoptionzIRPMA_RegionzK {
  enum kind_zoptionzIRPMA_RegionzK kind;
  union {
    struct { unit zNonezIRPMA_RegionzK; };
    struct { struct zPMA_Region zSomezIRPMA_RegionzK; };
  } variants;
};

// enum Architecture
enum zArchitecture : int { zRV32, zRV64, zRV128 };

// enum AmocasOddRegisterReservedBehavior
enum zAmocasOddRegisterReservedBehavior : int { zAMOCAS_Fatal, zAMOCAS_Illegal };

// struct AccessInfo
struct zAccessInfo {
  bool zas_guest;
  enum zPrivilege zeff_privilege;
  int64_t zpmlen;
};

struct zz5vecz8z5sbv64z9 {
  size_t len;
  sbits *data;
};
typedef struct zz5vecz8z5sbv64z9 zz5vecz8z5sbv64z9;

struct zz5vecz8z5vecz8z5sbv64z9z9 {
  size_t len;
  zz5vecz8z5sbv64z9 *data;
};
typedef struct zz5vecz8z5vecz8z5sbv64z9z9 zz5vecz8z5vecz8z5sbv64z9z9;

struct zz5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9 {
  size_t len;
  struct zoptionzIRTLB_EntryzK *data;
};
typedef struct zz5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9 zz5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9;

struct zz5vecz8z5enumz0zzextensionz9 {
  size_t len;
  enum zextension *data;
};
typedef struct zz5vecz8z5enumz0zzextensionz9 zz5vecz8z5enumz0zzextensionz9;

struct zz5vecz8z5bv16z9 {
  size_t len;
  uint64_t *data;
};
typedef struct zz5vecz8z5bv16z9 zz5vecz8z5bv16z9;

struct zz5vecz8z5bv8z9 {
  size_t len;
  uint64_t *data;
};
typedef struct zz5vecz8z5bv8z9 zz5vecz8z5bv8z9;

struct zz5vecz8z5unionz0zzTriggerz9 {
  size_t len;
  struct zTrigger *data;
};
typedef struct zz5vecz8z5unionz0zzTriggerz9 zz5vecz8z5unionz0zzTriggerz9;

struct zz5vecz8z5bv5z9 {
  size_t len;
  uint64_t *data;
};
typedef struct zz5vecz8z5bv5z9 zz5vecz8z5bv5z9;

struct zz5vecz8z5bv64z9 {
  size_t len;
  uint64_t *data;
};
typedef struct zz5vecz8z5bv64z9 zz5vecz8z5bv64z9;

struct zz5vecz8z5bv32z9 {
  size_t len;
  uint64_t *data;
};
typedef struct zz5vecz8z5bv32z9 zz5vecz8z5bv32z9;

struct zz5vecz8z5structz0zzPmpcfg_entz9 {
  size_t len;
  struct zPmpcfg_ent *data;
};
typedef struct zz5vecz8z5structz0zzPmpcfg_entz9 zz5vecz8z5structz0zzPmpcfg_entz9;

struct node_zz5listz8z5structz0zzPMA_Regionz9 {
  unsigned int rc;
  struct zPMA_Region hd;
  struct node_zz5listz8z5structz0zzPMA_Regionz9 *tl;
};
typedef struct node_zz5listz8z5structz0zzPMA_Regionz9 *zz5listz8z5structz0zzPMA_Regionz9;

// struct tuple_(%i, %string)
struct ztuple_z8z5izCz0z5stringz9 {
  sail_int ztup0;
  sail_string ztup1;
};

// struct tuple_(%i64, %string)
struct ztuple_z8z5i64zCz0z5stringz9 {
  int64_t ztup0;
  sail_string ztup1;
};

// struct tuple_(%union zTrigger, %enum zTrig_Action, %bool)
struct ztuple_z8z5unionz0zzTriggerzCz0z5enumz0zzTrig_ActionzCz0z5boolz9 {
  struct zTrigger ztup0;
  enum zTrig_Action ztup1;
  bool ztup2;
};

// struct tuple_(%bool, %bool)
struct ztuple_z8z5boolzCz0z5boolz9 {
  bool ztup0;
  bool ztup1;
};

// struct tuple_(%enum zPM_Ext, %enum zPointerMaskingMode)
struct ztuple_z8z5enumz0zzPM_ExtzCz0z5enumz0zzPointerMaskingModez9 {
  enum zPM_Ext ztup0;
  enum zPointerMaskingMode ztup1;
};

// struct tuple_(%bv2, %bv1)
struct ztuple_z8z5bv2zCz0z5bv1z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%enum zArchitecture, %bv4)
struct ztuple_z8z5enumz0zzArchitecturezCz0z5bv4z9 {
  enum zArchitecture ztup0;
  uint64_t ztup1;
};

// struct tuple_(%vec(%bv8), %vec(%bool))
struct ztuple_z8z5vecz8z5bv8z9zCz0z5vecz8z5boolz9z9 {
  zz5vecz8z5bv8z9 ztup0;
  zz5vecz8z5boolz9 ztup1;
};

// struct tuple_(%string, %sbv64, %i64, %bv)
struct ztuple_z8z5stringzCz0z5sbv64zCz0z5i64zCz0z5bvz9 {
  sail_string ztup0;
  sbits ztup1;
  int64_t ztup2;
  lbits ztup3;
};

// struct tuple_(%sbv64, %bv6)
struct ztuple_z8z5sbv64zCz0z5bv6z9 {
  sbits ztup0;
  uint64_t ztup1;
};

// struct tuple_(%string, %sbv64, %sbv64)
struct ztuple_z8z5stringzCz0z5sbv64zCz0z5sbv64z9 {
  sail_string ztup0;
  sbits ztup1;
  sbits ztup2;
};

// struct tuple_(%string, %bv12, %sbv64)
struct ztuple_z8z5stringzCz0z5bv12zCz0z5sbv64z9 {
  sail_string ztup0;
  uint64_t ztup1;
  sbits ztup2;
};

// struct tuple_(%bool, %bv6)
struct ztuple_z8z5boolzCz0z5bv6z9 {
  bool ztup0;
  uint64_t ztup1;
};

struct node_zz5listz8z5structz0zzevent_selectorz9 {
  unsigned int rc;
  struct zevent_selector hd;
  struct node_zz5listz8z5structz0zzevent_selectorz9 *tl;
};
typedef struct node_zz5listz8z5structz0zzevent_selectorz9 *zz5listz8z5structz0zzevent_selectorz9;

// struct tuple_(%i64, %enum zevent_csr)
struct ztuple_z8z5i64zCz0z5enumz0zzevent_csrz9 {
  int64_t ztup0;
  enum zevent_csr ztup1;
};

// struct tuple_(%bv5, %bv16)
struct ztuple_z8z5bv5zCz0z5bv16z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv5, %bv32)
struct ztuple_z8z5bv5zCz0z5bv32z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv5, %bv64)
struct ztuple_z8z5bv5zCz0z5bv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv5, %bool)
struct ztuple_z8z5bv5zCz0z5boolz9 {
  uint64_t ztup0;
  bool ztup1;
};

// struct tuple_(%bv5, %bv)
struct ztuple_z8z5bv5zCz0z5bvz9 {
  uint64_t ztup0;
  lbits ztup1;
};

// struct tuple_(%sbv64, %enum zHit)
struct ztuple_z8z5sbv64zCz0z5enumz0zzHitz9 {
  sbits ztup0;
  enum zHit ztup1;
};

// struct tuple_(%bv12, %enum zPrivilege)
struct ztuple_z8z5bv12zCz0z5enumz0zzPrivilegez9 {
  uint64_t ztup0;
  enum zPrivilege ztup1;
};

// struct tuple_(%sbv64, %enum zPrivilege)
struct ztuple_z8z5sbv64zCz0z5enumz0zzPrivilegez9 {
  sbits ztup0;
  enum zPrivilege ztup1;
};

// struct tuple_(%bool, %union zoptionzIbzK, %union zoptionzIbzK, %union zoptionzIbzK, %union zoptionzIuzK)
struct ztuple_z8z5boolzCz0z5unionz0zzoptionzzIbzzKzCz0z5unionz0zzoptionzzIbzzKzCz0z5unionz0zzoptionzzIbzzKzCz0z5unionz0zzoptionzzIuzzKz9 {
  bool ztup0;
  struct zoptionzIbzK ztup1;
  struct zoptionzIbzK ztup2;
  struct zoptionzIbzK ztup3;
  struct zoptionzIuzK ztup4;
};

// struct tuple_(%sbv64, %union zExceptionType)
struct ztuple_z8z5sbv64zCz0z5unionz0zzExceptionTypez9 {
  sbits ztup0;
  struct zExceptionType ztup1;
};

// struct tuple_(%i64, %i64)
struct ztuple_z8z5i64zCz0z5i64z9 {
  int64_t ztup0;
  int64_t ztup1;
};

// struct tuple_(%i, %i, %i64)
struct ztuple_z8z5izCz0z5izCz0z5i64z9 {
  sail_int ztup0;
  sail_int ztup1;
  int64_t ztup2;
};

// struct tuple_(%i64, %i, %i64)
struct ztuple_z8z5i64zCz0z5izCz0z5i64z9 {
  int64_t ztup0;
  sail_int ztup1;
  int64_t ztup2;
};

// struct tuple_(%i, %i64, %i64)
struct ztuple_z8z5izCz0z5i64zCz0z5i64z9 {
  sail_int ztup0;
  int64_t ztup1;
  int64_t ztup2;
};

// struct tuple_(%enum zSplittability, %i64)
struct ztuple_z8z5enumz0zzSplittabilityzCz0z5i64z9 {
  enum zSplittability ztup0;
  int64_t ztup1;
};

// struct tuple_(%bool, %union zoptionzIizK)
struct ztuple_z8z5boolzCz0z5unionz0zzoptionzzIizzKz9 {
  bool ztup0;
  struct zoptionzIizK ztup1;
};

// struct tuple_(%bool, %bool, %bool)
struct ztuple_z8z5boolzCz0z5boolzCz0z5boolz9 {
  bool ztup0;
  bool ztup1;
  bool ztup2;
};

// struct tuple_(%i64, %i64, %i64)
struct ztuple_z8z5i64zCz0z5i64zCz0z5i64z9 {
  int64_t ztup0;
  int64_t ztup1;
  int64_t ztup2;
};

// struct tuple_(%union zMemoryAccessTypezIEmem_payloadz5zK, %union zPTW_Error)
struct ztuple_z8z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKzCz0z5unionz0zzPTW_Errorz9 {
  struct zMemoryAccessTypezIEmem_payloadz5zK ztup0;
  struct zPTW_Error ztup1;
};

// struct tuple_(%enum zTranslationStage, %i64, %bv64, %union zMemoryAccessTypezIEmem_payloadz5zK, %enum zPrivilege)
struct ztuple_z8z5enumz0zzTranslationStagezCz0z5i64zCz0z5bv64zCz0z5unionz0zzMemoryAccessTypezzIEmem_payloadzz5zzKzCz0z5enumz0zzPrivilegez9 {
  enum zTranslationStage ztup0;
  int64_t ztup1;
  uint64_t ztup2;
  struct zMemoryAccessTypezIEmem_payloadz5zK ztup3;
  enum zPrivilege ztup4;
};

// struct tuple_(%enum zTranslationStage, %i64, %sbv64, %bv64)
struct ztuple_z8z5enumz0zzTranslationStagezCz0z5i64zCz0z5sbv64zCz0z5bv64z9 {
  enum zTranslationStage ztup0;
  int64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zTranslationStage, %i64, %bv64)
struct ztuple_z8z5enumz0zzTranslationStagezCz0z5i64zCz0z5bv64z9 {
  enum zTranslationStage ztup0;
  int64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zTranslationStage, %i64, %union zPTW_Error, %sbv64)
struct ztuple_z8z5enumz0zzTranslationStagezCz0z5i64zCz0z5unionz0zzPTW_ErrorzCz0z5sbv64z9 {
  enum zTranslationStage ztup0;
  int64_t ztup1;
  struct zPTW_Error ztup2;
  sbits ztup3;
};

// struct tuple_(%vec(%union zoptionzIRTLB_EntryzK), %i64)
struct ztuple_z8z5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9zCz0z5i64z9 {
  zz5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9 ztup0;
  int64_t ztup1;
};

// struct tuple_(%i64, %struct zTLB_Entry)
struct ztuple_z8z5i64zCz0z5structz0zzTLB_Entryz9 {
  int64_t ztup0;
  struct zTLB_Entry ztup1;
};

// struct tuple_(%sbv64, %enum zpage_based_mem_type, %unit)
struct ztuple_z8z5sbv64zCz0z5enumz0zzpage_based_mem_typezCz0z5unitz9 {
  sbits ztup0;
  enum zpage_based_mem_type ztup1;
  unit ztup2;
};

// struct tuple_(%enum zTranslationStage, %enum zSATPMode)
struct ztuple_z8z5enumz0zzTranslationStagezCz0z5enumz0zzSATPModez9 {
  enum zTranslationStage ztup0;
  enum zSATPMode ztup1;
};

// struct tuple_(%sbv64, %bv)
struct ztuple_z8z5sbv64zCz0z5bvz9 {
  sbits ztup0;
  lbits ztup1;
};

// struct tuple_(%bv1, %bv8, %bv23)
struct ztuple_z8z5bv1zCz0z5bv8zCz0z5bv23z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bool, %bv5)
struct ztuple_z8z5boolzCz0z5bv5z9 {
  bool ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv1, %bv11, %bv52)
struct ztuple_z8z5bv1zCz0z5bv11zCz0z5bv52z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv1, %bv5, %bv10)
struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv10z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%vec(%bv), %bv)
struct ztuple_z8z5vecz8z5bvz9zCz0z5bvz9 {
  zz5vecz8z5bvz9 ztup0;
  lbits ztup1;
};

// struct tuple_(%bv5, %bv8)
struct ztuple_z8z5bv5zCz0z5bv8z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv64, %bv64)
struct ztuple_z8z5bv64zCz0z5bv64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv64, %bv64, %bv1, %i64, %i64)
struct ztuple_z8z5bv64zCz0z5bv64zCz0z5bv1zCz0z5i64zCz0z5i64z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  int64_t ztup3;
  int64_t ztup4;
};

struct zz5vecz8z5iz9 {
  size_t len;
  sail_int *data;
};
typedef struct zz5vecz8z5iz9 zz5vecz8z5iz9;

// struct tuple_(%bool, %bv64)
struct ztuple_z8z5boolzCz0z5bv64z9 {
  bool ztup0;
  uint64_t ztup1;
};

// struct tuple_(%bv3, %bv1, %bv1, %bv3, %bv3)
struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
  uint64_t ztup4;
};

// struct tuple_(%enum zcsrop, %bool, %bool)
struct ztuple_z8z5enumz0zzcsropzCz0z5boolzCz0z5boolz9 {
  enum zcsrop ztup0;
  bool ztup1;
  bool ztup2;
};

// struct tuple_(%bv1, %bv8, %bv7)
struct ztuple_z8z5bv1zCz0z5bv8zCz0z5bv7z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zcbop_zzicbop, %sbv64)
struct ztuple_z8z5enumz0zzcbop_zzzzicbopzCz0z5sbv64z9 {
  enum zcbop_zzicbop ztup0;
  sbits ztup1;
};

// struct tuple_(%enum zcsrop, %sbv64)
struct ztuple_z8z5enumz0zzcsropzCz0z5sbv64z9 {
  enum zcsrop ztup0;
  sbits ztup1;
};

// struct tuple_(%sbv64, %enum zbiop)
struct ztuple_z8z5sbv64zCz0z5enumz0zzbiopz9 {
  sbits ztup0;
  enum zbiop ztup1;
};

// struct tuple_(%sbv64, %enum zuop)
struct ztuple_z8z5sbv64zCz0z5enumz0zzuopz9 {
  sbits ztup0;
  enum zuop ztup1;
};

// struct tuple_(%enum znifunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zznifunct6zCz0z5bv5zCz0z5bv5z9 {
  enum znifunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum znisfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zznisfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum znisfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvicmpfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvicmpfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvicmpfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvifunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvifunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvifunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvimcfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimcfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvimcfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvimfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvimfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvimsfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvimsfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvimsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%enum zvisgfunct6, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvisgfunct6zCz0z5bv5zCz0z5bv5z9 {
  enum zvisgfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%sbv64, %enum zcsrop, %sbv64)
struct ztuple_z8z5sbv64zCz0z5enumz0zzcsropzCz0z5sbv64z9 {
  sbits ztup0;
  enum zcsrop ztup1;
  sbits ztup2;
};

// struct tuple_(%sbv64, %enum ziop, %sbv64)
struct ztuple_z8z5sbv64zCz0z5enumz0zziopzCz0z5sbv64z9 {
  sbits ztup0;
  enum ziop ztup1;
  sbits ztup2;
};

// struct tuple_(%sbv64, %enum zrounding_mode, %bv5)
struct ztuple_z8z5sbv64zCz0z5enumz0zzrounding_modezCz0z5bv5z9 {
  sbits ztup0;
  enum zrounding_mode ztup1;
  uint64_t ztup2;
};

// struct tuple_(%sbv64, %sbv64, %enum zbop)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5enumz0zzbopz9 {
  sbits ztup0;
  sbits ztup1;
  enum zbop ztup2;
};

// struct tuple_(%sbv64, %i64, %bv5)
struct ztuple_z8z5sbv64zCz0z5i64zCz0z5bv5z9 {
  sbits ztup0;
  int64_t ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %enum zrounding_mode, %sbv64)
struct ztuple_z8z5bv5zCz0z5enumz0zzrounding_modezCz0z5sbv64z9 {
  uint64_t ztup0;
  enum zrounding_mode ztup1;
  sbits ztup2;
};

// struct tuple_(%bv5, %enum zvextfunct6, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzvextfunct6zCz0z5bv5z9 {
  uint64_t ztup0;
  enum zvextfunct6 ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %enum zvfnunary0, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzvfnunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  enum zvfnunary0 ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %enum zvfunary0, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzvfunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  enum zvfunary0 ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %enum zvfunary1, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzvfunary1zCz0z5bv5z9 {
  uint64_t ztup0;
  enum zvfunary1 ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %enum zvfwunary0, %bv5)
struct ztuple_z8z5bv5zCz0z5enumz0zzvfwunary0zCz0z5bv5z9 {
  uint64_t ztup0;
  enum zvfwunary0 ztup1;
  uint64_t ztup2;
};

// struct tuple_(%bv5, %sbv64, %i64)
struct ztuple_z8z5bv5zCz0z5sbv64zCz0z5i64z9 {
  uint64_t ztup0;
  sbits ztup1;
  int64_t ztup2;
};

// struct tuple_(%enum zfvffunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvffunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvfmafunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvfmafunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvfmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvfmfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvfmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvfmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvvmafunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvmafunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfvvmfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfvvmfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfvvmfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwffunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwffunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwvffunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvffunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvffunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwvfmafunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvfmafunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvfmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zfwvvmafunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzfwvvmafunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zfwvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zmvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzmvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zmvvmafunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzmvvmafunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zmvvmafunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zmvxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzmvxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zmvxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zmvxmafunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzmvxmafunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zmvxmafunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum znvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum znvsfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zznvsfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum znvsfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum znxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zznxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum znxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum znxsfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zznxsfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum znxsfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zrfvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrfvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrfvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zrfwvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrfwvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrfwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zrivvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrivvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrivvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zrmvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzrmvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zrmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvvcmpfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvcmpfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvcmpfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxcmpfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxcmpfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxcmpfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zvxsgfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzvxsgfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zvxsgfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwmvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwmvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwmvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwmvxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwmvxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwmvxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwvvfunct6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzwvvfunct6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zwvvfunct6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwvxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwvxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwvxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zwxfunct6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzwxfunct6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zwxfunct6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zzzvabd_vabd_func6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zzzvabd_vabd_func6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zzzvabd_vabd_func6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vabd_func6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvabd_vabd_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zzzvabd_vwabda_func6, %bv5, %sbv64, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv5zCz0z5sbv64zCz0z5bv5z9 {
  enum zzzvabd_vwabda_func6 ztup0;
  uint64_t ztup1;
  sbits ztup2;
  uint64_t ztup3;
};

// struct tuple_(%enum zzzvabd_vwabda_func6, %bv5, %bv5, %bv5)
struct ztuple_z8z5enumz0zzzzzzvabd_vwabda_func6zCz0z5bv5zCz0z5bv5zCz0z5bv5z9 {
  enum zzzvabd_vwabda_func6 ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  uint64_t ztup3;
};

// struct tuple_(%sbv64, %bool, %i64, %sbv64)
struct ztuple_z8z5sbv64zCz0z5boolzCz0z5i64zCz0z5sbv64z9 {
  sbits ztup0;
  bool ztup1;
  int64_t ztup2;
  sbits ztup3;
};

// struct tuple_(%sbv64, %sbv64, %enum zzzicondop, %sbv64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5enumz0zzzzzzicondopzCz0z5sbv64z9 {
  sbits ztup0;
  sbits ztup1;
  enum zzzicondop ztup2;
  sbits ztup3;
};

// struct tuple_(%sbv64, %sbv64, %struct zmul_op, %sbv64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5structz0zzmul_opzCz0z5sbv64z9 {
  sbits ztup0;
  sbits ztup1;
  struct zmul_op ztup2;
  sbits ztup3;
};

// struct tuple_(%sbv64, %sbv64, %bool, %sbv64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5boolzCz0z5sbv64z9 {
  sbits ztup0;
  sbits ztup1;
  bool ztup2;
  sbits ztup3;
};

// struct tuple_(%bv5, %bv5, %enum zrounding_mode, %bv5)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  enum zrounding_mode ztup2;
  uint64_t ztup3;
};

// struct tuple_(%i64, %bool, %sbv64, %sbv64)
struct ztuple_z8z5i64zCz0z5boolzCz0z5sbv64zCz0z5sbv64z9 {
  int64_t ztup0;
  bool ztup1;
  sbits ztup2;
  sbits ztup3;
};

// struct tuple_(%bv5, %bv5, %bv5, %enum zrounding_mode, %bv5)
struct ztuple_z8z5bv5zCz0z5bv5zCz0z5bv5zCz0z5enumz0zzrounding_modezCz0z5bv5z9 {
  uint64_t ztup0;
  uint64_t ztup1;
  uint64_t ztup2;
  enum zrounding_mode ztup3;
  uint64_t ztup4;
};

// struct tuple_(%i64, %sbv64, %sbv64, %enum zvlewidth, %bv5)
struct ztuple_z8z5i64zCz0z5sbv64zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 {
  int64_t ztup0;
  sbits ztup1;
  sbits ztup2;
  enum zvlewidth ztup3;
  uint64_t ztup4;
};

// struct tuple_(%i64, %enum zindexed_mop, %bv5, %sbv64, %enum zvlewidth, %bv5)
struct ztuple_z8z5i64zCz0z5enumz0zzindexed_mopzCz0z5bv5zCz0z5sbv64zCz0z5enumz0zzvlewidthzCz0z5bv5z9 {
  int64_t ztup0;
  enum zindexed_mop ztup1;
  uint64_t ztup2;
  sbits ztup3;
  enum zvlewidth ztup4;
  uint64_t ztup5;
};

// struct tuple_(%vec(%sbv64), %bv)
struct ztuple_z8z5vecz8z5sbv64z9zCz0z5bvz9 {
  zz5vecz8z5sbv64z9 ztup0;
  lbits ztup1;
};

// struct tuple_(%sbv64, %enum zpage_based_mem_type)
struct ztuple_z8z5sbv64zCz0z5enumz0zzpage_based_mem_typez9 {
  sbits ztup0;
  enum zpage_based_mem_type ztup1;
};

// struct tuple_(%bv2, %bv2)
struct ztuple_z8z5bv2zCz0z5bv2z9 {
  uint64_t ztup0;
  uint64_t ztup1;
};

// struct tuple_(%sbv64, %sbv64, %sbv64, %i64)
struct ztuple_z8z5sbv64zCz0z5sbv64zCz0z5sbv64zCz0z5i64z9 {
  sbits ztup0;
  sbits ztup1;
  sbits ztup2;
  int64_t ztup3;
};

// struct tuple_(%bv12, %enum zPrivilege, %enum zCSRAccessType)
struct ztuple_z8z5bv12zCz0z5enumz0zzPrivilegezCz0z5enumz0zzCSRAccessTypez9 {
  uint64_t ztup0;
  enum zPrivilege ztup1;
  enum zCSRAccessType ztup2;
};

// struct tuple_(%bv12, %sbv64)
struct ztuple_z8z5bv12zCz0z5sbv64z9 {
  uint64_t ztup0;
  sbits ztup1;
};

// struct tuple_(%enum zWaitReason, %bool, %bool)
struct ztuple_z8z5enumz0zzWaitReasonzCz0z5boolzCz0z5boolz9 {
  enum zWaitReason ztup0;
  bool ztup1;
  bool ztup2;
};

// struct tuple_(%union zoptionzIUinstructionzK, %union zExecutionResult)
struct ztuple_z8z5unionz0zzoptionzzIUinstructionzzKzCz0z5unionz0zzExecutionResultz9 {
  struct zoptionzIUinstructionzK ztup0;
  struct zExecutionResult ztup1;
};

// struct tuple_(%sbv64, %bv16, %i64)
struct ztuple_z8z5sbv64zCz0z5bv16zCz0z5i64z9 {
  sbits ztup0;
  uint64_t ztup1;
  int64_t ztup2;
};

// struct tuple_(%sbv64, %bv32, %i64)
struct ztuple_z8z5sbv64zCz0z5bv32zCz0z5i64z9 {
  sbits ztup0;
  uint64_t ztup1;
  int64_t ztup2;
};

// struct tuple_(%union zoptionzIRPMA_RegionzK, %union zoptionzIEMemoryRegionTypez5zK)
struct ztuple_z8z5unionz0zzoptionzzIRPMA_RegionzzKzCz0z5unionz0zzoptionzzIEMemoryRegionTypezz5zzKz9 {
  struct zoptionzIRPMA_RegionzK ztup0;
  struct zoptionzIEMemoryRegionTypez5zK ztup1;
};

class Model : protected PlatformInterface {
public:

  void sail_set_abstract_xlen(void);

  void sail_set_abstract_vmidlen(void);

  void sail_set_abstract_vlen_exp(void);

  void sail_set_abstract_sdtrig_mcontrol6_maskmax(void);

  void sail_set_abstract_plat_hpmevent_width_bits(void);

  void sail_set_abstract_plat_hpmcounter_width_bits(void);

  void sail_set_abstract_physaddr_bits(void);

  void sail_set_abstract_num_triggers(void);

  void sail_set_abstract_geilen(void);

  void sail_set_abstract_ext_d_supported(void);

  void sail_set_abstract_elen_exp(void);

  void sail_set_abstract_base_E_enabled(void);

  void sail_set_abstract_asidlen(void);

  void z__id(sail_int *rop, sail_int);

  bool zis_nonezIz8izCEtdataz5z9zK(struct zoptionzIz8izCEtdataz5z9zK);

  bool zis_nonezIz8bzCEHitz5z9zK(struct zoptionzIz8bzCEHitz5z9zK);

  bool zis_somezIbzK(struct zoptionzIbzK);

  bool zis_somezIz8bzCEHitz5z9zK(struct zoptionzIz8bzCEHitz5z9zK);

  bool zis_somezIRPMA_RegionzK(struct zoptionzIRPMA_RegionzK);

  bool zneq_int(sail_int, sail_int);

  bool zneq_bool(bool, bool);

  void zsail_ones(lbits *rop, sail_int);

  void startup_zsail_ones(void);

  void finish_zsail_ones(void);

  void zto_bytes_le(zz5vecz8z5bv8z9 *rop, sail_int, lbits);

  void startup_zto_bytes_le(void);

  void finish_zto_bytes_le(void);

  void zfrom_bytes_le(lbits *rop, sail_int, zz5vecz8z5bv8z9);

  void startup_zfrom_bytes_le(void);

  void finish_zfrom_bytes_le(void);

  bool zneq_anythingzIB5zK(uint64_t, uint64_t);

  bool zneq_anythingzIS64zK(sbits, sbits);

  bool zneq_anythingzIUMemoryAccessTypezIEmem_payloadz5zKzK(struct zMemoryAccessTypezIEmem_payloadz5zK, struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zneq_anythingzIEzzilx_modez5zK(enum zzzilx_mode, enum zzzilx_mode);

  bool zneq_anythingzIEpage_based_mem_typez5zK(enum zpage_based_mem_type, enum zpage_based_mem_type);

  bool zneq_anythingzIEloop_chain_statez5zK(enum zloop_chain_state, enum zloop_chain_state);

  bool zneq_anythingzIEamoopz5zK(enum zamoop, enum zamoop);

  bool zneq_anythingzIETrig_Matchz5zK(enum zTrig_Match, enum zTrig_Match);

  bool zneq_anythingzIETrig_Actionz5zK(enum zTrig_Action, enum zTrig_Action);

  bool zneq_anythingzIETranslationStagez5zK(enum zTranslationStage, enum zTranslationStage);

  bool zneq_anythingzIESATPModez5zK(enum zSATPMode, enum zSATPMode);

  bool zneq_anythingzIEReservabilityz5zK(enum zReservability, enum zReservability);

  bool zneq_anythingzIEPrivilegez5zK(enum zPrivilege, enum zPrivilege);

  bool zneq_anythingzIEMemoryRegionTypez5zK(enum zMemoryRegionType, enum zMemoryRegionType);

  bool zneq_anythingzIEHGATPModez5zK(enum zHGATPMode, enum zHGATPMode);

  bool zneq_anythingzIEExtContextPolicyz5zK(enum zExtContextPolicy, enum zExtContextPolicy);

  bool zneq_anythingzIECSRBitConfigz5zK(enum zCSRBitConfig, enum zCSRBitConfig);

  bool zneq_anythingzIECSRAccessTypez5zK(enum zCSRAccessType, enum zCSRAccessType);

  bool zneq_anythingzIEAtomicSupportz5zK(enum zAtomicSupport, enum zAtomicSupport);

  void zhex_bits_forwards(struct ztuple_z8z5izCz0z5stringz9 *rop, lbits);

  void zhex_bits_backwards(lbits *rop, struct ztuple_z8z5izCz0z5stringz9);

  bool zhex_bits_forwards_matches(lbits);

  bool zhex_bits_backwards_matches(struct ztuple_z8z5izCz0z5stringz9);

  void startup_zhex_bits_forwards(void);

  void finish_zhex_bits_forwards(void);

  void startup_zhex_bits_backwards(void);

  void finish_zhex_bits_backwards(void);

  void startup_zhex_bits_backwards_matches(void);

  void finish_zhex_bits_backwards_matches(void);

  void zhex_bits_2_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_2_forwards(void);

  void finish_zhex_bits_2_forwards(void);

  void zhex_bits_2_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_2_forwards_infallible(void);

  void finish_zhex_bits_2_forwards_infallible(void);

  void zhex_bits_4_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_4_forwards(void);

  void finish_zhex_bits_4_forwards(void);

  void zhex_bits_4_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_4_forwards_infallible(void);

  void finish_zhex_bits_4_forwards_infallible(void);

  void zhex_bits_5_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_5_forwards(void);

  void finish_zhex_bits_5_forwards(void);

  void zhex_bits_5_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_5_forwards_infallible(void);

  void finish_zhex_bits_5_forwards_infallible(void);

  void zhex_bits_6_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_6_forwards(void);

  void finish_zhex_bits_6_forwards(void);

  void zhex_bits_6_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_6_forwards_infallible(void);

  void finish_zhex_bits_6_forwards_infallible(void);

  void zhex_bits_7_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_7_forwards(void);

  void finish_zhex_bits_7_forwards(void);

  void zhex_bits_7_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_7_forwards_infallible(void);

  void finish_zhex_bits_7_forwards_infallible(void);

  void zhex_bits_8_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_8_forwards(void);

  void finish_zhex_bits_8_forwards(void);

  void zhex_bits_8_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_8_forwards_infallible(void);

  void finish_zhex_bits_8_forwards_infallible(void);

  void zhex_bits_9_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_9_forwards(void);

  void finish_zhex_bits_9_forwards(void);

  void zhex_bits_9_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_9_forwards_infallible(void);

  void finish_zhex_bits_9_forwards_infallible(void);

  void zhex_bits_10_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_10_forwards(void);

  void finish_zhex_bits_10_forwards(void);

  void zhex_bits_10_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_10_forwards_infallible(void);

  void finish_zhex_bits_10_forwards_infallible(void);

  void zhex_bits_11_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_11_forwards(void);

  void finish_zhex_bits_11_forwards(void);

  void zhex_bits_11_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_11_forwards_infallible(void);

  void finish_zhex_bits_11_forwards_infallible(void);

  void zhex_bits_12_forwards(sail_string *rop, uint64_t);

  uint64_t zhex_bits_12_backwards(const_sail_string);

  bool zhex_bits_12_backwards_matches(const_sail_string);

  void startup_zhex_bits_12_forwards(void);

  void finish_zhex_bits_12_forwards(void);

  void zhex_bits_12_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_12_forwards_infallible(void);

  void finish_zhex_bits_12_forwards_infallible(void);

  void startup_zhex_bits_12_backwards(void);

  void finish_zhex_bits_12_backwards(void);

  uint64_t zhex_bits_12_backwards_infallible(const_sail_string);

  void startup_zhex_bits_12_backwards_infallible(void);

  void finish_zhex_bits_12_backwards_infallible(void);

  void zhex_bits_16_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_16_forwards(void);

  void finish_zhex_bits_16_forwards(void);

  void zhex_bits_16_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_16_forwards_infallible(void);

  void finish_zhex_bits_16_forwards_infallible(void);

  void zhex_bits_20_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_20_forwards(void);

  void finish_zhex_bits_20_forwards(void);

  void zhex_bits_20_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_20_forwards_infallible(void);

  void finish_zhex_bits_20_forwards_infallible(void);

  void zhex_bits_32_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_32_forwards(void);

  void finish_zhex_bits_32_forwards(void);

  void zhex_bits_32_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_32_forwards_infallible(void);

  void finish_zhex_bits_32_forwards_infallible(void);

  void zhex_bits_signed_forwards(struct ztuple_z8z5izCz0z5stringz9 *rop, lbits);

  bool zhex_bits_signed_forwards_matches(lbits);

  void startup_zhex_bits_signed_forwards(void);

  void finish_zhex_bits_signed_forwards(void);

  void zhex_bits_signed_5_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_5_forwards(void);

  void finish_zhex_bits_signed_5_forwards(void);

  void zhex_bits_signed_5_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_5_forwards_infallible(void);

  void finish_zhex_bits_signed_5_forwards_infallible(void);

  void zhex_bits_signed_6_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_6_forwards(void);

  void finish_zhex_bits_signed_6_forwards(void);

  void zhex_bits_signed_6_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_6_forwards_infallible(void);

  void finish_zhex_bits_signed_6_forwards_infallible(void);

  void zhex_bits_signed_9_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_9_forwards(void);

  void finish_zhex_bits_signed_9_forwards(void);

  void zhex_bits_signed_9_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_9_forwards_infallible(void);

  void finish_zhex_bits_signed_9_forwards_infallible(void);

  void zhex_bits_signed_10_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_10_forwards(void);

  void finish_zhex_bits_signed_10_forwards(void);

  void zhex_bits_signed_10_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_10_forwards_infallible(void);

  void finish_zhex_bits_signed_10_forwards_infallible(void);

  void zhex_bits_signed_12_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_12_forwards(void);

  void finish_zhex_bits_signed_12_forwards(void);

  void zhex_bits_signed_12_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_12_forwards_infallible(void);

  void finish_zhex_bits_signed_12_forwards_infallible(void);

  void zhex_bits_signed_13_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_13_forwards(void);

  void finish_zhex_bits_signed_13_forwards(void);

  void zhex_bits_signed_13_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_13_forwards_infallible(void);

  void finish_zhex_bits_signed_13_forwards_infallible(void);

  void zhex_bits_signed_20_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_20_forwards(void);

  void finish_zhex_bits_signed_20_forwards(void);

  void zhex_bits_signed_20_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_20_forwards_infallible(void);

  void finish_zhex_bits_signed_20_forwards_infallible(void);

  void zhex_bits_signed_21_forwards(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_21_forwards(void);

  void finish_zhex_bits_signed_21_forwards(void);

  void zhex_bits_signed_21_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zhex_bits_signed_21_forwards_infallible(void);

  void finish_zhex_bits_signed_21_forwards_infallible(void);

  void zdec_bits_forwards(struct ztuple_z8z5izCz0z5stringz9 *rop, lbits);

  bool zdec_bits_forwards_matches(lbits);

  void startup_zdec_bits_forwards(void);

  void finish_zdec_bits_forwards(void);

  void zdec_bits_3_forwards(sail_string *rop, uint64_t);

  void startup_zdec_bits_3_forwards(void);

  void finish_zdec_bits_3_forwards(void);

  void zdec_bits_3_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zdec_bits_3_forwards_infallible(void);

  void finish_zdec_bits_3_forwards_infallible(void);

  void zdec_bits_4_forwards(sail_string *rop, uint64_t);

  void startup_zdec_bits_4_forwards(void);

  void finish_zdec_bits_4_forwards(void);

  void zdec_bits_4_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zdec_bits_4_forwards_infallible(void);

  void finish_zdec_bits_4_forwards_infallible(void);

  void zdec_bits_5_forwards(sail_string *rop, uint64_t);

  void startup_zdec_bits_5_forwards(void);

  void finish_zdec_bits_5_forwards(void);

  void zdec_bits_5_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zdec_bits_5_forwards_infallible(void);

  void finish_zdec_bits_5_forwards_infallible(void);

  void create_letbind_0(void);
  void kill_letbind_0(void);


  void create_letbind_1(void);
  void kill_letbind_1(void);


  void create_letbind_2(void);
  void kill_letbind_2(void);


  void create_letbind_3(void);
  void kill_letbind_3(void);


  void create_letbind_4(void);
  void kill_letbind_4(void);


  void create_letbind_5(void);
  void kill_letbind_5(void);


  void create_letbind_6(void);
  void kill_letbind_6(void);


  void create_letbind_7(void);
  void kill_letbind_7(void);


  void create_letbind_8(void);
  void kill_letbind_8(void);


  void create_letbind_9(void);
  void kill_letbind_9(void);


  void create_letbind_10(void);
  void kill_letbind_10(void);


  void create_letbind_11(void);
  void kill_letbind_11(void);


  void create_letbind_12(void);
  void kill_letbind_12(void);


  void zfloat_decompose(struct zfloat_bits *rop, lbits);

  void startup_zfloat_decompose(void);

  void finish_zfloat_decompose(void);

  bool zis_highest_one(lbits);

  void startup_zis_highest_one(void);

  void finish_zis_highest_one(void);

  bool zis_all_ones(lbits);

  void startup_zis_all_ones(void);

  void finish_zis_all_ones(void);

  bool zis_highest_zzero(lbits);

  void startup_zis_highest_zzero(void);

  void finish_zis_highest_zzero(void);

  bool zis_all_zzeros(lbits);

  void startup_zis_all_zzeros(void);

  void finish_zis_all_zzeros(void);

  bool zfloat_is_nan(lbits);

  void startup_zfloat_is_nan(void);

  void finish_zfloat_is_nan(void);

  bool zfloat_is_snan(lbits);

  void startup_zfloat_is_snan(void);

  void finish_zfloat_is_snan(void);

  bool zfloat_is_qnan(lbits);

  void startup_zfloat_is_qnan(void);

  void finish_zfloat_is_qnan(void);

  bool zfloat_is_inf(lbits);

  void startup_zfloat_is_inf(void);

  void finish_zfloat_is_inf(void);

  bool zfloat_is_positive(lbits);

  bool zfloat_is_zzero(lbits);

  void startup_zfloat_is_zzero(void);

  void finish_zfloat_is_zzero(void);

  bool zfloat_is_normal(lbits);

  void startup_zfloat_is_normal(void);

  void finish_zfloat_is_normal(void);

  bool zfloat_is_subnormal(lbits);

  void startup_zfloat_is_subnormal(void);

  void finish_zfloat_is_subnormal(void);

  enum zfloat_class zfloat_classify(lbits);

  uint64_t znot_bit(uint64_t);

  bool znot(bool);

  void zsign_extend(lbits *rop, sail_int, lbits);

  void zzzero_extend(lbits *rop, sail_int, lbits);

  void zzzeros(lbits *rop, sail_int);

  void zones(lbits *rop, sail_int);

  void ztrunc(lbits *rop, sail_int, lbits);

  uint64_t zbool_bit_forwards(bool);

  bool zbool_bit_backwards(uint64_t);

  bool zbool_bit_backwards_matches(uint64_t);

  uint64_t zbool_bit_forwards_infallible(bool);

  bool zbool_bit_backwards_infallible(uint64_t);

  uint64_t zbool_to_bit(bool);

  bool zbit_to_bool(uint64_t);

  void zto_bits(lbits *rop, sail_int, sail_int);

  void startup_zto_bits(void);

  void finish_zto_bits(void);

  void zto_bits_checked(lbits *rop, sail_int, sail_int);

  void startup_zto_bits_checked(void);

  void finish_zto_bits_checked(void);

  void zto_bits_truncate(lbits *rop, sail_int, sail_int);

  void startup_zto_bits_truncate(void);

  void finish_zto_bits_truncate(void);

  void zto_bits_unsafe(lbits *rop, sail_int, sail_int);

  void startup_zto_bits_unsafe(void);

  void finish_zto_bits_unsafe(void);

  bool zz8operatorz0zI_sz9(lbits, lbits);

  bool zz8operatorz0zK_sz9(lbits, lbits);

  bool zz8operatorz0zKzJ_sz9(lbits, lbits);

  bool zz8operatorz0zI_uz9(lbits, lbits);

  bool zz8operatorz0zK_uz9(lbits, lbits);

  bool zz8operatorz0zIzJ_uz9(lbits, lbits);

  bool zz8operatorz0zKzJ_uz9(lbits, lbits);

  void startup_zz8operatorz0zI_sz9(void);

  void finish_zz8operatorz0zI_sz9(void);

  void startup_zz8operatorz0zK_sz9(void);

  void finish_zz8operatorz0zK_sz9(void);

  void startup_zz8operatorz0zKzJ_sz9(void);

  void finish_zz8operatorz0zKzJ_sz9(void);

  void startup_zz8operatorz0zI_uz9(void);

  void finish_zz8operatorz0zI_uz9(void);

  void startup_zz8operatorz0zK_uz9(void);

  void finish_zz8operatorz0zK_uz9(void);

  void startup_zz8operatorz0zIzJ_uz9(void);

  void finish_zz8operatorz0zIzJ_uz9(void);

  void startup_zz8operatorz0zKzJ_uz9(void);

  void finish_zz8operatorz0zKzJ_uz9(void);

  bool zz8operatorz0zJzJzKz9(bool, bool);

  void zshift_bits_right_arith(lbits *rop, lbits, lbits);

  void startup_zshift_bits_right_arith(void);

  void finish_zshift_bits_right_arith(void);

  void zrotater(lbits *rop, lbits, sail_int);

  void startup_zrotater(void);

  void finish_zrotater(void);

  void zrotatel(lbits *rop, lbits, sail_int);

  void startup_zrotatel(void);

  void finish_zrotatel(void);

  void zrotate_bits_right(lbits *rop, lbits, lbits);

  void startup_zrotate_bits_right(void);

  void finish_zrotate_bits_right(void);

  void zrotate_bits_left(lbits *rop, lbits, lbits);

  void startup_zrotate_bits_left(void);

  void finish_zrotate_bits_left(void);

  void zreverse_bits(lbits *rop, lbits);

  void startup_zreverse_bits(void);

  void finish_zreverse_bits(void);

  void zhex_bits_str(sail_string *rop, lbits);

  void startup_zhex_bits_str(void);

  void finish_zhex_bits_str(void);

  unit zstatic_assert(bool);

  int64_t zinternal_errorzII64zK(const_sail_string, sail_int, const_sail_string);

  uint64_t zinternal_errorzIB64zK(const_sail_string, sail_int, const_sail_string);

  uint64_t zinternal_errorzIB32zK(const_sail_string, sail_int, const_sail_string);

  uint64_t zinternal_errorzIB4zK(const_sail_string, sail_int, const_sail_string);

  uint64_t zinternal_errorzIB2zK(const_sail_string, sail_int, const_sail_string);

  uint64_t zinternal_errorzIB1zK(const_sail_string, sail_int, const_sail_string);

  sbits zinternal_errorzIS64zK(const_sail_string, sail_int, const_sail_string);

  unit zinternal_errorzIuzK(const_sail_string, sail_int, const_sail_string);

  bool zinternal_errorzIozK(const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIz8UTriggerzCETrig_Actionz5zCoz9zK(struct ztuple_z8z5unionz0zzTriggerzCz0z5enumz0zzTrig_ActionzCz0z5boolz9 *rop, const_sail_string, sail_int, const_sail_string);

  struct zMtvec zinternal_errorzIRMtveczK(const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIUresultzIbzCuzKzK(struct zresultzIbzCuzK *rop, const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIOzIEmisaligned_exceptionz5zKzK(struct zoptionzIEmisaligned_exceptionz5zK *rop, const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIUaccess_kindzK(struct zaccess_kind *rop, const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIUExecutionResultzK(struct zExecutionResult *rop, const_sail_string, sail_int, const_sail_string);

  void zinternal_errorzIUExceptionTypezK(struct zExceptionType *rop, const_sail_string, sail_int, const_sail_string);

  enum zwrite_kind zinternal_errorzIEwrite_kindz5zK(const_sail_string, sail_int, const_sail_string);

  enum zread_kind zinternal_errorzIEread_kindz5zK(const_sail_string, sail_int, const_sail_string);

  enum zcbie zinternal_errorzIEcbiez5zK(const_sail_string, sail_int, const_sail_string);

  enum zSATPMode zinternal_errorzIESATPModez5zK(const_sail_string, sail_int, const_sail_string);

  enum zPrivilege zinternal_errorzIEPrivilegez5zK(const_sail_string, sail_int, const_sail_string);

  enum zHGATPMode zinternal_errorzIEHGATPModez5zK(const_sail_string, sail_int, const_sail_string);

  enum zArchitecture zinternal_errorzIEArchitecturez5zK(const_sail_string, sail_int, const_sail_string);

  void startup_zinternal_errorzIRMtveczK(void);

  void finish_zinternal_errorzIRMtveczK(void);

  uint64_t zreserved_behaviorzIB2zK(const_sail_string);

  unit zreserved_behaviorzIuzK(const_sail_string);

  bool zreserved_behaviorzIozK(const_sail_string);

  struct zPmpcfg_ent zreserved_behaviorzIRPmpcfg_entzK(const_sail_string);

  struct zMtvec zreserved_behaviorzIRMtveczK(const_sail_string);

  void zreserved_behaviorzIOzIErounding_modez5zKzK(struct zoptionzIErounding_modez5zK *rop, const_sail_string);

  void startup_zreserved_behaviorzIRPmpcfg_entzK(void);

  void finish_zreserved_behaviorzIRPmpcfg_entzK(void);

  void startup_zreserved_behaviorzIRMtveczK(void);

  void finish_zreserved_behaviorzIRMtveczK(void);

  void zamo_mnemonic_forwards(sail_string *rop, enum zamoop);

  void zamo_mnemonic_forwards_infallible(sail_string *rop, enum zamoop);

  void zmaybe_aqrl_forwards(sail_string *rop, struct ztuple_z8z5boolzCz0z5boolz9);

  void zmaybe_aqrl_forwards_infallible(sail_string *rop, struct ztuple_z8z5boolzCz0z5boolz9);

  enum zPointerMaskingMode zpmm_mode_backwards(uint64_t);

  enum zPointerMaskingMode zpmm_mode_backwards_infallible(uint64_t);

  bool zis_supported_pmm(enum zPM_Ext, enum zPointerMaskingMode);

  int64_t znum_of_Privileged_ISA_Version(enum zPrivileged_ISA_Version);

  void zprivileged_isa_version_name_forwards(sail_string *rop, enum zPrivileged_ISA_Version);

  void zprivileged_isa_version_name_forwards_infallible(sail_string *rop, enum zPrivileged_ISA_Version);

  bool zprivileged_isa_version_lt(enum zPrivileged_ISA_Version, enum zPrivileged_ISA_Version);

  bool zprivileged_isa_version_ge(enum zPrivileged_ISA_Version, enum zPrivileged_ISA_Version);

  void create_letbind_13(void);
  void kill_letbind_13(void);


  void create_letbind_14(void);
  void kill_letbind_14(void);


  void create_letbind_15(void);
  void kill_letbind_15(void);


  void create_letbind_16(void);
  void kill_letbind_16(void);


  void create_letbind_17(void);
  void kill_letbind_17(void);


  void create_letbind_18(void);
  void kill_letbind_18(void);


  void create_letbind_19(void);
  void kill_letbind_19(void);


  void create_letbind_20(void);
  void kill_letbind_20(void);


  void create_letbind_21(void);
  void kill_letbind_21(void);


  void create_letbind_22(void);
  void kill_letbind_22(void);


  void create_letbind_23(void);
  void kill_letbind_23(void);


  void create_letbind_24(void);
  void kill_letbind_24(void);


  void create_letbind_25(void);
  void kill_letbind_25(void);


  void create_letbind_26(void);
  void kill_letbind_26(void);


  void create_letbind_27(void);
  void kill_letbind_27(void);


  void create_letbind_28(void);
  void kill_letbind_28(void);


  void create_letbind_29(void);
  void kill_letbind_29(void);


  void create_letbind_30(void);
  void kill_letbind_30(void);


  int64_t znum_of_vector_support(enum zvector_support);

  void create_letbind_31(void);
  void kill_letbind_31(void);


  bool zvector_support_ge(enum zvector_support, enum zvector_support);

  void create_letbind_32(void);
  void kill_letbind_32(void);


  void create_letbind_33(void);
  void kill_letbind_33(void);


  void create_letbind_34(void);
  void kill_letbind_34(void);


  void create_letbind_35(void);
  void kill_letbind_35(void);


  void create_letbind_36(void);
  void kill_letbind_36(void);


  sbits zbits_of_physaddr(sbits);

  sbits zbits_of_virtaddr(sbits);

  sbits zsub_virtaddr_xlenbits(sbits, sbits);

  sbits zsub_physaddr_xlenbits(sbits, sbits);

  void startup_zsub_physaddr_xlenbits(void);

  void finish_zsub_physaddr_xlenbits(void);

  void create_letbind_37(void);
  void kill_letbind_37(void);


  void create_letbind_38(void);
  void kill_letbind_38(void);


  unit z__WriteRAM_Meta(sbits, int64_t, unit);

  unit z__ReadRAM_Meta(sbits, int64_t);

  void zbrev8(lbits *rop, lbits);

  void startup_zbrev8(void);

  void finish_zbrev8(void);

  void zcarryless_mul(lbits *rop, lbits, lbits);

  void startup_zcarryless_mul(void);

  void finish_zcarryless_mul(void);

  void zcarryless_mulr(lbits *rop, lbits, lbits);

  void startup_zcarryless_mulr(void);

  void finish_zcarryless_mulr(void);

  void zmult_to_bits_half(lbits *rop, sail_int, enum zSignedness, enum zSignedness, lbits, lbits, enum zVectorHalf);

  void startup_zmult_to_bits_half(void);

  void finish_zmult_to_bits_half(void);

  void zrev8(lbits *rop, lbits);

  void startup_zrev8(void);

  void finish_zrev8(void);

  void zcount_ones(sail_int *rop, lbits);

  void startup_zcount_ones(void);

  void finish_zcount_ones(void);

  void zlowest_index_of(struct zoptionzIizK *rop, lbits, uint64_t);

  void startup_zlowest_index_of(void);

  void finish_zlowest_index_of(void);

  unit ztest_lowest_index_of(unit);

  void startup_ztest_lowest_index_of(void);

  void finish_ztest_lowest_index_of(void);

  void zhighest_index_of(struct zoptionzIizK *rop, lbits, uint64_t);

  void startup_zhighest_index_of(void);

  void finish_zhighest_index_of(void);

  unit ztest_highest_index_of(unit);

  void startup_ztest_highest_index_of(void);

  void finish_ztest_highest_index_of(void);

  void zleast_significant_zzero(struct zoptionzIizK *rop, lbits);

  bool zrange_subset(sbits, sbits, sbits, sbits);

  void startup_zrange_subset(void);

  void finish_zrange_subset(void);

  unit ztest_range_subset(unit);

  uint64_t zfloat_class_onehot_bits_forwards(enum zfloat_class);

  uint64_t zfloat_class_onehot_bits_forwards_infallible(enum zfloat_class);

  struct zRVFI_DII_Instruction_Packet zundefined_RVFI_DII_Instruction_Packet(unit);

  void startup_zundefined_RVFI_DII_Instruction_Packet(void);

  void finish_zundefined_RVFI_DII_Instruction_Packet(void);

  struct zRVFI_DII_Instruction_Packet zMk_RVFI_DII_Instruction_Packet(uint64_t);

  void startup_zMk_RVFI_DII_Instruction_Packet(void);

  void finish_zMk_RVFI_DII_Instruction_Packet(void);

  uint64_t z_get_RVFI_DII_Instruction_Packet_rvfi_insn(struct zRVFI_DII_Instruction_Packet);

  unit zrvfi_set_instr_packet(uint64_t);

  void zundefined_RVFI_DII_Execution_Packet_InstMetaData(struct zRVFI_DII_Execution_Packet_InstMetaData *rop, unit);

  void startup_zundefined_RVFI_DII_Execution_Packet_InstMetaData(void);

  void finish_zundefined_RVFI_DII_Execution_Packet_InstMetaData(void);

  void zundefined_RVFI_DII_Execution_Packet_PC(struct zRVFI_DII_Execution_Packet_PC *rop, unit);

  void startup_zundefined_RVFI_DII_Execution_Packet_PC(void);

  void finish_zundefined_RVFI_DII_Execution_Packet_PC(void);

  void zundefined_RVFI_DII_Execution_Packet_Ext_Integer(struct zRVFI_DII_Execution_Packet_Ext_Integer *rop, unit);

  void startup_zundefined_RVFI_DII_Execution_Packet_Ext_Integer(void);

  void finish_zundefined_RVFI_DII_Execution_Packet_Ext_Integer(void);

  void zundefined_RVFI_DII_Execution_Packet_Ext_MemAccess(struct zRVFI_DII_Execution_Packet_Ext_MemAccess *rop, unit);

  void startup_zundefined_RVFI_DII_Execution_Packet_Ext_MemAccess(void);

  void finish_zundefined_RVFI_DII_Execution_Packet_Ext_MemAccess(void);

  void create_letbind_39(void);
  void kill_letbind_39(void);


  void create_letbind_40(void);
  void kill_letbind_40(void);


  void create_letbind_41(void);
  void kill_letbind_41(void);


  void create_letbind_42(void);
  void kill_letbind_42(void);


  void create_letbind_43(void);
  void kill_letbind_43(void);


  void create_letbind_44(void);
  void kill_letbind_44(void);


  void create_letbind_45(void);
  void kill_letbind_45(void);


  void create_letbind_46(void);
  void kill_letbind_46(void);


  void create_letbind_47(void);
  void kill_letbind_47(void);


  void create_letbind_48(void);
  void kill_letbind_48(void);


  void create_letbind_49(void);
  void kill_letbind_49(void);


  void create_letbind_50(void);
  void kill_letbind_50(void);


  void create_letbind_51(void);
  void kill_letbind_51(void);


  void create_letbind_52(void);
  void kill_letbind_52(void);


  void create_letbind_53(void);
  void kill_letbind_53(void);


  void create_letbind_54(void);
  void kill_letbind_54(void);


  void create_letbind_55(void);
  void kill_letbind_55(void);


  void create_letbind_56(void);
  void kill_letbind_56(void);


  void create_letbind_57(void);
  void kill_letbind_57(void);


  void zmisaligned_exception_str_forwards(sail_string *rop, enum zmisaligned_exception);

  void zmisaligned_exception_str_forwards_infallible(sail_string *rop, enum zmisaligned_exception);

  void zoptional_misaligned_exception_str(sail_string *rop, struct zoptionzIEmisaligned_exceptionz5zK);

  bool zmisaligned_exception_is_access_fault(struct zoptionzIEmisaligned_exceptionz5zK);

  void create_letbind_58(void);
  void kill_letbind_58(void);


  uint64_t zlegalizze_csr_bit(enum zCSRBitConfig, bool, uint64_t);

  void create_letbind_59(void);
  void kill_letbind_59(void);


  void create_letbind_60(void);
  void kill_letbind_60(void);


  void create_letbind_61(void);
  void kill_letbind_61(void);


  void create_letbind_62(void);
  void kill_letbind_62(void);


  void create_letbind_63(void);
  void kill_letbind_63(void);


  void create_letbind_64(void);
  void kill_letbind_64(void);


  void create_letbind_65(void);
  void kill_letbind_65(void);


  void create_letbind_66(void);
  void kill_letbind_66(void);


  void create_letbind_67(void);
  void kill_letbind_67(void);


  void create_letbind_68(void);
  void kill_letbind_68(void);


  void create_letbind_69(void);
  void kill_letbind_69(void);


  void create_letbind_70(void);
  void kill_letbind_70(void);


  void create_letbind_71(void);
  void kill_letbind_71(void);


  void create_letbind_72(void);
  void kill_letbind_72(void);


  void create_letbind_73(void);
  void kill_letbind_73(void);


  void create_letbind_74(void);
  void kill_letbind_74(void);


  void create_letbind_75(void);
  void kill_letbind_75(void);


  void create_letbind_76(void);
  void kill_letbind_76(void);


  void create_letbind_77(void);
  void kill_letbind_77(void);


  void create_letbind_78(void);
  void kill_letbind_78(void);


  void create_letbind_79(void);
  void kill_letbind_79(void);


  void create_letbind_80(void);
  void kill_letbind_80(void);


  void create_letbind_81(void);
  void kill_letbind_81(void);


  void create_letbind_82(void);
  void kill_letbind_82(void);


  void create_letbind_83(void);
  void kill_letbind_83(void);


  void create_letbind_84(void);
  void kill_letbind_84(void);


  void create_letbind_85(void);
  void kill_letbind_85(void);


  void create_letbind_86(void);
  void kill_letbind_86(void);


  void create_letbind_87(void);
  void kill_letbind_87(void);


  void create_letbind_88(void);
  void kill_letbind_88(void);


  void create_letbind_89(void);
  void kill_letbind_89(void);


  void create_letbind_90(void);
  void kill_letbind_90(void);


  void create_letbind_91(void);
  void kill_letbind_91(void);


  void create_letbind_92(void);
  void kill_letbind_92(void);


  void create_letbind_93(void);
  void kill_letbind_93(void);


  void create_letbind_94(void);
  void kill_letbind_94(void);


  void create_letbind_95(void);
  void kill_letbind_95(void);


  void create_letbind_96(void);
  void kill_letbind_96(void);


  void create_letbind_97(void);
  void kill_letbind_97(void);


  void create_letbind_98(void);
  void kill_letbind_98(void);


  void create_letbind_99(void);
  void kill_letbind_99(void);


  void create_letbind_100(void);
  void kill_letbind_100(void);


  void create_letbind_101(void);
  void kill_letbind_101(void);


  void create_letbind_102(void);
  void kill_letbind_102(void);


  void create_letbind_103(void);
  void kill_letbind_103(void);


  void create_letbind_104(void);
  void kill_letbind_104(void);


  void create_letbind_105(void);
  void kill_letbind_105(void);


  void create_letbind_106(void);
  void kill_letbind_106(void);


  void create_letbind_107(void);
  void kill_letbind_107(void);


  void create_letbind_108(void);
  void kill_letbind_108(void);


  void create_letbind_109(void);
  void kill_letbind_109(void);


  void create_letbind_110(void);
  void kill_letbind_110(void);


  void create_letbind_111(void);
  void kill_letbind_111(void);


  void create_letbind_112(void);
  void kill_letbind_112(void);


  void create_letbind_113(void);
  void kill_letbind_113(void);


  void create_letbind_114(void);
  void kill_letbind_114(void);


  bool zmtval_is_readonly_zzero(unit);

  void create_letbind_115(void);
  void kill_letbind_115(void);


  void create_letbind_116(void);
  void kill_letbind_116(void);


  void create_letbind_117(void);
  void kill_letbind_117(void);


  void create_letbind_118(void);
  void kill_letbind_118(void);


  void create_letbind_119(void);
  void kill_letbind_119(void);


  void create_letbind_120(void);
  void kill_letbind_120(void);


  void create_letbind_121(void);
  void kill_letbind_121(void);


  void create_letbind_122(void);
  void kill_letbind_122(void);


  void create_letbind_123(void);
  void kill_letbind_123(void);


  void create_letbind_124(void);
  void kill_letbind_124(void);


  void create_letbind_125(void);
  void kill_letbind_125(void);


  void create_letbind_126(void);
  void kill_letbind_126(void);


  void create_letbind_127(void);
  void kill_letbind_127(void);


  void create_letbind_128(void);
  void kill_letbind_128(void);


  void create_letbind_129(void);
  void kill_letbind_129(void);


  void create_letbind_130(void);
  void kill_letbind_130(void);


  void create_letbind_131(void);
  void kill_letbind_131(void);


  void create_letbind_132(void);
  void kill_letbind_132(void);


  void create_letbind_133(void);
  void kill_letbind_133(void);


  void create_letbind_134(void);
  void kill_letbind_134(void);


  void create_letbind_135(void);
  void kill_letbind_135(void);


  void zextensionName_forwards(sail_string *rop, enum zextension);

  bool zhartSupports(enum zextension);

  bool zcurrentlyEnabled(enum zextension);

  void zextensionName_forwards_infallible(sail_string *rop, enum zextension);

  void create_letbind_136(void);
  void kill_letbind_136(void);


  void create_letbind_137(void);
  void kill_letbind_137(void);


  unit zext_translate_exception(unit);

  uint64_t zext_exc_type_bits_forwards(unit);

  unit zext_exc_type_bits_backwards(uint64_t);

  bool zext_exc_type_bits_backwards_matches(uint64_t);

  uint64_t zext_exc_type_bits_forwards_infallible(unit);

  unit zext_exc_type_bits_backwards_infallible(uint64_t);

  void zext_exc_type_to_str(sail_string *rop, unit);

  void create_letbind_138(void);
  void kill_letbind_138(void);


  void create_letbind_139(void);
  void kill_letbind_139(void);


  void create_letbind_140(void);
  void kill_letbind_140(void);


  sbits zregidx_offset_range(sbits, int64_t);

  void startup_zregidx_offset_range(void);

  void finish_zregidx_offset_range(void);

  sbits zregidx_bits(sbits);

  sbits zcreg2reg_idx(uint64_t);

  void startup_zcreg2reg_idx(void);

  void finish_zcreg2reg_idx(void);

  void create_letbind_141(void);
  void kill_letbind_141(void);


  void create_letbind_142(void);
  void kill_letbind_142(void);


  void create_letbind_143(void);
  void kill_letbind_143(void);


  void create_letbind_144(void);
  void kill_letbind_144(void);


  uint64_t zarchitecture_bits_forwards(enum zArchitecture);

  enum zArchitecture zarchitecture_bits_backwards(uint64_t);

  uint64_t zarchitecture_bits_forwards_infallible(enum zArchitecture);

  void startup_zarchitecture_bits_backwards(void);

  void finish_zarchitecture_bits_backwards(void);

  enum zArchitecture zarchitecture_bits_backwards_infallible(uint64_t);

  void startup_zarchitecture_bits_backwards_infallible(void);

  void finish_zarchitecture_bits_backwards_infallible(void);

  enum zPrivilege zundefined_Privilege(unit);

  enum zPrivilege zprivLevel_bits_forwards(struct ztuple_z8z5bv2zCz0z5bv1z9);

  struct ztuple_z8z5bv2zCz0z5bv1z9 zprivLevel_bits_backwards(enum zPrivilege);

  void startup_zprivLevel_bits_forwards(void);

  void finish_zprivLevel_bits_forwards(void);

  enum zPrivilege zprivLevel_bits_forwards_infallible(struct ztuple_z8z5bv2zCz0z5bv1z9);

  void startup_zprivLevel_bits_forwards_infallible(void);

  void finish_zprivLevel_bits_forwards_infallible(void);

  struct ztuple_z8z5bv2zCz0z5bv1z9 zprivLevel_bits_backwards_infallible(enum zPrivilege);

  uint64_t zprivLevel_to_bits(enum zPrivilege);

  uint64_t zprivLevel_to_virt_bit(enum zPrivilege);

  bool zprivLevel_is_virtual(enum zPrivilege);

  void zprivLevel_to_str(sail_string *rop, enum zPrivilege);

  bool zis_load_storezIEmem_payloadz5zK(struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_prefetch_accesszIEmem_payloadz5zK(struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_load_reservedzIEmem_payloadz5zK(struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_store_conditionalzIEmem_payloadz5zK(struct zMemoryAccessTypezIEmem_payloadz5zK);

  uint64_t zinterruptType_bits_forwards(enum zInterruptType);

  enum zInterruptType zinterruptType_bits_backwards(uint64_t);

  uint64_t zinterruptType_bits_forwards_infallible(enum zInterruptType);

  enum zInterruptType zinterruptType_bits_backwards_infallible(uint64_t);

  void zinterruptType_to_str(sail_string *rop, enum zInterruptType);

  bool zis_reserved_interrupt(enum zInterruptType);

  bool zis_hypervisor_interrupt(enum zInterruptType);

  uint64_t zexceptionType_bits_forwards(struct zExceptionType);

  void zexceptionType_bits_backwards(struct zExceptionType *rop, uint64_t);

  bool zexceptionType_bits_backwards_matches(uint64_t);

  uint64_t zexceptionType_bits_forwards_infallible(struct zExceptionType);

  void zexceptionType_bits_backwards_infallible(struct zExceptionType *rop, uint64_t);

  void zexceptionType_to_str(sail_string *rop, struct zExceptionType);

  bool zis_reserved_or_custom_exception(struct zExceptionType);

  bool zis_hypervisor_exception(struct zExceptionType);

  bool zis_guest_page_fault(struct zExceptionType);

  uint64_t ztrapCause_bits(struct zTrapCause);

  void startup_ztrapCause_bits(void);

  void finish_ztrapCause_bits(void);

  bool ztrapCause_is_interrupt(struct zTrapCause);

  void ztrapCause_to_str(sail_string *rop, struct zTrapCause);

  void startup_ztrapCause_to_str(void);

  void finish_ztrapCause_to_str(void);

  enum zTrapVectorMode ztrapVectorMode_forwards(uint64_t);

  enum zTrapVectorMode ztrapVectorMode_forwards_infallible(uint64_t);

  enum zExtStatus zextStatus_map_backwards(uint64_t);

  enum zExtStatus zextStatus_map_backwards_infallible(uint64_t);

  uint64_t zlegalizze_extStatus(enum zExtContextPolicy, uint64_t);

  void zhgatpMode_of_bits(struct zoptionzIEHGATPModez5zK *rop, enum zArchitecture, uint64_t);

  void zsatpMode_of_bits(struct zoptionzIESATPModez5zK *rop, enum zArchitecture, uint64_t);

  void zwait_name_forwards(sail_string *rop, enum zWaitReason);

  void zwait_name_forwards_infallible(sail_string *rop, enum zWaitReason);

  uint64_t zwidth_enc_forwards(int64_t);

  int64_t zwidth_enc_backwards(uint64_t);

  bool zwidth_enc_backwards_matches(uint64_t);

  uint64_t zwidth_enc_forwards_infallible(int64_t);

  int64_t zwidth_enc_backwards_infallible(uint64_t);

  void zwidth_mnemonic_forwards(sail_string *rop, int64_t);

  void zwidth_mnemonic_forwards_infallible(sail_string *rop, int64_t);

  uint64_t zwidth_enc_wide_forwards(int64_t);

  int64_t zwidth_enc_wide_backwards(uint64_t);

  bool zwidth_enc_wide_backwards_matches(uint64_t);

  uint64_t zwidth_enc_wide_forwards_infallible(int64_t);

  int64_t zwidth_enc_wide_backwards_infallible(uint64_t);

  void zwidth_mnemonic_wide_forwards(sail_string *rop, int64_t);

  void zwidth_mnemonic_wide_forwards_infallible(sail_string *rop, int64_t);

  int64_t zget_root_level(int64_t);

  void startup_zget_root_level(void);

  void finish_zget_root_level(void);

  int64_t zget_vpn_level_sizze(int64_t);

  void startup_zget_vpn_level_sizze(void);

  void finish_zget_vpn_level_sizze(void);

  void zmem_payload_name_forwards(sail_string *rop, enum zmem_payload);

  void zmem_payload_name_forwards_infallible(sail_string *rop, enum zmem_payload);

  void zmem_payload_str_forwards(sail_string *rop, enum zmem_payload);

  void zmem_payload_str_forwards_infallible(sail_string *rop, enum zmem_payload);

  void zaccessType_to_str(sail_string *rop, struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_shadow_stack_access(struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zis_shadow_stack_access(void);

  void finish_zis_shadow_stack_access(void);

  bool zis_amo_access(struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_vector_access(struct zMemoryAccessTypezIEmem_payloadz5zK);

  bool zis_implicit_access(struct zMemoryAccessTypezIEmem_payloadz5zK);

  enum zpage_based_mem_type zpage_based_mem_type_forwards(uint64_t);

  bool zpage_based_mem_type_forwards_matches(uint64_t);

  enum zpage_based_mem_type zpage_based_mem_type_forwards_infallible(uint64_t);

  void zread_memz3zIRMem_requestzIuzCUaccess_kindzKzK(lbits *rop, struct zMem_requestzIuzCUaccess_kindzK, int64_t, sbits, sail_int);

  void zread_mem_ifetchz3zIRMem_requestzIuzCUaccess_kindzKzK(lbits *rop, struct zMem_requestzIuzCUaccess_kindzK, int64_t, sbits, sail_int);

  void zread_mem_exclusivez3zIRMem_requestzIuzCUaccess_kindzKzK(lbits *rop, struct zMem_requestzIuzCUaccess_kindzK, int64_t, sbits, sail_int);

  bool zwrite_memz3zIRMem_requestzIuzCUaccess_kindzKzK(struct zMem_requestzIuzCUaccess_kindzK, int64_t, sbits, sail_int, lbits);

  bool zwrite_mem_exclusivez3zIRMem_requestzIuzCUaccess_kindzKzK(struct zMem_requestzIuzCUaccess_kindzK, int64_t, sbits, sail_int, lbits);

  unit zsail_instr_announce(lbits);

  unit zsail_branch_announce(int64_t, sbits);

  void z__monomorphizze(lbits *rop, lbits);

  void create_letbind_145(void);
  void kill_letbind_145(void);


  void create_letbind_146(void);
  void kill_letbind_146(void);


  void zak_memory_access(struct zMemoryAccessTypezIEmem_payloadz5zK *rop, struct zaccess_kind);

  bool zak_is_ifetch(struct zaccess_kind);

  bool zak_is_exclusive(struct zaccess_kind);

  void zsail_mem_write(struct zresultzIuzCuzK *rop, struct zMem_requestzIuzCUaccess_kindzK, zz5vecz8z5bv8z9, zz5vecz8z5boolz9);

  void startup_zsail_mem_write(void);

  void finish_zsail_mem_write(void);

  bool zwrite_ram(enum zwrite_kind, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t, lbits, unit);

  void startup_zwrite_ram(void);

  void finish_zwrite_ram(void);

  unit zsail_mem_address_announce(struct zMem_requestzIuzCUaccess_kindzK);

  unit zwrite_ram_ea(enum zwrite_kind, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t);

  void startup_zwrite_ram_ea(void);

  void finish_zwrite_ram_ea(void);

  void zsail_mem_read(struct zresultzIz8VbzCVoz9zCuzK *rop, struct zMem_requestzIuzCUaccess_kindzK);

  void startup_zsail_mem_read(void);

  void finish_zsail_mem_read(void);

  void zread_ram(struct ztuple_z8z5bvzCz0z5unitz9 *rop, enum zread_kind, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t, bool);

  void startup_zread_ram(void);

  void finish_zread_ram(void);

  void zaccessFaultFromAccessType(struct zExceptionType *rop, struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zaccessFaultFromAccessType(void);

  void finish_zaccessFaultFromAccessType(void);

  void zalignmentFaultFromAccessType(struct zExceptionType *rop, struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zalignmentFaultFromAccessType(void);

  void finish_zalignmentFaultFromAccessType(void);

  void zcsr_name_map_forwards(sail_string *rop, uint64_t);

  uint64_t zcsr_name_map_backwards(const_sail_string);

  bool zis_CSR_accessible(uint64_t, enum zPrivilege, enum zCSRAccessType);

  sbits zread_CSR(uint64_t);

  void zwrite_CSR(struct zresultzIbzCuzK *rop, uint64_t, sbits);

  bool zis_CSR_exception_virtual(uint64_t, enum zPrivilege, enum zCSRAccessType);

  unit zcsr_name_write_callback(const_sail_string, sbits);

  unit zcsr_id_write_callback(uint64_t, sbits);

  unit zcsr_id_read_callback(uint64_t, sbits);

  unit zlong_csr_write_callback(const_sail_string, const_sail_string, uint64_t);

  void startup_zlong_csr_write_callback(void);

  void finish_zlong_csr_write_callback(void);

  void create_letbind_147(void);
  void kill_letbind_147(void);


  sbits zregval_from_reg(sbits);

  sbits zregval_into_reg(sbits);

  uint64_t zencdec_reg_forwards(sbits);

  sbits zencdec_reg_backwards(uint64_t);

  bool zencdec_reg_forwards_matches(sbits);

  bool zencdec_reg_backwards_matches(uint64_t);

  void startup_zencdec_reg_forwards(void);

  void finish_zencdec_reg_forwards(void);

  uint64_t zencdec_reg_forwards_infallible(sbits);

  void startup_zencdec_reg_forwards_infallible(void);

  void finish_zencdec_reg_forwards_infallible(void);

  void startup_zencdec_reg_backwards(void);

  void finish_zencdec_reg_backwards(void);

  sbits zencdec_reg_backwards_infallible(uint64_t);

  void startup_zencdec_reg_backwards_infallible(void);

  void finish_zencdec_reg_backwards_infallible(void);

  uint64_t zencdec_creg_backwards(uint64_t);

  bool zencdec_creg_backwards_matches(uint64_t);

  uint64_t zencdec_creg_backwards_infallible(uint64_t);

  void zreg_abi_name_raw_forwards(sail_string *rop, uint64_t);

  void zreg_abi_name_raw_forwards_infallible(sail_string *rop, uint64_t);

  void zreg_arch_name_raw_forwards(sail_string *rop, uint64_t);

  void zreg_arch_name_raw_forwards_infallible(sail_string *rop, uint64_t);

  void zreg_name_forwards(sail_string *rop, sbits);

  void zreg_name_forwards_infallible(sail_string *rop, sbits);

  void zsp_reg_name_forwards(sail_string *rop, unit);

  void zsp_reg_name_forwards_infallible(sail_string *rop, unit);

  void zcreg_name_forwards(sail_string *rop, uint64_t);

  void zcreg_name_forwards_infallible(sail_string *rop, uint64_t);

  unit zxreg_write_callback(sbits, sbits);

  sbits zrX(int64_t);

  unit zwX(int64_t, sbits);

  void startup_zwX(void);

  void finish_zwX(void);

  sbits zrX_bits(sbits);

  void startup_zrX_bits(void);

  void finish_zrX_bits(void);

  unit zwX_bits(sbits, sbits);

  void startup_zwX_bits(void);

  void finish_zwX_bits(void);

  void zrX_pair_bits(lbits *rop, sbits);

  void startup_zrX_pair_bits(void);

  void finish_zrX_pair_bits(void);

  unit zwX_pair_bits(sbits, lbits);

  void startup_zwX_pair_bits(void);

  void finish_zwX_pair_bits(void);

  sbits zget_arch_pc(unit);

  sbits zget_next_pc(unit);

  unit zset_next_pc(sbits);

  unit ztick_pc(unit);

  struct zMisa zMk_Misa(sbits);

  void startup_zMk_Misa(void);

  void finish_zMk_Misa(void);

  uint64_t z_get_Misa_A(struct zMisa);

  struct zMisa z_update_Misa_A(struct zMisa, uint64_t);

  void startup_z_update_Misa_A(void);

  void finish_z_update_Misa_A(void);

  uint64_t z_get_Misa_B(struct zMisa);

  struct zMisa z_update_Misa_B(struct zMisa, uint64_t);

  void startup_z_update_Misa_B(void);

  void finish_z_update_Misa_B(void);

  uint64_t z_get_Misa_C(struct zMisa);

  struct zMisa z_update_Misa_C(struct zMisa, uint64_t);

  void startup_z_update_Misa_C(void);

  void finish_z_update_Misa_C(void);

  uint64_t z_get_Misa_D(struct zMisa);

  struct zMisa z_update_Misa_D(struct zMisa, uint64_t);

  void startup_z_update_Misa_D(void);

  void finish_z_update_Misa_D(void);

  uint64_t z_get_Misa_E(struct zMisa);

  struct zMisa z_update_Misa_E(struct zMisa, uint64_t);

  void startup_z_update_Misa_E(void);

  void finish_z_update_Misa_E(void);

  uint64_t z_get_Misa_F(struct zMisa);

  struct zMisa z_update_Misa_F(struct zMisa, uint64_t);

  void startup_z_update_Misa_F(void);

  void finish_z_update_Misa_F(void);

  uint64_t z_get_Misa_H(struct zMisa);

  struct zMisa z_update_Misa_H(struct zMisa, uint64_t);

  void startup_z_update_Misa_H(void);

  void finish_z_update_Misa_H(void);

  uint64_t z_get_Misa_I(struct zMisa);

  struct zMisa z_update_Misa_I(struct zMisa, uint64_t);

  void startup_z_update_Misa_I(void);

  void finish_z_update_Misa_I(void);

  uint64_t z_get_Misa_M(struct zMisa);

  struct zMisa z_update_Misa_M(struct zMisa, uint64_t);

  void startup_z_update_Misa_M(void);

  void finish_z_update_Misa_M(void);

  sbits z_get_Misa_MXL(struct zMisa);

  void startup_z_get_Misa_MXL(void);

  void finish_z_get_Misa_MXL(void);

  struct zMisa z_update_Misa_MXL(struct zMisa, sbits);

  void startup_z_update_Misa_MXL(void);

  void finish_z_update_Misa_MXL(void);

  uint64_t z_get_Misa_S(struct zMisa);

  struct zMisa z_update_Misa_S(struct zMisa, uint64_t);

  void startup_z_update_Misa_S(void);

  void finish_z_update_Misa_S(void);

  uint64_t z_get_Misa_U(struct zMisa);

  struct zMisa z_update_Misa_U(struct zMisa, uint64_t);

  void startup_z_update_Misa_U(void);

  void finish_z_update_Misa_U(void);

  uint64_t z_get_Misa_V(struct zMisa);

  struct zMisa z_update_Misa_V(struct zMisa, uint64_t);

  void startup_z_update_Misa_V(void);

  void finish_z_update_Misa_V(void);

  void create_letbind_148(void);
  void kill_letbind_148(void);


  void create_letbind_149(void);
  void kill_letbind_149(void);


  void create_letbind_150(void);
  void kill_letbind_150(void);


  void create_letbind_151(void);
  void kill_letbind_151(void);


  void create_letbind_152(void);
  void kill_letbind_152(void);


  void create_letbind_153(void);
  void kill_letbind_153(void);


  void create_letbind_154(void);
  void kill_letbind_154(void);


  void create_letbind_155(void);
  void kill_letbind_155(void);


  void create_letbind_156(void);
  void kill_letbind_156(void);


  void create_letbind_157(void);
  void kill_letbind_157(void);


  void create_letbind_158(void);
  void kill_letbind_158(void);


  void create_letbind_159(void);
  void kill_letbind_159(void);


  void create_letbind_160(void);
  void kill_letbind_160(void);


  void create_letbind_161(void);
  void kill_letbind_161(void);


  void create_letbind_162(void);
  void kill_letbind_162(void);


  void create_letbind_163(void);
  void kill_letbind_163(void);


  void create_letbind_164(void);
  void kill_letbind_164(void);


  void create_letbind_165(void);
  void kill_letbind_165(void);


  void create_letbind_166(void);
  void kill_letbind_166(void);


  void create_letbind_167(void);
  void kill_letbind_167(void);


  struct zMisa zlegalizze_misa(struct zMisa, sbits);

  void startup_zlegalizze_misa(void);

  void finish_zlegalizze_misa(void);

  bool zvirtual_memory_supported(unit);

  bool zinVirtualPrivilege(unit);

  enum zPrivilege zlowest_supported_privLevel(unit);

  bool zhave_nominal_privLevel(uint64_t);

  struct zMstatus zMk_Mstatus(uint64_t);

  void startup_zMk_Mstatus(void);

  void finish_zMk_Mstatus(void);

  uint64_t z_get_Mstatus_FS(struct zMstatus);

  struct zMstatus z_update_Mstatus_FS(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_FS(void);

  void finish_z_update_Mstatus_FS(void);

  uint64_t z_get_Mstatus_GVA(struct zMstatus);

  struct zMstatus z_update_Mstatus_GVA(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_GVA(void);

  void finish_z_update_Mstatus_GVA(void);

  uint64_t z_get_Mstatus_MDT(struct zMstatus);

  struct zMstatus z_update_Mstatus_MDT(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MDT(void);

  void finish_z_update_Mstatus_MDT(void);

  uint64_t z_get_Mstatus_MIE(struct zMstatus);

  struct zMstatus z_update_Mstatus_MIE(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MIE(void);

  void finish_z_update_Mstatus_MIE(void);

  uint64_t z_get_Mstatus_MPELP(struct zMstatus);

  struct zMstatus z_update_Mstatus_MPELP(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MPELP(void);

  void finish_z_update_Mstatus_MPELP(void);

  uint64_t z_get_Mstatus_MPIE(struct zMstatus);

  struct zMstatus z_update_Mstatus_MPIE(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MPIE(void);

  void finish_z_update_Mstatus_MPIE(void);

  uint64_t z_get_Mstatus_MPP(struct zMstatus);

  struct zMstatus z_update_Mstatus_MPP(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MPP(void);

  void finish_z_update_Mstatus_MPP(void);

  uint64_t z_get_Mstatus_MPRV(struct zMstatus);

  struct zMstatus z_update_Mstatus_MPRV(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MPRV(void);

  void finish_z_update_Mstatus_MPRV(void);

  uint64_t z_get_Mstatus_MPV(struct zMstatus);

  struct zMstatus z_update_Mstatus_MPV(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MPV(void);

  void finish_z_update_Mstatus_MPV(void);

  uint64_t z_get_Mstatus_MXR(struct zMstatus);

  struct zMstatus z_update_Mstatus_MXR(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_MXR(void);

  void finish_z_update_Mstatus_MXR(void);

  sbits z_get_Mstatus_SD(struct zMstatus);

  void startup_z_get_Mstatus_SD(void);

  void finish_z_get_Mstatus_SD(void);

  struct zMstatus z_update_Mstatus_SD(struct zMstatus, sbits);

  void startup_z_update_Mstatus_SD(void);

  void finish_z_update_Mstatus_SD(void);

  uint64_t z_get_Mstatus_SDT(struct zMstatus);

  struct zMstatus z_update_Mstatus_SDT(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SDT(void);

  void finish_z_update_Mstatus_SDT(void);

  uint64_t z_get_Mstatus_SIE(struct zMstatus);

  struct zMstatus z_update_Mstatus_SIE(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SIE(void);

  void finish_z_update_Mstatus_SIE(void);

  uint64_t z_get_Mstatus_SPELP(struct zMstatus);

  struct zMstatus z_update_Mstatus_SPELP(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SPELP(void);

  void finish_z_update_Mstatus_SPELP(void);

  uint64_t z_get_Mstatus_SPIE(struct zMstatus);

  struct zMstatus z_update_Mstatus_SPIE(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SPIE(void);

  void finish_z_update_Mstatus_SPIE(void);

  uint64_t z_get_Mstatus_SPP(struct zMstatus);

  struct zMstatus z_update_Mstatus_SPP(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SPP(void);

  void finish_z_update_Mstatus_SPP(void);

  uint64_t z_get_Mstatus_SUM(struct zMstatus);

  struct zMstatus z_update_Mstatus_SUM(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SUM(void);

  void finish_z_update_Mstatus_SUM(void);

  uint64_t z_get_Mstatus_SXL(struct zMstatus);

  struct zMstatus z_update_Mstatus_SXL(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_SXL(void);

  void finish_z_update_Mstatus_SXL(void);

  uint64_t z_get_Mstatus_TSR(struct zMstatus);

  struct zMstatus z_update_Mstatus_TSR(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_TSR(void);

  void finish_z_update_Mstatus_TSR(void);

  uint64_t z_get_Mstatus_TVM(struct zMstatus);

  struct zMstatus z_update_Mstatus_TVM(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_TVM(void);

  void finish_z_update_Mstatus_TVM(void);

  uint64_t z_get_Mstatus_TW(struct zMstatus);

  struct zMstatus z_update_Mstatus_TW(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_TW(void);

  void finish_z_update_Mstatus_TW(void);

  uint64_t z_get_Mstatus_UXL(struct zMstatus);

  struct zMstatus z_update_Mstatus_UXL(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_UXL(void);

  void finish_z_update_Mstatus_UXL(void);

  uint64_t z_get_Mstatus_VS(struct zMstatus);

  struct zMstatus z_update_Mstatus_VS(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_VS(void);

  void finish_z_update_Mstatus_VS(void);

  uint64_t z_get_Mstatus_XS(struct zMstatus);

  struct zMstatus z_update_Mstatus_XS(struct zMstatus, uint64_t);

  void startup_z_update_Mstatus_XS(void);

  void finish_z_update_Mstatus_XS(void);

  struct zMstatus zlegalizze_mstatus(struct zMstatus, uint64_t);

  void startup_zlegalizze_mstatus(void);

  void finish_zlegalizze_mstatus(void);

  struct zMstatus zread_mstatus(unit);

  void startup_zread_mstatus(void);

  void finish_zread_mstatus(void);

  struct zHstatus zMk_Hstatus(uint64_t);

  void startup_zMk_Hstatus(void);

  void finish_zMk_Hstatus(void);

  uint64_t z_get_Hstatus_GVA(struct zHstatus);

  struct zHstatus z_update_Hstatus_GVA(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_GVA(void);

  void finish_z_update_Hstatus_GVA(void);

  uint64_t z_get_Hstatus_HU(struct zHstatus);

  struct zHstatus z_update_Hstatus_HU(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_HU(void);

  void finish_z_update_Hstatus_HU(void);

  uint64_t z_get_Hstatus_HUKTE(struct zHstatus);

  struct zHstatus z_update_Hstatus_HUKTE(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_HUKTE(void);

  void finish_z_update_Hstatus_HUKTE(void);

  uint64_t z_get_Hstatus_HUPMM(struct zHstatus);

  struct zHstatus z_update_Hstatus_HUPMM(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_HUPMM(void);

  void finish_z_update_Hstatus_HUPMM(void);

  uint64_t z_get_Hstatus_SPV(struct zHstatus);

  struct zHstatus z_update_Hstatus_SPV(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_SPV(void);

  void finish_z_update_Hstatus_SPV(void);

  uint64_t z_get_Hstatus_SPVP(struct zHstatus);

  struct zHstatus z_update_Hstatus_SPVP(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_SPVP(void);

  void finish_z_update_Hstatus_SPVP(void);

  uint64_t z_get_Hstatus_VGEIN(struct zHstatus);

  struct zHstatus z_update_Hstatus_VGEIN(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_VGEIN(void);

  void finish_z_update_Hstatus_VGEIN(void);

  uint64_t z_get_Hstatus_VSXL(struct zHstatus);

  struct zHstatus z_update_Hstatus_VSXL(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_VSXL(void);

  void finish_z_update_Hstatus_VSXL(void);

  uint64_t z_get_Hstatus_VTSR(struct zHstatus);

  struct zHstatus z_update_Hstatus_VTSR(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_VTSR(void);

  void finish_z_update_Hstatus_VTSR(void);

  uint64_t z_get_Hstatus_VTVM(struct zHstatus);

  struct zHstatus z_update_Hstatus_VTVM(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_VTVM(void);

  void finish_z_update_Hstatus_VTVM(void);

  uint64_t z_get_Hstatus_VTW(struct zHstatus);

  struct zHstatus z_update_Hstatus_VTW(struct zHstatus, uint64_t);

  void startup_z_update_Hstatus_VTW(void);

  void finish_z_update_Hstatus_VTW(void);

  struct zHstatus zlegalizze_hstatus(struct zHstatus, uint64_t);

  void startup_zlegalizze_hstatus(void);

  void finish_zlegalizze_hstatus(void);

  struct zSeccfg zMk_Seccfg(uint64_t);

  void startup_zMk_Seccfg(void);

  void finish_zMk_Seccfg(void);

  uint64_t z_get_Seccfg_MLPE(struct zSeccfg);

  struct zSeccfg z_update_Seccfg_MLPE(struct zSeccfg, uint64_t);

  void startup_z_update_Seccfg_MLPE(void);

  void finish_z_update_Seccfg_MLPE(void);

  uint64_t z_get_Seccfg_PMM(struct zSeccfg);

  struct zSeccfg z_update_Seccfg_PMM(struct zSeccfg, uint64_t);

  void startup_z_update_Seccfg_PMM(void);

  void finish_z_update_Seccfg_PMM(void);

  uint64_t z_get_Seccfg_SSEED(struct zSeccfg);

  struct zSeccfg z_update_Seccfg_SSEED(struct zSeccfg, uint64_t);

  void startup_z_update_Seccfg_SSEED(void);

  void finish_z_update_Seccfg_SSEED(void);

  uint64_t z_get_Seccfg_USEED(struct zSeccfg);

  struct zSeccfg z_update_Seccfg_USEED(struct zSeccfg, uint64_t);

  void startup_z_update_Seccfg_USEED(void);

  void finish_z_update_Seccfg_USEED(void);

  struct zSeccfg zlegalizze_mseccfg(struct zSeccfg, uint64_t);

  void startup_zlegalizze_mseccfg(void);

  void finish_zlegalizze_mseccfg(void);

  struct zMEnvcfg zMk_MEnvcfg(uint64_t);

  void startup_zMk_MEnvcfg(void);

  void finish_zMk_MEnvcfg(void);

  uint64_t z_get_MEnvcfg_ADUE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_ADUE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_ADUE(void);

  void finish_z_update_MEnvcfg_ADUE(void);

  uint64_t z_get_MEnvcfg_CBCFE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_CBCFE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_CBCFE(void);

  void finish_z_update_MEnvcfg_CBCFE(void);

  uint64_t z_get_MEnvcfg_CBIE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_CBIE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_CBIE(void);

  void finish_z_update_MEnvcfg_CBIE(void);

  uint64_t z_get_MEnvcfg_CBZE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_CBZE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_CBZE(void);

  void finish_z_update_MEnvcfg_CBZE(void);

  uint64_t z_get_MEnvcfg_DTE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_DTE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_DTE(void);

  void finish_z_update_MEnvcfg_DTE(void);

  uint64_t z_get_MEnvcfg_FIOM(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_FIOM(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_FIOM(void);

  void finish_z_update_MEnvcfg_FIOM(void);

  uint64_t z_get_MEnvcfg_LPE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_LPE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_LPE(void);

  void finish_z_update_MEnvcfg_LPE(void);

  uint64_t z_get_MEnvcfg_PBMTE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_PBMTE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_PBMTE(void);

  void finish_z_update_MEnvcfg_PBMTE(void);

  uint64_t z_get_MEnvcfg_PMM(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_PMM(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_PMM(void);

  void finish_z_update_MEnvcfg_PMM(void);

  uint64_t z_get_MEnvcfg_SSE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_SSE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_SSE(void);

  void finish_z_update_MEnvcfg_SSE(void);

  uint64_t z_get_MEnvcfg_STCE(struct zMEnvcfg);

  struct zMEnvcfg z_update_MEnvcfg_STCE(struct zMEnvcfg, uint64_t);

  void startup_z_update_MEnvcfg_STCE(void);

  void finish_z_update_MEnvcfg_STCE(void);

  struct zSEnvcfg zMk_SEnvcfg(uint64_t);

  void startup_zMk_SEnvcfg(void);

  void finish_zMk_SEnvcfg(void);

  uint64_t z_get_SEnvcfg_CBCFE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_CBCFE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_CBCFE(void);

  void finish_z_update_SEnvcfg_CBCFE(void);

  uint64_t z_get_SEnvcfg_CBIE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_CBIE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_CBIE(void);

  void finish_z_update_SEnvcfg_CBIE(void);

  uint64_t z_get_SEnvcfg_CBZE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_CBZE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_CBZE(void);

  void finish_z_update_SEnvcfg_CBZE(void);

  uint64_t z_get_SEnvcfg_FIOM(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_FIOM(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_FIOM(void);

  void finish_z_update_SEnvcfg_FIOM(void);

  uint64_t z_get_SEnvcfg_LPE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_LPE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_LPE(void);

  void finish_z_update_SEnvcfg_LPE(void);

  uint64_t z_get_SEnvcfg_PMM(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_PMM(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_PMM(void);

  void finish_z_update_SEnvcfg_PMM(void);

  uint64_t z_get_SEnvcfg_SSE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_SSE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_SSE(void);

  void finish_z_update_SEnvcfg_SSE(void);

  uint64_t z_get_SEnvcfg_UKTE(struct zSEnvcfg);

  struct zSEnvcfg z_update_SEnvcfg_UKTE(struct zSEnvcfg, uint64_t);

  void startup_z_update_SEnvcfg_UKTE(void);

  void finish_z_update_SEnvcfg_UKTE(void);

  struct zHEnvcfg zMk_HEnvcfg(uint64_t);

  void startup_zMk_HEnvcfg(void);

  void finish_zMk_HEnvcfg(void);

  uint64_t z_get_HEnvcfg_ADUE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_ADUE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_ADUE(void);

  void finish_z_update_HEnvcfg_ADUE(void);

  uint64_t z_get_HEnvcfg_CBCFE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_CBCFE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_CBCFE(void);

  void finish_z_update_HEnvcfg_CBCFE(void);

  uint64_t z_get_HEnvcfg_CBIE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_CBIE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_CBIE(void);

  void finish_z_update_HEnvcfg_CBIE(void);

  uint64_t z_get_HEnvcfg_CBZE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_CBZE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_CBZE(void);

  void finish_z_update_HEnvcfg_CBZE(void);

  uint64_t z_get_HEnvcfg_DTE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_DTE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_DTE(void);

  void finish_z_update_HEnvcfg_DTE(void);

  uint64_t z_get_HEnvcfg_FIOM(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_FIOM(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_FIOM(void);

  void finish_z_update_HEnvcfg_FIOM(void);

  uint64_t z_get_HEnvcfg_LPE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_LPE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_LPE(void);

  void finish_z_update_HEnvcfg_LPE(void);

  uint64_t z_get_HEnvcfg_PBMTE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_PBMTE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_PBMTE(void);

  void finish_z_update_HEnvcfg_PBMTE(void);

  uint64_t z_get_HEnvcfg_PMM(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_PMM(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_PMM(void);

  void finish_z_update_HEnvcfg_PMM(void);

  uint64_t z_get_HEnvcfg_SSE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_SSE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_SSE(void);

  void finish_z_update_HEnvcfg_SSE(void);

  uint64_t z_get_HEnvcfg_STCE(struct zHEnvcfg);

  struct zHEnvcfg z_update_HEnvcfg_STCE(struct zHEnvcfg, uint64_t);

  void startup_z_update_HEnvcfg_STCE(void);

  void finish_z_update_HEnvcfg_STCE(void);

  uint64_t zlegalizze_xenvcfg_cbie(uint64_t, uint64_t);

  struct zMEnvcfg zlegalizze_menvcfg(struct zMEnvcfg, uint64_t);

  void startup_zlegalizze_menvcfg(void);

  void finish_zlegalizze_menvcfg(void);

  struct zSEnvcfg zlegalizze_senvcfg(struct zSEnvcfg, uint64_t);

  void startup_zlegalizze_senvcfg(void);

  void finish_zlegalizze_senvcfg(void);

  struct zHEnvcfg zlegalizze_henvcfg(struct zHEnvcfg, uint64_t);

  void startup_zlegalizze_henvcfg(void);

  void finish_zlegalizze_henvcfg(void);

  struct zHEnvcfg zread_henvcfg(unit);

  void startup_zread_henvcfg(void);

  void finish_zread_henvcfg(void);

  struct zSEnvcfg zread_senvcfg(unit);

  void startup_zread_senvcfg(void);

  void finish_zread_senvcfg(void);

  bool zis_fiom_active(unit);

  struct zMtvec zundefined_Mtvec(unit);

  void startup_zundefined_Mtvec(void);

  void finish_zundefined_Mtvec(void);

  struct zMtvec zMk_Mtvec(sbits);

  void startup_zMk_Mtvec(void);

  void finish_zMk_Mtvec(void);

  sbits z_get_Mtvec_Base(struct zMtvec);

  void startup_z_get_Mtvec_Base(void);

  void finish_z_get_Mtvec_Base(void);

  struct zMtvec z_update_Mtvec_Base(struct zMtvec, sbits);

  void startup_z_update_Mtvec_Base(void);

  void finish_z_update_Mtvec_Base(void);

  uint64_t z_get_Mtvec_Mode(struct zMtvec);

  struct zMtvec z_update_Mtvec_Mode(struct zMtvec, uint64_t);

  void startup_z_update_Mtvec_Mode(void);

  void finish_z_update_Mtvec_Mode(void);

  struct zMtvec zlegalizze_tvec(struct zMtvec, sbits, bool, int64_t, bool, int64_t);

  void startup_zlegalizze_tvec(void);

  void finish_zlegalizze_tvec(void);

  struct zMcause zundefined_Mcause(unit);

  void startup_zundefined_Mcause(void);

  void finish_zundefined_Mcause(void);

  struct zMcause zMk_Mcause(sbits);

  void startup_zMk_Mcause(void);

  void finish_zMk_Mcause(void);

  sbits z_get_Mcause_Cause(struct zMcause);

  void startup_z_get_Mcause_Cause(void);

  void finish_z_get_Mcause_Cause(void);

  struct zMcause z_update_Mcause_Cause(struct zMcause, sbits);

  void startup_z_update_Mcause_Cause(void);

  void finish_z_update_Mcause_Cause(void);

  sbits z_get_Mcause_IsInterrupt(struct zMcause);

  void startup_z_get_Mcause_IsInterrupt(void);

  void finish_z_get_Mcause_IsInterrupt(void);

  struct zMcause z_update_Mcause_IsInterrupt(struct zMcause, sbits);

  void startup_z_update_Mcause_IsInterrupt(void);

  void finish_z_update_Mcause_IsInterrupt(void);

  struct zMcause zlegalizze_cause(struct zMcause, sbits, bool);

  void startup_zlegalizze_cause(void);

  void finish_zlegalizze_cause(void);

  void ztvec_addr(struct zoptionzIbzK *rop, struct zMtvec, struct zMcause);

  void startup_ztvec_addr(void);

  void finish_ztvec_addr(void);

  sbits zlegalizze_xepc(sbits);

  void startup_zlegalizze_xepc(void);

  void finish_zlegalizze_xepc(void);

  sbits zalign_pc(sbits);

  void startup_zalign_pc(void);

  void finish_zalign_pc(void);

  struct zCounteren zundefined_Counteren(unit);

  void startup_zundefined_Counteren(void);

  void finish_zundefined_Counteren(void);

  struct zCounteren zMk_Counteren(uint64_t);

  void startup_zMk_Counteren(void);

  void finish_zMk_Counteren(void);

  uint64_t z_get_Counteren_TM(struct zCounteren);

  void create_letbind_168(void);
  void kill_letbind_168(void);


  struct zCounteren zlegalizze_scounteren(struct zCounteren, sbits);

  void startup_zlegalizze_scounteren(void);

  void finish_zlegalizze_scounteren(void);

  void create_letbind_169(void);
  void kill_letbind_169(void);


  struct zCounteren zlegalizze_hcounteren(struct zCounteren, sbits);

  void startup_zlegalizze_hcounteren(void);

  void finish_zlegalizze_hcounteren(void);

  void create_letbind_170(void);
  void kill_letbind_170(void);


  struct zCounteren zlegalizze_mcounteren(struct zCounteren, sbits);

  void startup_zlegalizze_mcounteren(void);

  void finish_zlegalizze_mcounteren(void);

  struct zCounterin zMk_Counterin(uint64_t);

  void startup_zMk_Counterin(void);

  void finish_zMk_Counterin(void);

  uint64_t z_get_Counterin_CY(struct zCounterin);

  uint64_t z_get_Counterin_HPM(struct zCounterin);

  uint64_t z_get_Counterin_IR(struct zCounterin);

  struct zCounterin zlegalizze_mcountinhibit(struct zCounterin, sbits);

  void startup_zlegalizze_mcountinhibit(void);

  void finish_zlegalizze_mcountinhibit(void);

  struct zSstatus zMk_Sstatus(uint64_t);

  void startup_zMk_Sstatus(void);

  void finish_zMk_Sstatus(void);

  uint64_t z_get_Sstatus_FS(struct zSstatus);

  struct zSstatus z_update_Sstatus_FS(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_FS(void);

  void finish_z_update_Sstatus_FS(void);

  uint64_t z_get_Sstatus_MXR(struct zSstatus);

  struct zSstatus z_update_Sstatus_MXR(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_MXR(void);

  void finish_z_update_Sstatus_MXR(void);

  struct zSstatus z_update_Sstatus_SD(struct zSstatus, sbits);

  void startup_z_update_Sstatus_SD(void);

  void finish_z_update_Sstatus_SD(void);

  uint64_t z_get_Sstatus_SDT(struct zSstatus);

  struct zSstatus z_update_Sstatus_SDT(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SDT(void);

  void finish_z_update_Sstatus_SDT(void);

  uint64_t z_get_Sstatus_SIE(struct zSstatus);

  struct zSstatus z_update_Sstatus_SIE(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SIE(void);

  void finish_z_update_Sstatus_SIE(void);

  uint64_t z_get_Sstatus_SPELP(struct zSstatus);

  struct zSstatus z_update_Sstatus_SPELP(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SPELP(void);

  void finish_z_update_Sstatus_SPELP(void);

  uint64_t z_get_Sstatus_SPIE(struct zSstatus);

  struct zSstatus z_update_Sstatus_SPIE(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SPIE(void);

  void finish_z_update_Sstatus_SPIE(void);

  uint64_t z_get_Sstatus_SPP(struct zSstatus);

  struct zSstatus z_update_Sstatus_SPP(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SPP(void);

  void finish_z_update_Sstatus_SPP(void);

  uint64_t z_get_Sstatus_SUM(struct zSstatus);

  struct zSstatus z_update_Sstatus_SUM(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_SUM(void);

  void finish_z_update_Sstatus_SUM(void);

  uint64_t z_get_Sstatus_UXL(struct zSstatus);

  struct zSstatus z_update_Sstatus_UXL(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_UXL(void);

  void finish_z_update_Sstatus_UXL(void);

  uint64_t z_get_Sstatus_VS(struct zSstatus);

  struct zSstatus z_update_Sstatus_VS(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_VS(void);

  void finish_z_update_Sstatus_VS(void);

  uint64_t z_get_Sstatus_XS(struct zSstatus);

  struct zSstatus z_update_Sstatus_XS(struct zSstatus, uint64_t);

  void startup_z_update_Sstatus_XS(void);

  void finish_z_update_Sstatus_XS(void);

  struct zSstatus zlower_mstatus(struct zMstatus, bool);

  void startup_zlower_mstatus(void);

  void finish_zlower_mstatus(void);

  struct zMstatus zlift_sstatus(struct zMstatus, struct zSstatus);

  void startup_zlift_sstatus(void);

  void finish_zlift_sstatus(void);

  struct zMstatus zlegalizze_sstatus(struct zMstatus, sbits, bool);

  void startup_zlegalizze_sstatus(void);

  void finish_zlegalizze_sstatus(void);

  struct zHgatp64 zMk_Hgatp64(uint64_t);

  void startup_zMk_Hgatp64(void);

  void finish_zMk_Hgatp64(void);

  uint64_t z_get_Hgatp64_Mode(struct zHgatp64);

  struct zHgatp64 z_update_Hgatp64_Mode(struct zHgatp64, uint64_t);

  void startup_z_update_Hgatp64_Mode(void);

  void finish_z_update_Hgatp64_Mode(void);

  uint64_t z_get_Hgatp64_PPN(struct zHgatp64);

  struct zHgatp64 z_update_Hgatp64_PPN(struct zHgatp64, uint64_t);

  void startup_z_update_Hgatp64_PPN(void);

  void finish_z_update_Hgatp64_PPN(void);

  uint64_t z_get_Hgatp64_VMID(struct zHgatp64);

  struct zHgatp64 z_update_Hgatp64_VMID(struct zHgatp64, uint64_t);

  void startup_z_update_Hgatp64_VMID(void);

  void finish_z_update_Hgatp64_VMID(void);

  struct zHgatp32 zMk_Hgatp32(uint64_t);

  void startup_zMk_Hgatp32(void);

  void finish_zMk_Hgatp32(void);

  uint64_t z_get_Hgatp32_Mode(struct zHgatp32);

  struct zHgatp32 z_update_Hgatp32_Mode(struct zHgatp32, uint64_t);

  void startup_z_update_Hgatp32_Mode(void);

  void finish_z_update_Hgatp32_Mode(void);

  uint64_t z_get_Hgatp32_PPN(struct zHgatp32);

  struct zHgatp32 z_update_Hgatp32_PPN(struct zHgatp32, uint64_t);

  void startup_z_update_Hgatp32_PPN(void);

  void finish_z_update_Hgatp32_PPN(void);

  uint64_t z_get_Hgatp32_VMID(struct zHgatp32);

  struct zHgatp32 z_update_Hgatp32_VMID(struct zHgatp32, uint64_t);

  void startup_z_update_Hgatp32_VMID(void);

  void finish_z_update_Hgatp32_VMID(void);

  sbits zlegalizze_hgatp(enum zArchitecture, sbits, sbits);

  void startup_zlegalizze_hgatp(void);

  void finish_zlegalizze_hgatp(void);

  struct zSatp64 zMk_Satp64(uint64_t);

  void startup_zMk_Satp64(void);

  void finish_zMk_Satp64(void);

  uint64_t z_get_Satp64_Asid(struct zSatp64);

  struct zSatp64 z_update_Satp64_Asid(struct zSatp64, uint64_t);

  void startup_z_update_Satp64_Asid(void);

  void finish_z_update_Satp64_Asid(void);

  uint64_t z_get_Satp64_Mode(struct zSatp64);

  uint64_t z_get_Satp64_PPN(struct zSatp64);

  struct zSatp64 z_update_Satp64_PPN(struct zSatp64, uint64_t);

  void startup_z_update_Satp64_PPN(void);

  void finish_z_update_Satp64_PPN(void);

  struct zSatp32 zMk_Satp32(uint64_t);

  void startup_zMk_Satp32(void);

  void finish_zMk_Satp32(void);

  uint64_t z_get_Satp32_Asid(struct zSatp32);

  struct zSatp32 z_update_Satp32_Asid(struct zSatp32, uint64_t);

  void startup_z_update_Satp32_Asid(void);

  void finish_z_update_Satp32_Asid(void);

  uint64_t z_get_Satp32_Mode(struct zSatp32);

  uint64_t z_get_Satp32_PPN(struct zSatp32);

  struct zSatp32 z_update_Satp32_PPN(struct zSatp32, uint64_t);

  void startup_z_update_Satp32_PPN(void);

  void finish_z_update_Satp32_PPN(void);

  sbits zget_asid(enum zTranslationStage);

  void startup_zget_asid(void);

  void finish_zget_asid(void);

  sbits zget_vmid(enum zTranslationStage);

  void startup_zget_vmid(void);

  void finish_zget_vmid(void);

  sbits zlegalizze_satp(enum zArchitecture, bool, sbits, sbits);

  void startup_zlegalizze_satp(void);

  void finish_zlegalizze_satp(void);

  enum zFeatureEnabledResult zfeature_enabled_for_priv(enum zPrivilege, uint64_t, uint64_t, uint64_t);

  bool zcounter_enabled(int64_t, enum zPrivilege);

  enum zArchitecture zarchitecture(enum zPrivilege);

  bool zin32BitMode(unit);

  unit zgenerate_event(enum zEvent);

  unit zgenerate_trap_event(struct zTrapCause);

  void create_letbind_171(void);
  void kill_letbind_171(void);


  int64_t zevent_selector_width(unit);

  uint64_t zselector_value(uint64_t);

  void startup_zselector_value(void);

  void finish_zselector_value(void);

  bool zext_check_CSR(uint64_t, enum zPrivilege, enum zCSRAccessType);

  struct zMinterrupts zundefined_Minterrupts(unit);

  void startup_zundefined_Minterrupts(void);

  void finish_zundefined_Minterrupts(void);

  struct zMinterrupts zMk_Minterrupts(sbits);

  void startup_zMk_Minterrupts(void);

  void finish_zMk_Minterrupts(void);

  uint64_t z_get_Minterrupts_LCOFI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_LCOFI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_LCOFI(void);

  void finish_z_update_Minterrupts_LCOFI(void);

  uint64_t z_get_Minterrupts_MEI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_MEI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_MEI(void);

  void finish_z_update_Minterrupts_MEI(void);

  uint64_t z_get_Minterrupts_MSI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_MSI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_MSI(void);

  void finish_z_update_Minterrupts_MSI(void);

  uint64_t z_get_Minterrupts_MTI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_MTI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_MTI(void);

  void finish_z_update_Minterrupts_MTI(void);

  uint64_t z_get_Minterrupts_SEI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_SEI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_SEI(void);

  void finish_z_update_Minterrupts_SEI(void);

  uint64_t z_get_Minterrupts_SGEI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_SGEI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_SGEI(void);

  void finish_z_update_Minterrupts_SGEI(void);

  uint64_t z_get_Minterrupts_SSI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_SSI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_SSI(void);

  void finish_z_update_Minterrupts_SSI(void);

  uint64_t z_get_Minterrupts_STI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_STI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_STI(void);

  void finish_z_update_Minterrupts_STI(void);

  uint64_t z_get_Minterrupts_VSEI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_VSEI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_VSEI(void);

  void finish_z_update_Minterrupts_VSEI(void);

  uint64_t z_get_Minterrupts_VSSI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_VSSI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_VSSI(void);

  void finish_z_update_Minterrupts_VSSI(void);

  uint64_t z_get_Minterrupts_VSTI(struct zMinterrupts);

  struct zMinterrupts z_update_Minterrupts_VSTI(struct zMinterrupts, uint64_t);

  void startup_z_update_Minterrupts_VSTI(void);

  void finish_z_update_Minterrupts_VSTI(void);

  struct zMinterrupts zexternal_interrupts_pending(sbits);

  uint64_t zmachine_software_interrupt_pending(unit);

  uint64_t zsupervisor_software_interrupt_pending(unit);

  uint64_t zget_mtime(unit);

  uint64_t zget_hart_mtimecmp(unit);

  unit ztick_clock(unit);

  void create_letbind_172(void);
  void kill_letbind_172(void);


  sbits zlegalizze_hgeie(sbits);

  sbits zguest_external_interrupts_pending(unit);

  sbits zread_hgeip(unit);

  uint64_t zselected_vgein_in_hgeip(unit);

  void startup_zselected_vgein_in_hgeip(void);

  void finish_zselected_vgein_in_hgeip(void);

  struct zMinterrupts zsupported_interrupts_mask(struct zMinterrupts);

  void startup_zsupported_interrupts_mask(void);

  void finish_zsupported_interrupts_mask(void);

  struct zMinterrupts zlegalizze_mip(struct zMinterrupts, sbits);

  void startup_zlegalizze_mip(void);

  void finish_zlegalizze_mip(void);

  struct zMinterrupts zlegalizze_mie(struct zMinterrupts, sbits);

  void startup_zlegalizze_mie(void);

  void finish_zlegalizze_mie(void);

  struct zMinterrupts zlegalizze_mideleg(struct zMinterrupts, sbits);

  void startup_zlegalizze_mideleg(void);

  void finish_zlegalizze_mideleg(void);

  struct zMedeleg zundefined_Medeleg(unit);

  void startup_zundefined_Medeleg(void);

  void finish_zundefined_Medeleg(void);

  struct zMedeleg zMk_Medeleg(uint64_t);

  void startup_zMk_Medeleg(void);

  void finish_zMk_Medeleg(void);

  uint64_t z_get_Medeleg_Breakpoint(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Breakpoint(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Breakpoint(void);

  void finish_z_update_Medeleg_Breakpoint(void);

  uint64_t z_get_Medeleg_Double_Trap(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Double_Trap(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Double_Trap(void);

  void finish_z_update_Medeleg_Double_Trap(void);

  struct zMedeleg z_update_Medeleg_Fetch_Addr_Align(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Fetch_Addr_Align(void);

  void finish_z_update_Medeleg_Fetch_Addr_Align(void);

  uint64_t z_get_Medeleg_Fetch_GPage_Fault(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Fetch_GPage_Fault(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Fetch_GPage_Fault(void);

  void finish_z_update_Medeleg_Fetch_GPage_Fault(void);

  uint64_t z_get_Medeleg_Hardware_Error(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Hardware_Error(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Hardware_Error(void);

  void finish_z_update_Medeleg_Hardware_Error(void);

  uint64_t z_get_Medeleg_Load_GPage_Fault(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Load_GPage_Fault(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Load_GPage_Fault(void);

  void finish_z_update_Medeleg_Load_GPage_Fault(void);

  uint64_t z_get_Medeleg_MEnvCall(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_MEnvCall(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_MEnvCall(void);

  void finish_z_update_Medeleg_MEnvCall(void);

  uint64_t z_get_Medeleg_SAMO_GPage_Fault(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_SAMO_GPage_Fault(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_SAMO_GPage_Fault(void);

  void finish_z_update_Medeleg_SAMO_GPage_Fault(void);

  uint64_t z_get_Medeleg_Software_Check(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Software_Check(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Software_Check(void);

  void finish_z_update_Medeleg_Software_Check(void);

  uint64_t z_get_Medeleg_VSEnvCall(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_VSEnvCall(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_VSEnvCall(void);

  void finish_z_update_Medeleg_VSEnvCall(void);

  uint64_t z_get_Medeleg_Virtual_Instr(struct zMedeleg);

  struct zMedeleg z_update_Medeleg_Virtual_Instr(struct zMedeleg, uint64_t);

  void startup_z_update_Medeleg_Virtual_Instr(void);

  void finish_z_update_Medeleg_Virtual_Instr(void);

  struct zMedeleg zlegalizze_medeleg(struct zMedeleg, uint64_t);

  void startup_zlegalizze_medeleg(void);

  void finish_zlegalizze_medeleg(void);

  struct zMinterrupts zread_mip(enum zXipReadType);

  void startup_zread_mip(void);

  void finish_zread_mip(void);

  unit zupdate_mip(unit);

  void startup_zupdate_mip(void);

  void finish_zupdate_mip(void);

  unit zwrite_mip(sbits);

  struct zMinterrupts zlegalizze_hvip(struct zMinterrupts, sbits);

  void startup_zlegalizze_hvip(void);

  void finish_zlegalizze_hvip(void);

  struct zMinterrupts zlegalizze_hie(struct zMinterrupts, sbits);

  void startup_zlegalizze_hie(void);

  void finish_zlegalizze_hie(void);

  struct zMinterrupts zlegalizze_hip(struct zMinterrupts, sbits);

  void startup_zlegalizze_hip(void);

  void finish_zlegalizze_hip(void);

  struct zMinterrupts zlower_mip_to_hvip(struct zMinterrupts, struct zMinterrupts);

  void startup_zlower_mip_to_hvip(void);

  void finish_zlower_mip_to_hvip(void);

  struct zMinterrupts zlower_mie_to_hie(struct zMinterrupts);

  void startup_zlower_mie_to_hie(void);

  void finish_zlower_mie_to_hie(void);

  struct zMinterrupts zlower_mip_to_hip(struct zMinterrupts);

  void startup_zlower_mip_to_hip(void);

  void finish_zlower_mip_to_hip(void);

  uint64_t zhedeleg_writable_mask(unit);

  void startup_zhedeleg_writable_mask(void);

  void finish_zhedeleg_writable_mask(void);

  struct zMedeleg zlegalizze_hedeleg(struct zMedeleg, uint64_t);

  void startup_zlegalizze_hedeleg(void);

  void finish_zlegalizze_hedeleg(void);

  struct zMinterrupts zlegalizze_hideleg(struct zMinterrupts, sbits);

  void startup_zlegalizze_hideleg(void);

  void finish_zlegalizze_hideleg(void);

  struct zSinterrupts zMk_Sinterrupts(sbits);

  void startup_zMk_Sinterrupts(void);

  void finish_zMk_Sinterrupts(void);

  uint64_t z_get_Sinterrupts_LCOFI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_LCOFI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_LCOFI(void);

  void finish_z_update_Sinterrupts_LCOFI(void);

  uint64_t z_get_Sinterrupts_MEI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_MEI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_MEI(void);

  void finish_z_update_Sinterrupts_MEI(void);

  uint64_t z_get_Sinterrupts_MSI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_MSI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_MSI(void);

  void finish_z_update_Sinterrupts_MSI(void);

  uint64_t z_get_Sinterrupts_MTI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_MTI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_MTI(void);

  void finish_z_update_Sinterrupts_MTI(void);

  uint64_t z_get_Sinterrupts_SEI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_SEI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_SEI(void);

  void finish_z_update_Sinterrupts_SEI(void);

  uint64_t z_get_Sinterrupts_SSI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_SSI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_SSI(void);

  void finish_z_update_Sinterrupts_SSI(void);

  uint64_t z_get_Sinterrupts_STI(struct zSinterrupts);

  struct zSinterrupts z_update_Sinterrupts_STI(struct zSinterrupts, uint64_t);

  void startup_z_update_Sinterrupts_STI(void);

  void finish_z_update_Sinterrupts_STI(void);

  struct zSinterrupts zlower_mip(struct zMinterrupts, struct zMinterrupts);

  void startup_zlower_mip(void);

  void finish_zlower_mip(void);

  struct zSinterrupts zlower_mie(struct zMinterrupts, struct zMinterrupts);

  void startup_zlower_mie(void);

  void finish_zlower_mie(void);

  struct zSinterrupts zlower_mip_to_vsip(struct zMinterrupts, struct zMinterrupts);

  void startup_zlower_mip_to_vsip(void);

  void finish_zlower_mip_to_vsip(void);

  struct zMinterrupts zlower_mie_to_vsie(struct zMinterrupts, struct zMinterrupts);

  void startup_zlower_mie_to_vsie(void);

  void finish_zlower_mie_to_vsie(void);

  struct zMinterrupts zlift_sip(struct zMinterrupts, struct zMinterrupts, struct zSinterrupts);

  void startup_zlift_sip(void);

  void finish_zlift_sip(void);

  struct zMinterrupts zlegalizze_sip(struct zMinterrupts, struct zMinterrupts, sbits);

  void startup_zlegalizze_sip(void);

  void finish_zlegalizze_sip(void);

  struct zMinterrupts zlegalizze_vsip(struct zMinterrupts, struct zMinterrupts, sbits);

  void startup_zlegalizze_vsip(void);

  void finish_zlegalizze_vsip(void);

  struct zSinterrupts zread_sip(enum zXipReadType);

  void startup_zread_sip(void);

  void finish_zread_sip(void);

  unit zwrite_sip(sbits);

  struct zMinterrupts zlift_sie(struct zMinterrupts, struct zMinterrupts, struct zSinterrupts);

  void startup_zlift_sie(void);

  void finish_zlift_sie(void);

  struct zMinterrupts zlegalizze_sie(struct zMinterrupts, struct zMinterrupts, sbits);

  void startup_zlegalizze_sie(void);

  void finish_zlegalizze_sie(void);

  struct zMinterrupts zlegalizze_vsie(struct zMinterrupts, struct zMinterrupts, sbits);

  void startup_zlegalizze_vsie(void);

  void finish_zlegalizze_vsie(void);

  struct zHpmEvent zMk_HpmEvent(uint64_t);

  void startup_zMk_HpmEvent(void);

  void finish_zMk_HpmEvent(void);

  uint64_t z_get_HpmEvent_MINH(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_MINH(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_MINH(void);

  void finish_z_update_HpmEvent_MINH(void);

  uint64_t z_get_HpmEvent_OF(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_OF(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_OF(void);

  void finish_z_update_HpmEvent_OF(void);

  uint64_t z_get_HpmEvent_SINH(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_SINH(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_SINH(void);

  void finish_z_update_HpmEvent_SINH(void);

  uint64_t z_get_HpmEvent_UINH(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_UINH(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_UINH(void);

  void finish_z_update_HpmEvent_UINH(void);

  uint64_t z_get_HpmEvent_VSINH(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_VSINH(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_VSINH(void);

  void finish_z_update_HpmEvent_VSINH(void);

  uint64_t z_get_HpmEvent_VUINH(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_VUINH(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_VUINH(void);

  void finish_z_update_HpmEvent_VUINH(void);

  uint64_t z_get_HpmEvent_event(struct zHpmEvent);

  struct zHpmEvent z_update_HpmEvent_event(struct zHpmEvent, uint64_t);

  void startup_z_update_HpmEvent_event(void);

  void finish_z_update_HpmEvent_event(void);

  int64_t zhpmidx_from_bits(uint64_t);

  void startup_zhpmidx_from_bits(void);

  void finish_zhpmidx_from_bits(void);

  uint64_t zlegalizze_hpmevent(uint64_t);

  void startup_zlegalizze_hpmevent(void);

  void finish_zlegalizze_hpmevent(void);

  uint64_t zlegalizze_hpmcounter_value(uint64_t);

  void startup_zlegalizze_hpmcounter_value(void);

  void finish_zlegalizze_hpmcounter_value(void);

  sbits zread_mhpmcounter(int64_t);

  void startup_zread_mhpmcounter(void);

  void finish_zread_mhpmcounter(void);

  uint64_t zread_mhpmcounterh(int64_t);

  sbits zread_mhpmevent(int64_t);

  void startup_zread_mhpmevent(void);

  void finish_zread_mhpmevent(void);

  unit zclear_written_event_index(unit);

  unit zwrite_mhpmcounter(int64_t, uint64_t);

  void startup_zwrite_mhpmcounter(void);

  void finish_zwrite_mhpmcounter(void);

  unit zwrite_mhpmevent(int64_t, uint64_t);

  void startup_zwrite_mhpmevent(void);

  void finish_zwrite_mhpmevent(void);

  unit zdispatchEventCounter(int64_t, enum zPrivilege);

  void startup_zdispatchEventCounter(void);

  void finish_zdispatchEventCounter(void);

  void zext_fetch_check_pc(struct zoptionzIuzK *rop, sbits, sbits);

  unit zext_handle_fetch_check_error(unit);

  void zext_control_check_pc(struct zoptionzIuzK *rop, sbits);

  unit zext_handle_control_check_error(unit);

  void zext_data_get_addr(struct zExt_DataAddr_CheckzIuzK *rop, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, int64_t);

  unit zext_handle_data_check_error(unit);

  unit zhandle_trap_extension(enum zPrivilege, sbits, struct zoptionzIuzK);

  sbits zprepare_trap_vector(enum zPrivilege, struct zMcause);

  void startup_zprepare_trap_vector(void);

  void finish_zprepare_trap_vector(void);

  sbits zget_xepc(enum zPrivilege);

  void startup_zget_xepc(void);

  void finish_zget_xepc(void);

  sbits zset_xepc(enum zPrivilege, sbits);

  void startup_zset_xepc(void);

  void finish_zset_xepc(void);

  sbits zprepare_xret_target(enum zPrivilege);

  sbits zget_mtvec(unit);

  sbits zget_stvec(unit);

  sbits zget_vstvec(unit);

  sbits zset_mtvec(sbits);

  sbits zset_stvec(sbits);

  sbits zset_vstvec(sbits);

  unit zreset_tvecs(unit);

  void startup_zreset_tvecs(void);

  void finish_zreset_tvecs(void);

  void zexception_context(struct zExceptionContext *rop, struct zExceptionType, sbits);

  void startup_zexception_context(void);

  void finish_zexception_context(void);

  void zmake_exception_context(struct zExceptionContext *rop, struct zExceptionType, sbits, bool, struct zoptionzIbzK);

  void startup_zmake_exception_context(void);

  void finish_zmake_exception_context(void);

  void zmake_instr_exception_context(struct zExceptionContext *rop, struct zExceptionType, sbits);

  void startup_zmake_instr_exception_context(void);

  void finish_zmake_instr_exception_context(void);

  void create_letbind_173(void);
  void kill_letbind_173(void);


  void create_letbind_174(void);
  void kill_letbind_174(void);


  void create_letbind_175(void);
  void kill_letbind_175(void);


  enum zPmpAddrMatchType zpmpAddrMatchType_encdec_backwards(uint64_t);

  enum zPmpAddrMatchType zpmpAddrMatchType_encdec_backwards_infallible(uint64_t);

  struct zPmpcfg_ent zundefined_Pmpcfg_ent(unit);

  void startup_zundefined_Pmpcfg_ent(void);

  void finish_zundefined_Pmpcfg_ent(void);

  struct zPmpcfg_ent zMk_Pmpcfg_ent(uint64_t);

  void startup_zMk_Pmpcfg_ent(void);

  void finish_zMk_Pmpcfg_ent(void);

  uint64_t z_get_Pmpcfg_ent_A(struct zPmpcfg_ent);

  struct zPmpcfg_ent z_update_Pmpcfg_ent_A(struct zPmpcfg_ent, uint64_t);

  void startup_z_update_Pmpcfg_ent_A(void);

  void finish_z_update_Pmpcfg_ent_A(void);

  uint64_t z_get_Pmpcfg_ent_L(struct zPmpcfg_ent);

  struct zPmpcfg_ent z_update_Pmpcfg_ent_L(struct zPmpcfg_ent, uint64_t);

  void startup_z_update_Pmpcfg_ent_L(void);

  void finish_z_update_Pmpcfg_ent_L(void);

  uint64_t z_get_Pmpcfg_ent_R(struct zPmpcfg_ent);

  struct zPmpcfg_ent z_update_Pmpcfg_ent_R(struct zPmpcfg_ent, uint64_t);

  void startup_z_update_Pmpcfg_ent_R(void);

  void finish_z_update_Pmpcfg_ent_R(void);

  uint64_t z_get_Pmpcfg_ent_W(struct zPmpcfg_ent);

  struct zPmpcfg_ent z_update_Pmpcfg_ent_W(struct zPmpcfg_ent, uint64_t);

  void startup_z_update_Pmpcfg_ent_W(void);

  void finish_z_update_Pmpcfg_ent_W(void);

  uint64_t z_get_Pmpcfg_ent_X(struct zPmpcfg_ent);

  struct zPmpcfg_ent z_update_Pmpcfg_ent_X(struct zPmpcfg_ent, uint64_t);

  void startup_z_update_Pmpcfg_ent_X(void);

  void finish_z_update_Pmpcfg_ent_X(void);

  sbits zpmpReadCfgReg(int64_t);

  void startup_zpmpReadCfgReg(void);

  void finish_zpmpReadCfgReg(void);

  sbits zpmpReadAddrReg(int64_t);

  void startup_zpmpReadAddrReg(void);

  void finish_zpmpReadAddrReg(void);

  bool zpmpLocked(struct zPmpcfg_ent);

  bool zpmpTORLocked(struct zPmpcfg_ent);

  struct zPmpcfg_ent zpmpWriteCfg(struct zPmpcfg_ent, uint64_t);

  void startup_zpmpWriteCfg(void);

  void finish_zpmpWriteCfg(void);

  unit zpmpWriteCfgReg(int64_t, sbits);

  void startup_zpmpWriteCfgReg(void);

  void finish_zpmpWriteCfgReg(void);

  sbits zpmpWriteAddr(bool, bool, sbits, sbits);

  void startup_zpmpWriteAddr(void);

  void finish_zpmpWriteAddr(void);

  unit zpmpWriteAddrReg(int64_t, sbits);

  void startup_zpmpWriteAddrReg(void);

  void finish_zpmpWriteAddrReg(void);

  bool zpmpCheckRWX(struct zPmpcfg_ent, struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zpmpCheckRWX(void);

  void finish_zpmpCheckRWX(void);

  enum zpmpAddrMatch zpmpRangeMatch(sail_int, sail_int, sail_int, sail_int);

  void startup_zpmpRangeMatch(void);

  void finish_zpmpRangeMatch(void);

  sbits zpmpTORBound(sbits, int64_t);

  void startup_zpmpTORBound(void);

  void finish_zpmpTORBound(void);

  unit ztest_pmpTORBound(unit);

  void startup_ztest_pmpTORBound(void);

  void finish_ztest_pmpTORBound(void);

  enum zpmpAddrMatch zpmpMatchAddr(sbits, sbits, struct zPmpcfg_ent, sbits, sbits);

  void startup_zpmpMatchAddr(void);

  void finish_zpmpMatchAddr(void);

  void zpmpCheck(struct zoptionzIUExceptionTypezK *rop, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  void startup_zpmpCheck(void);

  void finish_zpmpCheck(void);

  unit zreset_pmp(unit);

  void startup_zreset_pmp(void);

  void finish_zreset_pmp(void);

  bool zis_mstateen_accessible(unit);

  bool zis_hstateen_accessible(unit);

  bool zis_sstateen_accessible(unit);

  int64_t zstateen_bit_index_forwards(enum zstateen_bit);

  int64_t zstateen_bit_index_forwards_infallible(enum zstateen_bit);

  struct zMstateen0 zMk_Mstateen0(uint64_t);

  void startup_zMk_Mstateen0(void);

  void finish_zMk_Mstateen0(void);

  uint64_t z_get_Mstateen0_C(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_C(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_C(void);

  void finish_z_update_Mstateen0_C(void);

  uint64_t z_get_Mstateen0_CONTEXT(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_CONTEXT(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_CONTEXT(void);

  void finish_z_update_Mstateen0_CONTEXT(void);

  uint64_t z_get_Mstateen0_ENVCFG(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_ENVCFG(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_ENVCFG(void);

  void finish_z_update_Mstateen0_ENVCFG(void);

  uint64_t z_get_Mstateen0_FCSR(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_FCSR(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_FCSR(void);

  void finish_z_update_Mstateen0_FCSR(void);

  uint64_t z_get_Mstateen0_P1P13(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_P1P13(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_P1P13(void);

  void finish_z_update_Mstateen0_P1P13(void);

  uint64_t z_get_Mstateen0_SE0(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_SE0(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_SE0(void);

  void finish_z_update_Mstateen0_SE0(void);

  uint64_t z_get_Mstateen0_SRMCFG(struct zMstateen0);

  struct zMstateen0 z_update_Mstateen0_SRMCFG(struct zMstateen0, uint64_t);

  void startup_z_update_Mstateen0_SRMCFG(void);

  void finish_z_update_Mstateen0_SRMCFG(void);

  struct zMstateen1 zMk_Mstateen1(uint64_t);

  void startup_zMk_Mstateen1(void);

  void finish_zMk_Mstateen1(void);

  uint64_t z_get_Mstateen1_SE1(struct zMstateen1);

  struct zMstateen1 z_update_Mstateen1_SE1(struct zMstateen1, uint64_t);

  void startup_z_update_Mstateen1_SE1(void);

  void finish_z_update_Mstateen1_SE1(void);

  struct zMstateen2 zMk_Mstateen2(uint64_t);

  void startup_zMk_Mstateen2(void);

  void finish_zMk_Mstateen2(void);

  uint64_t z_get_Mstateen2_SE2(struct zMstateen2);

  struct zMstateen2 z_update_Mstateen2_SE2(struct zMstateen2, uint64_t);

  void startup_z_update_Mstateen2_SE2(void);

  void finish_z_update_Mstateen2_SE2(void);

  struct zMstateen3 zMk_Mstateen3(uint64_t);

  void startup_zMk_Mstateen3(void);

  void finish_zMk_Mstateen3(void);

  uint64_t z_get_Mstateen3_SE3(struct zMstateen3);

  struct zMstateen3 z_update_Mstateen3_SE3(struct zMstateen3, uint64_t);

  void startup_z_update_Mstateen3_SE3(void);

  void finish_z_update_Mstateen3_SE3(void);

  struct zMstateen0 zlegalizze_mstateen0(struct zMstateen0, uint64_t);

  struct zMstateen0 zread_mstateen0(unit);

  uint64_t zget_mstateen(int64_t);

  struct zMstateen1 zlegalizze_mstateen1(struct zMstateen1, uint64_t);

  void startup_zlegalizze_mstateen1(void);

  void finish_zlegalizze_mstateen1(void);

  struct zMstateen2 zlegalizze_mstateen2(struct zMstateen2, uint64_t);

  void startup_zlegalizze_mstateen2(void);

  void finish_zlegalizze_mstateen2(void);

  struct zMstateen3 zlegalizze_mstateen3(struct zMstateen3, uint64_t);

  void startup_zlegalizze_mstateen3(void);

  void finish_zlegalizze_mstateen3(void);

  struct zHstateen0 zMk_Hstateen0(uint64_t);

  void startup_zMk_Hstateen0(void);

  void finish_zMk_Hstateen0(void);

  uint64_t z_get_Hstateen0_C(struct zHstateen0);

  struct zHstateen0 z_update_Hstateen0_C(struct zHstateen0, uint64_t);

  void startup_z_update_Hstateen0_C(void);

  void finish_z_update_Hstateen0_C(void);

  uint64_t z_get_Hstateen0_CONTEXT(struct zHstateen0);

  struct zHstateen0 z_update_Hstateen0_CONTEXT(struct zHstateen0, uint64_t);

  void startup_z_update_Hstateen0_CONTEXT(void);

  void finish_z_update_Hstateen0_CONTEXT(void);

  uint64_t z_get_Hstateen0_ENVCFG(struct zHstateen0);

  struct zHstateen0 z_update_Hstateen0_ENVCFG(struct zHstateen0, uint64_t);

  void startup_z_update_Hstateen0_ENVCFG(void);

  void finish_z_update_Hstateen0_ENVCFG(void);

  uint64_t z_get_Hstateen0_FCSR(struct zHstateen0);

  struct zHstateen0 z_update_Hstateen0_FCSR(struct zHstateen0, uint64_t);

  void startup_z_update_Hstateen0_FCSR(void);

  void finish_z_update_Hstateen0_FCSR(void);

  uint64_t z_get_Hstateen0_SE0(struct zHstateen0);

  struct zHstateen0 z_update_Hstateen0_SE0(struct zHstateen0, uint64_t);

  void startup_z_update_Hstateen0_SE0(void);

  void finish_z_update_Hstateen0_SE0(void);

  struct zHstateen1 zMk_Hstateen1(uint64_t);

  void startup_zMk_Hstateen1(void);

  void finish_zMk_Hstateen1(void);

  uint64_t z_get_Hstateen1_SE1(struct zHstateen1);

  struct zHstateen1 z_update_Hstateen1_SE1(struct zHstateen1, uint64_t);

  void startup_z_update_Hstateen1_SE1(void);

  void finish_z_update_Hstateen1_SE1(void);

  struct zHstateen2 zMk_Hstateen2(uint64_t);

  void startup_zMk_Hstateen2(void);

  void finish_zMk_Hstateen2(void);

  uint64_t z_get_Hstateen2_SE2(struct zHstateen2);

  struct zHstateen2 z_update_Hstateen2_SE2(struct zHstateen2, uint64_t);

  void startup_z_update_Hstateen2_SE2(void);

  void finish_z_update_Hstateen2_SE2(void);

  struct zHstateen3 zMk_Hstateen3(uint64_t);

  void startup_zMk_Hstateen3(void);

  void finish_zMk_Hstateen3(void);

  uint64_t z_get_Hstateen3_SE3(struct zHstateen3);

  struct zHstateen3 z_update_Hstateen3_SE3(struct zHstateen3, uint64_t);

  void startup_z_update_Hstateen3_SE3(void);

  void finish_z_update_Hstateen3_SE3(void);

  uint64_t zget_hstateen(int64_t);

  uint64_t zget_hstateen_mask(int64_t);

  struct zHstateen0 zlegalizze_hstateen0(struct zHstateen0, uint64_t);

  void startup_zlegalizze_hstateen0(void);

  void finish_zlegalizze_hstateen0(void);

  struct zHstateen1 zlegalizze_hstateen1(struct zHstateen1, uint64_t);

  void startup_zlegalizze_hstateen1(void);

  void finish_zlegalizze_hstateen1(void);

  struct zHstateen2 zlegalizze_hstateen2(struct zHstateen2, uint64_t);

  void startup_zlegalizze_hstateen2(void);

  void finish_zlegalizze_hstateen2(void);

  struct zHstateen3 zlegalizze_hstateen3(struct zHstateen3, uint64_t);

  void startup_zlegalizze_hstateen3(void);

  void finish_zlegalizze_hstateen3(void);

  struct zSstateen0 zMk_Sstateen0(uint64_t);

  void startup_zMk_Sstateen0(void);

  void finish_zMk_Sstateen0(void);

  uint64_t z_get_Sstateen0_C(struct zSstateen0);

  struct zSstateen0 z_update_Sstateen0_C(struct zSstateen0, uint64_t);

  void startup_z_update_Sstateen0_C(void);

  void finish_z_update_Sstateen0_C(void);

  uint64_t z_get_Sstateen0_FCSR(struct zSstateen0);

  struct zSstateen0 z_update_Sstateen0_FCSR(struct zSstateen0, uint64_t);

  void startup_z_update_Sstateen0_FCSR(void);

  void finish_z_update_Sstateen0_FCSR(void);

  uint64_t zget_sstateen(int64_t);

  uint64_t zget_sstateen_mask(int64_t);

  struct zSstateen0 zlegalizze_sstateen0(struct zSstateen0, uint64_t);

  void startup_zlegalizze_sstateen0(void);

  void finish_zlegalizze_sstateen0(void);

  struct zSstateen1 zlegalizze_sstateen1(struct zSstateen1, uint64_t);

  void startup_zlegalizze_sstateen1(void);

  void finish_zlegalizze_sstateen1(void);

  struct zSstateen2 zlegalizze_sstateen2(struct zSstateen2, uint64_t);

  void startup_zlegalizze_sstateen2(void);

  void finish_zlegalizze_sstateen2(void);

  struct zSstateen3 zlegalizze_sstateen3(struct zSstateen3, uint64_t);

  void startup_zlegalizze_sstateen3(void);

  void finish_zlegalizze_sstateen3(void);

  bool zcheck_stateen_bit(enum zPrivilege, enum zstateen_bit, int64_t);

  bool zis_zzfinx_enabled_by_stateen(unit);

  unit zreset_stateen(unit);

  void startup_zreset_stateen(void);

  void finish_zreset_stateen(void);

  void create_letbind_176(void);
  void kill_letbind_176(void);


  sbits zfregval_from_freg(sbits);

  sbits zfregval_into_freg(sbits);

  void zcanonical_NaN(lbits *rop, int64_t);

  void startup_zcanonical_NaN(void);

  void finish_zcanonical_NaN(void);

  void create_letbind_177(void);
  void kill_letbind_177(void);


  void znan_box(lbits *rop, sail_int, lbits);

  void startup_znan_box(void);

  void finish_znan_box(void);

  void znan_unbox(lbits *rop, int64_t, lbits);

  void startup_znan_unbox(void);

  void finish_znan_unbox(void);

  uint64_t zfregidx_bits(uint64_t);

  uint64_t zcfregidx_to_fregidx(uint64_t);

  uint64_t zencdec_cfreg_backwards(uint64_t);

  bool zencdec_cfreg_backwards_matches(uint64_t);

  uint64_t zencdec_cfreg_backwards_infallible(uint64_t);

  sbits zfregidx_to_regidx(uint64_t);

  void startup_zfregidx_to_regidx(void);

  void finish_zfregidx_to_regidx(void);

  uint64_t zencdec_freg_forwards(uint64_t);

  uint64_t zencdec_freg_backwards(uint64_t);

  bool zencdec_freg_backwards_matches(uint64_t);

  uint64_t zencdec_freg_forwards_infallible(uint64_t);

  uint64_t zencdec_freg_backwards_infallible(uint64_t);

  unit zdirty_fd_context(unit);

  void startup_zdirty_fd_context(void);

  void finish_zdirty_fd_context(void);

  unit zdirty_fd_context_if_present(unit);

  sbits zrF(int64_t);

  unit zwF(int64_t, sbits);

  void startup_zwF(void);

  void finish_zwF(void);

  sbits zrF_bits(uint64_t);

  void startup_zrF_bits(void);

  void finish_zrF_bits(void);

  unit zwF_bits(uint64_t, sbits);

  void startup_zwF_bits(void);

  void finish_zwF_bits(void);

  uint64_t zrF_BF16(uint64_t);

  void startup_zrF_BF16(void);

  void finish_zrF_BF16(void);

  unit zwF_BF16(uint64_t, uint64_t);

  void startup_zwF_BF16(void);

  void finish_zwF_BF16(void);

  uint64_t zrF_H(uint64_t);

  void startup_zrF_H(void);

  void finish_zrF_H(void);

  unit zwF_H(uint64_t, uint64_t);

  void startup_zwF_H(void);

  void finish_zwF_H(void);

  uint64_t zrF_S(uint64_t);

  void startup_zrF_S(void);

  void finish_zrF_S(void);

  unit zwF_S(uint64_t, uint64_t);

  void startup_zwF_S(void);

  void finish_zwF_S(void);

  uint64_t zrF_D(uint64_t);

  unit zwF_D(uint64_t, uint64_t);

  uint64_t zrF_or_X_H(uint64_t);

  uint64_t zrF_or_X_S(uint64_t);

  uint64_t zrF_or_X_D(uint64_t);

  unit zwF_or_X_H(uint64_t, uint64_t);

  void startup_zwF_or_X_H(void);

  void finish_zwF_or_X_H(void);

  unit zwF_or_X_S(uint64_t, uint64_t);

  void startup_zwF_or_X_S(void);

  void finish_zwF_or_X_S(void);

  unit zwF_or_X_D(uint64_t, uint64_t);

  void startup_zwF_or_X_D(void);

  void finish_zwF_or_X_D(void);

  void zfreg_abi_name_raw_forwards(sail_string *rop, uint64_t);

  void zfreg_abi_name_raw_forwards_infallible(sail_string *rop, uint64_t);

  void zfreg_arch_name_raw_forwards(sail_string *rop, uint64_t);

  void zfreg_arch_name_raw_forwards_infallible(sail_string *rop, uint64_t);

  void zfreg_name_forwards(sail_string *rop, uint64_t);

  void zfreg_name_forwards_infallible(sail_string *rop, uint64_t);

  void zfreg_or_reg_name_forwards(sail_string *rop, uint64_t);

  void zfreg_or_reg_name_forwards_infallible(sail_string *rop, uint64_t);

  void zcfreg_name_forwards(sail_string *rop, uint64_t);

  void zcfreg_name_forwards_infallible(sail_string *rop, uint64_t);

  struct zFcsr zundefined_Fcsr(unit);

  void startup_zundefined_Fcsr(void);

  void finish_zundefined_Fcsr(void);

  struct zFcsr zMk_Fcsr(uint64_t);

  void startup_zMk_Fcsr(void);

  void finish_zMk_Fcsr(void);

  uint64_t z_get_Fcsr_FFLAGS(struct zFcsr);

  uint64_t z_get_Fcsr_FRM(struct zFcsr);

  unit zwrite_fcsr(uint64_t, uint64_t);

  void startup_zwrite_fcsr(void);

  void finish_zwrite_fcsr(void);

  unit zaccrue_fflags(uint64_t);

  void startup_zaccrue_fflags(void);

  void finish_zaccrue_fflags(void);

  int64_t zencdec_nfields_forwards(uint64_t);

  uint64_t zencdec_nfields_backwards(int64_t);

  bool zencdec_nfields_forwards_matches(uint64_t);

  int64_t zencdec_nfields_forwards_infallible(uint64_t);

  uint64_t zencdec_nfields_backwards_infallible(int64_t);

  void znfields_string_forwards(sail_string *rop, int64_t);

  void znfields_string_forwards_infallible(sail_string *rop, int64_t);

  int64_t zencdec_nfields_pow2_forwards(uint64_t);

  uint64_t zencdec_nfields_pow2_backwards(int64_t);

  bool zencdec_nfields_pow2_forwards_matches(uint64_t);

  int64_t zencdec_nfields_pow2_forwards_infallible(uint64_t);

  uint64_t zencdec_nfields_pow2_backwards_infallible(int64_t);

  void znfields_pow2_string_forwards(sail_string *rop, int64_t);

  void znfields_pow2_string_forwards_infallible(sail_string *rop, int64_t);

  int64_t zvregidx_to_vregno(uint64_t);

  void startup_zvregidx_to_vregno(void);

  void finish_zvregidx_to_vregno(void);

  uint64_t zvregno_to_vregidx(int64_t);

  void startup_zvregno_to_vregidx(void);

  void finish_zvregno_to_vregidx(void);

  uint64_t zvregidx_offset(uint64_t, uint64_t);

  uint64_t zvregidx_offset_range(uint64_t, int64_t);

  void startup_zvregidx_offset_range(void);

  void finish_zvregidx_offset_range(void);

  uint64_t zvregidx_bits(uint64_t);

  uint64_t zencdec_vreg_forwards(uint64_t);

  uint64_t zencdec_vreg_backwards(uint64_t);

  bool zencdec_vreg_backwards_matches(uint64_t);

  uint64_t zencdec_vreg_forwards_infallible(uint64_t);

  uint64_t zencdec_vreg_backwards_infallible(uint64_t);

  void create_letbind_178(void);
  void kill_letbind_178(void);


  void zvreg_name_raw_forwards(sail_string *rop, uint64_t);

  void zvreg_name_raw_forwards_infallible(sail_string *rop, uint64_t);

  void zvreg_name_forwards(sail_string *rop, uint64_t);

  void zvreg_name_forwards_infallible(sail_string *rop, uint64_t);

  void zrV(lbits *rop, int64_t);

  void startup_zrV(void);

  void finish_zrV(void);

  unit zdirty_v_context(unit);

  void startup_zdirty_v_context(void);

  void finish_zdirty_v_context(void);

  unit zwV(int64_t, lbits);

  void zrV_bits(lbits *rop, uint64_t);

  unit zwV_bits(uint64_t, lbits);

  void create_letbind_179(void);
  void kill_letbind_179(void);


  struct zVtype zundefined_Vtype(unit);

  void startup_zundefined_Vtype(void);

  void finish_zundefined_Vtype(void);

  struct zVtype zMk_Vtype(sbits);

  void startup_zMk_Vtype(void);

  void finish_zMk_Vtype(void);

  sbits z_get_Vtype_reserved(struct zVtype);

  void startup_z_get_Vtype_reserved(void);

  void finish_z_get_Vtype_reserved(void);

  sbits z_get_Vtype_vill(struct zVtype);

  void startup_z_get_Vtype_vill(void);

  void finish_z_get_Vtype_vill(void);

  struct zVtype z_update_Vtype_vill(struct zVtype, sbits);

  void startup_z_update_Vtype_vill(void);

  void finish_z_update_Vtype_vill(void);

  uint64_t z_get_Vtype_vlmul(struct zVtype);

  struct zVtype z_update_Vtype_vlmul(struct zVtype, uint64_t);

  void startup_z_update_Vtype_vlmul(void);

  void finish_z_update_Vtype_vlmul(void);

  uint64_t z_get_Vtype_vma(struct zVtype);

  struct zVtype z_update_Vtype_vma(struct zVtype, uint64_t);

  void startup_z_update_Vtype_vma(void);

  void finish_z_update_Vtype_vma(void);

  uint64_t z_get_Vtype_vsew(struct zVtype);

  struct zVtype z_update_Vtype_vsew(struct zVtype, uint64_t);

  void startup_z_update_Vtype_vsew(void);

  void finish_z_update_Vtype_vsew(void);

  uint64_t z_get_Vtype_vta(struct zVtype);

  struct zVtype z_update_Vtype_vta(struct zVtype, uint64_t);

  void startup_z_update_Vtype_vta(void);

  void finish_z_update_Vtype_vta(void);

  bool zis_invalid_sew_pow(uint64_t);

  void startup_zis_invalid_sew_pow(void);

  void finish_zis_invalid_sew_pow(void);

  bool zis_invalid_lmul_pow(uint64_t);

  int64_t zget_sew_pow(unit);

  void startup_zget_sew_pow(void);

  void finish_zget_sew_pow(void);

  int64_t zget_sew(unit);

  void startup_zget_sew(void);

  void finish_zget_sew(void);

  int64_t zget_sew_bytes(unit);

  void startup_zget_sew_bytes(void);

  void finish_zget_sew_bytes(void);

  int64_t zget_lmul_pow(unit);

  void startup_zget_lmul_pow(void);

  void finish_zget_lmul_pow(void);

  enum zagtype zdecode_agtype(uint64_t);

  enum zagtype zget_vtype_vma(unit);

  enum zagtype zget_vtype_vta(unit);

  struct zVcsr zundefined_Vcsr(unit);

  void startup_zundefined_Vcsr(void);

  void finish_zundefined_Vcsr(void);

  struct zVcsr zMk_Vcsr(uint64_t);

  void startup_zMk_Vcsr(void);

  void finish_zMk_Vcsr(void);

  uint64_t z_get_Vcsr_vxrm(struct zVcsr);

  uint64_t z_get_Vcsr_vxsat(struct zVcsr);

  unit zset_vstart(uint64_t);

  void startup_zset_vstart(void);

  void finish_zset_vstart(void);

  unit zwrite_vcsr(uint64_t, uint64_t);

  void startup_zwrite_vcsr(void);

  void finish_zwrite_vcsr(void);

  unit zwrite_vxsat(uint64_t);

  void startup_zwrite_vxsat(void);

  void finish_zwrite_vxsat(void);

  void create_letbind_180(void);
  void kill_letbind_180(void);


  int64_t zget_num_elem(int64_t, int64_t);

  void startup_zget_num_elem(void);

  void finish_zget_num_elem(void);

  sbits zread_single_element(int64_t, sail_int, uint64_t);

  void startup_zread_single_element(void);

  void finish_zread_single_element(void);

  void zread_vreg(zz5vecz8z5sbv64z9 *rop, sail_int, int64_t, sail_int, uint64_t);

  void startup_zread_vreg(void);

  void finish_zread_vreg(void);

  unit zwrite_single_element(int64_t, sail_int, uint64_t, sbits);

  void startup_zwrite_single_element(void);

  void finish_zwrite_single_element(void);

  unit zwrite_vreg(sail_int, int64_t, int64_t, uint64_t, zz5vecz8z5sbv64z9);

  void startup_zwrite_vreg(void);

  void finish_zwrite_vreg(void);

  void zread_vmask(lbits *rop, int64_t, uint64_t, uint64_t);

  void startup_zread_vmask(void);

  void finish_zread_vmask(void);

  void zread_vmask_carry(lbits *rop, int64_t, uint64_t, uint64_t);

  void startup_zread_vmask_carry(void);

  void finish_zread_vmask_carry(void);

  unit zwrite_vmask(sail_int, uint64_t, lbits);

  void startup_zwrite_vmask(void);

  void finish_zwrite_vmask(void);

  uint64_t zxt2(uint64_t);

  void startup_zxt2(void);

  void finish_zxt2(void);

  uint64_t zxt3(uint64_t);

  uint64_t zgfmul(uint64_t, uint64_t);

  uint64_t zaes_mixcolumn_byte_fwd(uint64_t);

  uint64_t zaes_mixcolumn_byte_inv(uint64_t);

  uint64_t zaes_mixcolumn_fwd(uint64_t);

  uint64_t zaes_mixcolumn_inv(uint64_t);

  uint64_t zaes_decode_rcon(uint64_t);

  void startup_zaes_decode_rcon(void);

  void finish_zaes_decode_rcon(void);

  void create_letbind_181(void);
  void kill_letbind_181(void);


  void create_letbind_182(void);
  void kill_letbind_182(void);


  void create_letbind_183(void);
  void kill_letbind_183(void);


  uint64_t zsbox_lookup(uint64_t, zz5vecz8z5bv8z9);

  void startup_zsbox_lookup(void);

  void finish_zsbox_lookup(void);

  uint64_t zaes_sbox_fwd(uint64_t);

  uint64_t zaes_sbox_inv(uint64_t);

  uint64_t zaes_subword_fwd(uint64_t);

  uint64_t zaes_subword_inv(uint64_t);

  uint64_t zsm4_sbox(uint64_t);

  uint64_t zaes_get_column(lbits, int64_t);

  void startup_zaes_get_column(void);

  void finish_zaes_get_column(void);

  uint64_t zaes_apply_fwd_sbox_to_each_byte(uint64_t);

  uint64_t zaes_apply_inv_sbox_to_each_byte(uint64_t);

  uint64_t zgetbyte(uint64_t, int64_t);

  void startup_zgetbyte(void);

  void finish_zgetbyte(void);

  uint64_t zaes_rv64_shiftrows_fwd(uint64_t, uint64_t);

  uint64_t zaes_rv64_shiftrows_inv(uint64_t, uint64_t);

  void zaes_shift_rows_fwd(lbits *rop, lbits);

  void startup_zaes_shift_rows_fwd(void);

  void finish_zaes_shift_rows_fwd(void);

  void zaes_shift_rows_inv(lbits *rop, lbits);

  void startup_zaes_shift_rows_inv(void);

  void finish_zaes_shift_rows_inv(void);

  void zaes_subbytes_fwd(lbits *rop, lbits);

  void startup_zaes_subbytes_fwd(void);

  void finish_zaes_subbytes_fwd(void);

  void zaes_subbytes_inv(lbits *rop, lbits);

  void startup_zaes_subbytes_inv(void);

  void finish_zaes_subbytes_inv(void);

  void zaes_mixcolumns_fwd(lbits *rop, lbits);

  void startup_zaes_mixcolumns_fwd(void);

  void finish_zaes_mixcolumns_fwd(void);

  void zaes_mixcolumns_inv(lbits *rop, lbits);

  void startup_zaes_mixcolumns_inv(void);

  void finish_zaes_mixcolumns_inv(void);

  bool zzzvk_valid_reg_overlap(uint64_t, uint64_t, sail_int);

  void startup_zzzvk_valid_reg_overlap(void);

  void finish_zzzvk_valid_reg_overlap(void);

  void zzzvk_vs_emul_pow(sail_int *rop, unit);

  void startup_zzzvk_vs_emul_pow(void);

  void finish_zzzvk_vs_emul_pow(void);

  bool zzzvk_valid_vs_reg_overlap(uint64_t, uint64_t, sail_int);

  void startup_zzzvk_valid_vs_reg_overlap(void);

  void finish_zzzvk_valid_vs_reg_overlap(void);

  void zzzvk_read_eg32x4(zz5vecz8z5bv32z9 *rop, uint64_t, sail_int);

  void startup_zzzvk_read_eg32x4(void);

  void finish_zzzvk_read_eg32x4(void);

  bool zzzvk_check_encdec(sail_int, sail_int);

  void startup_zzzvk_check_encdec(void);

  void finish_zzzvk_check_encdec(void);

  bool zzzvknhab_check_encdec(uint64_t, uint64_t, uint64_t);

  void startup_zzzvknhab_check_encdec(void);

  void finish_zzzvknhab_check_encdec(void);

  sbits zzzvk_sig0(sbits, int64_t);

  void startup_zzzvk_sig0(void);

  void finish_zzzvk_sig0(void);

  sbits zzzvk_sig1(sbits, int64_t);

  void startup_zzzvk_sig1(void);

  void finish_zzzvk_sig1(void);

  sbits zzzvk_sum0(sbits, int64_t);

  void startup_zzzvk_sum0(void);

  void finish_zzzvk_sum0(void);

  sbits zzzvk_sum1(sbits, int64_t);

  void startup_zzzvk_sum1(void);

  void finish_zzzvk_sum1(void);

  void zzzvk_ch(lbits *rop, lbits, lbits, lbits);

  void startup_zzzvk_ch(void);

  void finish_zzzvk_ch(void);

  void zzzvk_maj(lbits *rop, lbits, lbits, lbits);

  void startup_zzzvk_maj(void);

  void finish_zzzvk_maj(void);

  uint64_t zzzvk_round_key(uint64_t, uint64_t);

  void startup_zzzvk_round_key(void);

  void finish_zzzvk_round_key(void);

  uint64_t zzzvk_sm4_round(uint64_t, uint64_t);

  void startup_zzzvk_sm4_round(void);

  void finish_zzzvk_sm4_round(void);

  void create_letbind_184(void);
  void kill_letbind_184(void);


  uint64_t zzzvksed_box_lookup(uint64_t, zz5vecz8z5bv32z9);

  void startup_zzzvksed_box_lookup(void);

  void finish_zzzvksed_box_lookup(void);

  uint64_t zzzvk_sm4_sbox(uint64_t);

  uint64_t zzzvk_sm4_subword(uint64_t);

  uint64_t zzzvk_p0(uint64_t);

  void startup_zzzvk_p0(void);

  void finish_zzzvk_p0(void);

  uint64_t zzzvk_p1(uint64_t);

  void startup_zzzvk_p1(void);

  void finish_zzzvk_p1(void);

  uint64_t zzzvk_sh_w(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

  void startup_zzzvk_sh_w(void);

  void finish_zzzvk_sh_w(void);

  uint64_t zzzvk_ff1(uint64_t, uint64_t, uint64_t);

  uint64_t zzzvk_ff2(uint64_t, uint64_t, uint64_t);

  uint64_t zzzvk_ff_j(uint64_t, uint64_t, uint64_t, sail_int);

  void startup_zzzvk_ff_j(void);

  void finish_zzzvk_ff_j(void);

  uint64_t zzzvk_gg1(uint64_t, uint64_t, uint64_t);

  uint64_t zzzvk_gg2(uint64_t, uint64_t, uint64_t);

  uint64_t zzzvk_gg_j(uint64_t, uint64_t, uint64_t, sail_int);

  void startup_zzzvk_gg_j(void);

  void finish_zzzvk_gg_j(void);

  uint64_t zzzvk_t_j(sail_int);

  void startup_zzzvk_t_j(void);

  void finish_zzzvk_t_j(void);

  void zzzvk_sm3_round(zz5vecz8z5bv32z9 *rop, zz5vecz8z5bv32z9, uint64_t, uint64_t, sail_int);

  void startup_zzzvk_sm3_round(void);

  void finish_zzzvk_sm3_round(void);

  struct zCountSmcntrpmf zundefined_CountSmcntrpmf(unit);

  void startup_zundefined_CountSmcntrpmf(void);

  void finish_zundefined_CountSmcntrpmf(void);

  struct zCountSmcntrpmf zMk_CountSmcntrpmf(uint64_t);

  void startup_zMk_CountSmcntrpmf(void);

  void finish_zMk_CountSmcntrpmf(void);

  uint64_t z_get_CountSmcntrpmf_MINH(struct zCountSmcntrpmf);

  struct zCountSmcntrpmf z_update_CountSmcntrpmf_MINH(struct zCountSmcntrpmf, uint64_t);

  void startup_z_update_CountSmcntrpmf_MINH(void);

  void finish_z_update_CountSmcntrpmf_MINH(void);

  uint64_t z_get_CountSmcntrpmf_SINH(struct zCountSmcntrpmf);

  struct zCountSmcntrpmf z_update_CountSmcntrpmf_SINH(struct zCountSmcntrpmf, uint64_t);

  void startup_z_update_CountSmcntrpmf_SINH(void);

  void finish_z_update_CountSmcntrpmf_SINH(void);

  uint64_t z_get_CountSmcntrpmf_UINH(struct zCountSmcntrpmf);

  struct zCountSmcntrpmf z_update_CountSmcntrpmf_UINH(struct zCountSmcntrpmf, uint64_t);

  void startup_z_update_CountSmcntrpmf_UINH(void);

  void finish_z_update_CountSmcntrpmf_UINH(void);

  uint64_t z_get_CountSmcntrpmf_VSINH(struct zCountSmcntrpmf);

  struct zCountSmcntrpmf z_update_CountSmcntrpmf_VSINH(struct zCountSmcntrpmf, uint64_t);

  void startup_z_update_CountSmcntrpmf_VSINH(void);

  void finish_z_update_CountSmcntrpmf_VSINH(void);

  uint64_t z_get_CountSmcntrpmf_VUINH(struct zCountSmcntrpmf);

  struct zCountSmcntrpmf z_update_CountSmcntrpmf_VUINH(struct zCountSmcntrpmf, uint64_t);

  void startup_z_update_CountSmcntrpmf_VUINH(void);

  void finish_z_update_CountSmcntrpmf_VUINH(void);

  struct zCountSmcntrpmf zlegalizze_smcntrpmf(struct zCountSmcntrpmf, uint64_t);

  void startup_zlegalizze_smcntrpmf(void);

  void finish_zlegalizze_smcntrpmf(void);

  uint64_t zcounter_priv_filter_bit(struct zCountSmcntrpmf, enum zPrivilege);

  sbits zmake_etrigger_flag(struct zExceptionType);

  void startup_zmake_etrigger_flag(void);

  void finish_zmake_etrigger_flag(void);

  sbits zmake_itrigger_flag(enum zInterruptType);

  void startup_zmake_itrigger_flag(void);

  void finish_zmake_itrigger_flag(void);

  bool zis_valid_napot_compare_value(sbits);

  void startup_zis_valid_napot_compare_value(void);

  void finish_zis_valid_napot_compare_value(void);

  sbits zlegalizze_napot_compare_value(sbits);

  void startup_zlegalizze_napot_compare_value(void);

  void finish_zlegalizze_napot_compare_value(void);

  enum zTrig_Type ztrig_type_bits_forwards(uint64_t);

  bool ztrig_type_bits_forwards_matches(uint64_t);

  enum zTrig_Type ztrig_type_bits_forwards_infallible(uint64_t);

  void ztrig_type_name_forwards(sail_string *rop, enum zTrig_Type);

  void ztrig_type_name_forwards_infallible(sail_string *rop, enum zTrig_Type);

  bool zis_supported_trigger_type(uint64_t);

  uint64_t zsupported_triggers_info(unit);

  enum zTrig_Action ztrig_action_forwards(uint64_t);

  uint64_t ztrig_action_backwards(enum zTrig_Action);

  bool ztrig_action_forwards_matches(uint64_t);

  enum zTrig_Action ztrig_action_forwards_infallible(uint64_t);

  uint64_t ztrig_action_backwards_infallible(enum zTrig_Action);

  void ztrigger_action_name_forwards(sail_string *rop, enum zTrig_Action);

  void ztrigger_action_name_forwards_infallible(sail_string *rop, enum zTrig_Action);

  bool zis_supported_action(uint64_t);

  enum zHit zhit_bits_forwards(uint64_t);

  uint64_t zhit_bits_backwards(enum zHit);

  enum zHit zhit_bits_forwards_infallible(uint64_t);

  uint64_t zhit_bits_backwards_infallible(enum zHit);

  void zhit_name_forwards(sail_string *rop, enum zHit);

  void zhit_name_forwards_infallible(sail_string *rop, enum zHit);

  enum zCompare_Selection zcompare_select_bits_forwards(uint64_t);

  uint64_t zcompare_select_bits_backwards(enum zCompare_Selection);

  enum zCompare_Selection zcompare_select_bits_forwards_infallible(uint64_t);

  uint64_t zcompare_select_bits_backwards_infallible(enum zCompare_Selection);

  int64_t ztrig_match_sizze_forwards(uint64_t);

  uint64_t ztrig_match_sizze_backwards(int64_t);

  bool ztrig_match_sizze_forwards_matches(uint64_t);

  int64_t ztrig_match_sizze_forwards_infallible(uint64_t);

  uint64_t ztrig_match_sizze_backwards_infallible(int64_t);

  bool zis_supported_match_sizze(uint64_t);

  enum zTrig_Match ztrig_match_val_forwards(uint64_t);

  uint64_t ztrig_match_val_backwards(enum zTrig_Match);

  bool ztrig_match_val_forwards_matches(uint64_t);

  enum zTrig_Match ztrig_match_val_forwards_infallible(uint64_t);

  uint64_t ztrig_match_val_backwards_infallible(enum zTrig_Match);

  bool zis_supported_match_val(uint64_t);

  struct zTrigger_Extra_RV32 zMk_Trigger_Extra_RV32(uint64_t);

  void startup_zMk_Trigger_Extra_RV32(void);

  void finish_zMk_Trigger_Extra_RV32(void);

  uint64_t z_get_Trigger_Extra_RV32_mhselect(struct zTrigger_Extra_RV32);

  struct zTrigger_Extra_RV32 z_update_Trigger_Extra_RV32_mhselect(struct zTrigger_Extra_RV32, uint64_t);

  void startup_z_update_Trigger_Extra_RV32_mhselect(void);

  void finish_z_update_Trigger_Extra_RV32_mhselect(void);

  uint64_t z_get_Trigger_Extra_RV32_mhvalue(struct zTrigger_Extra_RV32);

  struct zTrigger_Extra_RV32 z_update_Trigger_Extra_RV32_mhvalue(struct zTrigger_Extra_RV32, uint64_t);

  void startup_z_update_Trigger_Extra_RV32_mhvalue(void);

  void finish_z_update_Trigger_Extra_RV32_mhvalue(void);

  uint64_t z_get_Trigger_Extra_RV32_sbytemask(struct zTrigger_Extra_RV32);

  struct zTrigger_Extra_RV32 z_update_Trigger_Extra_RV32_sbytemask(struct zTrigger_Extra_RV32, uint64_t);

  void startup_z_update_Trigger_Extra_RV32_sbytemask(void);

  void finish_z_update_Trigger_Extra_RV32_sbytemask(void);

  uint64_t z_get_Trigger_Extra_RV32_sselect(struct zTrigger_Extra_RV32);

  struct zTrigger_Extra_RV32 z_update_Trigger_Extra_RV32_sselect(struct zTrigger_Extra_RV32, uint64_t);

  void startup_z_update_Trigger_Extra_RV32_sselect(void);

  void finish_z_update_Trigger_Extra_RV32_sselect(void);

  uint64_t z_get_Trigger_Extra_RV32_svalue(struct zTrigger_Extra_RV32);

  struct zTrigger_Extra_RV32 z_update_Trigger_Extra_RV32_svalue(struct zTrigger_Extra_RV32, uint64_t);

  void startup_z_update_Trigger_Extra_RV32_svalue(void);

  void finish_z_update_Trigger_Extra_RV32_svalue(void);

  struct zTrigger_Extra_RV64 zMk_Trigger_Extra_RV64(uint64_t);

  void startup_zMk_Trigger_Extra_RV64(void);

  void finish_zMk_Trigger_Extra_RV64(void);

  uint64_t z_get_Trigger_Extra_RV64_mhselect(struct zTrigger_Extra_RV64);

  struct zTrigger_Extra_RV64 z_update_Trigger_Extra_RV64_mhselect(struct zTrigger_Extra_RV64, uint64_t);

  void startup_z_update_Trigger_Extra_RV64_mhselect(void);

  void finish_z_update_Trigger_Extra_RV64_mhselect(void);

  uint64_t z_get_Trigger_Extra_RV64_mhvalue(struct zTrigger_Extra_RV64);

  struct zTrigger_Extra_RV64 z_update_Trigger_Extra_RV64_mhvalue(struct zTrigger_Extra_RV64, uint64_t);

  void startup_z_update_Trigger_Extra_RV64_mhvalue(void);

  void finish_z_update_Trigger_Extra_RV64_mhvalue(void);

  uint64_t z_get_Trigger_Extra_RV64_sbytemask(struct zTrigger_Extra_RV64);

  struct zTrigger_Extra_RV64 z_update_Trigger_Extra_RV64_sbytemask(struct zTrigger_Extra_RV64, uint64_t);

  void startup_z_update_Trigger_Extra_RV64_sbytemask(void);

  void finish_z_update_Trigger_Extra_RV64_sbytemask(void);

  uint64_t z_get_Trigger_Extra_RV64_sselect(struct zTrigger_Extra_RV64);

  struct zTrigger_Extra_RV64 z_update_Trigger_Extra_RV64_sselect(struct zTrigger_Extra_RV64, uint64_t);

  void startup_z_update_Trigger_Extra_RV64_sselect(void);

  void finish_z_update_Trigger_Extra_RV64_sselect(void);

  uint64_t z_get_Trigger_Extra_RV64_svalue(struct zTrigger_Extra_RV64);

  struct zTrigger_Extra_RV64 z_update_Trigger_Extra_RV64_svalue(struct zTrigger_Extra_RV64, uint64_t);

  void startup_z_update_Trigger_Extra_RV64_svalue(void);

  void finish_z_update_Trigger_Extra_RV64_svalue(void);

  void create_letbind_185(void);
  void kill_letbind_185(void);


  void create_letbind_186(void);
  void kill_letbind_186(void);


  void create_letbind_187(void);
  void kill_letbind_187(void);


  void create_letbind_188(void);
  void kill_letbind_188(void);


  void create_letbind_189(void);
  void kill_letbind_189(void);


  void create_letbind_190(void);
  void kill_letbind_190(void);


  sbits zTExtra_to_bits(struct zTExtra);

  void startup_zTExtra_to_bits(void);

  void finish_zTExtra_to_bits(void);

  uint64_t zlegalizze_mhselect(uint64_t);

  uint64_t zlegalizze_sselect(uint64_t);

  struct zTExtra zmake_textra(sbits);

  void startup_zmake_textra(void);

  void finish_zmake_textra(void);

  struct zTDisabled_bits zMk_TDisabled_bits(sbits);

  void startup_zMk_TDisabled_bits(void);

  void finish_zMk_TDisabled_bits(void);

  struct zTDisabled_bits z_update_TDisabled_bits_data(struct zTDisabled_bits, sbits);

  void startup_z_update_TDisabled_bits_data(void);

  void finish_z_update_TDisabled_bits_data(void);

  struct zTDisabled_bits z_update_TDisabled_bits_dmode(struct zTDisabled_bits, sbits);

  void startup_z_update_TDisabled_bits_dmode(void);

  void finish_z_update_TDisabled_bits_dmode(void);

  struct zTDisabled_bits z_update_TDisabled_bits_trig_type(struct zTDisabled_bits, sbits);

  void startup_z_update_TDisabled_bits_trig_type(void);

  void finish_z_update_TDisabled_bits_trig_type(void);

  struct zTDisabled_bits zTDisabled_to_bits(struct zTDisabled);

  void startup_zTDisabled_to_bits(void);

  void finish_zTDisabled_to_bits(void);

  struct zMControl6_bits zMk_MControl6_bits(sbits);

  void startup_zMk_MControl6_bits(void);

  void finish_zMk_MControl6_bits(void);

  uint64_t z_get_MControl6_bits_action(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_action(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_action(void);

  void finish_z_update_MControl6_bits_action(void);

  uint64_t z_get_MControl6_bits_chain(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_chain(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_chain(void);

  void finish_z_update_MControl6_bits_chain(void);

  struct zMControl6_bits z_update_MControl6_bits_dmode(struct zMControl6_bits, sbits);

  void startup_z_update_MControl6_bits_dmode(void);

  void finish_z_update_MControl6_bits_dmode(void);

  uint64_t z_get_MControl6_bits_execute(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_execute(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_execute(void);

  void finish_z_update_MControl6_bits_execute(void);

  uint64_t z_get_MControl6_bits_hit0(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_hit0(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_hit0(void);

  void finish_z_update_MControl6_bits_hit0(void);

  uint64_t z_get_MControl6_bits_hit1(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_hit1(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_hit1(void);

  void finish_z_update_MControl6_bits_hit1(void);

  uint64_t z_get_MControl6_bits_load(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_load(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_load(void);

  void finish_z_update_MControl6_bits_load(void);

  uint64_t z_get_MControl6_bits_m(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_m(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_m(void);

  void finish_z_update_MControl6_bits_m(void);

  uint64_t z_get_MControl6_bits_s(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_s(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_s(void);

  void finish_z_update_MControl6_bits_s(void);

  uint64_t z_get_MControl6_bits_select(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_select(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_select(void);

  void finish_z_update_MControl6_bits_select(void);

  uint64_t z_get_MControl6_bits_sizze(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_sizze(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_sizze(void);

  void finish_z_update_MControl6_bits_sizze(void);

  uint64_t z_get_MControl6_bits_store(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_store(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_store(void);

  void finish_z_update_MControl6_bits_store(void);

  uint64_t z_get_MControl6_bits_t_match(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_t_match(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_t_match(void);

  void finish_z_update_MControl6_bits_t_match(void);

  struct zMControl6_bits z_update_MControl6_bits_trig_type(struct zMControl6_bits, sbits);

  void startup_z_update_MControl6_bits_trig_type(void);

  void finish_z_update_MControl6_bits_trig_type(void);

  uint64_t z_get_MControl6_bits_u(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_u(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_u(void);

  void finish_z_update_MControl6_bits_u(void);

  struct zMControl6_bits z_update_MControl6_bits_uncertain(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_uncertain(void);

  void finish_z_update_MControl6_bits_uncertain(void);

  struct zMControl6_bits z_update_MControl6_bits_uncertainen(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_uncertainen(void);

  void finish_z_update_MControl6_bits_uncertainen(void);

  uint64_t z_get_MControl6_bits_vs(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_vs(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_vs(void);

  void finish_z_update_MControl6_bits_vs(void);

  uint64_t z_get_MControl6_bits_vu(struct zMControl6_bits);

  struct zMControl6_bits z_update_MControl6_bits_vu(struct zMControl6_bits, uint64_t);

  void startup_z_update_MControl6_bits_vu(void);

  void finish_z_update_MControl6_bits_vu(void);

  struct zMControl6_bits zMControl6_to_bits(struct zMControl6);

  void startup_zMControl6_to_bits(void);

  void finish_zMControl6_to_bits(void);

  void create_letbind_191(void);
  void kill_letbind_191(void);


  void create_letbind_192(void);
  void kill_letbind_192(void);


  struct zICount_bits zMk_ICount_bits(sbits);

  void startup_zMk_ICount_bits(void);

  void finish_zMk_ICount_bits(void);

  uint64_t z_get_ICount_bits_action(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_action(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_action(void);

  void finish_z_update_ICount_bits_action(void);

  uint64_t z_get_ICount_bits_count(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_count(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_count(void);

  void finish_z_update_ICount_bits_count(void);

  struct zICount_bits z_update_ICount_bits_dmode(struct zICount_bits, sbits);

  void startup_z_update_ICount_bits_dmode(void);

  void finish_z_update_ICount_bits_dmode(void);

  uint64_t z_get_ICount_bits_hit(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_hit(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_hit(void);

  void finish_z_update_ICount_bits_hit(void);

  uint64_t z_get_ICount_bits_m(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_m(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_m(void);

  void finish_z_update_ICount_bits_m(void);

  uint64_t z_get_ICount_bits_pending(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_pending(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_pending(void);

  void finish_z_update_ICount_bits_pending(void);

  uint64_t z_get_ICount_bits_s(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_s(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_s(void);

  void finish_z_update_ICount_bits_s(void);

  struct zICount_bits z_update_ICount_bits_trig_type(struct zICount_bits, sbits);

  void startup_z_update_ICount_bits_trig_type(void);

  void finish_z_update_ICount_bits_trig_type(void);

  uint64_t z_get_ICount_bits_u(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_u(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_u(void);

  void finish_z_update_ICount_bits_u(void);

  uint64_t z_get_ICount_bits_vs(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_vs(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_vs(void);

  void finish_z_update_ICount_bits_vs(void);

  uint64_t z_get_ICount_bits_vu(struct zICount_bits);

  struct zICount_bits z_update_ICount_bits_vu(struct zICount_bits, uint64_t);

  void startup_z_update_ICount_bits_vu(void);

  void finish_z_update_ICount_bits_vu(void);

  struct zICount_bits zICount_to_bits(struct zICount);

  void startup_zICount_to_bits(void);

  void finish_zICount_to_bits(void);

  struct zIETrigger_bits zMk_IETrigger_bits(sbits);

  void startup_zMk_IETrigger_bits(void);

  void finish_zMk_IETrigger_bits(void);

  uint64_t z_get_IETrigger_bits_action(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_action(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_action(void);

  void finish_z_update_IETrigger_bits_action(void);

  struct zIETrigger_bits z_update_IETrigger_bits_dmode(struct zIETrigger_bits, sbits);

  void startup_z_update_IETrigger_bits_dmode(void);

  void finish_z_update_IETrigger_bits_dmode(void);

  sbits z_get_IETrigger_bits_hit(struct zIETrigger_bits);

  void startup_z_get_IETrigger_bits_hit(void);

  void finish_z_get_IETrigger_bits_hit(void);

  struct zIETrigger_bits z_update_IETrigger_bits_hit(struct zIETrigger_bits, sbits);

  void startup_z_update_IETrigger_bits_hit(void);

  void finish_z_update_IETrigger_bits_hit(void);

  uint64_t z_get_IETrigger_bits_m(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_m(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_m(void);

  void finish_z_update_IETrigger_bits_m(void);

  uint64_t z_get_IETrigger_bits_nmi(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_nmi(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_nmi(void);

  void finish_z_update_IETrigger_bits_nmi(void);

  uint64_t z_get_IETrigger_bits_s(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_s(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_s(void);

  void finish_z_update_IETrigger_bits_s(void);

  struct zIETrigger_bits z_update_IETrigger_bits_trig_type(struct zIETrigger_bits, sbits);

  void startup_z_update_IETrigger_bits_trig_type(void);

  void finish_z_update_IETrigger_bits_trig_type(void);

  uint64_t z_get_IETrigger_bits_u(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_u(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_u(void);

  void finish_z_update_IETrigger_bits_u(void);

  uint64_t z_get_IETrigger_bits_vs(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_vs(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_vs(void);

  void finish_z_update_IETrigger_bits_vs(void);

  uint64_t z_get_IETrigger_bits_vu(struct zIETrigger_bits);

  struct zIETrigger_bits z_update_IETrigger_bits_vu(struct zIETrigger_bits, uint64_t);

  void startup_z_update_IETrigger_bits_vu(void);

  void finish_z_update_IETrigger_bits_vu(void);

  struct zIETrigger_bits zITrigger_to_bits(struct zITrigger);

  void startup_zITrigger_to_bits(void);

  void finish_zITrigger_to_bits(void);

  struct zIETrigger_bits zETrigger_to_bits(struct zETrigger);

  void startup_zETrigger_to_bits(void);

  void finish_zETrigger_to_bits(void);

  void ztrigger_name(sail_string *rop, struct zTrigger);

  void startup_ztrigger_name(void);

  void finish_ztrigger_name(void);

  void create_letbind_193(void);
  void kill_letbind_193(void);


  sbits ztdata1_of_trigger(struct zTrigger);

  void startup_ztdata1_of_trigger(void);

  void finish_ztdata1_of_trigger(void);

  sbits ztdata2_of_trigger(struct zTrigger);

  void startup_ztdata2_of_trigger(void);

  void finish_ztdata2_of_trigger(void);

  struct zTExtra ztextra_of_trigger(struct zTrigger);

  void startup_ztextra_of_trigger(void);

  void finish_ztextra_of_trigger(void);

  sbits ztdata3_of_trigger(struct zTrigger);

  void startup_ztdata3_of_trigger(void);

  void finish_ztdata3_of_trigger(void);

  bool ztrigger_is_in_chain(struct zTrigger);

  void startup_ztrigger_is_in_chain(void);

  void finish_ztrigger_is_in_chain(void);

  uint64_t zinfo_of_trigger(struct zTrigger);

  struct zTInfo zMk_TInfo(sbits);

  void startup_zMk_TInfo(void);

  void finish_zMk_TInfo(void);

  struct zTInfo z_update_TInfo_info(struct zTInfo, uint64_t);

  void startup_z_update_TInfo_info(void);

  void finish_z_update_TInfo_info(void);

  struct zTInfo z_update_TInfo_version(struct zTInfo, uint64_t);

  void startup_z_update_TInfo_version(void);

  void finish_z_update_TInfo_version(void);

  struct zTInfo ztinfo_of_trigger(struct zTrigger);

  void startup_ztinfo_of_trigger(void);

  void finish_ztinfo_of_trigger(void);

  struct zTData1 zMk_TData1(sbits);

  void startup_zMk_TData1(void);

  void finish_zMk_TData1(void);

  sbits z_get_TData1_data(struct zTData1);

  void startup_z_get_TData1_data(void);

  void finish_z_get_TData1_data(void);

  sbits z_get_TData1_trig_type(struct zTData1);

  void startup_z_get_TData1_trig_type(void);

  void finish_z_get_TData1_trig_type(void);

  struct zTControl zMk_TControl(sbits);

  void startup_zMk_TControl(void);

  void finish_zMk_TControl(void);

  uint64_t z_get_TControl_mpte(struct zTControl);

  struct zTControl z_update_TControl_mpte(struct zTControl, uint64_t);

  void startup_z_update_TControl_mpte(void);

  void finish_z_update_TControl_mpte(void);

  uint64_t z_get_TControl_mte(struct zTControl);

  struct zTControl z_update_TControl_mte(struct zTControl, uint64_t);

  void startup_z_update_TControl_mte(void);

  void finish_z_update_TControl_mte(void);

  struct zSContext zMk_SContext(sbits);

  void startup_zMk_SContext(void);

  void finish_zMk_SContext(void);

  uint64_t z_get_SContext_data(struct zSContext);

  struct zSContext z_update_SContext_data(struct zSContext, uint64_t);

  void startup_z_update_SContext_data(void);

  void finish_z_update_SContext_data(void);

  struct zMContext zMk_MContext(sbits);

  void startup_zMk_MContext(void);

  void finish_zMk_MContext(void);

  uint64_t z_get_MContext_hcontext(struct zMContext);

  struct zMContext z_update_MContext_hcontext(struct zMContext, uint64_t);

  void startup_z_update_MContext_hcontext(void);

  void finish_z_update_MContext_hcontext(void);

  void zmake_disabled_trigger(struct zTrigger *rop, struct zTData1, sbits, struct zTExtra);

  void startup_zmake_disabled_trigger(void);

  void finish_zmake_disabled_trigger(void);

  void create_letbind_194(void);
  void kill_letbind_194(void);


  void create_letbind_195(void);
  void kill_letbind_195(void);


  bool zallow_chain_at(int64_t);

  void zmake_trigger(struct zTrigger *rop, int64_t, struct zTData1, sbits, struct zTExtra);

  void startup_zmake_trigger(void);

  void finish_zmake_trigger(void);

  void ztrigger_write_tdata1(struct zTrigger *rop, int64_t, struct zTrigger, sbits);

  void startup_ztrigger_write_tdata1(void);

  void finish_ztrigger_write_tdata1(void);

  void ztrigger_write_tdata2(struct zTrigger *rop, int64_t, struct zTrigger, sbits);

  void startup_ztrigger_write_tdata2(void);

  void finish_ztrigger_write_tdata2(void);

  void ztrigger_write_tdata3(struct zTrigger *rop, int64_t, struct zTrigger, sbits);

  void startup_ztrigger_write_tdata3(void);

  void finish_ztrigger_write_tdata3(void);

  unit ztcontrol_trap_into_mmode(unit);

  void startup_ztcontrol_trap_into_mmode(void);

  void finish_ztcontrol_trap_into_mmode(void);

  unit ztcontrol_mret_from_mmode(unit);

  void startup_zallow_chain_at(void);

  void finish_zallow_chain_at(void);

  bool zprevent_reentrance(enum zTrig_Action, enum zPrivilege);

  bool zsselect_match(struct zTExtra, enum zPrivilege);

  void startup_zsselect_match(void);

  void finish_zsselect_match(void);

  bool zmhselect_match(struct zTExtra);

  void startup_zmhselect_match(void);

  void finish_zmhselect_match(void);

  bool ztextra_match(struct zTExtra, enum zPrivilege);

  bool zicount_match(struct zICount, enum zPrivilege, bool);

  void startup_zicount_match(void);

  void finish_zicount_match(void);

  unit zmatch_icount_triggers(enum zPrivilege, bool);

  void startup_zmatch_icount_triggers(void);

  void finish_zmatch_icount_triggers(void);

  bool zitrigger_match(struct zITrigger, enum zInterruptType, enum zPrivilege, enum zPrivilege);

  void startup_zitrigger_match(void);

  void finish_zitrigger_match(void);

  unit zmatch_itrigger_triggers(enum zInterruptType, enum zPrivilege, enum zPrivilege);

  void startup_zmatch_itrigger_triggers(void);

  void finish_zmatch_itrigger_triggers(void);

  bool zetrigger_match(struct zETrigger, struct zExceptionType, enum zPrivilege, enum zPrivilege);

  void startup_zetrigger_match(void);

  void finish_zetrigger_match(void);

  unit zmatch_etrigger_triggers(struct zExceptionType, enum zPrivilege, enum zPrivilege);

  void startup_zmatch_etrigger_triggers(void);

  void finish_zmatch_etrigger_triggers(void);

  bool zcompare_access_sizze(int64_t, int64_t);

  void startup_zcompare_access_sizze(void);

  void finish_zcompare_access_sizze(void);

  bool zcompare_value_napot(sbits, sbits);

  void startup_zcompare_value_napot(void);

  void finish_zcompare_value_napot(void);

  bool zcompare_value_mask(sbits, sbits, enum zmask_type);

  void startup_zcompare_value_mask(void);

  void finish_zcompare_value_mask(void);

  bool zcompare_value_xlen(enum zTrig_Match, sbits, sbits);

  void startup_zcompare_value_xlen(void);

  void finish_zcompare_value_xlen(void);

  void create_letbind_196(void);
  void kill_letbind_196(void);


  void zcompare_address(struct zoptionzIbzK *rop, enum zTrig_Match, sbits, int64_t, sbits);

  void startup_zcompare_address(void);

  void finish_zcompare_address(void);

  bool zcompare_value(enum zTrig_Match, int64_t, lbits, int64_t, sbits);

  void startup_zcompare_value(void);

  void finish_zcompare_value(void);

  void zmatch_mcontrol6(struct zoptionzIbzK *rop, int64_t, struct zMControl6, enum zPrivilege, struct zMemoryTriggerPayload);

  void startup_zmatch_mcontrol6(void);

  void finish_zmatch_mcontrol6(void);

  void zmatch_memory_triggers(struct zoptionzIz8ETrig_Actionz5zCizCbz9zK *rop, enum zPrivilege, struct zMemoryTriggerPayload, enum zHit);

  void startup_zmatch_memory_triggers(void);

  void finish_zmatch_memory_triggers(void);

  void zmatch_memory_trigger_before(struct zoptionzIz8ETrig_Actionz5zCizCbz9zK *rop, enum zPrivilege, struct zMemoryTriggerPayload);

  unit zmatch_memory_trigger_after(enum zPrivilege, struct zMemoryTriggerPayload);

  unit zfire_pending_before_triggers(struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9);

  void startup_zfire_pending_before_triggers(void);

  void finish_zfire_pending_before_triggers(void);

  bool zfire_trigger_after(int64_t);

  void startup_zfire_trigger_after(void);

  void finish_zfire_trigger_after(void);

  void zfind_highest_priority_pending_trigger(struct zoptionzIz8ETrig_Actionz5zCizCbz9zK *rop, enum zPrivilege);

  void startup_zfind_highest_priority_pending_trigger(void);

  void finish_zfind_highest_priority_pending_trigger(void);

  enum zloop_chain_state znew_chain_state(struct zMControl6);

  unit zupdate_triggers(unit);

  void startup_zupdate_triggers(void);

  void finish_zupdate_triggers(void);

  void zntl_name_forwards(sail_string *rop, enum zntl_type);

  void zntl_name_forwards_infallible(sail_string *rop, enum zntl_type);

  uint64_t zencdec_ntl_forwards(enum zntl_type);

  enum zntl_type zencdec_ntl_backwards(uint64_t);

  bool zencdec_ntl_backwards_matches(uint64_t);

  uint64_t zencdec_ntl_forwards_infallible(enum zntl_type);

  enum zntl_type zencdec_ntl_backwards_infallible(uint64_t);

  bool zget_xLPE(enum zPrivilege);

  unit zupdate_elp_state(sbits);

  void startup_zupdate_elp_state(void);

  void finish_zupdate_elp_state(void);

  bool zis_landing_pad_expected(unit);

  unit zreset_elp(unit);

  unit zzzicfilp_preserve_elp_on_trap(enum zPrivilege);

  void startup_zzzicfilp_preserve_elp_on_trap(void);

  void finish_zzzicfilp_preserve_elp_on_trap(void);

  unit zzzicfilp_restore_elp_on_xret(enum zxRET_type, enum zPrivilege, enum zPrivilege);

  void startup_zzzicfilp_restore_elp_on_xret(void);

  void finish_zzzicfilp_restore_elp_on_xret(void);

  bool zstateen_allows_CSR_access(uint64_t, enum zPrivilege, enum zCSRAccessType);

  enum zPointerMaskingMode zget_pmm(enum zPrivilege);

  void startup_zget_pmm(void);

  void finish_zget_pmm(void);

  bool zis_pmm_applicable(struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  int64_t zpmlen_of_mode(enum zPointerMaskingMode);

  void startup_zpmlen_of_mode(void);

  void finish_zpmlen_of_mode(void);

  int64_t zget_pmlen(struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  int64_t zget_hlsv_pmlen(struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  sbits zpm_transform_VA(sbits, int64_t);

  void startup_zpm_transform_VA(void);

  void finish_zpm_transform_VA(void);

  sbits zpm_transform_PA(sbits, int64_t);

  void startup_zpm_transform_PA(void);

  void finish_zpm_transform_PA(void);

  struct zMinterrupts zsig_external_interrupts_pending(sbits);

  void startup_zsig_external_interrupts_pending(void);

  void finish_zsig_external_interrupts_pending(void);

  uint64_t zsig_machine_software_interrupt_pending(unit);

  uint64_t zsig_supervisor_software_interrupt_pending(unit);

  enum zPrivilege zeffectivePrivilege(struct zMemoryAccessTypezIEmem_payloadz5zK, struct zMstatus, enum zPrivilege);

  uint64_t zcsrAccess(uint64_t);

  uint64_t zcsrPriv(uint64_t);

  uint64_t zprivLevel_to_CSR_privbits(enum zPrivilege);

  bool zcheck_CSR_priv(uint64_t, enum zPrivilege);

  void startup_zcheck_CSR_priv(void);

  void finish_zcheck_CSR_priv(void);

  bool zcheck_CSR_access(uint64_t, enum zCSRAccessType);

  bool zcheck_CSR(uint64_t, enum zPrivilege, enum zCSRAccessType);

  void zcheck_CSR_result(struct zCSRCheckResult *rop, uint64_t, enum zPrivilege, enum zCSRAccessType);

  enum zPrivilege zexception_delegatee(struct zExceptionType, enum zPrivilege);

  void startup_zexception_delegatee(void);

  void finish_zexception_delegatee(void);

  void zfindPendingInterrupt(struct zoptionzIEInterruptTypez5zK *rop, sbits);

  void startup_zfindPendingInterrupt(void);

  void finish_zfindPendingInterrupt(void);

  void zgetPendingSet(struct zoptionzIz8bzCEPrivilegez5z9zK *rop, enum zPrivilege);

  void startup_zgetPendingSet(void);

  void finish_zgetPendingSet(void);

  bool zshouldWakeForInterrupt(unit);

  void startup_zshouldWakeForInterrupt(void);

  void finish_zshouldWakeForInterrupt(void);

  void zdispatchInterrupt(struct zoptionzIz8EInterruptTypez5zCEPrivilegez5z9zK *rop, enum zPrivilege);

  sbits ztval(struct zoptionzIbzK);

  void startup_ztval(void);

  void finish_ztval(void);

  unit ztrack_trap(enum zPrivilege, bool, uint64_t);

  void startup_ztrack_trap(void);

  void finish_ztrack_trap(void);

  void zxtval_exception_value(struct zoptionzIbzK *rop, struct zExceptionType, sbits);

  void startup_zxtval_exception_value(void);

  void finish_zxtval_exception_value(void);

  bool zxtval_is_gva(struct zExceptionContext);

  sbits ztrap_handler_inner(enum zPrivilege, struct zTrapCause, sbits);

  void startup_ztrap_handler_inner(void);

  void finish_ztrap_handler_inner(void);

  unit zmachine_trap_set_mdt(unit);

  void startup_zmachine_trap_set_mdt(void);

  void finish_zmachine_trap_set_mdt(void);

  void zdouble_trap_cause(struct zTrapCause *rop, struct zTrapCause);

  void startup_zdouble_trap_cause(void);

  void finish_zdouble_trap_cause(void);

  sbits ztrap_handler(enum zPrivilege, struct zTrapCause, sbits);

  void startup_ztrap_handler(void);

  void finish_ztrap_handler(void);

  sbits zexception_handler(enum zPrivilege, struct zExceptionContext, sbits);

  unit zhandle_exception(struct zExceptionContext);

  unit zhandle_interrupt(enum zInterruptType, enum zPrivilege);

  unit zreset_misa(unit);

  void startup_zreset_misa(void);

  void finish_zreset_misa(void);

  unit zset_pc_reset_address(uint64_t);

  void startup_zset_pc_reset_address(void);

  void finish_zset_pc_reset_address(void);

  unit zreset_sys(unit);

  void startup_zreset_sys(void);

  void finish_zreset_sys(void);

  void zMemoryOpResult_drop_metazIbzK(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK);

  void startup_zMemoryOpResult_drop_metazIbzK(void);

  void finish_zMemoryOpResult_drop_metazIbzK(void);

  void create_letbind_197(void);
  void kill_letbind_197(void);


  void create_letbind_198(void);
  void kill_letbind_198(void);


  void create_letbind_199(void);
  void kill_letbind_199(void);


  void zsig_load(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t);

  void startup_zsig_load(void);

  void finish_zsig_load(void);

  void zsig_store(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits);

  void startup_zsig_store(void);

  void finish_zsig_store(void);

  void create_letbind_200(void);
  void kill_letbind_200(void);


  bool zwithin_clint(sbits, int64_t);

  void startup_zwithin_clint(void);

  void finish_zwithin_clint(void);

  bool zwithin_sig(sbits, int64_t);

  void startup_zwithin_sig(void);

  void finish_zwithin_sig(void);

  bool zwithin_htif_writable(sbits, int64_t);

  void startup_zwithin_htif_writable(void);

  void finish_zwithin_htif_writable(void);

  bool zwithin_htif_readable(sbits, int64_t);

  uint64_t zclint_get_mtime(unit);

  uint64_t zclint_get_hart_mtimecmp(unit);

  uint64_t zclint_machine_software_interrupt_pending(unit);

  void create_letbind_201(void);
  void kill_letbind_201(void);


  void create_letbind_202(void);
  void kill_letbind_202(void);


  void create_letbind_203(void);
  void kill_letbind_203(void);


  void create_letbind_204(void);
  void kill_letbind_204(void);


  void create_letbind_205(void);
  void kill_letbind_205(void);


  void zclint_load(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, sail_int);

  void startup_zclint_load(void);

  void finish_zclint_load(void);

  void zclint_store(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, sail_int, lbits);

  void startup_zclint_store(void);

  void finish_zclint_store(void);

  bool zshould_inc_mcycle(enum zPrivilege);

  bool zshould_inc_minstret(enum zPrivilege);

  unit zclint_tick_clock(unit);

  void startup_zclint_tick_clock(void);

  void finish_zclint_tick_clock(void);

  struct zhtif_cmd zMk_htif_cmd(uint64_t);

  void startup_zMk_htif_cmd(void);

  void finish_zMk_htif_cmd(void);

  uint64_t z_get_htif_cmd_cmd(struct zhtif_cmd);

  uint64_t z_get_htif_cmd_device(struct zhtif_cmd);

  uint64_t z_get_htif_cmd_payload(struct zhtif_cmd);

  unit zreset_htif(unit);

  void zhtif_load(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t);

  void startup_zhtif_load(void);

  void finish_zhtif_load(void);

  void zhtif_store(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits);

  void startup_zhtif_store(void);

  void finish_zhtif_store(void);

  bool zwithin_mmio_readable(sbits, int64_t);

  void startup_zwithin_mmio_readable(void);

  void finish_zwithin_mmio_readable(void);

  bool zwithin_mmio_writable(sbits, int64_t);

  void startup_zwithin_mmio_writable(void);

  void finish_zwithin_mmio_writable(void);

  void zmmio_read(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t);

  void startup_zmmio_read(void);

  void finish_zmmio_read(void);

  void zmmio_write(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits);

  void startup_zmmio_write(void);

  void finish_zmmio_write(void);

  void startup_zexternal_interrupts_pending(void);

  void finish_zexternal_interrupts_pending(void);

  bool zaccess_within(lbits, sail_int, sail_int);

  void startup_zaccess_within(void);

  void finish_zaccess_within(void);

  bool zallowed_misaligned(sbits, int64_t, int64_t);

  void startup_zallowed_misaligned(void);

  void finish_zallowed_misaligned(void);

  bool zis_aligned_paddr(sbits, sail_int);

  void startup_zis_aligned_paddr(void);

  void finish_zis_aligned_paddr(void);

  bool zis_aligned_vaddr(sbits, sail_int);

  void startup_zis_aligned_vaddr(void);

  void finish_zis_aligned_vaddr(void);

  void create_letbind_206(void);
  void kill_letbind_206(void);


  void create_letbind_207(void);
  void kill_letbind_207(void);


  struct ztuple_z8z5i64zCz0z5i64z9 zsplit_access(sbits, int64_t);

  void startup_zsplit_access(void);

  void finish_zsplit_access(void);

  void create_letbind_208(void);
  void kill_letbind_208(void);


  struct ztuple_z8z5i64zCz0z5i64z9 zsplit_misaligned(sbits, int64_t, int64_t, enum zSplittability);

  void startup_zsplit_misaligned(void);

  void finish_zsplit_misaligned(void);

  void zmisaligned_order(struct ztuple_z8z5izCz0z5izCz0z5i64z9 *rop, sail_int);

  void startup_zmisaligned_order(void);

  void finish_zmisaligned_order(void);

  struct ztuple_z8z5i64zCz0z5i64z9 zsplit_on_page_boundary(sbits, int64_t);

  void startup_zsplit_on_page_boundary(void);

  void finish_zsplit_on_page_boundary(void);

  int64_t znum_of_AtomicSupport(enum zAtomicSupport);

  bool zpma_atomicity_support_lt(enum zAtomicSupport, enum zAtomicSupport);

  void zatomic_support_str_forwards(sail_string *rop, enum zAtomicSupport);

  void zatomic_support_str_forwards_infallible(sail_string *rop, enum zAtomicSupport);

  bool zpma_allows_atomic_op(enum zAtomicSupport, enum zamoop, int64_t);

  void zreservability_str_forwards(sail_string *rop, enum zReservability);

  void zreservability_str_forwards_infallible(sail_string *rop, enum zReservability);

  void zmemory_region_type_str_forwards(sail_string *rop, enum zMemoryRegionType);

  void zmemory_region_type_str_forwards_infallible(sail_string *rop, enum zMemoryRegionType);

  void zoverride_PMA(struct zPMA *rop, struct zPMA, enum zpage_based_mem_type);

  void startup_zoverride_PMA(void);

  void finish_zoverride_PMA(void);

  void zpma_misaligned_exception(struct zoptionzIEmisaligned_exceptionz5zK *rop, struct zPMA, struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zpma_misaligned_exception(void);

  void finish_zpma_misaligned_exception(void);

  bool zis_mag_applicable_access(struct zMemoryAccessTypezIEmem_payloadz5zK, sail_int);

  void startup_zis_mag_applicable_access(void);

  void finish_zis_mag_applicable_access(void);

  void zmag_of_pma(struct zoptionzIizK *rop, struct zPMA, bool);

  void startup_zmag_of_pma(void);

  void finish_zmag_of_pma(void);

  bool zwithin_pma_mag(struct zPMA, sbits, int64_t, bool);

  void startup_zwithin_pma_mag(void);

  void finish_zwithin_pma_mag(void);

  void zmag_pma_check(struct zresultzIz8ESplittabilityz5zCiz9zCEmisaligned_exceptionz5zK *rop, struct zPMA, struct zMemoryAccessTypezIEmem_payloadz5zK, sbits, int64_t);

  void startup_zmag_pma_check(void);

  void finish_zmag_pma_check(void);

  void zmatching_pma_region_bits_range(struct zoptionzIRPMA_RegionzK *rop, zz5listz8z5structz0zzPMA_Regionz9, uint64_t, uint64_t);

  void zmatching_pma_region(struct zoptionzIRPMA_RegionzK *rop, zz5listz8z5structz0zzPMA_Regionz9, sbits, int64_t);

  void startup_zmatching_pma_region(void);

  void finish_zmatching_pma_region(void);

  bool zis_valid_physaddr(zz5listz8z5structz0zzPMA_Regionz9, sbits);

  void startup_zis_valid_physaddr(void);

  void finish_zis_valid_physaddr(void);

  void zpma_misaligned_to_str(sail_string *rop, struct zPMAMisalignedExceptions);

  void zpma_attributes_to_str(sail_string *rop, struct zPMA);

  void startup_zpma_attributes_to_str(void);

  void finish_zpma_attributes_to_str(void);

  enum zread_kind zread_kind_of_flags(bool, bool, bool);

  void startup_zread_kind_of_flags(void);

  void finish_zread_kind_of_flags(void);

  enum zwrite_kind zwrite_kind_of_flags(bool, bool, bool);

  void startup_zwrite_kind_of_flags(void);

  void finish_zwrite_kind_of_flags(void);

  void zpmaCheck(struct zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK *rop, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, bool);

  void startup_zpmaCheck(void);

  void finish_zpmaCheck(void);

  void zphys_access_check(struct zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, sbits, int64_t, bool);

  void zcheck_pma_with_pmp_priority(struct zresultzIRPhys_Mem_Access_InfozCUExceptionTypezK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, sbits, int64_t, bool);

  void startup_zcheck_pma_with_pmp_priority(void);

  void finish_zcheck_pma_with_pmp_priority(void);

  void zchecked_mem_read(struct zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, sbits, int64_t, bool, bool, bool, bool);

  void startup_zchecked_mem_read(void);

  void finish_zchecked_mem_read(void);

  void zmem_read(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, sbits, int64_t, bool, bool, bool);

  void zmem_read_priv_meta(struct zresultzIz8bzCuz9zCz8bzCUExceptionTypez9zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, sbits, int64_t, bool, bool, bool, bool);

  void startup_zmem_read_priv_meta(void);

  void finish_zmem_read_priv_meta(void);

  void zmem_write_ea(struct zresultzIuzCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, enum zPrivilege, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, bool, bool, bool);

  void startup_zmem_write_ea(void);

  void finish_zmem_write_ea(void);

  void zchecked_mem_write(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, unit, bool, bool, bool);

  void startup_zchecked_mem_write(void);

  void finish_zchecked_mem_write(void);

  void zmem_write_value_priv_meta(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, enum zPrivilege, unit, bool, bool, bool);

  void zmem_write_value(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, lbits, enum zPrivilege, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zpage_based_mem_type, bool, bool, bool);

  struct zPTE_Ext zMk_PTE_Ext(uint64_t);

  void startup_zMk_PTE_Ext(void);

  void finish_zMk_PTE_Ext(void);

  uint64_t z_get_PTE_Ext_N(struct zPTE_Ext);

  uint64_t z_get_PTE_Ext_PBMT(struct zPTE_Ext);

  uint64_t z_get_PTE_Ext_RSW_60t59b(struct zPTE_Ext);

  struct zPTE_Ext z_update_PTE_Ext_RSW_60t59b(struct zPTE_Ext, uint64_t);

  void startup_z_update_PTE_Ext_RSW_60t59b(void);

  void finish_z_update_PTE_Ext_RSW_60t59b(void);

  uint64_t z_get_PTE_Ext_reserved(struct zPTE_Ext);

  void create_letbind_209(void);
  void kill_letbind_209(void);


  struct zPTE_Ext zext_bits_of_PTE(sbits);

  void startup_zext_bits_of_PTE(void);

  void finish_zext_bits_of_PTE(void);

  sbits zPPN_of_PTE(sbits);

  void startup_zPPN_of_PTE(void);

  void finish_zPPN_of_PTE(void);

  struct zPTE_Flags zMk_PTE_Flags(uint64_t);

  void startup_zMk_PTE_Flags(void);

  void finish_zMk_PTE_Flags(void);

  uint64_t z_get_PTE_Flags_A(struct zPTE_Flags);

  struct zPTE_Flags z_update_PTE_Flags_A(struct zPTE_Flags, uint64_t);

  void startup_z_update_PTE_Flags_A(void);

  void finish_z_update_PTE_Flags_A(void);

  uint64_t z_get_PTE_Flags_D(struct zPTE_Flags);

  struct zPTE_Flags z_update_PTE_Flags_D(struct zPTE_Flags, uint64_t);

  void startup_z_update_PTE_Flags_D(void);

  void finish_z_update_PTE_Flags_D(void);

  uint64_t z_get_PTE_Flags_G(struct zPTE_Flags);

  uint64_t z_get_PTE_Flags_R(struct zPTE_Flags);

  uint64_t z_get_PTE_Flags_U(struct zPTE_Flags);

  uint64_t z_get_PTE_Flags_V(struct zPTE_Flags);

  uint64_t z_get_PTE_Flags_W(struct zPTE_Flags);

  uint64_t z_get_PTE_Flags_X(struct zPTE_Flags);

  bool zpte_is_non_leaf(struct zPTE_Flags);

  bool zpte_is_invalid(struct zPTE_Flags, struct zPTE_Ext, enum zTranslationStage);

  void startup_zpte_is_invalid(void);

  void finish_zpte_is_invalid(void);

  void zcheck_PTE_permission(struct zPTE_Check *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, enum zTranslationStage, bool, bool, struct zPTE_Flags, struct zPTE_Ext, unit);

  void startup_zcheck_PTE_permission(void);

  void finish_zcheck_PTE_permission(void);

  bool zhw_updates_pte(enum zTranslationStage);

  void startup_zhw_updates_pte(void);

  void finish_zhw_updates_pte(void);

  void zupdate_PTE_Bits(struct zoptionzIbzK *rop, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zTranslationStage);

  void startup_zupdate_PTE_Bits(void);

  void finish_zupdate_PTE_Bits(void);

  void zext_get_ptw_error(struct zPTW_Error *rop, struct zpte_check_failure);

  void zconvertToGuestException(struct zExceptionType *rop, struct zExceptionType);

  sbits zg_stage_tval2_exception_value(struct zExceptionType, sbits);

  void startup_zg_stage_tval2_exception_value(void);

  void finish_zg_stage_tval2_exception_value(void);

  void ztranslationException(struct zExceptionType *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zPTW_Error);

  void startup_ztranslationException(void);

  void finish_ztranslationException(void);

  void create_letbind_210(void);
  void kill_letbind_210(void);


  void create_letbind_211(void);
  void kill_letbind_211(void);


  sbits ztlb_get_pte(int64_t, struct zTLB_Entry);

  void startup_ztlb_get_pte(void);

  void finish_ztlb_get_pte(void);

  struct zTLB_Entry ztlb_set_pte(struct zTLB_Entry, sbits);

  void startup_ztlb_set_pte(void);

  void finish_ztlb_set_pte(void);

  sbits ztlb_get_ppn(int64_t, struct zTLB_Entry, sbits);

  void startup_ztlb_get_ppn(void);

  void finish_ztlb_get_ppn(void);

  enum zpage_based_mem_type ztlb_get_pbmt(struct zTLB_Entry);

  void startup_ztlb_get_pbmt(void);

  void finish_ztlb_get_pbmt(void);

  void create_letbind_212(void);
  void kill_letbind_212(void);


  int64_t ztlb_hash(int64_t, sbits, enum zTranslationStage);

  void startup_ztlb_hash(void);

  void finish_ztlb_hash(void);

  unit zreset_TLB(unit);

  void startup_zreset_TLB(void);

  void finish_zreset_TLB(void);

  unit zwrite_TLB(int64_t, struct zTLB_Entry);

  void startup_zwrite_TLB(void);

  void finish_zwrite_TLB(void);

  bool zmatch_TLB_Entry(struct zTLB_Entry, sbits, sbits, uint64_t, enum zTranslationStage);

  bool zflush_TLB_Entry(struct zTLB_Entry, struct zoptionzIbzK, struct zoptionzIbzK, struct zoptionzIbzK, enum zTranslationStage);

  void startup_zflush_TLB_Entry(void);

  void finish_zflush_TLB_Entry(void);

  void zlookup_TLB(struct zoptionzIz8izCRTLB_Entryz9zK *rop, int64_t, sbits, sbits, sbits, enum zTranslationStage);

  void startup_zlookup_TLB(void);

  void finish_zlookup_TLB(void);

  unit zadd_to_TLB(int64_t, sbits, sbits, sbits, sbits, sbits, sbits, int64_t, bool, enum zTranslationStage);

  void startup_zadd_to_TLB(void);

  void finish_zadd_to_TLB(void);

  unit zflush_TLB(struct zoptionzIbzK, struct zoptionzIbzK, struct zoptionzIbzK, enum zTranslationStage);

  void startup_zflush_TLB(void);

  void finish_zflush_TLB(void);

  void ztranslate_g_stage(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK);

  void zwrite_pte(struct zresultzIozCz8bzCUExceptionTypez9zK *rop, sbits, int64_t, sbits);

  void startup_zwrite_pte(void);

  void finish_zwrite_pte(void);

  void zread_pte(struct zresultzIbzCz8bzCUExceptionTypez9zK *rop, sbits, int64_t);

  void ztranslate_PTE_addr(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zTranslationStage, unit);

  void zupdate_and_write_pte(struct zresultzIUoptionzIbzKzCUPTW_ErrorzK *rop, sbits, int64_t, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zTranslationStage, unit);

  void zpt_walk(struct zresultzIz8RPTW_OutputzCuz9zCz8UPTW_ErrorzCuz9zK *rop, int64_t, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, bool, bool, sbits, int64_t, bool, enum zTranslationStage, unit);

  bool zis_satp_accessible(enum zPrivilege);

  sbits zxatp_to_ppn(enum zTranslationStage);

  void startup_zxatp_to_ppn(void);

  void finish_zxatp_to_ppn(void);

  enum zSATPMode zsatp_mode(enum zPrivilege);

  void startup_zsatp_mode(void);

  void finish_zsatp_mode(void);

  enum zSATPMode zvsatp_mode(unit);

  void startup_zvsatp_mode(void);

  void finish_zvsatp_mode(void);

  enum zHGATPMode zhgatp_mode(unit);

  void startup_zhgatp_mode(void);

  void finish_zhgatp_mode(void);

  void ztranslate_TLB_hit(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, int64_t, sbits, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, bool, bool, int64_t, struct zTLB_Entry, enum zTranslationStage, unit);

  void ztranslate_TLB_miss(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, int64_t, sbits, sbits, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, bool, bool, enum zTranslationStage, unit);

  int64_t zsatp_mode_width_forwards(enum zSATPMode);

  int64_t zsatp_mode_width_forwards_infallible(enum zSATPMode);

  int64_t zhgatp_mode_width_forwards(enum zHGATPMode);

  int64_t zhgatp_mode_width_forwards_infallible(enum zHGATPMode);

  void ztranslate(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, int64_t, sbits, sbits, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, bool, bool, enum zTranslationStage, unit);

  bool zget_mxr(enum zTranslationStage);

  bool zget_sum(enum zTranslationStage);

  void ztranslate_validate_address(struct zresultzIbzCUPTW_ErrorzK *rop, lbits, int64_t, enum zTranslationStage);

  void startup_ztranslate_validate_address(void);

  void finish_ztranslate_validate_address(void);

  void ztranslate_stage(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, int64_t, lbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, enum zTranslationStage);

  void ztranslate_vs_stage(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8UPTW_ErrorzCuz9zK *rop, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  void startup_ztranslate_vs_stage(void);

  void finish_ztranslate_vs_stage(void);

  void zbuild_exception_context(struct zExceptionContext *rop, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zPTW_Error, enum zTranslationStage);

  void startup_zbuild_exception_context(void);

  void finish_zbuild_exception_context(void);

  bool zis_svukte_qualified(struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege, enum zSATPMode);

  void startup_zis_svukte_qualified(void);

  void finish_zis_svukte_qualified(void);

  void ztranslateAddr(struct zresultzIz8bzCEpage_based_mem_typez5zCuz9zCz8RExceptionContextzCuz9zK *rop, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, enum zPrivilege);

  void startup_ztranslateAddr(void);

  void finish_ztranslateAddr(void);

  unit zreset_vmem(unit);

  void startup_zreset_vmem(void);

  void finish_zreset_vmem(void);

  void create_letbind_213(void);
  void kill_letbind_213(void);


  void ztrap(struct zExecutionResult *rop, struct zExceptionContext);

  void zexecute(struct zExecutionResult *rop, struct zinstruction);

  void zassembly_forwards(sail_string *rop, struct zinstruction);

  bool zassembly_forwards_matches(struct zinstruction);

  uint64_t zencdec_forwards(struct zinstruction);

  void zencdec_backwards(struct zinstruction *rop, uint64_t);

  void zencdec_compressed_backwards(struct zinstruction *rop, uint64_t);

  void zplat_misaligned_exception(struct zoptionzIEmisaligned_exceptionz5zK *rop, struct zMemoryAccessTypezIEmem_payloadz5zK, bool);

  bool zis_vmem_active(enum zPrivilege);

  bool zwraps_past_xlen(sbits, sail_int);

  void startup_zwraps_past_xlen(void);

  void finish_zwraps_past_xlen(void);

  sbits zexception_vaddr(struct zAccessInfo, sbits, sbits, sbits);

  void startup_zexception_vaddr(void);

  void finish_zexception_vaddr(void);

  struct zAccessInfo zdefault_access_info(struct zMemoryAccessTypezIEmem_payloadz5zK);

  void startup_zdefault_access_info(void);

  void finish_zdefault_access_info(void);

  sbits ztransform_effective_address(sbits, struct zAccessInfo);

  bool zaccess_is_gva(struct zAccessInfo);

  void zmem_exception_context(struct zExceptionContext *rop, struct zExceptionType, sbits, struct zAccessInfo);

  void zwith_excinst_offset(struct zExecutionResult *rop, struct zExecutionResult, sbits);

  void startup_zwith_excinst_offset(void);

  void finish_zwith_excinst_offset(void);

  void zmemory_exception(struct zExecutionResult *rop, struct zExceptionType, sbits, struct zAccessInfo);

  void startup_zmemory_exception(void);

  void finish_zmemory_exception(void);

  void ztranslate_and_read_value(struct zresultzIz8bzCbz9zCUExecutionResultzK *rop, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void startup_ztranslate_and_read_value(void);

  void finish_ztranslate_and_read_value(void);

  void zvmem_read_addr(struct zresultzIbzCUExecutionResultzK *rop, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void startup_zvmem_read_addr(void);

  void finish_zvmem_read_addr(void);

  void ztranslate_and_write_value(struct zresultzIozCUExecutionResultzK *rop, sbits, int64_t, lbits, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void startup_ztranslate_and_write_value(void);

  void finish_ztranslate_and_write_value(void);

  void zvmem_write_addr(struct zresultzIozCUExecutionResultzK *rop, sbits, int64_t, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void startup_zvmem_write_addr(void);

  void finish_zvmem_write_addr(void);

  void zget_transformed_data_addr(struct zExt_DataAddr_CheckzIuzK *rop, sbits, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, int64_t);

  void zvmem_read_explicit(struct zresultzIbzCUExecutionResultzK *rop, sbits, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void startup_zvmem_read_explicit(void);

  void finish_zvmem_read_explicit(void);

  void zvmem_read(struct zresultzIbzCUExecutionResultzK *rop, sbits, sbits, int64_t, struct zMemoryAccessTypezIEmem_payloadz5zK, bool, bool, bool);

  void startup_zvmem_read(void);

  void finish_zvmem_read(void);

  void zvmem_write_explicit(struct zresultzIozCUExecutionResultzK *rop, sbits, sbits, int64_t, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, struct zAccessInfo, bool, bool, bool);

  void zvmem_write(struct zresultzIozCUExecutionResultzK *rop, sbits, sbits, int64_t, sbits, struct zMemoryAccessTypezIEmem_payloadz5zK, bool, bool, bool);

  void startup_zvmem_write(void);

  void finish_zvmem_write(void);

  uint64_t zencdec_cbop_zzicbop_forwards(enum zcbop_zzicbop);

  enum zcbop_zzicbop zencdec_cbop_zzicbop_backwards(uint64_t);

  bool zencdec_cbop_zzicbop_backwards_matches(uint64_t);

  uint64_t zencdec_cbop_zzicbop_forwards_infallible(enum zcbop_zzicbop);

  enum zcbop_zzicbop zencdec_cbop_zzicbop_backwards_infallible(uint64_t);

  void zprefetch_mnemonic_forwards(sail_string *rop, enum zcbop_zzicbop);

  void zprefetch_mnemonic_forwards_infallible(sail_string *rop, enum zcbop_zzicbop);

  void zmake_landing_pad_exception(struct zExceptionContext *rop, unit);

  void startup_zmake_landing_pad_exception(void);

  void finish_zmake_landing_pad_exception(void);

  bool zis_lpad_instruction(struct zinstruction);

  uint64_t zencdec_uop_forwards(enum zuop);

  enum zuop zencdec_uop_backwards(uint64_t);

  bool zencdec_uop_backwards_matches(uint64_t);

  uint64_t zencdec_uop_forwards_infallible(enum zuop);

  enum zuop zencdec_uop_backwards_infallible(uint64_t);

  void zutype_mnemonic_forwards(sail_string *rop, enum zuop);

  void zutype_mnemonic_forwards_infallible(sail_string *rop, enum zuop);

  void zjump_to(struct zExecutionResult *rop, sbits);

  void startup_zjump_to(void);

  void finish_zjump_to(void);

  uint64_t zencdec_bop_forwards(enum zbop);

  enum zbop zencdec_bop_backwards(uint64_t);

  bool zencdec_bop_backwards_matches(uint64_t);

  uint64_t zencdec_bop_forwards_infallible(enum zbop);

  enum zbop zencdec_bop_backwards_infallible(uint64_t);

  void zbtype_mnemonic_forwards(sail_string *rop, enum zbop);

  void zbtype_mnemonic_forwards_infallible(sail_string *rop, enum zbop);

  uint64_t zencdec_iop_forwards(enum ziop);

  enum ziop zencdec_iop_backwards(uint64_t);

  bool zencdec_iop_backwards_matches(uint64_t);

  uint64_t zencdec_iop_forwards_infallible(enum ziop);

  enum ziop zencdec_iop_backwards_infallible(uint64_t);

  void zitype_mnemonic_forwards(sail_string *rop, enum ziop);

  void zitype_mnemonic_forwards_infallible(sail_string *rop, enum ziop);

  void zshiftiop_mnemonic_forwards(sail_string *rop, enum zsop);

  void zshiftiop_mnemonic_forwards_infallible(sail_string *rop, enum zsop);

  void zrtype_mnemonic_forwards(sail_string *rop, enum zrop);

  void zrtype_mnemonic_forwards_infallible(sail_string *rop, enum zrop);

  bool zvalid_load_encdec(int64_t, bool);

  sbits zextend_value(bool, sbits);

  void startup_zextend_value(void);

  void finish_zextend_value(void);

  void zmaybe_u_forwards(sail_string *rop, bool);

  void zmaybe_u_forwards_infallible(sail_string *rop, bool);

  void zrtypew_mnemonic_forwards(sail_string *rop, enum zropw);

  void zrtypew_mnemonic_forwards_infallible(sail_string *rop, enum zropw);

  void zshiftiwop_mnemonic_forwards(sail_string *rop, enum zsopw);

  void zshiftiwop_mnemonic_forwards_infallible(sail_string *rop, enum zsopw);

  uint64_t zeffective_fence_set(uint64_t, bool);

  void zbit_maybe_r_forwards(sail_string *rop, uint64_t);

  void zbit_maybe_r_forwards_infallible(sail_string *rop, uint64_t);

  void zbit_maybe_w_forwards(sail_string *rop, uint64_t);

  void zbit_maybe_w_forwards_infallible(sail_string *rop, uint64_t);

  void zbit_maybe_i_forwards(sail_string *rop, uint64_t);

  void zbit_maybe_i_forwards_infallible(sail_string *rop, uint64_t);

  void zbit_maybe_o_forwards(sail_string *rop, uint64_t);

  void zbit_maybe_o_forwards_infallible(sail_string *rop, uint64_t);

  void zfence_bits_forwards(sail_string *rop, uint64_t);

  void zfence_bits_forwards_infallible(sail_string *rop, uint64_t);

  bool zxret_modifies_vsstatus(enum zPrivilege, enum zPrivilege);

  void startup_zxret_modifies_vsstatus(void);

  void finish_zxret_modifies_vsstatus(void);

  unit zxret_clear_dbltrp(enum zPrivilege, enum zPrivilege);

  void startup_zxret_clear_dbltrp(void);

  void finish_zxret_clear_dbltrp(void);

  bool zamo_encoding_valid(int64_t, enum zamoop, sbits, sbits);

  void startup_zamo_encoding_valid(void);

  void finish_zamo_encoding_valid(void);

  uint64_t zencdec_amoop_forwards(enum zamoop);

  enum zamoop zencdec_amoop_backwards(uint64_t);

  bool zencdec_amoop_backwards_matches(uint64_t);

  uint64_t zencdec_amoop_forwards_infallible(enum zamoop);

  enum zamoop zencdec_amoop_backwards_infallible(uint64_t);

  bool zlrsc_width_valid(int64_t);

  uint64_t zencdec_mul_op_forwards(struct zmul_op);

  struct zmul_op zencdec_mul_op_backwards(uint64_t);

  bool zencdec_mul_op_backwards_matches(uint64_t);

  uint64_t zencdec_mul_op_forwards_infallible(struct zmul_op);

  void startup_zencdec_mul_op_backwards(void);

  void finish_zencdec_mul_op_backwards(void);

  struct zmul_op zencdec_mul_op_backwards_infallible(uint64_t);

  void startup_zencdec_mul_op_backwards_infallible(void);

  void finish_zencdec_mul_op_backwards_infallible(void);

  void zmul_mnemonic_forwards(sail_string *rop, struct zmul_op);

  void zmul_mnemonic_forwards_infallible(sail_string *rop, struct zmul_op);

  void zzzba_rtypeuw_mnemonic_forwards(sail_string *rop, uint64_t);

  void zzzba_rtypeuw_mnemonic_forwards_infallible(sail_string *rop, uint64_t);

  void zzzba_rtype_mnemonic_forwards(sail_string *rop, uint64_t);

  void zzzba_rtype_mnemonic_forwards_infallible(sail_string *rop, uint64_t);

  void zzzbb_rtypew_mnemonic_forwards(sail_string *rop, enum zbropw_zzbb);

  void zzzbb_rtypew_mnemonic_forwards_infallible(sail_string *rop, enum zbropw_zzbb);

  void zzzbb_rtype_mnemonic_forwards(sail_string *rop, enum zbrop_zzbb);

  void zzzbb_rtype_mnemonic_forwards_infallible(sail_string *rop, enum zbrop_zzbb);

  void zzzbb_extop_mnemonic_forwards(sail_string *rop, enum zextop_zzbb);

  void zzzbb_extop_mnemonic_forwards_infallible(sail_string *rop, enum zextop_zzbb);

  void zzzbs_iop_mnemonic_forwards(sail_string *rop, enum zbiop_zzbs);

  void zzzbs_iop_mnemonic_forwards_infallible(sail_string *rop, enum zbiop_zzbs);

  void zzzbs_rtype_mnemonic_forwards(sail_string *rop, enum zbrop_zzbs);

  void zzzbs_rtype_mnemonic_forwards_infallible(sail_string *rop, enum zbrop_zzbs);

  void zmaybe_hlvx_forwards(sail_string *rop, enum zhlvop);

  void zmaybe_hlvx_forwards_infallible(sail_string *rop, enum zhlvop);

  uint64_t zencdec_rounding_mode_forwards(enum zrounding_mode);

  enum zrounding_mode zencdec_rounding_mode_backwards(uint64_t);

  bool zencdec_rounding_mode_backwards_matches(uint64_t);

  uint64_t zencdec_rounding_mode_forwards_infallible(enum zrounding_mode);

  enum zrounding_mode zencdec_rounding_mode_backwards_infallible(uint64_t);

  void zfrm_mnemonic_forwards(sail_string *rop, enum zrounding_mode);

  void zfrm_mnemonic_forwards_infallible(sail_string *rop, enum zrounding_mode);

  bool zvalid_rounding_mode(uint64_t);

  void zselect_instr_or_fcsr_rm(struct zoptionzIErounding_modez5zK *rop, enum zrounding_mode);

  void startup_zselect_instr_or_fcsr_rm(void);

  void finish_zselect_instr_or_fcsr_rm(void);

  struct ztuple_z8z5bv1zCz0z5bv8zCz0z5bv23z9 zfsplit_S(uint64_t);

  uint64_t zfmake_S(uint64_t, uint64_t, uint64_t);

  bool zf_is_neg_zzero_S(uint64_t);

  bool zf_is_pos_zzero_S(uint64_t);

  bool zf_is_SNaN_S(uint64_t);

  bool zf_is_NaN_S(uint64_t);

  uint64_t znegate_S(uint64_t);

  struct ztuple_z8z5boolzCz0z5bv5z9 zfle_S(uint64_t, uint64_t, bool);

  void startup_zfle_S(void);

  void finish_zfle_S(void);

  bool zhaveSingleFPU(unit);

  bool zfloat_load_store_width_supported(int64_t);

  void zf_madd_type_mnemonic_S_forwards(sail_string *rop, enum zf_madd_op_S);

  void zf_madd_type_mnemonic_S_forwards_infallible(sail_string *rop, enum zf_madd_op_S);

  void zf_bin_rm_type_mnemonic_S_forwards(sail_string *rop, enum zf_bin_rm_op_S);

  void zf_bin_rm_type_mnemonic_S_forwards_infallible(sail_string *rop, enum zf_bin_rm_op_S);

  void zf_un_rm_fx_type_mnemonic_S_forwards(sail_string *rop, enum zf_un_rm_fx_op_S);

  void zf_un_rm_fx_type_mnemonic_S_forwards_infallible(sail_string *rop, enum zf_un_rm_fx_op_S);

  void zf_un_rm_xf_type_mnemonic_S_forwards(sail_string *rop, enum zf_un_rm_xf_op_S);

  void zf_un_rm_xf_type_mnemonic_S_forwards_infallible(sail_string *rop, enum zf_un_rm_xf_op_S);

  void zf_bin_type_mnemonic_f_S_forwards(sail_string *rop, enum zf_bin_op_f_S);

  void zf_bin_type_mnemonic_f_S_forwards_infallible(sail_string *rop, enum zf_bin_op_f_S);

  void zf_bin_type_mnemonic_x_S_forwards(sail_string *rop, enum zf_bin_op_x_S);

  void zf_bin_type_mnemonic_x_S_forwards_infallible(sail_string *rop, enum zf_bin_op_x_S);

  void zf_un_type_mnemonic_x_S_forwards(sail_string *rop, enum zf_un_op_x_S);

  void zf_un_type_mnemonic_x_S_forwards_infallible(sail_string *rop, enum zf_un_op_x_S);

  void zf_un_type_mnemonic_f_S_forwards(sail_string *rop, enum zf_un_op_f_S);

  void zf_un_type_mnemonic_f_S_forwards_infallible(sail_string *rop, enum zf_un_op_f_S);

  struct ztuple_z8z5bv1zCz0z5bv11zCz0z5bv52z9 zfsplit_D(uint64_t);

  uint64_t zfmake_D(uint64_t, uint64_t, uint64_t);

  bool zf_is_neg_zzero_D(uint64_t);

  bool zf_is_pos_zzero_D(uint64_t);

  bool zf_is_SNaN_D(uint64_t);

  bool zf_is_NaN_D(uint64_t);

  uint64_t znegate_D(uint64_t);

  struct ztuple_z8z5boolzCz0z5bv5z9 zfle_D(uint64_t, uint64_t, bool);

  void startup_zfle_D(void);

  void finish_zfle_D(void);

  bool zhaveDoubleFPU(unit);

  bool zvalidDoubleRegs(sail_int, zz5vecz8z5bv5z9);

  void startup_zvalidDoubleRegs(void);

  void finish_zvalidDoubleRegs(void);

  void zf_madd_type_mnemonic_D_forwards(sail_string *rop, enum zf_madd_op_D);

  void zf_madd_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_madd_op_D);

  void zf_bin_rm_type_mnemonic_D_forwards(sail_string *rop, enum zf_bin_rm_op_D);

  void zf_bin_rm_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_bin_rm_op_D);

  void zf_un_rm_ff_type_mnemonic_D_forwards(sail_string *rop, enum zf_un_rm_ff_op_D);

  void zf_un_rm_ff_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_un_rm_ff_op_D);

  void zf_un_rm_fx_type_mnemonic_D_forwards(sail_string *rop, enum zf_un_rm_fx_op_D);

  void zf_un_rm_fx_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_un_rm_fx_op_D);

  void zf_un_rm_xf_type_mnemonic_D_forwards(sail_string *rop, enum zf_un_rm_xf_op_D);

  void zf_un_rm_xf_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_un_rm_xf_op_D);

  void zf_bin_f_type_mnemonic_D_forwards(sail_string *rop, enum zf_bin_f_op_D);

  void zf_bin_f_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_bin_f_op_D);

  void zf_bin_x_type_mnemonic_D_forwards(sail_string *rop, enum zf_bin_x_op_D);

  void zf_bin_x_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_bin_x_op_D);

  void zf_un_x_type_mnemonic_D_forwards(sail_string *rop, enum zf_un_x_op_D);

  void zf_un_x_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_un_x_op_D);

  void zf_un_f_type_mnemonic_D_forwards(sail_string *rop, enum zf_un_f_op_D);

  void zf_un_f_type_mnemonic_D_forwards_infallible(sail_string *rop, enum zf_un_f_op_D);

  struct ztuple_z8z5bv1zCz0z5bv5zCz0z5bv10z9 zfsplit_H(uint64_t);

  uint64_t zfmake_H(uint64_t, uint64_t, uint64_t);

  uint64_t znegate_H(uint64_t);

  bool zf_is_neg_zzero_H(uint64_t);

  bool zf_is_pos_zzero_H(uint64_t);

  bool zf_is_SNaN_H(uint64_t);

  bool zf_is_NaN_H(uint64_t);

  struct ztuple_z8z5boolzCz0z5bv5z9 zfle_H(uint64_t, uint64_t, bool);

  void startup_zfle_H(void);

  void finish_zfle_H(void);

  bool zhaveHalfFPU(unit);

  bool zhaveHalfMin(unit);

  void zf_bin_rm_type_mnemonic_H_forwards(sail_string *rop, enum zf_bin_rm_op_H);

  void zf_bin_rm_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_bin_rm_op_H);

  void zf_madd_type_mnemonic_H_forwards(sail_string *rop, enum zf_madd_op_H);

  void zf_madd_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_madd_op_H);

  void zf_bin_f_type_mnemonic_H_forwards(sail_string *rop, enum zf_bin_f_op_H);

  void zf_bin_f_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_bin_f_op_H);

  void zf_bin_x_type_mnemonic_H_forwards(sail_string *rop, enum zf_bin_x_op_H);

  void zf_bin_x_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_bin_x_op_H);

  void zf_un_rm_ff_type_mnemonic_H_forwards(sail_string *rop, enum zf_un_rm_ff_op_H);

  void zf_un_rm_ff_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_un_rm_ff_op_H);

  void zf_un_rm_fx_type_mnemonic_H_forwards(sail_string *rop, enum zf_un_rm_fx_op_H);

  void zf_un_rm_fx_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_un_rm_fx_op_H);

  void zf_un_rm_xf_type_mnemonic_H_forwards(sail_string *rop, enum zf_un_rm_xf_op_H);

  void zf_un_rm_xf_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_un_rm_xf_op_H);

  void zf_un_f_type_mnemonic_H_forwards(sail_string *rop, enum zf_un_f_op_H);

  void zf_un_f_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_un_f_op_H);

  void zf_un_x_type_mnemonic_H_forwards(sail_string *rop, enum zf_un_x_op_H);

  void zf_un_x_type_mnemonic_H_forwards_infallible(sail_string *rop, enum zf_un_x_op_H);

  struct ztuple_z8z5bv5zCz0z5bv32z9 zfcvtmod_helper(uint64_t);

  void startup_zfcvtmod_helper(void);

  void finish_zfcvtmod_helper(void);

  void zmaybe_vmask_backwards(sail_string *rop, uint64_t);

  void zmaybe_vmask_backwards_infallible(sail_string *rop, uint64_t);

  void create_letbind_214(void);
  void kill_letbind_214(void);


  void create_letbind_215(void);
  void kill_letbind_215(void);


  bool zillegal_vstart(enum zvstart_class, sail_int, sail_int);

  void startup_zillegal_vstart(void);

  void finish_zillegal_vstart(void);

  bool zvalid_eew_emul(sail_int, sail_int);

  void startup_zvalid_eew_emul(void);

  void finish_zvalid_eew_emul(void);

  bool zvalid_vtype(unit);

  void startup_zvalid_vtype(void);

  void finish_zvalid_vtype(void);

  bool zvalid_rd_mask(uint64_t, uint64_t);

  bool zvalid_reg_group(uint64_t, sail_int);

  void startup_zvalid_reg_group(void);

  void finish_zvalid_reg_group(void);

  bool zvalid_whole_register(uint64_t, int64_t);

  void startup_zvalid_whole_register(void);

  void finish_zvalid_whole_register(void);

  bool zvalid_reg_overlap(uint64_t, uint64_t, sail_int, sail_int);

  void startup_zvalid_reg_overlap(void);

  void finish_zvalid_reg_overlap(void);

  bool zvalid_disjoint_reg_groups(uint64_t, uint64_t, sail_int, sail_int);

  void startup_zvalid_disjoint_reg_groups(void);

  void finish_zvalid_disjoint_reg_groups(void);

  bool zvalid_disjoint_reg_groups_segmented(uint64_t, uint64_t, sail_int, sail_int, int64_t);

  void startup_zvalid_disjoint_reg_groups_segmented(void);

  void finish_zvalid_disjoint_reg_groups_segmented(void);

  bool zvalid_src_overlap(uint64_t, sail_int, sail_int, uint64_t, sail_int, sail_int);

  void startup_zvalid_src_overlap(void);

  void finish_zvalid_src_overlap(void);

  bool zvalid_src_overlap_segmented(uint64_t, sail_int, sail_int, uint64_t, sail_int, sail_int, int64_t);

  bool zvalid_vm_src_overlap(uint64_t, uint64_t, sail_int);

  void startup_zvalid_vm_src_overlap(void);

  void finish_zvalid_vm_src_overlap(void);

  bool zvalid_mask_dest_overlap(uint64_t, uint64_t, sail_int);

  void startup_zvalid_mask_dest_overlap(void);

  void finish_zvalid_mask_dest_overlap(void);

  bool zvalid_segment_group_sizze(int64_t, sail_int);

  void startup_zvalid_segment_group_sizze(void);

  void finish_zvalid_segment_group_sizze(void);

  bool zvalid_segment_group_without_overflow(uint64_t, int64_t, sail_int);

  void startup_zvalid_segment_group_without_overflow(void);

  void finish_zvalid_segment_group_without_overflow(void);

  bool zvalid_wide_vvtype(enum zvvfunct6);

  bool zvalid_wide_vxtype(enum zvxfunct6);

  bool zvalid_wide_mvvtype(enum zmvvfunct6);

  bool zvalid_wide_mvxtype(enum zmvxfunct6);

  bool zvalid_widening_fp_conversion(enum zvfwunary0);

  bool zvalid_narrowing_fp_conversion(enum zvfnunary0);

  bool zillegal_normal(uint64_t, uint64_t);

  bool zillegal_vd_masked(uint64_t);

  bool zillegal_vd_unmasked(unit);

  bool zillegal_variable_width(uint64_t, uint64_t, sail_int, sail_int);

  bool zillegal_reduction(unit);

  bool zillegal_widening_reduction(sail_int);

  void startup_zillegal_widening_reduction(void);

  void finish_zillegal_widening_reduction(void);

  bool zillegal_load(uint64_t, uint64_t, int64_t, sail_int, sail_int);

  bool zillegal_store(uint64_t, int64_t, sail_int, sail_int);

  bool zillegal_indexed_load(uint64_t, uint64_t, int64_t, sail_int, sail_int, sail_int);

  bool zillegal_indexed_store(uint64_t, int64_t, sail_int, sail_int, sail_int);

  void zget_scalar(lbits *rop, sbits, sail_int);

  void startup_zget_scalar(void);

  void finish_zget_scalar(void);

  void zget_velem_quad(lbits *rop, zz5vecz8z5bvz9, sail_int);

  void startup_zget_velem_quad(void);

  void finish_zget_velem_quad(void);

  unit zwrite_velem_quad(uint64_t, int64_t, lbits, sail_int);

  void startup_zwrite_velem_quad(void);

  void finish_zwrite_velem_quad(void);

  void zget_velem_oct_vec(zz5vecz8z5sbv64z9 *rop, sail_int, zz5vecz8z5sbv64z9, sail_int);

  void startup_zget_velem_oct_vec(void);

  void finish_zget_velem_oct_vec(void);

  unit zwrite_velem_oct_vec(uint64_t, int64_t, zz5vecz8z5sbv64z9, sail_int);

  void startup_zwrite_velem_oct_vec(void);

  void finish_zwrite_velem_oct_vec(void);

  void zget_velem_quad_vec(zz5vecz8z5sbv64z9 *rop, zz5vecz8z5sbv64z9, sail_int);

  void startup_zget_velem_quad_vec(void);

  void finish_zget_velem_quad_vec(void);

  unit zwrite_velem_quad_vec(uint64_t, int64_t, zz5vecz8z5sbv64z9, sail_int);

  void startup_zwrite_velem_quad_vec(void);

  void finish_zwrite_velem_quad_vec(void);

  int64_t zget_start_element(unit);

  void startup_zget_start_element(void);

  void finish_zget_start_element(void);

  void zget_end_element(sail_int *rop, unit);

  void startup_zget_end_element(void);

  void finish_zget_end_element(void);

  void zinit_masked_result(struct ztuple_z8z5vecz8z5bvz9zCz0z5bvz9 *rop, sail_int, sail_int, sail_int, zz5vecz8z5bvz9, lbits);

  void startup_zinit_masked_result(void);

  void finish_zinit_masked_result(void);

  void zinit_masked_source(lbits *rop, sail_int, sail_int, lbits);

  void startup_zinit_masked_source(void);

  void finish_zinit_masked_source(void);

  void zinit_masked_result_carry(struct ztuple_z8z5bvzCz0z5bvz9 *rop, sail_int, int64_t, sail_int, lbits);

  void startup_zinit_masked_result_carry(void);

  void finish_zinit_masked_result_carry(void);

  void zinit_masked_result_cmp(struct ztuple_z8z5bvzCz0z5bvz9 *rop, sail_int, int64_t, sail_int, lbits, lbits);

  void startup_zinit_masked_result_cmp(void);

  void finish_zinit_masked_result_cmp(void);

  void zread_vreg_seg(zz5vecz8z5bvz9 *rop, sail_int, int64_t, sail_int, int64_t, uint64_t);

  void startup_zread_vreg_seg(void);

  void finish_zread_vreg_seg(void);

  void zget_shift_amount(sail_int *rop, lbits, int64_t);

  void startup_zget_shift_amount(void);

  void finish_zget_shift_amount(void);

  uint64_t zget_fixed_rounding_incr(lbits, sail_int);

  void startup_zget_fixed_rounding_incr(void);

  void finish_zget_fixed_rounding_incr(void);

  void zunsigned_saturation(lbits *rop, sail_int, lbits);

  void startup_zunsigned_saturation(void);

  void finish_zunsigned_saturation(void);

  void zsigned_saturation(lbits *rop, sail_int, lbits);

  void startup_zsigned_saturation(void);

  void finish_zsigned_saturation(void);

  void zvrev8(zz5vecz8z5bvz9 *rop, sail_int, zz5vecz8z5bvz9);

  void startup_zvrev8(void);

  void finish_zvrev8(void);

  bool zvalid_fp_op(int64_t, uint64_t);

  bool zillegal_fp_normal(uint64_t, uint64_t, int64_t, uint64_t);

  bool zillegal_fp_vd_masked(uint64_t, int64_t, uint64_t);

  bool zillegal_fp_vd_unmasked(int64_t, uint64_t);

  bool zillegal_fp_variable_width(uint64_t, uint64_t, int64_t, uint64_t, sail_int, sail_int);

  bool zillegal_fp_reduction(int64_t, uint64_t);

  bool zillegal_fp_widening_reduction(int64_t, uint64_t, sail_int);

  void startup_zillegal_fp_widening_reduction(void);

  void finish_zillegal_fp_widening_reduction(void);

  bool zf_is_neg_zzero(sbits);

  void startup_zf_is_neg_zzero(void);

  void finish_zf_is_neg_zzero(void);

  bool zf_is_pos_zzero(sbits);

  void startup_zf_is_pos_zzero(void);

  void finish_zf_is_pos_zzero(void);

  bool zf_is_NaN(sbits);

  void startup_zf_is_NaN(void);

  void finish_zf_is_NaN(void);

  sbits zget_scalar_fp(uint64_t, int64_t);

  sbits znegate_fp(sbits);

  void startup_znegate_fp(void);

  void finish_znegate_fp(void);

  sbits zfp_add(uint64_t, sbits, sbits);

  void startup_zfp_add(void);

  void finish_zfp_add(void);

  sbits zfp_sub(uint64_t, sbits, sbits);

  void startup_zfp_sub(void);

  void finish_zfp_sub(void);

  sbits zfp_min(sbits, sbits);

  void startup_zfp_min(void);

  void finish_zfp_min(void);

  sbits zfp_max(sbits, sbits);

  void startup_zfp_max(void);

  void finish_zfp_max(void);

  bool zfp_eq(sbits, sbits);

  void startup_zfp_eq(void);

  void finish_zfp_eq(void);

  bool zfp_gt(sbits, sbits);

  void startup_zfp_gt(void);

  void finish_zfp_gt(void);

  bool zfp_ge(sbits, sbits);

  void startup_zfp_ge(void);

  void finish_zfp_ge(void);

  bool zfp_lt(sbits, sbits);

  void startup_zfp_lt(void);

  void finish_zfp_lt(void);

  bool zfp_le(sbits, sbits);

  void startup_zfp_le(void);

  void finish_zfp_le(void);

  sbits zfp_mul(uint64_t, sbits, sbits);

  void startup_zfp_mul(void);

  void finish_zfp_mul(void);

  sbits zfp_div(uint64_t, sbits, sbits);

  void startup_zfp_div(void);

  void finish_zfp_div(void);

  sbits zfp_muladd(uint64_t, sbits, sbits, sbits);

  void startup_zfp_muladd(void);

  void finish_zfp_muladd(void);

  sbits zfp_nmuladd(uint64_t, sbits, sbits, sbits);

  void startup_zfp_nmuladd(void);

  void finish_zfp_nmuladd(void);

  sbits zfp_mulsub(uint64_t, sbits, sbits, sbits);

  void startup_zfp_mulsub(void);

  void finish_zfp_mulsub(void);

  sbits zfp_nmulsub(uint64_t, sbits, sbits, sbits);

  void startup_zfp_nmulsub(void);

  void finish_zfp_nmulsub(void);

  sbits zfp_widen(sbits);

  void startup_zfp_widen(void);

  void finish_zfp_widen(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f16ToI16(uint64_t, uint64_t);

  void startup_zriscv_f16ToI16(void);

  void finish_zriscv_f16ToI16(void);

  struct ztuple_z8z5bv5zCz0z5bv8z9 zriscv_f16ToI8(uint64_t, uint64_t);

  void startup_zriscv_f16ToI8(void);

  void finish_zriscv_f16ToI8(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f32ToI16(uint64_t, uint64_t);

  void startup_zriscv_f32ToI16(void);

  void finish_zriscv_f32ToI16(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f16ToUi16(uint64_t, uint64_t);

  void startup_zriscv_f16ToUi16(void);

  void finish_zriscv_f16ToUi16(void);

  struct ztuple_z8z5bv5zCz0z5bv8z9 zriscv_f16ToUi8(uint64_t, uint64_t);

  void startup_zriscv_f16ToUi8(void);

  void finish_zriscv_f16ToUi8(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f32ToUi16(uint64_t, uint64_t);

  void startup_zriscv_f32ToUi16(void);

  void finish_zriscv_f32ToUi16(void);

  uint64_t zrsqrt7(sbits, bool);

  void startup_zrsqrt7(void);

  void finish_zrsqrt7(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f16Rsqrte7(uint64_t, uint64_t);

  void startup_zriscv_f16Rsqrte7(void);

  void finish_zriscv_f16Rsqrte7(void);

  struct ztuple_z8z5bv5zCz0z5bv32z9 zriscv_f32Rsqrte7(uint64_t, uint64_t);

  void startup_zriscv_f32Rsqrte7(void);

  void finish_zriscv_f32Rsqrte7(void);

  struct ztuple_z8z5bv5zCz0z5bv64z9 zriscv_f64Rsqrte7(uint64_t, uint64_t);

  void startup_zriscv_f64Rsqrte7(void);

  void finish_zriscv_f64Rsqrte7(void);

  struct ztuple_z8z5boolzCz0z5bv64z9 zrecip7(sbits, uint64_t, bool);

  void startup_zrecip7(void);

  void finish_zrecip7(void);

  struct ztuple_z8z5bv5zCz0z5bv16z9 zriscv_f16Recip7(uint64_t, uint64_t);

  void startup_zriscv_f16Recip7(void);

  void finish_zriscv_f16Recip7(void);

  struct ztuple_z8z5bv5zCz0z5bv32z9 zriscv_f32Recip7(uint64_t, uint64_t);

  void startup_zriscv_f32Recip7(void);

  void finish_zriscv_f32Recip7(void);

  struct ztuple_z8z5bv5zCz0z5bv64z9 zriscv_f64Recip7(uint64_t, uint64_t);

  void startup_zriscv_f64Recip7(void);

  void finish_zriscv_f64Recip7(void);

  void zsew_flag_backwards(sail_string *rop, uint64_t);

  void zsew_flag_backwards_infallible(sail_string *rop, uint64_t);

  void zmaybe_lmul_flag_backwards(sail_string *rop, uint64_t);

  void zmaybe_lmul_flag_backwards_infallible(sail_string *rop, uint64_t);

  void zta_flag_backwards(sail_string *rop, uint64_t);

  void zta_flag_backwards_infallible(sail_string *rop, uint64_t);

  void zma_flag_backwards(sail_string *rop, uint64_t);

  void zma_flag_backwards_infallible(sail_string *rop, uint64_t);

  void zvtr_mnemonic_forwards(sail_string *rop, uint64_t);

  void zvtype_assembly_forwards(sail_string *rop, struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3z9);

  void zvtype_assembly_forwards_infallible(sail_string *rop, struct ztuple_z8z5bv3zCz0z5bv1zCz0z5bv1zCz0z5bv3zCz0z5bv3z9);

  void zhandle_illegal_vtype(struct zExecutionResult *rop, sbits);

  void startup_zhandle_illegal_vtype(void);

  void finish_zhandle_illegal_vtype(void);

  void create_letbind_216(void);
  void kill_letbind_216(void);


  int64_t zcalculate_new_vl(sbits, int64_t);

  void startup_zcalculate_new_vl(void);

  void finish_zcalculate_new_vl(void);

  void zexecute_vsetvl_type(struct zExecutionResult *rop, uint64_t, uint64_t, uint64_t, uint64_t, sbits, bool, sbits);

  void startup_zexecute_vsetvl_type(void);

  void finish_zexecute_vsetvl_type(void);

  uint64_t zencdec_vvfunct6_forwards(enum zvvfunct6);

  enum zvvfunct6 zencdec_vvfunct6_backwards(uint64_t);

  bool zencdec_vvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vvfunct6_forwards_infallible(enum zvvfunct6);

  enum zvvfunct6 zencdec_vvfunct6_backwards_infallible(uint64_t);

  void zvvtype_mnemonic_forwards(sail_string *rop, enum zvvfunct6);

  void zvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zvvfunct6);

  uint64_t zencdec_nvsfunct6_forwards(enum znvsfunct6);

  enum znvsfunct6 zencdec_nvsfunct6_backwards(uint64_t);

  bool zencdec_nvsfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nvsfunct6_forwards_infallible(enum znvsfunct6);

  enum znvsfunct6 zencdec_nvsfunct6_backwards_infallible(uint64_t);

  void znvstype_mnemonic_forwards(sail_string *rop, enum znvsfunct6);

  void znvstype_mnemonic_forwards_infallible(sail_string *rop, enum znvsfunct6);

  uint64_t zencdec_nvfunct6_forwards(enum znvfunct6);

  enum znvfunct6 zencdec_nvfunct6_backwards(uint64_t);

  bool zencdec_nvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nvfunct6_forwards_infallible(enum znvfunct6);

  enum znvfunct6 zencdec_nvfunct6_backwards_infallible(uint64_t);

  void znvtype_mnemonic_forwards(sail_string *rop, enum znvfunct6);

  void znvtype_mnemonic_forwards_infallible(sail_string *rop, enum znvfunct6);

  uint64_t zencdec_vxfunct6_forwards(enum zvxfunct6);

  enum zvxfunct6 zencdec_vxfunct6_backwards(uint64_t);

  bool zencdec_vxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxfunct6_forwards_infallible(enum zvxfunct6);

  enum zvxfunct6 zencdec_vxfunct6_backwards_infallible(uint64_t);

  void zvxtype_mnemonic_forwards(sail_string *rop, enum zvxfunct6);

  void zvxtype_mnemonic_forwards_infallible(sail_string *rop, enum zvxfunct6);

  uint64_t zencdec_nxsfunct6_forwards(enum znxsfunct6);

  enum znxsfunct6 zencdec_nxsfunct6_backwards(uint64_t);

  bool zencdec_nxsfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nxsfunct6_forwards_infallible(enum znxsfunct6);

  enum znxsfunct6 zencdec_nxsfunct6_backwards_infallible(uint64_t);

  void znxstype_mnemonic_forwards(sail_string *rop, enum znxsfunct6);

  void znxstype_mnemonic_forwards_infallible(sail_string *rop, enum znxsfunct6);

  uint64_t zencdec_nxfunct6_forwards(enum znxfunct6);

  enum znxfunct6 zencdec_nxfunct6_backwards(uint64_t);

  bool zencdec_nxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nxfunct6_forwards_infallible(enum znxfunct6);

  enum znxfunct6 zencdec_nxfunct6_backwards_infallible(uint64_t);

  void znxtype_mnemonic_forwards(sail_string *rop, enum znxfunct6);

  void znxtype_mnemonic_forwards_infallible(sail_string *rop, enum znxfunct6);

  uint64_t zencdec_vxsgfunct6_forwards(enum zvxsgfunct6);

  enum zvxsgfunct6 zencdec_vxsgfunct6_backwards(uint64_t);

  bool zencdec_vxsgfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxsgfunct6_forwards_infallible(enum zvxsgfunct6);

  enum zvxsgfunct6 zencdec_vxsgfunct6_backwards_infallible(uint64_t);

  void zvxsg_mnemonic_forwards(sail_string *rop, enum zvxsgfunct6);

  void zvxsg_mnemonic_forwards_infallible(sail_string *rop, enum zvxsgfunct6);

  uint64_t zencdec_vifunct6_forwards(enum zvifunct6);

  enum zvifunct6 zencdec_vifunct6_backwards(uint64_t);

  bool zencdec_vifunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vifunct6_forwards_infallible(enum zvifunct6);

  enum zvifunct6 zencdec_vifunct6_backwards_infallible(uint64_t);

  void zvitype_mnemonic_forwards(sail_string *rop, enum zvifunct6);

  void zvitype_mnemonic_forwards_infallible(sail_string *rop, enum zvifunct6);

  uint64_t zencdec_nisfunct6_forwards(enum znisfunct6);

  enum znisfunct6 zencdec_nisfunct6_backwards(uint64_t);

  bool zencdec_nisfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nisfunct6_forwards_infallible(enum znisfunct6);

  enum znisfunct6 zencdec_nisfunct6_backwards_infallible(uint64_t);

  void znistype_mnemonic_forwards(sail_string *rop, enum znisfunct6);

  void znistype_mnemonic_forwards_infallible(sail_string *rop, enum znisfunct6);

  uint64_t zencdec_nifunct6_forwards(enum znifunct6);

  enum znifunct6 zencdec_nifunct6_backwards(uint64_t);

  bool zencdec_nifunct6_backwards_matches(uint64_t);

  uint64_t zencdec_nifunct6_forwards_infallible(enum znifunct6);

  enum znifunct6 zencdec_nifunct6_backwards_infallible(uint64_t);

  void znitype_mnemonic_forwards(sail_string *rop, enum znifunct6);

  void znitype_mnemonic_forwards_infallible(sail_string *rop, enum znifunct6);

  uint64_t zencdec_visgfunct6_forwards(enum zvisgfunct6);

  enum zvisgfunct6 zencdec_visgfunct6_backwards(uint64_t);

  bool zencdec_visgfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_visgfunct6_forwards_infallible(enum zvisgfunct6);

  enum zvisgfunct6 zencdec_visgfunct6_backwards_infallible(uint64_t);

  void zvisg_mnemonic_forwards(sail_string *rop, enum zvisgfunct6);

  void zvisg_mnemonic_forwards_infallible(sail_string *rop, enum zvisgfunct6);

  int64_t zencdec_nreg_forwards(uint64_t);

  uint64_t zencdec_nreg_backwards(int64_t);

  bool zencdec_nreg_forwards_matches(uint64_t);

  int64_t zencdec_nreg_forwards_infallible(uint64_t);

  uint64_t zencdec_nreg_backwards_infallible(int64_t);

  void znreg_string_forwards(sail_string *rop, int64_t);

  void znreg_string_forwards_infallible(sail_string *rop, int64_t);

  uint64_t zencdec_mvvfunct6_forwards(enum zmvvfunct6);

  enum zmvvfunct6 zencdec_mvvfunct6_backwards(uint64_t);

  bool zencdec_mvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_mvvfunct6_forwards_infallible(enum zmvvfunct6);

  enum zmvvfunct6 zencdec_mvvfunct6_backwards_infallible(uint64_t);

  void zmvvtype_mnemonic_forwards(sail_string *rop, enum zmvvfunct6);

  void zmvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zmvvfunct6);

  uint64_t zencdec_mvvmafunct6_forwards(enum zmvvmafunct6);

  enum zmvvmafunct6 zencdec_mvvmafunct6_backwards(uint64_t);

  bool zencdec_mvvmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_mvvmafunct6_forwards_infallible(enum zmvvmafunct6);

  enum zmvvmafunct6 zencdec_mvvmafunct6_backwards_infallible(uint64_t);

  void zmvvmatype_mnemonic_forwards(sail_string *rop, enum zmvvmafunct6);

  void zmvvmatype_mnemonic_forwards_infallible(sail_string *rop, enum zmvvmafunct6);

  uint64_t zencdec_wvvfunct6_forwards(enum zwvvfunct6);

  enum zwvvfunct6 zencdec_wvvfunct6_backwards(uint64_t);

  bool zencdec_wvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wvvfunct6_forwards_infallible(enum zwvvfunct6);

  enum zwvvfunct6 zencdec_wvvfunct6_backwards_infallible(uint64_t);

  void zwvvtype_mnemonic_forwards(sail_string *rop, enum zwvvfunct6);

  void zwvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zwvvfunct6);

  uint64_t zencdec_wvfunct6_forwards(enum zwvfunct6);

  enum zwvfunct6 zencdec_wvfunct6_backwards(uint64_t);

  bool zencdec_wvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wvfunct6_forwards_infallible(enum zwvfunct6);

  enum zwvfunct6 zencdec_wvfunct6_backwards_infallible(uint64_t);

  void zwvtype_mnemonic_forwards(sail_string *rop, enum zwvfunct6);

  void zwvtype_mnemonic_forwards_infallible(sail_string *rop, enum zwvfunct6);

  uint64_t zencdec_wmvvfunct6_forwards(enum zwmvvfunct6);

  enum zwmvvfunct6 zencdec_wmvvfunct6_backwards(uint64_t);

  bool zencdec_wmvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wmvvfunct6_forwards_infallible(enum zwmvvfunct6);

  enum zwmvvfunct6 zencdec_wmvvfunct6_backwards_infallible(uint64_t);

  void zwmvvtype_mnemonic_forwards(sail_string *rop, enum zwmvvfunct6);

  void zwmvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zwmvvfunct6);

  uint64_t zvext_vs1_forwards(enum zvextfunct6);

  enum zvextfunct6 zvext_vs1_backwards(uint64_t);

  bool zvext_vs1_backwards_matches(uint64_t);

  uint64_t zvext_vs1_forwards_infallible(enum zvextfunct6);

  enum zvextfunct6 zvext_vs1_backwards_infallible(uint64_t);

  void zvexttype_mnemonic_forwards(sail_string *rop, enum zvextfunct6);

  void zvexttype_mnemonic_forwards_infallible(sail_string *rop, enum zvextfunct6);

  uint64_t zencdec_mvxfunct6_forwards(enum zmvxfunct6);

  enum zmvxfunct6 zencdec_mvxfunct6_backwards(uint64_t);

  bool zencdec_mvxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_mvxfunct6_forwards_infallible(enum zmvxfunct6);

  enum zmvxfunct6 zencdec_mvxfunct6_backwards_infallible(uint64_t);

  void zmvxtype_mnemonic_forwards(sail_string *rop, enum zmvxfunct6);

  void zmvxtype_mnemonic_forwards_infallible(sail_string *rop, enum zmvxfunct6);

  uint64_t zencdec_mvxmafunct6_forwards(enum zmvxmafunct6);

  enum zmvxmafunct6 zencdec_mvxmafunct6_backwards(uint64_t);

  bool zencdec_mvxmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_mvxmafunct6_forwards_infallible(enum zmvxmafunct6);

  enum zmvxmafunct6 zencdec_mvxmafunct6_backwards_infallible(uint64_t);

  void zmvxmatype_mnemonic_forwards(sail_string *rop, enum zmvxmafunct6);

  void zmvxmatype_mnemonic_forwards_infallible(sail_string *rop, enum zmvxmafunct6);

  uint64_t zencdec_wvxfunct6_forwards(enum zwvxfunct6);

  enum zwvxfunct6 zencdec_wvxfunct6_backwards(uint64_t);

  bool zencdec_wvxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wvxfunct6_forwards_infallible(enum zwvxfunct6);

  enum zwvxfunct6 zencdec_wvxfunct6_backwards_infallible(uint64_t);

  void zwvxtype_mnemonic_forwards(sail_string *rop, enum zwvxfunct6);

  void zwvxtype_mnemonic_forwards_infallible(sail_string *rop, enum zwvxfunct6);

  uint64_t zencdec_wxfunct6_forwards(enum zwxfunct6);

  enum zwxfunct6 zencdec_wxfunct6_backwards(uint64_t);

  bool zencdec_wxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wxfunct6_forwards_infallible(enum zwxfunct6);

  enum zwxfunct6 zencdec_wxfunct6_backwards_infallible(uint64_t);

  void zwxtype_mnemonic_forwards(sail_string *rop, enum zwxfunct6);

  void zwxtype_mnemonic_forwards_infallible(sail_string *rop, enum zwxfunct6);

  uint64_t zencdec_wmvxfunct6_forwards(enum zwmvxfunct6);

  enum zwmvxfunct6 zencdec_wmvxfunct6_backwards(uint64_t);

  bool zencdec_wmvxfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_wmvxfunct6_forwards_infallible(enum zwmvxfunct6);

  enum zwmvxfunct6 zencdec_wmvxfunct6_backwards_infallible(uint64_t);

  void zwmvxtype_mnemonic_forwards(sail_string *rop, enum zwmvxfunct6);

  void zwmvxtype_mnemonic_forwards_infallible(sail_string *rop, enum zwmvxfunct6);

  uint64_t zencdec_fvvfunct6_forwards(enum zfvvfunct6);

  enum zfvvfunct6 zencdec_fvvfunct6_backwards(uint64_t);

  bool zencdec_fvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvvfunct6_forwards_infallible(enum zfvvfunct6);

  enum zfvvfunct6 zencdec_fvvfunct6_backwards_infallible(uint64_t);

  void zfvvtype_mnemonic_forwards(sail_string *rop, enum zfvvfunct6);

  void zfvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zfvvfunct6);

  uint64_t zencdec_fvvmafunct6_forwards(enum zfvvmafunct6);

  enum zfvvmafunct6 zencdec_fvvmafunct6_backwards(uint64_t);

  bool zencdec_fvvmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvvmafunct6_forwards_infallible(enum zfvvmafunct6);

  enum zfvvmafunct6 zencdec_fvvmafunct6_backwards_infallible(uint64_t);

  void zfvvmatype_mnemonic_forwards(sail_string *rop, enum zfvvmafunct6);

  void zfvvmatype_mnemonic_forwards_infallible(sail_string *rop, enum zfvvmafunct6);

  uint64_t zencdec_fwvvfunct6_forwards(enum zfwvvfunct6);

  enum zfwvvfunct6 zencdec_fwvvfunct6_backwards(uint64_t);

  bool zencdec_fwvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwvvfunct6_forwards_infallible(enum zfwvvfunct6);

  enum zfwvvfunct6 zencdec_fwvvfunct6_backwards_infallible(uint64_t);

  void zfwvvtype_mnemonic_forwards(sail_string *rop, enum zfwvvfunct6);

  void zfwvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zfwvvfunct6);

  uint64_t zencdec_fwvvmafunct6_forwards(enum zfwvvmafunct6);

  enum zfwvvmafunct6 zencdec_fwvvmafunct6_backwards(uint64_t);

  bool zencdec_fwvvmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwvvmafunct6_forwards_infallible(enum zfwvvmafunct6);

  enum zfwvvmafunct6 zencdec_fwvvmafunct6_backwards_infallible(uint64_t);

  void zfwvvmatype_mnemonic_forwards(sail_string *rop, enum zfwvvmafunct6);

  void zfwvvmatype_mnemonic_forwards_infallible(sail_string *rop, enum zfwvvmafunct6);

  uint64_t zencdec_fwvfunct6_forwards(enum zfwvfunct6);

  enum zfwvfunct6 zencdec_fwvfunct6_backwards(uint64_t);

  bool zencdec_fwvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwvfunct6_forwards_infallible(enum zfwvfunct6);

  enum zfwvfunct6 zencdec_fwvfunct6_backwards_infallible(uint64_t);

  void zfwvtype_mnemonic_forwards(sail_string *rop, enum zfwvfunct6);

  void zfwvtype_mnemonic_forwards_infallible(sail_string *rop, enum zfwvfunct6);

  uint64_t zencdec_vfunary0_vs1_forwards(enum zvfunary0);

  enum zvfunary0 zencdec_vfunary0_vs1_backwards(uint64_t);

  bool zencdec_vfunary0_vs1_backwards_matches(uint64_t);

  uint64_t zencdec_vfunary0_vs1_forwards_infallible(enum zvfunary0);

  enum zvfunary0 zencdec_vfunary0_vs1_backwards_infallible(uint64_t);

  void zvfunary0_mnemonic_forwards(sail_string *rop, enum zvfunary0);

  void zvfunary0_mnemonic_forwards_infallible(sail_string *rop, enum zvfunary0);

  uint64_t zencdec_vfwunary0_vs1_forwards(enum zvfwunary0);

  enum zvfwunary0 zencdec_vfwunary0_vs1_backwards(uint64_t);

  bool zencdec_vfwunary0_vs1_backwards_matches(uint64_t);

  uint64_t zencdec_vfwunary0_vs1_forwards_infallible(enum zvfwunary0);

  enum zvfwunary0 zencdec_vfwunary0_vs1_backwards_infallible(uint64_t);

  void zvfwunary0_mnemonic_forwards(sail_string *rop, enum zvfwunary0);

  void zvfwunary0_mnemonic_forwards_infallible(sail_string *rop, enum zvfwunary0);

  uint64_t zencdec_vfnunary0_vs1_forwards(enum zvfnunary0);

  enum zvfnunary0 zencdec_vfnunary0_vs1_backwards(uint64_t);

  bool zencdec_vfnunary0_vs1_backwards_matches(uint64_t);

  uint64_t zencdec_vfnunary0_vs1_forwards_infallible(enum zvfnunary0);

  enum zvfnunary0 zencdec_vfnunary0_vs1_backwards_infallible(uint64_t);

  void zvfnunary0_mnemonic_forwards(sail_string *rop, enum zvfnunary0);

  void zvfnunary0_mnemonic_forwards_infallible(sail_string *rop, enum zvfnunary0);

  uint64_t zencdec_vfunary1_vs1_forwards(enum zvfunary1);

  enum zvfunary1 zencdec_vfunary1_vs1_backwards(uint64_t);

  bool zencdec_vfunary1_vs1_backwards_matches(uint64_t);

  uint64_t zencdec_vfunary1_vs1_forwards_infallible(enum zvfunary1);

  enum zvfunary1 zencdec_vfunary1_vs1_backwards_infallible(uint64_t);

  void zvfunary1_mnemonic_forwards(sail_string *rop, enum zvfunary1);

  void zvfunary1_mnemonic_forwards_infallible(sail_string *rop, enum zvfunary1);

  uint64_t zencdec_fvffunct6_forwards(enum zfvffunct6);

  enum zfvffunct6 zencdec_fvffunct6_backwards(uint64_t);

  bool zencdec_fvffunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvffunct6_forwards_infallible(enum zfvffunct6);

  enum zfvffunct6 zencdec_fvffunct6_backwards_infallible(uint64_t);

  void zfvftype_mnemonic_forwards(sail_string *rop, enum zfvffunct6);

  void zfvftype_mnemonic_forwards_infallible(sail_string *rop, enum zfvffunct6);

  uint64_t zencdec_fvfmafunct6_forwards(enum zfvfmafunct6);

  enum zfvfmafunct6 zencdec_fvfmafunct6_backwards(uint64_t);

  bool zencdec_fvfmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvfmafunct6_forwards_infallible(enum zfvfmafunct6);

  enum zfvfmafunct6 zencdec_fvfmafunct6_backwards_infallible(uint64_t);

  void zfvfmatype_mnemonic_forwards(sail_string *rop, enum zfvfmafunct6);

  void zfvfmatype_mnemonic_forwards_infallible(sail_string *rop, enum zfvfmafunct6);

  uint64_t zencdec_fwvffunct6_forwards(enum zfwvffunct6);

  enum zfwvffunct6 zencdec_fwvffunct6_backwards(uint64_t);

  bool zencdec_fwvffunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwvffunct6_forwards_infallible(enum zfwvffunct6);

  enum zfwvffunct6 zencdec_fwvffunct6_backwards_infallible(uint64_t);

  void zfwvftype_mnemonic_forwards(sail_string *rop, enum zfwvffunct6);

  void zfwvftype_mnemonic_forwards_infallible(sail_string *rop, enum zfwvffunct6);

  uint64_t zencdec_fwvfmafunct6_forwards(enum zfwvfmafunct6);

  enum zfwvfmafunct6 zencdec_fwvfmafunct6_backwards(uint64_t);

  bool zencdec_fwvfmafunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwvfmafunct6_forwards_infallible(enum zfwvfmafunct6);

  enum zfwvfmafunct6 zencdec_fwvfmafunct6_backwards_infallible(uint64_t);

  void zfwvfmatype_mnemonic_forwards(sail_string *rop, enum zfwvfmafunct6);

  void zfwvfmatype_mnemonic_forwards_infallible(sail_string *rop, enum zfwvfmafunct6);

  uint64_t zencdec_fwffunct6_forwards(enum zfwffunct6);

  enum zfwffunct6 zencdec_fwffunct6_backwards(uint64_t);

  bool zencdec_fwffunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fwffunct6_forwards_infallible(enum zfwffunct6);

  enum zfwffunct6 zencdec_fwffunct6_backwards_infallible(uint64_t);

  void zfwftype_mnemonic_forwards(sail_string *rop, enum zfwffunct6);

  void zfwftype_mnemonic_forwards_infallible(sail_string *rop, enum zfwffunct6);

  void zvlewidth_bitsnumberstr_forwards(sail_string *rop, enum zvlewidth);

  void zvlewidth_bitsnumberstr_forwards_infallible(sail_string *rop, enum zvlewidth);

  uint64_t zencdec_vlewidth_forwards(enum zvlewidth);

  enum zvlewidth zencdec_vlewidth_backwards(uint64_t);

  bool zencdec_vlewidth_backwards_matches(uint64_t);

  uint64_t zencdec_vlewidth_forwards_infallible(enum zvlewidth);

  enum zvlewidth zencdec_vlewidth_backwards_infallible(uint64_t);

  int64_t zvlewidth_pow_forwards(enum zvlewidth);

  int64_t zvlewidth_pow_forwards_infallible(enum zvlewidth);

  uint64_t zencdec_indexed_mop_forwards(enum zindexed_mop);

  enum zindexed_mop zencdec_indexed_mop_backwards(uint64_t);

  bool zencdec_indexed_mop_backwards_matches(uint64_t);

  uint64_t zencdec_indexed_mop_forwards_infallible(enum zindexed_mop);

  enum zindexed_mop zencdec_indexed_mop_backwards_infallible(uint64_t);

  void zindexed_mop_mnemonic_forwards(sail_string *rop, enum zindexed_mop);

  void zindexed_mop_mnemonic_forwards_infallible(sail_string *rop, enum zindexed_mop);

  uint64_t zencdec_lsop_forwards(enum zvmlsop);

  enum zvmlsop zencdec_lsop_backwards(uint64_t);

  bool zencdec_lsop_backwards_matches(uint64_t);

  uint64_t zencdec_lsop_forwards_infallible(enum zvmlsop);

  enum zvmlsop zencdec_lsop_backwards_infallible(uint64_t);

  void zvmtype_mnemonic_forwards(sail_string *rop, enum zvmlsop);

  void zvmtype_mnemonic_forwards_infallible(sail_string *rop, enum zvmlsop);

  uint64_t zencdec_mmfunct6_forwards(enum zmmfunct6);

  enum zmmfunct6 zencdec_mmfunct6_backwards(uint64_t);

  bool zencdec_mmfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_mmfunct6_forwards_infallible(enum zmmfunct6);

  enum zmmfunct6 zencdec_mmfunct6_backwards_infallible(uint64_t);

  void zmmtype_mnemonic_forwards(sail_string *rop, enum zmmfunct6);

  void zmmtype_mnemonic_forwards_infallible(sail_string *rop, enum zmmfunct6);

  uint64_t zencdec_vvmfunct6_forwards(enum zvvmfunct6);

  enum zvvmfunct6 zencdec_vvmfunct6_backwards(uint64_t);

  bool zencdec_vvmfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vvmfunct6_forwards_infallible(enum zvvmfunct6);

  enum zvvmfunct6 zencdec_vvmfunct6_backwards_infallible(uint64_t);

  void zvvmtype_mnemonic_forwards(sail_string *rop, enum zvvmfunct6);

  void zvvmtype_mnemonic_forwards_infallible(sail_string *rop, enum zvvmfunct6);

  uint64_t zencdec_vvmcfunct6_forwards(enum zvvmcfunct6);

  enum zvvmcfunct6 zencdec_vvmcfunct6_backwards(uint64_t);

  bool zencdec_vvmcfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vvmcfunct6_forwards_infallible(enum zvvmcfunct6);

  enum zvvmcfunct6 zencdec_vvmcfunct6_backwards_infallible(uint64_t);

  void zvvmctype_mnemonic_forwards(sail_string *rop, enum zvvmcfunct6);

  void zvvmctype_mnemonic_forwards_infallible(sail_string *rop, enum zvvmcfunct6);

  uint64_t zencdec_vvmsfunct6_forwards(enum zvvmsfunct6);

  enum zvvmsfunct6 zencdec_vvmsfunct6_backwards(uint64_t);

  bool zencdec_vvmsfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vvmsfunct6_forwards_infallible(enum zvvmsfunct6);

  enum zvvmsfunct6 zencdec_vvmsfunct6_backwards_infallible(uint64_t);

  void zvvmstype_mnemonic_forwards(sail_string *rop, enum zvvmsfunct6);

  void zvvmstype_mnemonic_forwards_infallible(sail_string *rop, enum zvvmsfunct6);

  uint64_t zencdec_vvcmpfunct6_forwards(enum zvvcmpfunct6);

  enum zvvcmpfunct6 zencdec_vvcmpfunct6_backwards(uint64_t);

  bool zencdec_vvcmpfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vvcmpfunct6_forwards_infallible(enum zvvcmpfunct6);

  enum zvvcmpfunct6 zencdec_vvcmpfunct6_backwards_infallible(uint64_t);

  void zvvcmptype_mnemonic_forwards(sail_string *rop, enum zvvcmpfunct6);

  void zvvcmptype_mnemonic_forwards_infallible(sail_string *rop, enum zvvcmpfunct6);

  uint64_t zencdec_vxmfunct6_forwards(enum zvxmfunct6);

  enum zvxmfunct6 zencdec_vxmfunct6_backwards(uint64_t);

  bool zencdec_vxmfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxmfunct6_forwards_infallible(enum zvxmfunct6);

  enum zvxmfunct6 zencdec_vxmfunct6_backwards_infallible(uint64_t);

  void zvxmtype_mnemonic_forwards(sail_string *rop, enum zvxmfunct6);

  void zvxmtype_mnemonic_forwards_infallible(sail_string *rop, enum zvxmfunct6);

  uint64_t zencdec_vxmcfunct6_forwards(enum zvxmcfunct6);

  enum zvxmcfunct6 zencdec_vxmcfunct6_backwards(uint64_t);

  bool zencdec_vxmcfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxmcfunct6_forwards_infallible(enum zvxmcfunct6);

  enum zvxmcfunct6 zencdec_vxmcfunct6_backwards_infallible(uint64_t);

  void zvxmctype_mnemonic_forwards(sail_string *rop, enum zvxmcfunct6);

  void zvxmctype_mnemonic_forwards_infallible(sail_string *rop, enum zvxmcfunct6);

  uint64_t zencdec_vxmsfunct6_forwards(enum zvxmsfunct6);

  enum zvxmsfunct6 zencdec_vxmsfunct6_backwards(uint64_t);

  bool zencdec_vxmsfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxmsfunct6_forwards_infallible(enum zvxmsfunct6);

  enum zvxmsfunct6 zencdec_vxmsfunct6_backwards_infallible(uint64_t);

  void zvxmstype_mnemonic_forwards(sail_string *rop, enum zvxmsfunct6);

  void zvxmstype_mnemonic_forwards_infallible(sail_string *rop, enum zvxmsfunct6);

  uint64_t zencdec_vxcmpfunct6_forwards(enum zvxcmpfunct6);

  enum zvxcmpfunct6 zencdec_vxcmpfunct6_backwards(uint64_t);

  bool zencdec_vxcmpfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vxcmpfunct6_forwards_infallible(enum zvxcmpfunct6);

  enum zvxcmpfunct6 zencdec_vxcmpfunct6_backwards_infallible(uint64_t);

  void zvxcmptype_mnemonic_forwards(sail_string *rop, enum zvxcmpfunct6);

  void zvxcmptype_mnemonic_forwards_infallible(sail_string *rop, enum zvxcmpfunct6);

  uint64_t zencdec_vimfunct6_forwards(enum zvimfunct6);

  enum zvimfunct6 zencdec_vimfunct6_backwards(uint64_t);

  bool zencdec_vimfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vimfunct6_forwards_infallible(enum zvimfunct6);

  enum zvimfunct6 zencdec_vimfunct6_backwards_infallible(uint64_t);

  void zvimtype_mnemonic_forwards(sail_string *rop, enum zvimfunct6);

  void zvimtype_mnemonic_forwards_infallible(sail_string *rop, enum zvimfunct6);

  uint64_t zencdec_vimcfunct6_forwards(enum zvimcfunct6);

  enum zvimcfunct6 zencdec_vimcfunct6_backwards(uint64_t);

  bool zencdec_vimcfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vimcfunct6_forwards_infallible(enum zvimcfunct6);

  enum zvimcfunct6 zencdec_vimcfunct6_backwards_infallible(uint64_t);

  void zvimctype_mnemonic_forwards(sail_string *rop, enum zvimcfunct6);

  void zvimctype_mnemonic_forwards_infallible(sail_string *rop, enum zvimcfunct6);

  uint64_t zencdec_vimsfunct6_forwards(enum zvimsfunct6);

  enum zvimsfunct6 zencdec_vimsfunct6_backwards(uint64_t);

  bool zencdec_vimsfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vimsfunct6_forwards_infallible(enum zvimsfunct6);

  enum zvimsfunct6 zencdec_vimsfunct6_backwards_infallible(uint64_t);

  void zvimstype_mnemonic_forwards(sail_string *rop, enum zvimsfunct6);

  void zvimstype_mnemonic_forwards_infallible(sail_string *rop, enum zvimsfunct6);

  uint64_t zencdec_vicmpfunct6_forwards(enum zvicmpfunct6);

  enum zvicmpfunct6 zencdec_vicmpfunct6_backwards(uint64_t);

  bool zencdec_vicmpfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_vicmpfunct6_forwards_infallible(enum zvicmpfunct6);

  enum zvicmpfunct6 zencdec_vicmpfunct6_backwards_infallible(uint64_t);

  void zvicmptype_mnemonic_forwards(sail_string *rop, enum zvicmpfunct6);

  void zvicmptype_mnemonic_forwards_infallible(sail_string *rop, enum zvicmpfunct6);

  uint64_t zencdec_fvvmfunct6_forwards(enum zfvvmfunct6);

  enum zfvvmfunct6 zencdec_fvvmfunct6_backwards(uint64_t);

  bool zencdec_fvvmfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvvmfunct6_forwards_infallible(enum zfvvmfunct6);

  enum zfvvmfunct6 zencdec_fvvmfunct6_backwards_infallible(uint64_t);

  void zfvvmtype_mnemonic_forwards(sail_string *rop, enum zfvvmfunct6);

  void zfvvmtype_mnemonic_forwards_infallible(sail_string *rop, enum zfvvmfunct6);

  uint64_t zencdec_fvfmfunct6_forwards(enum zfvfmfunct6);

  enum zfvfmfunct6 zencdec_fvfmfunct6_backwards(uint64_t);

  bool zencdec_fvfmfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_fvfmfunct6_forwards_infallible(enum zfvfmfunct6);

  enum zfvfmfunct6 zencdec_fvfmfunct6_backwards_infallible(uint64_t);

  void zfvfmtype_mnemonic_forwards(sail_string *rop, enum zfvfmfunct6);

  void zfvfmtype_mnemonic_forwards_infallible(sail_string *rop, enum zfvfmfunct6);

  uint64_t zencdec_rivvfunct6_forwards(enum zrivvfunct6);

  enum zrivvfunct6 zencdec_rivvfunct6_backwards(uint64_t);

  bool zencdec_rivvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_rivvfunct6_forwards_infallible(enum zrivvfunct6);

  enum zrivvfunct6 zencdec_rivvfunct6_backwards_infallible(uint64_t);

  void zrivvtype_mnemonic_forwards(sail_string *rop, enum zrivvfunct6);

  void zrivvtype_mnemonic_forwards_infallible(sail_string *rop, enum zrivvfunct6);

  uint64_t zencdec_rmvvfunct6_forwards(enum zrmvvfunct6);

  enum zrmvvfunct6 zencdec_rmvvfunct6_backwards(uint64_t);

  bool zencdec_rmvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_rmvvfunct6_forwards_infallible(enum zrmvvfunct6);

  enum zrmvvfunct6 zencdec_rmvvfunct6_backwards_infallible(uint64_t);

  void zrmvvtype_mnemonic_forwards(sail_string *rop, enum zrmvvfunct6);

  void zrmvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zrmvvfunct6);

  uint64_t zencdec_rfvvfunct6_forwards(enum zrfvvfunct6);

  enum zrfvvfunct6 zencdec_rfvvfunct6_backwards(uint64_t);

  bool zencdec_rfvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_rfvvfunct6_forwards_infallible(enum zrfvvfunct6);

  enum zrfvvfunct6 zencdec_rfvvfunct6_backwards_infallible(uint64_t);

  void zrfvvtype_mnemonic_forwards(sail_string *rop, enum zrfvvfunct6);

  void zrfvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zrfvvfunct6);

  uint64_t zencdec_rfwvvfunct6_forwards(enum zrfwvvfunct6);

  enum zrfwvvfunct6 zencdec_rfwvvfunct6_backwards(uint64_t);

  bool zencdec_rfwvvfunct6_backwards_matches(uint64_t);

  uint64_t zencdec_rfwvvfunct6_forwards_infallible(enum zrfwvvfunct6);

  enum zrfwvvfunct6 zencdec_rfwvvfunct6_backwards_infallible(uint64_t);

  void zrfwvvtype_mnemonic_forwards(sail_string *rop, enum zrfwvvfunct6);

  void zrfwvvtype_mnemonic_forwards_infallible(sail_string *rop, enum zrfwvvfunct6);

  sbits zread_seed_csr(unit);

  void startup_zread_seed_csr(void);

  void finish_zread_seed_csr(void);

  sbits zwrite_seed_csr(unit);

  void startup_zwrite_seed_csr(void);

  void finish_zwrite_seed_csr(void);

  void zzzbkb_rtype_mnemonic_forwards(sail_string *rop, enum zbrop_zzbkb);

  void zzzbkb_rtype_mnemonic_forwards_infallible(sail_string *rop, enum zbrop_zzbkb);

  uint64_t zencdec_vaesdf_forwards(enum zzzvk_vaesdf_funct6);

  enum zzzvk_vaesdf_funct6 zencdec_vaesdf_backwards(uint64_t);

  bool zencdec_vaesdf_backwards_matches(uint64_t);

  uint64_t zencdec_vaesdf_forwards_infallible(enum zzzvk_vaesdf_funct6);

  enum zzzvk_vaesdf_funct6 zencdec_vaesdf_backwards_infallible(uint64_t);

  void zvaesdf_mnemonic_forwards(sail_string *rop, enum zzzvk_vaesdf_funct6);

  void zvaesdf_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vaesdf_funct6);

  uint64_t zencdec_vaesdm_forwards(enum zzzvk_vaesdm_funct6);

  enum zzzvk_vaesdm_funct6 zencdec_vaesdm_backwards(uint64_t);

  bool zencdec_vaesdm_backwards_matches(uint64_t);

  uint64_t zencdec_vaesdm_forwards_infallible(enum zzzvk_vaesdm_funct6);

  enum zzzvk_vaesdm_funct6 zencdec_vaesdm_backwards_infallible(uint64_t);

  void zvaesdm_mnemonic_forwards(sail_string *rop, enum zzzvk_vaesdm_funct6);

  void zvaesdm_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vaesdm_funct6);

  uint64_t zencdec_vaesef_forwards(enum zzzvk_vaesef_funct6);

  enum zzzvk_vaesef_funct6 zencdec_vaesef_backwards(uint64_t);

  bool zencdec_vaesef_backwards_matches(uint64_t);

  uint64_t zencdec_vaesef_forwards_infallible(enum zzzvk_vaesef_funct6);

  enum zzzvk_vaesef_funct6 zencdec_vaesef_backwards_infallible(uint64_t);

  void zvaesef_mnemonic_forwards(sail_string *rop, enum zzzvk_vaesef_funct6);

  void zvaesef_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vaesef_funct6);

  uint64_t zencdec_vaesem_forwards(enum zzzvk_vaesem_funct6);

  enum zzzvk_vaesem_funct6 zencdec_vaesem_backwards(uint64_t);

  bool zencdec_vaesem_backwards_matches(uint64_t);

  uint64_t zencdec_vaesem_forwards_infallible(enum zzzvk_vaesem_funct6);

  enum zzzvk_vaesem_funct6 zencdec_vaesem_backwards_infallible(uint64_t);

  void zvaesem_mnemonic_forwards(sail_string *rop, enum zzzvk_vaesem_funct6);

  void zvaesem_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vaesem_funct6);

  void zvsm4r_mnemonic_forwards(sail_string *rop, enum zzzvk_vsm4r_funct6);

  void zvsm4r_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vsm4r_funct6);

  uint64_t zencdec_vsha2_forwards(enum zzzvk_vsha2_funct6);

  enum zzzvk_vsha2_funct6 zencdec_vsha2_backwards(uint64_t);

  bool zencdec_vsha2_backwards_matches(uint64_t);

  uint64_t zencdec_vsha2_forwards_infallible(enum zzzvk_vsha2_funct6);

  enum zzzvk_vsha2_funct6 zencdec_vsha2_backwards_infallible(uint64_t);

  void zvsha2_mnemonic_forwards(sail_string *rop, enum zzzvk_vsha2_funct6);

  void zvsha2_mnemonic_forwards_infallible(sail_string *rop, enum zzzvk_vsha2_funct6);

  bool zvalid_zzvwabda_sew(int64_t);

  uint64_t zencdec_zzvabd_vabd_func6_forwards(enum zzzvabd_vabd_func6);

  enum zzzvabd_vabd_func6 zencdec_zzvabd_vabd_func6_backwards(uint64_t);

  bool zencdec_zzvabd_vabd_func6_backwards_matches(uint64_t);

  uint64_t zencdec_zzvabd_vabd_func6_forwards_infallible(enum zzzvabd_vabd_func6);

  enum zzzvabd_vabd_func6 zencdec_zzvabd_vabd_func6_backwards_infallible(uint64_t);

  void zvabd_vv_mnemonic_forwards(sail_string *rop, enum zzzvabd_vabd_func6);

  void zvabd_vv_mnemonic_forwards_infallible(sail_string *rop, enum zzzvabd_vabd_func6);

  void zvabd_vx_mnemonic_forwards(sail_string *rop, enum zzzvabd_vabd_func6);

  void zvabd_vx_mnemonic_forwards_infallible(sail_string *rop, enum zzzvabd_vabd_func6);

  uint64_t zencdec_zzvabd_vwabda_func6_forwards(enum zzzvabd_vwabda_func6);

  enum zzzvabd_vwabda_func6 zencdec_zzvabd_vwabda_func6_backwards(uint64_t);

  bool zencdec_zzvabd_vwabda_func6_backwards_matches(uint64_t);

  uint64_t zencdec_zzvabd_vwabda_func6_forwards_infallible(enum zzzvabd_vwabda_func6);

  enum zzzvabd_vwabda_func6 zencdec_zzvabd_vwabda_func6_backwards_infallible(uint64_t);

  void zvwabda_vv_mnemonic_forwards(sail_string *rop, enum zzzvabd_vwabda_func6);

  void zvwabda_vv_mnemonic_forwards_infallible(sail_string *rop, enum zzzvabd_vwabda_func6);

  void zvwabda_vx_mnemonic_forwards(sail_string *rop, enum zzzvabd_vwabda_func6);

  void zvwabda_vx_mnemonic_forwards_infallible(sail_string *rop, enum zzzvabd_vwabda_func6);

  uint64_t zencdec_csrop_forwards(enum zcsrop);

  enum zcsrop zencdec_csrop_backwards(uint64_t);

  bool zencdec_csrop_backwards_matches(uint64_t);

  uint64_t zencdec_csrop_forwards_infallible(enum zcsrop);

  enum zcsrop zencdec_csrop_backwards_infallible(uint64_t);

  enum zCSRAccessType zcsr_access_type(enum zcsrop, bool, bool);

  void zdoCSR(struct zExecutionResult *rop, uint64_t, sbits, sbits, enum zcsrop, enum zCSRAccessType);

  void startup_zdoCSR(void);

  void finish_zdoCSR(void);

  void zcsr_mnemonic_forwards(sail_string *rop, enum zcsrop);

  void zcsr_mnemonic_forwards_infallible(sail_string *rop, enum zcsrop);

  uint64_t zread_mhpmeventh(int64_t);

  uint64_t zget_scountovf(enum zPrivilege);

  void startup_zget_scountovf(void);

  void finish_zget_scountovf(void);

  bool zis_stimecmp_accessible(enum zPrivilege);

  void startup_zis_stimecmp_accessible(void);

  void finish_zis_stimecmp_accessible(void);

  bool zis_vstimecmp_accessible(enum zPrivilege);

  uint64_t zencdec_wrsop_forwards(enum zwrsop);

  enum zwrsop zencdec_wrsop_backwards(uint64_t);

  bool zencdec_wrsop_backwards_matches(uint64_t);

  uint64_t zencdec_wrsop_forwards_infallible(enum zwrsop);

  enum zwrsop zencdec_wrsop_backwards_infallible(uint64_t);

  bool zzzicfiss_xSSE(enum zPrivilege);

  void startup_zzzicfiss_xSSE(void);

  void finish_zzzicfiss_xSSE(void);

  bool zis_ssp_accessible(enum zPrivilege);

  void startup_zis_ssp_accessible(void);

  void finish_zis_ssp_accessible(void);

  void zmake_shadow_stack_exception(struct zExceptionContext *rop, unit);

  void startup_zmake_shadow_stack_exception(void);

  void finish_zmake_shadow_stack_exception(void);

  uint64_t zencdec_zzicondop_forwards(enum zzzicondop);

  enum zzzicondop zencdec_zzicondop_backwards(uint64_t);

  bool zencdec_zzicondop_backwards_matches(uint64_t);

  uint64_t zencdec_zzicondop_forwards_infallible(enum zzzicondop);

  enum zzzicondop zencdec_zzicondop_backwards_infallible(uint64_t);

  void zzzicond_mnemonic_forwards(sail_string *rop, enum zzzicondop);

  void zzzicond_mnemonic_forwards_infallible(sail_string *rop, enum zzzicondop);

  uint64_t zencdec_cbop_forwards(enum zcbop_zzicbom);

  enum zcbop_zzicbom zencdec_cbop_backwards(uint64_t);

  bool zencdec_cbop_backwards_matches(uint64_t);

  uint64_t zencdec_cbop_forwards_infallible(enum zcbop_zzicbom);

  enum zcbop_zzicbom zencdec_cbop_backwards_infallible(uint64_t);

  void zcbop_mnemonic_forwards(sail_string *rop, enum zcbop_zzicbom);

  void zcbop_mnemonic_forwards_infallible(sail_string *rop, enum zcbop_zzicbom);

  enum zcbie zencdec_cbie_backwards(uint64_t);

  void startup_zencdec_cbie_backwards(void);

  void finish_zencdec_cbie_backwards(void);

  enum zcbie zencdec_cbie_backwards_infallible(uint64_t);

  void startup_zencdec_cbie_backwards_infallible(void);

  void finish_zencdec_cbie_backwards_infallible(void);

  enum zchecked_cbop zcbop_priv_check(enum zPrivilege);

  void startup_zcbop_priv_check(void);

  void finish_zcbop_priv_check(void);

  void zprocess_clean_inval(struct zExecutionResult *rop, sbits, enum zcbop_zzicbom);

  void startup_zprocess_clean_inval(void);

  void finish_zprocess_clean_inval(void);

  uint64_t zencdec_biop_forwards(enum zbiop);

  enum zbiop zencdec_biop_backwards(uint64_t);

  bool zencdec_biop_backwards_matches(uint64_t);

  uint64_t zencdec_biop_forwards_infallible(enum zbiop);

  enum zbiop zencdec_biop_backwards_infallible(uint64_t);

  void zbitype_mnemonic_forwards(sail_string *rop, enum zbiop);

  void zbitype_mnemonic_forwards_infallible(sail_string *rop, enum zbiop);

  uint64_t zencdec_zzilx_mode_forwards(enum zzzilx_mode);

  enum zzzilx_mode zencdec_zzilx_mode_backwards(uint64_t);

  bool zencdec_zzilx_mode_backwards_matches(uint64_t);

  uint64_t zencdec_zzilx_mode_forwards_infallible(enum zzzilx_mode);

  enum zzzilx_mode zencdec_zzilx_mode_backwards_infallible(uint64_t);

  bool zzzilx_encoding_valid(enum zzzilx_mode, int64_t, bool);

  void startup_zzzilx_encoding_valid(void);

  void finish_zzzilx_encoding_valid(void);

  void zzzilx_mode_mnemonic_forwards(sail_string *rop, enum zzzilx_mode);

  void zzzilx_mode_mnemonic_forwards_infallible(sail_string *rop, enum zzzilx_mode);

  void create_letbind_217(void);
  void kill_letbind_217(void);


  void create_letbind_218(void);
  void kill_letbind_218(void);


  struct zSrmcfg zundefined_Srmcfg(unit);

  void startup_zundefined_Srmcfg(void);

  void finish_zundefined_Srmcfg(void);

  struct zSrmcfg zMk_Srmcfg(sbits);

  void startup_zMk_Srmcfg(void);

  void finish_zMk_Srmcfg(void);

  uint64_t z_get_Srmcfg_MCID(struct zSrmcfg);

  struct zSrmcfg z_update_Srmcfg_MCID(struct zSrmcfg, uint64_t);

  void startup_z_update_Srmcfg_MCID(void);

  void finish_z_update_Srmcfg_MCID(void);

  uint64_t z_get_Srmcfg_RCID(struct zSrmcfg);

  struct zSrmcfg z_update_Srmcfg_RCID(struct zSrmcfg, uint64_t);

  void startup_z_update_Srmcfg_RCID(void);

  void finish_z_update_Srmcfg_RCID(void);

  struct zSrmcfg zlegalizze_srmcfg(struct zSrmcfg, sbits);

  void startup_zlegalizze_srmcfg(void);

  void finish_zlegalizze_srmcfg(void);

  struct ztuple_z8z5bv1zCz0z5bv8zCz0z5bv7z9 zfsplit_BF16(uint64_t);

  struct ztuple_z8z5bv5zCz0z5bv32z9 zbf16_to_f32(uint64_t);

  void startup_zbf16_to_f32(void);

  void finish_zbf16_to_f32(void);

  uint64_t zbf16_to_f32_set_flags(uint64_t);

  void startup_zencdec_forwards(void);

  void finish_zencdec_forwards(void);

  uint64_t zencdec_forwards_infallible(struct zinstruction);

  void startup_zencdec_forwards_infallible(void);

  void finish_zencdec_forwards_infallible(void);

  void startup_zencdec_backwards(void);

  void finish_zencdec_backwards(void);

  void zencdec_backwards_infallible(struct zinstruction *rop, uint64_t);

  void startup_zencdec_backwards_infallible(void);

  void finish_zencdec_backwards_infallible(void);

  void zencdec_compressed_backwards_infallible(struct zinstruction *rop, uint64_t);

  void startup_zexecute(void);

  void finish_zexecute(void);

  void startup_zassembly_forwards(void);

  void finish_zassembly_forwards(void);

  void zassembly_forwards_infallible(sail_string *rop, struct zinstruction);

  void startup_zassembly_forwards_infallible(void);

  void finish_zassembly_forwards_infallible(void);

  void startup_zassembly_forwards_matches(void);

  void finish_zassembly_forwards_matches(void);

  void zinstruction_to_str(sail_string *rop, struct zinstruction);

  void startup_zinstruction_to_str(void);

  void finish_zinstruction_to_str(void);

  void zcsr_name_map_forwards_infallible(sail_string *rop, uint64_t);

  void startup_zcsr_name_map_backwards(void);

  void finish_zcsr_name_map_backwards(void);

  uint64_t zcsr_name_map_backwards_infallible(const_sail_string);

  void startup_zcsr_name_map_backwards_infallible(void);

  void finish_zcsr_name_map_backwards_infallible(void);

  void startup_zis_CSR_accessible(void);

  void finish_zis_CSR_accessible(void);

  void startup_zread_CSR(void);

  void finish_zread_CSR(void);

  void startup_zwrite_CSR(void);

  void finish_zwrite_CSR(void);

  bool zhart_is_active(struct zHartState);

  bool zhart_is_waiting(struct zHartState);

  void zext_fetch_hook(struct zFetchResult *rop, struct zFetchResult);

  void zext_decode_compressed(struct zinstruction *rop, uint64_t);

  void zext_decode(struct zinstruction *rop, uint64_t);

  void zrvfi_fetch(struct zFetchResult *rop, unit);

  void startup_zrvfi_fetch(void);

  void finish_zrvfi_fetch(void);

  bool zisRVC(uint64_t);

  void zfetch_bytes(struct zFetchBytes_Result *rop, sbits, sbits, int64_t);

  void startup_zfetch_bytes(void);

  void finish_zfetch_bytes(void);

  void zfetch(struct zFetchResult *rop, unit);

  void startup_zfetch(void);

  void finish_zfetch(void);

  bool zallows_transformed_instruction(struct zExceptionType);

  void ztransformed_instruction(struct zoptionzIbzK *rop, struct zinstruction);

  void startup_ztransformed_instruction(void);

  void finish_ztransformed_instruction(void);

  void ztransform_exception_context(struct zExceptionContext *rop, struct zExceptionContext, struct zinstr_info);

  void startup_ztransform_exception_context(void);

  void finish_ztransform_exception_context(void);

  void zrun_hart_waiting(struct zStep *rop, sail_int, enum zWaitReason, struct zinstr_info, bool);

  void startup_zrun_hart_waiting(void);

  void finish_zrun_hart_waiting(void);

  void zrun_hart_active(struct zStep *rop, sail_int);

  void startup_zrun_hart_active(void);

  void finish_zrun_hart_active(void);

  unit zhandle_pending_trigger(struct ztuple_z8z5enumz0zzTrig_ActionzCz0z5i64zCz0z5sbv64z9);

  void startup_zhandle_pending_trigger(void);

  void finish_zhandle_pending_trigger(void);

  bool zwait_is_nop(enum zWaitReason);

  bool ztry_step(sail_int, bool);

  void startup_ztry_step(void);

  void finish_ztry_step(void);

  void zloop(sail_int *rop, unit);

  void startup_zloop(void);

  void finish_zloop(void);

  bool zcheck_privs(unit);

  bool zcheck_tvecs(unit);

  bool zrequire_Sv32(const_sail_string);

  bool zcheck_mutable_misa(unit);

  bool zrequire_Sv39(const_sail_string);

  bool zcheck_sha_dependency(const_sail_string, bool);

  bool zcheck_shgatpa_mode(const_sail_string, bool, bool);

  bool zcheck_shvsatpa_mode(const_sail_string, bool, bool);

  bool zrequire_virtual_memory(const_sail_string);

  bool zcheck_mmu_config(unit);

  void startup_zcheck_mmu_config(void);

  void finish_zcheck_mmu_config(void);

  bool zcheck_vlen_elen(unit);

  void startup_zcheck_vlen_elen(void);

  void finish_zcheck_vlen_elen(void);

  bool zcheck_vext_config(unit);

  void startup_zcheck_vext_config(void);

  void finish_zcheck_vext_config(void);

  bool zcheck_pma_region(struct zPMA_Region);

  void startup_zcheck_pma_region(void);

  void finish_zcheck_pma_region(void);

  bool zcheck_pma_regions(zz5listz8z5structz0zzPMA_Regionz9, uint64_t, uint64_t, struct zpma_check_opts, bool);

  bool zwithin_configured_pma_memory(const_sail_string, struct zoptionzIEMemoryRegionTypez5zK, uint64_t, uint64_t);

  void startup_zwithin_configured_pma_memory(void);

  void finish_zwithin_configured_pma_memory(void);

  bool zcheck_mem_layout(unit);

  void startup_zcheck_mem_layout(void);

  void finish_zcheck_mem_layout(void);

  bool zcheck_pmp(unit);

  void startup_zcheck_pmp(void);

  void finish_zcheck_pmp(void);

  bool zcheck_required_xtval_option(const_sail_string, const_sail_string, bool);

  uint64_t zreserved_exception_mask(unit);

  bool zcheck_misc_extension_dependencies(unit);

  void startup_zcheck_misc_extension_dependencies(void);

  void finish_zcheck_misc_extension_dependencies(void);

  bool zcheck_extension_param_constraints(unit);

  void startup_zcheck_extension_param_constraints(void);

  void finish_zcheck_extension_param_constraints(void);

  bool zcheck_stateen_bit_feature(const_sail_string, enum zCSRBitConfig, bool);

  bool zcheck_stateen_config(unit);

  bool zcheck_mmio_devices(unit);

  void startup_zcheck_mmio_devices(void);

  void finish_zcheck_mmio_devices(void);

  bool zcheck_mstatus_fields(unit);

  bool zcheck_physaddr_bits(unit);

  void startup_zcheck_physaddr_bits(void);

  void finish_zcheck_physaddr_bits(void);

  bool zcheck_version_constraints(unit);

  bool zcheck_platform_constraints(unit);

  bool zconfig_is_valid(unit);

  void zext_wrap(sail_string *rop, enum zextension, enum zISA_Format);

  void startup_zext_wrap(void);

  void finish_zext_wrap(void);

  void zgenerate_isa_string(sail_string *rop, enum zISA_Format);

  void startup_zgenerate_isa_string(void);

  void finish_zgenerate_isa_string(void);

  void zgenerate_canonical_isa_string(sail_string *rop, unit);

  unit zreset(unit);

  unit zinit_model(const_sail_string);

  unit ztest_mstatus_sxl_uxl_reset_values(unit);

  void startup_ztest_mstatus_sxl_uxl_reset_values(void);

  void finish_ztest_mstatus_sxl_uxl_reset_values(void);

  unit zmain(unit);

  void startup_zmain(void);

  void finish_zmain(void);

  unit zoracle_init(unit);

  void startup_zoracle_init(void);

  void finish_zoracle_init(void);

  uint64_t zoracle_xlen(unit);

  void startup_zoracle_xlen(void);

  void finish_zoracle_xlen(void);

  uint64_t zoracle_flen(unit);

  void startup_zoracle_flen(void);

  void finish_zoracle_flen(void);

  uint64_t zoracle_vlen(unit);

  void startup_zoracle_vlen(void);

  void finish_zoracle_vlen(void);

  uint64_t zoracle_elen(unit);

  void startup_zoracle_elen(void);

  void finish_zoracle_elen(void);

  bool zoracle_has_fregs(unit);

  bool zoracle_has_vregs(unit);

  uint64_t zoracle_get_x(uint64_t);

  void startup_zoracle_get_x(void);

  void finish_zoracle_get_x(void);

  unit zoracle_set_x(uint64_t, uint64_t);

  void startup_zoracle_set_x(void);

  void finish_zoracle_set_x(void);

  uint64_t zoracle_get_pc(unit);

  void startup_zoracle_get_pc(void);

  void finish_zoracle_get_pc(void);

  unit zoracle_set_pc(uint64_t);

  void startup_zoracle_set_pc(void);

  void finish_zoracle_set_pc(void);

  uint64_t zoracle_get_f(uint64_t);

  void startup_zoracle_get_f(void);

  void finish_zoracle_get_f(void);

  unit zoracle_set_f(uint64_t, uint64_t);

  void startup_zoracle_set_f(void);

  void finish_zoracle_set_f(void);

  uint64_t zoracle_get_fcsr(unit);

  void startup_zoracle_get_fcsr(void);

  void finish_zoracle_get_fcsr(void);

  unit zoracle_set_fcsr(uint64_t);

  uint64_t zoracle_get_v_chunk(uint64_t, uint64_t);

  void startup_zoracle_get_v_chunk(void);

  void finish_zoracle_get_v_chunk(void);

  unit zoracle_set_v_chunk(uint64_t, uint64_t, uint64_t);

  void startup_zoracle_set_v_chunk(void);

  void finish_zoracle_set_v_chunk(void);

  uint64_t zoracle_get_vl(unit);

  void startup_zoracle_get_vl(void);

  void finish_zoracle_get_vl(void);

  unit zoracle_set_vl(uint64_t);

  void startup_zoracle_set_vl(void);

  void finish_zoracle_set_vl(void);

  uint64_t zoracle_get_vtype(unit);

  void startup_zoracle_get_vtype(void);

  void finish_zoracle_get_vtype(void);

  unit zoracle_set_vtype(uint64_t);

  void startup_zoracle_set_vtype(void);

  void finish_zoracle_set_vtype(void);

  uint64_t zoracle_get_vstart(unit);

  void startup_zoracle_get_vstart(void);

  void finish_zoracle_get_vstart(void);

  unit zoracle_set_vstart(uint64_t);

  void startup_zoracle_set_vstart(void);

  void finish_zoracle_set_vstart(void);

  uint64_t zoracle_get_vcsr(unit);

  void startup_zoracle_get_vcsr(void);

  void finish_zoracle_get_vcsr(void);

  unit zoracle_set_vcsr(uint64_t);

  uint64_t zoracle_get_priv(unit);

  void startup_zoracle_get_priv(void);

  void finish_zoracle_get_priv(void);

  unit zoracle_set_priv(uint64_t);

  bool zoracle_csr_readable(uint64_t);

  uint64_t zoracle_read_csr(uint64_t);

  void startup_zoracle_read_csr(void);

  void finish_zoracle_read_csr(void);

  bool zoracle_write_csr(uint64_t, uint64_t);

  void startup_zoracle_write_csr(void);

  void finish_zoracle_write_csr(void);

  unit zinitializze_registers(unit);

  void startup_zinitializze_registers(void);

  void finish_zinitializze_registers(void);

  Model();

  ~Model();

  Model(const Model&) = delete;

  int64_t abstract_zxlen = {};

  int64_t abstract_zvmidlen = {};

  int64_t abstract_zvlen_exp = {};

  int64_t abstract_zsdtrig_mcontrol6_maskmax = {};

  int64_t abstract_zplat_hpmevent_width_bits = {};

  int64_t abstract_zplat_hpmcounter_width_bits = {};

  int64_t abstract_zphysaddr_bits = {};

  int64_t abstract_znum_triggers = {};

  int64_t abstract_zgeilen = {};

  bool abstract_zext_d_supported = {};

  struct zexception *current_exception = NULL;

  bool have_exception = false;

  sail_string *throw_location = NULL;

  int64_t abstract_zelen_exp = {};

  bool abstract_zbase_E_enabled = {};

  int64_t abstract_zasidlen = {};

  uint64_t zfp_eflag_none = {};


  uint64_t zfp_eflag_invalid = {};


  uint64_t zfp_eflag_divide_by_zzero = {};


  uint64_t zfp_eflag_oveflow = {};


  uint64_t zfp_eflag_underflow = {};


  uint64_t zfp_eflag_inexact = {};


  uint64_t zfp_eflag_overflow_and_inexact = {};


  uint64_t zfp_rounding_rne = {};


  uint64_t zfp_rounding_rna = {};


  uint64_t zfp_rounding_rdn = {};


  uint64_t zfp_rounding_rup = {};


  uint64_t zfp_rounding_rtzz = {};


  uint64_t zfp_rounding_default = {};


  // register zz50zE1088
  bool z0zE1088 = {};

  // register zz50zE1089
  bool z0zE1089 = {};

  // register zz50zE1086
  bool z0zE1086 = {};

  // register zz50zE1087
  bool z0zE1087 = {};

  // register zz50zE1084
  bool z0zE1084 = {};

  // register zz50zE1085
  bool z0zE1085 = {};

  // register zz50zE1082
  bool z0zE1082 = {};

  // register zz50zE1083
  bool z0zE1083 = {};

  // register zz50zE1080
  bool z0zE1080 = {};

  // register zz50zE1081
  bool z0zE1081 = {};

  // register zz50zE1078
  bool z0zE1078 = {};

  // register zz50zE1079
  bool z0zE1079 = {};

  // register zz50zE0
  bool z0zE0 = {};

  // register zz50zE1
  enum zPrivileged_ISA_Version z0zE1 = {};

  enum zPrivileged_ISA_Version zpriv_isa_version = {};


  bool zpte_reserved_bits_must_be_zzero = {};


  bool zxenvcfg_csrs_are_defined = {};


  bool zmconfigptr_is_defined = {};


  bool zmseccfg_csrs_are_defined = {};


  bool zmstatush_is_defined = {};


  bool zdelegh_csrs_are_defined = {};


  int64_t zlog2_xlen = {};


  int64_t zxlen_bytes = {};


  int64_t zxlen = {};


  int64_t zgpalen = {};


  int64_t zasidmax = {};


  int64_t zvmidmax = {};


  int64_t zasidlen = {};


  int64_t zvmidlen = {};


  int64_t zgeilen = {};


  int64_t zflen_bytes = {};


  int64_t zflen = {};


  // register zz50zE2
  bool z0zE2 = {};

  // register zz50zE3
  enum zvector_support z0zE3 = {};

  enum zvector_support zvector_support_level = {};


  int64_t zvlen_exp = {};


  int64_t zelen_exp = {};


  int64_t zvlen = {};


  int64_t zelen = {};


  int64_t zphysaddrbits_len = {};


  int64_t zphysaddr_bits = {};


  unit zdefault_meta = {};


  // register zrvfi_instruction
  struct zRVFI_DII_Instruction_Packet zrvfi_instruction = {};

  // register zrvfi_inst_data
  struct zRVFI_DII_Execution_Packet_InstMetaData zrvfi_inst_data = {};

  // register zrvfi_pc_data
  struct zRVFI_DII_Execution_Packet_PC zrvfi_pc_data = {};

  // register zrvfi_int_data
  struct zRVFI_DII_Execution_Packet_Ext_Integer zrvfi_int_data = {};

  // register zrvfi_int_data_present
  bool zrvfi_int_data_present = {};

  // register zrvfi_mem_data
  struct zRVFI_DII_Execution_Packet_Ext_MemAccess zrvfi_mem_data = {};

  // register zrvfi_mem_data_present
  bool zrvfi_mem_data_present = {};

  // register zz50zE4
  bool z0zE4 = {};

  // register zz50zE5
  bool z0zE5 = {};

  bool zplat_have_mcountinhibit = {};


  // register zz50zE6
  bool z0zE6 = {};

  // register zz50zE7
  uint64_t z0zE7 = {};

  uint64_t zplat_mcountinhibit_writable_bits = {};


  // register zz50zE8
  bool z0zE8 = {};

  // register zz50zE9
  bool z0zE9 = {};

  bool zplat_mtvec_direct_mode_supported = {};


  // register zz50zE10
  bool z0zE10 = {};

  // register zz50zE11
  bool z0zE11 = {};

  bool zplat_mtvec_vectored_mode_supported = {};


  // register zz50zE12
  bool z0zE12 = {};

  // register zz50zE13
  bool z0zE13 = {};

  bool zplat_stvec_direct_mode_supported = {};


  // register zz50zE14
  bool z0zE14 = {};

  // register zz50zE15
  bool z0zE15 = {};

  bool zplat_stvec_vectored_mode_supported = {};


  // register zz50zE16
  bool z0zE16 = {};

  // register zz50zE17
  bool z0zE17 = {};

  bool zplat_vstvec_direct_mode_supported = {};


  // register zz50zE18
  bool z0zE18 = {};

  // register zz50zE19
  bool z0zE19 = {};

  bool zplat_vstvec_vectored_mode_supported = {};


  // register zz50zE20
  bool z0zE20 = {};

  // register zz50zE21
  int64_t z0zE21 = {};

  int64_t zplat_mtvec_direct_base_alignment_exp = {};


  // register zz50zE22
  bool z0zE22 = {};

  // register zz50zE23
  int64_t z0zE23 = {};

  int64_t zplat_mtvec_vectored_base_alignment_exp = {};


  // register zz50zE24
  bool z0zE24 = {};

  // register zz50zE25
  int64_t z0zE25 = {};

  int64_t zplat_stvec_vectored_base_alignment_exp = {};


  // register zz50zE26
  bool z0zE26 = {};

  // register zz50zE27
  int64_t z0zE27 = {};

  int64_t zplat_vstvec_vectored_base_alignment_exp = {};


  // register zz50zE28
  bool z0zE28 = {};

  // register zz50zE29
  uint64_t z0zE29 = {};

  uint64_t zplat_medeleg_delegatable_bits = {};


  // register zz50zE30
  bool z0zE30 = {};

  // register zz50zE31
  sbits z0zE31 = {};

  sbits zplat_mideleg_delegatable_bits = {};


  // register zz50zE32
  bool z0zE32 = {};

  // register zz50zE33
  bool z0zE33 = {};

  bool zplat_hedeleg_zzero_writable = {};


  // register zz50zE34
  bool z0zE34 = {};

  // register zz50zE35
  int64_t z0zE35 = {};

  int64_t zplat_cache_block_sizze_exp = {};


  // register zz50zE36
  bool z0zE36 = {};

  // register zz50zE37
  int64_t z0zE37 = {};

  int64_t zplat_reservation_set_sizze_exp = {};


  // register zz50zE38
  bool z0zE38 = {};

  // register zz50zE39
  bool z0zE39 = {};

  bool zplat_reservation_require_exact_addr_match = {};


  // register zz50zE40
  bool z0zE40 = {};

  // register zz50zE41
  bool z0zE41 = {};

  bool zplat_reservation_invalidate_on_same_hart_store = {};


  // register zz50zE42
  bool z0zE42 = {};

  // register zz50zE43
  struct zGlobalMisalignedExceptions z0zE43 = {};

  struct zGlobalMisalignedExceptions zplat_misaligned_access = {};


  // register zz50zE44
  bool z0zE44 = {};

  // register zz50zE45
  enum zCSRBitConfig z0zE45 = {};

  enum zCSRBitConfig zmstateen0_se0 = {};


  // register zz50zE46
  bool z0zE46 = {};

  // register zz50zE47
  enum zCSRBitConfig z0zE47 = {};

  enum zCSRBitConfig zmstateen0_envcfg = {};


  // register zz50zE48
  bool z0zE48 = {};

  // register zz50zE49
  enum zCSRBitConfig z0zE49 = {};

  enum zCSRBitConfig zmstateen0_context = {};


  // register zz50zE50
  bool z0zE50 = {};

  // register zz50zE51
  enum zCSRBitConfig z0zE51 = {};

  enum zCSRBitConfig zmstateen0_p1p13 = {};


  // register zz50zE52
  bool z0zE52 = {};

  // register zz50zE53
  enum zCSRBitConfig z0zE53 = {};

  enum zCSRBitConfig zmstateen0_srmcfg = {};


  // register zz50zE54
  bool z0zE54 = {};

  // register zz50zE55
  enum zCSRBitConfig z0zE55 = {};

  enum zCSRBitConfig zmstateen0_fcsr = {};


  // register zz50zE56
  bool z0zE56 = {};

  // register zz50zE57
  enum zCSRBitConfig z0zE57 = {};

  enum zCSRBitConfig zmstateen0_c = {};


  // register zz50zE58
  bool z0zE58 = {};

  // register zz50zE59
  enum zCSRBitConfig z0zE59 = {};

  enum zCSRBitConfig zmstateen1_se1 = {};


  // register zz50zE60
  bool z0zE60 = {};

  // register zz50zE61
  enum zCSRBitConfig z0zE61 = {};

  enum zCSRBitConfig zmstateen2_se2 = {};


  // register zz50zE62
  bool z0zE62 = {};

  // register zz50zE63
  enum zCSRBitConfig z0zE63 = {};

  enum zCSRBitConfig zmstateen3_se3 = {};


  // register zz50zE64
  bool z0zE64 = {};

  // register zz50zE65
  enum zCSRBitConfig z0zE65 = {};

  enum zCSRBitConfig zhstateen0_envcfg = {};


  // register zz50zE66
  bool z0zE66 = {};

  // register zz50zE67
  enum zCSRBitConfig z0zE67 = {};

  enum zCSRBitConfig zhstateen0_context = {};


  // register zz50zE68
  bool z0zE68 = {};

  // register zz50zE69
  enum zCSRBitConfig z0zE69 = {};

  enum zCSRBitConfig zhstateen0_fcsr = {};


  // register zz50zE70
  bool z0zE70 = {};

  // register zz50zE71
  enum zCSRBitConfig z0zE71 = {};

  enum zCSRBitConfig zhstateen0_c = {};


  // register zz50zE72
  bool z0zE72 = {};

  // register zz50zE73
  enum zCSRBitConfig z0zE73 = {};

  enum zCSRBitConfig zsstateen0_fcsr = {};


  // register zz50zE74
  bool z0zE74 = {};

  // register zz50zE75
  enum zCSRBitConfig z0zE75 = {};

  enum zCSRBitConfig zsstateen0_c = {};


  // register zz50zE76
  bool z0zE76 = {};

  // register zz50zE77
  enum zExtContextPolicy z0zE77 = {};

  enum zExtContextPolicy zplat_mstatus_legal_fs = {};


  // register zz50zE78
  bool z0zE78 = {};

  // register zz50zE79
  enum zExtContextPolicy z0zE79 = {};

  enum zExtContextPolicy zplat_mstatus_legal_vs = {};


  int64_t zplat_hpmcounter_width_bits = {};


  int64_t zplat_hpmevent_width_bits = {};


  // register zz50zE80
  bool z0zE80 = {};

  // register zz50zE81
  bool z0zE81 = {};

  bool zplat_hpmcounter_increments_in_self_hpmevent_write = {};


  // register zz50zE82
  bool z0zE82 = {};

  // register zz50zE83
  bool z0zE83 = {};

  bool zplat_have_clint = {};


  // register zz50zE84
  bool z0zE84 = {};

  // register zz50zE85
  sail_int z0zE85 = {};

  sbits zplat_clint_base = {};


  // register zz50zE86
  bool z0zE86 = {};

  // register zz50zE87
  sail_int z0zE87 = {};

  sbits zplat_clint_sizze = {};


  // register zz50zE88
  bool z0zE88 = {};

  // register zz50zE89
  bool z0zE89 = {};

  bool zplat_have_sig = {};


  // register zz50zE90
  bool z0zE90 = {};

  // register zz50zE91
  sail_int z0zE91 = {};

  sbits zplat_sig_base = {};


  sbits zplat_sig_sizze = {};


  // register zz50zE92
  bool z0zE92 = {};

  // register zz50zE93
  struct zoptionzIbzK z0zE93 = {};

  struct zoptionzIbzK zplat_invalid_physical_address = {};


  // register zz50zE94
  bool z0zE94 = {};

  // register zz50zE95
  sail_int z0zE95 = {};

  sail_int zplat_insns_per_tick = {};


  // register zz50zE96
  bool z0zE96 = {};

  // register zz50zE97
  bool z0zE97 = {};

  bool zplat_wfi_available_to_usermode = {};


  // register zz50zE98
  bool z0zE98 = {};

  // register zz50zE99
  sail_int z0zE99 = {};

  sail_int zmax_wait_time = {};


  // register zz50zE100
  bool z0zE100 = {};

  // register zz50zE101
  bool z0zE101 = {};

  bool zplat_has_msi = {};


  // register zz50zE102
  bool z0zE102 = {};

  // register zz50zE103
  bool z0zE103 = {};

  bool zplat_has_mti = {};


  // register zz50zE104
  bool z0zE104 = {};

  // register zz50zE105
  bool z0zE105 = {};

  bool zplat_has_mei = {};


  // register zz50zE106
  bool z0zE106 = {};

  // register zz50zE107
  bool z0zE107 = {};

  bool zplat_has_ssi = {};


  // register zz50zE108
  bool z0zE108 = {};

  // register zz50zE109
  bool z0zE109 = {};

  bool zplat_has_sti = {};


  // register zz50zE110
  bool z0zE110 = {};

  // register zz50zE111
  bool z0zE111 = {};

  bool zplat_has_sei = {};


  // register zz50zE112
  bool z0zE112 = {};

  // register zz50zE113
  bool z0zE113 = {};

  bool zillegal_instruction_writes_xtval = {};


  // register zz50zE114
  bool z0zE114 = {};

  // register zz50zE115
  bool z0zE115 = {};

  bool zvirtual_instruction_writes_xtval = {};


  // register zz50zE116
  bool z0zE116 = {};

  // register zz50zE117
  bool z0zE117 = {};

  bool zsoftware_breakpoint_writes_xtval = {};


  // register zz50zE118
  bool z0zE118 = {};

  // register zz50zE119
  bool z0zE119 = {};

  bool zhardware_breakpoint_writes_xtval = {};


  // register zz50zE120
  bool z0zE120 = {};

  // register zz50zE121
  bool z0zE121 = {};

  bool zmisaligned_load_writes_xtval = {};


  // register zz50zE122
  bool z0zE122 = {};

  // register zz50zE123
  bool z0zE123 = {};

  bool zload_access_fault_writes_xtval = {};


  // register zz50zE124
  bool z0zE124 = {};

  // register zz50zE125
  bool z0zE125 = {};

  bool zload_page_fault_writes_xtval = {};


  // register zz50zE126
  bool z0zE126 = {};

  // register zz50zE127
  bool z0zE127 = {};

  bool zload_guest_page_fault_writes_xtval = {};


  // register zz50zE128
  bool z0zE128 = {};

  // register zz50zE129
  bool z0zE129 = {};

  bool zmisaligned_samo_writes_xtval = {};


  // register zz50zE130
  bool z0zE130 = {};

  // register zz50zE131
  bool z0zE131 = {};

  bool zsamo_access_fault_writes_xtval = {};


  // register zz50zE132
  bool z0zE132 = {};

  // register zz50zE133
  bool z0zE133 = {};

  bool zsamo_page_fault_writes_xtval = {};


  // register zz50zE134
  bool z0zE134 = {};

  // register zz50zE135
  bool z0zE135 = {};

  bool zsamo_guest_page_fault_writes_xtval = {};


  // register zz50zE136
  bool z0zE136 = {};

  // register zz50zE137
  bool z0zE137 = {};

  bool zmisaligned_fetch_writes_xtval = {};


  // register zz50zE138
  bool z0zE138 = {};

  // register zz50zE139
  bool z0zE139 = {};

  bool zfetch_access_fault_writes_xtval = {};


  // register zz50zE140
  bool z0zE140 = {};

  // register zz50zE141
  bool z0zE141 = {};

  bool zfetch_page_fault_writes_xtval = {};


  // register zz50zE142
  bool z0zE142 = {};

  // register zz50zE143
  bool z0zE143 = {};

  bool zfetch_guest_page_fault_writes_xtval = {};


  // register zz50zE144
  bool z0zE144 = {};

  // register zz50zE145
  bool z0zE145 = {};

  bool zsoftware_check_exception_writes_xtval = {};


  // register zz50zE146
  bool z0zE146 = {};

  // register zz50zE147
  bool z0zE147 = {};

  bool zhardware_error_exception_writes_xtval = {};


  // register zz50zE148
  bool z0zE148 = {};

  // register zz50zE149
  bool z0zE149 = {};

  bool zreserved_exceptions_write_xtval = {};


  // register zz50zE150
  bool z0zE150 = {};

  // register zz50zE151
  bool z0zE151 = {};

  bool zsdtrig_has_icount = {};


  // register zz50zE152
  bool z0zE152 = {};

  // register zz50zE153
  bool z0zE153 = {};

  bool zsdtrig_has_etrigger = {};


  // register zz50zE154
  bool z0zE154 = {};

  // register zz50zE155
  bool z0zE155 = {};

  bool zsdtrig_has_itrigger = {};


  // register zz50zE156
  bool z0zE156 = {};

  // register zz50zE157
  bool z0zE157 = {};

  bool zsdtrig_has_mcontrol6 = {};


  int64_t zsdtrig_mcontrol6_maskmax = {};


  // register zz50zE158
  bool z0zE158 = {};

  // register zz50zE159
  sail_int z0zE159 = {};

  sail_int zsdtrig_max_chain_limit = {};


  // register zz50zE160
  bool z0zE160 = {};

  // register zz50zE161
  bool z0zE161 = {};

  bool zsdtrig_has_mcontext = {};


  // register zz50zE162
  bool z0zE162 = {};

  // register zz50zE163
  bool z0zE163 = {};

  bool zsdtrig_has_hcontext = {};


  // register zz50zE164
  bool z0zE164 = {};

  // register zz50zE165
  bool z0zE165 = {};

  bool zsdtrig_has_scontext = {};


  int64_t znum_triggers = {};


  // register zz50zE166
  bool z0zE166 = {};

  // register zz50zE167
  enum zSdtrig_breakpoint_reentrancy z0zE167 = {};

  enum zSdtrig_breakpoint_reentrancy zsdtrig_breakpoint_reentrancy = {};


  bool zsdtrig_has_tcontrol = {};


  // register zz50zE168
  bool z0zE168 = {};

  // register zz50zE169
  enum zAmocasOddRegisterReservedBehavior z0zE169 = {};

  enum zAmocasOddRegisterReservedBehavior zamocas_odd_register_reserved_behavior = {};


  // register zz50zE170
  bool z0zE170 = {};

  // register zz50zE171
  enum zFcsrRmReservedBehavior z0zE171 = {};

  enum zFcsrRmReservedBehavior zfcsr_rm_reserved_behavior = {};


  // register zz50zE172
  bool z0zE172 = {};

  // register zz50zE173
  enum zPmpWriteOnlyReservedBehavior z0zE173 = {};

  enum zPmpWriteOnlyReservedBehavior zpmp_write_only_reserved_behavior = {};


  // register zz50zE174
  bool z0zE174 = {};

  // register zz50zE175
  enum zXenvcfgCbieReservedBehavior z0zE175 = {};

  enum zXenvcfgCbieReservedBehavior zxenvcfg_cbie_reserved_behavior = {};


  // register zz50zE176
  bool z0zE176 = {};

  // register zz50zE177
  enum zXtvecModeReservedBehavior z0zE177 = {};

  enum zXtvecModeReservedBehavior zxtvec_mode_reserved_behavior = {};


  // register zz50zE178
  bool z0zE178 = {};

  // register zz50zE179
  enum zRV32ZdinxOddRegisterReservedBehavior z0zE179 = {};

  enum zRV32ZdinxOddRegisterReservedBehavior zrv32zzdinx_odd_register_reserved_behavior = {};


  // register zz50zE180
  bool z0zE180 = {};

  // register zz50zE181
  enum zIllegalVtypeReservedBehavior z0zE181 = {};

  enum zIllegalVtypeReservedBehavior zillegal_vtype_reserved_behavior = {};


  // register zz50zE182
  bool z0zE182 = {};

  // register zz50zE183
  enum zOOBVstartReservedBehavior z0zE183 = {};

  enum zOOBVstartReservedBehavior zvstart_reserved_behavior = {};


  // register zz50zE184
  bool z0zE184 = {};

  // register zz50zE185
  enum zFflagsDirtyPolicy z0zE185 = {};

  enum zFflagsDirtyPolicy zfflags_dirty_policy = {};


  // register zz50zE1076
  bool z0zE1076 = {};

  // register zz50zE1077
  bool z0zE1077 = {};

  // register zz50zE1074
  bool z0zE1074 = {};

  // register zz50zE1075
  bool z0zE1075 = {};

  // register zz50zE1072
  bool z0zE1072 = {};

  // register zz50zE1073
  bool z0zE1073 = {};

  // register zz50zE1070
  bool z0zE1070 = {};

  // register zz50zE1071
  bool z0zE1071 = {};

  // register zz50zE1068
  bool z0zE1068 = {};

  // register zz50zE1069
  bool z0zE1069 = {};

  // register zz50zE1066
  bool z0zE1066 = {};

  // register zz50zE1067
  bool z0zE1067 = {};

  // register zz50zE1064
  bool z0zE1064 = {};

  // register zz50zE1065
  bool z0zE1065 = {};

  // register zz50zE1062
  bool z0zE1062 = {};

  // register zz50zE1063
  bool z0zE1063 = {};

  // register zz50zE1060
  bool z0zE1060 = {};

  // register zz50zE1061
  bool z0zE1061 = {};

  // register zz50zE1058
  bool z0zE1058 = {};

  // register zz50zE1059
  bool z0zE1059 = {};

  // register zz50zE1056
  bool z0zE1056 = {};

  // register zz50zE1057
  bool z0zE1057 = {};

  // register zz50zE1054
  bool z0zE1054 = {};

  // register zz50zE1055
  bool z0zE1055 = {};

  // register zz50zE1052
  bool z0zE1052 = {};

  // register zz50zE1053
  bool z0zE1053 = {};

  // register zz50zE1050
  bool z0zE1050 = {};

  // register zz50zE1051
  bool z0zE1051 = {};

  // register zz50zE1048
  bool z0zE1048 = {};

  // register zz50zE1049
  bool z0zE1049 = {};

  // register zz50zE1046
  bool z0zE1046 = {};

  // register zz50zE1047
  bool z0zE1047 = {};

  // register zz50zE1044
  bool z0zE1044 = {};

  // register zz50zE1045
  bool z0zE1045 = {};

  // register zz50zE1042
  bool z0zE1042 = {};

  // register zz50zE1043
  bool z0zE1043 = {};

  // register zz50zE1040
  bool z0zE1040 = {};

  // register zz50zE1041
  bool z0zE1041 = {};

  // register zz50zE1038
  bool z0zE1038 = {};

  // register zz50zE1039
  bool z0zE1039 = {};

  // register zz50zE1036
  bool z0zE1036 = {};

  // register zz50zE1037
  bool z0zE1037 = {};

  // register zz50zE1034
  bool z0zE1034 = {};

  // register zz50zE1035
  bool z0zE1035 = {};

  // register zz50zE1032
  bool z0zE1032 = {};

  // register zz50zE1033
  bool z0zE1033 = {};

  // register zz50zE1030
  bool z0zE1030 = {};

  // register zz50zE1031
  bool z0zE1031 = {};

  // register zz50zE1028
  bool z0zE1028 = {};

  // register zz50zE1029
  bool z0zE1029 = {};

  // register zz50zE1026
  bool z0zE1026 = {};

  // register zz50zE1027
  bool z0zE1027 = {};

  // register zz50zE1024
  bool z0zE1024 = {};

  // register zz50zE1025
  bool z0zE1025 = {};

  // register zz50zE1022
  bool z0zE1022 = {};

  // register zz50zE1023
  bool z0zE1023 = {};

  // register zz50zE1020
  bool z0zE1020 = {};

  // register zz50zE1021
  bool z0zE1021 = {};

  // register zz50zE1018
  bool z0zE1018 = {};

  // register zz50zE1019
  bool z0zE1019 = {};

  // register zz50zE1016
  bool z0zE1016 = {};

  // register zz50zE1017
  bool z0zE1017 = {};

  // register zz50zE1014
  bool z0zE1014 = {};

  // register zz50zE1015
  bool z0zE1015 = {};

  // register zz50zE1012
  bool z0zE1012 = {};

  // register zz50zE1013
  bool z0zE1013 = {};

  // register zz50zE1010
  bool z0zE1010 = {};

  // register zz50zE1011
  bool z0zE1011 = {};

  // register zz50zE1008
  bool z0zE1008 = {};

  // register zz50zE1009
  bool z0zE1009 = {};

  // register zz50zE1006
  bool z0zE1006 = {};

  // register zz50zE1007
  bool z0zE1007 = {};

  // register zz50zE1004
  bool z0zE1004 = {};

  // register zz50zE1005
  bool z0zE1005 = {};

  // register zz50zE1000
  bool z0zE1000 = {};

  // register zz50zE1001
  bool z0zE1001 = {};

  // register zz50zE1002
  bool z0zE1002 = {};

  // register zz50zE1003
  bool z0zE1003 = {};

  // register zz50zE996
  bool z0zE996 = {};

  // register zz50zE997
  bool z0zE997 = {};

  // register zz50zE998
  bool z0zE998 = {};

  // register zz50zE999
  bool z0zE999 = {};

  // register zz50zE994
  bool z0zE994 = {};

  // register zz50zE995
  bool z0zE995 = {};

  // register zz50zE992
  bool z0zE992 = {};

  // register zz50zE993
  bool z0zE993 = {};

  // register zz50zE990
  bool z0zE990 = {};

  // register zz50zE991
  bool z0zE991 = {};

  // register zz50zE988
  bool z0zE988 = {};

  // register zz50zE989
  bool z0zE989 = {};

  // register zz50zE986
  bool z0zE986 = {};

  // register zz50zE987
  bool z0zE987 = {};

  // register zz50zE984
  bool z0zE984 = {};

  // register zz50zE985
  bool z0zE985 = {};

  // register zz50zE982
  bool z0zE982 = {};

  // register zz50zE983
  bool z0zE983 = {};

  // register zz50zE980
  bool z0zE980 = {};

  // register zz50zE981
  bool z0zE981 = {};

  // register zz50zE978
  bool z0zE978 = {};

  // register zz50zE979
  bool z0zE979 = {};

  // register zz50zE976
  bool z0zE976 = {};

  // register zz50zE977
  bool z0zE977 = {};

  // register zz50zE974
  bool z0zE974 = {};

  // register zz50zE975
  bool z0zE975 = {};

  // register zz50zE972
  bool z0zE972 = {};

  // register zz50zE973
  bool z0zE973 = {};

  // register zz50zE970
  bool z0zE970 = {};

  // register zz50zE971
  bool z0zE971 = {};

  // register zz50zE968
  bool z0zE968 = {};

  // register zz50zE969
  bool z0zE969 = {};

  // register zz50zE966
  bool z0zE966 = {};

  // register zz50zE967
  bool z0zE967 = {};

  // register zz50zE964
  bool z0zE964 = {};

  // register zz50zE965
  bool z0zE965 = {};

  // register zz50zE962
  bool z0zE962 = {};

  // register zz50zE963
  bool z0zE963 = {};

  // register zz50zE960
  bool z0zE960 = {};

  // register zz50zE961
  bool z0zE961 = {};

  // register zz50zE958
  bool z0zE958 = {};

  // register zz50zE959
  bool z0zE959 = {};

  // register zz50zE956
  bool z0zE956 = {};

  // register zz50zE957
  bool z0zE957 = {};

  // register zz50zE954
  bool z0zE954 = {};

  // register zz50zE955
  bool z0zE955 = {};

  // register zz50zE952
  bool z0zE952 = {};

  // register zz50zE953
  bool z0zE953 = {};

  // register zz50zE950
  bool z0zE950 = {};

  // register zz50zE951
  bool z0zE951 = {};

  // register zz50zE948
  bool z0zE948 = {};

  // register zz50zE949
  bool z0zE949 = {};

  // register zz50zE946
  bool z0zE946 = {};

  // register zz50zE947
  bool z0zE947 = {};

  // register zz50zE944
  bool z0zE944 = {};

  // register zz50zE945
  bool z0zE945 = {};

  // register zz50zE942
  bool z0zE942 = {};

  // register zz50zE943
  bool z0zE943 = {};

  // register zz50zE940
  bool z0zE940 = {};

  // register zz50zE941
  bool z0zE941 = {};

  // register zz50zE938
  bool z0zE938 = {};

  // register zz50zE939
  bool z0zE939 = {};

  // register zz50zE936
  bool z0zE936 = {};

  // register zz50zE937
  bool z0zE937 = {};

  // register zz50zE934
  bool z0zE934 = {};

  // register zz50zE935
  bool z0zE935 = {};

  // register zz50zE932
  bool z0zE932 = {};

  // register zz50zE933
  bool z0zE933 = {};

  // register zz50zE930
  bool z0zE930 = {};

  // register zz50zE931
  bool z0zE931 = {};

  // register zz50zE928
  bool z0zE928 = {};

  // register zz50zE929
  bool z0zE929 = {};

  // register zz50zE926
  bool z0zE926 = {};

  // register zz50zE927
  bool z0zE927 = {};

  // register zz50zE924
  bool z0zE924 = {};

  // register zz50zE925
  bool z0zE925 = {};

  // register zz50zE922
  bool z0zE922 = {};

  // register zz50zE923
  bool z0zE923 = {};

  // register zz50zE920
  bool z0zE920 = {};

  // register zz50zE921
  bool z0zE921 = {};

  // register zz50zE918
  bool z0zE918 = {};

  // register zz50zE919
  bool z0zE919 = {};

  // register zz50zE916
  bool z0zE916 = {};

  // register zz50zE917
  bool z0zE917 = {};

  // register zz50zE914
  bool z0zE914 = {};

  // register zz50zE915
  bool z0zE915 = {};

  // register zz50zE912
  bool z0zE912 = {};

  // register zz50zE913
  bool z0zE913 = {};

  // register zz50zE910
  bool z0zE910 = {};

  // register zz50zE911
  bool z0zE911 = {};

  // register zz50zE908
  bool z0zE908 = {};

  // register zz50zE909
  bool z0zE909 = {};

  // register zz50zE906
  bool z0zE906 = {};

  // register zz50zE907
  bool z0zE907 = {};

  // register zz50zE904
  bool z0zE904 = {};

  // register zz50zE905
  bool z0zE905 = {};

  // register zz50zE902
  bool z0zE902 = {};

  // register zz50zE903
  bool z0zE903 = {};

  // register zz50zE900
  bool z0zE900 = {};

  // register zz50zE901
  bool z0zE901 = {};

  // register zz50zE898
  bool z0zE898 = {};

  // register zz50zE899
  bool z0zE899 = {};

  // register zz50zE896
  bool z0zE896 = {};

  // register zz50zE897
  bool z0zE897 = {};

  // register zz50zE894
  bool z0zE894 = {};

  // register zz50zE895
  bool z0zE895 = {};

  // register zz50zE892
  bool z0zE892 = {};

  // register zz50zE893
  bool z0zE893 = {};

  // register zz50zE890
  bool z0zE890 = {};

  // register zz50zE891
  bool z0zE891 = {};

  // register zz50zE888
  bool z0zE888 = {};

  // register zz50zE889
  bool z0zE889 = {};

  // register zz50zE886
  bool z0zE886 = {};

  // register zz50zE887
  bool z0zE887 = {};

  // register zz50zE884
  bool z0zE884 = {};

  // register zz50zE885
  bool z0zE885 = {};

  // register zz50zE882
  bool z0zE882 = {};

  // register zz50zE883
  bool z0zE883 = {};

  // register zz50zE880
  bool z0zE880 = {};

  // register zz50zE881
  bool z0zE881 = {};

  // register zz50zE878
  bool z0zE878 = {};

  // register zz50zE879
  bool z0zE879 = {};

  // register zz50zE876
  bool z0zE876 = {};

  // register zz50zE877
  bool z0zE877 = {};

  // register zz50zE874
  bool z0zE874 = {};

  // register zz50zE875
  bool z0zE875 = {};

  // register zz50zE872
  bool z0zE872 = {};

  // register zz50zE873
  bool z0zE873 = {};

  // register zz50zE870
  bool z0zE870 = {};

  // register zz50zE871
  bool z0zE871 = {};

  // register zz50zE868
  bool z0zE868 = {};

  // register zz50zE869
  bool z0zE869 = {};

  // register zz50zE866
  bool z0zE866 = {};

  // register zz50zE867
  bool z0zE867 = {};

  // register zz50zE864
  bool z0zE864 = {};

  // register zz50zE865
  bool z0zE865 = {};

  // register zz50zE862
  bool z0zE862 = {};

  // register zz50zE863
  bool z0zE863 = {};

  // register zz50zE860
  bool z0zE860 = {};

  // register zz50zE861
  bool z0zE861 = {};

  // register zz50zE858
  bool z0zE858 = {};

  // register zz50zE859
  bool z0zE859 = {};

  // register zz50zE856
  bool z0zE856 = {};

  // register zz50zE857
  bool z0zE857 = {};

  // register zz50zE854
  bool z0zE854 = {};

  // register zz50zE855
  bool z0zE855 = {};

  // register zz50zE852
  bool z0zE852 = {};

  // register zz50zE853
  bool z0zE853 = {};

  // register zz50zE850
  bool z0zE850 = {};

  // register zz50zE851
  bool z0zE851 = {};

  // register zz50zE848
  bool z0zE848 = {};

  // register zz50zE849
  bool z0zE849 = {};

  // register zz50zE846
  bool z0zE846 = {};

  // register zz50zE847
  bool z0zE847 = {};

  // register zz50zE844
  bool z0zE844 = {};

  // register zz50zE845
  bool z0zE845 = {};

  // register zz50zE842
  bool z0zE842 = {};

  // register zz50zE843
  bool z0zE843 = {};

  zz5vecz8z5enumz0zzextensionz9 zextensions_ordered_for_isa_string = {};


  unit zinit_ext_ptw = {};


  int64_t zpagesizze_bits = {};


  bool zbase_E_enabled = {};


  int64_t zregidx_bit_width = {};


  sbits zzzreg = {};


  sbits zra = {};


  sbits zsp = {};


  sbits zt0 = {};


  bool z__monomorphizze_reads = {};


  bool z__monomorphizze_writes = {};


  sbits zzzero_reg = {};


  // register zPC
  sbits zPC = {};

  // register znextPC
  sbits znextPC = {};

  // register zx1
  sbits zx1 = {};

  // register zx2
  sbits zx2 = {};

  // register zx3
  sbits zx3 = {};

  // register zx4
  sbits zx4 = {};

  // register zx5
  sbits zx5 = {};

  // register zx6
  sbits zx6 = {};

  // register zx7
  sbits zx7 = {};

  // register zx8
  sbits zx8 = {};

  // register zx9
  sbits zx9 = {};

  // register zx10
  sbits zx10 = {};

  // register zx11
  sbits zx11 = {};

  // register zx12
  sbits zx12 = {};

  // register zx13
  sbits zx13 = {};

  // register zx14
  sbits zx14 = {};

  // register zx15
  sbits zx15 = {};

  // register zx16
  sbits zx16 = {};

  // register zx17
  sbits zx17 = {};

  // register zx18
  sbits zx18 = {};

  // register zx19
  sbits zx19 = {};

  // register zx20
  sbits zx20 = {};

  // register zx21
  sbits zx21 = {};

  // register zx22
  sbits zx22 = {};

  // register zx23
  sbits zx23 = {};

  // register zx24
  sbits zx24 = {};

  // register zx25
  sbits zx25 = {};

  // register zx26
  sbits zx26 = {};

  // register zx27
  sbits zx27 = {};

  // register zx28
  sbits zx28 = {};

  // register zx29
  sbits zx29 = {};

  // register zx30
  sbits zx30 = {};

  // register zx31
  sbits zx31 = {};

  // register zcur_privilege
  enum zPrivilege zcur_privilege = {};

  // register zcur_inst
  sbits zcur_inst = {};

  // register zmisa
  struct zMisa zmisa = {};

  // register zz50zE186
  bool z0zE186 = {};

  // register zz50zE187
  bool z0zE187 = {};

  bool zsys_enable_writable_fiom = {};


  // register zz50zE188
  bool z0zE188 = {};

  // register zz50zE189
  bool z0zE189 = {};

  bool zsys_hgatp_sv32x4_supported = {};


  // register zz50zE190
  bool z0zE190 = {};

  // register zz50zE191
  bool z0zE191 = {};

  bool zsys_hgatp_sv39x4_supported = {};


  // register zz50zE192
  bool z0zE192 = {};

  // register zz50zE193
  bool z0zE193 = {};

  bool zsys_hgatp_sv48x4_supported = {};


  // register zz50zE194
  bool z0zE194 = {};

  // register zz50zE195
  bool z0zE195 = {};

  bool zsys_hgatp_sv57x4_supported = {};


  // register zz50zE196
  bool z0zE196 = {};

  // register zz50zE197
  bool z0zE197 = {};

  bool zsys_vsatp_sv32_supported = {};


  // register zz50zE198
  bool z0zE198 = {};

  // register zz50zE199
  bool z0zE199 = {};

  bool zsys_vsatp_sv39_supported = {};


  // register zz50zE200
  bool z0zE200 = {};

  // register zz50zE201
  bool z0zE201 = {};

  bool zsys_vsatp_sv48_supported = {};


  // register zz50zE202
  bool z0zE202 = {};

  // register zz50zE203
  bool z0zE203 = {};

  bool zsys_vsatp_sv57_supported = {};


  // register zz50zE204
  bool z0zE204 = {};

  // register zz50zE205
  bool z0zE205 = {};

  bool zsys_misaligned_load_writes_tinst = {};


  // register zz50zE206
  bool z0zE206 = {};

  // register zz50zE207
  bool z0zE207 = {};

  bool zsys_load_access_fault_writes_tinst = {};


  // register zz50zE208
  bool z0zE208 = {};

  // register zz50zE209
  bool z0zE209 = {};

  bool zsys_load_page_fault_writes_tinst = {};


  // register zz50zE210
  bool z0zE210 = {};

  // register zz50zE211
  bool z0zE211 = {};

  bool zsys_load_guest_page_fault_writes_tinst = {};


  // register zz50zE212
  bool z0zE212 = {};

  // register zz50zE213
  bool z0zE213 = {};

  bool zsys_misaligned_samo_writes_tinst = {};


  // register zz50zE214
  bool z0zE214 = {};

  // register zz50zE215
  bool z0zE215 = {};

  bool zsys_samo_access_fault_writes_tinst = {};


  // register zz50zE216
  bool z0zE216 = {};

  // register zz50zE217
  bool z0zE217 = {};

  bool zsys_samo_page_fault_writes_tinst = {};


  // register zz50zE218
  bool z0zE218 = {};

  // register zz50zE219
  bool z0zE219 = {};

  bool zsys_samo_guest_page_fault_writes_tinst = {};


  // register zz50zE220
  bool z0zE220 = {};

  // register zz50zE221
  bool z0zE221 = {};

  bool zsys_guest_page_fault_writes_htval = {};


  // register zz50zE222
  bool z0zE222 = {};

  // register zz50zE223
  bool z0zE223 = {};

  bool zsys_implicit_vs_pte_access_sets_gstage_d = {};


  // register zz50zE224
  bool z0zE224 = {};

  // register zz50zE225
  uint64_t z0zE225 = {};

  uint64_t zsys_writable_hpm_counters = {};


  // register zz50zE822
  bool z0zE822 = {};

  // register zz50zE823
  bool z0zE823 = {};

  // register zz50zE824
  bool z0zE824 = {};

  // register zz50zE825
  bool z0zE825 = {};

  // register zz50zE826
  bool z0zE826 = {};

  // register zz50zE827
  bool z0zE827 = {};

  // register zz50zE828
  bool z0zE828 = {};

  // register zz50zE829
  bool z0zE829 = {};

  // register zz50zE830
  bool z0zE830 = {};

  // register zz50zE831
  bool z0zE831 = {};

  // register zz50zE832
  bool z0zE832 = {};

  // register zz50zE833
  bool z0zE833 = {};

  // register zz50zE834
  bool z0zE834 = {};

  // register zz50zE835
  bool z0zE835 = {};

  // register zz50zE836
  bool z0zE836 = {};

  // register zz50zE837
  bool z0zE837 = {};

  // register zz50zE838
  bool z0zE838 = {};

  // register zz50zE839
  bool z0zE839 = {};

  // register zz50zE840
  bool z0zE840 = {};

  // register zz50zE841
  bool z0zE841 = {};

  // register zmstatus
  struct zMstatus zmstatus = {};

  // register zhstatus
  struct zHstatus zhstatus = {};

  // register zz50zE818
  bool z0zE818 = {};

  // register zz50zE819
  bool z0zE819 = {};

  // register zz50zE820
  bool z0zE820 = {};

  // register zz50zE821
  bool z0zE821 = {};

  // register zmseccfg
  struct zSeccfg zmseccfg = {};

  // register zmenvcfg
  struct zMEnvcfg zmenvcfg = {};

  // register zsenvcfg
  struct zSEnvcfg zsenvcfg = {};

  // register zhenvcfg
  struct zHEnvcfg zhenvcfg = {};

  // register zmtvec
  struct zMtvec zmtvec = {};

  // register zmcause
  struct zMcause zmcause = {};

  // register zmepc
  sbits zmepc = {};

  // register zmtval
  sbits zmtval = {};

  // register zmscratch
  sbits zmscratch = {};

  // register zz50zE226
  bool z0zE226 = {};

  // register zz50zE227
  uint64_t z0zE227 = {};

  uint64_t zsys_scounteren_writable_bits = {};


  // register zscounteren
  struct zCounteren zscounteren = {};

  // register zz50zE228
  bool z0zE228 = {};

  // register zz50zE229
  uint64_t z0zE229 = {};

  uint64_t zsys_hcounteren_writable_bits = {};


  // register zhcounteren
  struct zCounteren zhcounteren = {};

  // register zz50zE230
  bool z0zE230 = {};

  // register zz50zE231
  uint64_t z0zE231 = {};

  uint64_t zsys_mcounteren_writable_bits = {};


  // register zmcounteren
  struct zCounteren zmcounteren = {};

  // register zmcountinhibit
  struct zCounterin zmcountinhibit = {};

  // register zmcycle
  uint64_t zmcycle = {};

  // register zminstret
  uint64_t zminstret = {};

  // register zminstret_increment
  bool zminstret_increment = {};

  // register zz50zE232
  bool z0zE232 = {};

  // register zz50zE233
  sail_int z0zE233 = {};

  // register zmvendorid
  uint64_t zmvendorid = {};

  // register zz50zE234
  bool z0zE234 = {};

  // register zz50zE235
  sail_int z0zE235 = {};

  // register zmimpid
  sbits zmimpid = {};

  // register zz50zE236
  bool z0zE236 = {};

  // register zz50zE237
  sail_int z0zE237 = {};

  // register zmarchid
  sbits zmarchid = {};

  // register zz50zE238
  bool z0zE238 = {};

  // register zz50zE239
  sail_int z0zE239 = {};

  // register zmhartid
  sbits zmhartid = {};

  // register zmconfigptr
  sbits zmconfigptr = {};

  // register zmtinst
  sbits zmtinst = {};

  // register zmtval2
  sbits zmtval2 = {};

  // register zhtimedelta
  uint64_t zhtimedelta = {};

  // register zhtval
  sbits zhtval = {};

  // register zhtinst
  sbits zhtinst = {};

  // register zvsstatus
  struct zMstatus zvsstatus = {};

  // register zvstvec
  struct zMtvec zvstvec = {};

  // register zvsscratch
  sbits zvsscratch = {};

  // register zvsepc
  sbits zvsepc = {};

  // register zvscause
  struct zMcause zvscause = {};

  // register zvstval
  sbits zvstval = {};

  // register zstvec
  struct zMtvec zstvec = {};

  // register zsscratch
  sbits zsscratch = {};

  // register zsepc
  sbits zsepc = {};

  // register zscause
  struct zMcause zscause = {};

  // register zstval
  sbits zstval = {};

  // register zhgatp
  sbits zhgatp = {};

  // register zsatp
  sbits zsatp = {};

  // register zvsatp
  sbits zvsatp = {};

  // register zz50zE240
  bool z0zE240 = {};

  // register zz50zE241
  zz5listz8z5structz0zzevent_selectorz9 z0zE241 = {};

  zz5listz8z5structz0zzevent_selectorz9 zplatform_event_selectors = {};


  // register zstimecmp
  uint64_t zstimecmp = {};

  // register zvstimecmp
  uint64_t zvstimecmp = {};

  sbits zhgei_mask = {};


  // register zhgeie
  sbits zhgeie = {};

  // register zhvip
  struct zMinterrupts zhvip = {};

  // register zmie
  struct zMinterrupts zmie = {};

  // register zmip
  struct zMinterrupts zmip = {};

  // register zmedeleg
  struct zMedeleg zmedeleg = {};

  // register zmideleg
  struct zMinterrupts zmideleg = {};

  // register zhedeleg
  struct zMedeleg zhedeleg = {};

  // register zhideleg
  struct zMinterrupts zhideleg = {};

  // register zvsie
  sbits zvsie = {};

  // register zvsip
  sbits zvsip = {};

  // register zmhpmevent
  zz5vecz8z5bv64z9 zmhpmevent = {};

  // register zmhpmcounter
  zz5vecz8z5bv64z9 zmhpmcounter = {};

  // register zwritten_event_index
  struct zoptionzIz8izCEevent_csrz5z9zK zwritten_event_index = {};

  // register zz50zE242
  bool z0zE242 = {};

  // register zz50zE243
  int64_t z0zE243 = {};

  int64_t zsys_pmp_count = {};


  // register zz50zE244
  bool z0zE244 = {};

  // register zz50zE245
  int64_t z0zE245 = {};

  int64_t zsys_pmp_usable_count = {};


  // register zz50zE246
  bool z0zE246 = {};

  // register zz50zE247
  int64_t z0zE247 = {};

  int64_t zsys_pmp_grain = {};


  // register zpmpcfg_n
  zz5vecz8z5structz0zzPmpcfg_entz9 zpmpcfg_n = {};

  // register zpmpaddr_n
  zz5vecz8z5sbv64z9 zpmpaddr_n = {};

  // register zz50zE816
  bool z0zE816 = {};

  // register zz50zE817
  bool z0zE817 = {};

  // register zz50zE814
  bool z0zE814 = {};

  // register zz50zE815
  bool z0zE815 = {};

  // register zz50zE812
  bool z0zE812 = {};

  // register zz50zE813
  bool z0zE813 = {};

  // register zmstateen0
  struct zMstateen0 zmstateen0 = {};

  // register zmstateen1
  struct zMstateen1 zmstateen1 = {};

  // register zmstateen2
  struct zMstateen2 zmstateen2 = {};

  // register zmstateen3
  struct zMstateen3 zmstateen3 = {};

  // register zhstateen0
  struct zHstateen0 zhstateen0 = {};

  // register zhstateen1
  struct zHstateen1 zhstateen1 = {};

  // register zhstateen2
  struct zHstateen2 zhstateen2 = {};

  // register zhstateen3
  struct zHstateen3 zhstateen3 = {};

  // register zsstateen0
  struct zSstateen0 zsstateen0 = {};

  // register zsstateen1
  struct zSstateen1 zsstateen1 = {};

  // register zsstateen2
  struct zSstateen2 zsstateen2 = {};

  // register zsstateen3
  struct zSstateen3 zsstateen3 = {};

  sbits zzzero_freg = {};


  uint64_t zcanonical_NaN_BF16 = {};


  // register zf0
  sbits zf0 = {};

  // register zf1
  sbits zf1 = {};

  // register zf2
  sbits zf2 = {};

  // register zf3
  sbits zf3 = {};

  // register zf4
  sbits zf4 = {};

  // register zf5
  sbits zf5 = {};

  // register zf6
  sbits zf6 = {};

  // register zf7
  sbits zf7 = {};

  // register zf8
  sbits zf8 = {};

  // register zf9
  sbits zf9 = {};

  // register zf10
  sbits zf10 = {};

  // register zf11
  sbits zf11 = {};

  // register zf12
  sbits zf12 = {};

  // register zf13
  sbits zf13 = {};

  // register zf14
  sbits zf14 = {};

  // register zf15
  sbits zf15 = {};

  // register zf16
  sbits zf16 = {};

  // register zf17
  sbits zf17 = {};

  // register zf18
  sbits zf18 = {};

  // register zf19
  sbits zf19 = {};

  // register zf20
  sbits zf20 = {};

  // register zf21
  sbits zf21 = {};

  // register zf22
  sbits zf22 = {};

  // register zf23
  sbits zf23 = {};

  // register zf24
  sbits zf24 = {};

  // register zf25
  sbits zf25 = {};

  // register zf26
  sbits zf26 = {};

  // register zf27
  sbits zf27 = {};

  // register zf28
  sbits zf28 = {};

  // register zf29
  sbits zf29 = {};

  // register zf30
  sbits zf30 = {};

  // register zf31
  sbits zf31 = {};

  // register zfcsr
  struct zFcsr zfcsr = {};

  uint64_t zzzvreg = {};


  // register zvr0
  lbits zvr0 = {};

  // register zvr1
  lbits zvr1 = {};

  // register zvr2
  lbits zvr2 = {};

  // register zvr3
  lbits zvr3 = {};

  // register zvr4
  lbits zvr4 = {};

  // register zvr5
  lbits zvr5 = {};

  // register zvr6
  lbits zvr6 = {};

  // register zvr7
  lbits zvr7 = {};

  // register zvr8
  lbits zvr8 = {};

  // register zvr9
  lbits zvr9 = {};

  // register zvr10
  lbits zvr10 = {};

  // register zvr11
  lbits zvr11 = {};

  // register zvr12
  lbits zvr12 = {};

  // register zvr13
  lbits zvr13 = {};

  // register zvr14
  lbits zvr14 = {};

  // register zvr15
  lbits zvr15 = {};

  // register zvr16
  lbits zvr16 = {};

  // register zvr17
  lbits zvr17 = {};

  // register zvr18
  lbits zvr18 = {};

  // register zvr19
  lbits zvr19 = {};

  // register zvr20
  lbits zvr20 = {};

  // register zvr21
  lbits zvr21 = {};

  // register zvr22
  lbits zvr22 = {};

  // register zvr23
  lbits zvr23 = {};

  // register zvr24
  lbits zvr24 = {};

  // register zvr25
  lbits zvr25 = {};

  // register zvr26
  lbits zvr26 = {};

  // register zvr27
  lbits zvr27 = {};

  // register zvr28
  lbits zvr28 = {};

  // register zvr29
  lbits zvr29 = {};

  // register zvr30
  lbits zvr30 = {};

  // register zvr31
  lbits zvr31 = {};

  // register zvstart
  sbits zvstart = {};

  // register zvl
  sbits zvl = {};

  sbits zVLENB = {};


  // register zvtype
  struct zVtype zvtype = {};

  // register zvcsr
  struct zVcsr zvcsr = {};

  // register zz50zE248
  bool z0zE248 = {};

  // register zz50zE249
  sail_int z0zE249 = {};

  sail_int zmax_index_eew_exp = {};


  zz5vecz8z5bv8z9 zsm4_sbox_table = {};


  zz5vecz8z5bv8z9 zaes_sbox_fwd_table = {};


  zz5vecz8z5bv8z9 zaes_sbox_inv_table = {};


  zz5vecz8z5bv32z9 zzzvksed_ck = {};


  // register zmcyclecfg
  struct zCountSmcntrpmf zmcyclecfg = {};

  // register zminstretcfg
  struct zCountSmcntrpmf zminstretcfg = {};

  // register zz50zE250
  bool z0zE250 = {};

  // register zz50zE251
  bool z0zE251 = {};

  bool zmhselect_mcontext_match = {};


  // register zz50zE252
  bool z0zE252 = {};

  // register zz50zE253
  bool z0zE253 = {};

  bool zmhselect_vmid_match = {};


  // register zz50zE254
  bool z0zE254 = {};

  // register zz50zE255
  bool z0zE255 = {};

  bool zsselect_scontext_match = {};


  // register zz50zE256
  bool z0zE256 = {};

  // register zz50zE257
  bool z0zE257 = {};

  bool zsselect_asid_match = {};


  // register zz50zE258
  bool z0zE258 = {};

  // register zz50zE259
  int64_t z0zE259 = {};

  int64_t zsdtrig_mhvalue_len = {};


  // register zz50zE260
  bool z0zE260 = {};

  // register zz50zE261
  int64_t z0zE261 = {};

  int64_t zsdtrig_svalue_len = {};


  // register zz50zE262
  bool z0zE262 = {};

  // register zz50zE263
  bool z0zE263 = {};

  bool zicount_count_is_hardwired_one = {};


  // register zz50zE264
  bool z0zE264 = {};

  // register zz50zE265
  bool z0zE265 = {};

  bool zicount_self_write_sets_pending = {};


  struct zTrigger ztrig_reset_val = {};


  // register zz50zE266
  bool z0zE266 = {};

  // register zz50zE267
  sbits z0zE267 = {};

  sbits zsupported_etrigger_mask = {};


  // register zz50zE268
  bool z0zE268 = {};

  // register zz50zE269
  sbits z0zE269 = {};

  sbits zsupported_itrigger_mask = {};


  // register ztriggers
  zz5vecz8z5unionz0zzTriggerz9 ztriggers = {};

  // register ztselect
  sbits ztselect = {};

  // register zwritten_trigger_index
  struct zoptionzIz8izCEtdataz5z9zK zwritten_trigger_index = {};

  // register ztcontrol
  struct zTControl ztcontrol = {};

  // register zscontext
  struct zSContext zscontext = {};

  // register zmcontext
  struct zMContext zmcontext = {};

  // register zz50zE270
  bool z0zE270 = {};

  // register zz50zE271
  bool z0zE271 = {};

  bool zaddress_select_matches_all = {};


  // register zelp
  uint64_t zelp = {};

  // register zsig_msip
  uint64_t zsig_msip = {};

  // register zsig_meip
  uint64_t zsig_meip = {};

  // register zsig_seip
  uint64_t zsig_seip = {};

  // register zsig_ssip
  uint64_t zsig_ssip = {};

  // register zsig_hgeip
  sbits zsig_hgeip = {};

  // register zpc_reset_address
  sbits zpc_reset_address = {};

  // register zz50zE808
  bool z0zE808 = {};

  // register zz50zE809
  bool z0zE809 = {};

  // register zz50zE810
  bool z0zE810 = {};

  // register zz50zE811
  bool z0zE811 = {};

  int64_t zSIG_VERSION_OFFSET = {};


  int64_t zSIG_PLATFORM_OFFSET = {};


  int64_t zSIG_GUEST_OFFSET = {};


  // register zhtif_tohost_base
  struct zoptionzIbzK zhtif_tohost_base = {};

  int64_t zhtif_tohost_sizze = {};


  // register zmsip
  uint64_t zmsip = {};

  // register zmtimecmp
  uint64_t zmtimecmp = {};

  // register zmtime
  uint64_t zmtime = {};

  sbits zMSIP_BASE = {};


  sbits zMTIMECMP_BASE = {};


  sbits zMTIMECMP_BASE_HI = {};


  sbits zMTIME_BASE = {};


  sbits zMTIME_BASE_HI = {};


  // register zhtif_tohost
  uint64_t zhtif_tohost = {};

  // register zhtif_done
  bool zhtif_done = {};

  // register zhtif_exit_code
  uint64_t zhtif_exit_code = {};

  // register zhtif_cmd_write
  uint64_t zhtif_cmd_write = {};

  // register zhtif_payload_writes
  uint64_t zhtif_payload_writes = {};

  // register zz50zE272
  bool z0zE272 = {};

  // register zz50zE273
  int64_t z0zE273 = {};

  int64_t zsys_misaligned_allowed_within_exp = {};


  // register zz50zE274
  bool z0zE274 = {};

  // register zz50zE275
  bool z0zE275 = {};

  bool zsys_misaligned_order_decreasing = {};


  // register zz50zE276
  bool z0zE276 = {};

  // register zz50zE277
  bool z0zE277 = {};

  bool zsys_misaligned_byte_by_byte = {};


  // register zz50zE278
  bool z0zE278 = {};

  // register zz50zE279
  zz5listz8z5structz0zzPMA_Regionz9 z0zE279 = {};

  // register zpma_regions
  zz5listz8z5structz0zzPMA_Regionz9 zpma_regions = {};

  uint64_t zdefault_sv32_ext_pte = {};


  int64_t ztlb_vpn_bits = {};


  int64_t ztlb_ppn_bits = {};


  int64_t znum_tlb_entries_exp = {};


  // register ztlb
  zz5vecz8z5unionz0zzoptionzzIRTLB_EntryzzKz9 ztlb = {};

  struct zExecutionResult zRETIRE_SUCCESS = {};


  // register zz50zE280
  bool z0zE280 = {};

  // register zz50zE281
  bool z0zE281 = {};

  bool zvstart_arith_zzero_required = {};


  // register zz50zE282
  bool z0zE282 = {};

  // register zz50zE283
  bool z0zE283 = {};

  bool zvstart_scalar_move_zzero_required = {};


  // register zz50zE284
  bool z0zE284 = {};

  // register zz50zE285
  bool z0zE285 = {};

  bool zvl_use_ceil = {};


  // register zssp
  sbits zssp = {};

  // register zz50zE286
  bool z0zE286 = {};

  // register zz50zE287
  int64_t z0zE287 = {};

  int64_t zrcidlen = {};


  // register zz50zE288
  bool z0zE288 = {};

  // register zz50zE289
  int64_t z0zE289 = {};

  int64_t zmcidlen = {};


  // register zsrmcfg
  struct zSrmcfg zsrmcfg = {};

  // register zz50zE804
  bool z0zE804 = {};

  // register zz50zE805
  bool z0zE805 = {};

  // register zz50zE806
  bool z0zE806 = {};

  // register zz50zE807
  bool z0zE807 = {};

  // register zz50zE800
  bool z0zE800 = {};

  // register zz50zE801
  bool z0zE801 = {};

  // register zz50zE802
  bool z0zE802 = {};

  // register zz50zE803
  bool z0zE803 = {};

  // register zhart_state
  struct zHartState zhart_state = {};

  // register zz50zE798
  bool z0zE798 = {};

  // register zz50zE799
  bool z0zE799 = {};

  // register zz50zE796
  bool z0zE796 = {};

  // register zz50zE797
  bool z0zE797 = {};

  // register zz50zE794
  bool z0zE794 = {};

  // register zz50zE795
  bool z0zE795 = {};

  // register zz50zE790
  bool z0zE790 = {};

  // register zz50zE791
  bool z0zE791 = {};

  // register zz50zE792
  bool z0zE792 = {};

  // register zz50zE793
  bool z0zE793 = {};

  // register zz50zE774
  bool z0zE774 = {};

  // register zz50zE775
  bool z0zE775 = {};

  // register zz50zE776
  bool z0zE776 = {};

  // register zz50zE777
  bool z0zE777 = {};

  // register zz50zE778
  bool z0zE778 = {};

  // register zz50zE779
  bool z0zE779 = {};

  // register zz50zE780
  bool z0zE780 = {};

  // register zz50zE781
  bool z0zE781 = {};

  // register zz50zE782
  bool z0zE782 = {};

  // register zz50zE783
  bool z0zE783 = {};

  // register zz50zE784
  bool z0zE784 = {};

  // register zz50zE785
  bool z0zE785 = {};

  // register zz50zE786
  bool z0zE786 = {};

  // register zz50zE787
  bool z0zE787 = {};

  // register zz50zE788
  bool z0zE788 = {};

  // register zz50zE789
  bool z0zE789 = {};

  // register zz50zE772
  bool z0zE772 = {};

  // register zz50zE773
  bool z0zE773 = {};

  // register zz50zE752
  bool z0zE752 = {};

  // register zz50zE753
  bool z0zE753 = {};

  // register zz50zE754
  bool z0zE754 = {};

  // register zz50zE755
  bool z0zE755 = {};

  // register zz50zE756
  bool z0zE756 = {};

  // register zz50zE757
  bool z0zE757 = {};

  // register zz50zE758
  bool z0zE758 = {};

  // register zz50zE759
  bool z0zE759 = {};

  // register zz50zE760
  bool z0zE760 = {};

  // register zz50zE761
  bool z0zE761 = {};

  // register zz50zE762
  bool z0zE762 = {};

  // register zz50zE763
  bool z0zE763 = {};

  // register zz50zE764
  bool z0zE764 = {};

  // register zz50zE765
  bool z0zE765 = {};

  // register zz50zE766
  bool z0zE766 = {};

  // register zz50zE767
  bool z0zE767 = {};

  // register zz50zE768
  bool z0zE768 = {};

  // register zz50zE769
  bool z0zE769 = {};

  // register zz50zE770
  bool z0zE770 = {};

  // register zz50zE771
  bool z0zE771 = {};

  // register zz50zE750
  bool z0zE750 = {};

  // register zz50zE751
  bool z0zE751 = {};

  // register zz50zE716
  bool z0zE716 = {};

  // register zz50zE717
  bool z0zE717 = {};

  // register zz50zE718
  bool z0zE718 = {};

  // register zz50zE719
  bool z0zE719 = {};

  // register zz50zE720
  bool z0zE720 = {};

  // register zz50zE721
  bool z0zE721 = {};

  // register zz50zE722
  bool z0zE722 = {};

  // register zz50zE723
  bool z0zE723 = {};

  // register zz50zE724
  bool z0zE724 = {};

  // register zz50zE725
  bool z0zE725 = {};

  // register zz50zE726
  bool z0zE726 = {};

  // register zz50zE727
  bool z0zE727 = {};

  // register zz50zE728
  bool z0zE728 = {};

  // register zz50zE729
  bool z0zE729 = {};

  // register zz50zE730
  bool z0zE730 = {};

  // register zz50zE731
  bool z0zE731 = {};

  // register zz50zE732
  bool z0zE732 = {};

  // register zz50zE733
  bool z0zE733 = {};

  // register zz50zE734
  bool z0zE734 = {};

  // register zz50zE735
  bool z0zE735 = {};

  // register zz50zE736
  bool z0zE736 = {};

  // register zz50zE737
  bool z0zE737 = {};

  // register zz50zE738
  bool z0zE738 = {};

  // register zz50zE739
  bool z0zE739 = {};

  // register zz50zE740
  bool z0zE740 = {};

  // register zz50zE741
  bool z0zE741 = {};

  // register zz50zE742
  bool z0zE742 = {};

  // register zz50zE743
  bool z0zE743 = {};

  // register zz50zE744
  bool z0zE744 = {};

  // register zz50zE745
  bool z0zE745 = {};

  // register zz50zE698
  bool z0zE698 = {};

  // register zz50zE699
  bool z0zE699 = {};

  // register zz50zE700
  bool z0zE700 = {};

  // register zz50zE701
  bool z0zE701 = {};

  // register zz50zE702
  bool z0zE702 = {};

  // register zz50zE703
  bool z0zE703 = {};

  // register zz50zE704
  bool z0zE704 = {};

  // register zz50zE705
  bool z0zE705 = {};

  // register zz50zE706
  bool z0zE706 = {};

  // register zz50zE707
  bool z0zE707 = {};

  // register zz50zE708
  bool z0zE708 = {};

  // register zz50zE709
  bool z0zE709 = {};

  // register zz50zE710
  bool z0zE710 = {};

  // register zz50zE711
  bool z0zE711 = {};

  // register zz50zE712
  bool z0zE712 = {};

  // register zz50zE713
  bool z0zE713 = {};

  // register zz50zE714
  bool z0zE714 = {};

  // register zz50zE715
  bool z0zE715 = {};

  // register zz50zE682
  bool z0zE682 = {};

  // register zz50zE683
  bool z0zE683 = {};

  // register zz50zE684
  bool z0zE684 = {};

  // register zz50zE685
  bool z0zE685 = {};

  // register zz50zE686
  bool z0zE686 = {};

  // register zz50zE687
  bool z0zE687 = {};

  // register zz50zE688
  bool z0zE688 = {};

  // register zz50zE689
  bool z0zE689 = {};

  // register zz50zE690
  bool z0zE690 = {};

  // register zz50zE691
  bool z0zE691 = {};

  // register zz50zE692
  bool z0zE692 = {};

  // register zz50zE693
  bool z0zE693 = {};

  // register zz50zE694
  bool z0zE694 = {};

  // register zz50zE695
  bool z0zE695 = {};

  // register zz50zE696
  bool z0zE696 = {};

  // register zz50zE697
  bool z0zE697 = {};

  // register zz50zE746
  bool z0zE746 = {};

  // register zz50zE747
  bool z0zE747 = {};

  // register zz50zE748
  bool z0zE748 = {};

  // register zz50zE749
  bool z0zE749 = {};

  // register zz50zE648
  bool z0zE648 = {};

  // register zz50zE649
  sail_int z0zE649 = {};

  // register zz50zE650
  bool z0zE650 = {};

  // register zz50zE651
  bool z0zE651 = {};

  // register zz50zE652
  bool z0zE652 = {};

  // register zz50zE653
  bool z0zE653 = {};

  // register zz50zE654
  bool z0zE654 = {};

  // register zz50zE655
  bool z0zE655 = {};

  // register zz50zE656
  bool z0zE656 = {};

  // register zz50zE657
  bool z0zE657 = {};

  // register zz50zE658
  bool z0zE658 = {};

  // register zz50zE659
  bool z0zE659 = {};

  // register zz50zE660
  bool z0zE660 = {};

  // register zz50zE661
  bool z0zE661 = {};

  // register zz50zE662
  bool z0zE662 = {};

  // register zz50zE663
  bool z0zE663 = {};

  // register zz50zE664
  bool z0zE664 = {};

  // register zz50zE665
  bool z0zE665 = {};

  // register zz50zE666
  bool z0zE666 = {};

  // register zz50zE667
  bool z0zE667 = {};

  // register zz50zE668
  bool z0zE668 = {};

  // register zz50zE669
  bool z0zE669 = {};

  // register zz50zE670
  bool z0zE670 = {};

  // register zz50zE671
  bool z0zE671 = {};

  // register zz50zE672
  bool z0zE672 = {};

  // register zz50zE673
  bool z0zE673 = {};

  // register zz50zE674
  bool z0zE674 = {};

  // register zz50zE675
  bool z0zE675 = {};

  // register zz50zE676
  bool z0zE676 = {};

  // register zz50zE677
  bool z0zE677 = {};

  // register zz50zE678
  bool z0zE678 = {};

  // register zz50zE679
  bool z0zE679 = {};

  // register zz50zE680
  bool z0zE680 = {};

  // register zz50zE681
  bool z0zE681 = {};

  // register zz50zE620
  bool z0zE620 = {};

  // register zz50zE621
  bool z0zE621 = {};

  // register zz50zE622
  bool z0zE622 = {};

  // register zz50zE623
  bool z0zE623 = {};

  // register zz50zE624
  bool z0zE624 = {};

  // register zz50zE625
  bool z0zE625 = {};

  // register zz50zE626
  bool z0zE626 = {};

  // register zz50zE627
  bool z0zE627 = {};

  // register zz50zE628
  bool z0zE628 = {};

  // register zz50zE629
  bool z0zE629 = {};

  // register zz50zE630
  bool z0zE630 = {};

  // register zz50zE631
  bool z0zE631 = {};

  // register zz50zE632
  bool z0zE632 = {};

  // register zz50zE633
  bool z0zE633 = {};

  // register zz50zE634
  bool z0zE634 = {};

  // register zz50zE635
  bool z0zE635 = {};

  // register zz50zE636
  bool z0zE636 = {};

  // register zz50zE637
  bool z0zE637 = {};

  // register zz50zE638
  bool z0zE638 = {};

  // register zz50zE639
  sail_int z0zE639 = {};

  // register zz50zE640
  bool z0zE640 = {};

  // register zz50zE641
  sail_int z0zE641 = {};

  // register zz50zE642
  bool z0zE642 = {};

  // register zz50zE643
  bool z0zE643 = {};

  // register zz50zE644
  bool z0zE644 = {};

  // register zz50zE645
  sail_int z0zE645 = {};

  // register zz50zE646
  bool z0zE646 = {};

  // register zz50zE647
  struct zoptionzIbzK z0zE647 = {};

  // register zz50zE618
  bool z0zE618 = {};

  // register zz50zE619
  bool z0zE619 = {};

  // register zz50zE616
  bool z0zE616 = {};

  // register zz50zE617
  bool z0zE617 = {};

  // register zz50zE358
  bool z0zE358 = {};

  // register zz50zE359
  bool z0zE359 = {};

  // register zz50zE360
  bool z0zE360 = {};

  // register zz50zE361
  bool z0zE361 = {};

  // register zz50zE362
  bool z0zE362 = {};

  // register zz50zE363
  bool z0zE363 = {};

  // register zz50zE364
  bool z0zE364 = {};

  // register zz50zE365
  bool z0zE365 = {};

  // register zz50zE606
  bool z0zE606 = {};

  // register zz50zE607
  bool z0zE607 = {};

  // register zz50zE608
  bool z0zE608 = {};

  // register zz50zE609
  bool z0zE609 = {};

  // register zz50zE610
  bool z0zE610 = {};

  // register zz50zE611
  bool z0zE611 = {};

  // register zz50zE612
  bool z0zE612 = {};

  // register zz50zE613
  bool z0zE613 = {};

  // register zz50zE614
  bool z0zE614 = {};

  // register zz50zE615
  bool z0zE615 = {};

  // register zz50zE366
  bool z0zE366 = {};

  // register zz50zE367
  bool z0zE367 = {};

  // register zz50zE368
  bool z0zE368 = {};

  // register zz50zE369
  bool z0zE369 = {};

  // register zz50zE370
  bool z0zE370 = {};

  // register zz50zE371
  bool z0zE371 = {};

  // register zz50zE372
  bool z0zE372 = {};

  // register zz50zE373
  bool z0zE373 = {};

  // register zz50zE374
  bool z0zE374 = {};

  // register zz50zE375
  bool z0zE375 = {};

  // register zz50zE376
  bool z0zE376 = {};

  // register zz50zE377
  bool z0zE377 = {};

  // register zz50zE378
  bool z0zE378 = {};

  // register zz50zE379
  bool z0zE379 = {};

  // register zz50zE380
  bool z0zE380 = {};

  // register zz50zE381
  bool z0zE381 = {};

  // register zz50zE382
  bool z0zE382 = {};

  // register zz50zE383
  bool z0zE383 = {};

  // register zz50zE384
  bool z0zE384 = {};

  // register zz50zE385
  bool z0zE385 = {};

  // register zz50zE386
  bool z0zE386 = {};

  // register zz50zE387
  bool z0zE387 = {};

  // register zz50zE388
  bool z0zE388 = {};

  // register zz50zE389
  bool z0zE389 = {};

  // register zz50zE390
  bool z0zE390 = {};

  // register zz50zE391
  bool z0zE391 = {};

  // register zz50zE392
  bool z0zE392 = {};

  // register zz50zE393
  bool z0zE393 = {};

  // register zz50zE394
  bool z0zE394 = {};

  // register zz50zE395
  bool z0zE395 = {};

  // register zz50zE396
  bool z0zE396 = {};

  // register zz50zE397
  bool z0zE397 = {};

  // register zz50zE398
  bool z0zE398 = {};

  // register zz50zE399
  bool z0zE399 = {};

  // register zz50zE400
  bool z0zE400 = {};

  // register zz50zE401
  bool z0zE401 = {};

  // register zz50zE402
  bool z0zE402 = {};

  // register zz50zE403
  bool z0zE403 = {};

  // register zz50zE404
  bool z0zE404 = {};

  // register zz50zE405
  bool z0zE405 = {};

  // register zz50zE406
  bool z0zE406 = {};

  // register zz50zE407
  bool z0zE407 = {};

  // register zz50zE408
  bool z0zE408 = {};

  // register zz50zE409
  bool z0zE409 = {};

  // register zz50zE410
  bool z0zE410 = {};

  // register zz50zE411
  bool z0zE411 = {};

  // register zz50zE412
  bool z0zE412 = {};

  // register zz50zE413
  bool z0zE413 = {};

  // register zz50zE414
  bool z0zE414 = {};

  // register zz50zE415
  bool z0zE415 = {};

  // register zz50zE416
  bool z0zE416 = {};

  // register zz50zE417
  bool z0zE417 = {};

  // register zz50zE418
  bool z0zE418 = {};

  // register zz50zE419
  bool z0zE419 = {};

  // register zz50zE602
  bool z0zE602 = {};

  // register zz50zE603
  bool z0zE603 = {};

  // register zz50zE604
  bool z0zE604 = {};

  // register zz50zE605
  bool z0zE605 = {};

  // register zz50zE420
  bool z0zE420 = {};

  // register zz50zE421
  bool z0zE421 = {};

  // register zz50zE600
  bool z0zE600 = {};

  // register zz50zE601
  bool z0zE601 = {};

  // register zz50zE422
  bool z0zE422 = {};

  // register zz50zE423
  bool z0zE423 = {};

  // register zz50zE596
  bool z0zE596 = {};

  // register zz50zE597
  bool z0zE597 = {};

  // register zz50zE598
  bool z0zE598 = {};

  // register zz50zE599
  bool z0zE599 = {};

  // register zz50zE424
  bool z0zE424 = {};

  // register zz50zE425
  bool z0zE425 = {};

  // register zz50zE426
  bool z0zE426 = {};

  // register zz50zE427
  bool z0zE427 = {};

  // register zz50zE428
  bool z0zE428 = {};

  // register zz50zE429
  bool z0zE429 = {};

  // register zz50zE594
  bool z0zE594 = {};

  // register zz50zE595
  bool z0zE595 = {};

  // register zz50zE430
  bool z0zE430 = {};

  // register zz50zE431
  bool z0zE431 = {};

  // register zz50zE592
  bool z0zE592 = {};

  // register zz50zE593
  bool z0zE593 = {};

  // register zz50zE432
  bool z0zE432 = {};

  // register zz50zE433
  bool z0zE433 = {};

  // register zz50zE590
  bool z0zE590 = {};

  // register zz50zE591
  uint64_t z0zE591 = {};

  // register zz50zE434
  bool z0zE434 = {};

  // register zz50zE435
  bool z0zE435 = {};

  // register zz50zE436
  bool z0zE436 = {};

  // register zz50zE437
  bool z0zE437 = {};

  // register zz50zE438
  bool z0zE438 = {};

  // register zz50zE439
  bool z0zE439 = {};

  // register zz50zE556
  bool z0zE556 = {};

  // register zz50zE557
  bool z0zE557 = {};

  // register zz50zE558
  bool z0zE558 = {};

  // register zz50zE559
  bool z0zE559 = {};

  // register zz50zE560
  bool z0zE560 = {};

  // register zz50zE561
  struct zoptionzIbzK z0zE561 = {};

  // register zz50zE562
  bool z0zE562 = {};

  // register zz50zE563
  bool z0zE563 = {};

  // register zz50zE564
  bool z0zE564 = {};

  // register zz50zE565
  bool z0zE565 = {};

  // register zz50zE566
  bool z0zE566 = {};

  // register zz50zE567
  bool z0zE567 = {};

  // register zz50zE568
  bool z0zE568 = {};

  // register zz50zE569
  bool z0zE569 = {};

  // register zz50zE570
  bool z0zE570 = {};

  // register zz50zE571
  bool z0zE571 = {};

  // register zz50zE572
  bool z0zE572 = {};

  // register zz50zE573
  bool z0zE573 = {};

  // register zz50zE574
  bool z0zE574 = {};

  // register zz50zE575
  bool z0zE575 = {};

  // register zz50zE576
  bool z0zE576 = {};

  // register zz50zE577
  bool z0zE577 = {};

  // register zz50zE578
  bool z0zE578 = {};

  // register zz50zE579
  bool z0zE579 = {};

  // register zz50zE580
  bool z0zE580 = {};

  // register zz50zE581
  bool z0zE581 = {};

  // register zz50zE582
  bool z0zE582 = {};

  // register zz50zE583
  bool z0zE583 = {};

  // register zz50zE584
  bool z0zE584 = {};

  // register zz50zE585
  bool z0zE585 = {};

  // register zz50zE586
  bool z0zE586 = {};

  // register zz50zE587
  bool z0zE587 = {};

  // register zz50zE588
  bool z0zE588 = {};

  // register zz50zE589
  bool z0zE589 = {};

  // register zz50zE440
  bool z0zE440 = {};

  // register zz50zE441
  bool z0zE441 = {};

  // register zz50zE442
  bool z0zE442 = {};

  // register zz50zE443
  bool z0zE443 = {};

  // register zz50zE444
  bool z0zE444 = {};

  // register zz50zE445
  bool z0zE445 = {};

  // register zz50zE446
  bool z0zE446 = {};

  // register zz50zE447
  bool z0zE447 = {};

  // register zz50zE448
  bool z0zE448 = {};

  // register zz50zE449
  bool z0zE449 = {};

  // register zz50zE554
  bool z0zE554 = {};

  // register zz50zE555
  bool z0zE555 = {};

  // register zz50zE450
  bool z0zE450 = {};

  // register zz50zE451
  bool z0zE451 = {};

  // register zz50zE552
  bool z0zE552 = {};

  // register zz50zE553
  bool z0zE553 = {};

  // register zz50zE452
  bool z0zE452 = {};

  // register zz50zE453
  bool z0zE453 = {};

  // register zz50zE542
  bool z0zE542 = {};

  // register zz50zE543
  bool z0zE543 = {};

  // register zz50zE544
  bool z0zE544 = {};

  // register zz50zE545
  bool z0zE545 = {};

  // register zz50zE546
  bool z0zE546 = {};

  // register zz50zE547
  bool z0zE547 = {};

  // register zz50zE548
  bool z0zE548 = {};

  // register zz50zE549
  bool z0zE549 = {};

  // register zz50zE550
  bool z0zE550 = {};

  // register zz50zE551
  bool z0zE551 = {};

  // register zz50zE454
  bool z0zE454 = {};

  // register zz50zE455
  bool z0zE455 = {};

  // register zz50zE540
  bool z0zE540 = {};

  // register zz50zE541
  bool z0zE541 = {};

  // register zz50zE456
  bool z0zE456 = {};

  // register zz50zE457
  bool z0zE457 = {};

  // register zz50zE536
  bool z0zE536 = {};

  // register zz50zE537
  bool z0zE537 = {};

  // register zz50zE538
  bool z0zE538 = {};

  // register zz50zE539
  bool z0zE539 = {};

  // register zz50zE458
  bool z0zE458 = {};

  // register zz50zE459
  bool z0zE459 = {};

  // register zz50zE526
  bool z0zE526 = {};

  // register zz50zE527
  bool z0zE527 = {};

  // register zz50zE528
  bool z0zE528 = {};

  // register zz50zE529
  bool z0zE529 = {};

  // register zz50zE530
  bool z0zE530 = {};

  // register zz50zE531
  bool z0zE531 = {};

  // register zz50zE532
  bool z0zE532 = {};

  // register zz50zE533
  bool z0zE533 = {};

  // register zz50zE534
  bool z0zE534 = {};

  // register zz50zE535
  bool z0zE535 = {};

  // register zz50zE460
  bool z0zE460 = {};

  // register zz50zE461
  bool z0zE461 = {};

  // register zz50zE510
  bool z0zE510 = {};

  // register zz50zE511
  bool z0zE511 = {};

  // register zz50zE512
  bool z0zE512 = {};

  // register zz50zE513
  bool z0zE513 = {};

  // register zz50zE514
  bool z0zE514 = {};

  // register zz50zE515
  bool z0zE515 = {};

  // register zz50zE516
  bool z0zE516 = {};

  // register zz50zE517
  bool z0zE517 = {};

  // register zz50zE518
  bool z0zE518 = {};

  // register zz50zE519
  bool z0zE519 = {};

  // register zz50zE520
  bool z0zE520 = {};

  // register zz50zE521
  bool z0zE521 = {};

  // register zz50zE522
  bool z0zE522 = {};

  // register zz50zE523
  bool z0zE523 = {};

  // register zz50zE524
  bool z0zE524 = {};

  // register zz50zE525
  bool z0zE525 = {};

  // register zz50zE462
  bool z0zE462 = {};

  // register zz50zE463
  bool z0zE463 = {};

  // register zz50zE464
  bool z0zE464 = {};

  // register zz50zE465
  bool z0zE465 = {};

  // register zz50zE466
  bool z0zE466 = {};

  // register zz50zE467
  bool z0zE467 = {};

  // register zz50zE468
  bool z0zE468 = {};

  // register zz50zE469
  bool z0zE469 = {};

  // register zz50zE470
  bool z0zE470 = {};

  // register zz50zE471
  bool z0zE471 = {};

  // register zz50zE472
  bool z0zE472 = {};

  // register zz50zE473
  bool z0zE473 = {};

  // register zz50zE474
  bool z0zE474 = {};

  // register zz50zE475
  bool z0zE475 = {};

  // register zz50zE476
  bool z0zE476 = {};

  // register zz50zE477
  bool z0zE477 = {};

  // register zz50zE478
  bool z0zE478 = {};

  // register zz50zE479
  sbits z0zE479 = {};

  // register zz50zE480
  bool z0zE480 = {};

  // register zz50zE481
  bool z0zE481 = {};

  // register zz50zE482
  bool z0zE482 = {};

  // register zz50zE483
  sbits z0zE483 = {};

  // register zz50zE484
  bool z0zE484 = {};

  // register zz50zE485
  enum zSdtrig_breakpoint_reentrancy z0zE485 = {};

  // register zz50zE504
  bool z0zE504 = {};

  // register zz50zE505
  uint64_t z0zE505 = {};

  // register zz50zE486
  bool z0zE486 = {};

  // register zz50zE487
  bool z0zE487 = {};

  // register zz50zE488
  bool z0zE488 = {};

  // register zz50zE489
  bool z0zE489 = {};

  // register zz50zE490
  bool z0zE490 = {};

  // register zz50zE491
  bool z0zE491 = {};

  // register zz50zE492
  bool z0zE492 = {};

  // register zz50zE493
  bool z0zE493 = {};

  // register zz50zE494
  bool z0zE494 = {};

  // register zz50zE495
  bool z0zE495 = {};

  // register zz50zE496
  bool z0zE496 = {};

  // register zz50zE497
  bool z0zE497 = {};

  // register zz50zE498
  bool z0zE498 = {};

  // register zz50zE499
  bool z0zE499 = {};

  // register zz50zE500
  bool z0zE500 = {};

  // register zz50zE501
  bool z0zE501 = {};

  // register zz50zE502
  bool z0zE502 = {};

  // register zz50zE503
  bool z0zE503 = {};

  // register zz50zE506
  bool z0zE506 = {};

  // register zz50zE507
  bool z0zE507 = {};

  // register zz50zE508
  bool z0zE508 = {};

  // register zz50zE509
  sail_int z0zE509 = {};

  // register zz50zE320
  bool z0zE320 = {};

  // register zz50zE321
  bool z0zE321 = {};

  // register zz50zE322
  bool z0zE322 = {};

  // register zz50zE323
  bool z0zE323 = {};

  // register zz50zE324
  bool z0zE324 = {};

  // register zz50zE325
  bool z0zE325 = {};

  // register zz50zE326
  bool z0zE326 = {};

  // register zz50zE327
  bool z0zE327 = {};

  // register zz50zE354
  bool z0zE354 = {};

  // register zz50zE355
  struct zGlobalMisalignedExceptions z0zE355 = {};

  // register zz50zE356
  bool z0zE356 = {};

  // register zz50zE357
  struct zGlobalMisalignedExceptions z0zE357 = {};

  // register zz50zE328
  bool z0zE328 = {};

  // register zz50zE329
  bool z0zE329 = {};

  // register zz50zE342
  bool z0zE342 = {};

  // register zz50zE343
  uint64_t z0zE343 = {};

  // register zz50zE344
  bool z0zE344 = {};

  // register zz50zE345
  bool z0zE345 = {};

  // register zz50zE346
  bool z0zE346 = {};

  // register zz50zE347
  bool z0zE347 = {};

  // register zz50zE348
  bool z0zE348 = {};

  // register zz50zE349
  sbits z0zE349 = {};

  // register zz50zE350
  bool z0zE350 = {};

  // register zz50zE351
  bool z0zE351 = {};

  // register zz50zE352
  bool z0zE352 = {};

  // register zz50zE353
  bool z0zE353 = {};

  // register zz50zE330
  bool z0zE330 = {};

  // register zz50zE331
  bool z0zE331 = {};

  // register zz50zE338
  bool z0zE338 = {};

  // register zz50zE339
  bool z0zE339 = {};

  // register zz50zE340
  bool z0zE340 = {};

  // register zz50zE341
  bool z0zE341 = {};

  // register zz50zE332
  bool z0zE332 = {};

  // register zz50zE333
  bool z0zE333 = {};

  // register zz50zE334
  bool z0zE334 = {};

  // register zz50zE335
  bool z0zE335 = {};

  // register zz50zE336
  bool z0zE336 = {};

  // register zz50zE337
  bool z0zE337 = {};

  // register zz50zE314
  bool z0zE314 = {};

  // register zz50zE315
  bool z0zE315 = {};

  // register zz50zE316
  bool z0zE316 = {};

  // register zz50zE317
  bool z0zE317 = {};

  // register zz50zE318
  bool z0zE318 = {};

  // register zz50zE319
  bool z0zE319 = {};

  // register zz50zE304
  bool z0zE304 = {};

  // register zz50zE305
  bool z0zE305 = {};

  // register zz50zE306
  bool z0zE306 = {};

  // register zz50zE307
  bool z0zE307 = {};

  // register zz50zE312
  bool z0zE312 = {};

  // register zz50zE313
  bool z0zE313 = {};

  // register zz50zE308
  bool z0zE308 = {};

  // register zz50zE309
  bool z0zE309 = {};

  // register zz50zE310
  bool z0zE310 = {};

  // register zz50zE311
  sail_int z0zE311 = {};

  // register zz50zE292
  bool z0zE292 = {};

  // register zz50zE293
  enum zExtContextPolicy z0zE293 = {};

  // register zz50zE294
  bool z0zE294 = {};

  // register zz50zE295
  bool z0zE295 = {};

  // register zz50zE296
  bool z0zE296 = {};

  // register zz50zE297
  bool z0zE297 = {};

  // register zz50zE298
  bool z0zE298 = {};

  // register zz50zE299
  bool z0zE299 = {};

  // register zz50zE300
  bool z0zE300 = {};

  // register zz50zE301
  enum zExtContextPolicy z0zE301 = {};

  // register zz50zE302
  bool z0zE302 = {};

  // register zz50zE303
  bool z0zE303 = {};

  // register zz50zE290
  bool z0zE290 = {};

  // register zz50zE291
  bool z0zE291 = {};

  inline static const size_t SAIL_TEST_COUNT = 5;
  inline static unit (Model::*const SAIL_TESTS[6])(unit) = {
    &Model::ztest_highest_index_of,
    &Model::ztest_lowest_index_of,
    &Model::ztest_mstatus_sxl_uxl_reset_values,
    &Model::ztest_pmpTORBound,
    &Model::ztest_range_subset,
    NULL
  };
  inline static const char* const SAIL_TEST_NAMES[6] = {
    "test_highest_index_of",
    "test_lowest_index_of",
    "test_mstatus_sxl_uxl_reset_values",
    "test_pmpTORBound",
    "test_range_subset",
    NULL
  };

  void model_init();
  void model_fini();
  };
} // namespace


