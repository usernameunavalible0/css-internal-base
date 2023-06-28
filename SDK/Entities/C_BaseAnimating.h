#pragma once
#include "C_BaseEntity.h"

class CBoneBitList;
class IBoneSetup;
class CBoneAccessor;

struct ClientModelRenderInfo_t : public ModelRenderInfo_t
{
	// Added space for lighting origin override. Just allocated space, need to set base pointer
	matrix3x4_t lightingOffset;

	// Added space for model to world matrix. Just allocated space, need to set base pointer
	matrix3x4_t modelToWorld;
};

class IModelLoadCallback
{
	virtual void OnModelLoadComplete(const model_t* pModel) = 0;
};

class C_BaseAnimating : public C_BaseEntity, private IModelLoadCallback
{
public:
	virtual							~C_BaseAnimating() = 0;

	virtual void					GetBoneControllers(float controllers[MAXSTUDIOBONECTRLS]) = 0;
	virtual float					SetBoneController(int iController, float flValue) = 0;
	virtual void					GetPoseParameters(CStudioHdr* pStudioHdr, float poseParameter[MAXSTUDIOPOSEPARAM]) = 0;
	virtual void					BuildTransformations(CStudioHdr* pStudioHdr, Vector* pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList& boneComputed) = 0;
	virtual void					ApplyBoneMatrixTransform(matrix3x4_t& transform) = 0;
	virtual void					UpdateIKLocks(float currentTime) = 0;
	virtual void					CalculateIKLocks(float currentTime) = 0;
	virtual int						InternalDrawModel(int flags) = 0;
	virtual bool					OnInternalDrawModel(ClientModelRenderInfo_t* pInfo) = 0;
	virtual bool					OnPostInternalDrawModel(ClientModelRenderInfo_t* pInfo) = 0;
	virtual void					ControlMouth(CStudioHdr* pStudioHdr) = 0;
	virtual void					DoAnimationEvents(CStudioHdr* pStudio) = 0;
	virtual void					FireEvent(const Vector& origin, const Vector& angles, int event, const char* options) = 0;
	virtual void					FireObsoleteEvent(const Vector& origin, const Vector& angles, int event, const char* options) = 0;
	virtual const char*				ModifyEventParticles(const char* token) = 0;
	virtual bool					DispatchMuzzleEffect(const char* options, bool isFirstPerson) = 0;
	virtual	void					StandardBlendingRules(CStudioHdr* pStudioHdr, Vector pos[], Quaternion q[], float currentTime, int boneMask) = 0;
	virtual void					AccumulateLayers(IBoneSetup& boneSetup, Vector pos[], Quaternion q[], float currentTime) = 0;
	virtual void					ChildLayerBlend(Vector pos[], Quaternion q[], float currentTime, int boneMask) = 0;
	virtual void					AttachEntityToBone(C_BaseAnimating* attachTarget, int boneIndexAttached = -1, Vector bonePosition = Vector(0, 0, 0), Vector boneAngles = Vector(0, 0, 0)) = 0;
	virtual void					NotifyBoneAttached(C_BaseAnimating* attachTarget) = 0;
	virtual void					UpdateBoneAttachments(void) = 0;
	virtual C_BaseAnimating*		BecomeRagdollOnClient() = 0;
	virtual void					SaveRagdollInfo(int numbones, const matrix3x4_t& cameraTransform, CBoneAccessor& pBoneToWorld) = 0;
	virtual bool					RetrieveRagdollInfo(Vector* pos, Quaternion* q) = 0;
	virtual bool					GetRagdollInitBoneArrays(matrix3x4_t* pDeltaBones0, matrix3x4_t* pDeltaBones1, matrix3x4_t* pCurrentBones, float boneDt) = 0;
	virtual	void					RefreshCollisionBounds(void) = 0;
	virtual void					SetSequence(int nSequence) = 0;
	virtual void					StudioFrameAdvance() = 0;
	virtual float					FrameAdvance(float flInterval = 0.0f) = 0;
	virtual float					GetSequenceCycleRate(CStudioHdr* pStudioHdr, int iSequence) = 0;
	virtual void					UpdateClientSideAnimation() = 0;
	virtual unsigned int			ComputeClientSideAnimationFlags() = 0;
	virtual void					ResetClientsideFrame(void) = 0;
	virtual bool					IsActivityFinished(void) = 0;
	virtual void					UncorrectViewModelAttachment(Vector& vOrigin) = 0;
	virtual void					DoMuzzleFlash() = 0;
	virtual void					ProcessMuzzleFlashEvent() = 0;
	virtual void					SetServerIntendedCycle(float intended) = 0;
	virtual float					GetServerIntendedCycle(void) = 0;
	virtual bool					ShouldResetSequenceOnNewModel(void) = 0;
	virtual bool					IsViewModel() const = 0;
	virtual void					FormatViewModelAttachment(int nAttachment, matrix3x4_t& attachmentToWorld) = 0;
	virtual bool					IsMenuModel() const = 0;
	virtual bool					CalcAttachments() = 0;
	virtual float					LastBoneChangedTime() = 0;
	virtual void					OnModelLoadComplete(const model_t* pModel) = 0;
};