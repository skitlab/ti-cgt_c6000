TMS320C6000 C/C++ CODE GENERATION TOOLS
7.2.11 Release Notes
December 2012


===============================================================================
Contents
===============================================================================
1) Support Information
   1.1) Defect History
   1.2) Compiler Documentation Errata
   1.3) TI E2E Community
   1.4) C67x Fast Run-Time Support (RTS) Library
   1.5) Defect Tracking Database
2) Support for C6600 ISA
   2.1) C6600 ISA Characteristics
   2.2) Tools Usage
        2.2.1) -mv6600 Option
        2.2.2) Default ABI
        2.2.3) C6600 Pre-Defined Symbols
   2.3) C6600 Instructions Supported Using intrinsics
        2.3.1) Vector-in-Scalar (SIMD) Support Intrinsics
   2.4) C6600 Instructions Supported Natively
   2.5) 128-bit Container Type (__x128_t)
        2.5.1) Description of 128-bit Container Type
        2.5.2) Calling Convention Additions
   2.6) C6600 Predefined Macros and Predefined Symbolic Constants
   2.7) Linear Assembly Support for C6600
   2.8) Notes on Register Quad Syntax
   2.9) Notes on Stack Pointer Alignment
   2.10) Notes on Top-level Array Alignment
3) New native 40-bit type support (__int40_t)
   3.1) Syntax
   3.2) 40-bit Literals
   3.3) Bit-fields
   3.4) printf()/scanf() Format String
   3.5) Intrinsics
   3.6) Standard Header Files
4) Support of GCC Language Extensions
   4.1) Additional Features Supported
   4.2) GCC Language Extensions Available in C++
   4.3) GCC Language Extensions Included in Relaxed ANSI Mode
   4.4) Improved Robustness in Processing of GCC Extensions
5) Change in EABI Enumeration Type
6) New CLINK and RETAIN Pragmas
   6.1) COFF and EABI Conditional Linking Models
   6.2) The CLINK and RETAIN Pragmas
   6.3) The .clink and .retain Assembler Directives
7) New --emit_warnings_as_errors Compiler Option
8) Run Length Encoding (RLE) Extended to Handle 24-bit Run Lengths
9) New __float2_t Type; Recommendations on the use of "double" type
10) Early Adopter Version of Prelink Utility - prelink6x
11) New --symdebug:keep_all_types Compiler Option
12) Linker MEMORY directive expressions

-------------------------------------------------------------------------------
1) Support Information
-------------------------------------------------------------------------------

1.1) Defect History
-------------------

The list of defects fixed in this release as well as known issues can
be found in the file DefectHistory.txt.

1.2) Compiler Documentation Errata
----------------------------------

Errata from the "TMS320C6000 Optimizing Compiler User's Guide" and the
"TMS320C6000 Assembly Language User's Guide" is available online at the
Texas Instruments Embedded Processors CG Wiki:

http://tiexpressdsp.com/wiki/index.php?title=Category:CGT

under the 'Compiler Documentation Errata' link.

This Wiki has been established to assist developers in using TI Embedded
Processor Software and Tools.  Developers are encouraged to dig through all
the articles.  Registered users can update missing or incorrect information.

1.3) TI E2E Community
---------------------

Questions concerning TI Code Generation Tools can be posted to the TI E2E
Community forums.  The "Development Tools" forum can be found at:

http://e2e.ti.com/support/development_tools/f/default.aspx

1.4) C67x Fast Run-Time Support (RTS) Library
---------------------------------------------

These libraries are no longer included in the C6000 Code Generation Tools.
They are available for download at the following Texas Instruments page:

http://focus.ti.com/docs/toolsw/folders/print/sprc060.html

Or search the ti.com site for the tag: tms320c67x fastrts library

1.5) Defect Tracking Database
-----------------------------

Compiler defect reports can be tracked at the Development Tools bug
database, SDOWP. The log in page for SDOWP, as well as a link to create
an account with the defect tracking database is found at:

https://cqweb.ext.ti.com/pages/SDO-Web.html

A my.ti.com account is required to access this page.  To find an issue
in SDOWP, enter your bug id in the "Find Record ID" box once logged in.
To find tables of all compiler issues click the queries under the folder:

"Public Queries" -> "Development Tools" -> "TI C-C++ Compiler"

With your SDOWP account you can save your own queries in your
"Personal Queries" folder.


-------------------------------------------------------------------------------
2) Support for C6600 ISA
-------------------------------------------------------------------------------
This 7.2.0 release has support for the C6600 ISA.

 * All C6600 instructions are supported using intrinsics or native C support.

 * The 17 C6600 instructions that require 128-bit C data type are supported
   in this release. See section 2.3.1 of this readme for details.

 * The assembler and disassembler have full support for all C6600
   instructions.

 * The compiler utilizes the 64-bit cross path capability of the C6600 ISA.

 * The compiler can exploit the widened .M unit write port.
 
 * The assembler does not check for certain illegal conditions when two
   instructions are writing through the same functional unit on the same
   cycle.  
   (1) The assembler does not check for the illegal condition where 
       an instruction accesses a register pair over the cross path and another 
       instruction in that same cycle only references one of those registers 
       (of the register pair) via the cross path.  

   (2) The assembler will not catch the case of an attempt to write 160-bits 
       of output on the same cycle from two different M unit instructions. 

   (3) The assembler will not catch the case of an attempt of a 4 cycle 
       L(S) unit instruction and a 2 cycle L(S) unit instruction writing 
       on the same cycle.  These checks may be implemented in the future 
       version of the assembler.

 * This release package includes Runtime Support (RTS) libraries built for 
   C6600.  The linker will automatically choose the correct rts library.


2.1) C6600 ISA Characteristics
------------------------------
C6600 ISA is an improvement over C674x ISA (C67x + C64+) and provides the 
following features:
 * Allow fully pipelined double precision floating point multiplies
 * Reduce latency of double precision multiply from 10 cycles to 4 cycles
 * Allow four single precision multiplies per cycle
 * Allow up to sixteen 16x16 fixed point multiplies, or four 32x32-bit 
   multiplies per cycle  This makes the C6600 a 32 MAC machine.
 * The C6600 ISA adds about 100 new instructions. 11 of these instructions
   operate on and/or produce 128-bit data. 


