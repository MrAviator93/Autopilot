#include "ISettings.hpp"

#include <pugixml.hpp>

namespace ATL::Core::Common
{

ISettings::ISettings( std::string settingsFileName ) noexcept( true )
	: m_settingsFileName { std::move( settingsFileName ) }
{
	m_pXMLFile = new pugi::xml_document {};
}

ISettings::~ISettings()
{
	delete m_pXMLFile;
}

} // namespace ATL::Core::Common
