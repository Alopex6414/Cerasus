/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusGrowArray.cpp
* @brief	This File is CreasusGrowArray Header File.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "CerasusGrowArray.h"

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::SetSizeInternal(int nNewMaxSize)
{
	if (nNewMaxSize < 0 || (nNewMaxSize > INT_MAX / sizeof(TYPE)))
	{
		assert(false);
		return E_INVALIDARG;
	}

	if (nNewMaxSize == 0)
	{
		// Shrink to 0 size & cleanup
		if (m_pData)
		{
			free(m_pData);
			m_pData = NULL;
		}

		m_nMaxSize = 0;
		m_nSize = 0;
	}
	else if (m_pData == NULL || nNewMaxSize > m_nMaxSize)
	{
		// Grow array
		int nGrowBy = (m_nMaxSize == 0) ? 16 : m_nMaxSize;

		// Limit nGrowBy to keep m_nMaxSize less than INT_MAX
		if ((UINT)m_nMaxSize + (UINT)nGrowBy > (UINT)INT_MAX)
			nGrowBy = INT_MAX - m_nMaxSize;

		nNewMaxSize = __max(nNewMaxSize, m_nMaxSize + nGrowBy);

		// Verify that (nNewMaxSize * sizeof(TYPE)) is not greater than UINT_MAX or the realloc will overrun
		if (sizeof(TYPE) > UINT_MAX / (UINT)nNewMaxSize)
			return E_INVALIDARG;

		TYPE* pDataNew = (TYPE*)realloc(m_pData, nNewMaxSize * sizeof(TYPE));
		if (pDataNew == NULL)
			return E_OUTOFMEMORY;

		m_pData = pDataNew;
		m_nMaxSize = nNewMaxSize;
	}

	return S_OK;
}

template<typename TYPE>
inline CGrowableArray<TYPE>::CGrowableArray()
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
}

template<typename TYPE>
CGrowableArray<TYPE>::CGrowableArray(const CGrowableArray<TYPE>& a)
{
	for (int i = 0; i < a.m_nSize; i++)
	{
		Add(a.m_pData[i]);
	}

}

template<typename TYPE>
CGrowableArray<TYPE>::~CGrowableArray()
{
	RemoveAll();
}

template<typename TYPE>
const TYPE & CGrowableArray<TYPE>::operator[](int nIndex) const
{
	return GetAt(nIndex);
}

template<typename TYPE>
TYPE & CGrowableArray<TYPE>::operator[](int nIndex)
{
	return GetAt(nIndex);
}

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::SetSize(int nNewMaxSize)
{
	int nOldSize = m_nSize;

	if (nOldSize > nNewMaxSize)
	{
		assert(m_pData);
		if (m_pData)
		{
			// Removing elements. Call dtor.

			for (int i = nNewMaxSize; i < nOldSize; ++i)
				m_pData[i].~TYPE();
		}
	}

	// Adjust buffer.  Note that there's no need to check for error
	// since if it happens, nOldSize == nNewMaxSize will be true.)
	HRESULT hr = SetSizeInternal(nNewMaxSize);

	if (nOldSize < nNewMaxSize)
	{
		assert(m_pData);
		if (m_pData)
		{
			// Adding elements. Call ctor.

			for (int i = nOldSize; i < nNewMaxSize; ++i)
				::new (&m_pData[i]) TYPE;
		}
	}

	return hr;
}

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::Add(const TYPE & value)
{
	HRESULT hr;
	if (FAILED(hr = SetSizeInternal(m_nSize + 1)))
		return hr;

	assert(m_pData != NULL);

	// Construct the new element
	::new (&m_pData[m_nSize]) TYPE;

	// Assign
	m_pData[m_nSize] = value;
	++m_nSize;

	return S_OK;
}

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::Insert(int nIndex, const TYPE & value)
{
	HRESULT hr;

	// Validate index
	if (nIndex < 0 ||
		nIndex > m_nSize)
	{
		assert(false);
		return E_INVALIDARG;
	}

	// Prepare the buffer
	if (FAILED(hr = SetSizeInternal(m_nSize + 1)))
		return hr;

	// Shift the array
	MoveMemory(&m_pData[nIndex + 1], &m_pData[nIndex], sizeof(TYPE) * (m_nSize - nIndex));

	// Construct the new element
	::new (&m_pData[nIndex]) TYPE;

	// Set the value and increase the size
	m_pData[nIndex] = value;
	++m_nSize;

	return S_OK;
}

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::SetAt(int nIndex, const TYPE & value)
{
	// Validate arguments
	if (nIndex < 0 ||
		nIndex >= m_nSize)
	{
		assert(false);
		return E_INVALIDARG;
	}

	m_pData[nIndex] = value;
	return S_OK;
}

