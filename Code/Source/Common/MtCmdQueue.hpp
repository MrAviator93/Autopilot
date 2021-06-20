/***********************************************************************
FILE MTQUEUE.HPP CONTAINS MULTI THREAD SAFE COMMAND QUEUE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (16.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_COMMON_MT_CMD_QUEUE_HPP__
#define ATL_CORE_COMMON_MT_CMD_QUEUE_HPP__

#include <NonCopyableMovable.hpp>

#include <list>
#include <mutex>
#include <memory>
#include <functional>

namespace ATL::Core::Common
{
using CMD_QUEUE_LIST =
	std::list< std::pair< std::unique_ptr< std::function< void() > >, std::unique_ptr< std::function< bool() > > > >;

inline bool alwaysTrue()
{
	return true;
}

//-----------------------------------------------------------------------
// MULTI THREAD SAFE COMMAND QUEUE
//
// TBW
//-----------------------------------------------------------------------

class CMtCmdQueue : Templates::CNonCopyableMovable
{
public:
	CMtCmdQueue()
		: m_mutex {}
		, m_commandQueue {}
	{ }
	virtual ~CMtCmdQueue() = default;

	std::size_t size() const noexcept( true );

	bool empty() const noexcept( true );

	void addCommand( std::function< void() >* command,
					 std::function< bool() >* process = new std::function< bool() >( &alwaysTrue ) );

	bool execCommand();

private:
	mutable std::mutex m_mutex;
	CMD_QUEUE_LIST m_commandQueue;
};

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_MT_CMD_QUEUE_HPP__
