
C_FILES	:= $(wildcard *.c)
IR_FILES	:= $(patsubst %.c,%.ll,${C_FILES})
BC_FILES	:= $(patsubst %.c,%.bc,${C_FILES})

CLANG_ROOT	:= ${HOME}/Programming/llvm-project/build-debug/bin
CLANG := ${CLANG_ROOT}/clang
CLANG++ := ${CLANG_ROOT}/clang++
OPT  := ${CLANG_ROOT}/opt


all: ${IR_FILES} ${BC_FILES}


${IR_FILES}: %.ll : %.c
	${CLANG} -S -emit-llvm $< -g


${BC_FILES}: %.bc : %.c
	${CLANG} -c -emit-llvm $< -g