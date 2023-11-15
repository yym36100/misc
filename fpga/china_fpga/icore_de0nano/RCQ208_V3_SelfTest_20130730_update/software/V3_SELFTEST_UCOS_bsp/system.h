/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_0' in SOPC Builder design 'RC_2C8V3_Nios_CPU'
 * SOPC Builder design path: D:/CD_BAK/RCQ208_V3_CH_EDITION/04_Nios_Examples/RCQ208_V3_SelfTest_20130128_update/RC_2C8V3_Nios_CPU.sopcinfo
 *
 * Generated: Tue Jul 30 17:55:56 CST 2013
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * ADC_DATA configuration
 *
 */

#define ADC_DATA_BASE 0x4002150
#define ADC_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define ADC_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ADC_DATA_CAPTURE 1
#define ADC_DATA_DATA_WIDTH 8
#define ADC_DATA_DO_TEST_BENCH_WIRING 0
#define ADC_DATA_DRIVEN_SIM_VALUE 0x0
#define ADC_DATA_EDGE_TYPE "RISING"
#define ADC_DATA_FREQ 50000000u
#define ADC_DATA_HAS_IN 1
#define ADC_DATA_HAS_OUT 0
#define ADC_DATA_HAS_TRI 0
#define ADC_DATA_IRQ -1
#define ADC_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ADC_DATA_IRQ_TYPE "NONE"
#define ADC_DATA_NAME "/dev/ADC_DATA"
#define ADC_DATA_RESET_VALUE 0x0
#define ADC_DATA_SPAN 16
#define ADC_DATA_TYPE "altera_avalon_pio"
#define ALT_MODULE_CLASS_ADC_DATA altera_avalon_pio


