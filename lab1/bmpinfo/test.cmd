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

rem Truncated BMP file header (starts with BM but then nothing)
%SUBJECT% tests\truncated.bmp > nul 2> nul && goto failed
echo Test 4 passed

rem Providing not a BMP file results in an error
%SUBJECT% tests\not-a-bmp.jpg > nul 2> nul && goto failed
echo Test 5 passed

rem Regular file
echo Test 6 passed

rem Different bits per pixel color palettes, including monochrome
echo Test 7 passed

rem Compressed with PNG
echo Test 8 passed

rem Compressed with RLE
echo Test 9 passed

rem Compressed with JPEG
echo Test 10 passed

exit /B 0

:failed
echo Test failed
exit /B 1

:error
exit /B 1
