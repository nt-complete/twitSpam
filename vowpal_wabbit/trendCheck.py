import sys
import re

if len(sys.argv) < 3:
    print "Please input trending topics file, tweet file, and file to output to."
    sys.exit()

trendFile = open(sys.argv[1], "r")
tweetFile = open(sys.argv[2], "r")
if len(sys.argv) == 4:
    writeFile = open(sys.argv[3], "w")

wordArray = []
countArray = []
tweetSet = set()
countDict = {}

for line in trendFile:
    p = re.match("^(\w+) (\d+)", line)
    if p is not None:
        wordArray.append(p.group(1))
        countArray.append(p.group(2))
    else:
        sys.exit()

for i in range(len(wordArray)):
    for j in range(i+1, len(wordArray)):
        word1 = wordArray[i]
        word2 = wordArray[j]

        wordCombo = word1 + " " + word2
        countDict[wordCombo] = 0


fullCount = 0
for line in tweetFile:
    r = re.match("^(\d+) .*", line)
    tweetId = r.group(1)
    r = re.match(".*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|.*\|\|\|(.*)", line)
    if r is None:
        tweet = line
    else:
        tweet = r.group(1)


    for i in range(len(wordArray)):
        word1a = wordArray[i]
        tCount = countArray[i]
        word1 = ".*#" + word1a + ".*"
        #word12 = ".*#" + word + " .*"

        count = 0
        for j in range(i+1, len(wordArray)):
            if count >= tCount:
                break
            word2a = wordArray[j]
            word2 = ".*#" + word2a + ".*"
            #word22 =  ".*#" + word + "\Z"

            #print line
            p = re.match(word1, tweet)
            #p2 = re.match(word12, tweet)
            if p is not None: # or p2 is not None:
                q = re.match(word2, tweet)
                #q2 = re.match(word22, tweet)
                if q is not None: # or q2 is not None:
                    if tweetId not in tweetSet:
                        tweetSet.add(tweetId)
                        count += 1
                        fullCount += 1
                        wordCombo = word1a + " " + word2a
                        countDict[wordCombo] += 1
                        if len(sys.argv) == 4:
                            writeFile.write(line)
                        else:
                            print word1 + " " + word2 + " - " + line
                            

print fullCount


for key, value in sorted(countDict.iteritems(), key=lambda (k,v): (v,k)):
    if value > 0:
        print key + " - " + str(value)