/*
 * BUZZER_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_BUZZER_DATA altera_avalon_pio
#define BUZZER_DATA_BASE 0x4002130
#define BUZZER_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define BUZZER_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUZZER_DATA_CAPTURE 1
#define BUZZER_DATA_DATA_WIDTH 1
#define BUZZER_DATA_DO_TEST_BENCH_WIRING 0
#define BUZZER_DATA_DRIVEN_SIM_VALUE 0x0
#define BUZZER_DATA_EDGE_TYPE "RISING"
#define BUZZER_DATA_FREQ 50000000u
#define BUZZER_DATA_HAS_IN 1
#define BUZZER_DATA_HAS_OUT 0
#define BUZZER_DATA_HAS_TRI 0
#define BUZZER_DATA_IRQ -1
#define BUZZER_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BUZZER_DATA_IRQ_TYPE "NONE"
#define BUZZER_DATA_NAME "/dev/BUZZER_DATA"
#define BUZZER_DATA_RESET_VALUE 0x0
#define BUZZER_DATA_SPAN 16
#define BUZZER_DATA_TYPE "altera_avalon_pio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x4001020
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x2000020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x4001800


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x4001020
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x2000020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x4001800


/*
 * DAC_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_DAC_DATA altera_avalon_pio
#define DAC_DATA_BASE 0x4002140
#define DAC_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define DAC_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DAC_DATA_CAPTURE 1
#define DAC_DATA_DATA_WIDTH 8
#define DAC_DATA_DO_TEST_BENCH_WIRING 0
#define DAC_DATA_DRIVEN_SIM_VALUE 0x0
#define DAC_DATA_EDGE_TYPE "RISING"
#define DAC_DATA_FREQ 50000000u
#define DAC_DATA_HAS_IN 1
#define DAC_DATA_HAS_OUT 0
#define DAC_DATA_HAS_TRI 0
#define DAC_DATA_IRQ -1
#define DAC_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DAC_DATA_IRQ_TYPE "NONE"
#define DAC_DATA_NAME "/dev/DAC_DATA"
#define DAC_DATA_RESET_VALUE 0x0
#define DAC_DATA_SPAN 16
#define DAC_DATA_TYPE "altera_avalon_pio"


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2


/*
 * ETH_CLKOUT_I configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_CLKOUT_I altera_avalon_pio
#define ETH_CLKOUT_I_BASE 0x4002250
#define ETH_CLKOUT_I_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_CLKOUT_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_CLKOUT_I_CAPTURE 1
#define ETH_CLKOUT_I_DATA_WIDTH 1
#define ETH_CLKOUT_I_DO_TEST_BENCH_WIRING 0
#define ETH_CLKOUT_I_DRIVEN_SIM_VALUE 0x0
#define ETH_CLKOUT_I_EDGE_TYPE "RISING"
#define ETH_CLKOUT_I_FREQ 50000000u
#define ETH_CLKOUT_I_HAS_IN 1
#define ETH_CLKOUT_I_HAS_OUT 0
#define ETH_CLKOUT_I_HAS_TRI 0
#define ETH_CLKOUT_I_IRQ -1
#define ETH_CLKOUT_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_CLKOUT_I_IRQ_TYPE "NONE"
#define ETH_CLKOUT_I_NAME "/dev/ETH_CLKOUT_I"
#define ETH_CLKOUT_I_RESET_VALUE 0x0
#define ETH_CLKOUT_I_SPAN 16
#define ETH_CLKOUT_I_TYPE "altera_avalon_pio"


/*
 * ETH_CS_O configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_CS_O altera_avalon_pio
#define ETH_CS_O_BASE 0x4002270
#define ETH_CS_O_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_CS_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_CS_O_CAPTURE 0
#define ETH_CS_O_DATA_WIDTH 1
#define ETH_CS_O_DO_TEST_BENCH_WIRING 0
#define ETH_CS_O_DRIVEN_SIM_VALUE 0x0
#define ETH_CS_O_EDGE_TYPE "NONE"
#define ETH_CS_O_FREQ 50000000u
#define ETH_CS_O_HAS_IN 0
#define ETH_CS_O_HAS_OUT 1
#define ETH_CS_O_HAS_TRI 0
#define ETH_CS_O_IRQ -1
#define ETH_CS_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_CS_O_IRQ_TYPE "NONE"
#define ETH_CS_O_NAME "/dev/ETH_CS_O"
#define ETH_CS_O_RESET_VALUE 0x0
#define ETH_CS_O_SPAN 16
#define ETH_CS_O_TYPE "altera_avalon_pio"


/*
 * ETH_INT_I configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_INT_I altera_avalon_pio
#define ETH_INT_I_BASE 0x4002260
#define ETH_INT_I_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_INT_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_INT_I_CAPTURE 1
#define ETH_INT_I_DATA_WIDTH 8
#define ETH_INT_I_DO_TEST_BENCH_WIRING 0
#define ETH_INT_I_DRIVEN_SIM_VALUE 0x0
#define ETH_INT_I_EDGE_TYPE "RISING"
#define ETH_INT_I_FREQ 50000000u
#define ETH_INT_I_HAS_IN 1
#define ETH_INT_I_HAS_OUT 0
#define ETH_INT_I_HAS_TRI 0
#define ETH_INT_I_IRQ -1
#define ETH_INT_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_INT_I_IRQ_TYPE "NONE"
#define ETH_INT_I_NAME "/dev/ETH_INT_I"
#define ETH_INT_I_RESET_VALUE 0x0
#define ETH_INT_I_SPAN 16
#define ETH_INT_I_TYPE "altera_avalon_pio"


/*
 * ETH_RESET_O configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_RESET_O altera_avalon_pio
#define ETH_RESET_O_BASE 0x4002210
#define ETH_RESET_O_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_RESET_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_RESET_O_CAPTURE 0
#define ETH_RESET_O_DATA_WIDTH 1
#define ETH_RESET_O_DO_TEST_BENCH_WIRING 0
#define ETH_RESET_O_DRIVEN_SIM_VALUE 0x0
#define ETH_RESET_O_EDGE_TYPE "NONE"
#define ETH_RESET_O_FREQ 50000000u
#define ETH_RESET_O_HAS_IN 0
#define ETH_RESET_O_HAS_OUT 1
#define ETH_RESET_O_HAS_TRI 0
#define ETH_RESET_O_IRQ -1
#define ETH_RESET_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_RESET_O_IRQ_TYPE "NONE"
#define ETH_RESET_O_NAME "/dev/ETH_RESET_O"
#define ETH_RESET_O_RESET_VALUE 0x0
#define ETH_RESET_O_SPAN 16
#define ETH_RESET_O_TYPE "altera_avalon_pio"


/*
 * ETH_SCK_O configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_SCK_O altera_avalon_pio
#define ETH_SCK_O_BASE 0x4002220
#define ETH_SCK_O_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_SCK_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_SCK_O_CAPTURE 0
#define ETH_SCK_O_DATA_WIDTH 1
#define ETH_SCK_O_DO_TEST_BENCH_WIRING 0
#define ETH_SCK_O_DRIVEN_SIM_VALUE 0x0
#define ETH_SCK_O_EDGE_TYPE "NONE"
#define ETH_SCK_O_FREQ 50000000u
#define ETH_SCK_O_HAS_IN 0
#define ETH_SCK_O_HAS_OUT 1
#define ETH_SCK_O_HAS_TRI 0
#define ETH_SCK_O_IRQ -1
#define ETH_SCK_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_SCK_O_IRQ_TYPE "NONE"
#define ETH_SCK_O_NAME "/dev/ETH_SCK_O"
#define ETH_SCK_O_RESET_VALUE 0x0
#define ETH_SCK_O_SPAN 16
#define ETH_SCK_O_TYPE "altera_avalon_pio"


/*
 * ETH_SI_O configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_SI_O altera_avalon_pio
#define ETH_SI_O_BASE 0x4002230
#define ETH_SI_O_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_SI_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_SI_O_CAPTURE 0
#define ETH_SI_O_DATA_WIDTH 1
#define ETH_SI_O_DO_TEST_BENCH_WIRING 0
#define ETH_SI_O_DRIVEN_SIM_VALUE 0x0
#define ETH_SI_O_EDGE_TYPE "NONE"
#define ETH_SI_O_FREQ 50000000u
#define ETH_SI_O_HAS_IN 0
#define ETH_SI_O_HAS_OUT 1
#define ETH_SI_O_HAS_TRI 0
#define ETH_SI_O_IRQ -1
#define ETH_SI_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_SI_O_IRQ_TYPE "NONE"
#define ETH_SI_O_NAME "/dev/ETH_SI_O"
#define ETH_SI_O_RESET_VALUE 0x0
#define ETH_SI_O_SPAN 16
#define ETH_SI_O_TYPE "altera_avalon_pio"


/*
 * ETH_SO_I configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_SO_I altera_avalon_pio
#define ETH_SO_I_BASE 0x4002240
#define ETH_SO_I_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_SO_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_SO_I_CAPTURE 1
#define ETH_SO_I_DATA_WIDTH 1
#define ETH_SO_I_DO_TEST_BENCH_WIRING 0
#define ETH_SO_I_DRIVEN_SIM_VALUE 0x0
#define ETH_SO_I_EDGE_TYPE "RISING"
#define ETH_SO_I_FREQ 50000000u
#define ETH_SO_I_HAS_IN 1
#define ETH_SO_I_HAS_OUT 0
#define ETH_SO_I_HAS_TRI 0
#define ETH_SO_I_IRQ -1
#define ETH_SO_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_SO_I_IRQ_TYPE "NONE"
#define ETH_SO_I_NAME "/dev/ETH_SO_I"
#define ETH_SO_I_RESET_VALUE 0x0
#define ETH_SO_I_SPAN 16
#define ETH_SO_I_TYPE "altera_avalon_pio"


/*
 * ETH_WOL_I configuration
 *
 */

