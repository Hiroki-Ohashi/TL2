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

	// COM���C�u����������
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// �e�N�X�`���R���o�[�^�[
	TextureConverter converter;

	// �e�N�X�`���ϊ�
	converter.ConverTextureWICToDDS(argv[kFilePath]);

	// COM ���C�u�����̏I��
	CoUninitialize();

	system("pause");
	return 0;
}