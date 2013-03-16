#pragma once

#include <../ThirdParty/utf8/utf8.h>
#include <Foundation/Strings/UnicodeUtils.h>

// **************** ezStringWChar ****************

inline ezStringWChar::ezStringWChar(ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  m_Data.Push('\0');
}

inline ezStringWChar::ezStringWChar(const char* szUtf8, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf8;
}

inline ezStringWChar::ezStringWChar(const ezUInt16* szUtf16, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf16;
}

inline ezStringWChar::ezStringWChar(const ezUInt32* szUtf32, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf32;
}

inline ezStringWChar::ezStringWChar(const wchar_t* szWChar, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szWChar;
}



// **************** ezStringUtf8 ****************

inline ezStringUtf8::ezStringUtf8(ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  m_Data.Push('\0');
}

inline ezStringUtf8::ezStringUtf8(const char* szUtf8, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf8;
}

inline ezStringUtf8::ezStringUtf8(const ezUInt16* szUtf16, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf16;
}

inline ezStringUtf8::ezStringUtf8(const ezUInt32* szUtf32, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf32;
}

inline ezStringUtf8::ezStringUtf8(const wchar_t* szWChar, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szWChar;
}



// **************** ezStringUtf16 ****************

inline ezStringUtf16::ezStringUtf16(ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  m_Data.Push('\0');
}

inline ezStringUtf16::ezStringUtf16(const char* szUtf8, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf8;
}

inline ezStringUtf16::ezStringUtf16(const ezUInt16* szUtf16, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf16;
}

inline ezStringUtf16::ezStringUtf16(const ezUInt32* szUtf32, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf32;
}

inline ezStringUtf16::ezStringUtf16(const wchar_t* szWChar, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szWChar;
}





// **************** ezStringUtf32 ****************

inline ezStringUtf32::ezStringUtf32(ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  m_Data.Push('\0');
}

inline ezStringUtf32::ezStringUtf32(const char* szUtf8, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf8;
}

inline ezStringUtf32::ezStringUtf32(const ezUInt16* szUtf16, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf16;
}

inline ezStringUtf32::ezStringUtf32(const ezUInt32* szUtf32, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szUtf32;
}

inline ezStringUtf32::ezStringUtf32(const wchar_t* szWChar, ezIAllocator* pAllocator) : 
  m_Data(pAllocator)
{
  *this = szWChar;
}


