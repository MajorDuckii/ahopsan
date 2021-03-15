
C_FILES	:= $(wildcard *.c)
IR_FILES	:= $(patsubst %.c,%.ll,${C_FILES})
BC_FILES	:= $(patsubst %.c,%.bc,${C_FILES})
ASANIR_FILES	:= $(patsubst %.c,%.asan.ll,${C_FILES})
ASANBC_FILES	:= $(patsubst %.c,%.asan.bc,${C_FILES})
ASANEXE_FILES	:= $(patsubst %.c,%.asan.exe,${C_FILES})

CLANG_ROOT	:= ${HOME}/Programming/llvm-project/build-debug/bin
CLANG := ${CLANG_ROOT}/clang
CLANG++ := ${CLANG_ROOT}/clang++
OPT  := ${CLANG_ROOT}/opt


OPT2	:= 0
ifeq (${OPT2}, 1)
	CLANG 	:=  ${CLANG} -O2
endif

all: ${IR_FILES} ${BC_FILES} ${ASANIR_FILES} ${ASANBC_FILES} ${ASANEXE_FILES}


${IR_FILES}: %.ll : %.c
	${CLANG} -g -S -emit-llvm $< -o $@


${BC_FILES}: %.bc : %.c
	${CLANG} -g -c -emit-llvm $< -o $@


${ASANIR_FILES}: %.asan.ll : %.c
	${CLANG} -g -S -emit-llvm -fsanitize=address  $< -o $@


${ASANBC_FILES}: %.asan.bc : %.c
	${CLANG} -g -c -emit-llvm -fsanitize=address  $< -o $@  


${ASANEXE_FILES}: %.asan.exe : %.c
	${CLANG} -g -fsanitize=address $< -o $@


clean: 
	rm -rf ${IR_FILES} ${BC_FILES} ${ASANIR_FILES} ${ASANBC_FILES} ${ASANEXE_FILES}
