#include <iostream>
#include "cms.h"

int main(int argc, char** argv)
{
	std::cout << "main" << std::endl;

	SECItem item;

	PRFileDesc *sigFileDesc = NULL;
	PRFileInfo sigFileInfo;

	sigFileDesc = PR_Open("../protocolo.p7s", PR_RDONLY, 0);
	if (!sigFileDesc) {
		std::cerr << "Wasn't possible to open the signature file." << std::endl;
		return 0;
	}

	PR_GetOpenFileInfo(sigFileDesc, &sigFileInfo);
	SECITEM_AllocItem(
		NULL, //NO PLArena
		&item,
		sigFileInfo.size
		);

	std::cout << PR_Read(sigFileDesc, item.data, sigFileInfo.size) << std::endl;

	NSSCMSMessage * msg = NULL;
	NSS_CMSMessage_CreateFromDER(&item, NULL, NULL /* Content callback */, NULL, NULL /*Password callback*/, NULL, NULL /*Decrypt callback*/);

	if (NSS_CMSMessage_IsSigned(msg) == PR_FALSE) {
		std::cout << "The CMS isn't a Signature!" << std::cout;
		goto end;
	}

	NSSCMSSignedData * signedData;
	signedData = NSS_CMSSignedData_Create(msg);
	NSSCMSSignerInfo *signerInfo;
	signerInfo = NSS_CMSSignedData_GetSignerInfo(signedData, 0); // we only want to check the first signer
	SECItem *digest;
	SECItem *contentType;

	std::cout << "Status: " << NSS_CMSSignerInfo_Verify(
		signerInfo,
		digest,
		contentType
		) << std::endl;

end:
	NSS_CMSSignedData_Destroy(signedData);
	NSS_CMSMessage_Destroy(msg);
	SECITEM_FreeItem(&item, PR_FALSE);
	return 0;
}