@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"
set TEST_NUMBER=1

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing invalid radix (either source or destination) results in an error
%SUBJECT% 42 1 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-radix-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 37 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-radix-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 10 1 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-destination-radix-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 10 37 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-destination-radix-output.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Incompatible source number and radix result in an error
%SUBJECT% 42 2 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Converting from hexadecimal to binary works correctly
%SUBJECT% A 16 2 > %OUTPUT% 2>&1 || goto failed
fc tests\A-16-2.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Converting from and to arbitrary numeric systems works correctly
%SUBJECT% GUNS 36 10 > %OUTPUT% 2>&1 || goto failed
fc tests\GUNS-36-10.txt %OUTPUT% > nul || goto failed

%SUBJECT% 786232 10 36 > %OUTPUT% 2>&1 || goto failed
fc tests\786232-10-36.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing really big number as either source number or radix results in an error
%SUBJECT% WHATTHEFUCKISTHISNUMBER 36 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 WHATTHEFUCKISTHISNUMBER 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-radix-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% 42 10 WHATTHEFUCKISTHISNUMBER > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-destination-radix-output.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Negative number conversion works correctly
%SUBJECT% -75 8 10 > %OUTPUT% 2>&1 || goto failed
fc tests\-75-8-10.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing really small negative number as a source results in an error
%SUBJECT% -WHATTHEFUCKISTHISNUMBER 36 10 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-source-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Borderline overflowing numbers are processed correctly
%SUBJECT% 2147483647 10 16 > %OUTPUT% 2>&1 || goto failed
fc tests\positive-no-overflow.txt %OUTPUT% > nul || goto failed

%SUBJECT% -2147483648 10 16 > %OUTPUT% 2>&1 || goto failed
fc tests\negative-no-overflow.txt %OUTPUT% > nul || goto failed

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
