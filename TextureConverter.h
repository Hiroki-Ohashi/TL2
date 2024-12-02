#pragma once
#include <string>
#include <WinNls.h>
#include <stringapiset.h>

// �e�N�X�`���R���o�[�^�[
class TextureConverter {
public:
	// �e�N�X�`��DDS�ɕϊ�����
	void ConverTextureWICToDDS(const std::string& filePath);

private:
	// �e�N�X�`���t�@�C���ǂݍ���
	void LoadWICTextureFromFile(const std::string& filePath);
	// �}���`�o�C�g����������C�h������ɕϊ�
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
};
