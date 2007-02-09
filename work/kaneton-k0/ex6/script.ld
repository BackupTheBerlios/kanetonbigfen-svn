PHDRS
{
	text PT_LOAD AT (0x100000);
	data PT_LOAD AT (0x200000);
}
SECTIONS
{
	. = 0x100000;
	.text :
	{
			*(.text*)
	} : text
	. = 0x200000;
	.data :
	{
		*(.data*)
	} : data
	.rodata :
	{
		*(.rodata*)
	} : data
	.bss :
	{
		*(.bss*)

	} : data
}
