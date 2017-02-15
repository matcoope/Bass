#include "bass.h"

extern void BASSFLACplugin, BASSWVplugin, BASS_APEplugin, BASS_MPCplugin, BASSOPUSplugin;

void BASS_LoadPlugins() {
    BASS_PluginLoad(&BASSFLACplugin, 0);
    BASS_PluginLoad(&BASSOPUSplugin, 0);
    
    BASS_PluginLoad(&BASSWVplugin, 0);   // WavePack
    BASS_PluginLoad(&BASS_APEplugin, 0); // Monkey's Audio
    BASS_PluginLoad(&BASS_MPCplugin, 0); // MusePack
}
