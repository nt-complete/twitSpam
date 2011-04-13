import sys
import re
import math
if len(sys.argv) < 3:
    print ("Please input file to change and file to output to.")
    sys.exit()

readFile = open(sys.argv[1], 'r')
writeFile = open(sys.argv[2], 'w')

for line in readFile:
    p = re.match(r"(.*)\|Friends (\d+) \|Followers (\d+) \|age (\d+)", line)
    if p is not None:

        friends = int(p.group(2))
        if friends > 0:
            friends = math.log(friends)

        followers = int(p.group(3))
        if followers > 0:
            followers = math.log(followers)

        age = int(p.group(4))
        if age > 0:
            age = math.log(age)

        writeFile.write(p.group(1) + "|Friends " + str(friends) + " |Followers " + str(followers) + " |age " + str(age) + "\n")
    else:
        writeFile.write(line)
