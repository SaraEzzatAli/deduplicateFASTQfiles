#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

//have not used this..
class fragment
{
	public:
	string id;
	string seq;
	string score;

	int checked = 0; //can have only 1 or 0
	int unique = 1; //can have only 1 or 0
};

//global variables


//a vector of fragments
vector<fragment> fragments;


vector <string> id;
vector <string> sequence;
vector <string> score;

vector <int> checked;
vector <int> unique;

void readFile()
{
	string filename;
	cout << "Please enter your file name: " <<endl;
	cin >> filename;
	ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		cerr <<"Error .. could not open file!";
		exit(1);
	}



//TODO: needs to be tested..
	string line;
	int i = 0;
	while (getline(file, line))
	{

		switch(i)
		{
			case 0:
				id.push_back(line);
				checked.push_back(0);
				unique.push_back(1);
				i++;
				break;
			case 1:
				sequence.push_back(line);
				i++;
				break;
			case 2:
				i++;
				break;
			case 3:
				score.push_back(line);
				i = 0;
				break;
		}
	}

}


void deduplicate()
{
	//iterate over the one of the vector
	for (int i = 0; i < id.size(); i++)
	{
		if (!checked[i])
		{
			//iterate over the vector again starting from the struct in the big for loop
			for (int j = i; j < id.size(); j++)
			{
				if (sequence[i] == sequence[j])
				{
					checked[i] = 1;
					checked[j] = 1;
					unique[j] = 0;
				}
				else
				{
					unique[i] = 1;
				}
			}
		}
	}

}

int main()
{
	readFile();
	deduplicate();
	ofstream f;

	f.open("studenttest.fastq");
	for (int i = 0; i < id.size(); i++)
	{
	//iterate over the struct vector
		if(unique[i])
		{

			//write it to a file
			f << id[i] << "\n";
			f << sequence[i] << "\n";
			f << "+ \n";
			f <<  score[i] << "\n";

			cout << id[i] << endl;
			cout << sequence[i] << endl;
			cout << "+" << endl;
			cout << score[i] << endl;
		}
	}
	f.close();

	//TODO: bonus || output the new fragments to the new file

}
//read in 4 lines at a time as single string as a vector
//save the sequence  seperately as a vector

//print out all the uniqe sequences: it will look like a normal fastQ files but it has NO duplicates.


