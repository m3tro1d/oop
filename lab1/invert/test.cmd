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

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt > nul 2> nul && goto failed
echo Test 3 passed

rem Providing invalid matrix file results in an error
%SUBJECT% tests\invalid-matrix-format.txt > nul 2> nul && goto failed
echo Test 4 passed

rem Trying to find inverse of a zero-determined matrix results in an error
%SUBJECT% tests\zero-determinant.txt > nul 2> nul && goto failed
echo Test 5 passed

rem Regular matrix (invertible) is processed correctly
%SUBJECT% tests\regular.txt > %OUTPUT% 2> nul || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1