#define ALT_MODULE_CLASS_ETH_WOL_I altera_avalon_pio
#define ETH_WOL_I_BASE 0x4002280
#define ETH_WOL_I_BIT_CLEARING_EDGE_REGISTER 0
#define ETH_WOL_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ETH_WOL_I_CAPTURE 1
#define ETH_WOL_I_DATA_WIDTH 1
#define ETH_WOL_I_DO_TEST_BENCH_WIRING 0
#define ETH_WOL_I_DRIVEN_SIM_VALUE 0x0
#define ETH_WOL_I_EDGE_TYPE "RISING"
#define ETH_WOL_I_FREQ 50000000u
#define ETH_WOL_I_HAS_IN 1
#define ETH_WOL_I_HAS_OUT 0
#define ETH_WOL_I_HAS_TRI 0
#define ETH_WOL_I_IRQ -1
#define ETH_WOL_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETH_WOL_I_IRQ_TYPE "NONE"
#define ETH_WOL_I_NAME "/dev/ETH_WOL_I"
#define ETH_WOL_I_RESET_VALUE 0x0
#define ETH_WOL_I_SPAN 16
#define ETH_WOL_I_TYPE "altera_avalon_pio"


/*
 * IR_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_IR_DATA altera_avalon_pio
#define IR_DATA_BASE 0x4002100
#define IR_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define IR_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IR_DATA_CAPTURE 1
#define IR_DATA_DATA_WIDTH 32
#define IR_DATA_DO_TEST_BENCH_WIRING 0
#define IR_DATA_DRIVEN_SIM_VALUE 0x0
#define IR_DATA_EDGE_TYPE "RISING"
#define IR_DATA_FREQ 50000000u
#define IR_DATA_HAS_IN 1
#define IR_DATA_HAS_OUT 0
#define IR_DATA_HAS_TRI 0
#define IR_DATA_IRQ -1
#define IR_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IR_DATA_IRQ_TYPE "NONE"
#define IR_DATA_NAME "/dev/IR_DATA"
#define IR_DATA_RESET_VALUE 0x0
#define IR_DATA_SPAN 16
#define IR_DATA_TYPE "altera_avalon_pio"


/*
 * KEY_FOCUS configuration
 *
 */

#define ALT_MODULE_CLASS_KEY_FOCUS altera_avalon_pio
#define KEY_FOCUS_BASE 0x4002110
#define KEY_FOCUS_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_FOCUS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_FOCUS_CAPTURE 1
#define KEY_FOCUS_DATA_WIDTH 4
#define KEY_FOCUS_DO_TEST_BENCH_WIRING 0
#define KEY_FOCUS_DRIVEN_SIM_VALUE 0x0
#define KEY_FOCUS_EDGE_TYPE "RISING"
#define KEY_FOCUS_FREQ 50000000u
#define KEY_FOCUS_HAS_IN 1
#define KEY_FOCUS_HAS_OUT 0
#define KEY_FOCUS_HAS_TRI 0
#define KEY_FOCUS_IRQ -1
#define KEY_FOCUS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEY_FOCUS_IRQ_TYPE "NONE"
#define KEY_FOCUS_NAME "/dev/KEY_FOCUS"
#define KEY_FOCUS_RESET_VALUE 0x0
#define KEY_FOCUS_SPAN 16
#define KEY_FOCUS_TYPE "altera_avalon_pio"


