@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Providing invalid argument count results in an error
%SUBJECT% > %OUTPUT% 2>&1 && goto failed
fc tests\invalid-arguments-output.txt %OUTPUT% > nul || goto failed
echo Test 1 passed

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt > %OUTPUT% 2>&1 && goto failed
fc tests\non-existing-output.txt %OUTPUT% > nul || goto failed
echo Test 2 passed

rem Providing empty input file results in an error
%SUBJECT% tests\empty.bmp > %OUTPUT% 2>&1 && goto failed
fc tests\empty-output.txt %OUTPUT% > nul || goto failed
echo Test 3 passed

rem Providing file with truncated BMP file header (starts with BM but then nothing) results in an error
%SUBJECT% tests\truncated.bmp > %OUTPUT% 2>&1 && goto failed
fc tests\truncated-output.txt %OUTPUT% > nul || goto failed
echo Test 4 passed

rem Providing not a BMP file results in an error
%SUBJECT% tests\not-a-bmp.jpg > %OUTPUT% 2>&1 && goto failed
fc tests\not-a-bmp-output.txt %OUTPUT% > nul || goto failed
echo Test 5 passed

rem Valid BMP file is processed correctly
%SUBJECT% tests\regular.bmp > %OUTPUT% 2>&1 || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

rem Parsing different bits per pixel color palettes, including monochrome, works correctly
%SUBJECT% tests\4-bit-depth.bmp > %OUTPUT% 2>&1 || goto failed
fc tests\4-bit-depth-output.txt %OUTPUT% > nul || goto failed

%SUBJECT% tests\monochrome.bmp > %OUTPUT% 2>&1 || goto failed
fc tests\monochrome-output.txt %OUTPUT% > nul || goto failed

echo Test 7 passed

rem Compression detection works correctly
%SUBJECT% tests\rle8-compressed.bmp > %OUTPUT% 2>&1 || goto failed
fc tests\rle8-compressed-output.txt %OUTPUT% > nul || goto failed
echo Test 8 passed

echo.
echo All tests passed
exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
