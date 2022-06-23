/**CFile****************************************************************
  FileName    [demo.c]
  SystemName  [ABC: Logic synthesis and verification system.]
  PackageName [ABC as a static library.]
  Synopsis    [A demo program illustrating the use of ABC as a static library.]
  Author      [Alan Mishchenko]

  Affiliation [UC Berkeley]
  Date        [Ver. 1.0. Started - June 20, 2005.]
  Revision    [$Id: demo.c,v 1.00 2005/11/14 00:00:00 alanmi Exp $]
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

#if defined(ABC_NAMESPACE)
namespace ABC_NAMESPACE
{
#elif defined(__cplusplus)
extern "C"
{
#endif

  // procedures to start and stop the ABC framework
  // (should be called before and after the ABC procedures are called)
  void Abc_Start();
  void Abc_Stop();

  // procedures to get the ABC framework and execute commands in it
  typedef struct Abc_Frame_t_ Abc_Frame_t;

  Abc_Frame_t *
  Abc_FrameGetGlobalFrame();
  int Cmd_CommandExecute(Abc_Frame_t *pAbc, const char *sCommand);

#if defined(ABC_NAMESPACE)
}
using namespace ABC_NAMESPACE;
#elif defined(__cplusplus)
}
#endif

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************
  Synopsis    [The main() procedure.]
  Description [This procedure compiles into a stand-alone program for
  DAG-aware rewriting of the AIGs. A BLIF or PLA file to be considered
  for rewriting should be given as a command-line argument. Implementation
  of the rewriting is inspired by the paper: Per Bjesse, Arne Boralv,
  "DAG-aware circuit compression for formal verification", Proc. ICCAD 2004.]

  SideEffects []
  SeeAlso     []
***********************************************************************/
int main(int argc, char *argv[])
{
  // parameters
  int fVerify = 0;
  // variables
  Abc_Frame_t *pAbc;
  // char *pFileIn;
  char Command[1000];
  clock_t clkRead, clkResyn = 0, clkVer, clk;

  //////////////////////////////////////////////////////////////////////////
  // get the input file name
  if (argc != 3)
  {
    printf("Wrong number of command-line arguments.\n");
    return 1;
  }
  // convert gate level verilog --->>> dataflow verilog

  ifstream fin(argv[1]);

  string line;
  string name = "out_.v";
  // name = name + argv[1];
  ofstream fout(name);

  while (getline(fin, line))
  {
    stringstream ss(line);
    string tmp;
    string tmpline = line;
    ss >> tmp;

    if (tmp == "module" || tmp == "endmodule" || tmp == "input" || tmp == "output" || tmp == "wire")
    {
      fout << line << endl;
    }
    else if (tmp == "xnor")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " ~(" + input1 + " ^ " + input2 + " );";

      fout << func << endl;
    }
    else if (tmp == "xor")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " " + input1 + " ^ " + input2 + " ;";

      fout << func << endl;
    }
    else if (tmp == "or")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " " + input1 + " | " + input2 + " ;";

      fout << func << endl;
    }
    else if (tmp == "and")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " " + input1 + " & " + input2 + " ;";

      fout << func << endl;
    }
    else if (tmp == "nand")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " ~(" + input1 + " & " + input2 + " );";

      fout << func << endl;
    }
    else if (tmp == "nor")
    {
      string func = "  assign ";
      string output, input1, input2;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ',');
      getline(ss, input2, ')');
      func += " ~(" + input1 + " | " + input2 + " );";

      fout << func << endl;
    }
    else if (tmp == "not")
    {
      string func = "  assign ";
      string output, input1;
      getline(ss, output, '(');
      ss >> output;
      func += output + " =";
      ss.ignore(10, ',');
      getline(ss, input1, ')');
      func += " ~" + input1 + " ;";

      fout << func << endl;
    }
    else if (tmp == "buf")
    {
      string func = "  assign ";
      string output, input1;
      getline(ss, output, '(');
      ss >> output;
      if (output[output.size() - 1] == ',')
        output = output.substr(0, output.size() - 1);
      else
      {
        string ignore;
        getline(ss, ignore, ',');
      }
      func += output + " =";
      getline(ss, input1, ')');
      func += input1 + " ;";

      fout << func << endl;
    }
  }
  fin.close();
  fout.close();

  //////////////////////////////////////////////////////////////////////////
  // start the ABC framework
  Abc_Start();
  pAbc = Abc_FrameGetGlobalFrame();

  clk = clock();
  //////////////////////////////////////////////////////////////////////////
  // read the file (dataflow verilog)
  sprintf(Command, "read ./out_.v");
  if (Cmd_CommandExecute(pAbc, Command))
  {
    fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
    return 1;
  }
  clkRead = clock() - clk;

  //////////////////////////////////////////////////////////////////////////
  // change to GIA
  sprintf(Command, "strash");
  if (Cmd_CommandExecute(pAbc, Command))
  {
    fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
    return 1;
  }
  sprintf(Command, "&get");
  if (Cmd_CommandExecute(pAbc, Command))
  {
    fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
    return 1;
  }

  //////////////////////////////////////////////////////////////////////////
  // algorithm

  sprintf(Command, "print_stats");
  if (Cmd_CommandExecute(pAbc, Command))
  {
    fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
    return 1;
  }

/*  sprintf(Command, "alg2");
  if (Cmd_CommandExecute(pAbc, Command))
  {
    fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
    return 1;
  }*/
  //////////////////////////////////////////////////////////////////////////
  // write the result in output verilog
  ifstream fin2("./out_.v");
  ofstream fout2(argv[2]);
  int num = 1;
  string formula[num];

  // Please place the simplified formula here.
  formula[0] = "out1 = in1 + in2 + in3";

  while (getline(fin2, line))
  {
    string tmp;
    stringstream ss(line);
    ss >> tmp;
    if (tmp == "module" || tmp == "input" || tmp == "output")
    {
      fout2 << line << endl;
    }
  }
  for (int i = 0; i < num; i++)
  {
    fout2 << "  assign " << formula[i] << ";" << endl;
  }
  fout2 << "endmodule";
  fin2.close();
  fout2.close();

  //////////////////////////////////////////////////////////////////////////
  // perform verification
  clk = clock();
  if (fVerify)
  {
    sprintf(Command, "cec %s result.blif", "./out_.v");
    if (Cmd_CommandExecute(pAbc, Command))
    {
      fprintf(stdout, "Cannot execute command \"%s\".\n", Command);
      return 1;
    }
  }
  clkVer = clock() - clk;

  printf("Reading = %6.2f sec   ", (float)(clkRead) / (float)(CLOCKS_PER_SEC));
  printf("Rewriting = %6.2f sec   ", (float)(clkResyn) / (float)(CLOCKS_PER_SEC));
  printf("Verification = %6.2f sec\n", (float)(clkVer) / (float)(CLOCKS_PER_SEC));

  //////////////////////////////////////////////////////////////////////////
  // stop the ABC framework
  Abc_Stop();
  return 0;
}
