rem call copy_here.bat

copy ..\quartus\nios_300.sof
copy ..\sw\t2\t2.elf 

PATH="$PATH";D:\altera\13.0sp1\nios2eds\bin;D:\altera\13.0sp1\nios2eds\bin\gnu\H-i686-mingw32\bin
%QUARTUS_ROOTDIR%\\bin\\quartus_pgm.exe -m jtag -c USB-Blaster[USB-0] -o "p;nios_300.sof"

"%QUARTUS_ROOTDIR%\bin\cygwin\bin\bash.exe" --rcfile ".\test_bashrc"
pause