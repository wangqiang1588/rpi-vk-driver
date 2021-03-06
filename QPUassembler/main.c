#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "qpu_assembler.h"

int main()
{
	char asm_code[] =
			"sig_none ; nop = nop(r0, r0) ; nop = nop(r0, r0) ;"
			"sig_none ; nop = nop(r0, r0) ; nop = nop(r0, r0) ;"
			"sig_small_imm ; tlb_color_all = or.always(b, b, nop, -1) ; nop = nop(r0, r0) ;"
			"sig_end ; nop = nop(r0, r0) ; nop = nop(r0, r0) ;"
			"sig_none ; nop = nop(r0, r0) ; nop = nop(r0, r0) ;"
			"sig_unlock_score ; nop = nop(r0, r0) ; nop = nop(r0, r0) ;"
				"\0";

	printf("%s", asm_code);

	unsigned num_instructions = 0;
	char* ptr = asm_code;
	while(ptr && *ptr != '\0')
	{
		ptr = strstr(ptr, ";");
		if(!ptr) break;
		ptr = strstr(ptr+(ptr!=0), ";");
		if(!ptr) break;
		ptr = strstr(ptr+(ptr!=0), ";");
		if(ptr)
		{
			ptr += 1;
			num_instructions += 1;
		}
	}

	//printf("Num instructions: %i\n", num_instructions);

	if(!num_instructions)
	{
		return 0;
	}

	uint64_t instruction_size = sizeof(uint64_t)*num_instructions;
	uint64_t* instructions = malloc(instruction_size);

	assemble_qpu_asm(asm_code, instructions);

	for(int c = 0; c < instruction_size; ++c)
	{
		unsigned char d = ((char*)instructions)[c];
		//printf("%#x,\t", d);
		if((c+1)%8==0)
		{
			//printf("\n");
		}
	}

	printf("\n\n");

	for(int c = 0; c < num_instructions; ++c)
	{
			disassemble_qpu_asm(instructions[c]);
	}

	const char fragBytes[] =
	{
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x10,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x10,
		0x80, 0x7d, 0x82, 0x15, 0xa7, 0xb, 0x2, 0x10,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x30,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x10,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x50
	};

	unsigned numFragInstructions = sizeof(fragBytes) / sizeof(uint64_t);

	const char vertBytes[] =
	{
		0x80, 0x1f, 0x82, 0x2, 0x27, 0x10, 0x2, 0xd0,
		00, 0x1a, 0x20, 00, 0x67, 0x4c, 0x2, 0xe0,
		0x37, 00, 0xc2, 0x20, 0xe0, 0x49, 00, 0x10,
		0x7, 00, 0x9c, 0x20, 0xe1, 0x49, 00, 0x10,
		0x77, 0x2, 0xc2, 0x27, 0x22, 0x40, 0x12, 0x10,
		0x17, 00, 0x9c, 0x20, 0xe3, 0x49, 00, 0x10,
		0xc0, 0x76, 0x9e, 0x7, 0x27, 00, 0x22, 0x10,
		00, 0x1a, 00, 00, 0x67, 0x5c, 0x2, 0xe0,
		0x80, 0x7d, 0x2, 0x15, 0x27, 0xc, 0x2, 0x10,
		0x80, 0x7d, 0x82, 0x15, 0x27, 0xc, 0x2, 0x10,
		0xc0, 0xf, 0x9c, 0x15, 0x27, 0xc, 0x2, 0x10,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x30,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x10,
		00, 0x70, 0x9e, 00, 0xe7, 0x9, 00, 0x10,
	};

	unsigned numVertInstructions = sizeof(vertBytes) / sizeof(uint64_t);

	printf("\n\n");

	for(int c = 0; c < numVertInstructions; ++c)
	{
		disassemble_qpu_asm(((uint64_t*)vertBytes)[c]);
	}

	printf("\n\n");

	for(int c = 0; c < numFragInstructions; ++c)
	{
		disassemble_qpu_asm(((uint64_t*)fragBytes)[c]);
	}

	return 0;
}
