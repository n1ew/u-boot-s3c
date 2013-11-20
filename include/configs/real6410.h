/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <gj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * (C) Copyright 2013
 * Sh. Niew <shniew@gmail.com>
 *
 * Configuation settings for the REAL6410 board.
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

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_S3C6410		1		/* in a SAMSUNG S3C6410 SoC	*/
#define CONFIG_S3C64XX		1		/* in a SAMSUNG S3C64XX Family	*/
#define CONFIG_REAL6410		1		/* on a CoreWind REAL6410 Board	*/

#define MEMORY_BASE_ADDRESS	0x50000000

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000	/* REAL6410 has 12MHz input clock */

#define CONFIG_MEMORY_UPPER_CODE

#undef CONFIG_USE_IRQ				/* we don't need IRQ/FIQ stuff */

#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG

/*
 * Architecture magic and machine type
 */
#define MACH_TYPE		2990
#define UBOOT_MAGIC		(0x43090000 | MACH_TYPE)

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#undef CONFIG_SKIP_RELOCATE_UBOOT

/*
 * Size of malloc() pool
 */
#define CFG_MALLOC_LEN		(CFG_ENV_SIZE + 1024 * 1024)
#define CFG_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

#define CFG_STACK_SIZE		(512 * 1024)

/*
 * Hardware drivers
 */
#define CONFIG_DRIVER_DM9000    1	/* we have a DM9000 on-board	*/
#define CONFIG_DM9000_BASE      0x18000300
#define CONFIG_DM9000_USE_16BIT
#define DM9000_IO               CONFIG_DM9000_BASE
#define DM9000_DATA             (CONFIG_DM9000_BASE + 0x4)

/*
 * select serial console configuration
 */
#define CONFIG_SERIAL1          1	/* we use SERIAL 1 on REAL6410	*/

#define CFG_HUSH_PARSER			/* use "hush" command parser	*/
#ifdef CFG_HUSH_PARSER
#define CFG_PROMPT_HUSH_PS2	"> "
#endif

#define CONFIG_CMDLINE_EDITING

/***********************************************************
 * RTC
 ***********************************************************/
#define CONFIG_RTC_S3C64XX	1

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200

/***********************************************************
 * Command definition
 ***********************************************************/
#define CONFIG_COMMANDS \
			(CONFIG_CMD_DFL	| \
			CFG_CMD_CACHE	| \
			CFG_CMD_REGINFO	| \
			CFG_CMD_NAND	| \
			/*CFG_CMD_MOVINAND|*/ \
			/*CFG_CMD_ONENAND|*/ \
			CFG_CMD_PING	| \
			/*CFG_CMD_USB	|*/ \
			/*CFG_CMD_FAT	|*/ \
			CFG_CMD_DATE	| \
			CFG_CMD_ECHO	| \
		 	CFG_CMD_RUN	| \
			CFG_CMD_ELF) \
			& ~(CFG_CMD_IMLS| \
			    CFG_CMD_FLASH)

/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
#include <cmd_confdefs.h>

#define CONFIG_BOOTDELAY	3

#define CONFIG_ZERO_BOOTDELAY_CHECK

#if (CONFIG_COMMANDS & CFG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

/*
 * Miscellaneous configurable options
 */
#define CFG_LONGHELP			/* undef to save memory		*/
#define CFG_PROMPT	"U-Boot > "	/* Monitor Command Prompt	*/
#define CFG_CBSIZE	256		/* Console I/O Buffer Size	*/
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)	/* Print Buffer Size	*/
#define CFG_MAXARGS	16		/* max number of command args	*/
#define CFG_BARGSIZE	CFG_CBSIZE	/* Boot Argument Buffer Size	*/

#define CFG_MEMTEST_START	MEMORY_BASE_ADDRESS	/* memtest works on	*/
#define CFG_MEMTEST_END	(MEMORY_BASE_ADDRESS+0x7e00000)	/* 126 MB in DRAM	*/

#define CFG_LOAD_ADDR		MEMORY_BASE_ADDRESS	/* default load address	*/

#undef CFG_CLKS_IN_HZ			/* everything, incl board info, in Hz */

/* the PWM TImer 4 uses a counter of 15625 for 10 ms, so we need */
/* it to wrap 100 times (total 1562500) to get 1 sec. */
#define CFG_HZ			1562500		// at PCLK 50MHz

/* valid baudrates */
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	0x40000		/* regular stack 256KB */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 * 1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4 * 1024)	/* FIQ stack */
#endif

/*
#define CONFIG_CLK_800_133_66
#define CONFIG_CLK_666_133_66
*/
#define CONFIG_CLK_532_133_66
/*
#define CONFIG_CLK_400_133_66
#define CONFIG_CLK_400_100_50
#define CONFIG_CLK_OTHERS
*/

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

