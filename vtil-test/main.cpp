/*
将下面这段代码lift到vtil

LREGDW 0x68
LREGQ 0x58
LCONSTQ 0x140003640
ADDQ
SREGQ 0x70
WRITEDW





*/


#include<vtil/vtil>

int main()
{
	auto block = vtil::basic_block::begin(0x14000AC83);
	vtil::register_desc reg(vtil::register_virtual, 64, 32, (0x68%8)*8);
	vtil::register_desc reg2(vtil::register_virtual, 64, 64, (0x58 % 8) * 8);
	block->push(reg);
	block->push(reg2);
	block->push(0x140003640);
	

	vtil::debug::dump(block->owner);

	return 0;
}