2.2) Tools Usage
----------------
The 7.2.0 release supports the C6600 ISA when the shell option -mv6600 is 
used.

2.2.1) -mv6600 Option
---------------------
The compiler generates C6600 ISA code when -mv6600 option is specified. 

  To compile/assemble file for C6600
    > cl6x -mv6600 <source>

  To compile and link an executable file for C6600
    > cl6x -mv6600 <source> -z -l libc.a -l <lnk.cmd> 

  NOTE: linking against the pseudo library libc.a lets the linker pick the 
        best library. -c or -cr linker option implies -l libc.a

2.2.2) Default ABI
------------------
The C6000 compiler supports both COFF ABI and ELF ABI (EABI). The default 
compiler behavior for pre-C6600 ISA is to generate COFF ABI. For C6600 ISA, the 
default ABI is EABI.  The user needs to use --abi=coffabi to generate COFF ABI 
objects:
    > cl6x --abi=coffabi -mv6600 <source>

Existing COFF projects, when migrating to C6600 ISA should either first migrate 
to ELF or use the --abi=coffabi option along with -mv6600.

2.2.3) C6600 Pre-Defined Symbols
--------------------------------

The C6000 compiler and assembler provide pre-defined symbols to help 
isolate C6600-specific C/C++ or assembly language code from other code
in a source file.

In a C/C++ source file, use "_TMS320C6600" to isolate C6600-specific
code from other code. For example, in memset.c of the RTS library source, 
you will see an example of the use of this pre-defined symbol:

#if defined(_TMS320C6400) || defined(_TMS320C6740) || \
    defined(_TMS320C6600) || defined(_TI_C6X_TESLA)
_CODE_ACCESS void *memset(void *dst, int fill, size_t len) {
   char  *restrict dst1, *restrict dst2;
   int    pre_bytes, post_bytes, wfill, i;
   double dfill1, dfill2;

   dst1   = (char *)dst;

   /*--------------------------------------------------------------------*/
   /* Replicate the 8-bit value in
    * fill into all 4 bytes of
    * wfill        */
   /*--------------------------------------------------------------------*/
   wfill  = _pack2(fill,  fill);
   wfill  = _packl4(wfill, wfill);

   ...

#endif

In an assembly source file, use ".TMS320C6600" to isolate C6600-specific 
code from other code. For example, in strasg.asm of the RTS library source, 
you will see an example of the use of this pre-defined symbol:

        .if .TMS320C64_PLUS | .TMS320C6740 | .TMS320C6600

        .sect   ".text:__strasgi_64plus"
        .clink
        .global __strasgi_64plus, __c6xabi_strasgi_64plus

__c6xabi_strasgi_64plus:
__strasgi_64plus:  .asmfunc

        MV      .L1     A4, A30      ; Save dst
 ||     SHR     .S2X    A6,2,B31     ; Count / 4

        ...

        .endif


2.3) C6600 instructions supported using intrinsics
--------------------------------------------------
The C6600 instructions that are supported using intrinsics are defined
in the c6x.h file located in the RTS "include" directory.  Look for
the intrinsics under the #if defined(_TMS320C6600).  Most C6600
instructions are supported via intrinsics.  Others are supported in native
C (MPYDP, FADDSP, FSUBSP, FADDDP, FSUBDP, 64-bit AND, 64-bit ANDN, 
64-bit OR, 64-bit XOR, INTSPU, INTSP, SPINT).

If you need to use an intrinsic that uses the __x128_t container type 
(see next section), c6x.h MUST BE INCLUDED in the source file.

2.3.1) Vector-in-Scalar (SIMD) Support Intrinsics
-------------------------------------------------

NOTE: If you need to use an intrinsic that has the __x128_t container type
in the function signature, c6x.h MUST BE INCLUDED in the source file.

Creation

Intrinsic  src1 type  src2 type  src3 type  src4 type  return type   comment
-----------------------------------------------------------------------------------------------------------------------------
_itod      unsigned   unsigned                         double        create double from (u)int
_ftod      float      float                            double        create double from float
_ftof2     float      float                            __float2_t    create __float2_t from float
_itoll     unsigned   unsigned                         long long     create long long from (u)int
_itol      unsigned   unsigned                         long (40-bit) create long (40-bit) from (u)int
_ito128    unsigned   unsigned   unsigned   unsigned   __x128_t      create __x128_t from (u)int (reg+3, reg+2, reg+1, reg+0)
_fto128    float      float      float      float      __x128_t      create __x128_t from float (reg+3, reg+2, reg+1, reg+0)
_llto128   long long  long long                        __x128_t      create __x128_t from two long longs
_dto128    double     double                           __x128_t      create __x128_t from two doubles
_f2to128   __float2_t __float2_t                       __x128_t      create __x128_t from two __float2_t

Reinterpretation

Intrinsic    src1 type   src2 type   return type  comment
-----------------------------------------------------------------------------
_itof        unsigned                float        reinterpret (u)int as float
_ftoi        float                   unsigned     reinterpret float as (u)int
_lltod       long long               double       reinterpret long long as double
_lltof2      long long               __float2_t   reinterpret long long as __float2_t
_dtoll       double                  long long    reinterpret double as long long
_f2toll      __float2_t              long long    reinterpret __float2_t as long long

Extraction

