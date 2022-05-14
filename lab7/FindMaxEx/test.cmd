@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\e2e\invalid-arguments-output.txt %OUTPUT% > nul || goto failed
echo Test 1 passed

rem Providing non-existing sportsmen file results in an error
%SUBJECT% tests\e2e\non-existing.txt > %OUTPUT% 2>&1 && goto failed
fc tests\e2e\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test 2 passed

rem Providing invalid sportsmen file results in an error
%SUBJECT% tests\e2e\invalid-format.txt > %OUTPUT% 2>&1 && goto failed
fc tests\e2e\invalid-format-output.txt %OUTPUT% > nul || goto failed
echo Test 3 passed

rem Empty sportsmen file results in an error
%SUBJECT% tests\e2e\empty.txt > %OUTPUT% 2>&1 && goto failed
fc tests\e2e\empty-output.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem File with one sportsman is processed correctly
%SUBJECT% tests\e2e\one.txt > %OUTPUT% 2>&1 || goto failed
fc tests\e2e\one-output.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem File with several sportsmen is processed correctly
%SUBJECT% tests\e2e\regular.txt > %OUTPUT% 2>&1 || goto failed
fc tests\e2e\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
