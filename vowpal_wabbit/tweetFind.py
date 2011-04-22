import sys
import pycurl
import re
import StringIO
from lxml import etree


def main():
# input is probably nolines_tweet_data.txt.tmp
    if len(sys.arg) < 3:
        print ("Please input file to change and file to output to.")
        sys.exit()

    readFile = open(sys.argv[1], 'r')
    writeFile = open(sys.argv[2], 'w')
    curlStr = "http://twitter.com/#!/ceruleanbill/status/59998317995761665"
    
    curlObj = pycurl.Curl()
    curlObj.setopt(pycurl.URL, curlStr)
    b = StringIO.StringIO()
    curlObj.setopt(pycurl.WRITEFUNCTION, b.write)
    curlObj.perform()
    xml = b.getvalue()
    print (xml)


main()
