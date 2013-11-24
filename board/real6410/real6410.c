/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <s3c6410.h>

/* ------------------------------------------------------------------------- */
#define DM9000_Tacs	(0x0)	/* 0clk		address set-up		*/
#define DM9000_Tcos	(0x0)	/* 4clk		chip selection set-up	*/
#define DM9000_Tacc	(0x7)	/* 14clk	access cycle		*/
#define DM9000_Tcoh	(0x0)	/* 1clk		chip selection hold	*/
#define DM9000_Tah	(0x0)	/* 4clk		address holding time	*/
#define DM9000_Tacp	(0x0)	/* 6clk		page mode access cycle	*/
#define DM9000_PMC	(0x0)	/* normal(1data)page mode configuration	*/

static inline void delay(unsigned long loops)
{
	__asm__ volatile ("1:\n" "subs %0, %1, #1\n"
			  "bne 1b"
			  : "=r" (loops) : "0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

static void dm9000_pre_init(void)
{
	SROM_BW_REG &= ~(0xf << 4);
	SROM_BW_REG |= ( 1 << 4);
	SROM_BC1_REG = ((DM9000_Tacs << 28) + (DM9000_Tcos << 24) +
			(DM9000_Tacc << 16) + (DM9000_Tcoh << 12) +
			(DM9000_Tah << 8) + (DM9000_Tacp << 4) + DM9000_PMC);
}

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	dm9000_pre_init();

	gd->bd->bi_arch_number = MACH_TYPE;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

int dram_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

#ifdef CONFIG_DISPLAY_BOARDINFO
int checkboard(void)
{
	printf("Board:   REAL6410\n");
	return 0;
}
#endif

#ifdef CONFIG_ENABLE_MMU
ulong virt_to_phy_real6410(ulong addr)
{
	if ((0xc0000000 <= addr) && (addr < 0xc8000000))
		return (addr - 0xc0000000 + 0x50000000);
	else
		printf("do not support this address : %08lx\n", addr);

	return addr;
}
#endif

#if (CONFIG_COMMANDS & CFG_CMD_NAND) && defined(CFG_NAND_LEGACY)
#include <linux/mtd/nand.h>
extern struct nand_chip nand_dev_desc[CFG_MAX_NAND_DEVICE];
void nand_init(void)
{
	nand_probe(CFG_NAND_BASE);
        if (nand_dev_desc[0].ChipID != NAND_ChipID_UNKNOWN) {
                print_size(nand_dev_desc[0].totlen, "\n");
        }
}
#endif
