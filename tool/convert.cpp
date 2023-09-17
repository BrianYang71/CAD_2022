#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc,char* argv[]){
	ifstream in(argv[1]);
	if(!in) cout << "file cannot open";

	string line;
	string name = "out_.v";
	//name = name + argv[1];
	ofstream out(name);
	
	while(getline(in,line)){
		stringstream ss(line);
		string tmp;
		string tmpline = line;
		ss >> tmp;
		
		if(tmp == "module" || tmp == "endmodule" || tmp == "input" || tmp =="output" || tmp == "wire"){
			out << line << endl;
		}
		else if(tmp == "xnor") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " ~(" + input1 + " ^ " +input2 + " );";
			
			out << func <<endl;

		}
		else if(tmp == "xor") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " " + input1 + " ^ " +input2 + " ;";
			
			out << func <<endl;

		}
		else if(tmp == "or") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " " + input1 + " | " +input2 + " ;";
			
			out << func <<endl;

		}
		else if(tmp == "and") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " " + input1 + " & " +input2 + " ;";
			
			out << func <<endl;

		}
		else if(tmp == "nand") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " ~(" + input1 + " & " +input2 + " );";
			
			out << func <<endl;

		}
		else if(tmp == "nor") {
			string func = "  assign ";
			string output,input1,input2;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,',');
			getline(ss,input2,')');
			func += " ~(" + input1 + " | " +input2 + " );";
			
			out << func <<endl;

		}
		else if(tmp == "not") {
			string func = "  assign ";
			string output,input1;
			getline(ss,output,'(');
			ss >> output;
			func += output + " =";
			ss.ignore(10,',');
			getline(ss,input1,')');
			func += " ~" + input1 + " ;";
			
			out << func <<endl;

		}
		else if(tmp == "buf") {
			string func = "  assign ";
			string output,input1;
			getline(ss,output,'(');
			ss >> output;
			if(output[output.size()-1] == ',')
				output = output.substr(0,output.size()-1);
			else {
				string ignore;
				getline(ss,ignore,',');
			}
			func += output + " =";
			getline(ss,input1,')');
			func +=  input1 + " ;";
			
			out << func <<endl;

		}
	}

	return 0;
}
