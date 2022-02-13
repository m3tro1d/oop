from filecmp import cmp
import sys

if len(sys.argv) != 3:
    print('Usage: python compare.py <file 1> <file 2>')
    exit(1)

if cmp(sys.argv[1], sys.argv[2]):
    print('Files are equal')
    exit(0)

print('Files are different')
exit(1)