#if defined(CONFIG_CLK_666_133_66)	/* FIN 12MHz, Fout 666MHz */
#define APLL_MDIV	333
#define APLL_PDIV	3
#define APLL_SDIV	1
#undef  CONFIG_SYNC_MODE		/* ASYNC mode */
#elif defined(CONFIG_CLK_532_133_66)	/* FIN 12MHz, Fout 532MHz */
#define APLL_MDIV	266
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE		/* SYNC mode */
#elif defined(CONFIG_CLK_400_133_66) || defined(CONFIG_CLK_800_133_66)	/* FIN 12MHz, Fout 800MHz */
#define APLL_MDIV	400
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE		/* SYNC mode */
#elif defined(CONFIG_CLK_400_100_50)	/* FIN 12MHz, Fout 400MHz */
#define APLL_MDIV	400
#define APLL_PDIV	3
#define APLL_SDIV	2
#define CONFIG_SYNC_MODE		/* SYNC mode */
#elif defined(CONFIG_CLK_OTHERS)	/* Others PLL value, please define here */
#define APLL_MDIV	266
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE
#else
#error "Not Support Fequency or Mode!! you have to setup right configuration."
#endif

/*#define CONFIG_CLKSRC_CLKUART*/

#define CONFIG_UART_66	/* default clock value of CLK_UART */

#define APLL_VAL	set_pll(APLL_MDIV, APLL_PDIV, APLL_SDIV)
/* prevent overflow */
#define Startup_APLL	(CONFIG_SYS_CLK_FREQ/(APLL_PDIV<<APLL_SDIV)*APLL_MDIV)

/* fixed MPLL 533MHz */
#define MPLL_MDIV	266
#define MPLL_PDIV	3
#define MPLL_SDIV	1

#define MPLL_VAL	set_pll(MPLL_MDIV, MPLL_PDIV, MPLL_SDIV)
/* prevent overflow */
#define Startup_MPLL	((CONFIG_SYS_CLK_FREQ)/(MPLL_PDIV<<MPLL_SDIV)*MPLL_MDIV)

#if defined(CONFIG_CLK_800_133_66)
#define Startup_APLLdiv		0
#define Startup_HCLKx2div	2
#elif defined(CONFIG_CLK_400_133_66)
#define Startup_APLLdiv		1
#define Startup_HCLKx2div	2
#else
#define Startup_APLLdiv		0
#define Startup_HCLKx2div	1
#endif

#define	Startup_PCLKdiv		3
#define Startup_HCLKdiv		1
#define Startup_MPLLdiv		1

#define CLK_DIV_VAL	((Startup_PCLKdiv<<12)|(Startup_HCLKx2div<<9)|(Startup_HCLKdiv<<8)|(Startup_MPLLdiv<<4)|Startup_APLLdiv)

#if defined(CONFIG_SYNC_MODE)
#define Startup_HCLK	(Startup_APLL/(Startup_HCLKx2div+1)/(Startup_HCLKdiv+1))
#else
#define Startup_HCLK	(Startup_MPLL/(Startup_HCLKx2div+1)/(Startup_HCLKdiv+1))
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#ifndef CONFIG_SMDK6410_X5A

#define DMC1_MEM_CFG		0x0001001A	/* Supports one CKE control, Chip1, Burst4, Row/Column bit */
#define DMC1_MEM_CFG2		0xB45
#define DMC1_CHIP0_CFG		0x150F0    //0x150F8
#define DMC_DDR_32_CFG		0x0 		/* 32bit, DDR */

/* Memory Parameters */
/* DDR Parameters */
#define DDR_tREFRESH		7800		/* ns */
#define DDR_tRAS		45		/* ns (min: 45ns)*/
#define DDR_tRC 		68		/* ns (min: 67.5ns)*/
#define DDR_tRCD		23		/* ns (min: 22.5ns)*/
#define DDR_tRFC		80		/* ns (min: 80ns)*/
#define DDR_tRP 		23		/* ns (min: 22.5ns)*/
#define DDR_tRRD		15		/* ns (min: 15ns)*/
#define DDR_tWR 		15		/* ns (min: 15ns)*/
#define DDR_tXSR		120		/* ns (min: 120ns)*/
#define DDR_CASL		3		/* CAS Latency 3 */

#else

#define DMC1_MEM_CFG		0x00210011	/* Supports one CKE control, Chip1, Burst4, Row/Column bit */
#define DMC1_MEM_CFG2		0xB41
#define DMC1_CHIP0_CFG		0x150FC
#define DMC1_CHIP1_CFG		0x154FC
#define DMC_DDR_32_CFG		0x0		/* 32bit, DDR */

