@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"
set TRASH="%TEMP%\%RANDOM%.txt"
set TEST_NUMBER=1

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\regular.txt > nul 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt > %OUTPUT% 2>&1 && goto failed
fc tests\unavailable-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing invalid field input results in an error
%SUBJECT% tests\invalid.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Input containing no marker results in an error
%SUBJECT% tests\marker-less.txt %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\marker-less-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Filling the provided input works correctly
%SUBJECT% tests\regular.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Field above 100x100 area is ignored
%SUBJECT% tests\large-field.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\large-field-output.txt %OUTPUT% > nul 2>&1 || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem If the marker is placed outside, all surrounding area is filled
%SUBJECT% tests\who-spilled-the-bucket.txt %OUTPUT% > nul 2>&1 || goto failed
fc tests\who-spilled-the-bucket-output.txt %OUTPUT% > nul 2>&1 || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
