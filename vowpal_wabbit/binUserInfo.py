import sys
import re
import math
import pylab 

if len(sys.argv) < 3:
    print ("Please input file to change and file to output to.")
    sys.exit()

readFile = open(sys.argv[1], 'r')
writeFile = open(sys.argv[2], 'w')
friendArray = []
followerArray = []
ageArray = []
spamArray = []

friendBinArray = [3.85014760171, 4.66343909411, 5.45958551414, 13.4612113611]
followerBinArray = [3.49650756147, 4.49980967033, 5.58349630878, 15.9886216161]
ageBinArray = [5.22574667371, 5.94803498918, 6.34212141872, 7.50549227474]

for line in readFile:
    #print(line)

        #print(p.group(1) + " " + p.group(2) + "\n")
    val = re.match("^(.*)\|Friends \d+ [^ ]+ ([^ ]+) \|Followers \d+ [^ ]+ ([^ ]+) \|age \d+ [^ ]+ ([^ ]+)$", line)
    if val is not None:
        spamArray.append(val.group(1))
        friendArray.append(float(val.group(2)))
        followerArray.append(float(val.group(3)))
        ageArray.append(float(val.group(4)))


        #writeFile.write(p.group(1) + " " + p.group(2))

friendEvents, friendEdges, friendPatches = pylab.hist(friendArray, bins=5)
followerEvents, followerEdges, followerPatches = pylab.hist(followerArray, bins=5)
ageEvents, ageEdges, agePatches = pylab.hist(ageArray, bins=5)


'''for value in ageEdges:
    print(value)'''

i = 0
while i < len(friendArray):



    for num in friendEdges:
        oldNum = num
        if friendArray[i] <= oldNum:
            friendNum = num
            break


    for num in followerEdges:
        oldNum = num
        if followerArray[i] <= num:
            followerNum = num
            break


    for num in ageEdges:
        oldNum = num
        if ageArray[i] <= num:
            ageNum = num
            break
        oldNum = num
    
    writeFile.write(spamArray[i] + "|Friends " + str(friendNum) + " |Followers " + str(followerNum) + " |age " + str(ageNum) + "\n")
    i += 1
    
    









