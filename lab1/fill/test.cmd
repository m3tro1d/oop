@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > nul 2> nul && goto failed
%SUBJECT% tests\regular.txt > nul 2> nul && goto failed
echo Test 1 passed

rem Providing invalid field input results in an error
%SUBJECT% tests\invalid.txt %OUTPUT% > nul 2> nul && goto failed
echo Test 2 passed

rem Input containing no marker results in an error
%SUBJECT% tests\marker-less.txt %OUTPUT% > nul 2> nul && goto failed
echo Test 3 passed

rem Filling the provided input works correctly
%SUBJECT% tests\regular.txt %OUTPUT% > nul 2> nul || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem Field above 100x100 area is ignored
%SUBJECT% tests\large-field.txt %OUTPUT% > nul 2> nul || goto failed
fc tests\large-field-output.txt %OUTPUT% > nul 2> nul || goto failed
echo Test 5 passed

rem If the marker is placed outside, all surrounding area is filled
%SUBJECT% tests\who-spilled-the-bucket.txt %OUTPUT% > nul 2> nul || goto failed
fc tests\who-spilled-the-bucket-output.txt %OUTPUT% > nul 2> nul || goto failed
echo Test 6 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
