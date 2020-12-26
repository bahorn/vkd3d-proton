#include <stdio.h>

#include "GFSDK_Aftermath_GpuCrashDump.h"
#include "GFSDK_Aftermath_Defines.h"

#define LOG(x) printf("[!] %s\n", x)
#define LOG_S(x, y) printf("[!] %s %s\n", x, y)

/* Our Callback for handling GPU crashes */
void
crash_callback(const void* pGpuCrashDump, const uint32_t gpuCrashDumpSize, void* pUserData)
{
    /* Write out the crash dump to disk, it can be decoded later with better
     * tools */
    FILE *f;
    char *fname = tmpnam(NULL);
    LOG_S("GPU CRASH DETECTED, written to", fname);
    f = fopen(fname, "w+");
    fwrite(pGpuCrashDump, gpuCrashDumpSize, 1, f);
    fclose(f);
}

/* Setup NV Aftermath, so we can take crash dumps.
 * This needs to be called before any calls.
 */
void
enable_aftermath()
{
    // Should check if the extension is supported here?
    LOG("Aftermath Enabled");
    // Enable the crash dumps here
    GFSDK_Aftermath_EnableGpuCrashDumps(
        GFSDK_Aftermath_Version_API, // defined in GFSDK_Aftermath_Defines.h
        GFSDK_Aftermath_GpuCrashDumpWatchedApiFlags_Vulkan,
        GFSDK_Aftermath_GpuCrashDumpFeatureFlags_Default, // could enable defer, if wanted.
        &crash_callback,
        NULL,
        NULL,
        NULL // Maybe make this include vkd3d version info?
    );
}


/* Setup the vulkan flags for a device to collect the data we want. */
void
setup_aftermath_device()
{
    LOG("Configuring Aftermath Device");

}

/* Disable NV Aftermath */
void
disable_aftermath()
{
    LOG("Aftermath Disabled");
    GFSDK_Aftermath_DisableGpuCrashDumps();
}
