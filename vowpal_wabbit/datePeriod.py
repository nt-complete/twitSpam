import sys
import re
import time

if len(sys.argv) < 2:
    print "Please input the file to read."
    exit

readFile = open(sys.argv[1], "r")


lowest = 99999999999
highest = -1

for line in readFile:
    #print line
    p = re.match(r".* \|\|\| (\d+) \|\|\|.*$", line)
    if p is not None:
        if lowest > int(p.group(1)):
            lowest = int(p.group(1))

        if highest < int(p.group(1)):
            highest = int(p.group(1))



earliest = time.ctime(lowest)
latest = time.ctime(highest)
print earliest + " - " + latest



#print earliest.strftime('%X %x %Z')