Intrinsic    src1 type  src2 type    return type  comment
----------------------------------------------------------------------------
_hi          double                  float        upper reg of reg pair
_lo          double                  float        lower reg of reg pair
_hill        long long               unsigned     upper reg of reg pair
_loll        long long               unsigned     lower reg of reg pair
_hif         double                  float        upper reg of reg pair
_lof         double                  float        lower reg of reg pair
_hif2        __float2_t              float        upper reg of reg pair
_lof2        __float2_t              float        lower reg of reg pair
_hi128       __x128_t                long long    upper two regs of reg quad
_hid128      __x128_t                double       upper two regs of reg quad
_hif2_128    __x128_t                __float2_t   upper two regs of reg quad
_lo128       __x128_t                long long    lower two regs of reg quad
_lod128      __x128_t                double       lower two regs of reg quad
_lof2_128    __x128_t                __float2_t   lower two regs of reg quad
_get32_128   __x128_t   0 (literal)  unsigned     first reg of reg quad
_get32_128   __x128_t   1 (literal)  unsigned     second reg of reg quad
_get32_128   __x128_t   2 (literal)  unsigned     third reg of reg quad
_get32_128   __x128_t   3 (literal)  unsigned     fourth reg of reg quad
_get32f_128  __x128_t   0 (literal)  float        first reg of reg quad
_get32f_128  __x128_t   1 (literal)  float        second reg of reg quad
_get32f_128  __x128_t   2 (literal)  float        third reg of reg quad
_get32f_128  __x128_t   3 (literal)  float        fourth reg of reg quad 


C6600 Intrinsics 

Intrinsic       src1 type       src2 type       return type     comment  
---------------------------------------------------------------------------
_dcmpyr1        long long       long long       long long  
_dccmpyr1       long long       long long       long long  
_cmatmpyr1      long long       __x128_t        long long  
_ccmatmpyr1     long long       __x128_t        long long  
_cmatmpy        long long       __x128_t        __x128_t  
_ccmatmpy       long long       __x128_t        __x128_t  
_qsmpy32r1      __x128_t        __x128_t        __x128_t  
_cmpy32r1       long long       long long       long long  
_ccmpy32r1      long long       long long       long long  
_qmpy32         __x128_t        __x128_t        __x128_t  
_dsmpy2         long long       long long       __x128_t  
_mpyu2          unsigned int    unsigned int    long long  
_dmpy           long long       long long       __x128_t  
_dmpy2          long long       long long       __x128_t  
_dmpyu2         long long       long long       __x128_t  
_dotpsu4h       long long       long long       int  
_dotpsu4hll     long long       long long       long long  
_dadd           long long       long long       long long  
_dadd_c         unsigned imm    long long       long long  
                (-16 to 15 only)
_dsadd          long long       long long       long long  
_dadd2          long long       long long       long long  
_dsadd2         long long       long long       long long  
_dsub           long long       long long       long long  
_dssub          long long       long long       long long  
_dsub2          long long       long long       long long  
_dssub2         long long       long long       long long  
_dapys2         long long       long long       long long  
_dshr           long long       unsigned int    long long
_dshru          long long       unsigned int    long ong  
_dshl           long long       unsigned int    long long
_dshr2          long long       unsigned int    long long
_dshru2         long long       unsigned int    long long
_shl2           unsigned int    unsigned int    unsigned int  
_dshl2          long long       unsigned        long long  
_dxpnd4         unsigned int    long long  
_dxpnd2         unsigned int    long long  
_crot90         int             int  
_dcrot90        long long       long long  
_crot270        int             int  
_dcrot270       long long       long long  

Intrinsic       src1 type       src2 type       return type     comment  
---------------------------------------------------------------------------
_dmvd           int             int             long long
_fdmvd_f2       float           float           __float2_t
_dmax2          long long       long long       long long  
_dmin2          long long       long long       long long  
_dmaxu4         long long       long long       long long  
_dminu4         long long       long long       long long  
_dcmpgt2        long long       long long       unsigned int  
_dcmpeq2        long long       long long       unsigned int  
_dcmpgtu4       long long       long long       unsigned int  
_dcmpeq4        long long       long long       unsigned int  
_davg2          long long       long long       long long  
_davgu4         long long       long long       long long  
_davgnr2        long long       long long       long long  
_davgnru4       long long       long long       long long  
_unpkbu4        unsigned int    long long  
_unpkh2         unsigned int    long long  
_unpkhu2        unsigned int    long long  
_dpackl2        long long       long long       long long  
_dpackh2        long long       long long       long long  
_dpacklh2       long long       long long       long long  
_dpacklh4       unsigned int    unsigned int    long long  
_dpackl4        long long       long long       long long  
_dpackh4        long long       long long       long long  
_dspacku4       long long       long long       long long  
_mfence         void
_dmpysp         __float2_t      __float2_t      __float2_t
_qmpysp         __x128_t        __x128_t        __x128_t  
_daddsp         __float2_t      __float2_t      __float2_t
_dsubsp         __float2_t      __float2_t      __float2_t
_dinthsp        int             __float2_t
_dinthspu       unsigned int    __float2_t
_dspinth        __float2_t      unsigned int  
_dspint         __float2_t      long long  
_land           int             int             int   
_landn          int             int             int   
_lor            int             int             int  

Intrinsic       src1 type       src2 type       return type
-----------------------------------------------------------
_dcmpy          long long       long long       __x128_t
_dmpysu4        long long       long long       __x128_t
_dmpyu4         long long       long long       __x128_t
_dotp4h         long long       long long       int
_dotp4hll       long long       long long       long long
_ddotp4h        __x128_t        __x128_t        long long
_ddotpsu4h      __x128_t        __x128_t        long long
_dintsp         long long                       __float2_t
_dintspu        long long                       __float2_t

Intrinsic                 src1 type  src2 type  return type  comment
-------------------------------------------------------------------------------
_complex_mpysp            __float2_t __float2_t __float2_t   CMPYSP then DADDSP
_complex_conjugate_mpysp  __float2_t __float2_t __float2_t   CMPYSP then DSUBSP


2.4) C6600 instructions supported natively
---------------------------------------------
The C6x 7.2.0 compiler can generate 30 new C6600 instructions from Native C. 
These instructions are SIMD instructions and the compiler identifies 
opportunities to generate these instructions from scalar loop code.  For 
example, consider the following C code: 

