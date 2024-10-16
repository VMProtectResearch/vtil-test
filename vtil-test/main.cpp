#include<vtil/vtil>
static constexpr vtil::register_desc make_virtual_register(uint8_t context_offset, uint8_t size)
{
	fassert(((context_offset & 7) + size) <= 8 && size);

	return {
		vtil::register_virtual,
		(size_t)context_offset / 8,
		size * 8,
		(context_offset % 8) * 8
	};
}
int main()
{
	auto block = vtil::basic_block::begin(0x14000AC83);

	// mov qword ptr [rax+0x140003640], 1337
	block->mov(make_virtual_register(0x58, 8), X86_REG_RAX);
	block->push(make_virtual_register(0x58, 8));
	block->push(vtil::operand(0x140003640,64));
	auto [o1, o2] = block->tmp(64, 64);
	block->pop(o2);
	block->pop(o1);
	block->add(o1, o2); // ignore eflags
	block->push(o1);
	block->pop(make_virtual_register(0x70, 8));
	block->str(make_virtual_register(0x70, 8), 0, 1337);
	// 

	vtil::debug::dump(block);

	vtil::optimizer::apply_all(block);

	vtil::debug::dump(block);

	return 0;
}