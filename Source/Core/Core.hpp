/***********************************************************************
FILE CORE.H CONTAINS CORE - PLATFORM SPECIFIC DEFINITIONS

FILE UTMOST REVIEW DONE ON (08.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_HPP
#define ATL_CORE_HPP

#define ENABLE_DOUBLE_PRECISION_FLOATING_POINT

namespace atl
{
	typedef char				int8;
	typedef short				int16;
	typedef int					int32;
	typedef long long			int64;				// Eight Byte Integer

	typedef unsigned char		uchar, byte, uint8; // Unsigned char, also known as byte
	typedef unsigned short		uint16;				// Two Byte Unsigned Integer
	typedef unsigned int		uint32;				// Four Byte Unsigned Integer
	typedef unsigned long long	uint64;				// Eight Byte Unsigned Integer


#ifdef ENABLE_DOUBLE_PRECISION_FLOATING_POINT
	using scalar = double;
#else
	using scalar = float;
#endif

#define UNUSED(x) (void)(x)

#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)
#define FORCE_INLINE inline
#define ATTRIBUTE_ALIGNED16
#define ATTRIBUTE_ALIGNED32
#define ATTRIBUTE_ALIGNED64
#define ATTRIBUTE_ALIGNED128
#else
#pragma warning(disable : 4324)
#define FORCE_INLINE __forceinline
#define ATTRIBUTE_ALIGNED16 __declspec(align(16))
#define ATTRIBUTE_ALIGNED32 __declspec(align(32))
#define ATTRIBUTE_ALIGNED64 __declspec(align(64))
#define ATTRIBUTE_ALIGNED128 __declspec (align(128))
#endif

} // namespace atl
#endif // !ATL_CORE_HPP