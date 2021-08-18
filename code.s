Symbol table level 0
 6222496        real  BASIC  basicdt   1          siz     8
 6222592     integer  BASIC  basicdt   0          siz     4
 6222688        char  BASIC  basicdt   2          siz     1
 6222784     boolean  BASIC  basicdt   3          siz     4
 6222880         exp  knd 5 0  typ 6222976  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6223168       trexp  knd 5 0  typ 6223264  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6223456         sin  knd 5 0  typ 6223552  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6223744         cos  knd 5 0  typ 6223840  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6224032       trsin  knd 5 0  typ 6224128  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6224320        sqrt  knd 5 0  typ 6224416  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6224608       round  knd 5 0  typ 6224704  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 6224896      iround  knd 5 0  typ 6224992  lvl  0  siz     0  off     0
(FUNCTION integer
          real)
 6225184         ord  knd 5 0  typ 6225280  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 6225472         new  knd 5 0  typ 6225568  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 6225760       trnew  knd 5 0  typ 6225856  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 6226048       write  knd 5 0  typ 6226144  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 6226336     writeln  knd 5 0  typ 6226432  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 6226624      writef  knd 5 0  typ 6226720  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 6226912    writelnf  knd 5 0  typ 6227008  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 6227200      writei  knd 5 0  typ 6227296  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 6227488    writelni  knd 5 0  typ 6227584  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 6227776        read  knd 5 0  typ 6227872  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 6228064      readln  knd 5 0  typ 6228160  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 6228352         eof  knd 5 0  typ 6228448  lvl  0  siz     0  off     0
(FUNCTION boolean
          NULL)
Symbol table level 1
 6254688     complex  TYPE   typ 6254400  lvl  1  siz    16  off     0
(RECORD (re real)
        (im real))
 6255488         red  CONST  typ INTEGER  val  0
 6255648       white  CONST  typ INTEGER  val  1
 6255808        blue  CONST  typ INTEGER  val  2
 6256000       color  TYPE   typ 6255904  lvl  1  siz     4  off     0
  0 ..   2
 6256416      person  TYPE   typ 6258240  lvl  1  siz    48  off     0
(RECORD (age integer)
        (friend (^ person))
        (location (RECORD (re real)
                          (im real)))
        (favorite   0 ..   2)
        (salary real))
 6256608          pp  TYPE   typ 6256512  lvl  1  siz     8  off     0
(^ person)
 6259136        john  VAR    4 typ 6256512  lvl  1  siz     8  off     0
(^ person)
yyparse result =        0
(program graph1
(progn output)
(progn (:= (aref (^ john) 0) 19)))
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
	movl	$19,%eax         	#  19 -> %eax
	movq	-32(%rbp),%rcx     	#  john -> %rcx
	movl	%eax,0(%rcx)         	#  %eax -> ^. [0+%rcx]
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
