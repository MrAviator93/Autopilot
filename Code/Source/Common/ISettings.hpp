/***********************************************************************
FILE ISETTINGS.HPP CONTAINS SETTINGS CLASS INTERFACE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (28.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_COMMON_ISETTINGS_HPP__
#define ATL_CORE_COMMON_ISETTINGS_HPP__

#include <NonCopyableMovable.hpp>

#include <mutex>
#include <string>

namespace pugi
{
class xml_document;
class xml_node;
} //namespace pugi

namespace ATL::Core::Common
{
//-----------------------------------------------------------------------
// SETTINGS CLASS INTERFACE
//
// TBW
//-----------------------------------------------------------------------

class ISettings : Templates::CNonCopyableMovable
{
public:
	explicit ISettings( std::string settingsFileName ) noexcept( true );
	virtual ~ISettings();

protected:
	std::string m_settingsFileName {};

	mutable std::mutex m_mutex;
	pugi::xml_document* m_pXMLFile { nullptr };
};

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_ISETTINGS_HPP__