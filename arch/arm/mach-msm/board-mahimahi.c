/* linux/arch/arm/mach-msm/board-mahimahi.c
 *
 * Copyright (C) 2009 Google, Inc.
 * Copyright (C) 2009 HTC Corporation.
 * Author: Dima Zavin <dima@android.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/memblock.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>

#include <mach/hardware.h>

#include "board-mahimahi.h"
#include "devices.h"
#include "proc_comm.h"
#include "common.h"

static uint debug_uart;

module_param_named(debug_uart, debug_uart, uint, 0);

static struct platform_device *devices[] __initdata = {
#if !defined(CONFIG_MSM_SERIAL_DEBUGGER)
	&msm_device_uart1,
#endif
	&msm_device_uart_dm1,
	&msm_device_nand,
};

static void __init mahimahi_init(void)
{
	platform_add_devices(devices, ARRAY_SIZE(devices));
}

static void __init mahimahi_fixup(struct tag *tags, char **cmdline)
{
	memblock_add(PHYS_OFFSET, 219*SZ_1M);
	memblock_add(MSM_HIGHMEM_BASE, MSM_HIGHMEM_SIZE);
}

static void __init mahimahi_map_io(void)
{
	msm_map_common_io();
	msm_clock_init();
}

static void __init mahimahi_init_late(void)
{
	smd_debugfs_init();
}

void msm_timer_init(void);

MACHINE_START(MAHIMAHI, "mahimahi")
	.atag_offset	= 0x100,
	.fixup		= mahimahi_fixup,
	.map_io		= mahimahi_map_io,
	.init_irq	= msm_init_irq,
	.init_machine	= mahimahi_init,
	.init_late	= mahimahi_init_late,
	.init_time	= msm_timer_init,
MACHINE_END
