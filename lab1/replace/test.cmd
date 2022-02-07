@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > nul && goto failed
echo Test 1 passed

rem Replacing string in empty file results in the same empty file
%SUBJECT% tests\empty.txt %TEMP%\output.txt string "other string" > nul || goto failed
fc tests\empty-output.txt %TEMP%\output.txt > nul || goto failed
echo Test 2 passed

rem Replacing pattern in file results in the same file with replacements instead of patterns
%SUBJECT% tests\regular.txt %TEMP%\output.txt to "bonus ducks" > nul || goto failed
fc tests\regular-output.txt %TEMP%\output.txt > nul || goto failed
echo Test 3 passed

rem Replacing repeatable pattern works correctly
%SUBJECT% tests\repeatable-pattern.txt %TEMP%\output.txt ма мама > nul || goto failed
fc tests\repeatable-pattern-output.txt %TEMP%\output.txt > nul || goto failed
echo Test 4 passed

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt %TEMP%\output.txt one two > nul && goto failed
echo Test 5 passed

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt one two > nul && goto failed
echo Test 6 passed

:done
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
