Symbol table level 0
 5522080        real  BASIC  basicdt   1          siz     8
 5522176     integer  BASIC  basicdt   0          siz     4
 5522272        char  BASIC  basicdt   2          siz     1
 5522368     boolean  BASIC  basicdt   3          siz     4
 5522464         exp  knd 5 0  typ 5522560  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5522752       trexp  knd 5 0  typ 5522848  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5523040         sin  knd 5 0  typ 5523136  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5523328         cos  knd 5 0  typ 5523424  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5523616       trsin  knd 5 0  typ 5523712  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5523904        sqrt  knd 5 0  typ 5524000  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5524192       round  knd 5 0  typ 5524288  lvl  0  siz     0  off     0
(FUNCTION real
          real)
 5524480      iround  knd 5 0  typ 5524576  lvl  0  siz     0  off     0
(FUNCTION integer
          real)
 5524768         ord  knd 5 0  typ 5524864  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 5525056         new  knd 5 0  typ 5525152  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 5525344       trnew  knd 5 0  typ 5525440  lvl  0  siz     0  off     0
(FUNCTION integer
          integer)
 5525632       write  knd 5 0  typ 5525728  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 5525920     writeln  knd 5 0  typ 5526016  lvl  0  siz     0  off     0
(FUNCTION NULL
          char)
 5526208      writef  knd 5 0  typ 5526304  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 5526496    writelnf  knd 5 0  typ 5526592  lvl  0  siz     0  off     0
(FUNCTION NULL
          real)
 5526784      writei  knd 5 0  typ 5526880  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 5527072    writelni  knd 5 0  typ 5527168  lvl  0  siz     0  off     0
(FUNCTION NULL
          integer)
 5527360        read  knd 5 0  typ 5527456  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 5527648      readln  knd 5 0  typ 5527744  lvl  0  siz     0  off     0
(FUNCTION NULL
          NULL)
 5527936         eof  knd 5 0  typ 5528032  lvl  0  siz     0  off     0
(FUNCTION boolean
          NULL)
Symbol table level 1
 5554272     complex  TYPE   typ 5553984  lvl  1  siz    16  off     0
(RECORD (re real)
        (im real))
 5555072         red  CONST  typ INTEGER  val  0
 5555232       white  CONST  typ INTEGER  val  1
 5555392        blue  CONST  typ INTEGER  val  2
 5555584       color  TYPE   typ 5555488  lvl  1  siz     4  off     0
  0 ..   2
 5556000      person  TYPE   typ 5557824  lvl  1  siz    48  off     0
(RECORD (age integer)
        (friend (^ person))
        (location (RECORD (re real)
                          (im real)))
        (favorite   0 ..   2)
        (salary real))
 5556192          pp  TYPE   typ 5556096  lvl  1  siz     8  off     0
(^ person)
 5558720        john  VAR    4 typ 5556096  lvl  1  siz     8  off     0
(^ person)
yyparse result =        0
(program graph1
(progn output)
(progn (:= (aref (^ (aref (^ john) 8)) 24) 4.500000e+00)))
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
	movsd	.LC1(%rip),%xmm0   	#  4.500000 -> %xmm0
	movq	-32(%rbp),%rax     	#  john -> %rax
	movq	8(%rax),%rcx         	#  ^.[8+%rax] -> %rcx
	movsd	%xmm0,24(%rcx)         	#  %xmm0 -> ^. [24+%rcx]
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   graph1, .-graph1
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata
	.align  8
.LC1:
	.long	0   	#  4.500000
	.long	1074921472

        .ident  "CS 375 Compiler - Fall 2020"
