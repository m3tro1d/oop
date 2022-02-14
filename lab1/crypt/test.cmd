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

rem Providing unavailable output file results in an error

rem Existing but not available for writing output file results in an error

rem Providing empty input file results in an empty output in both encryption and decryption

rem Normal encryption and decryption works correctly

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