void dmaxu4( const unsigned char *restrict a,
             const unsigned char *restrict b,
             unsigned char       *restrict out,
             int                M)
{
   int i;
   _nassert((int)a  % 8  == 0);
   _nassert((int)b  % 8  == 0);
   _nassert((int)out % 8  == 0);
   #pragma MUST_ITERATE(8,,8)
   for (i = 0; i < M; i++ )
   {
       out[i] =  (a[i]>b[i]) ? a[i]:b[i]; // DMAXU4
   }
}

When compiled with -o2 or -o3 optimization, the compiler can generate the
DMAXU4 instruction: 

   $C$L1:    ; PIPED LOOP PROLOG
              SPLOOP  2       ;8                ; (P)
   ||         MV      .L1     A4,A3             ; |7| (R)
   ;** --------------------------------------------------------------------------*
   $C$L2:    ; PIPED LOOP KERNEL
              SPMASK          L1,L2
   ||         MV      .L1     A6,A8             ; (R)
   ||         MV      .L2     B4,B6             ; (R)
   ||         LDDW    .D1T1   *A3++,A7:A6       ; |14| (P) <0,0>
              LDDW    .D2T2   *B6++,B5:B4       ; |14| (P) <0,1>
              NOP             4
              DMAXU4  .L1X    B5:B4,A7:A6,A5:A4 ; |14| <0,6>
              SPKERNEL 0,0
   ||         STDW    .D1T1   A5:A4,*A8++       ; |14| <0,7>
   ;** --------------------------------------------------------------------------*
   $C$L3:    ; PIPED LOOP EPILOG

The list of instructions natively generated by the 7.2.0 Compiler: 

  DADD
  DSADD
  DADD2
  DSADD2
  DSUB
  DSSUB
  DSUB2
  DSSUB2
  DSHR
  DSHRU
  DSHL
  DSHR2
  DSHRU2
  SHL2
  DSHL2
  DSHR
  DSHRU
  DSHL
  DSHR2
  DSHRU2
  SHL2
  DSHL2
  DMAX2
  DMIN2
  DMAXU4
  DMINU4
  DAVG2
  DAVGU4
  DAVGNR2
  DAVGNRU4
  MPYU2
  DOTPSU4H
  DOTPSU4H
  AND (64-bit)
  ANDN (64-bit)
  OR (64-bit)
  XOR (64-bit)
  XOR (64-bit, 1st arg immediate)
  DCROT90
  DCROT270
  UNPKBU4
  UNPKH2
  UNPKHU2
  DPACKL2
  DPACKH2
  DPACKLH2
  DPACKHL2
  DPACKLH4
  DPACKL4
  DPACKH4
  DSPACKU4
  DCMPY
  DCCMPY
  DOTP4H, 32- and 64-bit versions
  DDOTP4H
  DDOTPSU4H
  DMPYU4
  DMPYSU4
  DINTSP
  DINTSPU
  40-bit ADD  (reg, long, long) on L and S unit
  40-bit ADDU (reg, long, long) on L and S unit

The following instructions are improved versions of the existing instructions 
and the compiler will generate the improved C6600 version: 

  FADDSP 
  FSUBSP
  FADDDP
  FSUBDP
  INTSPU
  INTSP 
  SPINT
  ADD  (40-bit, now operates on L and S)
  ADDU (40-bit, now operates on L and S)


2.5) 128-bit Container Type (__x128_t)
--------------------------------------
__x128_t is a new container type for storing 128-bits of data.  This type
facilitates the usage of new 128-bit SIMD instructions on the C6600 ISA
from C and C++ through the use of intrinsics.

2.5.1) Description of the 128-bit Container Type
------------------------------------------------
__x128_t is a container type for storing 128-bits of data and is defined in 
vect.h -- which is included by c6x.h.  In order to use the __x128_t 
container type, c6x.h MUST BE INCLUDED in the source file.

This type can be used to define objects that can be used in C6600
intrinsics. The object can be filled and manipulated using various 
intrinsics.  The type is not a full-fledged built-in type (like long long), 
and so various native C operations are not allowed. Think of this type as a 
struct with private members and special manipulation functions.

Global objects of this type are aligned to a 128-bit boundary. Local objects
of this type are subject to stack pointer alignment. Please see section 2.9
below for more information on use of __x128_t data objects and stack 
alignment.

Requirements:
    * In order to use the __x128_t container type, c6x.h must be included
      in the source file.

Supported/allowed:

    * Declare a __x128_t global object (e.g. __x128_t a;). By default, it will
      be put in the .far section.
    * Declare a __x128_t local object (e.g. __x128_t a;). It will be put on
      the stack.
    * Declare a __x128_t global/local pointer (e.g. __x128_t *a;).
    * Declare an array of __x128_t objects (e.g. __x128_t a[10];).
    * Assign a __x128_t object to another __x128_t object.
    * Pass a __x128_t object to a function (including variable argument
      functions). (Pass by value.)
    * Return a __x128_t object from a function.
    * Use 128-bit manipulation intrinsics to set and extract (see list below) 

Not supported/disallowed:

    * Cast an object to a __x128_t type.
    * Access the "elements" of a __x128_t using array or struct notation. 
    * Other operations not explicitly stated as Supported above.

2.5.2) Calling Convention Additions
-----------------------------------

The addition of the __x128_t container type requires additions to the 
C6000 calling convention as described in the TMS320C6000 Optimizing Compiler 
User's Guide, chapter 7.  The relevant changes to the documentation are 
shown here.  See chapter 7 of spru187 for the full specification of the 
calling convention.

Arguments passed to a function are placed in registers or on the stack. A
function (parent function) performs the following tasks when it calls another
function (child function): If arguments are passed to a function, up to the
first ten arguments are placed in registers A4, B4, A6, B6, A8, B8, A10, B10,
A12, and B12. If longs, long longs, doubles, long doubles or __float2_t
are passed, they are placed in register pairs A5:A4, B5:B4, A7:A6, and so 
on.  However, if one or more __x128_t arguments are passed, the next 
__x128_t argument is passed in the first available register quad, where the 
list of available quads has the ordering: 
A7:A6:A5:A4, B7:B6:B5:B4, A11:A10:A9:A8, B11:B10:B9:B8.
If there are no more available register quads, the __x128_t goes onto the 
stack.  A subsequent 32-bit, 40-bit, or 64-bit argument can take an 
available argument register or register pair even if an earlier __x128_t 
argument has been put on the stack.

