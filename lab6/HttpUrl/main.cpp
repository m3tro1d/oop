#include "CHttpUrl.h"
#include <iostream>

void PrintUrlInfo(std::ostream& output, CHttpUrl const& url);

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintUrlInfo(std::cout, url);
		}
		catch (CUrlParsingError const& e)
		{
			std::cerr << e.what() << '\n';
		}
		catch (std::runtime_error const& e)
		{
			std::cerr << "impl: " << e.what() << '\n';
		}
	}

	return EXIT_SUCCESS;
}

void PrintUrlInfo(std::ostream& output, CHttpUrl const& url)
{
	output << "URL: " << url.GetUrl() << '\n'
		   << "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << '\n'
		   << "Domain: " << url.GetDomain() << '\n'
		   << "Port: " << url.GetPort() << '\n'
		   << "Document: " << url.GetDocument() << '\n';
}
