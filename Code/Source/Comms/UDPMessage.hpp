/***********************************************************************
FILE UDPMESSAGE.HPP CONTAINS GENERAL UDP MESSAGE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (16.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_COMMS_UDP_MESSAGE_HPP__
#define ATL_CORE_COMMS_UDP_MESSAGE_HPP__

#include <MtQueue.hpp>

#include <array>
#include <memory>

namespace ATL::Core::Comms
{
//-----------------------------------------------------------------------
// UDP MESSAGE
//
// TBW
// TODO Rename to UDPMessageBase
//-----------------------------------------------------------------------

class CUDPMessage
{
public:
	CUDPMessage()
		: m_data {}
	{ }

	~CUDPMessage() = default;

private:
	std::array< std::uint8_t, 512 > m_data;
};

static_assert( sizeof( CUDPMessage ) == 512, "The size of CUDPMessage must be of 256 bytes." );

using UDPMessageQueue = Common::CMtQueue< std::unique_ptr< CUDPMessage > >;

} // namespace ATL::Core::Comms
#endif // ATL_CORE_COMMS_UDP_MESSAGE_HPP__
