#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: D:\CD_BAK\RCQ208_V3_CH_EDITION\04_Nios_Examples\RCQ208_V3_SelfTest_20130730_update\RedCore_2C8V3_Nios_Example.sof to: "..\flash/RedCore_2C8V3_Nios_Example_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/sof2flash --input="D:/CD_BAK/RCQ208_V3_CH_EDITION/04_Nios_Examples/RCQ208_V3_SelfTest_20130730_update/RedCore_2C8V3_Nios_Example.sof" --output="../flash/RedCore_2C8V3_Nios_Example_epcs_flash_controller_0.flash" --epcs 

#
# Programming File: "..\flash/RedCore_2C8V3_Nios_Example_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/RedCore_2C8V3_Nios_Example_epcs_flash_controller_0.flash" --base=0x4001800 --epcs --sidp=0x40022C0 --id=0x75BCD15 --timestamp=1375177753 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

#
# Converting ELF File: D:\CD_BAK\RCQ208_V3_CH_EDITION\04_Nios_Examples\RCQ208_V3_SelfTest_20130730_update\software\V3_SELFTEST_UCOS\V3_SELFTEST_UCOS.elf to: "..\flash/V3_SELFTEST_UCOS_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/elf2flash --input="D:/CD_BAK/RCQ208_V3_CH_EDITION/04_Nios_Examples/RCQ208_V3_SelfTest_20130730_update/software/V3_SELFTEST_UCOS/V3_SELFTEST_UCOS.elf" --output="../flash/V3_SELFTEST_UCOS_epcs_flash_controller_0.flash" --epcs --after="../flash/RedCore_2C8V3_Nios_Example_epcs_flash_controller_0.flash" 

#
# Programming File: "..\flash/V3_SELFTEST_UCOS_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/V3_SELFTEST_UCOS_epcs_flash_controller_0.flash" --base=0x4001800 --epcs --sidp=0x40022C0 --id=0x75BCD15 --timestamp=1375177753 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --go 

