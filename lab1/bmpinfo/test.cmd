@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem TODO
rem FILE access, argument count!!

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
