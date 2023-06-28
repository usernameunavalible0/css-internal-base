//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#if !defined( IPREDICTION_H )
#define IPREDICTION_H
#ifdef _WIN32
#pragma once
#endif

#include "IGameMovement.h"

class C_BaseEntity;
class C_BasePlayer;

class IPrediction
{
public:
	virtual			~IPrediction(void) = 0;
	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;
	virtual void	Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command) = 0;
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;
	virtual void	OnReceivedUncompressedPacket(void) = 0;
	virtual void	GetViewOrigin(Vector& org) = 0;
	virtual void	SetViewOrigin(Vector& org) = 0;
	virtual void	GetViewAngles(Vector& ang) = 0;
	virtual void	SetViewAngles(Vector& ang) = 0;
	virtual void	GetLocalViewAngles(Vector& ang) = 0;
	virtual void	SetLocalViewAngles(Vector& ang) = 0;
};

class CPrediction : public IPrediction
{
public:
	virtual			~CPrediction(void) = 0;
	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;
	virtual void	Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command) = 0;
	virtual void	OnReceivedUncompressedPacket(void) = 0;
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;
	virtual bool	InPrediction(void) const = 0;
	virtual bool	IsFirstTimePredicted(void) const = 0;
	virtual int		GetIncomingPacketNumber(void) const = 0;
	virtual void	GetViewOrigin(Vector& org) = 0;
	virtual void	SetViewOrigin(Vector& org) = 0;
	virtual void	GetViewAngles(Vector& ang) = 0;
	virtual void	SetViewAngles(Vector& ang) = 0;
	virtual void	GetLocalViewAngles(Vector& ang) = 0;
	virtual void	SetLocalViewAngles(Vector& ang) = 0;
	virtual void	RunCommand(C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper) = 0;
	virtual void	SetupMove(C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* pHelper, CMoveData* move) = 0;
	virtual void	FinishMove(C_BasePlayer* player, CUserCmd* ucmd, CMoveData* move) = 0;
	virtual void	SetIdealPitch(C_BasePlayer* player, const Vector& origin, const Vector& angles, const Vector& viewheight) = 0;
	virtual void	_Update(bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command) = 0;

public:
	CHandle< C_BaseEntity > m_hLastGround;
	bool			m_bInPrediction;
	bool			m_bFirstTimePredicted;
	bool			m_bOldCLPredictValue;
	bool			m_bEnginePaused;
	int				m_nPreviousStartFrame;
	int				m_nCommandsPredicted;
	int				m_nServerCommandsAcknowledged;
	int				m_bPreviousAckHadErrors;
	int				m_nIncomingPacketNumber;
	float			m_flIdealPitch;
};

namespace I { inline CPrediction* ClientPrediction = nullptr; }

#endif // IPREDICTION_H