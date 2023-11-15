#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: E:\WORK\iBoard\infinity\fpga\dso.sof to: "..\flash/dso_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/sof2flash --input="E:/WORK/iBoard/infinity/fpga/dso.sof" --output="../flash/dso_epcs_flash_controller_0.flash" --epcs --verbose 

#
# Programming File: "..\flash/dso_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/dso_epcs_flash_controller_0.flash" --base=0x1001800 --epcs --sidp=0x1002010 --id=0x7 --timestamp=1340895316 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

#
# Converting ELF File: E:\WORK\iBoard\infinity\fpga\software\iboard_niosii_firmware\iboard_niosii_firmware.elf to: "..\flash/iboard_niosii_firmware_epcs_flash_controller_0.flash"
#
$SOPC_KIT_NIOS2/bin/elf2flash --input="E:/WORK/iBoard/infinity/fpga/software/iboard_niosii_firmware/iboard_niosii_firmware.elf" --output="../flash/iboard_niosii_firmware_epcs_flash_controller_0.flash" --epcs --after="../flash/dso_epcs_flash_controller_0.flash" --verbose 

#
# Programming File: "..\flash/iboard_niosii_firmware_epcs_flash_controller_0.flash" To Device: epcs_flash_controller_0
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/iboard_niosii_firmware_epcs_flash_controller_0.flash" --base=0x1001800 --epcs --sidp=0x1002010 --id=0x7 --timestamp=1340895316 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

