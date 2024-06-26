// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Runtime.InteropServices;

internal static partial class Interop
{
    internal static partial class Sys
    {
        [LibraryImport(Libraries.SystemNative, EntryPoint = "SystemNative_Connect")]
        internal static unsafe partial Error Connect(SafeHandle socket, byte* socketAddress, int socketAddressLen);

        [LibraryImport(Libraries.SystemNative, EntryPoint = "SystemNative_Connectx")]
        internal static unsafe partial Error Connectx(SafeHandle socket, byte* socketAddress, int socketAddressLen, Span<byte> buffer, int bufferLen, int enableTfo, int* sent);
    }
}
