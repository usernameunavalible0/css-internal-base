//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Interfaces between the client.dll and engine
//
//===========================================================================//

#ifndef BASE_CLIENT_DLL_H
#define BASE_CLIENT_DLL_H
#ifdef _WIN32
#pragma once
#endif

#include "IClientEntityList.h"

class IMaterial;
struct ButtonCode_t;
struct vrect_t;
struct ScreenFade_t;
struct datamap_t;
struct typedescription_t;
class CEngineSprite;
class CRenamedRecvTableInfo;
class IFileList;

typedef int qboolean;

typedef struct player_info_s
{
	char			name[MAX_PLAYER_NAME_LENGTH];
	int				userID;
	char			guid[SIGNED_GUID_LEN + 1];
	unsigned __int32			friendsID;
	char			friendsName[MAX_PLAYER_NAME_LENGTH];
	bool			fakeplayer;
	bool			ishltv;
	bool			isreplay;
	CRC32_t			customFiles[MAX_CUSTOM_FILES];
	unsigned char	filesDownloaded;
} player_info_t;

struct AudioState_t
{
	Vector m_Origin;
	Vector m_Angles;
	bool m_bIsUnderwater;
};

enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0,
	SKYBOX_3DSKYBOX_VISIBLE,
	SKYBOX_2DSKYBOX_VISIBLE,
};

struct SkyBoxMaterials_t
{
	IMaterial* material[6];
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};

struct OcclusionParams_t
{
	float	m_flMaxOccludeeArea;
	float	m_flMinOccluderArea;
};

class IBaseClientDLL
{
public:
	virtual int				Init(CreateInterfaceFn appSystemFactory,CreateInterfaceFn physicsFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void			PostInit() = 0;
	virtual void			Shutdown(void) = 0;
	virtual bool			ReplayInit(CreateInterfaceFn replayFactory) = 0;
	virtual bool			ReplayPostInit() = 0;
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	virtual void			LevelInitPostEntity() = 0;
	virtual void			LevelShutdown(void) = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
	virtual int				HudVidInit(void) = 0;
	virtual void			HudProcessInput(bool bActive) = 0;
	virtual void			HudUpdate(bool bActive) = 0;
	virtual void			HudReset(void) = 0;
	virtual void			HudText(const char* message) = 0;
	virtual void			IN_ActivateMouse(void) = 0;
	virtual void			IN_DeactivateMouse(void) = 0;
	virtual void			IN_Accumulate(void) = 0;
	virtual void			IN_ClearStates(void) = 0;
	virtual bool			IN_IsKeyDown(const char* name, bool& isdown) = 0;
	virtual void			IN_OnMouseWheeled(int nDelta) = 0;
	virtual int				IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char* pszCurrentBinding) = 0;
	virtual void			CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool			WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) = 0;
	virtual void			EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual void			DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual void			View_Render(vrect_t* rect) = 0;
	virtual void			RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	virtual void			View_Fade(ScreenFade_t* pSF) = 0;
	virtual void			SetCrosshairAngle(const Vector& angle) = 0;
	virtual void			InitSprite(CEngineSprite* pSprite, const char* loadname) = 0;
	virtual void			ShutdownSprite(CEngineSprite* pSprite) = 0;
	virtual int				GetSpriteSize(void) const = 0;
	virtual void			VoiceStatus(int entindex, qboolean bTalking) = 0;
	virtual void			InstallStringTableCallback(char const* tableName) = 0;
	virtual void			FrameStageNotify(ClientFrameStage_t curStage) = 0;
	virtual bool			DispatchUserMessage(int msg_type, bf_read& msg_data) = 0;
	virtual CSaveRestoreData* SaveInit(int size) = 0;
	virtual void			SaveWriteFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void			SaveReadFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void			PreSave(CSaveRestoreData*) = 0;
	virtual void			Save(CSaveRestoreData*) = 0;
	virtual void			WriteSaveHeaders(CSaveRestoreData*) = 0;
	virtual void			ReadRestoreHeaders(CSaveRestoreData*) = 0;
	virtual void			Restore(CSaveRestoreData*, bool) = 0;
	virtual void			DispatchOnRestore() = 0;
	virtual CStandardRecvProxies* GetStandardRecvProxies() = 0;
	virtual void			WriteSaveGameScreenshot(const char* pFilename) = 0;
	virtual void			EmitSentenceCloseCaption(char const* tokenstream) = 0;
	virtual void			EmitCloseCaption(char const* captionname, float duration) = 0;
	virtual bool			CanRecordDemo(char* errorMsg, int length) const = 0;
	virtual void			OnDemoRecordStart(char const* pDemoBaseName) = 0;
	virtual void			OnDemoRecordStop() = 0;
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName) = 0;
	virtual void			OnDemoPlaybackStop() = 0;
	virtual bool			ShouldDrawDropdownConsole() = 0;
	virtual int				GetScreenWidth() = 0;
	virtual int				GetScreenHeight() = 0;
	virtual void			WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;
	virtual bool			GetPlayerView(CViewSetup& playerView) = 0;
	virtual void			SetupGameProperties(CUtlVector< XUSER_CONTEXT >& contexts, CUtlVector< XUSER_PROPERTY >& properties) = 0;
	virtual unsigned int	GetPresenceID(const char* pIDName) = 0;
	virtual const char* GetPropertyIdString(const unsigned int id) = 0;
	virtual void			GetPropertyDisplayString(unsigned int id, unsigned int value, char* pOutput, int nBytes) = 0;
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated) = 0;
	virtual void			InvalidateMdlCache() = 0;
	virtual void			IN_SetSampleTime(float frametime) = 0;
	virtual void			ReloadFilesInList(IFileList* pFilesToReload) = 0;
	virtual bool			HandleUiToggle() = 0;
	virtual bool			ShouldAllowConsole() = 0;
	virtual CRenamedRecvTableInfo* GetRenamedRecvTableInfos() = 0;
	virtual CMouthInfo* GetClientUIMouthInfo() = 0;
	virtual void			FileReceived(const char* fileName, unsigned int transferID) = 0;
	virtual const char* TranslateEffectForVisionFilter(const char* pchEffectType, const char* pchEffectName) = 0;
	virtual void			ClientAdjustStartSoundParams(struct StartSoundParams_t& params) = 0;
	virtual bool DisconnectAttempt(void) = 0;
	virtual bool IsConnectedUserInfoChangeAllowed(IConVar* pCvar) = 0;
};

namespace I { inline IBaseClientDLL* BaseClientDLL = nullptr; }

#endif // CDLL_INT_H