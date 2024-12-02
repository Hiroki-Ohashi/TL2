#pragma once
#include <string>
#include <WinNls.h>
#include <stringapiset.h>

// テクスチャコンバーター
class TextureConverter {
public:
	// テクスチャDDSに変換する
	void ConverTextureWICToDDS(const std::string& filePath);

private:
	// テクスチャファイル読み込み
	void LoadWICTextureFromFile(const std::string& filePath);
	// マルチバイト文字列をワイド文字列に変換
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
};
