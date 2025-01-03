#include "TextureConverter.h"
#include <stdexcept>
#include <iostream>
using namespace DirectX;

void TextureConverter::ConverTextureWICToDDS(const std::string& filePath)
{
	// テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	// 読み込んだテクスチャをSRGBとして扱う
	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// ファイルパスをワイド文字列に変換
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	// WICテクスチャのロード
	HRESULT result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));

	// フォルダパスとファイル名を分解
	SeparateFilePath(wfilePath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ワイド文字列に変換した際の文字列を計算
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ワイド文字列
	std::wstring wString;
	wString.resize(filePathBufferSize);

	// ワイド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

void TextureConverter::SeparateFilePath(const std::wstring& filepath)
{
	size_t pos1;
	std::wstring exceptExt;

	// 区切り文字'.'が出てくる一番最後の部分検索
	pos1 = filepath.rfind('.');
	// 検索ヒット
	if (pos1 != std::wstring::npos) {
		// 区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filepath.substr(pos1 + 1, filepath.size() - pos1 - 1);
		// 区切り文字の前までを抜き出す
		exceptExt = filepath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filepath;
	}

	// 区切り文字'\\' が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		// 区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// 区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	// 区切り文字'/' が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		// 区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// 区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	// 区切り文字がないのでファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	// 読み込んだテクスチャをSRGBとして扱う
	metadata_.format = MakeSRGB(metadata_.format);

	HRESULT result;
	
	// 出力ファイル名を設定
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	// DDSファイル書き出し
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
