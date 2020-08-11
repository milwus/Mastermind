#include <iostream>

#include <ctime>
#include <unordered_map>

using namespace std;

const string options = "ABCDEF";

bool is_correct(const string guess, const string correct, string& retVal)
{
	if(guess.size() != correct.size())
		return false;
	
	int matching = 0, partiallyMatching = 0, missed = 0;
	unordered_map<char, int> partialMatch, correctMap;
	
	for(unsigned i = 0; i < guess.size(); i++){
		if(guess[i] == correct[i])
			matching++;
		else{
			partialMatch[guess[i]]++;
			correctMap[correct[i]]++;
		}
	}
	
	for(auto it : partialMatch){
		auto pointer = correctMap.find(it.first);
		
		if(pointer != correctMap.end())
			partiallyMatching += min(it.second, pointer->second);
		else
			missed += it.second;
	}
	
	bool retBool;
	if(matching == (int)correct.size())
		retBool = true;
	
	int idx = 0;
	while(matching--)
		retVal[idx++] = '#';
	while(partiallyMatching--)
		retVal[idx++] = 'o';
	while(missed--)
		retVal[idx++] = '.';
	cout << endl;
	
	return retBool;
}

string make_random_string(const string& options)
{
	string rand_string;
	srand(time(nullptr));
	
	for(int i = 0; i < 4; i++){
		int idx = rand() % 6;
		rand_string += options[idx];
	}
	
	return rand_string;
}

int main()
{
	cout << "Options: ";
	for(char c: options)
		cout << c << " ";
	cout << endl;
	cout << "# - correct place" << endl;
	cout << "o - incorrect place" << endl;
	cout << ". - doesn't exist" << endl;
	cout << endl;
	
	string guess;
	string correct = make_random_string(options);
	bool success;
	
	for(int i = 1; i <= 6; i++){
		cout << i << ": ";
		cin >> guess;
		string retVal(correct.size(), '.');
		
		success = is_correct(guess, correct, retVal);
		
		cout << i << ": " << retVal << endl;
		
		if(success)
			break;
		else
			cout << endl;
	}
	
	if(success)
		 cout << "Correct answer!";
	else
		cout << correct << endl;
	
	return 0;
}
