#include "base/abc/abc.h"
#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "misc/vec/vecInt.h"
#include "base/../proof/acec/acecCover.c"
//#include "base/../proof/acec/acecPolyn.c"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
static int Cad_CommandAigOptimization(Abc_Frame_t *pAbc, int argc, char **argv);
static int Cad_Commandpoly(Abc_Frame_t *pAbc, int argc, char **argv);

void init(Abc_Frame_t *pAbc)
{
  Cmd_CommandAdd(pAbc, "Cad", "alg1", Cad_CommandAigOptimization, 0);
  Cmd_CommandAdd(pAbc, "Cad", "alg2", Cad_Commandpoly, 0);
}

void destroy(Abc_Frame_t *pAbc) {}

Abc_FrameInitializer_t frame_initializer = {init, destroy};

struct PackageRegistrationManager
{
  PackageRegistrationManager() { Abc_FrameAddInitializer(&frame_initializer); }
} CadPackageRegistrationManager;

void Cad_Extractfunc(Abc_Frame_t *pAbc, Abc_Ntk_t *pNtk)
{
  Abc_Obj_t *pObj;
  pObj = Abc_NtkObj(pNtk, Vec_PtrSize((pNtk)->vObjs) - 1);
}

Abc_Frame_t* Cad_NtkAigOptimization(Abc_Frame_t *pAbc, Abc_Ntk_t *pNtk)
{
  Abc_Obj_t *pObj;
  pObj = Abc_NtkObj(pNtk, Vec_PtrSize((pNtk)->vObjs) - 1);

  int and_n = Abc_NtkNodeNum(pNtk);
  int level_n = Abc_ObjLevel(pObj);
  bool b_compress2rs = true;
  bool b_dc2 = false;
  while (b_compress2rs)
  {
    Cmd_CommandExecute(pAbc, "compress2rs; ps");
    pNtk = Abc_FrameReadNtk(pAbc);
    pObj = Abc_NtkObj(pNtk, Vec_PtrSize((pNtk)->vObjs) - 1);
    if ((Abc_NtkNodeNum(pNtk) < and_n) || (Abc_ObjLevel(pObj) < level_n))
    {
      and_n = Abc_NtkNodeNum(pNtk);
      level_n = Abc_ObjLevel(pObj);
    }
    else
    {
      b_compress2rs = false;
      b_dc2 = true;
    }
    while (b_dc2)
    {
      Cmd_CommandExecute(pAbc, "dc2; ps");
      pNtk = Abc_FrameReadNtk(pAbc);
      pObj = Abc_NtkObj(pNtk, Vec_PtrSize((pNtk)->vObjs) - 1);
      if ((Abc_NtkNodeNum(pNtk) < and_n) || (Abc_ObjLevel(pObj) < level_n))
      {
        and_n = Abc_NtkNodeNum(pNtk);
        level_n = Abc_ObjLevel(pObj);
        b_compress2rs = true;
        b_dc2 = false;
      }
      else
      {
        b_dc2 = false;
      }
    }
  }
  printf("And: %d\n", and_n);
  printf("Level: %d\n", level_n);
  return pAbc;
}


