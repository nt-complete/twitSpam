import sys
import re
if len(sys.argv) < 2:
    print ("Please input file to change.")
else:
    f = open(sys.argv[1], 'r')
    for line in f:
        p = re.compile("[a-z]+\d+")
        m = p.search(line)
        if m is not None:
            print(m.group())
