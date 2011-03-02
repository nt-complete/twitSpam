all: examiner setter vwInputMaker thresholdFinder precisionVsRecall

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

clean:
	rm -f setter examiner vwInputMaker thresholdFinder precisionVsRecall

