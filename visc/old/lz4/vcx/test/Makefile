CC=cl -c -nologo -W2 -O2 -MD
LINK=link /NOLOGO /OPT:NOWIN98
RC=rc
CCO=-Fo
LNKO=/OUT:
RCO=/fo
MAKEFILES=Makefile
WCXTEST_VER=0.22

all : wcxtest.exe

zip : wcxtest-$(WCXTEST_VER).zip


wcxtest.exe : $(MAKEFILES) wcxtest.obj wcxtest.res
    $(LINK) $(LNKO)wcxtest.exe wcxtest.obj wcxtest.res user32.lib

wcxtest.obj : $(MAKEFILES) wcxtest.c
    $(CC) $(CCO)wcxtest.obj wcxtest.c

wcxtest.res : $(MAKEFILES) wcxtest.rh wcxtest.rc
	$(RC) $(RCO)$@ wcxtest.rc

wcxtest-$(WCXTEST_VER).zip : $(MAKEFILES) wcxtest.rc wcxtest.rh wcxtest.c wcxtest.exe README.txt READMEru.txt
    -del wcxtest-$(WCXTEST_VER).zip
    zip -rX9 wcxtest-$(WCXTEST_VER).zip $(MAKEFILES) wcxtest.rc wcxtest.rh wcxtest.c wcxtest.exe README.txt READMEru.txt


clean :
    -del wcxtest.exe
    -del wcxtest.obj
    -del wcxtest-$(WCXTEST_VER).zip