If a called function returns a __x128_t, the value is placed in A7:A6:A5:A4.

Please see section 2.9 of this readme for important information about the 
stack pointer alignment when compiling for C6600.


2.6) C6600 Predefined Macros and Predefined Symbolic Constants
---------------------------------------------------------------
This compiler maintains and recognizes the additional predefined
macro names: 
  _TMS320C6600   Defined if target is '6600

This assembler maintains and recognizes the additional predefined
symbols (assembly language):
  .TMS320C6600   Set to 1 if '6600, otherwise 0


2.7) Linear Assembly Support for C6600
--------------------------------------
The 7.2.0 compiler includes the support for linear assembly for C6600. 

The new instructions can be called in linear assembly files by mnemonics
(e.g., QMPY) or intrinsic function names (e.g., _qmpy).

Register quads are used for storing 128-bit data types and represented by 
four variable names concatenated with colons (i.e. a:b:c:d).   


2.8) Notes on Register Quad Syntax
----------------------------------
The 7.2.0 compiler supports a register quad syntax, in order to specify 
128-bit operands of 128-bit capable instructions in linear assembly and 
assembly source code.  The register quad syntax extends the register pair 
syntax.  Thus, four consecutive, aligned registers are needed, each 
separated by a colon.  An example of a register quad is:

    A3:A2:A1:A0

For example, register quads must be used in a QMPYSP instruction:

    QMPYSP  .M1     A27:A26:A25:A24, A11:A10:A9:A8, A19:A18:A17:A16

Do not use substitution symbols for a single register in register quads.  
For example, the assembler will translate the following

    .asg B14,DP
    .asg B15,SP
    QMPYSP  .M2     SP:DP:B13:B12,B11:B10:B9:B8,B19:B18:B17:B16

into

    QMPYSP  .M2     B15B14B13:B12,B11:B10:B9:B8,B19:B18:B17:B16

and then issue a couple of errors concerning the first operand and trailing
operands and also two remarks about symbol substitution.

Note that the colons are missing between the B15 and B14 and B14 and B13.
This is because the :DP: is seen as forced substitution syntax and the
assembler replaces DP with B14 and consumes the colons as required by the 
forced substitution feature.

There are two possible solutions to this problem ...

One solution is to specify the pair or quad with a single symbol (with no
colons).  For example:

    .asg a3:a2:a1:a0, x3x2x1x0

    QMPYSP   .M1   x3x2x1x0, a7:a6:a5:a4, a11:a10:a9:a8

Note that the C6000 7.2 compiler will not use SP or DP in register quads.  
It will instead use B15 and B14.

A second solution is to use an alternate register quad syntax that is now
supported in the C6000 7.2 assembler. A register quad can now be specified
as in the following instruction:

    QMPYSP   .M1   a3::a0, a7::a4, a11::a8
    
In the above substitution symbol example, you can write:

    .asg B14,DP
    .asg B15,SP
    QMPYSP  .M2     SP::B12,B11::B8,B19::B16

The register specified on the right hand side of the '::' operator in the
above register specifications must map to an aligned register (i.e. a0,
a4, a8, a12, ..., b0, b4, b8, ...).


2.9) Notes on Stack Pointer Alignment
-------------------------------------
The C6600 ISA introduces the 128-bit container type __x128_t. Global objects
of this type are aligned to a 16-byte boundary (128 bits). Local __x128_t type
variables are allocated on the stack, but are not necessarily aligned on a
16-byte boundary since the actual alignment of the local variable will depend
on the alignment of the stack and the SP-relative offset of the local __x128_t
type object. For the C6400/C6400+/C6740/C6600 ISAs, the compiler will always
align the stack to an 8-byte boundary.


2.10) Notes on Top-level Array Alignment
----------------------------------------
Top-level arrays are global array variables.  The compiler aligns the top-level 
array to 128-bits for the C6600 ISA. The C6400/C6400+/C6740 ISAs align 
top-level array to 64-bits. This C6600 ISA change doesn't break compatibility 
with existing objects. 


-------------------------------------------------------------------------------
3) New native 40-bit type support (__int40_t)
-------------------------------------------------------------------------------

C6x ISA has efficient 40-bit arithmetic and can benefit from a 40-bit     
C/C++ type. In COFF mode the type 'long' is 40-bits. However this has     
caused issues when porting open source code or code from other platforms 
as most of the code is written with the assumption that longs are 32-bits.   
To aid in migrating such code, we changed the C/C++ type 'long' to be 
32-bits in EABI. 

To leverage the C6x ISA's efficient 40-bit arithmetic in the EABI mode
a new native 40-bit extended C/C++ type '__int40_t' is added. This type 
is supported in both COFF and ELF to make it easy to maintain code across 
ABI.                                         


3.1) Syntax
-----------

The syntax for defining ABI independent 40-bit type is:
            __int40_t  signed_40bit_int_var;
   signed   __int40_t  explicitly_signed_40bit_int_var;
   unsigned __int40_t  unsigned_40bit_int_var;

   NOTE: The following syntax is _not_ allowed:
       __int40_t int x;
         whereas 'long int x;' is allowed.

The __int40_t type has a precision of 40-bits, size of 64-bits and an 
alignment of 64-bits. 

The compiler defines __TI_INT40_T__ macro (set to 1) to indicate that the
type __int40_t is available. 


3.2) 40-bit Literals 
--------------------
A literal integer constant can have an optional prefix to indicate the type
of the constant. For example 1UL indicates that the constant has the type
unsigned long. Users can use the prefixes I40/i40 and UI40/ui40 to indicate
__int40_t type constants:
   1UI40
   0x2ui40
   -1i40
   -03I40
An integer constant without explicit prefix does not get __int40_t type.


3.3) Bit-fields
---------------
The type __int40_t is not allowed to declare bit-fields. For example the 
following struct definition results in a compile time warning.

struct BF_ST 
{
   __int40_t a:3;
}

