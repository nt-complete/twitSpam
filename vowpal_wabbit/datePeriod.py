import sys
import re
import time
import datetime
import pylab
import operator

if len(sys.argv) < 3:
    print "Please input the file to read and file to output to."
    sys.exit()


decTime = 1293782400
decEnd = datetime.datetime(2010, 12, 30, 23, 59, 59)

decEndEpoch = time.mktime(decEnd.timetuple())
epochDay = 86400
readFile = open(sys.argv[1], "r")
writeFile = open(sys.argv[2], "w")
dateDict = {}
dateTrend = {}
trends = {}


lowest = 99999999999
highest = -1

janBeg = datetime.datetime(2011, 1, 10, 00, 00, 00)
janEnd = datetime.datetime(2011, 1, 10, 23, 59, 59)
#print str(time.mktime(janBeg.timetuple())) + " - " + str(time.mktime(janEnd.timetuple()))


for i in range(32):
    dateTrend[i*epochDay] = 0
    dateDict[i*epochDay] = 0
    #print i*epochDay

trendCount = 0
for line in readFile:
    #print line
    p = re.match(r".* \|\|\| (\d+) \|\|\|.*$", line)
    if p is not None:
        if int(p.group(1)) >= 1294646400 and int(p.group(1)) <= 1294732799:
           writeFile.write(line)
        
''' if lowest > int(p.group(1)):
            lowest = int(p.group(1))

        if highest < int(p.group(1)):
            highest = int(p.group(1))
                
        mult = int((int(p.group(1))-decTime)/epochDay)

        dateDict[mult*epochDay] += 1

        p = re.findall(r" #\w+ ", line)
        if p is not None:
            for topic in p:
                dateTrend[mult*epochDay] += 1
                trendCount += 1
                q = re.match(r" #(\w+) ", topic)
                topic = q.group(1)
                if topic in trends:
                    trends[topic] += 1
                else:
                    trends[topic] = 1
            

highcount = 0
print trendCount
for i in range(32):
    print str(i) + " tweets:" + str(dateDict[i*epochDay]) + " topics:" + str(dateTrend[i*epochDay])
    if highcount < dateDict[i*epochDay]:
        highcount = dateDict[i*epochDay]
        isave = i
        
print str(isave) + " - " + str(highcount) 


sorted_x = sorted(trends.iteritems(), key=operator.itemgetter(1))

for each in sorted_x:
    if each[1] > 10:
        writeFile.write(str(each[0]) + " " + str(each[1]) + "\n")
'''

'''
earliest = time.ctime(lowest)
latest = time.ctime(highest)
print earliest + " " + str(lowest) + " - " + latest + " " + str(highest-decTime)

testDate = time.ctime(highest+epochDay)
print testDate
testDate = time.ctime(lowest+epochDay)
print testDate
'''