/*
 * LCD_CS configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_CS altera_avalon_pio
#define LCD_CS_BASE 0x4002070
#define LCD_CS_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_CS_CAPTURE 0
#define LCD_CS_DATA_WIDTH 1
#define LCD_CS_DO_TEST_BENCH_WIRING 0
#define LCD_CS_DRIVEN_SIM_VALUE 0x0
#define LCD_CS_EDGE_TYPE "NONE"
#define LCD_CS_FREQ 50000000u
#define LCD_CS_HAS_IN 0
#define LCD_CS_HAS_OUT 1
#define LCD_CS_HAS_TRI 0
#define LCD_CS_IRQ -1
#define LCD_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_CS_IRQ_TYPE "NONE"
#define LCD_CS_NAME "/dev/LCD_CS"
#define LCD_CS_RESET_VALUE 0x0
#define LCD_CS_SPAN 16
#define LCD_CS_TYPE "altera_avalon_pio"


/*
 * LCD_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_DATA altera_avalon_pio
#define LCD_DATA_BASE 0x4002060
#define LCD_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_DATA_CAPTURE 0
#define LCD_DATA_DATA_WIDTH 16
#define LCD_DATA_DO_TEST_BENCH_WIRING 0
#define LCD_DATA_DRIVEN_SIM_VALUE 0x0
#define LCD_DATA_EDGE_TYPE "NONE"
#define LCD_DATA_FREQ 50000000u
#define LCD_DATA_HAS_IN 0
#define LCD_DATA_HAS_OUT 1
#define LCD_DATA_HAS_TRI 0
#define LCD_DATA_IRQ -1
#define LCD_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_DATA_IRQ_TYPE "NONE"
#define LCD_DATA_NAME "/dev/LCD_DATA"
#define LCD_DATA_RESET_VALUE 0x0
#define LCD_DATA_SPAN 16
#define LCD_DATA_TYPE "altera_avalon_pio"


/*
 * LCD_RD configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_RD altera_avalon_pio
#define LCD_RD_BASE 0x4002090
#define LCD_RD_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RD_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RD_CAPTURE 0
#define LCD_RD_DATA_WIDTH 1
#define LCD_RD_DO_TEST_BENCH_WIRING 0
#define LCD_RD_DRIVEN_SIM_VALUE 0x0
#define LCD_RD_EDGE_TYPE "NONE"
#define LCD_RD_FREQ 50000000u
#define LCD_RD_HAS_IN 0
#define LCD_RD_HAS_OUT 1
#define LCD_RD_HAS_TRI 0
#define LCD_RD_IRQ -1
#define LCD_RD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RD_IRQ_TYPE "NONE"
#define LCD_RD_NAME "/dev/LCD_RD"
#define LCD_RD_RESET_VALUE 0x0
#define LCD_RD_SPAN 16
#define LCD_RD_TYPE "altera_avalon_pio"


/*
 * LCD_RS configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_RS altera_avalon_pio
#define LCD_RS_BASE 0x4002080
#define LCD_RS_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RS_CAPTURE 0
#define LCD_RS_DATA_WIDTH 1
#define LCD_RS_DO_TEST_BENCH_WIRING 0
#define LCD_RS_DRIVEN_SIM_VALUE 0x0
#define LCD_RS_EDGE_TYPE "NONE"
#define LCD_RS_FREQ 50000000u
#define LCD_RS_HAS_IN 0
#define LCD_RS_HAS_OUT 1
#define LCD_RS_HAS_TRI 0
#define LCD_RS_IRQ -1
#define LCD_RS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RS_IRQ_TYPE "NONE"
#define LCD_RS_NAME "/dev/LCD_RS"
#define LCD_RS_RESET_VALUE 0x1
#define LCD_RS_SPAN 16
#define LCD_RS_TYPE "altera_avalon_pio"


/*
 * LCD_RST configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_RST altera_avalon_pio
#define LCD_RST_BASE 0x40020a0
#define LCD_RST_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RST_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RST_CAPTURE 0
#define LCD_RST_DATA_WIDTH 1
#define LCD_RST_DO_TEST_BENCH_WIRING 0
#define LCD_RST_DRIVEN_SIM_VALUE 0x0
#define LCD_RST_EDGE_TYPE "NONE"
#define LCD_RST_FREQ 50000000u
#define LCD_RST_HAS_IN 0
#define LCD_RST_HAS_OUT 1
#define LCD_RST_HAS_TRI 0
#define LCD_RST_IRQ -1
#define LCD_RST_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RST_IRQ_TYPE "NONE"
#define LCD_RST_NAME "/dev/LCD_RST"
#define LCD_RST_RESET_VALUE 0x1
#define LCD_RST_SPAN 16
#define LCD_RST_TYPE "altera_avalon_pio"


/*
 * LCD_WR configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_WR altera_avalon_pio
#define LCD_WR_BASE 0x40020b0
#define LCD_WR_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_WR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_WR_CAPTURE 0
#define LCD_WR_DATA_WIDTH 1
#define LCD_WR_DO_TEST_BENCH_WIRING 0
#define LCD_WR_DRIVEN_SIM_VALUE 0x0
#define LCD_WR_EDGE_TYPE "NONE"
#define LCD_WR_FREQ 50000000u
#define LCD_WR_HAS_IN 0
#define LCD_WR_HAS_OUT 1
#define LCD_WR_HAS_TRI 0
#define LCD_WR_IRQ -1
#define LCD_WR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_WR_IRQ_TYPE "NONE"
#define LCD_WR_NAME "/dev/LCD_WR"
#define LCD_WR_RESET_VALUE 0x1
#define LCD_WR_SPAN 16
#define LCD_WR_TYPE "altera_avalon_pio"


/*
 * LED_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_LED_DATA altera_avalon_pio
#define LED_DATA_BASE 0x4002120
#define LED_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define LED_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_DATA_CAPTURE 1
#define LED_DATA_DATA_WIDTH 6
#define LED_DATA_DO_TEST_BENCH_WIRING 0
#define LED_DATA_DRIVEN_SIM_VALUE 0x0
#define LED_DATA_EDGE_TYPE "RISING"
#define LED_DATA_FREQ 50000000u
#define LED_DATA_HAS_IN 1
#define LED_DATA_HAS_OUT 0
#define LED_DATA_HAS_TRI 0
#define LED_DATA_IRQ -1
#define LED_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_DATA_IRQ_TYPE "NONE"
#define LED_DATA_NAME "/dev/LED_DATA"
#define LED_DATA_RESET_VALUE 0x0
#define LED_DATA_SPAN 16
#define LED_DATA_TYPE "altera_avalon_pio"


/*
 * PS2_DATA_REC configuration
 *
 */

#define ALT_MODULE_CLASS_PS2_DATA_REC altera_avalon_pio
#define PS2_DATA_REC_BASE 0x40020d0
#define PS2_DATA_REC_BIT_CLEARING_EDGE_REGISTER 0
#define PS2_DATA_REC_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PS2_DATA_REC_CAPTURE 1
#define PS2_DATA_REC_DATA_WIDTH 16
#define PS2_DATA_REC_DO_TEST_BENCH_WIRING 0
#define PS2_DATA_REC_DRIVEN_SIM_VALUE 0x0
#define PS2_DATA_REC_EDGE_TYPE "RISING"
#define PS2_DATA_REC_FREQ 50000000u
#define PS2_DATA_REC_HAS_IN 1
#define PS2_DATA_REC_HAS_OUT 0
#define PS2_DATA_REC_HAS_TRI 0
#define PS2_DATA_REC_IRQ -1
#define PS2_DATA_REC_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PS2_DATA_REC_IRQ_TYPE "NONE"
#define PS2_DATA_REC_NAME "/dev/PS2_DATA_REC"
#define PS2_DATA_REC_RESET_VALUE 0x0
#define PS2_DATA_REC_SPAN 16
#define PS2_DATA_REC_TYPE "altera_avalon_pio"


