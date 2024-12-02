#pragma once
#include <string>
#include <windows.h>
#include "externals/DirectXTex/DirectXTex.h"

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
	// フォルダパスとフォルダ名を分離
	void SeparateFilePath(const std::wstring& filepath);
	// DDSテクスチャとしてファイル書き出し
	void SaveDDSTextureToFile();
private:
	// 画像情報
	DirectX::TexMetadata metadata_;
	// 画像のイメージコンテナ
	DirectX::ScratchImage scratchImage_;

	// ディレクトリパス
	std::wstring directoryPath_;
	// ファイル名
	std::wstring fileName_;
	// ファイル拡張子
	std::wstring fileExt_;
};