Abc_Frame_t* Cad_poly(Abc_Frame_t *pAbc, Abc_Ntk_t *pNtk,vector<vector<int> > infoPi,vector<vector<int> > infoPo)
{ 
	pNtk = Abc_FrameReadNtk(pAbc);
  /*  Gia_Man_t * p =	pAbc->pGia;
    Vec_Int_t * vAdds = Ree_ManComputeCuts( p,NULL ,0);
	Ree_ManPrintAdders( vAdds, 1);
	Vec_Int_t *Xor = Vec_IntStart(Vec_IntSize(vAdds)/6);
	Vec_Int_t *Maj = Vec_IntStart(Vec_IntSize(vAdds)/6);
	for(int i=0;6*i <Vec_IntSize(vAdds);i++){
		
		Vec_IntWriteEntry( Xor, i, Vec_IntEntry(vAdds,6*i+3) );
		Vec_IntWriteEntry( Maj, i, Vec_IntEntry(vAdds,6*i+4) );
		cout << "Xor3: " << Vec_IntEntry(Xor,i) <<"      Maj3: " <<Vec_IntEntry(Maj,i)<<endl;
	}
	return pAbc;*/
  int ngatePi = infoPi.size();
  //cout << "nagatePi: " << infoPi.size()<<endl;
  int *pibit = new int [infoPi.size()];
  for(int i =0; i<infoPi.size();i++){
    pibit[i] = infoPi[i].size();
   // cout << "in" << i<<"'s bit = " << pibit[i] <<endl;
  }
  int ngatePo = infoPo.size();
  //cout << "nagatePo: " << infoPo.size()<<endl;
  int *pobit = new int [infoPo.size()];
  for(int i =0; i<infoPo.size();i++){
    pobit[i] = infoPo[i].size();
    //cout << "out" << i<<"'s bit = " << pobit[i] <<endl;
  }
  Cmd_CommandExecute(pAbc, "r out_.v; &get; ps");
  Vec_Int_t * vOrder = NULL;
  char* str =  Gia_PolynBuild_CAD( pAbc->pGia, vOrder, 0, 1, 0 ,ngatePi,pibit,ngatePo,pobit);
  string str2 = str;
  ofstream out("out.txt");
  out << str2;
  out.close();
  
  
  Vec_IntFreeP( &vOrder );
  return pAbc;
}
int Cad_CommandAigOptimization(Abc_Frame_t *pAbc, int argc, char **argv)
{
  Abc_Ntk_t *pNtk = Abc_FrameReadNtk(pAbc);
  
  int c;
  Extra_UtilGetoptReset();
  while ((c = Extra_UtilGetopt(argc, argv, "h")) != EOF)
  {
    switch (c)
    {
    case 'h':
      goto usage;
    default:
      goto usage;
    }
  }
  if (!pNtk)
  {
    Abc_Print(-1, "Empty network.\n");
    return 1;
  }
  // start alg
  Cmd_CommandExecute(pAbc, "st; ps");
  pNtk = Abc_FrameReadNtk(pAbc);
  pAbc = Cad_NtkAigOptimization(pAbc, pNtk);
  Cmd_CommandExecute(pAbc, "st; ps");
  pNtk = Abc_FrameReadNtk(pAbc);
  Cad_Extractfunc(pAbc,pNtk);
  return 0;

usage:
  Abc_Print(-2, "usage: alg [-h]\n");
  Abc_Print(-2, "\t        perform aig structure optimization\n");
  Abc_Print(-2, "\t-h    : print the command usage\n");
  return 1;
}
int Cad_Commandpoly(Abc_Frame_t *pAbc, int argc, char **argv)
{
  Abc_Ntk_t *pNtk = Abc_FrameReadNtk(pAbc);
  Abc_Obj_t* pObj;
  int i;
  vector<vector<int> > infoPi ;
  int tmp1;
  int tmp2;
  int cnt = 0;
  int cnt2 =0;
  //infoPi.resize(cnt);
  Abc_NtkForEachPi(pNtk, pObj, i) {
    stringstream ss("");
    int newtmp;
    //printf("Object Id = %d, name = %s\n", Abc_ObjId(pObj), Abc_ObjName(pObj));
    string str = Abc_ObjName(pObj);
    ss << str;
    ss.ignore(10,'n');
    ss >> newtmp ;
    ss.ignore(1);
    ss>>tmp2;
    
    tmp1 = tmp2==0 ? newtmp :tmp1;
    if(tmp2 ==0 ){
      cnt++;
      cnt2=1;
      infoPi.resize(cnt);
      infoPi[cnt-1].push_back ( tmp2);

    }
    else {
      infoPi[cnt-1].push_back(tmp2);
      cnt2++;
    }
    
    //cout << cnt  << "  " << infoPi[cnt-1][cnt2-1] <<endl;


  }

  vector<vector<int> > infoPo ;
  cnt = 0;
  cnt2 =0;
  infoPo.resize(cnt);

  Abc_NtkForEachPo(pNtk, pObj, i) {
    stringstream ss("");
    int newtmp;
    //printf("Object Id = %d, name = %s\n", Abc_ObjId(pObj), Abc_ObjName(pObj));
    string str = Abc_ObjName(pObj);
    ss << str;
    ss.ignore(10,'t');
    ss >> newtmp ;
    ss.ignore(1);
    ss>>tmp2;
    
    tmp1 = tmp2==0 ? newtmp :tmp1;
    if(tmp2 ==0 ){
      cnt++;
      cnt2=1;
      infoPo.resize(cnt);
      infoPo[cnt-1].push_back ( tmp2);

    }
    else {
      infoPo[cnt-1].push_back(tmp2);
      cnt2++;
    }
    
    //cout << cnt  << "  " << infoPo[cnt-1][cnt2-1] <<endl;


  }
  
  int c;
  Extra_UtilGetoptReset();
  while ((c = Extra_UtilGetopt(argc, argv, "h")) != EOF)
  {
    switch (c)
    {
    case 'h':
      goto usage;
    default:
      goto usage;
    }
  }
  if (!pNtk)
  {
    Abc_Print(-1, "Empty network.\n");
    return 1;
  }
  // start alg2
  //Cmd_CommandExecute(pAbc, "alg1");
  Cmd_CommandExecute(pAbc, "st;&get; ps");
  pNtk = Abc_FrameReadNtk(pAbc);
  pAbc = Cad_poly(pAbc, pNtk, infoPi,infoPo);
  return 0;

usage:
  Abc_Print(-2, "usage: alg2 [-h]\n");
  Abc_Print(-2, "\t        perform aig structure polynomial optimization\n");
  Abc_Print(-2, "\t-h    : print the command usage\n");
  return 1;
}