/*
 * RTC_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_RTC_DATA altera_avalon_pio
#define RTC_DATA_BASE 0x40020f0
#define RTC_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define RTC_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RTC_DATA_CAPTURE 1
#define RTC_DATA_DATA_WIDTH 24
#define RTC_DATA_DO_TEST_BENCH_WIRING 0
#define RTC_DATA_DRIVEN_SIM_VALUE 0x0
#define RTC_DATA_EDGE_TYPE "RISING"
#define RTC_DATA_FREQ 50000000u
#define RTC_DATA_HAS_IN 1
#define RTC_DATA_HAS_OUT 0
#define RTC_DATA_HAS_TRI 0
#define RTC_DATA_IRQ -1
#define RTC_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RTC_DATA_IRQ_TYPE "NONE"
#define RTC_DATA_NAME "/dev/RTC_DATA"
#define RTC_DATA_RESET_VALUE 0x0
#define RTC_DATA_SPAN 16
#define RTC_DATA_TYPE "altera_avalon_pio"


/*
 * SCL configuration
 *
 */

#define ALT_MODULE_CLASS_SCL altera_avalon_pio
#define SCL_BASE 0x4002290
#define SCL_BIT_CLEARING_EDGE_REGISTER 0
#define SCL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SCL_CAPTURE 0
#define SCL_DATA_WIDTH 1
#define SCL_DO_TEST_BENCH_WIRING 0
#define SCL_DRIVEN_SIM_VALUE 0x0
#define SCL_EDGE_TYPE "NONE"
#define SCL_FREQ 50000000u
#define SCL_HAS_IN 0
#define SCL_HAS_OUT 1
#define SCL_HAS_TRI 0
#define SCL_IRQ -1
#define SCL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SCL_IRQ_TYPE "NONE"
#define SCL_NAME "/dev/SCL"
#define SCL_RESET_VALUE 0x1
#define SCL_SPAN 16
#define SCL_TYPE "altera_avalon_pio"


/*
 * SDA configuration
 *
 */

#define ALT_MODULE_CLASS_SDA altera_avalon_pio
#define SDA_BASE 0x40022a0
#define SDA_BIT_CLEARING_EDGE_REGISTER 0
#define SDA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SDA_CAPTURE 0
#define SDA_DATA_WIDTH 1
#define SDA_DO_TEST_BENCH_WIRING 0
#define SDA_DRIVEN_SIM_VALUE 0x0
#define SDA_EDGE_TYPE "NONE"
#define SDA_FREQ 50000000u
#define SDA_HAS_IN 0
#define SDA_HAS_OUT 0
#define SDA_HAS_TRI 1
#define SDA_IRQ -1
#define SDA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDA_IRQ_TYPE "NONE"
#define SDA_NAME "/dev/SDA"
#define SDA_RESET_VALUE 0x1
#define SDA_SPAN 16
#define SDA_TYPE "altera_avalon_pio"


/*
 * SD_CLK configuration
 *
 */

#define ALT_MODULE_CLASS_SD_CLK altera_avalon_pio
#define SD_CLK_BASE 0x4002180
#define SD_CLK_BIT_CLEARING_EDGE_REGISTER 0
#define SD_CLK_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SD_CLK_CAPTURE 0
#define SD_CLK_DATA_WIDTH 1
#define SD_CLK_DO_TEST_BENCH_WIRING 0
#define SD_CLK_DRIVEN_SIM_VALUE 0x0
#define SD_CLK_EDGE_TYPE "NONE"
#define SD_CLK_FREQ 50000000u
#define SD_CLK_HAS_IN 0
#define SD_CLK_HAS_OUT 1
#define SD_CLK_HAS_TRI 0
#define SD_CLK_IRQ -1
#define SD_CLK_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_CLK_IRQ_TYPE "NONE"
#define SD_CLK_NAME "/dev/SD_CLK"
#define SD_CLK_RESET_VALUE 0x0
#define SD_CLK_SPAN 16
#define SD_CLK_TYPE "altera_avalon_pio"


/*
 * SD_CS configuration
 *
 */

#define ALT_MODULE_CLASS_SD_CS altera_avalon_pio
#define SD_CS_BASE 0x4002160
#define SD_CS_BIT_CLEARING_EDGE_REGISTER 0
#define SD_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SD_CS_CAPTURE 0
#define SD_CS_DATA_WIDTH 1
#define SD_CS_DO_TEST_BENCH_WIRING 0
#define SD_CS_DRIVEN_SIM_VALUE 0x0
#define SD_CS_EDGE_TYPE "NONE"
#define SD_CS_FREQ 50000000u
#define SD_CS_HAS_IN 0
#define SD_CS_HAS_OUT 1
#define SD_CS_HAS_TRI 0
#define SD_CS_IRQ -1
#define SD_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_CS_IRQ_TYPE "NONE"
#define SD_CS_NAME "/dev/SD_CS"
#define SD_CS_RESET_VALUE 0x0
#define SD_CS_SPAN 16
#define SD_CS_TYPE "altera_avalon_pio"


/*
 * SD_DI configuration
 *
 */

#define ALT_MODULE_CLASS_SD_DI altera_avalon_pio
#define SD_DI_BASE 0x4002170
#define SD_DI_BIT_CLEARING_EDGE_REGISTER 0
#define SD_DI_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SD_DI_CAPTURE 0
#define SD_DI_DATA_WIDTH 1
#define SD_DI_DO_TEST_BENCH_WIRING 0
#define SD_DI_DRIVEN_SIM_VALUE 0x0
#define SD_DI_EDGE_TYPE "NONE"
#define SD_DI_FREQ 50000000u
#define SD_DI_HAS_IN 0
#define SD_DI_HAS_OUT 1
#define SD_DI_HAS_TRI 0
#define SD_DI_IRQ -1
#define SD_DI_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_DI_IRQ_TYPE "NONE"
#define SD_DI_NAME "/dev/SD_DI"
#define SD_DI_RESET_VALUE 0x0
#define SD_DI_SPAN 16
#define SD_DI_TYPE "altera_avalon_pio"


/*
 * SD_DO configuration
 *
 */

