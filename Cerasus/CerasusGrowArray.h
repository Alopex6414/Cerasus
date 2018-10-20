/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusGrowArray.h
* @brief	This File is CreasusGrowArray Header File.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSGROWARRAY_H_
#define __CERASUSGROWARRAY_H_

//Include Direct Common Header File
#include "DirectCommon.h"

//Class Definition
template<typename TYPE> class CGrowableArray
{
protected:
	TYPE* m_pData;
	int m_nSize;
	int m_nMaxSize;

protected:
	HRESULT SetSizeInternal(int nNewMaxSize);

public:
	CGrowableArray();
	CGrowableArray(const CGrowableArray <TYPE>& a);
	~CGrowableArray();

	const TYPE& operator[](int nIndex) const;
	TYPE& operator[](int nIndex);
	CGrowableArray& operator=(const CGrowableArray <TYPE>& a)
	{
		if (this == &a) return *this; RemoveAll(); for (int i = 0; i < a.m_nSize;
			i++) Add(a.m_pData[i]); return *this;
	}

	HRESULT SetSize(int nNewMaxSize);
	HRESULT Add(const TYPE& value);
	HRESULT Insert(int nIndex, const TYPE& value);
	HRESULT SetAt(int nIndex, const TYPE& value);
	TYPE& GetAt(int nIndex) const;
	int GetSize() const;
	TYPE* GetData();
	bool Contains(const TYPE& value);

	int IndexOf(const TYPE& value);
	int IndexOf(const TYPE& value, int iStart);
	int IndexOf(const TYPE& value, int iStart, int nNumElements);

	int LastIndexOf(const TYPE& value);
	int LastIndexOf(const TYPE& value, int nIndex);
	int LastIndexOf(const TYPE& value, int iEnd, int nNumElements);

	HRESULT Remove(int nIndex);
	void RemoveAll();
	void Reset();

};

#endif // !__CERASUSGROWARRAY_H_
