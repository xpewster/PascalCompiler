Symbol table level 0
 34366112        real  BASIC  basicdt   1          siz     8
 34366208     integer  BASIC  basicdt   0          siz     4
 34366304        char  BASIC  basicdt   2          siz     1
 34366400     boolean  BASIC  basicdt   3          siz     4
 34366496         exp  knd 5 0  typ 34366592  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34366784       trexp  knd 5 0  typ 34366880  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34367072         sin  knd 5 0  typ 34367168  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34367360         cos  knd 5 0  typ 34367456  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34367648       trsin  knd 5 0  typ 34367744  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34367936        sqrt  knd 5 0  typ 34368032  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34368224       round  knd 5 0  typ 34368320  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 34368512      iround  knd 5 0  typ 34368608  lvl  0  siz     0  off     0
(FUNCTION integer
          real)
 34368800         ord  knd 5 0  typ 34368896  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 34369088         new  knd 5 0  typ 34369184  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 34369376       trnew  knd 5 0  typ 34369472  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 34369664       write  knd 5 0  typ 34369760  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 34369952     writeln  knd 5 0  typ 34370048  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 34370240      writef  knd 5 0  typ 34370336  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 34370528    writelnf  knd 5 0  typ 34370624  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 34370816      writei  knd 5 0  typ 34370912  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 34371104    writelni  knd 5 0  typ 34371200  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 34371392        read  knd 5 0  typ 34371488  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 34371680      readln  knd 5 0  typ 34371776  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 34371968         eof  knd 5 0  typ 34372064  lvl  0  siz     0  off     0
(FUNCTION boolean
          NULL)
Symbol table level 1
 34397920         ptr  VAR    4 typ 34397824  lvl  1  siz     8  off     0
(^ real)
 34398016        john  VAR    4 typ 34397824  lvl  1  siz     8  off     8
(^ real)
yyparse result =        0
(program graph1
(progn output)
(progn (:= ptr john)))
# ---------------- Beginning of Generated Code --------------------
        .file   "foo"
        .text
        .globl graph1
        .type   graph1, @function
graph1:
.LFB0:
	.cfi_startproc
	pushq	%rbp              # save base pointer on stack
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp        # move stack pointer to base pointer
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
        subq	$32, %rsp 	  # make space for this stack frame
	movq	%rbx, %r9        # save %rbx (callee-saved) in %r9
# ------------------------- begin Your code -----------------------------
	movq	-8(%rbp),%rax     	#  john -> %rax
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   graph1, .-graph1
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata

        .ident  "CS 375 Compiler - Fall 2020"
