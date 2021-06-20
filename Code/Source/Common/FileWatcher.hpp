/***********************************************************************
FILE FILEWATCHER.HPP CONTAINS FILE WATCHER

FILE UTMOST REVIEW DONE ON (01.06.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_COMMON_FILE_WATCHER_HPP__
#define ATL_CORE_COMMON_FILE_WATCHER_HPP__

#include <chrono>
#include <string>
#include <filesystem>
#include <functional>
#include <unordered_map>

namespace ATL::Core::Common
{
// Define available file changes
enum class FWFileStatus
{
	CREATED,
	MODIFIED,
	ERASED
};

using FWDelay = std::chrono::duration< int, std::milli >;

//-----------------------------------------------------------------------
// FILE WATCHER
//
// https://solarianprogrammer.com/2019/01/13/cpp-17-filesystem-write-file-watcher-monitor/
//-----------------------------------------------------------------------

class CFileWatcher
{
public:
	CFileWatcher( const std::string& path_to_watch, FWDelay delay );

	// Monitor "path_to_watch" for changes and in case of a change execute the user supplied "action" function
	void start( const std::function< void( std::string, FWFileStatus ) >& action );

private:
	// Check if "paths_" contains a given key
	// If your compiler supports C++20 use paths_.contains(key) instead of this function
	bool contains( const std::string& key );

	std::unordered_map< std::string, std::filesystem::file_time_type > m_paths;
	std::string m_path_to_watch {};

	// Time interval at which we check the base folder for changes
	FWDelay m_delay {};
	bool m_running { true };
};

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_FILE_WATCHER_HPP__
