#ifndef DOLORI_GAMEOBJECT_PC_H_
#define DOLORI_GAMEOBJECT_PC_H_

#include <string>
#include "GameActor.h"

class CPc : public CGameActor {
 protected:
  std::string m_imfName;
  int m_honor;
  int m_virtue;
  int m_headDir;
  int m_head;
  int m_headPalette;
  int m_weapon;
  int m_accessory;
  int m_accessory2;
  int m_accessory3;
  int m_shield;
  int m_shoe;
  int m_shoe_count;
  //    /* this+0x3ac */ struct vector3d shoe_pos
  //
  //    /* this+0x3b8 */ int m_renderWithoutLayer
  //    /* this+0x3bc */ class std::string m_headPaletteName
  //
  //    /* this+0x3cc */ class UIPcGage * m_gage
  //    /* this+0x3d0 */ long m_pk_rank
  //    /* this+0x3d4 */ long m_pk_total
  //    /* this+0x3d8 */ class std::vector<CSprRes *, std::allocator<CSprRes *>
  //    > m_sprResList
  //
  //    /* this+0x3e8 */ class std::vector<CActRes *, std::allocator<CActRes *>
  //    >
};

// class CPc {
//  CGameActor, offset = 0x0
//
//    public void CPc(const class CPc &)
//    public void CPc::CPc()
//    public void CPc::~CPc()
//    public void CPc::OnInit()
//    public void CPc::OnExit()
//    public unsigned char CPc::OnProcess()
//    public unsigned char CPc::ProcessState()
//    public void CPc::SetState(int)
//    public void CPc::Render(struct matrix &)
//    public void CPc::SetSprAct(int, int, int, int, int, int, int, int, int,
//    int) public void CPc::SetSprAct2(int, int, int, int, int, int, int, int,
//    int, int, int) public void CPc::SetSprJob(int) public void
//    CPc::SetSprHead(int) public void CPc::SetSprJobDye(int) public void
//    CPc::SetSprWeapon(int) public void CPc::SetSprWeapon2(int) public void
//    CPc::SetSprAccessory(int) public void CPc::SetSprAccessory2(int) public
//    void CPc::SetSprAccessory3(int) public void CPc::SetSprShield(int) public
//    void CPc::SetSprShoe(int) public void CPc::SetImfFileName() public void
//    CPc::SetHeadPaletteName() public void CPc::SetBodyPaletteName() public int
//    CPc::GetWeapon() public void CPc::SetModifyFactorOfmotionSpeed(int) public
//    void CPc::SendMsg(class CGameObject *, int, int, int, int) public void
//    CPc::SetBodyPalette(int) public void CPc::SetHeadPalette(int) public void
//    CPc::SetHonor(int) public void CPc::SetPropensityInfo(int, int) public
//    long GetPKRank() public long GetPKTotal() public void SetPKRank(int)
//    public void SetPKTotal(int)
//    public void CPc::RenderBody2(struct matrix &, int)
//    public void CPc::RenderBodyLayer(struct matrix &, int)
//    public void CPc::RenderShadowLayer(struct matrix &)
//    public void CPc::ProcessGage()
//    public void CPc::SetRank(int, int)
//    public const class std::vector<std::string, std::allocator<std::string > >
//    CPc::GetSprNames() public void CPc::SetSprNames(const class
//    std::vector<std::string, std::allocator<std::string > > &) public const
//    class std::vector<std::string, std::allocator<std::string > >
//    CPc::GetActNames() public void CPc::SetActNames(const class
//    std::vector<std::string, std::allocator<std::string > > &) public const
//    class std::string & GetImfNames() public int GetHeadPalette() public class
//    std::string CPc::GetHeadPaletteName() public void CPc::RenderShoe(int)
//    public int GetHp()
//    public int GetMaxHp()
//    protected void CPc::SetSprNameList(int, const char *)
//    protected const char * CPc::GetSprNameList(int)
//    protected class CSprRes * CPc::GetSprResList(int)
//    protected class CSprRes * CPc::GetIllusionSprResList()
//    protected void CPc::SetActNameList(int, const char *)
//    protected const char * CPc::GetActNameList(int)
//    protected class CActRes * CPc::GetActResList(int)
//    protected class CActRes * CPc::GetIllusionActResList()
//    protected int CPc::MakeWeaponType(int, int)
//    /* this+0x36c */ class std::string m_imfName
//
//    /* this+0x37c */ int m_honor
//    /* this+0x380 */ int m_virtue
//    /* this+0x384 */ int m_headDir
//    /* this+0x388 */ int m_head
//    /* this+0x38c */ int m_headPalette
//    /* this+0x390 */ int m_weapon
//    /* this+0x394 */ int m_accessory
//    /* this+0x398 */ int m_accessory2
//    /* this+0x39c */ int m_accessory3
//    /* this+0x3a0 */ int m_shield
//    /* this+0x3a4 */ int m_shoe
//    /* this+0x3a8 */ int m_shoe_count
//    /* this+0x3ac */ struct vector3d shoe_pos
//
//    /* this+0x3b8 */ int m_renderWithoutLayer
//    /* this+0x3bc */ class std::string m_headPaletteName
//
//    /* this+0x3cc */ class UIPcGage * m_gage
//    /* this+0x3d0 */ long m_pk_rank
//    /* this+0x3d4 */ long m_pk_total
//    /* this+0x3d8 */ class std::vector<CSprRes *, std::allocator<CSprRes *> >
//    m_sprResList
//
//    /* this+0x3e8 */ class std::vector<CActRes *, std::allocator<CActRes *> >
//    m_actResList
//
//    public class CPc & operator=(const class CPc &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif /* DOLORI_GAMEOBJECT_PC_H_ */