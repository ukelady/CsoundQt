<CsoundSynthesizer>

; Id: G03_TR17-2.CSD mg (2006, rev.2009)
; author: marco gasperini (marcogsp at yahoo dot it)

; G.M. Koenig
; ESSAY (1957)

<CsOptions>
-W -f -oG03_TR17-2.wav
</CsOptions>

<CsInstruments>

sr     = 192000
kr     = 19200
ksmps  = 10
nchnls = 1

;=============================================
; 272.17 TRANSPOSITION (RESAMPLING)
;=============================================
	instr 1
itrasp	= p4
ifile	= p5

a1	diskin2 ifile, itrasp

ifrq	= 96000*p4		; anti-aliasing filter
a1	tonex a1 , ifrq , 10
a1	tonex a1 , ifrq , 10

	out a1
	endin
;=============================================

</CsInstruments>
<CsScore>
t0	4572		; 76.2 cm/sec. tape speed (durations in cm)

;			p4	p5
;			itrasp	ifile
i1	0	1870	.6944	"G01.wav"	; 34.72/50

e

</CsScore>
</CsoundSynthesizer>