#include "UDPClientThread.hpp"

#include <boost/bind.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <ostream>
#include <iostream>

namespace ATL::Core::Comms
{

CUDPClientThread::CUDPClientThread( std::string rawServerIP,
									std::uint16_t serverPortNo,
									UDPMessageQueue& inputMsgQueue,
									UDPMessageQueue& outputMsgQueue )
	: m_rawServerIP { rawServerIP }
	, m_serverPort { serverPortNo }
	, m_inputMsgQueue { inputMsgQueue }
	, m_outputMsgQueue { outputMsgQueue }
	, m_deadline { m_io_service }
{ }

void CUDPClientThread::start() noexcept( false )
{
	if( !m_clientThread )
	{
		m_initialized = true;
		m_clientThread = std::make_unique< std::thread >( [ & ] { startThread(); } );
	}
}

void CUDPClientThread::terminate()
{
	m_initialized = false;
}

void CUDPClientThread::join()
{
	if( m_clientThread )
	{
		if( m_clientThread->joinable() )
		{
			m_clientThread->join();
		}
	}
}

using RCV_TIMEOUT_OPTION = boost::asio::detail::socket_option::integer< SOL_SOCKET, SO_RCVTIMEO >;

void CUDPClientThread::startThread()
{
	// This is servers ip address
	auto ipAddress = boost::asio::ip::address::from_string( "127.0.0.1" );

	boost::asio::ip::udp::endpoint ep { ipAddress, m_serverPort };

	m_pSocket = std::make_unique< boost::asio::ip::udp::socket >( boost::asio::ip::udp::socket { m_io_service, ep } );

	// Stores info about error
	boost::system::error_code err {};

	if( err.value() != 0 )
	{
		std::ostringstream oss;
		oss << "Error occured when opening the socket with error: ";
		oss << err.value() << " ";
		oss << err.message();

		throw std::logic_error( oss.str() );
	}

	// No deadline is required until the first socket operation is started. We
	// set the deadline to positive infinity so that the actor takes no action
	// until a specific deadline is set.
	m_deadline.expires_at( boost::posix_time::pos_infin );

	// Start the persistent actor that checks for deadline expiry.
	checkDeadline();

	while( m_initialized )
	{
		std::cout << "UDP Thread udpate()" << std::endl;

		if( !m_initialized )
		{
			break;
		}

		// Timeout needs to be added, this halts/freezes the software
		// https://lists.boost.org/Archives/boost/2007/04/120339.php
		//auto bytes_received = socket.receive_from( boost::asio::buffer( response ), ep);

		char data[ 512 ];
		boost::system::error_code err;
		std::size_t bytes_received = receive( boost::asio::buffer( data ), boost::posix_time::microseconds( 10 ), err );

		bool actionsPerformed = false;
		if( bytes_received > 0 )
		{
			// If any messages received push them into the readMessageQueue
			actionsPerformed = true;
		}

		if( !m_outputMsgQueue.empty() )
		{
			// ****** TODO: If there any messages to write it's time to send them
			//socket.send_to(boost::asio::buffer(response), ep);
			actionsPerformed = true;
		}

		if( !actionsPerformed )
		{
			// If no actions performed sleep for 10ms
			std::this_thread::sleep_for( std::chrono::microseconds( 100 ) );
		}
	}

	// Shut down everything
	// m_pSocket->shutdown( boost::asio::ip::udp::socket::shutdown_both );
}

void CUDPClientThread::handleReceive( const boost::system::error_code& errCode,
									  std::size_t length,
									  boost::system::error_code* pOutError,
									  std::size_t* pOutLength )
{
	*pOutError = errCode;
	*pOutLength = length;
}

void CUDPClientThread::checkDeadline()
{
	if( !m_pSocket )
	{
		return;
	}

	// Check whether the deadline has passed. We compare the deadline against
	// the current time since a new asynchronous operation may have moved the
	// deadline before this actor had a chance to run.
	if( m_deadline.expires_at() <= boost::asio::deadline_timer::traits_type::now() )
	{
		// The deadline has passed. The outstanding asynchronous operation needs
		// to be cancelled so that the blocked receive() function will return.
		//
		// Please note that cancel() has portability issues on some versions of
		// Microsoft Windows, and it may be necessary to use close() instead.
		// Consult the documentation for cancel() for further information.
		m_pSocket->cancel();

		// There is no longer an active deadline. The expiry is set to positive
		// infinity so that the actor takes no action until a new deadline is set.
		m_deadline.expires_at( boost::posix_time::pos_infin );
	}

	// Put the actor back to sleep.
	//m_deadline.async_wait( [ & ] { checkDeadline(); } );
	m_deadline.async_wait( boost::bind( &CUDPClientThread::checkDeadline, this ) );
}

std::size_t CUDPClientThread::receive( const boost::asio::mutable_buffer& buffer,
									   boost::posix_time::time_duration timeout,
									   boost::system::error_code& errCode )
{
	// Set a deadline for the asynchronous operation.
	m_deadline.expires_from_now( timeout );

	// Set up the variables that receive the result of the asynchronous
	// operation. The error code is set to would_block to signal that the
	// operation is incomplete. Asio guarantees that its asynchronous
	// operations will never fail with would_block, so any other value in
	// ec indicates completion.
	errCode = boost::asio::error::would_block;
	std::size_t length = 0;

	// Start the asynchronous operation itself. The handle_receive function
	// used as a callback will update the ec and length variables.
	m_pSocket->async_receive( boost::asio::buffer( buffer ),
							  boost::bind( &CUDPClientThread::handleReceive, _1, _2, &errCode, &length ) );

	// Block until the asynchronous operation has completed.
	do
	{
		m_io_service.run_one();
	} while( errCode == boost::asio::error::would_block );

	return length;
}

} // namespace ATL::Core::Comms
