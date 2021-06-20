#include "SerialPort.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//-----------------------------------------------------------------------
// https://github.com/manashmndl/SerialPort/blob/master/include/SerialPort.h
// https://playground.arduino.cc/Interfacing/CPPWindows
// https://blablacode.ru/programmirovanie/392
// https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c
// https://github.com/manashmndl/SerialPort/blob/master/src/SerialPort.cpp
//-----------------------------------------------------------------------

namespace atl
{
CSerialPort::CSerialPort( const char* pPortName, BoudRate boudRate )
{
	this->m_pHandle = CreateFileA( static_cast< LPCSTR >( pPortName ),
								   GENERIC_READ | GENERIC_WRITE,
								   0,
								   NULL,
								   OPEN_EXISTING,
								   FILE_ATTRIBUTE_NORMAL,
								   NULL );

	if( this->m_pHandle == INVALID_HANDLE_VALUE )
	{
		if( GetLastError() == ERROR_FILE_NOT_FOUND )
		{
			printf( "ERROR: Handle was not attached. Reason: %s not available\n", pPortName );
		}
		else
		{
			printf( "Error!\n" );
		}
	}
	else
	{
		DCB dcbSerialParameters = { 0 };

		if( !GetCommState( this->m_pHandle, &dcbSerialParameters ) )
		{
			printf( "Failed to get current serial parameters." );
		}
		else
		{
			// Baudrate is very important, it must match the micro controllers
			// one, otherwise communication is not going to establish.
			dcbSerialParameters.BaudRate = (DWORD)boudRate; // CBR_256000;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if( !SetCommState( m_pHandle, &dcbSerialParameters ) )
			{
				printf( "ERROR: Could not set Serial port parameters\n" );
			}
			else
			{
				this->m_initialized = true;
				PurgeComm( this->m_pHandle, PURGE_RXCLEAR | PURGE_TXCLEAR );
				Sleep( MAX_ARDUINO_WAIT_TIME_MS );
			}
		}
	}
}

CSerialPort::~CSerialPort()
{
	if( m_initialized )
	{
		CloseHandle( (HANDLE)this->m_pHandle );
		m_initialized = false;
	}
}

int CSerialPort::readSerialPort( void* pBuffer, uint32 bufferSize )
{
	DWORD bytesRead = 0;
	uint32 inBufferSize = 0;
	COMSTAT stat;
	ClearCommError( this->m_pHandle, (DWORD*)&this->m_errors, &stat );

	if( stat.cbInQue > 0 )
	{
		if( stat.cbInQue > bufferSize )
		{
			inBufferSize = bufferSize;
		}
		else
		{
			inBufferSize = stat.cbInQue;
		}
	}

	memset( pBuffer, 0x00, bufferSize );

	if( ReadFile( this->m_pHandle, pBuffer, inBufferSize, &bytesRead, NULL ) )
	{
		return bytesRead;
	}

	return 0;
}

int CSerialPort::readSerialPort( char* pBuffer, uint32 bufferSize )
{
	DWORD bytesRead = 0;
	uint32 inBufferSize = 0;
	COMSTAT stat;
	ClearCommError( this->m_pHandle, (DWORD*)&this->m_errors, &stat );

	if( stat.cbInQue > 0 )
	{
		if( stat.cbInQue > bufferSize )
		{
			inBufferSize = bufferSize;
		}
		else
		{
			inBufferSize = stat.cbInQue;
		}
	}

	memset( pBuffer, 0x00, bufferSize );

	if( ReadFile( this->m_pHandle, pBuffer, inBufferSize, &bytesRead, NULL ) )
	{
		return bytesRead;
	}

	return 0;
}

bool CSerialPort::writeSerialPort( char* pBuffer, uint32 bufferSize )
{
	DWORD bytesSend;

	if( !WriteFile( this->m_pHandle, (void*)pBuffer, bufferSize, &bytesSend, 0 ) )
	{
		ClearCommError( this->m_pHandle, (DWORD*)&this->m_errors, ( LPCOMSTAT ) & this->m_pStatus );
		return false;
	}

	return true;
}

bool CSerialPort::isConnected()
{
	if( !ClearCommError( this->m_pHandle, (DWORD*)&this->m_errors, ( LPCOMSTAT ) & this->m_pStatus ) )
	{
		m_initialized = false;
	}
	return this->m_initialized;
}

} // namespace atl
