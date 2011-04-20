# 16369144 ||| 58420198205698048 ||| RT http://www.totallyreal.com @ntiller @DrCodyFaeth Memories... http://i.imgur.com/Aqtmq.jpg
# Need to run top 100,000 of complete_combined_tweets.txt

import sys
import pycurl
import re
import StringIO
import datetime
import calendar
from xml.etree import ElementTree 



def findUserInfo(xml):

#root = ElementTree()
    try:
        root = ElementTree.XML(xml)
    except:
        root = None
    if root is not None:
        userId = root.find("id").text
        followerCount = root.find("followers_count").text
        friendCount = root.find("friends_count").text
        dateCreated = root.find("created_at").text
        
    
        dateRgx = re.match("^.*\s(.*)\s(\d+)\s.*\s(\d+)$",dateCreated)
        
        caldic = dict((v,k) for k,v in enumerate(calendar.month_abbr))
        month = int(caldic[dateRgx.group(1)])
        
        dateCreated = datetime.date(int(dateRgx.group(3)), month, int(dateRgx.group(2)))

        delta = datetime.date.today() - dateCreated


        userInfo = {'friendCount':friendCount, 'followerCount':followerCount, 'dateCreated':dateCreated, 'age':delta.days}
    
        return userInfo
    else:
        return None

def addHyperlink(fullLinkStr):
    fullLinkStr = fullLinkStr.replace(":", "_")

    if fullLinkStr[7:11] == "www.":
        i = 11
    else:
        i = 7

    linkStr = ""
    while i < len(fullLinkStr):
        if fullLinkStr[i] == '/' or fullLinkStr[i] == '.':
            linkStr += " " + fullLinkStr[:i]
        i += 1
    
    linkStr += " " + fullLinkStr[:i]

    return linkStr




def main():
# input is probably nolines_tweet_data.txt.tmp
    if len(sys.argv) < 2:
        print("Please input a file.")
        sys.exit()
    
    readFile = open(sys.argv[1], 'r')
    writeFile = open(str(sys.argv[1]) + ".output", 'w')
    print("Printing to " + str(sys.argv[1]) + ".output")
    tweetSet = set()
    invUserIdSet = set()

    for line in readFile:
        rgx = re.match(r"^(\d+) \|\|\| (\d+) \|\|\| .* \|\|\| .* \|\|\| .* \|\|\| (\d+) \|\|\| (.*)$", line)
        #If for some reason we don't match...
        if rgx is not None and rgx.group(1) not in tweetSet:

            tweetId = rgx.group(1)
            userId = rgx.group(2)
            epochDate = rgx.group(3)
            fullStr = rgx.group(4)
            tweetSet.add(tweetId)
            #print(fullStr)

            tweetDate = datetime.datetime.fromtimestamp(float(epochDate))



            userInfoRgx = re.match("^(.*) \_\_\_ (\d+) \_\_\_ (\d+) \_\_\_ (\d+)$", fullStr)
            #If there's already user data, assign it to the appropriate variables
            if userInfoRgx is not None:
                friendCount = userInfoRgx.group(2)
                followerCount = userInfoRgx.group(3)
                age = userInfoRgx.group(4)
                fullStr = userInfoRgx.group(1)


            linkStr = ""
            for link in re.finditer("(http://[^\s]+)",fullStr):
                linkStr += " " + addHyperlink(link.group(1))


            fullStr = re.sub("http://[^ ]+", " ", fullStr)
            fullStr = linkStr + " " + fullStr
            if userId not in invUserIdSet:

                curlStr = "http://twitter.com/users/" + userId
                curlObj = pycurl.Curl()
                curlObj.setopt(pycurl.URL, curlStr)
                b = StringIO.StringIO()
                curlObj.setopt(pycurl.WRITEFUNCTION, b.write)
                curlObj.perform()
                xml = b.getvalue()
                
                xmlUserInfo = findUserInfo(xml)
            else:
                xmlUserInfo = None
            #tweetDate = getTweetDate(userId, tweetId)
    
            
            
            



            # If we were able to find the user in Twitter
            if xmlUserInfo is not None:
                isSpam = 0
                fullStr = str(isSpam) + " | " + fullStr
                delta = tweetDate.date() - xmlUserInfo['dateCreated']
                if userInfoRgx is not None:
                    userInfo = {'friendCount':friendCount, 'followerCount':followerCount, 'age':age}

                
                else:
                    userInfo = xmlUserInfo
                    userInfo['age'] = delta.days
                fullStr += " |Friends " + str(userInfo['friendCount']) + " |Followers " + str(userInfo['followerCount']) + " |Age " + str(userInfo['age'])

            else:
                invUserIdSet.add(userId)
                isSpam = 1
                fullStr = str(isSpam) + " | " + fullStr
                if userInfoRgx is not None:
                    userInfo = {'friendCount':friendCount, 'followerCount':followerCount, 'age':age}
                    fullStr += " |Friends " + str(userInfo['friendCount']) + " |Followers " + str(userInfo['followerCount']) + " |Age " + str(userInfo['age'])
                



            writeFile.write(fullStr + "\n")

            '''       if userInfo is not None:
                fullStr += " |Friends " + str(userInfo['friendCount']) + " |Followers " + str(userInfo['followerCount']) + " |Age " + str(userInfo['age'])'''


            #print(fullStr)
        '''else:
            print(line)'''
    

main()
