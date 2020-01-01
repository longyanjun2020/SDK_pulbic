//==============================================================================
//
//  File        : AHC_Version.c
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define FW_VERSION_MAJOR            0x0001
#define FW_VERSION_MEDIUM           0x0020
#define FW_VERSION_MINOR            0x0023
#define FW_VERSION_TEST             0x0000
#define FW_VERSION_BRANCH           2    // SZ Version. //decimal number

#ifdef CUS_FW_VERSION_RELEASE_NAME
#define FW_VERSION_RELEASE_NAME  CUS_FW_VERSION_RELEASE_NAME
#else
#define FW_VERSION_RELEASE_NAME     "MV5_CarDV_SDK"
#endif
#define FW_STANDALONE_BASE          1

/*===========================================================================
 * Main body
 *===========================================================================*/

int AHC_GetMinorVersion(void)
{
    return FW_VERSION_MINOR;
}

void AHC_GetFwVersion( unsigned short* puwFwMajorVersion,
                       unsigned short* puwFwMediumVersion, 
                       unsigned short* puwFwMinorVersion, 
                       unsigned short* puwFwBranchVersion, 
                       unsigned short* puwFwTestVersion, 
                       char**          pszReleaseName)
{
    if (puwFwMajorVersion)
        *puwFwMajorVersion  = FW_VERSION_MAJOR;
    if (puwFwMediumVersion)
        *puwFwMediumVersion = FW_VERSION_MEDIUM;
    if (puwFwMinorVersion)
        *puwFwMinorVersion  = FW_VERSION_MINOR;
    if (puwFwBranchVersion)
        *puwFwBranchVersion = FW_VERSION_BRANCH;
    if (puwFwTestVersion)
        *puwFwTestVersion   = FW_VERSION_TEST;
    if (pszReleaseName)
        *pszReleaseName     = FW_VERSION_RELEASE_NAME;
}
