/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectTemplate.h
* @brief	This File is DirectX Library Template Header.
* @author	Alopex/Alice
* @version	v1.00a
* @date		2019-03-30	v1.00a	alopex	Create File.
*/
#pragma once

#ifndef __DIRECTTEMPLATE_H_
#define __DIRECTTEMPLATE_H_

// Include DirectX Common Header File
#include "DirectCommon.h"

// Template Definition
template <typename T>
inline void Safe_Release(T* &p)
{
	if (p != nullptr)
	{
		p->Release();
		p = nullptr;
	}
}

template <typename T>
inline void Safe_Delete(T* &p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void Safe_Delete_Array(T* &p)
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}
}


#endif // !__DIRECTTEMPLATE_H_

