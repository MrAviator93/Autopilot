#include "MtCmdQueue.hpp"

namespace ATL::Core::Common
{

std::size_t CMtCmdQueue::size() const noexcept( true )
{
	std::unique_lock< std::mutex > lock { m_mutex };
	return m_commandQueue.size();
}

bool CMtCmdQueue::empty() const noexcept( true )
{
	std::unique_lock< std::mutex > lock { m_mutex };
	return m_commandQueue.empty();
}

void CMtCmdQueue::addCommand( std::function< void() >* command, std::function< bool() >* process )
{
	std::unique_lock< std::mutex > lock { m_mutex };
	m_commandQueue.emplace_back( std::unique_ptr< std::function< void() > >( command ),
								 std::unique_ptr< std::function< bool() > >( process ) );
}

bool CMtCmdQueue::execCommand()
{
	std::pair< std::unique_ptr< std::function< void() > >, std::unique_ptr< std::function< bool() > > > command;

	{
		// This is the critical section which we must lock
		std::unique_lock< std::mutex > lock { m_mutex };

		if( m_commandQueue.empty() )
		{
			return false;
		}

		command = std::move( m_commandQueue.front() );

		if( !( *( command.second ) )() )
		{
			return false;
		}

		m_commandQueue.pop_front();
	}

	try
	{
		( *( command.first ) )();
	}
	catch( ... )
	{ }

	return true;
}

} // namespace ATL::Core::Common
