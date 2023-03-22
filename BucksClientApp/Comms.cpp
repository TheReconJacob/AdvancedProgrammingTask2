#include "Comms.h"
#include <ws2tcpip.h>
#include <tchar.h>

void Comms::ServiceSetup()
{
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
}