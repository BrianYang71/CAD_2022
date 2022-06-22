// To test, run "./write ./out_.v ./test_out.v".
// "out_.v" is test13 with 5 outputs here.
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "./write_ari_ver.h"
using namespace std;

int main(int argc, char *argv[])
{
  ifstream input(argv[1]);
  ofstream output(argv[2]);
  ifstream input_cnt(argv[1]);
  if (!input)
    cout << "The input file cannot be opened!\n";
  if (!output)
    cout << "The output file cannot be opened!\n";

  int num = count_out(input_cnt);
  string formula[num];

  // Please place the simplified formula here.
  formula[0] = "out1 = in1 + in2 + in3";

  write_ari_ver(input, output, formula, num);
  input.close();
  input_cnt.close();
  output.close();
  return 0;
}