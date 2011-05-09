import sys
import re 

if len(sys.argv) < 3:
    print "Please input single trend file, tweet file, and (optional) output file"
    sys.exit()

trendFile = open(sys.argv[1], "r")
tweetFile = open(sys.argv[2], "r")

if len(sys.argv) == 4:
    writeFile = open(sys.argv[3], "w")

trendSet = set()
lineCount = 0

for line in trendFile:
    p = re.match("^(\w+)", line)
    if p is None:
        print line
    else:
        trendSet.add(p.group(1))

#print len(trendSet)

for line in tweetFile:
    p = re.findall("#(\w+)", line)
    fullCount = len(p)
    count = 0
    for topic in p:
        if topic in trendSet:
            count += 1
    if count != fullCount:
        lineCount += 1
        if len(sys.argv) == 4:
            writeFile.write(line)
        else:
            print line

