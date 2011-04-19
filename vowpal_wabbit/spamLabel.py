# 16369144 ||| 58420198205698048 ||| RT http://www.totallyreal.com @ntiller @DrCodyFaeth Memories... http://i.imgur.com/Aqtmq.jpg


import sys
import pycurl
import re
import StringIO
import BeautifulSoup
from lxml import etree

def findUserInfo(xml):
    root = etree.parse(xml)

    print(root)
"""    root = root.getroot
    userId = root.Element("id")
    print("Attack readiness!")
    print(userId.tag)"""


def addHyperlink(fullLinkStr):
    fullLinkStr = fullLinkStr.replace(":", "_")
    #print(fullLinkStr)
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
    
    #print(linkStr)
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
            #linkRgx = re.findall(r"^(.*)(http://[^ ][^ ]*)(.*)$",fullStr);
            #print(fullStr)
            for link in re.finditer("(http://[^\s]+)",fullStr):
                #print(link.group(1))
                fakeStr = addHyperlink(link.group(1))


            fullStr = re.sub("http://[^ ]+", " ", fullStr)
            #print(fullStr)

            curlStr = "http://twitter.com/users/" + userId
            curlObj = pycurl.Curl()
            curlObj.setopt(pycurl.URL, curlStr)
            b = StringIO.StringIO()
            curlObj.setopt(pycurl.WRITEFUNCTION, b.write)
            curlObj.perform()
            xml = b.getvalue()
#print (xml)
            if xml is None:
                isSpam = 1
            else:
                isSpam = 0
                #findUserInfo(xml)
        else:
            print(line)
    

main()
