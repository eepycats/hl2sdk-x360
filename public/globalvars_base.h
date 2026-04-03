//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef GLOBALVARS_BASE_H
#define GLOBALVARS_BASE_H

#ifdef _WIN32
#pragma once
#endif

class CSaveRestoreData;

//-----------------------------------------------------------------------------
// Purpose: Global variables used by shared code
//-----------------------------------------------------------------------------
class CGlobalVarsBase
{
public:

	CGlobalVarsBase( bool bIsClient );
	
	// This can be used to filter debug output or to catch the client or server in the act.
	bool IsClient() const;
	
	bool IsRemoteClient() const;

	// for encoding m_flSimulationTime, m_flAnimTime
	int GetNetworkBase( int nTick, int nEntity );

public:
	
	 float realtime;
	 int framecount;
	 float absoluteframetime;
	 float curtime;                      // XREF: CGameServer::SpawnServer(char *,char *,char *)+48C/w
	                                     // SV_Think(bool)+7E/w
	 float frametime;                    // XREF: SV_Think(bool)+93/w
	                                     // SV_Think(bool):loc_1EBF40/w ...
	 int maxClients;                     // XREF: CGameServer::SpawnServer(char *,char *,char *)+2C7/w
	 int tickcount;                      // XREF: CGameServer::SpawnServer(char *,char *,char *):loc_1EAC64/w
	                                     // CGameServer::SpawnServer(char *,char *,char *)+492/r ...
	 float interval_per_tick;
	 float interpolation_amount;
	 int simTicksThisFrame;
	 int network_protocol;
	 CSaveRestoreData *pSaveData;
	 bool m_bClient;                     // XREF: `global constructor keyed to'sv_main.cpp+2CE/w
	 bool m_bRemoteClient;
	 // padding byte
	 // padding byte
	 int nTimestampNetworkingBase;       // XREF: `global constructor keyed to'sv_main.cpp+2D5/w
	 int nTimestampRandomizeWindow;      // XREF: `global constructor keyed to'sv_main.cpp+2DF/w
	
};

inline int CGlobalVarsBase::GetNetworkBase( int nTick, int nEntity )
{
	int nEntityMod = nEntity % nTimestampRandomizeWindow;
	int nBaseTick = nTimestampNetworkingBase * (int)( ( nTick - nEntityMod ) / nTimestampNetworkingBase );
	return nBaseTick;
}

inline CGlobalVarsBase::CGlobalVarsBase( bool bIsClient ) :
	m_bClient( bIsClient ),
	nTimestampNetworkingBase( 100 ),
	nTimestampRandomizeWindow( 32 )
{
}

inline bool CGlobalVarsBase::IsClient() const
{
	return m_bClient;
}

inline bool CGlobalVarsBase::IsRemoteClient() const
{
	return m_bRemoteClient;
}

#endif // GLOBALVARS_BASE_H
