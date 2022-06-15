#include "base/abc/abc.h"
#include "base/main/main.h"
#include "base/main/mainInt.h"

static int Cad_CommandAigOptimization(Abc_Frame_t *pAbc, int argc, char **argv);

void init(Abc_Frame_t *pAbc)
{
  Cmd_CommandAdd(pAbc, "Cad", "alg", Cad_CommandAigOptimization, 0);
}

void destroy(Abc_Frame_t *pAbc) {}

Abc_FrameInitializer_t frame_initializer = {init, destroy};

struct PackageRegistrationManager
{
  PackageRegistrationManager() { Abc_FrameAddInitializer(&frame_initializer); }
} CadPackageRegistrationManager;

void Cad_NtkAigOptimization(Abc_Frame_t *pAbc, Abc_Ntk_t *pNtk)
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
  Cad_NtkAigOptimization(pAbc, pNtk);
  return 0;

usage:
  Abc_Print(-2, "usage: alg [-h]\n");
  Abc_Print(-2, "\t        perform aig structure optimization\n");
  Abc_Print(-2, "\t-h    : print the command usage\n");
  return 1;
}
