@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Providing invalid argument count results in an error
%SUBJECT% > nul 2> nul && goto failed
echo Test 1 passed

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt > nul 2> nul && goto failed
echo Test 2 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