template<typename TYPE>
TYPE & CGrowableArray<TYPE>::GetAt(int nIndex) const
{
	assert(nIndex >= 0 && nIndex < m_nSize); return m_pData[nIndex];
}

template<typename TYPE>
int CGrowableArray<TYPE>::GetSize() const
{
	return m_nSize;
}

template<typename TYPE>
TYPE * CGrowableArray<TYPE>::GetData()
{
	return m_pData;
}

template<typename TYPE>
bool CGrowableArray<TYPE>::Contains(const TYPE & value)
{
	return (-1 != IndexOf(value));
}

template<typename TYPE>
int CGrowableArray<TYPE>::IndexOf(const TYPE & value)
{
	return (m_nSize > 0) ? IndexOf(value, 0, m_nSize) : -1;
}

template<typename TYPE>
int CGrowableArray<TYPE>::IndexOf(const TYPE & value, int iStart)
{
	return IndexOf(value, iStart, m_nSize - iStart);
}

template<typename TYPE>
int CGrowableArray<TYPE>::IndexOf(const TYPE& value, int iStart, int nNumElements)
{
	// Validate arguments
	if (iStart < 0 ||
		iStart >= m_nSize ||
		nNumElements < 0 ||
		iStart + nNumElements > m_nSize)
	{
		assert(false);
		return -1;
	}

	// Search
	for (int i = iStart; i < (iStart + nNumElements); i++)
	{
		if (value == m_pData[i])
			return i;
	}

	// Not found
	return -1;
}

template<typename TYPE>
int CGrowableArray<TYPE>::LastIndexOf(const TYPE & value)
{
	return (m_nSize > 0) ? LastIndexOf(value, m_nSize - 1, m_nSize) : -1;
}

template<typename TYPE>
int CGrowableArray<TYPE>::LastIndexOf(const TYPE & value, int nIndex)
{
	return LastIndexOf(value, nIndex, nIndex + 1);
}

template<typename TYPE>
int CGrowableArray<TYPE>::LastIndexOf(const TYPE& value, int iEnd, int nNumElements)
{
	// Validate arguments
	if (iEnd < 0 ||
		iEnd >= m_nSize ||
		nNumElements < 0 ||
		iEnd - nNumElements < 0)
	{
		assert(false);
		return -1;
	}

	// Search
	for (int i = iEnd; i > (iEnd - nNumElements); i--)
	{
		if (value == m_pData[i])
			return i;
	}

	// Not found
	return -1;
}

template<typename TYPE>
HRESULT CGrowableArray<TYPE>::Remove(int nIndex)
{
	if (nIndex < 0 ||
		nIndex >= m_nSize)
	{
		assert(false);
		return E_INVALIDARG;
	}

	// Destruct the element to be removed
	m_pData[nIndex].~TYPE();

	// Compact the array and decrease the size
	MoveMemory(&m_pData[nIndex], &m_pData[nIndex + 1], sizeof(TYPE) * (m_nSize - (nIndex + 1)));
	--m_nSize;

	return S_OK;
}

template<typename TYPE>
void CGrowableArray<TYPE>::RemoveAll()
{
	SetSize(0);
}

template<typename TYPE>
void CGrowableArray<TYPE>::Reset()
{
	m_nSize = 0;
}


