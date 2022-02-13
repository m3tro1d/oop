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
%SUBJECT% tests\regular.txt %OUTPUT% > nul 2> nul && goto failed
%SUBJECT% tests\regular.txt %OUTPUT% "work, damn it!" > nul 2> nul && goto failed
echo Test 1 passed

rem Replacing string in empty file results in the same empty file
%SUBJECT% tests\empty.txt %OUTPUT% string "other string" > nul 2> nul || goto failed
fc tests\empty-output.txt %OUTPUT% > nul || goto failed
echo Test 2 passed

rem Replacing pattern in file results in the same file with replacements instead of patterns
%SUBJECT% tests\regular.txt %OUTPUT% to "bonus ducks" > nul || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 3 passed

rem Replacing with empty string removes search pattern from the file
%SUBJECT% tests\regular.txt %OUTPUT% to "" > nul 2> nul || goto failed
fc tests\regular-remove-output.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem Replacing repeatable pattern works correctly
%SUBJECT% tests\repeatable-pattern.txt %OUTPUT% cho chocho > nul 2> nul || goto failed
fc tests\repeatable-pattern-output.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem Replacing non-existing search pattern doesn't change the file
%SUBJECT% tests\regular.txt %OUTPUT% "the cake is a lie" "bonus ducks" > nul 2> nul || goto failed
fc tests\regular.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

rem Heavy text (over 10000000 occurrences) is processed correctly and fast enough
rem Uncomment if you have Python 3 installed, because fc takes too long to compare files
rem powershell (Measure-Command { ".\\%SUBJECT%" tests\heavy.txt %OUTPUT% A BB }).ToString() || goto failed
rem python ..\..\utils\compare.py tests\heavy-output.txt %OUTPUT% > nul || goto failed
rem echo Test 7 passed
echo Test 7 skipped

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt %OUTPUT% one two > nul 2> nul && goto failed
echo Test 8 passed

rem Providing unavailable output file results in an error
%SUBJECT% tests\regular.txt Y:\output.txt one two > nul 2> nul && goto failed
echo Test 9 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
