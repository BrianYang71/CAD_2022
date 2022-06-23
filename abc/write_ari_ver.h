#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int count_out(ifstream& in) // Return # of outputs.
{
    int num_of_out = 0;
    string line;
	while(getline(in, line))
	{
		string tmp; 
		stringstream ss(line);
		ss >> tmp;
		if(tmp == "output")
		{
			while(ss >> tmp)
			{
				if(tmp[0] != '[')
				{
					num_of_out++;
				}
			}
		}
	}
	return num_of_out;
}

void write_ari_ver(ifstream& in, ofstream& out, string* formula, int num_of_formulas) // Write arithmetic verilog file.
{
	string line;
	while(getline(in, line))
	{
		string tmp; 
		stringstream ss(line);
		ss >> tmp;
		if(tmp == "module" || tmp == "input" || tmp == "output")
		{
			out << line << endl;
		}
	}
	for (int i = 0; i < num_of_formulas; i++)
	{
		out << "  assign " << formula[i] << ";" << endl;
	}
	out << "endmodule";
	return;
}