warning: 40-bit declared type not allowed for bit-fields, changed to 32-bit 
type


3.4) printf()/scanf() Format String
-----------------------------------
Printing or scanning a value of type __int40_t can be done by using one of 
the following format strings:

	printf("I40d", i40var);
	printf("I40i", i40var);
	printf("I40o", i40var);
	printf("I40u", i40var);
	printf("I40x", i40var);
	printf("I40X", i40var);

The standard header file inttypes.h has many typedefs and macro definitions
to aid writing portable code. inttypes.h now includes the following macro
definitions:

	#define PRId40          "I40d"
	#define PRIi40          "I40i"
	#define PRIo40          "I40o"
	#define PRIu40          "I40u"
	#define PRIx40          "I40x"
	#define PRIX40          "I40X"


3.5) Intrinsics
---------------
The following COFF intrinsics are now available in EABI. In both COFF and EABI
the signature of these intrinsics have been changed from type 'long' to 
'__int40_t'.  This should not impact code that uses these intrinsics. 

   __int40_t  _labs    (__int40_t);
   __int40_t  _lsadd   (int, __int40_t);
   __int40_t  _lssub   (int, __int40_t);
   int        _sat     (__int40_t);
   unsigned   _lnorm   (__int40_t);
   __int40_t  _dtol    (double); 
   __int40_t  _f2tol   (__float2_t); 
   double     _ltod    (__int40_t); 
   __float2_t _ltof2   (__int40_t); 
   __int40_t  _ldotp2  (int, int);

The following intrinsics were added in v7.2 compiler to workaround the lack 
of 40-bit type in EABI. 

   long long          _add40_s32 (int,      int);
   unsigned long long _add40_u32 (unsigned, unsigned);
   long long          _add40_s40 (int,      long long);
   unsigned long long _add40_u40 (unsigned, unsigned long long);
   int                _cmpeq40   (int, long long);
   int                _cmpgt40   (int, long long);
   int                _cmplt40   (int, long long);
   int                _cmpltu40  (int, long long);
   int                _cmpgtu40  (int, long long);
   long long          _mov40     (long long);
   long long          _neg40     (long long);
   long long          _labs40    (long long);
   long long          _shl40     (long long, int);
   long long          _shr40     (long long, int);
   unsigned long long _shru40    (unsigned long long, int);
   unsigned long long _shl40_s32 (int      , int);
   long long          _sub40_s32 (int      , int);
   unsigned long long _sub40_u32 (unsigned , unsigned); 
   long long          _sub40_s40 (int,       long long);
   long long          _zero40    ();


3.6) Standard Header Files
--------------------------
The standard header file limits.h now defines the following macros:

    INT40_T_MIN  /* MIN VALUE FOR __INT40_T          */
    INT40_T_MAX  /* MAX VALUE FOR __INT40_T          */
    UINT40_T_MAX /* MAX VALUE FOR UNSIGNED __INT40_T */

The standard header file stdint.h now defines the following typedefs

    typedef          __int40_t  int40_t;
    typedef unsigned __int40_t uint40_t;

    typedef  int40_t  int_least40_t;
    typedef uint40_t uint_least40_t;

    typedef  int40_t  int_fast40_t;
    typedef uint40_t uint_fast40_t;


-------------------------------------------------------------------------------
4) Support of GCC Language Extensions
-------------------------------------------------------------------------------

4.1) Additional Features Supported
----------------------------------
The GNU Compiler Collection C compiler (gcc) defines a number of language
features not found in the ISO standard for the C language.  Many of the GCC
extensions are and have been available (since version 6.1.0) in the TI compiler
when the --gcc option is used.  With this release, support for the following
features has been added:

 o Designated initializers for unions.  (Designated initializers for arrays and
   structs have been available previously.)

 o Pointer arithmetic on void* and function pointers.

 o The function attributes always_inline, const, constructor, format,
   format_arg, malloc, noinline, noreturn, pure, used, warn_unused_result,
   and weak (EABI mode only).

   The format attribute is applied to the declarations of printf, fprintf,
   sprintf, snprintf, vprintf, vfprintf, vsprintf, vsnprintf, scanf, fscanf and
   sscanf in stdio.h.  This means that when GCC extensions are available the
   data arguments of these functions will be type checked against the format
   specifiers in the format string argument and warnings issued when there is a
   mismatch.  These warnings can be suppressed in the usual ways if they are
   not desired.

 o The malloc attribute is applied to the declarations of malloc, calloc,
   realloc and memalign in stdlib.h

 o The variable attributes aligned, mode, packed (only on targets that
   supported unaligned access), transparent_union, used, and weak (EABI mode
   only).

 o The type attributes aligned, deprecated and transparent_union.

 o The type attribute packed on structure and union types (only on targets
   that supported unaligned access).  packed was previously available for
   enumerated types.

 o The function __builtin_constant_p.  (Previously partially available.)

 o The function __builtin_frame_address.  This function returns zero for all
   arguments except a constant zero.

   The functions __builtin_abs, __builtin_fabs, __builtin_fabsf,
   __builtin_labs, __builtin_llabs, and __builtin_memcpy.

The definition and examples of these language constructs can be found online at
http://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/C-Extensions.html#C-Extensions


4.2) GCC Language Extensions Available in C++
---------------------------------------------
Any GCC extensions supported in the TI compiler and which are supported in the
GNU C++ compiler (g++) are also available in the TI compiler for C++ source.


4.3) GCC Language Extensions Included in Relaxed ANSI Mode
----------------------------------------------------------
When relaxed ANSI mode is selected using the --relaxed_ansi (or -pr) option,
all supported GCC language extensions are available.  (Previously the --gcc
option had to be used to enable the GCC extensions.)


4.4) Improved Robustness in Processing of GCC Extensions
--------------------------------------------------------
The GCC features usually referred to as Labels as Values, Hex Floats, Extended
Asm and Constraints are rejected by the compiler.  Previouly the constructs
associated with these features were accepted but the feature was not
implemented.

