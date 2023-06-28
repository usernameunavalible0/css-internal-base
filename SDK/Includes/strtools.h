#pragma once
#include "const.h"

typedef wchar_t uchar16;
typedef unsigned int uchar32;

// Unicode string conversion policies - what to do if an illegal sequence is encountered
enum EStringConvertErrorPolicy
{
	_STRINGCONVERTFLAG_SKIP = 1,
	_STRINGCONVERTFLAG_FAIL = 2,
	_STRINGCONVERTFLAG_ASSERT = 4,

	STRINGCONVERT_REPLACE = 0,
	STRINGCONVERT_SKIP = _STRINGCONVERTFLAG_SKIP,
	STRINGCONVERT_FAIL = _STRINGCONVERTFLAG_FAIL,

	STRINGCONVERT_ASSERT_REPLACE = _STRINGCONVERTFLAG_ASSERT + STRINGCONVERT_REPLACE,
	STRINGCONVERT_ASSERT_SKIP = _STRINGCONVERTFLAG_ASSERT + STRINGCONVERT_SKIP,
	STRINGCONVERT_ASSERT_FAIL = _STRINGCONVERTFLAG_ASSERT + STRINGCONVERT_FAIL,
};

// A generic Unicode processing loop: decode one character from input to uchar32, handle errors, encode uchar32 to output
template < typename SrcType, typename DstType, bool bStopAtNull, int(&DecodeSrc)(const SrcType*, uchar32&, bool&), int(&EncodeDstLen)(uchar32), int(&EncodeDst)(uchar32, DstType*) >
inline int Q_UnicodeConvertT(const SrcType* pIn, int nInChars, DstType* pOut, int nOutBytes, EStringConvertErrorPolicy ePolicy)
{
	if (!pIn)
	{
		return 0;
	}

	int nOut = 0;

	if (!pOut)
	{
		while (bStopAtNull ? (*pIn) : (nInChars-- > 0))
		{
			uchar32 uVal;
			// Initialize in order to avoid /analyze warnings.
			bool bErr = false;
			pIn += DecodeSrc(pIn, uVal, bErr);
			nOut += EncodeDstLen(uVal);
			if (bErr)
			{
				if (ePolicy & _STRINGCONVERTFLAG_SKIP)
				{
					nOut -= EncodeDstLen(uVal);
				}
				else if (ePolicy & _STRINGCONVERTFLAG_FAIL)
				{
					pOut[0] = 0;
					return 0;
				}
			}
		}
	}
	else
	{
		int nOutElems = nOutBytes / sizeof(DstType);
		if (nOutElems <= 0)
			return 0;

		int nMaxOut = nOutElems - 1;
		while (bStopAtNull ? (*pIn) : (nInChars-- > 0))
		{
			uchar32 uVal;
			// Initialize in order to avoid /analyze warnings.
			bool bErr = false;
			pIn += DecodeSrc(pIn, uVal, bErr);
			if (nOut + EncodeDstLen(uVal) > nMaxOut)
				break;
			nOut += EncodeDst(uVal, pOut + nOut);
			if (bErr)
			{
				if (ePolicy & _STRINGCONVERTFLAG_SKIP)
				{
					nOut -= EncodeDstLen(uVal);
				}
				else if (ePolicy & _STRINGCONVERTFLAG_FAIL)
				{
					pOut[0] = 0;
					return 0;
				}
			}
		}
		pOut[nOut] = 0;
	}

	return (nOut + 1) * sizeof(DstType);
}

//-----------------------------------------------------------------------------
// Purpose: determine if a uchar32 represents a valid Unicode code point
//-----------------------------------------------------------------------------
inline bool Q_IsValidUChar32(uchar32 uVal)
{
	// Values > 0x10FFFF are explicitly invalid; ditto for UTF-16 surrogate halves,
	// values ending in FFFE or FFFF, or values in the 0x00FDD0-0x00FDEF reserved range
	return (uVal < 0x110000u) && ((uVal - 0x00D800u) > 0x7FFu) && ((uVal & 0xFFFFu) < 0xFFFEu) && ((uVal - 0x00FDD0u) > 0x1Fu);
}

