import sys
import re 

if len(sys.argv) < 2:
    print "Input tweet file and output file."
    sys.exit()

readFile = open(sys.argv[1], "r")

if len(sys.argv) == 3:
    writeFile = open(sys.argv[2], "w")

countDict = {}

for line in readFile:
    p = re.match(".*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|(.*)", line)
    tweet = p.group(1)
    p = re.findall("#\w+", tweet)
    length = len(p)
    if length == 10:
        print line
    if length in countDict:
        countDict[length] += 1 
    else:
        countDict[length] = 1



if len(sys.argv) == 3:
    for key in countDict.keys():
        writeFile.write(str(key) + " - " + str(countDict[key]))
else:
    for key in countDict.keys():
        print str(key) + " - " + str(countDict[key])