/* Memory Parameters */
/* DDR Parameters */
#define DDR_tREFRESH		5865		/* ns */
#define DDR_tRAS		50		/* ns (min: 45ns)*/
#define DDR_tRC 		68		/* ns (min: 67.5ns)*/
#define DDR_tRCD		23		/* ns (min: 22.5ns)*/
#define DDR_tRFC		133		/* ns (min: 80ns)*/
#define DDR_tRP 		23		/* ns (min: 22.5ns)*/
#define DDR_tRRD		20		/* ns (min: 15ns)*/
#define DDR_tWR 		20		/* ns (min: 15ns)*/
#define DDR_tXSR		125		/* ns (min: 120ns)*/
#define DDR_CASL		3		/* CAS Latency 3 */

#endif

/*
 * mDDR memory configuration
 */
#define DMC_DDR_BA_EMRS 	2
#define DMC_DDR_MEM_CASLAT	3
#define DMC_DDR_CAS_LATENCY	(DDR_CASL<<1)						//6   Set Cas Latency to 3
#define DMC_DDR_t_DQSS		1							// Min 0.75 ~ 1.25
#define DMC_DDR_t_MRD		2							//Min 2 tck
#define DMC_DDR_t_RAS		(((Startup_HCLK / 1000 * DDR_tRAS) - 1) / 1000000 + 1)	//7, Min 45ns
#define DMC_DDR_t_RC		(((Startup_HCLK / 1000 * DDR_tRC) - 1) / 1000000 + 1) 	//10, Min 67.5ns
#define DMC_DDR_t_RCD		(((Startup_HCLK / 1000 * DDR_tRCD) - 1) / 1000000 + 1) 	//4,5(TRM), Min 22.5ns
#define DMC_DDR_schedule_RCD	((DMC_DDR_t_RCD - 3) << 3)
#define DMC_DDR_t_RFC		(((Startup_HCLK / 1000 * DDR_tRFC) - 1) / 1000000 + 1) 	//11,18(TRM) Min 80ns
#define DMC_DDR_schedule_RFC	((DMC_DDR_t_RFC - 3) << 5)
#define DMC_DDR_t_RP		(((Startup_HCLK / 1000 * DDR_tRP) - 1) / 1000000 + 1) 	//4, 5(TRM) Min 22.5ns
#define DMC_DDR_schedule_RP	((DMC_DDR_t_RP - 3) << 3)
#define DMC_DDR_t_RRD		(((Startup_HCLK / 1000 * DDR_tRRD) - 1) / 1000000 + 1)	//3, Min 15ns
#define DMC_DDR_t_WR		(((Startup_HCLK / 1000 * DDR_tWR) - 1) / 1000000 + 1)	//Min 15ns
#define DMC_DDR_t_WTR		2
#define DMC_DDR_t_XP		2							//1tck + tIS(1.5ns)
#define DMC_DDR_t_XSR		(((Startup_HCLK / 1000 * DDR_tXSR) - 1) / 1000000 + 1)	//17, Min 120ns
#define DMC_DDR_t_ESR		DMC_DDR_t_XSR
#define DMC_DDR_REFRESH_PRD	(((Startup_HCLK / 1000 * DDR_tREFRESH) - 1) / 1000000) 	// TRM 2656
#define DMC_DDR_USER_CONFIG	1							// 2b01 : mDDR

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 2 bank of DRAM */
#define PHYS_SDRAM_1		MEMORY_BASE_ADDRESS /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x10000000 /* 256 MB */

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_NO_FLASH		1	/* This board has NO flash */

#define CFG_ENV_SIZE		0x4000	/* Total Size of Environment Sector */
#define CFG_ENV_OFFSET		0x3c000	/* Must be? set to 0x3c000 */

/*
 * REAL6410 board specific data
 */
#define CONFIG_IDENT_STRING	" for REAL6410"

/* total memory required by uboot */
#define CFG_UBOOT_SIZE		(1024 * 1024)

/* base address for uboot */
#ifdef CONFIG_ENABLE_MMU
#define CFG_UBOOT_BASE		0xc7e00000
#else
#define CFG_UBOOT_BASE		0x57e00000
#endif
#define CFG_PHY_UBOOT_BASE	(MEMORY_BASE_ADDRESS + 0x7e00000)

/* NAND configuration */
#if (CONFIG_COMMANDS & CFG_CMD_NAND)
#define CFG_MAX_NAND_DEVICE     1
#define CFG_NAND_BASE           0x70200010
#define NAND_MAX_CHIPS          1
#define CFG_NAND_LARGEPAGE_SAVEENV
/*#define CFG_NAND_HWECC*/
/*#define CFG_NAND_FLASH_BBT*/
/*#define CONFIG_NAND_BL1_8BIT_ECC*/

