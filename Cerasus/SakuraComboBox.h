/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraComboBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-14	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURACOMBOBOX_H_
#define __SAKURACOMBOBOX_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraButton.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACOMBOBOX_API	__declspec(dllexport)
#else
#define SAKURACOMBOBOX_API	__declspec(dllimport)
#endif

#define	SAKURACOMBOBOX_CALLMETHOD	__stdcall

//Struct Definition
struct S_SakuraComboBoxItem
{
	WCHAR strText[256];
	void* pData;

	RECT rcActive;
	bool bVisible;
};

//Class Definition
class SAKURACOMBOBOX_API CSakuraComboBox : public CSakuraButton
{
protected:
	int m_iSelected;
	int m_iFocused;
	int m_nDropHeight;
	int m_nSBWidth;

	bool m_bOpened;

	RECT m_rcText;
	RECT m_rcButton;
	RECT m_rcDropdown;
	RECT m_rcDropdownText;

	vector<S_SakuraComboBoxItem*>	m_Items;

public:
			CSakuraComboBox(CSakuraDialog* pDialog = NULL);
	virtual	~CSakuraComboBox();

};

#endif // !__SAKURACOMBOBOX_H_

