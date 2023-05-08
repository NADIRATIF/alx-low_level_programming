#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void ck_elf(unsigned char *e_ident);
void p_m(unsigned char *e_ident);
void p_c(unsigned char *e_ident);
void p_d(unsigned char *e_ident);
void p_v(unsigned char *e_ident);
void p_abi(unsigned char *e_ident);
void p_osabi(unsigned char *e_ident);
void p_t(unsigned int e_type, unsigned char *e_ident);
void p_e(unsigned long int e_entry, unsigned char *e_ident);
void c_elf(int elf);

/**
 * ck_elf - Checks if an ELF file.
 * @e_i: pointer to an array containing the ELF magic numbers.
 *
 * D: e_i != ELF file - exit code 98.
 */
void ck_elf(unsigned char *e_i)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if (e_i[i] != 127 &&
		    e_i[i] != 'E' &&
		    e_i[i] != 'L' &&
		    e_i[i] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * p_m - Prints the magic numbers.
 * @e_i: pointer to an array containing the ELF magic numbers.
 *
 * D: Magic numbers 7f 45 4c 46 ...
 */
void p_m(unsigned char *e_i)
{
	int i;

	printf("  Magic:   ");

	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", e_i[i]);

		if (i == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * p_c - function to prints the class of an ELF header.
 * @e_i: pointer to an array containing the ELF class.
 */
void p_c(unsigned char *e_i)
{
	printf("  Class:                             ");

	switch (e_i[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", e_i[EI_CLASS]);
	}
}

/**
 * p_d - function to prints the data of an ELF header.
 * @e_i: pointer to an array containing the ELF class.
 */
void p_d(unsigned char *e_i)
{
	printf("  Data:                              ");

	switch (e_i[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", e_i[EI_CLASS]);
	}
}

/**
 * p_v - function to prints the version of an ELF header.
 * @e_i: pointer to an array containing the ELF version.
 */
void p_v(unsigned char *e_i)
{
	printf("  Version:                           %d",
	       e_i[EI_VERSION]);

	switch (e_i[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/**
 * p_osabi - function to prints the OS/ABI of an ELF header.
 * @e_i: pointer to an array containing the ELF version.
 */
void p_osabi(unsigned char *e_i)
{
	printf("  OS/ABI:                            ");

	switch (e_i[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
	default:
		printf("<unknown: %x>\n", e_i[EI_OSABI]);
	}
}

/**
 * p_abi - function to prints the ABI version of an ELF header.
 * @e_i: pointer to an array containing the ELF ABI version.
 */
void p_abi(unsigned char *e_i)
{
	printf("  ABI Version:                       %d\n",
	       e_i[EI_ABIVERSION]);
}

/**
 * p_t - function to prints the type of an ELF header.
 * @e_t: the ELF type.
 * @e_i: pointer to an array containing the ELF class.
 */
void p_t(unsigned int e_t, unsigned char *e_i)
{
	if (e_i[EI_DATA] == ELFDATA2MSB)
		e_t >>= 8;

	printf("  Type:                              ");

	switch (e_t)
	{
	case ET_NONE:
		printf("NONE (None)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", e_t);
	}
}

/**
 * p_e - function prints the entry point of an ELF header.
 * @e_e: the address of the ELF entry point.
 * @e_i: pointer to an array containing the ELF class.
 */
void p_e(unsigned long int e_e, unsigned char *e_i)
{
	printf("  Entry point address:               ");

	if (e_i[EI_DATA] == ELFDATA2MSB)
	{
		e_e = ((e_e << 8) & 0xFF00FF00) |
			  ((e_e >> 8) & 0xFF00FF);
		e_e = (e_e << 16) | (e_e >> 16);
	}

	if (e_i[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_e);

	else
		printf("%#lx\n", e_e);
}

/**
 * c_elf - function to closes an ELF file.
 * @elf: the file descriptor of the ELF file.
 *
 * Description: If the file cannot be closed - exit code 98.
 */
void c_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", elf);
		exit(98);
	}
}

/**
 * main - presents the details found in the ELF header
 * located at the beginning of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0.
 *
 * Description: file != ELF File || function fails - exit code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int op, rd;

	op = open(argv[1], O_RDONLY);
	if (op == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		c_elf(op);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	rd = read(op, header, sizeof(Elf64_Ehdr));
	if (rd == -1)
	{
		free(header);
		c_elf(op);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	ck_elf(header->e_ident);
	printf("ELF Header:\n");
	p_m(header->e_ident);
	p_c(header->e_ident);
	p_d(header->e_ident);
	p_v(header->e_ident);
	p_osabi(header->e_ident);
	p_abi(header->e_ident);
	p_t(header->e_type, header->e_ident);
	p_e(header->e_entry, header->e_ident);

	free(header);
	c_elf(op);
	return (0);
}
