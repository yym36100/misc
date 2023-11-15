cd .\hw
del *.bak

cd ..
del *.rpt
del *.done
del *.summary
del *.txt
del *.bak
del *.sof

cd .\db
del *.* /Q

cd ..\greybox_tmp
del *.* /Q

cd ..\incremental_db
del *.* /Q
cd .\compiled_partitions 
del *.* /Q

cd ..\..\..\sw\mifgen\Debug
del *.* /Q
cd ..\..\multisample_filter\Debug
del *.* /Q
cd ..\..\..