#define NAND_DISABLE_CE()	(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()	(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()		do { while(!(NFSTAT_REG & (1 << 0))); } while(0)

#define CFG_NAND_SKIP_BAD_DOT_I	1	/* ".i" read skips bad blocks */
#define	CFG_NAND_WP		1
#define CFG_NAND_YAFFS_WRITE	1	/* support yaffs write */

#define CONFIG_MTD_NAND_VERIFY_WRITE    1
#define CONFIG_MTD_NAND_ECC_JFFS2       1
#endif /* CONFIG_COMMANDS & CFG_CMD_NAND */

/* MMC configuration */
#if (CONFIG_COMMANDS & CFG_CMD_MMC)
#define CFG_MMC_BASE		0xf0000000
#define CFG_MAX_MMC_DEVICE	1
#endif

/* OneNAND configuration */
#if (CONFIG_COMMANDS & CFG_CMD_ONENAND)
#define CFG_ONENAND_BASE 	0x70100000
#define CFG_MAX_ONENAND_DEVICE	1
#endif

/*#define CONFIG_DOS_PARTITION*/
/*#define CONFIG_SUPPORT_VFAT*/

/*#define CONFIG_USB_OHCI*/
/*#define CONFIG_USB_STORAGE*/

/* Settings boot configuration */
#if (CONFIG_COMMANDS & CFG_CMD_NAND)
#define	CONFIG_NAND		1
#define CONFIG_BOOT_NAND
#define CFG_ENV_IS_IN_NAND
/*#define CONFIG_BOOTCOMMAND	"nand read c0008000 40000 3c0000; bootm"*/
#elif (CONFIG_BOOTCOMMAND & CFG_CMD_MOVINAND)
#define CONFIG_MOVINAND		1
#define CONFIG_MMC		1
#define CONFIG_BOOT_MOVINAND
#define CFG_ENV_IS_IN_MOVINAND
/*#define CONFIG_BOOTCOMMAND	"movi read uImage c0008000; bootm"*/
#elif (CONFIG_BOOTCOMMAND & CFG_CMD_ONENAND)
#define CONFIG_ONENAND		1
#define CONFIG_BOOT_ONENAND
#define CFG_ENV_IS_IN_ONENAND
/*#define CONFIG_BOOTCOMMAND	"onenand read c0008000 40000 1c0000; bootm"*/
#else
# error Define one of CFG_CMD_{NAND | MOVINAND | ONENAND}
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootcmd=\0" \
	"bootargs=\0" \
	"console=ttySAC0\0" \
	"video=fb:WX4300F\0" \
	"optargs=noinitrd\0" \
	"ipaddr=192.168.0.156\0" \
	"netmask=255.255.255.0\0" \
	"gatewayip=192.168.0.1\0" \
	"serverip=192.168.0.101\0" \
	"autoconf=off\0" \
	"loadaddr=0x50018000\0" \
	"bootfile=uImage\0" \
	"uboot_image=u-boot.real6410\0" \
	"initrd_image=initrd.img\0" \
	"initrd_addr=0x51000000\0" \
	"initrd_high=0xffffffff\0" \
	"nfsboot=run nfsargs; tftp ${loadaddr} ${bootfile} ; bootm\0" \
	"nfsargs=setenv bootargs console=${console},${baudrate}n8 " \
		"${optargs} video=${video} " \
		"root=/dev/nfs nfsroot=${serverip}:${rootpath} " \
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:" \
		"${hostname}:${device}:${autoconf}:${dns0}:${dns1}\0" \
	"rootpath=/home/niew/devel/wheezy-real6410\0" \
	"nandboot=nand read ${loadaddr} 100000 3c0000 ; bootm\0" \
	"nandargs=setenv bootargs console=${console},${baudrate}n8 " \
		"${optargs} video=${video} root=${rootfs} " \
		"rootfstype=${rootfstype} mtdparts=${mtdparts}\0" \
	"rootfs=/dev/mtdblock2\0" \
	"rootfstype=jffs2\0" \
	"mtdparts=nand:1m(uboot)ro,4m(kernel),-(rootfs)\0" \
	"upgradecmd=tftp ${loadaddr} ${uboot_image} && " \
		"setenv uboot_size $filesize ; " \
		"nand erase 0 0x40000 && sleep 3 ; " \
		"nand write ${loadaddr} 0 0x40000 && sleep 3 ; " \
		"nand read 0x52008000 0 ${uboot_size} ; " \
		"cmp.b $fileaddr 0x52008000 ${uboot_size} ; echo ; " \
		"echo U-Boot upgraded. Please reset the board manually!\0"
#endif	/* __CONFIG_H */
