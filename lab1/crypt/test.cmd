@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"
set BIN_OUTPUT="%TEMP%\output.bin"
set TRASH="%TEMP%\%RANDOM%.txt"

rem Launching with incorrect argument count returns non-zero exit code
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% crypt > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% crypt tests\regular.jpg > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% crypt tests\regular.jpg %TRASH% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed

echo Test 1 passed

rem Providing invalid mode results in an error
%SUBJECT% celebration tests\regular.jpg %TRASH% 12 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-mode-output.txt %OUTPUT% > nul || goto failed
echo Test 2 passed

rem Providing invalid key results in an error
%SUBJECT% decrypt tests\regular.jpg %TRASH% houston > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-key-output.txt %OUTPUT% > nul || goto failed
echo Test 3 passed

rem Providing invalid key value results in an error
%SUBJECT% decrypt tests\regular.jpg %TRASH% 256 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-key-value-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% decrypt tests\regular.jpg %TRASH% -1 > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-key-value-output.txt %OUTPUT% > nul || goto failed

echo Test 4 passed

rem Providing non-existing input file results in an error
%SUBJECT% crypt tests\non-existing.jpg %TRASH% 42 > %OUTPUT% 2>&1 && goto failed
fc tests\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem Providing unavailable output file results in an error
%SUBJECT% crypt tests\regular.jpg Y:\output.bin 42 > %OUTPUT% 2>&1 && goto failed
fc tests\unavailable-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

rem Existing but not available for writing output file results in an error
%SUBJECT% crypt tests\regular.jpg %SUBJECT% 42 > %OUTPUT% 2>&1 && goto failed
fc tests\not-writable-output.txt %OUTPUT% > nul || goto failed
echo Test 7 passed

rem Providing empty input file results in an empty output in both encryption and decryption
%SUBJECT% crypt tests\empty.bin %BIN_OUTPUT% 42 > nul 2>&1 || goto failed
fc /b tests\empty-output.bin %BIN_OUTPUT% > nul || goto failed

%SUBJECT% decrypt tests\empty-output.bin %BIN_OUTPUT% 42 > nul 2>&1 || goto failed
fc /b tests\empty.bin %BIN_OUTPUT% > nul || goto failed

echo Test 8 passed

rem Normal encryption and decryption works correctly
%SUBJECT% crypt tests\regular.jpg %BIN_OUTPUT% 42 > nul 2>&1 || goto failed
fc /b tests\regular-42-output.bin %BIN_OUTPUT% > nul || goto failed

%SUBJECT% decrypt tests\regular-42-output.bin %BIN_OUTPUT% 42 > nul 2>&1 || goto failed
fc /b tests\regular.jpg %BIN_OUTPUT% > nul || goto failed

echo Test 9 passed

rem Trying to decrypt file encrypted with different key doesn't produce the same file
%SUBJECT% decrypt tests\regular-42-output.bin %BIN_OUTPUT% 13 > nul 2>&1 || goto failed
fc /b tests\regular.jpg %BIN_OUTPUT% > nul 2>&1 && goto failed
echo Test 10 passed

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
