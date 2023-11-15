@ REM ######################################
@ REM # Variable to ignore <CR> in DOS
@ REM # line endings
@ set SHELLOPTS=igncr

@ REM ######################################
@ REM # Variable to ignore mixed paths
@ REM # i.e. G:/$SOPC_KIT_NIOS2/bin
@ set CYGWIN=nodosfilewarning

E:\Tools\rare\intelFPGA\17.1\quartus\bin64\quartus_pgm.exe -m jtag -c 1 -o "p;DE10_Lite_ControlPanel.sof"