// Decode one character from a UTF-8 encoded string. Treats 6-byte CESU-8 sequences
// as a single character, as if they were a correctly-encoded 4-byte UTF-8 sequence.
inline int Q_UTF8ToUChar32(const char* pUTF8_, uchar32& uValueOut, bool& bErrorOut)
{
	const unsigned char* pUTF8 = (const unsigned char*)pUTF8_;

	int nBytes = 1;
	unsigned __int32 uValue = pUTF8[0];
	unsigned __int32 uMinValue = 0;

	// 0....... single byte
	if (uValue < 0x80)
		goto decodeFinishedNoCheck;

	// Expecting at least a two-byte sequence with 0xC0 <= first <= 0xF7 (110...... and 11110...)
	if ((uValue - 0xC0u) > 0x37u || (pUTF8[1] & 0xC0) != 0x80)
		goto decodeError;

	uValue = (uValue << 6) - (0xC0 << 6) + pUTF8[1] - 0x80;
	nBytes = 2;
	uMinValue = 0x80;

	// 110..... two-byte lead byte
	if (!(uValue & (0x20 << 6)))
		goto decodeFinished;

	// Expecting at least a three-byte sequence
	if ((pUTF8[2] & 0xC0) != 0x80)
		goto decodeError;

	uValue = (uValue << 6) - (0x20 << 12) + pUTF8[2] - 0x80;
	nBytes = 3;
	uMinValue = 0x800;

	// 1110.... three-byte lead byte
	if (!(uValue & (0x10 << 12)))
		goto decodeFinishedMaybeCESU8;

	// Expecting a four-byte sequence, longest permissible in UTF-8
	if ((pUTF8[3] & 0xC0) != 0x80)
		goto decodeError;

	uValue = (uValue << 6) - (0x10 << 18) + pUTF8[3] - 0x80;
	nBytes = 4;
	uMinValue = 0x10000;

	// 11110... four-byte lead byte. fall through to finished.

decodeFinished:
	if (uValue >= uMinValue && Q_IsValidUChar32(uValue))
	{
	decodeFinishedNoCheck:
		uValueOut = uValue;
		bErrorOut = false;
		return nBytes;
	}
decodeError:
	uValueOut = '?';
	bErrorOut = true;
	return nBytes;

decodeFinishedMaybeCESU8:
	// Do we have a full UTF-16 surrogate pair that's been UTF-8 encoded afterwards?
	// That is, do we have 0xD800-0xDBFF followed by 0xDC00-0xDFFF? If so, decode it all.
	if ((uValue - 0xD800u) < 0x400u && pUTF8[3] == 0xED && (unsigned char)(pUTF8[4] - 0xB0) < 0x10 && (pUTF8[5] & 0xC0) == 0x80)
	{
		uValue = 0x10000 + ((uValue - 0xD800u) << 10) + ((unsigned char)(pUTF8[4] - 0xB0) << 6) + pUTF8[5] - 0x80;
		nBytes = 6;
		uMinValue = 0x10000;
	}
	goto decodeFinished;
}

//-----------------------------------------------------------------------------
// Purpose: return number of UTF-16 elements required to encode a Unicode code point
//-----------------------------------------------------------------------------
inline int Q_UChar32ToUTF16Len(uchar32 uVal)
{
	//DbgAssert(Q_IsValidUChar32(uVal));
	if (uVal <= 0xFFFF)
		return 1;
	return 2;
}

//-----------------------------------------------------------------------------
// Purpose: encode Unicode code point as UTF-16, returns number of elements written
//-----------------------------------------------------------------------------
inline int Q_UChar32ToUTF16(uchar32 uVal, uchar16* pUTF16Out)
{
	//DbgAssert(Q_IsValidUChar32(uVal));

	if (uVal <= 0xFFFF)
	{
		pUTF16Out[0] = (uchar16)uVal;
		return 1;
	}

	uVal -= 0x010000;
	pUTF16Out[0] = (uchar16)(uVal >> 10) | 0xD800;
	pUTF16Out[1] = (uchar16)(uVal & 0x3FF) | 0xDC00;

	return 2;
}

//-----------------------------------------------------------------------------
// Purpose: Perform conversion. Returns number of *bytes* required if output pointer is NULL.
//-----------------------------------------------------------------------------
inline int Q_UTF8ToUTF16(const char* pUTF8, uchar16* pUTF16, int cubDestSizeInBytes, EStringConvertErrorPolicy ePolicy = STRINGCONVERT_ASSERT_REPLACE)
{
	return Q_UnicodeConvertT< char, uchar16, true, Q_UTF8ToUChar32, Q_UChar32ToUTF16Len, Q_UChar32ToUTF16 >(pUTF8, 0, pUTF16, cubDestSizeInBytes, ePolicy);
}