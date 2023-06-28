#pragma once
#include "C_BaseCombatCharacter.h"

class CSteamID;
class CUserCmd;
class IRagdoll;
class C_BaseViewModel;
struct stepsoundtimes_t;
struct surfacedata_t;
class CSoundParameters;
class CHintSystem;

enum PLAYER_ANIM
{
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_JUMP,
	PLAYER_SUPERJUMP,
	PLAYER_DIE,
	PLAYER_ATTACK1,
	PLAYER_IN_VEHICLE,
	PLAYER_RELOAD,
	PLAYER_START_AIMING,
	PLAYER_LEAVE_AIMING,
};

class C_BasePlayer : public C_BaseCombatCharacter, public CGameEventListener
{
public:
	virtual ~C_BasePlayer() = 0;

	virtual void				SharedSpawn() = 0;
	virtual bool				GetSteamID(CSteamID* pID) = 0;
	virtual float				GetPlayerMaxSpeed() = 0;
	virtual void				CalcView(Vector& eyeOrigin, Vector& eyeAngles, float& zNear, float& zFar, float& fov) = 0;
	virtual void				CalcViewModelView(const Vector& eyeOrigin, const Vector& eyeAngles) = 0;
	virtual float				CalcRoll(const Vector& angles, const Vector& velocity, float rollangle, float rollspeed) = 0;
	virtual void				SetPlayerUnderwater(bool state) = 0;
	virtual Vector				Weapon_ShootPosition() = 0;
	virtual void				Weapon_DropPrimary(void) = 0;
	virtual Vector				GetAutoaimVector(float flScale) = 0;
	virtual bool				CreateMove(float flInputSampleTime, CUserCmd* pCmd) = 0;
	virtual void				AvoidPhysicsProps(CUserCmd* pCmd) = 0;
	virtual void				PlayerUse(void) = 0;
	virtual bool				IsUseableEntity(C_BaseEntity* pEntity, unsigned int requiredCaps) = 0;
	virtual int					GetObserverMode() const = 0;
	virtual C_BaseEntity*		GetObserverTarget() const = 0;
	virtual IRagdoll*			GetRepresentativeRagdoll() const = 0;
	virtual void				TeamChange(int iNewTeam) = 0;
	virtual bool				IsAllowedToSwitchWeapons(void) = 0;
	virtual C_BaseCombatWeapon* GetActiveWeaponForSelection(void) = 0;
	virtual C_BaseAnimating*	GetRenderedWeaponModel() = 0;
	virtual bool				IsOverridingViewmodel(void) = 0;
	virtual int					DrawOverriddenViewmodel(C_BaseViewModel* pViewmodel, int flags) = 0;
	virtual float				GetDefaultAnimSpeed(void) = 0;
	virtual void				ThirdPersonSwitch(bool bThirdperson) = 0;
	virtual bool				CanSetSoundMixer(void) = 0;
	virtual int					GetVisionFilterFlags(bool bWeaponsCheck = false) = 0;
	virtual void				CalculateVisionUsingCurrentFlags(void) = 0;
	virtual bool				ViewModel_IsTransparent(void) = 0;
	virtual bool				ViewModel_IsUsingFBTexture(void) = 0;
	virtual void				PreThink(void) = 0;
	virtual void				PostThink(void) = 0;
	virtual void				ItemPreFrame(void) = 0;
	virtual void				ItemPostFrame(void) = 0;
	virtual void				AbortReload(void) = 0;
	virtual void				SelectLastItem(void) = 0;
	virtual void				Weapon_SetLast(C_BaseCombatWeapon* pWeapon) = 0;
	virtual bool				Weapon_ShouldSetLast(C_BaseCombatWeapon* pOldWeapon, C_BaseCombatWeapon* pNewWeapon) = 0;
	virtual bool				Weapon_ShouldSelectItem(C_BaseCombatWeapon* pWeapon) = 0;
	virtual C_BaseCombatWeapon* GetLastWeapon(void) = 0;
	virtual void 				SelectItem(const char* pstr, int iSubType = 0) = 0;
	virtual void				UpdateClientData(void) = 0;
	virtual float				GetFOV(void) = 0;
	virtual bool				IsZoomed(void) = 0;
	virtual void				ViewPunch(const Vector& angleOffset) = 0;
	virtual void				OverrideView(CViewSetup* pSetup) = 0;
	virtual const Vector		GetPlayerMins(void) const = 0;
	virtual const Vector		GetPlayerMaxs(void) const = 0;
	virtual void				SetVehicleRole(int nRole) = 0;
	virtual void				SetAnimation(PLAYER_ANIM playerAnim) = 0;
	virtual float				GetMinFOV() const = 0;
	virtual void				PlayPlayerJingle() = 0;
	virtual void				UpdateStepSound(surfacedata_t* psurface, const Vector& vecOrigin, const Vector& vecVelocity) = 0;
	virtual void				PlayStepSound(Vector& vecOrigin, surfacedata_t* psurface, float fvol, bool force) = 0;
	virtual surfacedata_t*		GetFootstepSurface(const Vector& origin, const char* surfaceName) = 0;
	virtual void				GetStepSoundVelocities(float* velwalk, float* velrun) = 0;
	virtual void				SetStepSoundTime(stepsoundtimes_t iStepSoundTime, bool bWalking) = 0;
	virtual const char*			GetOverrideStepSound(const char* pszBaseStepSoundName) = 0;
	virtual void				OnEmitFootstepSound(const CSoundParameters& params, const Vector& vecOrigin, float fVolume) = 0;
	virtual void				ExitLadder() = 0;
	virtual CHintSystem*		Hints(void) = 0;
	virtual	IMaterial*			GetHeadLabelMaterial(void) = 0;
	virtual void				OnAchievementAchieved(int iAchievement) = 0;
	virtual bool				CanUseFirstPersonCommand(void) = 0;
	virtual void				CalcObserverView(Vector& eyeOrigin, Vector& eyeAngles, float& fov) = 0;
	virtual Vector				GetChaseCamViewOffset(C_BaseEntity* target) = 0;
	virtual void				CalcInEyeCamView(Vector& eyeOrigin, Vector& eyeAngles, float& fov) = 0;
	virtual float				GetDeathCamInterpolationTime() = 0;
	virtual void				CalcDeathCamView(Vector& eyeOrigin, Vector& eyeAngles, float& fov) = 0;
	virtual void				CalcFreezeCamView(Vector& eyeOrigin, Vector& eyeAngles, float& fov) = 0;
	virtual void				SetLocalViewAngles(const Vector& viewAngles) = 0;
	virtual void				SetViewAngles(const Vector& ang) = 0;
	virtual bool				IsDucked(void) const = 0;
	virtual bool				IsDucking(void) const = 0;
	virtual float				GetFallVelocity(void) = 0;

public:
	NETVAR(m_vecPunchAngle, Vector, "CBasePlayer", "m_vecPunchAngle");
	NETVAR(m_fFlags, int, "CBasePlayer", "m_fFlags");
	NETVAR(m_nTickBase, int, "CBasePlayer", "m_nTickBase");
	NETVAR(deadflag, bool, "CBasePlayer", "deadflag");

	inline void SetCurrentCommand(CUserCmd* cmd)
	{
		static const int nOffset = (H::NetVar.Get("CBasePlayer", "m_hConstraintEntity") - 0x4);
		*reinterpret_cast<CUserCmd**>(reinterpret_cast<DWORD>(this) + nOffset) = cmd;
	}

	inline bool UsingStandardWeaponsInVehicle()
	{
		return reinterpret_cast<bool(__thiscall*)(void*)>(U::Offsets.m_dwC_BasePlayer_UsingStandardWeaponsInVehicle)(this);
	}

	inline void UpdateButtonState(int nUserCmdButtonMask)
	{
		reinterpret_cast<void(__thiscall*)(void*, int)>(U::Offsets.m_dwC_BasePlayer_UpdateButtonState)(this, nUserCmdButtonMask);
	}

	inline int& m_nImpulse()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + 0x10C4);
	}
};

namespace Util
{
	inline C_BasePlayer* PlayerByIndex(const int entindex)
	{
		IClientEntity* pEntity = Util::EntityByIndex(entindex);

		return pEntity ? pEntity->As<C_BasePlayer*>() : nullptr;
	}
}