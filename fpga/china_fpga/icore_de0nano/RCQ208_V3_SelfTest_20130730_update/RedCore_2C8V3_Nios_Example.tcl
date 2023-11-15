# Copyright (C) 1991-2009 Altera Corporation
# Your use of Altera Corporation's design tools, logic functions 
# and other software and tools, and its AMPP partner logic 
# functions, and any output files from any of the foregoing 
# (including device programming or simulation files), and any 
# associated documentation or information are expressly subject 
# to the terms and conditions of the Altera Program License 
# Subscription Agreement, Altera MegaCore Function License 
# Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by 
# Altera or its authorized distributors.  Please refer to the 
# applicable agreement for further details.

# Quartus II Version 9.0 Build 132 02/25/2009 SJ Full Version
# File: E:\Workspace\RC8Q208_V3_New_32MB_SDRAM\V3_Nios_Test\RedCore_2C8V3_Nios_Example.tcl
# Generated on: Fri Jan 25 12:07:40 2013

package require ::quartus::project

set_location_assignment PIN_117 -to SDRAM_ADDR[12]
set_location_assignment PIN_118 -to SDRAM_ADDR[11]
set_location_assignment PIN_146 -to SDRAM_ADDR[10]
set_location_assignment PIN_127 -to SDRAM_ADDR[9]
set_location_assignment PIN_128 -to SDRAM_ADDR[8]
set_location_assignment PIN_133 -to SDRAM_ADDR[7]
set_location_assignment PIN_134 -to SDRAM_ADDR[6]
set_location_assignment PIN_135 -to SDRAM_ADDR[5]
set_location_assignment PIN_137 -to SDRAM_ADDR[4]
set_location_assignment PIN_151 -to SDRAM_ADDR[3]
set_location_assignment PIN_150 -to SDRAM_ADDR[2]
set_location_assignment PIN_149 -to SDRAM_ADDR[1]
set_location_assignment PIN_147 -to SDRAM_ADDR[0]
set_location_assignment PIN_145 -to SDRAM_BA[1]
set_location_assignment PIN_144 -to SDRAM_BA[0]
set_location_assignment PIN_141 -to SDRAM_CAS
set_location_assignment PIN_116 -to SDRAM_CKE
set_location_assignment PIN_143 -to SDRAM_CS
set_location_assignment PIN_103 -to SDRAM_DQ[15]
set_location_assignment PIN_105 -to SDRAM_DQ[14]
set_location_assignment PIN_106 -to SDRAM_DQ[13]
set_location_assignment PIN_107 -to SDRAM_DQ[12]
set_location_assignment PIN_108 -to SDRAM_DQ[11]
set_location_assignment PIN_110 -to SDRAM_DQ[10]
set_location_assignment PIN_112 -to SDRAM_DQ[9]
set_location_assignment PIN_113 -to SDRAM_DQ[8]
set_location_assignment PIN_104 -to SDRAM_DQ[7]
set_location_assignment PIN_102 -to SDRAM_DQ[6]
set_location_assignment PIN_101 -to SDRAM_DQ[5]
set_location_assignment PIN_99 -to SDRAM_DQ[4]
set_location_assignment PIN_97 -to SDRAM_DQ[3]
set_location_assignment PIN_96 -to SDRAM_DQ[2]
set_location_assignment PIN_95 -to SDRAM_DQ[1]
set_location_assignment PIN_94 -to SDRAM_DQ[0]
set_location_assignment PIN_114 -to SDRAM_DQM[1]
set_location_assignment PIN_138 -to SDRAM_DQM[0]
set_location_assignment PIN_142 -to SDRAM_RAS
set_location_assignment PIN_139 -to SDRAM_WE
set_location_assignment PIN_27 -to RST_B
set_location_assignment PIN_23 -to SYSCLK
set_location_assignment PIN_115 -to SDRAM_CLK
set_location_assignment PIN_14 -to UART_RX
set_location_assignment PIN_15 -to UART_TX
set_location_assignment PIN_82 -to LCD_DATA[15]
set_location_assignment PIN_160 -to LCD_DATA[14]
set_location_assignment PIN_168 -to LCD_DATA[13]
set_location_assignment PIN_165 -to LCD_DATA[12]
set_location_assignment PIN_164 -to LCD_DATA[11]
set_location_assignment PIN_163 -to LCD_DATA[10]
set_location_assignment PIN_162 -to LCD_DATA[9]
set_location_assignment PIN_161 -to LCD_DATA[8]
set_location_assignment PIN_152 -to LCD_DATA[7]
set_location_assignment PIN_92 -to LCD_DATA[6]
set_location_assignment PIN_90 -to LCD_DATA[5]
set_location_assignment PIN_89 -to LCD_DATA[4]
set_location_assignment PIN_88 -to LCD_DATA[3]
set_location_assignment PIN_87 -to LCD_DATA[2]
set_location_assignment PIN_86 -to LCD_DATA[1]
set_location_assignment PIN_84 -to LCD_DATA[0]
set_location_assignment PIN_185 -to LCD_CS
set_location_assignment PIN_81 -to LCD_RD
set_location_assignment PIN_77 -to LCD_RS
set_location_assignment PIN_169 -to LCD_RST
set_location_assignment PIN_80 -to LCD_WR
set_location_assignment PIN_182 -to TEMP_IO
set_location_assignment PIN_208 -to PS2_CLK
set_location_assignment PIN_207 -to PS2_DATA
set_location_assignment PIN_60 -to RTC_CLK
set_location_assignment PIN_61 -to RTC_IO
set_location_assignment PIN_63 -to RTC_RST
set_location_assignment PIN_74 -to IR_IO
set_location_assignment PIN_129 -to KEY[6]
set_location_assignment PIN_130 -to KEY[5]
set_location_assignment PIN_76 -to KEY[4]
set_location_assignment PIN_28 -to KEY[3]
set_location_assignment PIN_131 -to KEY[2]
set_location_assignment PIN_75 -to KEY[1]
set_location_assignment PIN_132 -to KEY[0]
set_location_assignment PIN_187 -to BUZZER_OUT
set_location_assignment PIN_41 -to DAC_CLK
set_location_assignment PIN_30 -to DAC_DATA[7]
set_location_assignment PIN_31 -to DAC_DATA[6]
set_location_assignment PIN_33 -to DAC_DATA[5]
set_location_assignment PIN_34 -to DAC_DATA[4]
set_location_assignment PIN_35 -to DAC_DATA[3]
set_location_assignment PIN_37 -to DAC_DATA[2]
set_location_assignment PIN_39 -to DAC_DATA[1]
set_location_assignment PIN_40 -to DAC_DATA[0]
set_location_assignment PIN_64 -to LED_DATA[5]
set_location_assignment PIN_67 -to LED_DATA[4]
set_location_assignment PIN_68 -to LED_DATA[3]
set_location_assignment PIN_69 -to LED_DATA[2]
set_location_assignment PIN_72 -to LED_DATA[1]
set_location_assignment PIN_70 -to LED_DATA[0]
set_location_assignment PIN_58 -to ADC_CLK
set_location_assignment PIN_59 -to ADC_CS
set_location_assignment PIN_57 -to ADC_DAT[7]
set_location_assignment PIN_56 -to ADC_DAT[6]
set_location_assignment PIN_48 -to ADC_DAT[5]
set_location_assignment PIN_47 -to ADC_DAT[4]
set_location_assignment PIN_46 -to ADC_DAT[3]
set_location_assignment PIN_45 -to ADC_DAT[2]
set_location_assignment PIN_44 -to ADC_DAT[1]
set_location_assignment PIN_43 -to ADC_DAT[0]
set_location_assignment PIN_173 -to SD_CLK
set_location_assignment PIN_170 -to SD_CS
set_location_assignment PIN_171 -to SD_DI
set_location_assignment PIN_175 -to SD_DO
set_location_assignment PIN_206 -to USB_PC_I
set_location_assignment PIN_198 -to USB_RST_O
set_location_assignment PIN_201 -to USB_SCK_O
set_location_assignment PIN_203 -to USB_SCS_O
set_location_assignment PIN_200 -to USB_SDI_O
set_location_assignment PIN_199 -to USB_SDO_I
set_location_assignment PIN_197 -to ETH_CS_O
set_location_assignment PIN_205 -to ETH_INT_I
set_location_assignment PIN_6 -to ETH_RESET_O
set_location_assignment PIN_5 -to ETH_SCK_O
set_location_assignment PIN_4 -to ETH_SI_O
set_location_assignment PIN_3 -to ETH_SO_I
set_location_assignment PIN_188 -to I2C_SDA
set_location_assignment PIN_189 -to I2C_SCL
set_location_assignment PIN_176 -to TUBE_EN[0]
set_location_assignment PIN_179 -to TUBE_EN[1]
set_location_assignment PIN_180 -to TUBE_EN[2]
set_location_assignment PIN_181 -to TUBE_EN[3]
set_location_assignment PIN_24 -to SYSCLK_40MHZ
set_location_assignment PIN_11 -to VGA_BLUE
set_location_assignment PIN_12 -to VGA_GREEN
set_location_assignment PIN_13 -to VGA_RED
set_location_assignment PIN_8 -to VGA_HSYNC
set_location_assignment PIN_10 -to VGA_VSYNC
