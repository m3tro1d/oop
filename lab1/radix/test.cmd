@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > nul 2> nul && goto failed
%SUBJECT% 42 > nul 2> nul && goto failed
%SUBJECT% 42 10 > nul 2> nul && goto failed
echo Test 1 passed

rem Providing invalid radix (either source or destination) results in an error
%SUBJECT% 42 1 10 > nul 2> nul && goto failed
%SUBJECT% 42 37 10 > nul 2> nul && goto failed
%SUBJECT% 42 10 1 > nul 2> nul && goto failed
%SUBJECT% 42 10 37 > nul 2> nul && goto failed
echo Test  passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
