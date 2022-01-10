//	Altirra - Atari 800/800XL/5200 emulator
//	Device emulation library - 8bit-Hub emulation
//	Copyright (C) 2022 Anthony Beaucamp
//
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along
//	with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef f_AT_ATDEVICES_HUB_H
#define f_AT_ATDEVICES_HUB_H

#include <vd2/system/vdalloc.h>
#include <vd2/system/vdstl.h>
#include <at/atcore/deviceimpl.h>
#include <at/atvm/vm.h>

class ATPropertySet;

class ATDeviceHub final
	: public ATDevice
	, public IATDevicePortInput
{
	ATDeviceHub(const ATDeviceHub&) = delete;
	ATDeviceHub& operator=(const ATDeviceHub&) = delete;

public:
	ATDeviceHub();
	~ATDeviceHub();
	
	void *AsInterface(uint32 iid) override;

public:
	void GetDeviceInfo(ATDeviceInfo& info) override;
	void GetSettings(ATPropertySet& pset) override;
	bool SetSettings(const ATPropertySet& pset) override;
	void Init() override;
	void ColdReset() override;
	void WarmReset() override;
	void Shutdown() override;

public:	// IATDevicePortInput
	void InitPortInput(IATDevicePortManager *portmgr) override;

private:
	void HubReset();
	void OnPortOutputChanged(uint32 outputState);
	void ReinitPortOutput();

	IATDevicePortManager *mpPortManager = nullptr;
	int mPortInput = -1;
	int mPortOutput = -1;
	uint32 mLastPortState = 0;
	uint8 mPortShift = 0;
};

/////////////////////  DEFINITIONS SHARED WITH HANDY, ORICUTRON, FCEUX   //////////////////////////

// 8bit-Hub Communication
#define HUB_TIMEOUT    1000  // Milliseconds
#define HUB_FILES		  8	 // Number of handles
#define HUB_SLOTS		  8	 // Number of tcp/udp handles
#define HUB_PACKET		256  // Max. byte size of packet

// 8bit-Hub Commands
#define HUB_SYS_ERROR     0
#define HUB_SYS_RESET     1
#define HUB_SYS_NOTIF     2
#define HUB_SYS_SCAN      3
#define HUB_SYS_CONNECT   4
#define HUB_SYS_IP        5
#define HUB_SYS_MOUSE     6
#define HUB_SYS_VERSION   7
#define HUB_SYS_UPDATE    8
#define HUB_DIR_LS       10
#define HUB_DIR_MK       11
#define HUB_DIR_RM       12
#define HUB_DIR_CD       13
#define HUB_FILE_OPEN    21
#define HUB_FILE_SEEK    22
#define HUB_FILE_READ    23
#define HUB_FILE_WRITE   24
#define HUB_FILE_CLOSE   25
#define HUB_UDP_OPEN     30
#define HUB_UDP_RECV     31
#define HUB_UDP_SEND     32
#define HUB_UDP_CLOSE    33
#define HUB_UDP_SLOT     34
#define HUB_TCP_OPEN     40
#define HUB_TCP_RECV     41
#define HUB_TCP_SEND     42
#define HUB_TCP_CLOSE    43
#define HUB_TCP_SLOT     44
#define HUB_WEB_OPEN     50
#define HUB_WEB_RECV     51
#define HUB_WEB_HEADER   52
#define HUB_WEB_BODY     53
#define HUB_WEB_SEND     54
#define HUB_WEB_CLOSE    55
#define HUB_HTTP_GET     60
#define HUB_HTTP_READ    61

typedef struct packet {
	unsigned char ID;
	unsigned char len;
	unsigned char* data;
	unsigned int timeout;
	struct packet* next;
} packet_t;

#endif