Similarly unsupported function, variable and type attributes are rejected with
a warning rather than being quietly accepted and ignored.


-------------------------------------------------------------------------------
5) Change in EABI Enumeration Type
-------------------------------------------------------------------------------
In EABI mode, previously the compiler generated 'packed' enums. That is, in 
EABI mode, the compiler generated enum types smaller than int size when 
possible. This is different from COFF ABI where the enum types are always int 
sized or greater. To enable easier COFF to ELF migration, the CGT 7.2 release 
changes the EABI enum type to match that of COFF ABI. This change is also 
introduced to CGT 7.1 Beta 2 release.

Unfortunately, this means that EABI objects built with previous releases are 
not compatible with the objects built with this release. The use of this 
release requires that all the objects are recompiled with either this release 
or CGT 7.1 Beta 2.

Since CGT 7.0 is already in production we don't plan to change the EABI 
behavior in that release. The EABI support is hidden in this release so is
not available except for specific customers.

Based on the feedback we've received, we believe that in the long run this 
change will be beneficial. Here are some common questions and answers:

Q: I am currently using CGT 7.2 (Build 2) Alpha1. What is the impact when I 
   upgrade to CGT 7.2 (beta 1 or later)?
A: All code needs to be rebuilt with CGT 7.2 beta 1 or later).

Q: I am using CGT 7.1 Beta 1. Can I continue to use this release?
A: We recommend upgrading to CGT 7.1 Beta 2. If objects built with release 
CGT 7.2 (beta 1 or later) need to be used then CGT 7.1 Beta 2 or CGT 7.2 (beta 1 
or later) must be used.

Q: What happens if I mix incompatible enum type objects?
A: The linker will generate a fatal error indicating that the object files are 
incompatible:
   fatal error: object files have incompatible enumeration types
   ("file1.obj" = --enum_type=packed, "file2.obj" = --enum_type=[unpacked|int])

Q: I am using 7.0 for ELF. When I move to 7.2 release what is the impact?
A: There are two options:
   - Rebuild all code using 7.2 compiler.
   - Use the CGT 7.2 compiler hidden option --enum_type=packed to get the 
     7.0 ELF behavior.


-------------------------------------------------------------------------------
6) New CLINK and RETAIN Pragmas
-------------------------------------------------------------------------------

6.1) COFF and EABI Conditional Linking Models
---------------------------------------------

In COFF ABI mode, if an object file is explicitly included in the link step,
or is pulled in from an object library to resolve a symbol definition, then, 
by default, the linker will include all of the sections in such an object file
into the linked output file. This can be inefficient if a given object file 
contains many sections that are not needed in the link but are included anyway
because one section in the file resolves a symbol.

To alleviate this inefficiency in COFF, the CGT has for a long time provided 
a .clink assembler directive which allows the compiler or a user to indicate
that a section is eligible for removal by the linker if it is not referenced.
This linker process is sometimes referred to as conditional linking.

In EABI mode, the default linker behavior with regards to conditional linking
is the opposite of COFF. In the EABI conditional linking model, a section is
assumed by default to be eligible for removal by the linker unless it is
referenced.

This difference between the COFF and EABI conditional linking models can
present an obstacle to a developer that is trying to migrate an existing
COFF application to use the EABI model. Under the EABI model, if you want to 
ensure that a function or data object is included in the linked output even
though it is not referenced anywhere in the program, you can use the 
--retain linker option or create an unresolved reference to the symbol 
using the -u linker option.


6.2) The CLINK and RETAIN Pragmas
---------------------------------

To help developers with the transition of existing COFF applications to the
EABI model and the creation of new applications, the CGT 7.2 release supports 
two new pragmas that are available for use in C/C++ source files:

  #pragma RETAIN(<symbol>)
 
     When this pragma is applied to a function or data object symbol, it
     instructs the compiler to generate a .retain assembler directive into
     the section that contains the definition of the symbol. This provides
     a mechanism for the developer to indicate in their C/C++ source that
     a section containing the specified symbol is to be considered 
     ineligible for removal during conditional linking.

     If the RETAIN pragma is applied to a symbol that is defined in its
     own subsection, then the .retain directive is applied to that 
     section. If the RETAIN pragma is applied to a symbol that is 
     defined in a section that contains other function or data object
     definitions, then the symbol will be put into a retain subsection.

     For example, if red_fish is a function defined in the ".text" section
     and the user specifies #pragma RETAIN(red_fish) in their C/C++ source,
     then the compiler will place the definition of red_fish into a 
     subsection named ".text:retain".

  #pragma CLINK(<symbol>)

     When this pragma is applied to a function or data object symbol, it
     instructs the compiler to generate a .clink assembler directive into
     the section that contains the definition of the symbol. This provides
     a mechanism for the developer to indicate in their C/C++ source that
     a section containing the specified symbol is to be considered eligible
     for removal during conditional linking.

When compiling code for an interrupt function that is written in C/C++, the
compiler will generate a .retain directive into the section that contains
the definition of the interrupt function. This can be overridden by applying
a #pragma CLINK() to the interrupt function symbol.


6.3) The .clink and .retain Assembler Directives
------------------------------------------------

In addition to the existing .clink assembler directive, the CGT 7.2 release 
adds support for the new .retain assembler directive. These two directives 
help to provide the infrastructure needed to implement the CLINK and RETAIN 
pragmas described in section 6.2. They also provide a mechanism for assembly 
language developers to control whether or not a section is to be considered 
eligible for removal in the link step if it is not referenced.

  .clink ["<section name>"]

    If a "section name" argument is provided to the .clink directive, 
    the assembler will mark the specified section as eligible for removal
    by conditional linking. If no "section name" argument is specified, 
    then the currently active initialized section is marked as eligible
    for removal via conditional linking.

  .retain ["<section name>"]

    If a "section name" argument is provided to the .retain directive, 
    the assembler will mark the specified section as ineligible for removal
    by conditional linking. If no "section name" argument is specified, 
    then the currently active initialized section is marked as ineligible
    for removal via conditional linking.


-------------------------------------------------------------------------------
7) New --emit_warnings_as_errors Compiler Option
-------------------------------------------------------------------------------

