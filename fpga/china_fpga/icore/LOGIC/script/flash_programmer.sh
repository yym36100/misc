#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: E:\WORK\iCore\demo\LOGIC\iCore_niosII.sof to: "..\flash/iCore_niosII_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/sof2flash --input="E:/WORK/iCore/demo/LOGIC/iCore_niosII.sof" --output="../flash/iCore_niosII_epcs_flash_controller_0.flash" --epcs --verbose 

#
# Programming File: "..\flash/iCore_niosII_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/iCore_niosII_epcs_flash_controller_0.flash" --base=0x1001800 --epcs --sidp=0x1002010 --id=0x929 --timestamp=1338063208 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

#
# Converting ELF File: E:\WORK\iCore\demo\LOGIC\software\icore_niosii\icore_niosii.elf to: "..\flash/icore_niosii_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/elf2flash --input="E:/WORK/iCore/demo/LOGIC/software/icore_niosii/icore_niosii.elf" --output="../flash/icore_niosii_epcs_flash_controller_0.flash" --epcs --after="../flash/iCore_niosII_epcs_flash_controller_0.flash" --verbose 

#
# Programming File: "..\flash/icore_niosii_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/icore_niosii_epcs_flash_controller_0.flash" --base=0x1001800 --epcs --sidp=0x1002010 --id=0x929 --timestamp=1338063208 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

