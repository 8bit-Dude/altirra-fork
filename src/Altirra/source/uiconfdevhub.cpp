//	Altirra - Atari 800/800XL/5200 emulator
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
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include <stdafx.h>
#include <at/atcore/propertyset.h>
#include <at/atnativeui/dialog.h>
#include <at/atnativeui/uiproxies.h>
#include "resource.h"

class ATUIDialogDeviceHub : public VDDialogFrameW32 {
public:
	ATUIDialogDeviceHub(ATPropertySet& props);

protected:
	bool OnLoaded();
	void OnDataExchange(bool write);

	ATPropertySet& mPropSet;
	VDUIProxyComboBoxControl mComboJoyPort;
};

ATUIDialogDeviceHub::ATUIDialogDeviceHub(ATPropertySet& props)
	: VDDialogFrameW32(IDD_DEVICE_HUB)
	, mPropSet(props)
{
}

bool ATUIDialogDeviceHub::OnLoaded() {
	AddProxy(&mComboJoyPort, IDC_PORT);
	mComboJoyPort.AddItem(L"Port 2");
	mComboJoyPort.SetSelection(0);
	return VDDialogFrameW32::OnLoaded();
}

void ATUIDialogDeviceHub::OnDataExchange(bool write) {
	if (write) {
		mPropSet.Clear();
		mPropSet.SetUint32("port", 1);
	} else {
		mComboJoyPort.SetSelection(0);
	}
}

bool ATUIConfDevHub(VDGUIHandle hParent, ATPropertySet& props) {
	ATUIDialogDeviceHub dlg(props);
	return dlg.ShowDialog(hParent) != 0;
}
