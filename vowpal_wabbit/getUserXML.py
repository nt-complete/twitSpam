import sys
import pycurl
import StringIO


userInfo = raw_input("Input username or id: ")

curlStr = "twitter.com/users/" + str(userInfo)

curlObj = pycurl.Curl()
curlObj.setopt(pycurl.URL, curlStr)
b = StringIO.StringIO()
curlObj.setopt(pycurl.WRITEFUNCTION, b.write)
curlObj.perform()
xml = b.getvalue()

print(xml)
