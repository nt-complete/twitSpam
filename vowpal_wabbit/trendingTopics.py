import sys
import re
import operator

if len(sys.argv) < 3:
    print ("Input file to search for trending topics and file to output to.")
    exit

readFile = open(sys.argv[1], "r")
writeFile = open(sys.argv[2], "w")

trends = {}
count = 0
for line in readFile:
    p = re.findall("#\w+", line)
    for topic in p:
        q = re.match("#(\w+)", topic)
        topic = q.group(1)

        count += 1
        if topic in trends:
            trends[topic] += 1
        else:
            trends[topic] = 1



sorted_x = sorted(trends.iteritems(), key=operator.itemgetter(1))

print count
for each in sorted_x:
    #if each[1] > 20:
    writeFile.write(str(each[0]) + " " + str(each[1]) + "\n")


#for key in trends.keys():
 #   print(key + " " + str(trends[key]))
            
