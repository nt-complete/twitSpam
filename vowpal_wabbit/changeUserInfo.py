import sys
if len(sys.argv) < 2:
    print ("Please input file to change.")
else:
    f = open(sys.argv[1], 'r')
    for line in f:
        
