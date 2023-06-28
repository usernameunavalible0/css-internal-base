#pragma once
#include "C_BaseCombatWeapon.h"

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN

};

enum CSWeaponID
{
	WEAPON_NONE = 0,
	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HEGRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKEGRENADE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_UMP45,
	WEAPON_SG550,
	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_AWP,
	WEAPON_MP5NAVY,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90,
	WEAPON_SHIELDGUN,
	WEAPON_KEVLAR,
	WEAPON_ASSAULTSUIT,
	WEAPON_NVG,
	WEAPON_MAX,
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	virtual				~C_WeaponCSBase() = 0;

	virtual bool		IsFullAuto() const = 0;
	virtual float		GetMaxSpeed() const = 0;
	virtual CSWeaponID	GetWeaponID(void) const = 0;
	virtual bool		IsSilenced(void) const = 0;
	virtual void		SetWeaponModelIndex(const char* pName) = 0;
	virtual void		OnJump(float fImpulse) = 0;
	virtual void		OnLand(float fVelocity) = 0;
	virtual int			GetMuzzleAttachment(void) = 0;
	virtual bool		HideViewModelWhenZoomed(void) = 0;
	virtual void		UpdateShieldState(void) = 0;
	virtual Activity	GetDeployActivity(void) = 0;
	virtual bool		DefaultPistolReload() = 0;
	virtual float		GetInaccuracy() const = 0;
	virtual float		GetSpread() const = 0;
	virtual void		UpdateAccuracyPenalty() = 0;
};