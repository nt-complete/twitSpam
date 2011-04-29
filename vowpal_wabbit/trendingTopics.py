import sys
import re
import operator

if len(sys.argv) < 3:
    print ("Input file to search for trending topics and file to output to.")
    exit

readFile = open(sys.argv[1], "r")
writeFile = open(sys.argv[2], "w")

trends = {}
for line in readFile:
    p = re.findall(r"#\w+", line)
    for topic in p:
        p = re.match(r"#(\w+)", topic)
        topic = p.group(1)

        if topic in trends:
            trends[topic] += 1
        else:
            trends[topic] = 1



sorted_x = sorted(trends.iteritems(), key=operator.itemgetter(1))


for each in sorted_x:
    if each[1] > 200:
        writeFile.write(str(each[0]) + " " + str(each[1]) + "\n")


#for key in trends.keys():
 #   print(key + " " + str(trends[key]))
            