#define ALT_MODULE_CLASS_SD_DO altera_avalon_pio
#define SD_DO_BASE 0x4002190
#define SD_DO_BIT_CLEARING_EDGE_REGISTER 0
#define SD_DO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SD_DO_CAPTURE 1
#define SD_DO_DATA_WIDTH 1
#define SD_DO_DO_TEST_BENCH_WIRING 0
#define SD_DO_DRIVEN_SIM_VALUE 0x0
#define SD_DO_EDGE_TYPE "RISING"
#define SD_DO_FREQ 50000000u
#define SD_DO_HAS_IN 1
#define SD_DO_HAS_OUT 0
#define SD_DO_HAS_TRI 0
#define SD_DO_IRQ -1
#define SD_DO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_DO_IRQ_TYPE "NONE"
#define SD_DO_NAME "/dev/SD_DO"
#define SD_DO_RESET_VALUE 0x0
#define SD_DO_SPAN 16
#define SD_DO_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "CYCLONEII"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/uart_0"
#define ALT_STDERR_BASE 0x4002000
#define ALT_STDERR_DEV uart_0
#define ALT_STDERR_IS_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_uart"
#define ALT_STDIN "/dev/uart_0"
#define ALT_STDIN_BASE 0x4002000
#define ALT_STDIN_DEV uart_0
#define ALT_STDIN_IS_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_uart"
#define ALT_STDOUT "/dev/uart_0"
#define ALT_STDOUT_BASE 0x4002000
#define ALT_STDOUT_DEV uart_0
#define ALT_STDOUT_IS_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_uart"
#define ALT_SYSTEM_NAME "RC_2C8V3_Nios_CPU"


/*
 * TEMP_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_TEMP_DATA altera_avalon_pio
#define TEMP_DATA_BASE 0x40020c0
#define TEMP_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define TEMP_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TEMP_DATA_CAPTURE 1
#define TEMP_DATA_DATA_WIDTH 16
#define TEMP_DATA_DO_TEST_BENCH_WIRING 0
#define TEMP_DATA_DRIVEN_SIM_VALUE 0x0
#define TEMP_DATA_EDGE_TYPE "RISING"
#define TEMP_DATA_FREQ 50000000u
#define TEMP_DATA_HAS_IN 1
#define TEMP_DATA_HAS_OUT 0
#define TEMP_DATA_HAS_TRI 0
#define TEMP_DATA_IRQ -1
#define TEMP_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TEMP_DATA_IRQ_TYPE "NONE"
#define TEMP_DATA_NAME "/dev/TEMP_DATA"
#define TEMP_DATA_RESET_VALUE 0x0
#define TEMP_DATA_SPAN 16
#define TEMP_DATA_TYPE "altera_avalon_pio"


/*
 * TUBE_EN configuration
 *
 */

#define ALT_MODULE_CLASS_TUBE_EN altera_avalon_pio
#define TUBE_EN_BASE 0x40022b0
#define TUBE_EN_BIT_CLEARING_EDGE_REGISTER 0
#define TUBE_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TUBE_EN_CAPTURE 0
#define TUBE_EN_DATA_WIDTH 4
#define TUBE_EN_DO_TEST_BENCH_WIRING 0
#define TUBE_EN_DRIVEN_SIM_VALUE 0x0
#define TUBE_EN_EDGE_TYPE "NONE"
#define TUBE_EN_FREQ 50000000u
#define TUBE_EN_HAS_IN 0
#define TUBE_EN_HAS_OUT 1
#define TUBE_EN_HAS_TRI 0
#define TUBE_EN_IRQ -1
#define TUBE_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TUBE_EN_IRQ_TYPE "NONE"
#define TUBE_EN_NAME "/dev/TUBE_EN"
#define TUBE_EN_RESET_VALUE 0xf
#define TUBE_EN_SPAN 16
#define TUBE_EN_TYPE "altera_avalon_pio"


/*
 * UART_RX_DATA configuration
 *
 */

#define ALT_MODULE_CLASS_UART_RX_DATA altera_avalon_pio
#define UART_RX_DATA_BASE 0x40020e0
#define UART_RX_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define UART_RX_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define UART_RX_DATA_CAPTURE 1
#define UART_RX_DATA_DATA_WIDTH 8
#define UART_RX_DATA_DO_TEST_BENCH_WIRING 0
#define UART_RX_DATA_DRIVEN_SIM_VALUE 0x0
#define UART_RX_DATA_EDGE_TYPE "RISING"
#define UART_RX_DATA_FREQ 50000000u
#define UART_RX_DATA_HAS_IN 1
#define UART_RX_DATA_HAS_OUT 0
#define UART_RX_DATA_HAS_TRI 0
#define UART_RX_DATA_IRQ -1
#define UART_RX_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define UART_RX_DATA_IRQ_TYPE "NONE"
#define UART_RX_DATA_NAME "/dev/UART_RX_DATA"
#define UART_RX_DATA_RESET_VALUE 0x0
#define UART_RX_DATA_SPAN 16
#define UART_RX_DATA_TYPE "altera_avalon_pio"


/*
 * USB_INT_I configuration
 *
 */

#define ALT_MODULE_CLASS_USB_INT_I altera_avalon_pio
#define USB_INT_I_BASE 0x40021e0
#define USB_INT_I_BIT_CLEARING_EDGE_REGISTER 0
#define USB_INT_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_INT_I_CAPTURE 0
#define USB_INT_I_DATA_WIDTH 1
#define USB_INT_I_DO_TEST_BENCH_WIRING 0
#define USB_INT_I_DRIVEN_SIM_VALUE 0x0
#define USB_INT_I_EDGE_TYPE "NONE"
#define USB_INT_I_FREQ 50000000u
#define USB_INT_I_HAS_IN 1
#define USB_INT_I_HAS_OUT 0
#define USB_INT_I_HAS_TRI 0
#define USB_INT_I_IRQ -1
#define USB_INT_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_INT_I_IRQ_TYPE "NONE"
#define USB_INT_I_NAME "/dev/USB_INT_I"
#define USB_INT_I_RESET_VALUE 0x0
#define USB_INT_I_SPAN 16
#define USB_INT_I_TYPE "altera_avalon_pio"


