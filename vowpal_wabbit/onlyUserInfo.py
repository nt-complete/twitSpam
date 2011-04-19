import sys
import re
import math
if len(sys.argv) < 3:
    print ("Please input file to change and file to output to.")
    sys.exit()

readFile = open(sys.argv[1], 'r')
writeFile = open(sys.argv[2], 'w')

for line in readFile:
    p = re.match(r"^(\d).*(\|Friends \d+ \|Followers \d+ \|age \d+)$", line)
    if p is not None:
        print(p.group(1) + " " + p.group(2) + "\n")
        writeFile.write(p.group(1) + " " + p.group(2) + "\n")
    else:
        writeFile.write(line)
