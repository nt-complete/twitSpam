all: examiner setter vwInputMaker thresholdFinder precisionVsRecall inputMaker sortTweetUserIds combineData preprocess

examiner: examiner.cpp
	g++ -g examiner.cpp -o examiner

precisionVsRecall: precisionVsRecall.cpp
	g++ -g  precisionVsRecall.cpp -o precisionVsRecall


thresholdFinder: thresholdFinder.cpp
	g++ -g thresholdFinder.cpp -o thresholdFinder

setter: setter.cpp
	g++ -g setter.cpp -o setter

vwInputMaker: vwInputMaker.cpp
	g++ -g vwInputMaker.cpp -o vwInputMaker

inputMaker: inputMaker.cpp
	g++ -g inputMaker.cpp -o inputMaker

sortTweetUserIds: sortTweetUserIds.cpp
	g++ -g sortTweetUserIds.cpp -o sortTweetUserIds

combineData: combineData.cpp
	g++ -g combineData.cpp -o combineData

preprocess: preprocess.cpp
	g++ -g preprocess.cpp -o preprocess


clean:
	rm -f setter examiner vwInputMaker thresholdFinder precisionVsRecall inputMaker sortTweetUserIds combineData preprocess