/*
 * USB_PC_I configuration
 *
 */

#define ALT_MODULE_CLASS_USB_PC_I altera_avalon_pio
#define USB_PC_I_BASE 0x4002200
#define USB_PC_I_BIT_CLEARING_EDGE_REGISTER 0
#define USB_PC_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_PC_I_CAPTURE 1
#define USB_PC_I_DATA_WIDTH 1
#define USB_PC_I_DO_TEST_BENCH_WIRING 0
#define USB_PC_I_DRIVEN_SIM_VALUE 0x0
#define USB_PC_I_EDGE_TYPE "RISING"
#define USB_PC_I_FREQ 50000000u
#define USB_PC_I_HAS_IN 1
#define USB_PC_I_HAS_OUT 0
#define USB_PC_I_HAS_TRI 0
#define USB_PC_I_IRQ -1
#define USB_PC_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_PC_I_IRQ_TYPE "NONE"
#define USB_PC_I_NAME "/dev/USB_PC_I"
#define USB_PC_I_RESET_VALUE 0x0
#define USB_PC_I_SPAN 16
#define USB_PC_I_TYPE "altera_avalon_pio"


/*
 * USB_RST_O configuration
 *
 */

#define ALT_MODULE_CLASS_USB_RST_O altera_avalon_pio
#define USB_RST_O_BASE 0x40021f0
#define USB_RST_O_BIT_CLEARING_EDGE_REGISTER 0
#define USB_RST_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_RST_O_CAPTURE 0
#define USB_RST_O_DATA_WIDTH 1
#define USB_RST_O_DO_TEST_BENCH_WIRING 0
#define USB_RST_O_DRIVEN_SIM_VALUE 0x0
#define USB_RST_O_EDGE_TYPE "NONE"
#define USB_RST_O_FREQ 50000000u
#define USB_RST_O_HAS_IN 0
#define USB_RST_O_HAS_OUT 1
#define USB_RST_O_HAS_TRI 0
#define USB_RST_O_IRQ -1
#define USB_RST_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_RST_O_IRQ_TYPE "NONE"
#define USB_RST_O_NAME "/dev/USB_RST_O"
#define USB_RST_O_RESET_VALUE 0x0
#define USB_RST_O_SPAN 16
#define USB_RST_O_TYPE "altera_avalon_pio"


/*
 * USB_SCK_O configuration
 *
 */

#define ALT_MODULE_CLASS_USB_SCK_O altera_avalon_pio
#define USB_SCK_O_BASE 0x40021d0
#define USB_SCK_O_BIT_CLEARING_EDGE_REGISTER 0
#define USB_SCK_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_SCK_O_CAPTURE 0
#define USB_SCK_O_DATA_WIDTH 1
#define USB_SCK_O_DO_TEST_BENCH_WIRING 0
#define USB_SCK_O_DRIVEN_SIM_VALUE 0x0
#define USB_SCK_O_EDGE_TYPE "NONE"
#define USB_SCK_O_FREQ 50000000u
#define USB_SCK_O_HAS_IN 0
#define USB_SCK_O_HAS_OUT 1
#define USB_SCK_O_HAS_TRI 0
#define USB_SCK_O_IRQ -1
#define USB_SCK_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_SCK_O_IRQ_TYPE "NONE"
#define USB_SCK_O_NAME "/dev/USB_SCK_O"
#define USB_SCK_O_RESET_VALUE 0x0
#define USB_SCK_O_SPAN 16
#define USB_SCK_O_TYPE "altera_avalon_pio"


/*
 * USB_SCS_O configuration
 *
 */

#define ALT_MODULE_CLASS_USB_SCS_O altera_avalon_pio
#define USB_SCS_O_BASE 0x40021a0
#define USB_SCS_O_BIT_CLEARING_EDGE_REGISTER 0
#define USB_SCS_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_SCS_O_CAPTURE 0
#define USB_SCS_O_DATA_WIDTH 1
#define USB_SCS_O_DO_TEST_BENCH_WIRING 0
#define USB_SCS_O_DRIVEN_SIM_VALUE 0x0
#define USB_SCS_O_EDGE_TYPE "NONE"
#define USB_SCS_O_FREQ 50000000u
#define USB_SCS_O_HAS_IN 0
#define USB_SCS_O_HAS_OUT 1
#define USB_SCS_O_HAS_TRI 0
#define USB_SCS_O_IRQ -1
#define USB_SCS_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_SCS_O_IRQ_TYPE "NONE"
#define USB_SCS_O_NAME "/dev/USB_SCS_O"
#define USB_SCS_O_RESET_VALUE 0x0
#define USB_SCS_O_SPAN 16
#define USB_SCS_O_TYPE "altera_avalon_pio"


/*
 * USB_SDI_O configuration
 *
 */

#define ALT_MODULE_CLASS_USB_SDI_O altera_avalon_pio
#define USB_SDI_O_BASE 0x40021c0
#define USB_SDI_O_BIT_CLEARING_EDGE_REGISTER 0
#define USB_SDI_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_SDI_O_CAPTURE 0
#define USB_SDI_O_DATA_WIDTH 1
#define USB_SDI_O_DO_TEST_BENCH_WIRING 0
#define USB_SDI_O_DRIVEN_SIM_VALUE 0x0
#define USB_SDI_O_EDGE_TYPE "NONE"
#define USB_SDI_O_FREQ 50000000u
#define USB_SDI_O_HAS_IN 0
#define USB_SDI_O_HAS_OUT 1
#define USB_SDI_O_HAS_TRI 0
#define USB_SDI_O_IRQ -1
#define USB_SDI_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_SDI_O_IRQ_TYPE "NONE"
#define USB_SDI_O_NAME "/dev/USB_SDI_O"
#define USB_SDI_O_RESET_VALUE 0x0
#define USB_SDI_O_SPAN 16
#define USB_SDI_O_TYPE "altera_avalon_pio"


