cmake_minimum_required(VERSION 2.8)

project(QPUassembler)

file(GLOB asmSrc
	"qpu_assembler.h"
	"qpu_assembler.c"
)

add_library(QPUassembler SHARED ${asmSrc})
target_compile_options(QPUassembler PRIVATE -Wall -Werror=implicit-function-declaration -std=c11)
