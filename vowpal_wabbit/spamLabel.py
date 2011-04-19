# 16369144 ||| 58420198205698048 ||| RT http://www.totallyreal.com @ntiller @DrCodyFaeth Memories... http://i.imgur.com/Aqtmq.jpg


import sys
import pycurl
import re
import StringIO
import BeautifulSoup
from xml.etree.ElementTree import ElementTree



def findUserInfo(xml):
    root = ElementTree()
    root = ElementTree.XML(xml)

    print(root)
"""    root = root.getroot
    userId = root.Element("id")
    print("Attack readiness!")
    print(userId.tag)"""




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
    tweetSet = set()

    for line in readFile:
        rgx = re.match(r"^(\d+) \|\|\| (\d+) \|\|\| (.*)$", line)
        if rgx is not None and rgx.group(2) not in tweetSet:
            userId = rgx.group(1)
            tweetId = rgx.group(2)
            fullStr = rgx.group(3)
            tweetSet.add(tweetId)

            userInfoRgx = re.match("^(.*) \|\|\| (\d+) \|\|\| (\d+) \|\|\| (\d+)$", fullStr)
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

            curlStr = "http://twitter.com/users/" + userId
            curlObj = pycurl.Curl()
            curlObj.setopt(pycurl.URL, curlStr)
            b = StringIO.StringIO()
            curlObj.setopt(pycurl.WRITEFUNCTION, b.write)
            curlObj.perform()
            xml = b.getvalue()

            if userInfoRgx is None:
                findUserInfo(xml)
            else:
                print(fullStr)
    
            if xml is None:
                isSpam = 1
            else:
                isSpam = 0

            fullStr = str(isSpam) + " | " + fullStr
            if userInfoRgx is not None:
                fullStr += " |Friends " + friendCount + " |Followers " + followerCount + " |Age " + age


            #print(fullStr)
        '''else:
            print(line)'''
    

main()
