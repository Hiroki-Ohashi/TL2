#include <cstdio>
#include <cstdlib>
#include "TextureConverter.h"
#include <cassert>
#include <combaseapi.h>


enum Argument {
	kApplicationPath,
	kFilePath,

	NumArgument
};

int main(int argc, char* argv[]) {

	assert(argc >= NumArgument);

	// COMライブラリ初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// テクスチャコンバーター
	TextureConverter converter;

	// テクスチャ変換
	converter.ConverTextureWICToDDS(argv[kFilePath]);

	// COM ライブラリの終了
	CoUninitialize();

	system("pause");
	return 0;
}