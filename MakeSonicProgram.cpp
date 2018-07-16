//this program takes two text files (the cantus firmus and the species counterpoint)
//and creates a txt file that can work as a program in sonic pi.
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> Fillvector(ifstream& stream) {
	vector<int> a;
	for (int tmp; stream >> tmp; a.push_back(tmp));
	return a;
}
int convertNote(int n) {
	//middle c is 60 for rasp. pi
	//21 in my program
	return n + 39;
}
int main() {
	ifstream cf_stream;
	ifstream cp_stream;
	ofstream pi_stream;

	cf_stream.open("CFInput.txt");
	cp_stream.open("CounterpointInput.txt");
	pi_stream.open("SonicProgram.txt");

	vector<int> CF = Fillvector(cf_stream);
	vector<int> CP = Fillvector(cp_stream);
	for (int i = 0; i < CP.size(); i++) {
		pi_stream << "play " << convertNote(CF[i]) << '\n' << 
			"play " << convertNote(CP[i]) << '\n' << "sleep 0.5" << endl;//play both notes than sleep
	}

	cout << "Program is done running, press any key to continue" << endl;
	char dummy;
	cin >> dummy;
}
