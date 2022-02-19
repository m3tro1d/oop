@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"
set TRASH="%TEMP%\%RANDOM%.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\regular.txt > nul 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

echo Test 1 passed

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test 2 passed

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt > %OUTPUT% 2>&1 && goto failed
fc tests\unavailable-output.txt %OUTPUT% > nul || goto failed
echo Test 3 passed

rem Existing but not available for writing output file results in an error
%SUBJECT% tests\regular.txt %SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\not-writable-output.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem Providing invalid field input results in an error
%SUBJECT% tests\invalid.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-output.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem Input containing no marker results in an error
%SUBJECT% tests\marker-less.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\marker-less-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

rem Filling the provided input works correctly
%SUBJECT% tests\regular.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 7 passed

rem Field above 100x100 area is ignored
%SUBJECT% tests\large-field.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\large-field-output.txt %OUTPUT% > nul 2>&1 || goto failed
echo Test 8 passed

rem If the marker is placed outside, all surrounding area is filled
%SUBJECT% tests\who-spilled-the-bucket.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\who-spilled-the-bucket-output.txt %OUTPUT% > nul 2>&1 || goto failed
echo Test 9 passed

rem Maximum fill field is not causing stack overflow
%SUBJECT% tests\max-field.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\max-field-output.txt %OUTPUT% > nul 2>&1 || goto failed
echo Test 10 passed

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
