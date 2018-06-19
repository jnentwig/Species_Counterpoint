#include <iostream>
#include <cmath>
#include <vector>
#define MAX_NOTE 35
#define MIN_NOTE 0
int NaturalNotes[7] = { 0, 2, 4, 6, 7, 9, 11 };
bool IsNatural(int note){
	note = note % 12;
	for (int i = 0; i < 7; i++) {
		if (note == NaturalNotes[i]) {
			return true;
		}
	}
	return false;
}

//may change this later
int cf[3] = { 24,26,28};

class cptNode {
private:
	int note;
	std::vector<cptNode*> nextNode;
	std::vector<int> cpt; //this is what the cpt is so far //possibly change this to vector of vector of ints
public:
	cptNode(int n) {//this constuctor will only be used for the beginning notes
		note = n;
		nextNode = {};
		cpt = {};
	}
	cptNode(int n, cptNode beforeNode) {
		note = n;
		nextNode = {};
		cpt = cptSoFar(n, beforeNode);
	}
	std::vector<cptNode*> get_nextNode() {
		return nextNode;
	}
	int sizeOfnextNode() {
		return nextNode.size();
	}
	std::vector<int> cptSoFar(int lastnote, cptNode beforeHarmony) {
		std::vector<int> harmony = beforeHarmony.cpt;
		harmony.push_back(lastnote);
		return harmony;
	}
	bool rulesofcpt(int i, std::vector<int> cpt) {
		return (abs(cpt[i] - cpt[i - 1]) != 6)* //no tritones
			(abs(cpt[i] - cpt[i - 1]) != 9)*//  noSixSkip
			(abs(cpt[i] - cpt[i - 1]) <= 12)*// no skip more than octave
			(abs(cpt[i] - cf[i]) <= 16); // within Interval
			//add rule for perfect motion later on
	}
	void addNode(int& note, cptNode&beforeNode) {
		cptNode* NextNode = new cptNode(note, beforeNode);
		beforeNode.nextNode.push_back(NextNode);
	}
	void possibleNodes(cptNode& beforeNode) {
		for (int i = MIN_NOTE; i <= MAX_NOTE; i++) {
			if (IsNatural(i)) {
				if (rulesofcpt(i, beforeNode.cpt)) {
					addNode(i, beforeNode);
				}
			}
		}
	}
};

int main() {
	using namespace std;
	vector<cptNode> Beginning = { (cf[0]), (cf[0] + 7), (cf[0] + 12) };//cpt starts with either unison, fifth, or octave
	//now build
	//fix this stuff later
	for (int i = 0; i < Beginning.size(); i++) {
		Beginning[i].possibleNodes(Beginning[i]);
		for (int j = 0; j < Beginning[i].sizeOfnextNode(); j++) {
			(Beginning[i].get_nextNode[j])*.possibleNodes((Beginning[i].get_nextNode[j])*);
		}
}
