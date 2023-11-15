rem call copy_here.bat

copy ..\quartus\firstnios2_time_limited.sof
copy ..\quartus\software\test1\test1.elf

PATH="$PATH";D:\altera\13.0sp1\nios2eds\bin;D:\altera\13.0sp1\nios2eds\bin\gnu\H-i686-mingw32\bin
start %QUARTUS_ROOTDIR%\\bin\\quartus_pgm.exe -m jtag -c USB-Blaster[USB-0] -o "p;firstnios2_time_limited.sof"

pause
"%QUARTUS_ROOTDIR%\bin\cygwin\bin\bash.exe" --rcfile ".\test_bashrc"
pause