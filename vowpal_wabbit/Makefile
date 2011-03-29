all: setter thresholdFinder precisionVsRecall sortTweetUserIds combineData preprocess inputMakerWithCurl countLinks


precisionVsRecall: precisionVsRecall.cpp
	g++ -g  precisionVsRecall.cpp -o precisionVsRecall


thresholdFinder: thresholdFinder.cpp
	g++ -g thresholdFinder.cpp -o thresholdFinder

setter: setter.cpp
	g++ -g setter.cpp -o setter


inputMakerWithCurl: inputMakerWithCurl.o curler.o 
	g++ inputMakerWithCurl.o curler.o -lboost_regex -lcurl -ltinyxml -lboost_date_time -o inputMakerWithCurl

inputMakerWithCurl.o: inputMakerWithCurl.cpp curler.h 
	g++ -g -c inputMakerWithCurl.cpp 

curler.o: curler.cpp
	g++ -g -c curler.cpp

sortTweetUserIds: sortTweetUserIds.cpp
	g++ -g sortTweetUserIds.cpp -o sortTweetUserIds

countLinks: countLinks.cpp
	g++ -g -lboost_regex countLinks.cpp -o countLinks

combineData: combineData.cpp
	g++ -g combineData.cpp -o combineData

preprocess: preprocess.cpp
	g++ -g preprocess.cpp -o preprocess


clean:
	rm -f setter inputMakerWithCurl thresholdFinder precisionVsRecall sortTweetUserIds combineData preprocess countLinks *.o