The C6x CGT 7.2 release contains support for a compiler option:

	--emit_warnings_as_errors

which can also be specified with "-pdew".

This option instructs the compiler to treat any warnings that are detected 
during the compilation as errors.


-------------------------------------------------------------------------------
8) Run Length Encoding (RLE) Extended to Handle 24-bit Run Lengths
-------------------------------------------------------------------------------

The C6x CGT 7.2 release extends the run length encoding (RLE) compression 
format to handle 24-bit run length fields. In previous versions of the 
C6x CGT, the run length field in a given RLE entry was limited to a size
of 16-bits.

In cases where the support of 24-bit run lengths in the RLE comes into play,
the size of the RLE compressed data generated by the linker will be smaller
and the performance of the RLE decompression routine, __TI_decompress_rle24
in the runtime support library, will be improved.

-------------------------------------------------------------------------------
9) New __float2_t Type; Recommendations on the use of the "double" type
-------------------------------------------------------------------------------
In order to better support packed data compiler optimizations in the 
future, the use of the type "double" for *packed data* is now discouraged 
and its support may be discontinued in the future.  ("double" support is
NOT going away!)

There are several recommendations and changes as a result.  Note that
these changes do NOT break compatibility with older code (source files 
or object files).

(1) long long should be used for 64-bit packed integer data.  The double
    type should be used only for double-precision floating point values.

(2) There is a new type, __float2_t, that holds two floats and should
    be used instead of double for holding two floats.  For now, this new
    type is typedef'ed to double in c6x.h, but could be changed in the
    future to a structure or vector type to allow better optimization of
    packed data floats.  We recommend the use of __float2_t for any
    float x2 data instead of double.

(3) There are new __float2_t manipulation intrinsics (see below) that
    should be used to create and manipulate objects of type __float2_t.

(4) C66 intrinsics that deal with packed float data are now declared
    using __float2_t instead of double.  See the c6x.h RTS file.

(5) When using any intrinsic that involves __float2_t, c6x.h must be
    included.

(6) Certain intrinsics that used double to store fixed-point packed
    data have been deprecated.  They will still be supported in the
    near future, but their descriptions will be removed from the
    compiler user's guide (spru187).  Deprecated: _mpy2, _mpyhi, _mpyli,
    _mpysu4, _mpyu4, and _smpy2.  Use the long long versions instead.

New __float2_t manipulation intrinsics:

Return type   Name                      Description
-------------------------------------------------------------------------------
__float2_t    _lltof2 (long long)       Reinterprets long long as __float2_t
long long     _f2toll (__float2_t)      Reinterprets _float2_t as long long
__float2_t    _hif2_128 (__x128_t)      Extract high 64 bits      (C6600)
__float2_t    _lof2_128 (__x128_t)      Extract low 64 bits       (C6600)
__float2_t    _ftof2 (float, float)     Create __float2_t from two floats
float         _hif2 (__float2_t)        Extract high 32 bits
float         _lof2 (__float2_t)        Extract low 32 bits
__float2_t    _fdmv_f2 (__float2_t)     Explicit move             (C6400+)
__float2_t    _fdmvd_f2                 Explicit four-cycle move. (C6600)
__x128_t      _f2to128 (__float2_t, float2_t)
                                        Create a __x128_t out of two __float2_t

The following are intriniscs that allow loads and stores of 8 bytes to/from
memory.  Please see the Compiler User's Guide for more information.

      __float2_t & _amem8_f2 (void *ptr)
const __float2_t & _amem8_f2_const (void *ptr)
      __float2_t & _mem8_f2 (void *ptr)                            (6400)
const __float2_t & _mem8_f2_const (void *ptr)                      (6400)


For more information, please see
http://processors.wiki.ti.com/index.php/C6000_Intrinsics_and_Type_Double

-------------------------------------------------------------------------------
10) Early Adopter Version of Prelink Utility - prelink6x
-------------------------------------------------------------------------------

The C6000 Code Generation Tools Release v7.2.0 includes an early adopter 
version of a prelink utility, prelink6x, which can be used in the development
flow of a dynamic system to offload tasks that are normally performed by the 
dynamic linker/loader at load time. By reducing the work required of the 
dynamic linker/loader, the prelinker helps to reduce the load and/or startup 
time of a dynamic application.

A more detailed description of the prelink utility's functionality can be
found in the "prelink" sub-directory of this release distribution. Please
see the prelink_readme.txt in that directory for more details about the
prelink utility and some walk-through examples of how it is used.

-------------------------------------------------------------------------------
11) New --symdebug:keep_all_types Compiler Option
-------------------------------------------------------------------------------

The C6x CGT 7.2 release contains support for a compiler option:

        --symdebug:keep_all_types

This option instructs the parser to keep unreferenced type information 
(default for ELF with debug).

This option affects the ability to view unused types in the debugger that
are from a COFF executable. Use this option to view the details of a type
that is defined but not used to define any symbols. Such unused types are 
not included in the debug information by default for COFF. However, in EABI
mode, all types are included in the debug information and this option has
no effect.

-------------------------------------------------------------------------------
12) Linker MEMORY directive expressions
-------------------------------------------------------------------------------

The C6x CGT 7.2 release extends the linker's expression handling capability
to include linker command file MEMORY directive fields for origin and length.
Additionally, three new memory range address operators (start, size and end) 
will allow memory ranges to reference previously defined memory ranges.

Example:

/********************************************************/
/* Sample command file with MEMORY directive            */
/********************************************************/
#define ORIGIN 0x00000000
#define BUFFER 0x00000200
#define CACHE  0x00001000

MEMORY
{
  FAST_MEM (RX): origin = ORIGIN + CACHE length = 0x00001000 + BUFFER
  SLOW_MEM (RW): origin = end(FAST_MEM)  length = 0x00001800 - size(FAST_MEM)
  EXT_MEM  (RX): origin = 0x10000000     length = size(FAST_MEM) - CACHE
}

For more details please see spru186u for the 7.2 release.

-- End Of File --
