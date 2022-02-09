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
echo Test 2 passed

rem Incompatible source number and radix result in an error
%SUBJECT% 42 2 10 > nul 2> nul && goto failed
echo Test 3 passed

rem Converting from hexadecimal to binary works correctly
%SUBJECT% A 16 2 > %OUTPUT% 2> nul || goto failed
fc tests\A-16-2.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem Converting from and to arbitrary numeric systems works correctly
%SUBJECT% GUNS 36 10 > %OUTPUT% 2> nul || goto failed
fc tests\GUNS-36-10.txt %OUTPUT% > nul || goto failed
%SUBJECT% 786232 10 36 > %OUTPUT% 2> nul || goto failed
fc tests\786232-10-36.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem Providing really big number as either source number or radix results in an error
%SUBJECT% WHATTHEFUCKISTHISNUMBER 36 10 > nul 2> nul && goto failed
%SUBJECT% 42 WHATTHEFUCKISTHISNUMBER 10 > nul 2> nul && goto failed
%SUBJECT% 42 10 WHATTHEFUCKISTHISNUMBER > nul 2> nul && goto failed
echo Test 6 passed

rem Negative number conversion works correctly
%SUBJECT% -75 8 10 > %OUTPUT% 2> nul || goto failed
fc tests\-75-8-10.txt %OUTPUT% > nul || goto failed
echo Test 7 passed

rem Providing really small negative number as a source results in an error
%SUBJECT% -WHATTHEFUCKISTHISNUMBER 36 10 > nul 2> nul && goto failed
echo Test 8 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
