#include <ntifs.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegistryPath)
{
    pDrvObj = pDrvObj;
    pRegistryPath = pRegistryPath;

    ULONG ProcessId = 0x99999999;
    if (ProcessId == 0)
        goto exit;

    PEPROCESS pEprocess = NULL;
    PsLookupProcessByProcessId((HANDLE)ProcessId, &pEprocess);
    if (pEprocess)
        *(unsigned char*)((unsigned char*)pEprocess - 0x15) = 0x14;

    return STATUS_SUCCESS;
exit:
    return STATUS_UNSUCCESSFUL;
}