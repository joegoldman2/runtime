// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

/*****************************************************************************
 **                                                                         **
 ** bundle.h - Information about applications bundled as a single-file      **
 **                                                                         **
 *****************************************************************************/

#ifndef _BUNDLE_H_
#define _BUNDLE_H_

#include <sstring.h>
#include "coreclrhost.h"

class Bundle;

struct BundleFileLocation
{
    INT64 Size;
    INT64 Offset;
    INT64 UncompressedSize;

    BundleFileLocation()
    {
        LIMITED_METHOD_CONTRACT;

        Size = 0;
        Offset = 0;
        UncompressedSize = 0;
    }

    static BundleFileLocation Invalid() { LIMITED_METHOD_CONTRACT; return BundleFileLocation(); }

    const SString &Path() const;

    bool IsValid() const { LIMITED_METHOD_CONTRACT; return Offset != 0; }
};

class Bundle
{
public:
    Bundle(LPCSTR bundlePath, BundleProbeFn *probe);
    BundleFileLocation Probe(const SString& path, bool pathIsBundleRelative = false) const;

    // Paths do not change and should remain valid for the lifetime of the Bundle
    const SString& Path() const { LIMITED_METHOD_CONTRACT; return m_path; }
    const UTF8* BasePath() const { LIMITED_METHOD_CONTRACT; return m_basePath.GetUTF8(); }

    // Extraction path does not change and should remain valid for the lifetime of the Bundle
    bool HasExtractedFiles() const { LIMITED_METHOD_CONTRACT; return !m_extractionPath.IsEmpty(); }
    const WCHAR* ExtractionPath() const { LIMITED_METHOD_CONTRACT; return m_extractionPath.GetUnicode(); }

    static Bundle* AppBundle; // The BundleInfo for the current app, initialized by coreclr_initialize.
    static bool AppIsBundle() { LIMITED_METHOD_CONTRACT; return AppBundle != nullptr; }
    static BundleFileLocation ProbeAppBundle(const SString& path, bool pathIsBundleRelative = false);

private:
    SString m_path; // The path to single-file executable
    BundleProbeFn *m_probe;
    SString m_extractionPath; // The path to the extraction location, if bundle extracted any files

    SString m_basePath; // The prefix to denote a path within the bundle
    COUNT_T m_basePathLength;
};

#endif // _BUNDLE_H_
