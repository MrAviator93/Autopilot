#include "FileWatcher.hpp"

#include <thread>

namespace fs = std::filesystem;

namespace ATL::Core::Common
{
CFileWatcher::CFileWatcher( const std::string& path_to_watch, FWDelay delay )
	: m_path_to_watch { path_to_watch }
	, m_delay { delay }
{ }

void CFileWatcher::start( const std::function< void( std::string, FWFileStatus ) >& action )
{
	while( m_running )
	{
		// Wait for "delay" milliseconds
		std::this_thread::sleep_for( m_delay );

		auto it = m_paths.begin();
		while( it != m_paths.end() )
		{
			if( !fs::exists( it->first ) )
			{
				action( it->first, FWFileStatus::ERASED );
				it = m_paths.erase( it );
			}
			else
			{
				it++;
			}
		}

		// Check if a file was created or modified
		for( auto& file : fs::recursive_directory_iterator( m_path_to_watch ) )
		{
			auto current_file_last_write_time = fs::last_write_time( file );

			// File creation
			if( !contains( file.path().string() ) )
			{
				m_paths[ file.path().string() ] = current_file_last_write_time;
				action( file.path().string(), FWFileStatus::CREATED );
				// File modification
			}
			else
			{
				if( m_paths[ file.path().string() ] != current_file_last_write_time )
				{
					m_paths[ file.path().string() ] = current_file_last_write_time;
					action( file.path().string(), FWFileStatus::MODIFIED );
				}
			}
		}
	}
}

bool CFileWatcher::contains( const std::string& key )
{
	auto el = m_paths.find( key );
	return el != m_paths.end();
}

} // namespace ATL::Core::Common