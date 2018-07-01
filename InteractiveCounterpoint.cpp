#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define MAX_NOTE 35
#define MIN_NOTE 0
int NaturalNotes[7] = { 0, 2, 4, 6, 7, 9, 11 };
bool IsNatural(int note) {
	note = note % 12;
	for (int i = 0; i < 7; i++) {
		if (note == NaturalNotes[i]) {
			return true;
		}
	}
	return false;
}

//may change this later
int cf[3] = { 24,26,28 };

class cptNode {
private:
	int note;
	vector<cptNode*> nextNode;
	vector<int> cpt; //this is what the cpt is so far //possibly change this to vector of vector of ints
public:
	cptNode(int n) {//this constuctor will only be used for the beginning notes
		note = n;
		nextNode = {};
		cpt = {};
	}
	cptNode(int n, std::vector<int> beforeNode) {
		note = n;
		nextNode = {};
		cpt = beforeNode;
		cpt.push_back(n);
	}
	std::vector<cptNode*> get_nextNode() {
		return nextNode;
	}
	int get_Note() {
		return note;
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
		return (abs(cpt[i] - cpt[i - 1]) != 6) &&   //no tritones
			(abs(cpt[i] - cpt[i - 1]) != 9) &&  //  noSixSkip
			(abs(cpt[i] - cpt[i - 1]) <= 12) &&  // no skip more than octave
			(abs(cpt[i] - cf[i]) <= 16); // within Interval
										 //going to add rule for perfect motion later on
	}
	void addNode(int& note) {
		cptNode* NextNode = new cptNode(note, this->cpt);
		this->nextNode.push_back(NextNode);
	}
	void possibleNodes() {
		for (int i = MIN_NOTE; i <= MAX_NOTE; i++) {
			if (IsNatural(i)) {
				if (rulesofcpt(i, this->cpt)) {
					addNode(i);
					std::cout << this->note << '\t' << i << std::endl;
				}
			}
		}
	}
	friend void PrintVector(vector<cptNode*> vect);
	friend void findNextNote(cptNode& node, int countDown);
};
void findNextNote(cptNode& node, int countDown) {//change
	node.possibleNodes;
	cout << "The next note could be:" << endl;
	PrintVector(node.get_nextNode);
	if (countDown > 1) {
		int a;
		cin >> a;
		findNextNote(node.get_nextNode[a - 1], countDown--);
	}
}
void PrintVector(vector<cptNode*> vect) {
	for (int i = 0; i < vect.size(); i++) {
		cout << vect[i]->note << '\t';
	}
	cout << endl;
}
int main() {
	cout << "Here is the cantus firmus:" << endl;
	for (int i = 0; i < 3; i++) {
		cout << cf[i] << '\t';
	}
	vector<cptNode> Beginning = { (cf[0]), (cf[0] + 7), (cf[0] + 12) };//cpt starts with either unison, fifth, or octave
	cout << "The first note in the species counterpoint could be:" << endl;
	for (int i = 0; i < 3; i++) {
		cout << Beginning[i].get_Note << '\t';
	}
	int a;
	cin >> a;
	findNextNote(Beginning[a - 1], 3);
	cout << "This is the end of the counterpoint" << endl;
	char dummy;
	cin >> dummy;
}
