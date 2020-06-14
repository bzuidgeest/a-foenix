@echo off
cls

rem for foenix hardware

del *.tmp

wdc816as -DUSING_816 -DLARGE -V -L fxloader.asm -O fxloader.obj

cd FMX
wdc816cc -ML -Ic:\wdc\projects\foenixLibrary -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include fmxkeyboard.c
wdc816cc -ML -Ic:\wdc\projects\foenixLibrary -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include fmxtimer.c
cd ..

cd misc
wdc816cc -ML -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include pckeys.c
cd ..

wdc816cc -ML -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include keyboard.c
wdc816cc -ML -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include timer.c
wdc816cc -ML -Ic:\wdc\projects\foenixLibrary\fatfs -Ic:\wdc\projects\a-foenix\include main.c

wdcln -HIE -T  -P00 FMX/fmxkeyboard.obj misc/pckeys.obj keyboard.obj FMX/fmxtimer.obj timer.obj main.obj fxloader.obj -L../foenixLibrary/FMX -LML -LCL -O amachine.hex -C10000  -D20000

rem wdc816cc -AT -ML -Ic:\wdc\projects\foenixLibrary\fatfs object.c