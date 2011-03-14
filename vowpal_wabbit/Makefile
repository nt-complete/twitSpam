all: examiner setter inputMakerWithRegex thresholdFinder precisionVsRecall inputMaker sortTweetUserIds combineData preprocess inputMakerWithCurl

examiner: examiner.cpp
	g++ -g examiner.cpp -o examiner

precisionVsRecall: precisionVsRecall.cpp
	g++ -g  precisionVsRecall.cpp -o precisionVsRecall


thresholdFinder: thresholdFinder.cpp
	g++ -g thresholdFinder.cpp -o thresholdFinder

setter: setter.cpp
	g++ -g setter.cpp -o setter

inputMakerWithRegex: inputMakerWithRegex.cpp
	g++ -g inputMakerWithRegex.cpp -lboost_regex -o inputMakerWithRegex

inputMakerWithCurl: inputMakerWithCurl.o curler.o 
	g++ inputMakerWithCurl.o curler.o -lboost_regex -lcurl -ltinyxml -lboost_date_time -o inputMakerWithCurl

inputMakerWithCurl.o: inputMakerWithCurl.cpp curler.h 
	g++ -g -c inputMakerWithCurl.cpp 

curler.o: curler.cpp
	g++ -g -c curler.cpp

inputMaker: inputMaker.cpp
	g++ -g inputMaker.cpp -o inputMaker

sortTweetUserIds: sortTweetUserIds.cpp
	g++ -g sortTweetUserIds.cpp -o sortTweetUserIds

combineData: combineData.cpp
	g++ -g combineData.cpp -o combineData

preprocess: preprocess.cpp
	g++ -g preprocess.cpp -o preprocess


clean:
	rm -f setter examiner inputMakerWithRegex inputMakerWithCurl thresholdFinder precisionVsRecall inputMaker sortTweetUserIds combineData preprocess *.o

