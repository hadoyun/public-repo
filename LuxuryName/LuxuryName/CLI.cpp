//winsock2.h가 windows.h의 기능을 일부 포함하고 있으나, 전부 포함한 것은 아니므로, windows.h의 다른 함수를 쓰기 위해
//include할 필요가 있을 경우 해당 코드를 사용하여 include하면 오류가 발생하지 않음.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
//windows.h를 Winsock2.h 내부에서 먼저 include함. 따라서 Winsock2.h 이전에 windows.h를 include 할 경우 오류가 발생.
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>

// _setmode로 UTF16용 wcout을 하기 위함.
#include <io.h>
#include <fcntl.h>

const int bufferCount{ 1500 };

int main(int argc, char* argv[])
{
	using byte = unsigned char;
	
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "text") == 0)
		{
			std::wifstream ifs{};

			std::wstring completeBuffer{};

			ifs.open("TestB.txt", std::ios_base::in);

			if (ifs.is_open() == false)
			{
				OutputDebugString(TEXT("[ERROR] File이 Open되지 않았습니다.\n"));

#ifndef _DEBUG
				std::cout << "[ERROR] File이 Open되지 않았습니다.\n";
#endif // _DEBUG

				continue;
			}

			wchar_t buffer[bufferCount]{};

			// BOM 제거 (UTF-16 LE)
			{
				byte BOM[2]{
					static_cast<byte>(ifs.get()),
					static_cast<byte>(ifs.get())
				};
				if (BOM[0] != 0xFF || BOM[1] != 0xFE)
				{
					std::wcout << L"[ERROR] 파일의 문자열 인코딩이 UTF-16 LE 가 아닙니다.\n";
					continue;
				}
			}

			while (!ifs.eof())
			{
				byte lowByte{ static_cast<byte>(ifs.get()) }; // get()은 항상 1바이트를 읽어온다!!!
				byte highByte{ static_cast<byte>(ifs.get()) };
				wchar_t wch{ static_cast<wchar_t>((highByte << 8) | lowByte) };
				completeBuffer += wch;
			}

			// @중요!!! 이걸 호출해야 기본 wide stream의 문자열 인코딩이 UTF-16이 됨!!!!
			_setmode(_fileno(stdout), _O_U16TEXT);

			std::wcout << completeBuffer.c_str();

			// @중요! 문자열 인코딩을 다시 원래대로 되돌린다!
			_setmode(_fileno(stdout), _O_TEXT);

			ifs.close();
		}
		else if (strcmp(argv[i], "net") == 0 || strcmp(argv[i], "n") == 0)
		{
			WSADATA wsaData{};

			WSAStartup(MAKEWORD(2, 2), &wsaData);

			char hostName[256]{};

			gethostname(hostName, 256);

			//무조건 중단점을 걸어주는 함수.
			//DebugBreak();

			ADDRINFOA hint{};
			hint.ai_family = PF_INET;

			ADDRINFOA* result{};

			getaddrinfo(hostName, nullptr, &hint, &result);

			char ip[16]{};

			inet_ntop(AF_INET, result->ai_addr->sa_data + 2, ip, 16);

			freeaddrinfo(result);

			std::cout << "\n\nIP Address : " << ip << "\n";

			std::cout << "Host Name  : " << hostName << "\n";

			WSACleanup();
		}


	}

	return 0;
}