.include "xc.inc"   ; required "boiler-plate" (BP)

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF &/* BKBUG_ON & */GWRP_ON & GCP_ON & JTAGEN_OFF
    .bss	; put the following labels in RAM
counter:
    .space 2	; a variable that takes two bytes (we won?t use
		; it for now, but put here to make this a generic
		; template to be used later).
stack:
    .space 32	; this will be our stack area, needed for func calls
    
.text		; BP (put the following data in ROM(program memory))

;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main	    ;BP
_main:

    bclr CLKDIV,#8  ;BP
    nop
;; --- Begin your program below here ---
    mov #0x9fff, w0
    mov w0, AD1PCFG
    mov #0b1111111111111110, w0
    mov w0, TRISA
    mov #0x0001, w0
    mov w0, LATA
    call delay_one_hundred_us
    call delay_one_ms
    foreverLoop:
    call write_bit_stream
    bra foreverLoop
    nop
    write_bit_stream:
    call high_time
    BCLR LATA, #0
    call low_time
    BSET LATA, #0
    return
    high_time:
		;2 cycles for function call
    repeat #9	;1 cycle to load and prep
    nop		;3+1 cycles to execute NO
    return	
    low_time:
		;2 cycles for function call
    repeat #24	;1 cycle to load and prep
    nop		;3+1 cycles to execute NO
    return
    delay_one_ms:
    repeat #15993
    nop
    return
    delay_one_hundred_us:
    repeat #1593
    nop
    return
    .end
    
; this doesn?t actually end anything. Does not translate to assembly
; code. Just a way to tell the compiler we are done with this file.
    
    