/*
 * USB_SDO_I configuration
 *
 */

#define ALT_MODULE_CLASS_USB_SDO_I altera_avalon_pio
#define USB_SDO_I_BASE 0x40021b0
#define USB_SDO_I_BIT_CLEARING_EDGE_REGISTER 0
#define USB_SDO_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USB_SDO_I_CAPTURE 1
#define USB_SDO_I_DATA_WIDTH 1
#define USB_SDO_I_DO_TEST_BENCH_WIRING 0
#define USB_SDO_I_DRIVEN_SIM_VALUE 0x0
#define USB_SDO_I_EDGE_TYPE "RISING"
#define USB_SDO_I_FREQ 50000000u
#define USB_SDO_I_HAS_IN 1
#define USB_SDO_I_HAS_OUT 0
#define USB_SDO_I_HAS_TRI 0
#define USB_SDO_I_IRQ -1
#define USB_SDO_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_SDO_I_IRQ_TYPE "NONE"
#define USB_SDO_I_NAME "/dev/USB_SDO_I"
#define USB_SDO_I_RESET_VALUE 0x0
#define USB_SDO_I_SPAN 16
#define USB_SDO_I_TYPE "altera_avalon_pio"


/*
 * epcs_flash_controller_0 configuration
 *
 */

#define ALT_MODULE_CLASS_epcs_flash_controller_0 altera_avalon_epcs_flash_controller
#define EPCS_FLASH_CONTROLLER_0_BASE 0x4001800
#define EPCS_FLASH_CONTROLLER_0_IRQ 0
#define EPCS_FLASH_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EPCS_FLASH_CONTROLLER_0_NAME "/dev/epcs_flash_controller_0"
#define EPCS_FLASH_CONTROLLER_0_REGISTER_OFFSET 512
#define EPCS_FLASH_CONTROLLER_0_SPAN 2048
#define EPCS_FLASH_CONTROLLER_0_TYPE "altera_avalon_epcs_flash_controller"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none


/*
 * sdram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sdram_0 altera_avalon_new_sdram_controller
#define SDRAM_0_BASE 0x2000000
#define SDRAM_0_CAS_LATENCY 3
#define SDRAM_0_CONTENTS_INFO ""
#define SDRAM_0_INIT_NOP_DELAY 0.0
#define SDRAM_0_INIT_REFRESH_COMMANDS 2
#define SDRAM_0_IRQ -1
#define SDRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_0_IS_INITIALIZED 1
#define SDRAM_0_NAME "/dev/sdram_0"
#define SDRAM_0_POWERUP_DELAY 100.0
#define SDRAM_0_REFRESH_PERIOD 15.625
#define SDRAM_0_REGISTER_DATA_IN 1
#define SDRAM_0_SDRAM_ADDR_WIDTH 0x18
#define SDRAM_0_SDRAM_BANK_WIDTH 2
#define SDRAM_0_SDRAM_COL_WIDTH 9
#define SDRAM_0_SDRAM_DATA_WIDTH 16
#define SDRAM_0_SDRAM_NUM_BANKS 4
#define SDRAM_0_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_0_SDRAM_ROW_WIDTH 13
#define SDRAM_0_SHARED_DATA 0
#define SDRAM_0_SIM_MODEL_BASE 0
#define SDRAM_0_SPAN 33554432
#define SDRAM_0_STARVATION_INDICATOR 0
#define SDRAM_0_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_0_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_0_T_AC 5.5
#define SDRAM_0_T_MRD 3
#define SDRAM_0_T_RCD 20.0
#define SDRAM_0_T_RFC 70.0
#define SDRAM_0_T_RP 20.0
#define SDRAM_0_T_WR 14.0


/*
 * sysid_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_0 altera_avalon_sysid
#define SYSID_0_BASE 0x40022c0
#define SYSID_0_ID 123456789u
#define SYSID_0_IRQ -1
#define SYSID_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_0_NAME "/dev/sysid_0"
#define SYSID_0_SPAN 8
#define SYSID_0_TIMESTAMP 1375177753u
#define SYSID_0_TYPE "altera_avalon_sysid"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x4002020
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000u
#define TIMER_0_IRQ 2
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999ull
#define TIMER_0_MULT 0.0010
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000u
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * timer_1 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_BASE 0x4002040
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_FREQ 50000000u
#define TIMER_1_IRQ 3
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_LOAD_VALUE 49ull
#define TIMER_1_MULT 1.0E-6
#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "us"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_SPAN 32
#define TIMER_1_TICKS_PER_SEC 1000000u
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_TYPE "altera_avalon_timer"


/*
 * uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_0 altera_avalon_uart
#define UART_0_BASE 0x4002000
#define UART_0_BAUD 115200
#define UART_0_DATA_BITS 8
#define UART_0_FIXED_BAUD 1
#define UART_0_FREQ 50000000u
#define UART_0_IRQ 1
#define UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_0_NAME "/dev/uart_0"
#define UART_0_PARITY 'N'
#define UART_0_SIM_CHAR_STREAM ""
#define UART_0_SIM_TRUE_BAUD 0
#define UART_0_SPAN 32
#define UART_0_STOP_BITS 1
#define UART_0_SYNC_REG_DEPTH 2
#define UART_0_TYPE "altera_avalon_uart"
#define UART_0_USE_CTS_RTS 0
#define UART_0_USE_EOP_REGISTER 0


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICKS_PER_SEC TIMER_0_TICKS_PER_SEC
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
