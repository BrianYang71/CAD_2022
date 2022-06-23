//Command line: ./cost file1.v file2.v
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

double num1 = 0, num2 = 0;

int main(int argc, char* argv[]){	
	string line;
	ifstream in1(argv[1]), in2(argv[2]);
	if(!in1) cout << "File 1 cannot open!\n";
	if(!in2) cout << "File 2 cannot open!\n";	
	while(getline(in1,line)){
		stringstream ss(line);
		string tmp;
		ss >> tmp;
		if(tmp == "module" || tmp == "endmodule" || tmp == "input" || tmp =="output" || tmp == "wire")
		{
			continue;
		}
		else if (tmp == "assign")
		{
			string s;
			getline(ss, s);
			int len = s.length();
			for(int i = 0; i < len; i++)
			{
				if(s[i] == '[' || s[i] == '^' || s[i] == '~' || s[i] == '&' || s[i] == '|')
				{
					num1++;
				}
			}
		}
	}
	while(getline(in2,line)){
		stringstream ss(line);
		string tmp;
		ss >> tmp;
		if(tmp == "module" || tmp == "endmodule" || tmp == "input" || tmp =="output" || tmp == "wire")
		{
			continue;
		}
		else if (tmp == "assign")
		{
			string s;
			getline(ss, s);
			int len = s.length();
			for(int i = 0; i < len; i++)
			{
				if(s[i] == '[' || s[i] == '^' || s[i] == '~' || s[i] == '&' || s[i] == '|')
				{
					num2++;
				}
			}
		}
	}
	cout << "The cost of the 1st verilog file is " << num1 << endl;
	cout << "The cost of the 2nd verilog file is " << num2 << endl;
	cout << "The reduction rate is " << (1 - double(num2/num1)) * 100 << "%." << endl;

	return 0;
}
