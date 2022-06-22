#include "base/abc/abc.h"
#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "proof/acec/acec.h"
#include "proof/acec/acecInt.h"
#include "aig/gia/gia.h"

static int Cad_CommandAigOptimization(Abc_Frame_t *pAbc, int argc, char **argv);
static int Cad_CommandAigPrintgates(Abc_Frame_t *pAbc, int argc, char **argv);
static int Cad_CommandPrintFA(Abc_Frame_t *pAbc, int argc, char **argv);

void init(Abc_Frame_t *pAbc)
{
  Cmd_CommandAdd(pAbc, "Cad", "alg", Cad_CommandAigOptimization, 0);
  Cmd_CommandAdd(pAbc, "Cad", "aig_pg", Cad_CommandAigPrintgates, 0);
  Cmd_CommandAdd(pAbc, "Cad", "FA_p", Cad_CommandPrintFA, 0);
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

void Cad_NtkAigPrintgates(Abc_Frame_t *pAbc, Abc_Ntk_t *pNtk)
{
  Abc_Obj_t *pPi;
  Abc_Obj_t *pPo;
  int i, j;
  Abc_NtkForEachPi(pNtk, pPi, i)
  {
    printf("Pi Id = %d, name = %s\n", Abc_ObjId(pPi), Abc_ObjName(pPi));
  }

  Abc_NtkForEachPo(pNtk, pPo, j)
  {
    printf("Po Id = %d, name = %s\n", Abc_ObjId(pPo), Abc_ObjName(pPo));
  }
}

int Cad_CommandAigPrintgates(Abc_Frame_t *pAbc, int argc, char **argv)
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
  Cad_NtkAigPrintgates(pAbc, pNtk);
  return 0;

usage:
  Abc_Print(-2, "usage: alg [-h]\n");
  Abc_Print(-2, "\t        perform aig structure optimization\n");
  Abc_Print(-2, "\t-h    : print the command usage\n");
  return 1;
}

int Cad_CommandPrintFA(Abc_Frame_t *pAbc, int argc, char **argv)
{
  Abc_Ntk_t *pNtk = Abc_FrameReadNtk(pAbc);
  Gia_Man_t *pMan = pAbc->pGia;
  Vec_Int_t *vXors = NULL;
  Vec_Int_t *vAdds = Ree_ManComputeCuts(pMan, &vXors, 0);

  for (int i = 0; 6 * i < Vec_IntSize(vAdds); i++)
  {
    printf("%6d : ", i);
    printf("%6d ", Vec_IntEntry(vAdds, 6 * i + 0));
    printf("%6d ", Vec_IntEntry(vAdds, 6 * i + 1));
    printf("%6d ", Vec_IntEntry(vAdds, 6 * i + 2));
    printf("   ->  ");
    printf("%6d ", Vec_IntEntry(vAdds, 6 * i + 3));
    printf("%6d ", Vec_IntEntry(vAdds, 6 * i + 4));
    printf("  (%d)", Vec_IntEntry(vAdds, 6 * i + 5));
    printf("\n");
  }
  Acec_Box_t *pBox = Acec_ProduceBox(pMan, 0);
  printf("Adders:\n");
  Acec_PrintAdders(pBox->vAdds, vAdds);
  printf("Inputs:\n");
  Vec_WecPrintLits(pBox->vLeafLits);
  printf("Outputs:\n");
  Vec_WecPrintLits(pBox->vRootLits);

  Vec_IntFree(vXors);
  Vec_IntFree(vAdds);

  /*
  Acec_Box_t *pBox = Acec_ProduceBox(p, 0);
  Acec_TreePrintBox(pBox, vAdds);
  Vec_Int_t *vFadds = Gia_ManDetectFullAdders(p, 0, NULL);
  Vec_Int_t *vHadds = Gia_ManDetectHalfAdders(p, 0);
  Vec_Int_t *vOrder = Gia_PolynFindOrder(p, vFadds, vHadds, 1, 0);
  // Vec_Int_t *vTops = Acec_ManPoolTopMost(p, vAdds);
  */

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

  // Vec_IntFree(vAdds);
  // Vec_IntFree(vTops);
  return 0;

usage:
  Abc_Print(-2, "usage: alg [-h]\n");
  Abc_Print(-2, "\t        perform aig structure optimization\n");
  Abc_Print(-2, "\t-h    : print the command usage\n");
  return 1;
}