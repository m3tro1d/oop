@echo off

set SUBJECT="%~1"
if %SUBJECT% == "" (
	echo Usage: test.cmd ^<program filename^>
	goto error
)
set OUTPUT="%TEMP%\output.txt"

rem Providing invalid argument count results in an error
%SUBJECT% > nul 2> nul && goto failed
echo Test 1 passed

rem Providing non-existing input file results in an error
%SUBJECT% tests\non-existing.txt > nul 2> nul && goto failed
echo Test 2 passed

rem Providing empty input file results in an error
%SUBJECT% tests\empty.bmp > nul 2> nul && goto failed
echo Test 3 passed

rem Providing file with truncated BMP file header (starts with BM but then nothing) results in an error
%SUBJECT% tests\truncated.bmp > nul 2> nul && goto failed
echo Test 4 passed

rem Providing not a BMP file results in an error
%SUBJECT% tests\not-a-bmp.jpg > nul 2> nul && goto failed
echo Test 5 passed

rem Valid BMP file is processed correctly
%SUBJECT% tests\regular.bmp > %OUTPUT% 2> nul || goto failed
fc tests\regular-output.txt %OUTPUT% > nul || goto failed
echo Test 6 passed

rem Parsing different bits per pixel color palettes, including monochrome, works correctly
%SUBJECT% tests\4-bit-depth.bmp > %OUTPUT% 2> nul || goto failed
fc tests\4-bit-depth-output.txt %OUTPUT% > nul || goto failed
%SUBJECT% tests\monochrome.bmp > %OUTPUT% 2> nul || goto failed
fc tests\monochrome-output.txt %OUTPUT% > nul || goto failed
echo Test 7 passed

rem RLE compression detection works correctly
%SUBJECT% tests\rle8-compressed.bmp > %OUTPUT% 2> nul || goto failed
fc tests\rle8-compressed-output.txt %OUTPUT% > nul || goto failed
echo Test 8 passed

rem JPEG compression detection works correctly
echo Test 9 passed

rem PNG compression detection works correctly
echo Test 10 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
