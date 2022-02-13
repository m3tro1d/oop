@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"
set TEST_NUMBER=1

rem Launching with incorrect argument count results in an error
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\regular.txt > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\regular.txt %OUTPUT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\regular.txt %OUTPUT% "work, damn it!" > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt %OUTPUT% one two > %OUTPUT% 2>&1 && goto failed
fc tests\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt one two > %OUTPUT% 2>&1 && goto failed
fc tests\unavailable-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Replacing string in empty file results in the same empty file
%SUBJECT% tests\empty.txt %OUTPUT% string "other string" > nul 2>&1 || goto failed
fc tests\empty-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Replacing pattern in file results in the same file with replacements instead of patterns
%SUBJECT% tests\regular.txt %OUTPUT% to "bonus ducks" > nul 2>&1 || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Replacing with empty string removes search pattern from the file
%SUBJECT% tests\regular.txt %OUTPUT% to "" > nul 2>&1 || goto failed
fc tests\regular-remove-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Replacing repeatable pattern works correctly
%SUBJECT% tests\repeatable-pattern.txt %OUTPUT% cho chocho > nul 2>&1 || goto failed
fc tests\repeatable-pattern-output.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Replacing non-existing search pattern doesn't change the file
%SUBJECT% tests\regular.txt %OUTPUT% "the cake is a lie" "bonus ducks" > nul 2>&1 || goto failed
fc tests\regular.txt %OUTPUT% > nul || goto failed
echo Test %TEST_NUMBER% passed
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

rem Heavy text (over 10000000 occurrences) is processed correctly and fast enough
rem Uncomment if you have Python 3 installed, because fc takes too long to compare files
rem powershell (Measure-Command { ".\\%SUBJECT%" tests\heavy.txt %OUTPUT% A BB }).ToString() || goto failed
rem python ..\..\utils\compare.py tests\heavy-output.txt %OUTPUT% > nul 2>&1 || goto failed
rem echo Test %TEST_NUMBER% passed
echo Test %TEST_NUMBER% skipped
set /a "TEST_NUMBER=%TEST_NUMBER%+1"

echo.
echo All test passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
