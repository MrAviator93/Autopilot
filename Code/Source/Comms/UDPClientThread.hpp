/***********************************************************************
FILE UDPCLIENTTHREAD.HPP CONTAINS UDP CLIENT THREAD IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (16.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_COMMS_UDP_CLIENT_THREAD_HPP__
#define ATL_CORE_COMMS_UDP_CLIENT_THREAD_HPP__

#include "UDPMessage.hpp"
#include <NonCopyableMovable.hpp>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>

// #include <boost/bind.hpp>
// #include <boost/asio/ip/udp.hpp>
// #include <boost/asio/io_service.hpp>
// #include <boost/asio/deadline_timer.hpp>
// #include <boost/date_time/posix_time/posix_time_types.hpp>

#include <thread>
#include <atomic>
#include <string>

namespace ATL::Core::Comms
{
//-----------------------------------------------------------------------
// UDP CLIENT THREAD
//
// Check how to implement deadline receive
// https://www.boost.org/doc/libs/1_51_0/doc/html/boost_asio/example/timeouts/blocking_udp_client.cpp
//-----------------------------------------------------------------------

class CUDPClientThread : Templates::CNonCopyableMovable
{
public:
	explicit CUDPClientThread( std::string rawServerIP,
							   std::uint16_t serverPortNo,
							   UDPMessageQueue& inputMsgQueue,
							   UDPMessageQueue& outputMsgQueue );

	void start() noexcept( false );

	void terminate();

	void join();

private:
	void startThread() noexcept( false );

	static void handleReceive( const boost::system::error_code& errCode,
							   std::size_t length,
							   boost::system::error_code* pOutError,
							   std::size_t* pOutLength );

	void checkDeadline();

	std::size_t receive( const boost::asio::mutable_buffer& buffer,
						 boost::posix_time::time_duration timeout,
						 boost::system::error_code& errCode );

	boost::asio::io_service m_io_service;
	boost::asio::deadline_timer m_deadline;
	std::unique_ptr< boost::asio::ip::udp::socket > m_pSocket { nullptr };
	std::unique_ptr< std::thread > m_clientThread { nullptr };

	std::string m_rawServerIP {};
	std::uint16_t m_serverPort {};

	std::atomic_bool m_initialized { false };

	UDPMessageQueue& m_inputMsgQueue;
	UDPMessageQueue& m_outputMsgQueue;
};

} // namespace ATL::Core::Comms
#endif // ATL_CORE_COMMS_UDP_CLIENT_THREAD_HPP__
