@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > nul 2> nul && goto failed
echo Test 1 passed

rem Providing non-existing matrix file results in an error
%SUBJECT% tests\non-existing.txt > nul 2> nul && goto failed
echo Test 2 passed

rem Providing invalid matrix file results in an error
%SUBJECT% tests\invalid-matrix-format.txt > nul 2> nul && goto failed
echo Test 3 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
