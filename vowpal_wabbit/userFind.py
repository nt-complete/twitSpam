import sys
import pycurl
import re
import StringIO
from lxml import etree

def findUserInfo(xml):
    root = etree.parse(xml)

    print(root)
"""    root = root.getroot
    userId = root.Element("id")
    print("Attack readiness!")
    print(userId.tag)"""


def main():
# input is probably nolines_tweet_data.txt.tmp
    if len(sys.argv) < 2:
        print("Please input a file.")
        sys.exit()
    
    readFile = open(sys.argv[1], 'r')
    for line in readFile:
        rgx = re.match(r"^(\d+) \|\|\| \d+ \|\|\| (.*)$", line)
        if rgx is not None:
            userId = rgx.group(1)
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
                findUserInfo(xml)
        else:
            print(line)
    

main()
