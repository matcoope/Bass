#import <AudioToolbox/AudioToolbox.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <CFNetwork/CFNetwork.h>
#import <Accelerate/Accelerate.h>
#import <CoreMIDI/CoreMIDI.h>

void BASS_LoadPlugins();

/*
	BASS 2.4 C/C++ header file
	Copyright (c) 1999-2014 Un4seen Developments Ltd.
 
	See the BASS.CHM file for more detailed documentation
 */

#ifndef BASS_H
#define BASS_H

#ifdef _WIN32
#include <wtypes.h>
typedef unsigned __int64 QWORD;
#else
#include <stdint.h>
#define WINAPI
#define CALLBACK
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;
#ifndef __OBJC__
typedef int BOOL;
#endif
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#define LOBYTE(a) (BYTE)(a)
#define HIBYTE(a) (BYTE)((a)>>8)
#define LOWORD(a) (WORD)(a)
#define HIWORD(a) (WORD)((a)>>16)
#define MAKEWORD(a,b) (WORD)(((a)&0xff)|((b)<<8))
#define MAKELONG(a,b) (DWORD)(((a)&0xffff)|((b)<<16))
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#define BASSVERSION			0x204	// API version
#define BASSVERSIONTEXT		"2.4"
    
#ifndef BASSDEF
#define BASSDEF(f) WINAPI f
#else
#define NOBASSOVERLOADS
#endif
    
    typedef DWORD HMUSIC;		// MOD music handle
    typedef DWORD HSAMPLE;		// sample handle
    typedef DWORD HCHANNEL;		// playing sample's channel handle
    typedef DWORD HSTREAM;		// sample stream handle
    typedef DWORD HRECORD;		// recording handle
    typedef DWORD HSYNC;		// synchronizer handle
    typedef DWORD HDSP;			// DSP handle
    typedef DWORD HFX;			// DX8 effect handle
    typedef DWORD HPLUGIN;		// Plugin handle
    
    // Error codes returned by BASS_ErrorGetCode
#define BASS_OK				0	// all is OK
#define BASS_ERROR_MEM		1	// memory error
#define BASS_ERROR_FILEOPEN	2	// can't open the file
#define BASS_ERROR_DRIVER	3	// can't find a free/valid driver
#define BASS_ERROR_BUFLOST	4	// the sample buffer was lost
#define BASS_ERROR_HANDLE	5	// invalid handle
#define BASS_ERROR_FORMAT	6	// unsupported sample format
#define BASS_ERROR_POSITION	7	// invalid position
#define BASS_ERROR_INIT		8	// BASS_Init has not been successfully called
#define BASS_ERROR_START	9	// BASS_Start has not been successfully called
#define BASS_ERROR_SSL		10	// SSL/HTTPS support isn't available
#define BASS_ERROR_ALREADY	14	// already initialized/paused/whatever
#define BASS_ERROR_NOCHAN	18	// can't get a free channel
#define BASS_ERROR_ILLTYPE	19	// an illegal type was specified
#define BASS_ERROR_ILLPARAM	20	// an illegal parameter was specified
#define BASS_ERROR_NO3D		21	// no 3D support
#define BASS_ERROR_NOEAX	22	// no EAX support
#define BASS_ERROR_DEVICE	23	// illegal device number
#define BASS_ERROR_NOPLAY	24	// not playing
#define BASS_ERROR_FREQ		25	// illegal sample rate
#define BASS_ERROR_NOTFILE	27	// the stream is not a file stream
#define BASS_ERROR_NOHW		29	// no hardware voices available
#define BASS_ERROR_EMPTY	31	// the MOD music has no sequence data
#define BASS_ERROR_NONET	32	// no internet connection could be opened
#define BASS_ERROR_CREATE	33	// couldn't create the file
#define BASS_ERROR_NOFX		34	// effects are not available
#define BASS_ERROR_NOTAVAIL	37	// requested data is not available
#define BASS_ERROR_DECODE	38	// the channel is/isn't a "decoding channel"
#define BASS_ERROR_DX		39	// a sufficient DirectX version is not installed
#define BASS_ERROR_TIMEOUT	40	// connection timedout
#define BASS_ERROR_FILEFORM	41	// unsupported file format
#define BASS_ERROR_SPEAKER	42	// unavailable speaker
#define BASS_ERROR_VERSION	43	// invalid BASS version (used by add-ons)
#define BASS_ERROR_CODEC	44	// codec is not available/supported
#define BASS_ERROR_ENDED	45	// the channel/file has ended
#define BASS_ERROR_BUSY		46	// the device is busy
#define BASS_ERROR_UNKNOWN	-1	// some other mystery problem
    
    // BASS_SetConfig options
#define BASS_CONFIG_BUFFER			0
#define BASS_CONFIG_UPDATEPERIOD	1
#define BASS_CONFIG_GVOL_SAMPLE		4
#define BASS_CONFIG_GVOL_STREAM		5
#define BASS_CONFIG_GVOL_MUSIC		6
#define BASS_CONFIG_CURVE_VOL		7
#define BASS_CONFIG_CURVE_PAN		8
#define BASS_CONFIG_FLOATDSP		9
#define BASS_CONFIG_3DALGORITHM		10
#define BASS_CONFIG_NET_TIMEOUT		11
#define BASS_CONFIG_NET_BUFFER		12
#define BASS_CONFIG_PAUSE_NOPLAY	13
#define BASS_CONFIG_NET_PREBUF		15
#define BASS_CONFIG_NET_PASSIVE		18
#define BASS_CONFIG_REC_BUFFER		19
#define BASS_CONFIG_NET_PLAYLIST	21
#define BASS_CONFIG_MUSIC_VIRTUAL	22
#define BASS_CONFIG_VERIFY			23
#define BASS_CONFIG_UPDATETHREADS	24
#define BASS_CONFIG_DEV_BUFFER		27
#define BASS_CONFIG_VISTA_TRUEPOS	30
#define BASS_CONFIG_IOS_MIXAUDIO	34
#define BASS_CONFIG_DEV_DEFAULT		36
#define BASS_CONFIG_NET_READTIMEOUT	37
#define BASS_CONFIG_VISTA_SPEAKERS	38
#define BASS_CONFIG_IOS_SPEAKER		39
#define BASS_CONFIG_MF_DISABLE		40
#define BASS_CONFIG_HANDLES			41
#define BASS_CONFIG_UNICODE			42
#define BASS_CONFIG_SRC				43
#define BASS_CONFIG_SRC_SAMPLE		44
#define BASS_CONFIG_ASYNCFILE_BUFFER 45
#define BASS_CONFIG_OGG_PRESCAN		47
#define BASS_CONFIG_MF_VIDEO		48
#define BASS_CONFIG_AIRPLAY			49
#define BASS_CONFIG_DEV_NONSTOP		50
#define BASS_CONFIG_IOS_NOCATEGORY	51
#define BASS_CONFIG_VERIFY_NET		52
#define BASS_CONFIG_DEV_PERIOD		53
#define BASS_CONFIG_FLOAT			54
#define BASS_CONFIG_NET_SEEK		56
    
    // BASS_SetConfigPtr options
#define BASS_CONFIG_NET_AGENT		16
#define BASS_CONFIG_NET_PROXY		17
#define BASS_CONFIG_IOS_NOTIFY		46
    
    // BASS_Init flags
#define BASS_DEVICE_8BITS		1		// 8 bit
#define BASS_DEVICE_MONO		2		// mono
#define BASS_DEVICE_3D			4		// enable 3D functionality
#define BASS_DEVICE_16BITS		8		// limit output to 16 bit
#define BASS_DEVICE_LATENCY		0x100	// calculate device latency (BASS_INFO struct)
#define BASS_DEVICE_CPSPEAKERS	0x400	// detect speakers via Windows control panel
#define BASS_DEVICE_SPEAKERS	0x800	// force enabling of speaker assignment
#define BASS_DEVICE_NOSPEAKER	0x1000	// ignore speaker arrangement
#define BASS_DEVICE_DMIX		0x2000	// use ALSA "dmix" plugin
#define BASS_DEVICE_FREQ		0x4000	// set device sample rate
#define BASS_DEVICE_STEREO		0x8000	// limit output to stereo
    
    // DirectSound interfaces (for use with BASS_GetDSoundObject)
#define BASS_OBJECT_DS		1	// IDirectSound
#define BASS_OBJECT_DS3DL	2	// IDirectSound3DListener
    
    // Device info structure
    typedef struct {
#if defined(_WIN32_WCE) || (WINAPI_FAMILY && WINAPI_FAMILY!=WINAPI_FAMILY_DESKTOP_APP)
        const wchar_t *name;	// description
        const wchar_t *driver;	// driver
#else
        const char *name;	// description
        const char *driver;	// driver
#endif
        DWORD flags;
    } BASS_DEVICEINFO;
    
    // BASS_DEVICEINFO flags
#define BASS_DEVICE_ENABLED		1
#define BASS_DEVICE_DEFAULT		2
#define BASS_DEVICE_INIT		4
    
#define BASS_DEVICE_TYPE_MASK			0xff000000
#define BASS_DEVICE_TYPE_NETWORK		0x01000000
#define BASS_DEVICE_TYPE_SPEAKERS		0x02000000
#define BASS_DEVICE_TYPE_LINE			0x03000000
#define BASS_DEVICE_TYPE_HEADPHONES		0x04000000
#define BASS_DEVICE_TYPE_MICROPHONE		0x05000000
#define BASS_DEVICE_TYPE_HEADSET		0x06000000
#define BASS_DEVICE_TYPE_HANDSET		0x07000000
#define BASS_DEVICE_TYPE_DIGITAL		0x08000000
#define BASS_DEVICE_TYPE_SPDIF			0x09000000
#define BASS_DEVICE_TYPE_HDMI			0x0a000000
#define BASS_DEVICE_TYPE_DISPLAYPORT	0x40000000
    
    // BASS_GetDeviceInfo flags
#define BASS_DEVICES_AIRPLAY	0x1000000
    
    typedef struct {
        DWORD flags;	// device capabilities (DSCAPS_xxx flags)
        DWORD hwsize;	// size of total device hardware memory
        DWORD hwfree;	// size of free device hardware memory
        DWORD freesam;	// number of free sample slots in the hardware
        DWORD free3d;	// number of free 3D sample slots in the hardware
        DWORD minrate;	// min sample rate supported by the hardware
        DWORD maxrate;	// max sample rate supported by the hardware
        BOOL eax;		// device supports EAX? (always FALSE if BASS_DEVICE_3D was not used)
        DWORD minbuf;	// recommended minimum buffer length in ms (requires BASS_DEVICE_LATENCY)
        DWORD dsver;	// DirectSound version
        DWORD latency;	// delay (in ms) before start of playback (requires BASS_DEVICE_LATENCY)
        DWORD initflags; // BASS_Init "flags" parameter
        DWORD speakers; // number of speakers available
        DWORD freq;		// current output rate
    } BASS_INFO;
    
    // BASS_INFO flags (from DSOUND.H)
#define DSCAPS_CONTINUOUSRATE	0x00000010	// supports all sample rates between min/maxrate
#define DSCAPS_EMULDRIVER		0x00000020	// device does NOT have hardware DirectSound support
#define DSCAPS_CERTIFIED		0x00000040	// device driver has been certified by Microsoft
#define DSCAPS_SECONDARYMONO	0x00000100	// mono
#define DSCAPS_SECONDARYSTEREO	0x00000200	// stereo
#define DSCAPS_SECONDARY8BIT	0x00000400	// 8 bit
#define DSCAPS_SECONDARY16BIT	0x00000800	// 16 bit
    
    // Recording device info structure
    typedef struct {
        DWORD flags;	// device capabilities (DSCCAPS_xxx flags)
        DWORD formats;	// supported standard formats (WAVE_FORMAT_xxx flags)
        DWORD inputs;	// number of inputs
        BOOL singlein;	// TRUE = only 1 input can be set at a time
        DWORD freq;		// current input rate
    } BASS_RECORDINFO;
    
    // BASS_RECORDINFO flags (from DSOUND.H)
#define DSCCAPS_EMULDRIVER		DSCAPS_EMULDRIVER	// device does NOT have hardware DirectSound recording support
#define DSCCAPS_CERTIFIED		DSCAPS_CERTIFIED	// device driver has been certified by Microsoft
    
    // defines for formats field of BASS_RECORDINFO (from MMSYSTEM.H)
#ifndef WAVE_FORMAT_1M08
#define WAVE_FORMAT_1M08       0x00000001       /* 11.025 kHz, Mono,   8-bit  */
#define WAVE_FORMAT_1S08       0x00000002       /* 11.025 kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_1M16       0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define WAVE_FORMAT_1S16       0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define WAVE_FORMAT_2M08       0x00000010       /* 22.05  kHz, Mono,   8-bit  */
#define WAVE_FORMAT_2S08       0x00000020       /* 22.05  kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_2M16       0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define WAVE_FORMAT_2S16       0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define WAVE_FORMAT_4M08       0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define WAVE_FORMAT_4S08       0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_4M16       0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define WAVE_FORMAT_4S16       0x00000800       /* 44.1   kHz, Stereo, 16-bit */
#endif
    
    // Sample info structure
    typedef struct {
        DWORD freq;		// default playback rate
        float volume;	// default volume (0-1)
        float pan;		// default pan (-1=left, 0=middle, 1=right)
        DWORD flags;	// BASS_SAMPLE_xxx flags
        DWORD length;	// length (in bytes)
        DWORD max;		// maximum simultaneous playbacks
        DWORD origres;	// original resolution bits
        DWORD chans;	// number of channels
        DWORD mingap;	// minimum gap (ms) between creating channels
        DWORD mode3d;	// BASS_3DMODE_xxx mode
        float mindist;	// minimum distance
        float maxdist;	// maximum distance
        DWORD iangle;	// angle of inside projection cone
        DWORD oangle;	// angle of outside projection cone
        float outvol;	// delta-volume outside the projection cone
        DWORD vam;		// voice allocation/management flags (BASS_VAM_xxx)
        DWORD priority;	// priority (0=lowest, 0xffffffff=highest)
    } BASS_SAMPLE;
    
#define BASS_SAMPLE_8BITS		1	// 8 bit
#define BASS_SAMPLE_FLOAT		256	// 32 bit floating-point
#define BASS_SAMPLE_MONO		2	// mono
#define BASS_SAMPLE_LOOP		4	// looped
#define BASS_SAMPLE_3D			8	// 3D functionality
#define BASS_SAMPLE_SOFTWARE	16	// not using hardware mixing
#define BASS_SAMPLE_MUTEMAX		32	// mute at max distance (3D only)
#define BASS_SAMPLE_VAM			64	// DX7 voice allocation & management
#define BASS_SAMPLE_FX			128	// old implementation of DX8 effects
#define BASS_SAMPLE_OVER_VOL	0x10000	// override lowest volume
#define BASS_SAMPLE_OVER_POS	0x20000	// override longest playing
#define BASS_SAMPLE_OVER_DIST	0x30000 // override furthest from listener (3D only)
    
#define BASS_STREAM_PRESCAN		0x20000 // enable pin-point seeking/length (MP3/MP2/MP1)
#define BASS_MP3_SETPOS			BASS_STREAM_PRESCAN
#define BASS_STREAM_AUTOFREE	0x40000	// automatically free the stream when it stop/ends
#define BASS_STREAM_RESTRATE	0x80000	// restrict the download rate of internet file streams
#define BASS_STREAM_BLOCK		0x100000 // download/play internet file stream in small blocks
#define BASS_STREAM_DECODE		0x200000 // don't play the stream, only decode (BASS_ChannelGetData)
#define BASS_STREAM_STATUS		0x800000 // give server status info (HTTP/ICY tags) in DOWNLOADPROC
    
#define BASS_MUSIC_FLOAT		BASS_SAMPLE_FLOAT
#define BASS_MUSIC_MONO			BASS_SAMPLE_MONO
#define BASS_MUSIC_LOOP			BASS_SAMPLE_LOOP
#define BASS_MUSIC_3D			BASS_SAMPLE_3D
#define BASS_MUSIC_FX			BASS_SAMPLE_FX
#define BASS_MUSIC_AUTOFREE		BASS_STREAM_AUTOFREE
#define BASS_MUSIC_DECODE		BASS_STREAM_DECODE
#define BASS_MUSIC_PRESCAN		BASS_STREAM_PRESCAN	// calculate playback length
#define BASS_MUSIC_CALCLEN		BASS_MUSIC_PRESCAN
#define BASS_MUSIC_RAMP			0x200	// normal ramping
#define BASS_MUSIC_RAMPS		0x400	// sensitive ramping
#define BASS_MUSIC_SURROUND		0x800	// surround sound
#define BASS_MUSIC_SURROUND2	0x1000	// surround sound (mode 2)
#define BASS_MUSIC_FT2PAN		0x2000	// apply FastTracker 2 panning to XM files
#define BASS_MUSIC_FT2MOD		0x2000	// play .MOD as FastTracker 2 does
#define BASS_MUSIC_PT1MOD		0x4000	// play .MOD as ProTracker 1 does
#define BASS_MUSIC_NONINTER		0x10000	// non-interpolated sample mixing
#define BASS_MUSIC_SINCINTER	0x800000 // sinc interpolated sample mixing
#define BASS_MUSIC_POSRESET		0x8000	// stop all notes when moving position
#define BASS_MUSIC_POSRESETEX	0x400000 // stop all notes and reset bmp/etc when moving position
#define BASS_MUSIC_STOPBACK		0x80000	// stop the music on a backwards jump effect
#define BASS_MUSIC_NOSAMPLE		0x100000 // don't load the samples
    
    // Speaker assignment flags
#define BASS_SPEAKER_FRONT	0x1000000	// front speakers
#define BASS_SPEAKER_REAR	0x2000000	// rear/side speakers
#define BASS_SPEAKER_CENLFE	0x3000000	// center & LFE speakers (5.1)
#define BASS_SPEAKER_REAR2	0x4000000	// rear center speakers (7.1)
#define BASS_SPEAKER_N(n)	((n)<<24)	// n'th pair of speakers (max 15)
#define BASS_SPEAKER_LEFT	0x10000000	// modifier: left
#define BASS_SPEAKER_RIGHT	0x20000000	// modifier: right
#define BASS_SPEAKER_FRONTLEFT	BASS_SPEAKER_FRONT|BASS_SPEAKER_LEFT
#define BASS_SPEAKER_FRONTRIGHT	BASS_SPEAKER_FRONT|BASS_SPEAKER_RIGHT
#define BASS_SPEAKER_REARLEFT	BASS_SPEAKER_REAR|BASS_SPEAKER_LEFT
#define BASS_SPEAKER_REARRIGHT	BASS_SPEAKER_REAR|BASS_SPEAKER_RIGHT
#define BASS_SPEAKER_CENTER		BASS_SPEAKER_CENLFE|BASS_SPEAKER_LEFT
#define BASS_SPEAKER_LFE		BASS_SPEAKER_CENLFE|BASS_SPEAKER_RIGHT
#define BASS_SPEAKER_REAR2LEFT	BASS_SPEAKER_REAR2|BASS_SPEAKER_LEFT
#define BASS_SPEAKER_REAR2RIGHT	BASS_SPEAKER_REAR2|BASS_SPEAKER_RIGHT
    
#define BASS_ASYNCFILE			0x40000000
#define BASS_UNICODE			0x80000000
    
#define BASS_RECORD_PAUSE		0x8000	// start recording paused
#define BASS_RECORD_ECHOCANCEL	0x2000
#define BASS_RECORD_AGC			0x4000
    
    // DX7 voice allocation & management flags
#define BASS_VAM_HARDWARE		1
#define BASS_VAM_SOFTWARE		2
#define BASS_VAM_TERM_TIME		4
#define BASS_VAM_TERM_DIST		8
#define BASS_VAM_TERM_PRIO		16
    
    // Channel info structure
    typedef struct {
        DWORD freq;		// default playback rate
        DWORD chans;	// channels
        DWORD flags;	// BASS_SAMPLE/STREAM/MUSIC/SPEAKER flags
        DWORD ctype;	// type of channel
        DWORD origres;	// original resolution
        HPLUGIN plugin;	// plugin
        HSAMPLE sample; // sample
        const char *filename; // filename
    } BASS_CHANNELINFO;
    
    // BASS_CHANNELINFO types
#define BASS_CTYPE_SAMPLE		1
#define BASS_CTYPE_RECORD		2
#define BASS_CTYPE_STREAM		0x10000
#define BASS_CTYPE_STREAM_OGG	0x10002
#define BASS_CTYPE_STREAM_MP1	0x10003
#define BASS_CTYPE_STREAM_MP2	0x10004
#define BASS_CTYPE_STREAM_MP3	0x10005
#define BASS_CTYPE_STREAM_AIFF	0x10006
#define BASS_CTYPE_STREAM_CA	0x10007
#define BASS_CTYPE_STREAM_MF	0x10008
#define BASS_CTYPE_STREAM_WAV	0x40000 // WAVE flag, LOWORD=codec
#define BASS_CTYPE_STREAM_WAV_PCM	0x50001
#define BASS_CTYPE_STREAM_WAV_FLOAT	0x50003
#define BASS_CTYPE_MUSIC_MOD	0x20000
#define BASS_CTYPE_MUSIC_MTM	0x20001
#define BASS_CTYPE_MUSIC_S3M	0x20002
#define BASS_CTYPE_MUSIC_XM		0x20003
#define BASS_CTYPE_MUSIC_IT		0x20004
#define BASS_CTYPE_MUSIC_MO3	0x00100 // MO3 flag
    
    typedef struct {
        DWORD ctype;		// channel type
#if defined(_WIN32_WCE) || (WINAPI_FAMILY && WINAPI_FAMILY!=WINAPI_FAMILY_DESKTOP_APP)
        const wchar_t *name;	// format description
        const wchar_t *exts;	// file extension filter (*.ext1;*.ext2;etc...)
#else
        const char *name;	// format description
        const char *exts;	// file extension filter (*.ext1;*.ext2;etc...)
#endif
    } BASS_PLUGINFORM;
    
    typedef struct {
        DWORD version;					// version (same form as BASS_GetVersion)
        DWORD formatc;					// number of formats
        const BASS_PLUGINFORM *formats;	// the array of formats
    } BASS_PLUGININFO;
    
    // 3D vector (for 3D positions/velocities/orientations)
    typedef struct BASS_3DVECTOR {
#ifdef __cplusplus
        BASS_3DVECTOR() {};
        BASS_3DVECTOR(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
#endif
        float x;	// +=right, -=left
        float y;	// +=up, -=down
        float z;	// +=front, -=behind
    } BASS_3DVECTOR;
    
    // 3D channel modes
#define BASS_3DMODE_NORMAL		0	// normal 3D processing
#define BASS_3DMODE_RELATIVE	1	// position is relative to the listener
#define BASS_3DMODE_OFF			2	// no 3D processing
    
    // software 3D mixing algorithms (used with BASS_CONFIG_3DALGORITHM)
#define BASS_3DALG_DEFAULT	0
#define BASS_3DALG_OFF		1
#define BASS_3DALG_FULL		2
#define BASS_3DALG_LIGHT	3
    
    // EAX environments, use with BASS_SetEAXParameters
    enum
    {
        EAX_ENVIRONMENT_GENERIC,
        EAX_ENVIRONMENT_PADDEDCELL,
        EAX_ENVIRONMENT_ROOM,
        EAX_ENVIRONMENT_BATHROOM,
        EAX_ENVIRONMENT_LIVINGROOM,
        EAX_ENVIRONMENT_STONEROOM,
        EAX_ENVIRONMENT_AUDITORIUM,
        EAX_ENVIRONMENT_CONCERTHALL,
        EAX_ENVIRONMENT_CAVE,
        EAX_ENVIRONMENT_ARENA,
        EAX_ENVIRONMENT_HANGAR,
        EAX_ENVIRONMENT_CARPETEDHALLWAY,
        EAX_ENVIRONMENT_HALLWAY,
        EAX_ENVIRONMENT_STONECORRIDOR,
        EAX_ENVIRONMENT_ALLEY,
        EAX_ENVIRONMENT_FOREST,
        EAX_ENVIRONMENT_CITY,
        EAX_ENVIRONMENT_MOUNTAINS,
        EAX_ENVIRONMENT_QUARRY,
        EAX_ENVIRONMENT_PLAIN,
        EAX_ENVIRONMENT_PARKINGLOT,
        EAX_ENVIRONMENT_SEWERPIPE,
        EAX_ENVIRONMENT_UNDERWATER,
        EAX_ENVIRONMENT_DRUGGED,
        EAX_ENVIRONMENT_DIZZY,
        EAX_ENVIRONMENT_PSYCHOTIC,
        
        EAX_ENVIRONMENT_COUNT			// total number of environments
    };
    
    // EAX presets, usage: BASS_SetEAXParameters(EAX_PRESET_xxx)
#define EAX_PRESET_GENERIC         EAX_ENVIRONMENT_GENERIC,0.5F,1.493F,0.5F
#define EAX_PRESET_PADDEDCELL      EAX_ENVIRONMENT_PADDEDCELL,0.25F,0.1F,0.0F
#define EAX_PRESET_ROOM            EAX_ENVIRONMENT_ROOM,0.417F,0.4F,0.666F
#define EAX_PRESET_BATHROOM        EAX_ENVIRONMENT_BATHROOM,0.653F,1.499F,0.166F
#define EAX_PRESET_LIVINGROOM      EAX_ENVIRONMENT_LIVINGROOM,0.208F,0.478F,0.0F
#define EAX_PRESET_STONEROOM       EAX_ENVIRONMENT_STONEROOM,0.5F,2.309F,0.888F
#define EAX_PRESET_AUDITORIUM      EAX_ENVIRONMENT_AUDITORIUM,0.403F,4.279F,0.5F
#define EAX_PRESET_CONCERTHALL     EAX_ENVIRONMENT_CONCERTHALL,0.5F,3.961F,0.5F
#define EAX_PRESET_CAVE            EAX_ENVIRONMENT_CAVE,0.5F,2.886F,1.304F
#define EAX_PRESET_ARENA           EAX_ENVIRONMENT_ARENA,0.361F,7.284F,0.332F
#define EAX_PRESET_HANGAR          EAX_ENVIRONMENT_HANGAR,0.5F,10.0F,0.3F
#define EAX_PRESET_CARPETEDHALLWAY EAX_ENVIRONMENT_CARPETEDHALLWAY,0.153F,0.259F,2.0F
#define EAX_PRESET_HALLWAY         EAX_ENVIRONMENT_HALLWAY,0.361F,1.493F,0.0F
#define EAX_PRESET_STONECORRIDOR   EAX_ENVIRONMENT_STONECORRIDOR,0.444F,2.697F,0.638F
#define EAX_PRESET_ALLEY           EAX_ENVIRONMENT_ALLEY,0.25F,1.752F,0.776F
#define EAX_PRESET_FOREST          EAX_ENVIRONMENT_FOREST,0.111F,3.145F,0.472F
#define EAX_PRESET_CITY            EAX_ENVIRONMENT_CITY,0.111F,2.767F,0.224F
#define EAX_PRESET_MOUNTAINS       EAX_ENVIRONMENT_MOUNTAINS,0.194F,7.841F,0.472F
#define EAX_PRESET_QUARRY          EAX_ENVIRONMENT_QUARRY,1.0F,1.499F,0.5F
#define EAX_PRESET_PLAIN           EAX_ENVIRONMENT_PLAIN,0.097F,2.767F,0.224F
#define EAX_PRESET_PARKINGLOT      EAX_ENVIRONMENT_PARKINGLOT,0.208F,1.652F,1.5F
#define EAX_PRESET_SEWERPIPE       EAX_ENVIRONMENT_SEWERPIPE,0.652F,2.886F,0.25F
#define EAX_PRESET_UNDERWATER      EAX_ENVIRONMENT_UNDERWATER,1.0F,1.499F,0.0F
#define EAX_PRESET_DRUGGED         EAX_ENVIRONMENT_DRUGGED,0.875F,8.392F,1.388F
#define EAX_PRESET_DIZZY           EAX_ENVIRONMENT_DIZZY,0.139F,17.234F,0.666F
#define EAX_PRESET_PSYCHOTIC       EAX_ENVIRONMENT_PSYCHOTIC,0.486F,7.563F,0.806F
    
    typedef DWORD (CALLBACK STREAMPROC)(HSTREAM handle, void *buffer, DWORD length, void *user);
    /* User stream callback function. NOTE: A stream function should obviously be as quick
     as possible, other streams (and MOD musics) can't be mixed until it's finished.
     handle : The stream that needs writing
     buffer : Buffer to write the samples in
     length : Number of bytes to write
     user   : The 'user' parameter value given when calling BASS_StreamCreate
     RETURN : Number of bytes written. Set the BASS_STREAMPROC_END flag to end
     the stream. */
    
#define BASS_STREAMPROC_END		0x80000000	// end of user stream flag
    
    // special STREAMPROCs
#define STREAMPROC_DUMMY		(STREAMPROC*)0		// "dummy" stream
#define STREAMPROC_PUSH			(STREAMPROC*)-1		// push stream
    
    // BASS_StreamCreateFileUser file systems
#define STREAMFILE_NOBUFFER		0
#define STREAMFILE_BUFFER		1
#define STREAMFILE_BUFFERPUSH	2
    
    // User file stream callback functions
    typedef void (CALLBACK FILECLOSEPROC)(void *user);
    typedef QWORD (CALLBACK FILELENPROC)(void *user);
    typedef DWORD (CALLBACK FILEREADPROC)(void *buffer, DWORD length, void *user);
    typedef BOOL (CALLBACK FILESEEKPROC)(QWORD offset, void *user);
    
    typedef struct {
        FILECLOSEPROC *close;
        FILELENPROC *length;
        FILEREADPROC *read;
        FILESEEKPROC *seek;
    } BASS_FILEPROCS;
    
    // BASS_StreamPutFileData options
#define BASS_FILEDATA_END		0	// end & close the file
    
    // BASS_StreamGetFilePosition modes
#define BASS_FILEPOS_CURRENT	0
#define BASS_FILEPOS_DECODE		BASS_FILEPOS_CURRENT
#define BASS_FILEPOS_DOWNLOAD	1
#define BASS_FILEPOS_END		2
#define BASS_FILEPOS_START		3
#define BASS_FILEPOS_CONNECTED	4
#define BASS_FILEPOS_BUFFER		5
#define BASS_FILEPOS_SOCKET		6
#define BASS_FILEPOS_ASYNCBUF	7
#define BASS_FILEPOS_SIZE		8
    
    typedef void (CALLBACK DOWNLOADPROC)(const void *buffer, DWORD length, void *user);
    /* Internet stream download callback function.
     buffer : Buffer containing the downloaded data... NULL=end of download
     length : Number of bytes in the buffer
     user   : The 'user' parameter value given when calling BASS_StreamCreateURL */
    
    // BASS_ChannelSetSync types
#define BASS_SYNC_POS			0
#define BASS_SYNC_END			2
#define BASS_SYNC_META			4
#define BASS_SYNC_SLIDE			5
#define BASS_SYNC_STALL			6
#define BASS_SYNC_DOWNLOAD		7
#define BASS_SYNC_FREE			8
#define BASS_SYNC_SETPOS		11
#define BASS_SYNC_MUSICPOS		10
#define BASS_SYNC_MUSICINST		1
#define BASS_SYNC_MUSICFX		3
#define BASS_SYNC_OGG_CHANGE	12
#define BASS_SYNC_MIXTIME		0x40000000	// flag: sync at mixtime, else at playtime
#define BASS_SYNC_ONETIME		0x80000000	// flag: sync only once, else continuously
    
    typedef void (CALLBACK SYNCPROC)(HSYNC handle, DWORD channel, DWORD data, void *user);
    /* Sync callback function. NOTE: a sync callback function should be very
     quick as other syncs can't be processed until it has finished. If the sync
     is a "mixtime" sync, then other streams and MOD musics can't be mixed until
     it's finished either.
     handle : The sync that has occured
     channel: Channel that the sync occured in
     data   : Additional data associated with the sync's occurance
     user   : The 'user' parameter given when calling BASS_ChannelSetSync */
    
    typedef void (CALLBACK DSPPROC)(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user);
    /* DSP callback function. NOTE: A DSP function should obviously be as quick as
     possible... other DSP functions, streams and MOD musics can not be processed
     until it's finished.
     handle : The DSP handle
     channel: Channel that the DSP is being applied to
     buffer : Buffer to apply the DSP to
     length : Number of bytes in the buffer
     user   : The 'user' parameter given when calling BASS_ChannelSetDSP */
    
    typedef BOOL (CALLBACK RECORDPROC)(HRECORD handle, const void *buffer, DWORD length, void *user);
    /* Recording callback function.
     handle : The recording handle
     buffer : Buffer containing the recorded sample data
     length : Number of bytes
     user   : The 'user' parameter value given when calling BASS_RecordStart
     RETURN : TRUE = continue recording, FALSE = stop */
    
    // BASS_ChannelIsActive return values
#define BASS_ACTIVE_STOPPED	0
#define BASS_ACTIVE_PLAYING	1
#define BASS_ACTIVE_STALLED	2
#define BASS_ACTIVE_PAUSED	3
    
    // Channel attributes
#define BASS_ATTRIB_FREQ			1
#define BASS_ATTRIB_VOL				2
#define BASS_ATTRIB_PAN				3
#define BASS_ATTRIB_EAXMIX			4
#define BASS_ATTRIB_NOBUFFER		5
#define BASS_ATTRIB_VBR				6
#define BASS_ATTRIB_CPU				7
#define BASS_ATTRIB_SRC				8
#define BASS_ATTRIB_NET_RESUME		9
#define BASS_ATTRIB_SCANINFO		10
#define BASS_ATTRIB_NORAMP			11
#define BASS_ATTRIB_BITRATE			12
#define BASS_ATTRIB_MUSIC_AMPLIFY	0x100
#define BASS_ATTRIB_MUSIC_PANSEP	0x101
#define BASS_ATTRIB_MUSIC_PSCALER	0x102
#define BASS_ATTRIB_MUSIC_BPM		0x103
#define BASS_ATTRIB_MUSIC_SPEED		0x104
#define BASS_ATTRIB_MUSIC_VOL_GLOBAL 0x105
#define BASS_ATTRIB_MUSIC_ACTIVE	0x106
#define BASS_ATTRIB_MUSIC_VOL_CHAN	0x200 // + channel #
#define BASS_ATTRIB_MUSIC_VOL_INST	0x300 // + instrument #
    
    // BASS_ChannelGetData flags
#define BASS_DATA_AVAILABLE	0			// query how much data is buffered
#define BASS_DATA_FIXED		0x20000000	// flag: return 8.24 fixed-point data
#define BASS_DATA_FLOAT		0x40000000	// flag: return floating-point sample data
#define BASS_DATA_FFT256	0x80000000	// 256 sample FFT
#define BASS_DATA_FFT512	0x80000001	// 512 FFT
#define BASS_DATA_FFT1024	0x80000002	// 1024 FFT
#define BASS_DATA_FFT2048	0x80000003	// 2048 FFT
#define BASS_DATA_FFT4096	0x80000004	// 4096 FFT
#define BASS_DATA_FFT8192	0x80000005	// 8192 FFT
#define BASS_DATA_FFT16384	0x80000006	// 16384 FFT
#define BASS_DATA_FFT32768	0x80000007	// 32768 FFT
#define BASS_DATA_FFT_INDIVIDUAL 0x10	// FFT flag: FFT for each channel, else all combined
#define BASS_DATA_FFT_NOWINDOW	0x20	// FFT flag: no Hanning window
#define BASS_DATA_FFT_REMOVEDC	0x40	// FFT flag: pre-remove DC bias
#define BASS_DATA_FFT_COMPLEX	0x80	// FFT flag: return complex data
    
    // BASS_ChannelGetLevelEx flags
#define BASS_LEVEL_MONO		1
#define BASS_LEVEL_STEREO	2
#define BASS_LEVEL_RMS		4
    
    // BASS_ChannelGetTags types : what's returned
#define BASS_TAG_ID3		0	// ID3v1 tags : TAG_ID3 structure
#define BASS_TAG_ID3V2		1	// ID3v2 tags : variable length block
#define BASS_TAG_OGG		2	// OGG comments : series of null-terminated UTF-8 strings
#define BASS_TAG_HTTP		3	// HTTP headers : series of null-terminated ANSI strings
#define BASS_TAG_ICY		4	// ICY headers : series of null-terminated ANSI strings
#define BASS_TAG_META		5	// ICY metadata : ANSI string
#define BASS_TAG_APE		6	// APE tags : series of null-terminated UTF-8 strings
#define BASS_TAG_MP4 		7	// MP4/iTunes metadata : series of null-terminated UTF-8 strings
#define BASS_TAG_WMA		8	// WMA tags : series of null-terminated UTF-8 strings
#define BASS_TAG_VENDOR		9	// OGG encoder : UTF-8 string
#define BASS_TAG_LYRICS3	10	// Lyric3v2 tag : ASCII string
#define BASS_TAG_CA_CODEC	11	// CoreAudio codec info : TAG_CA_CODEC structure
#define BASS_TAG_MF			13	// Media Foundation tags : series of null-terminated UTF-8 strings
#define BASS_TAG_WAVEFORMAT	14	// WAVE format : WAVEFORMATEEX structure
#define BASS_TAG_RIFF_INFO	0x100 // RIFF "INFO" tags : series of null-terminated ANSI strings
#define BASS_TAG_RIFF_BEXT	0x101 // RIFF/BWF "bext" tags : TAG_BEXT structure
#define BASS_TAG_RIFF_CART	0x102 // RIFF/BWF "cart" tags : TAG_CART structure
#define BASS_TAG_RIFF_DISP	0x103 // RIFF "DISP" text tag : ANSI string
#define BASS_TAG_APE_BINARY	0x1000	// + index #, binary APE tag : TAG_APE_BINARY structure
#define BASS_TAG_MUSIC_NAME		0x10000	// MOD music name : ANSI string
#define BASS_TAG_MUSIC_MESSAGE	0x10001	// MOD message : ANSI string
#define BASS_TAG_MUSIC_ORDERS	0x10002	// MOD order list : BYTE array of pattern numbers
#define BASS_TAG_MUSIC_AUTH		0x10003	// MOD author : UTF-8 string
#define BASS_TAG_MUSIC_INST		0x10100	// + instrument #, MOD instrument name : ANSI string
#define BASS_TAG_MUSIC_SAMPLE	0x10300	// + sample #, MOD sample name : ANSI string
    
    // ID3v1 tag structure
    typedef struct {
        char id[3];
        char title[30];
        char artist[30];
        char album[30];
        char year[4];
        char comment[30];
        BYTE genre;
    } TAG_ID3;
    
    // Binary APE tag structure
    typedef struct {
        const char *key;
        const void *data;
        DWORD length;
    } TAG_APE_BINARY;
    
    // BWF "bext" tag structure
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4200)
#endif
#pragma pack(push,1)
    typedef struct {
        char Description[256];			// description
        char Originator[32];			// name of the originator
        char OriginatorReference[32];	// reference of the originator
        char OriginationDate[10];		// date of creation (yyyy-mm-dd)
        char OriginationTime[8];		// time of creation (hh-mm-ss)
        QWORD TimeReference;			// first sample count since midnight (little-endian)
        WORD Version;					// BWF version (little-endian)
        BYTE UMID[64];					// SMPTE UMID
        BYTE Reserved[190];
#if defined(__GNUC__) && __GNUC__<3
        char CodingHistory[0];			// history
#elif 1 // change to 0 if compiler fails the following line
        char CodingHistory[];			// history
#else
        char CodingHistory[1];			// history
#endif
    } TAG_BEXT;
#pragma pack(pop)
    
    // BWF "cart" tag structures
    typedef struct
    {
        DWORD dwUsage;					// FOURCC timer usage ID
        DWORD dwValue;					// timer value in samples from head
    } TAG_CART_TIMER;
    
    typedef struct
    {
        char Version[4];				// version of the data structure
        char Title[64];					// title of cart audio sequence
        char Artist[64];				// artist or creator name
        char CutID[64];					// cut number identification
        char ClientID[64];				// client identification
        char Category[64];				// category ID, PSA, NEWS, etc
        char Classification[64];		// classification or auxiliary key
        char OutCue[64];				// out cue text
        char StartDate[10];				// yyyy-mm-dd
        char StartTime[8];				// hh:mm:ss
        char EndDate[10];				// yyyy-mm-dd
        char EndTime[8];				// hh:mm:ss
        char ProducerAppID[64];			// name of vendor or application
        char ProducerAppVersion[64];	// version of producer application
        char UserDef[64];				// user defined text
        DWORD dwLevelReference;			// sample value for 0 dB reference
        TAG_CART_TIMER PostTimer[8];	// 8 time markers after head
        char Reserved[276];
        char URL[1024];					// uniform resource locator
#if defined(__GNUC__) && __GNUC__<3
        char TagText[0];				// free form text for scripts or tags
#elif 1 // change to 0 if compiler fails the following line
        char TagText[];					// free form text for scripts or tags
#else
        char TagText[1];				// free form text for scripts or tags
#endif
    } TAG_CART;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    
    // CoreAudio codec info structure
    typedef struct {
        DWORD ftype;					// file format
        DWORD atype;					// audio format
        const char *name;				// description
    } TAG_CA_CODEC;
    
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
#pragma pack(push,1)
    typedef struct tWAVEFORMATEX
    {
        WORD wFormatTag;
        WORD nChannels;
        DWORD nSamplesPerSec;
        DWORD nAvgBytesPerSec;
        WORD nBlockAlign;
        WORD wBitsPerSample;
        WORD cbSize;
    } WAVEFORMATEX, *PWAVEFORMATEX, *LPWAVEFORMATEX;
    typedef const WAVEFORMATEX *LPCWAVEFORMATEX;
#pragma pack(pop)
#endif
    
    // BASS_ChannelGetLength/GetPosition/SetPosition modes
#define BASS_POS_BYTE			0		// byte position
#define BASS_POS_MUSIC_ORDER	1		// order.row position, MAKELONG(order,row)
#define BASS_POS_OGG			3		// OGG bitstream number
#define BASS_POS_INEXACT		0x8000000 // flag: allow seeking to inexact position
#define BASS_POS_DECODE			0x10000000 // flag: get the decoding (not playing) position
#define BASS_POS_DECODETO		0x20000000 // flag: decode to the position instead of seeking
#define BASS_POS_SCAN			0x40000000 // flag: scan to the position
    
    // BASS_RecordSetInput flags
#define BASS_INPUT_OFF		0x10000
#define BASS_INPUT_ON		0x20000
    
#define BASS_INPUT_TYPE_MASK		0xff000000
#define BASS_INPUT_TYPE_UNDEF		0x00000000
#define BASS_INPUT_TYPE_DIGITAL		0x01000000
#define BASS_INPUT_TYPE_LINE		0x02000000
#define BASS_INPUT_TYPE_MIC			0x03000000
#define BASS_INPUT_TYPE_SYNTH		0x04000000
#define BASS_INPUT_TYPE_CD			0x05000000
#define BASS_INPUT_TYPE_PHONE		0x06000000
#define BASS_INPUT_TYPE_SPEAKER		0x07000000
#define BASS_INPUT_TYPE_WAVE		0x08000000
#define BASS_INPUT_TYPE_AUX			0x09000000
#define BASS_INPUT_TYPE_ANALOG		0x0a000000
    
    // DX8 effect types, use with BASS_ChannelSetFX
    enum
    {
        BASS_FX_DX8_CHORUS,
        BASS_FX_DX8_COMPRESSOR,
        BASS_FX_DX8_DISTORTION,
        BASS_FX_DX8_ECHO,
        BASS_FX_DX8_FLANGER,
        BASS_FX_DX8_GARGLE,
        BASS_FX_DX8_I3DL2REVERB,
        BASS_FX_DX8_PARAMEQ,
        BASS_FX_DX8_REVERB
    };
    
    typedef struct {
        float       fWetDryMix;
        float       fDepth;
        float       fFeedback;
        float       fFrequency;
        DWORD       lWaveform;	// 0=triangle, 1=sine
        float       fDelay;
        DWORD       lPhase;		// BASS_DX8_PHASE_xxx
    } BASS_DX8_CHORUS;
    
    typedef struct {
        float   fGain;
        float   fAttack;
        float   fRelease;
        float   fThreshold;
        float   fRatio;
        float   fPredelay;
    } BASS_DX8_COMPRESSOR;
    
    typedef struct {
        float   fGain;
        float   fEdge;
        float   fPostEQCenterFrequency;
        float   fPostEQBandwidth;
        float   fPreLowpassCutoff;
    } BASS_DX8_DISTORTION;
    
    typedef struct {
        float   fWetDryMix;
        float   fFeedback;
        float   fLeftDelay;
        float   fRightDelay;
        BOOL    lPanDelay;
    } BASS_DX8_ECHO;
    
    typedef struct {
        float       fWetDryMix;
        float       fDepth;
        float       fFeedback;
        float       fFrequency;
        DWORD       lWaveform;	// 0=triangle, 1=sine
        float       fDelay;
        DWORD       lPhase;		// BASS_DX8_PHASE_xxx
    } BASS_DX8_FLANGER;
    
    typedef struct {
        DWORD       dwRateHz;               // Rate of modulation in hz
        DWORD       dwWaveShape;            // 0=triangle, 1=square
    } BASS_DX8_GARGLE;
    
    typedef struct {
        int     lRoom;                  // [-10000, 0]      default: -1000 mB
        int     lRoomHF;                // [-10000, 0]      default: 0 mB
        float   flRoomRolloffFactor;    // [0.0, 10.0]      default: 0.0
        float   flDecayTime;            // [0.1, 20.0]      default: 1.49s
        float   flDecayHFRatio;         // [0.1, 2.0]       default: 0.83
        int     lReflections;           // [-10000, 1000]   default: -2602 mB
        float   flReflectionsDelay;     // [0.0, 0.3]       default: 0.007 s
        int     lReverb;                // [-10000, 2000]   default: 200 mB
        float   flReverbDelay;          // [0.0, 0.1]       default: 0.011 s
        float   flDiffusion;            // [0.0, 100.0]     default: 100.0 %
        float   flDensity;              // [0.0, 100.0]     default: 100.0 %
        float   flHFReference;          // [20.0, 20000.0]  default: 5000.0 Hz
    } BASS_DX8_I3DL2REVERB;
    
    typedef struct {
        float   fCenter;
        float   fBandwidth;
        float   fGain;
    } BASS_DX8_PARAMEQ;
    
    typedef struct {
        float   fInGain;                // [-96.0,0.0]            default: 0.0 dB
        float   fReverbMix;             // [-96.0,0.0]            default: 0.0 db
        float   fReverbTime;            // [0.001,3000.0]         default: 1000.0 ms
        float   fHighFreqRTRatio;       // [0.001,0.999]          default: 0.001
    } BASS_DX8_REVERB;
    
#define BASS_DX8_PHASE_NEG_180        0
#define BASS_DX8_PHASE_NEG_90         1
#define BASS_DX8_PHASE_ZERO           2
#define BASS_DX8_PHASE_90             3
#define BASS_DX8_PHASE_180            4
    
    typedef void (CALLBACK IOSNOTIFYPROC)(DWORD status);
    /* iOS notification callback function.
     status : The notification (BASS_IOSNOTIFY_xxx) */
    
#define BASS_IOSNOTIFY_INTERRUPT		1	// interruption started
#define BASS_IOSNOTIFY_INTERRUPT_END	2	// interruption ended
    
    BOOL BASSDEF(BASS_SetConfig)(DWORD option, DWORD value);
    DWORD BASSDEF(BASS_GetConfig)(DWORD option);
    BOOL BASSDEF(BASS_SetConfigPtr)(DWORD option, const void *value);
    void *BASSDEF(BASS_GetConfigPtr)(DWORD option);
    DWORD BASSDEF(BASS_GetVersion)();
    int BASSDEF(BASS_ErrorGetCode)();
    BOOL BASSDEF(BASS_GetDeviceInfo)(DWORD device, BASS_DEVICEINFO *info);
#if defined(_WIN32) && !defined(_WIN32_WCE) && !(WINAPI_FAMILY && WINAPI_FAMILY!=WINAPI_FAMILY_DESKTOP_APP)
    BOOL BASSDEF(BASS_Init)(int device, DWORD freq, DWORD flags, HWND win, const GUID *dsguid);
#else
    BOOL BASSDEF(BASS_Init)(int device, DWORD freq, DWORD flags, void *win, void *dsguid);
#endif
    BOOL BASSDEF(BASS_SetDevice)(DWORD device);
    DWORD BASSDEF(BASS_GetDevice)();
    BOOL BASSDEF(BASS_Free)();
#if defined(_WIN32) && !defined(_WIN32_WCE) && !(WINAPI_FAMILY && WINAPI_FAMILY!=WINAPI_FAMILY_DESKTOP_APP)
    void *BASSDEF(BASS_GetDSoundObject)(DWORD object);
#endif
    BOOL BASSDEF(BASS_GetInfo)(BASS_INFO *info);
    BOOL BASSDEF(BASS_Update)(DWORD length);
    float BASSDEF(BASS_GetCPU)();
    BOOL BASSDEF(BASS_Start)();
    BOOL BASSDEF(BASS_Stop)();
    BOOL BASSDEF(BASS_Pause)();
    BOOL BASSDEF(BASS_SetVolume)(float volume);
    float BASSDEF(BASS_GetVolume)();
    
    HPLUGIN BASSDEF(BASS_PluginLoad)(const char *file, DWORD flags);
    BOOL BASSDEF(BASS_PluginFree)(HPLUGIN handle);
    const BASS_PLUGININFO *BASSDEF(BASS_PluginGetInfo)(HPLUGIN handle);
    
    BOOL BASSDEF(BASS_Set3DFactors)(float distf, float rollf, float doppf);
    BOOL BASSDEF(BASS_Get3DFactors)(float *distf, float *rollf, float *doppf);
    BOOL BASSDEF(BASS_Set3DPosition)(const BASS_3DVECTOR *pos, const BASS_3DVECTOR *vel, const BASS_3DVECTOR *front, const BASS_3DVECTOR *top);
    BOOL BASSDEF(BASS_Get3DPosition)(BASS_3DVECTOR *pos, BASS_3DVECTOR *vel, BASS_3DVECTOR *front, BASS_3DVECTOR *top);
    void BASSDEF(BASS_Apply3D)();
#if defined(_WIN32) && !defined(_WIN32_WCE) && !(WINAPI_FAMILY && WINAPI_FAMILY!=WINAPI_FAMILY_DESKTOP_APP)
    BOOL BASSDEF(BASS_SetEAXParameters)(int env, float vol, float decay, float damp);
    BOOL BASSDEF(BASS_GetEAXParameters)(DWORD *env, float *vol, float *decay, float *damp);
#endif
    
    HMUSIC BASSDEF(BASS_MusicLoad)(BOOL mem, const void *file, QWORD offset, DWORD length, DWORD flags, DWORD freq);
    BOOL BASSDEF(BASS_MusicFree)(HMUSIC handle);
    
    HSAMPLE BASSDEF(BASS_SampleLoad)(BOOL mem, const void *file, QWORD offset, DWORD length, DWORD max, DWORD flags);
    HSAMPLE BASSDEF(BASS_SampleCreate)(DWORD length, DWORD freq, DWORD chans, DWORD max, DWORD flags);
    BOOL BASSDEF(BASS_SampleFree)(HSAMPLE handle);
    BOOL BASSDEF(BASS_SampleSetData)(HSAMPLE handle, const void *buffer);
    BOOL BASSDEF(BASS_SampleGetData)(HSAMPLE handle, void *buffer);
    BOOL BASSDEF(BASS_SampleGetInfo)(HSAMPLE handle, BASS_SAMPLE *info);
    BOOL BASSDEF(BASS_SampleSetInfo)(HSAMPLE handle, const BASS_SAMPLE *info);
    HCHANNEL BASSDEF(BASS_SampleGetChannel)(HSAMPLE handle, BOOL onlynew);
    DWORD BASSDEF(BASS_SampleGetChannels)(HSAMPLE handle, HCHANNEL *channels);
    BOOL BASSDEF(BASS_SampleStop)(HSAMPLE handle);
    
    HSTREAM BASSDEF(BASS_StreamCreate)(DWORD freq, DWORD chans, DWORD flags, STREAMPROC *proc, void *user);
    HSTREAM BASSDEF(BASS_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSDEF(BASS_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user);
    HSTREAM BASSDEF(BASS_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *proc, void *user);
    BOOL BASSDEF(BASS_StreamFree)(HSTREAM handle);
    QWORD BASSDEF(BASS_StreamGetFilePosition)(HSTREAM handle, DWORD mode);
    DWORD BASSDEF(BASS_StreamPutData)(HSTREAM handle, const void *buffer, DWORD length);
    DWORD BASSDEF(BASS_StreamPutFileData)(HSTREAM handle, const void *buffer, DWORD length);
    
    BOOL BASSDEF(BASS_RecordGetDeviceInfo)(DWORD device, BASS_DEVICEINFO *info);
    BOOL BASSDEF(BASS_RecordInit)(int device);
    BOOL BASSDEF(BASS_RecordSetDevice)(DWORD device);
    DWORD BASSDEF(BASS_RecordGetDevice)();
    BOOL BASSDEF(BASS_RecordFree)();
    BOOL BASSDEF(BASS_RecordGetInfo)(BASS_RECORDINFO *info);
    const char *BASSDEF(BASS_RecordGetInputName)(int input);
    BOOL BASSDEF(BASS_RecordSetInput)(int input, DWORD flags, float volume);
    DWORD BASSDEF(BASS_RecordGetInput)(int input, float *volume);
    HRECORD BASSDEF(BASS_RecordStart)(DWORD freq, DWORD chans, DWORD flags, RECORDPROC *proc, void *user);
    
    double BASSDEF(BASS_ChannelBytes2Seconds)(DWORD handle, QWORD pos);
    QWORD BASSDEF(BASS_ChannelSeconds2Bytes)(DWORD handle, double pos);
    DWORD BASSDEF(BASS_ChannelGetDevice)(DWORD handle);
    BOOL BASSDEF(BASS_ChannelSetDevice)(DWORD handle, DWORD device);
    DWORD BASSDEF(BASS_ChannelIsActive)(DWORD handle);
    BOOL BASSDEF(BASS_ChannelGetInfo)(DWORD handle, BASS_CHANNELINFO *info);
    const char *BASSDEF(BASS_ChannelGetTags)(DWORD handle, DWORD tags);
    DWORD BASSDEF(BASS_ChannelFlags)(DWORD handle, DWORD flags, DWORD mask);
    BOOL BASSDEF(BASS_ChannelUpdate)(DWORD handle, DWORD length);
    BOOL BASSDEF(BASS_ChannelLock)(DWORD handle, BOOL lock);
    BOOL BASSDEF(BASS_ChannelPlay)(DWORD handle, BOOL restart);
    BOOL BASSDEF(BASS_ChannelStop)(DWORD handle);
    BOOL BASSDEF(BASS_ChannelPause)(DWORD handle);
    BOOL BASSDEF(BASS_ChannelSetAttribute)(DWORD handle, DWORD attrib, float value);
    BOOL BASSDEF(BASS_ChannelGetAttribute)(DWORD handle, DWORD attrib, float *value);
    BOOL BASSDEF(BASS_ChannelSlideAttribute)(DWORD handle, DWORD attrib, float value, DWORD time);
    BOOL BASSDEF(BASS_ChannelIsSliding)(DWORD handle, DWORD attrib);
    BOOL BASSDEF(BASS_ChannelSetAttributeEx)(DWORD handle, DWORD attrib, void *value, DWORD size);
    DWORD BASSDEF(BASS_ChannelGetAttributeEx)(DWORD handle, DWORD attrib, void *value, DWORD size);
    BOOL BASSDEF(BASS_ChannelSet3DAttributes)(DWORD handle, int mode, float min, float max, int iangle, int oangle, float outvol);
    BOOL BASSDEF(BASS_ChannelGet3DAttributes)(DWORD handle, DWORD *mode, float *min, float *max, DWORD *iangle, DWORD *oangle, float *outvol);
    BOOL BASSDEF(BASS_ChannelSet3DPosition)(DWORD handle, const BASS_3DVECTOR *pos, const BASS_3DVECTOR *orient, const BASS_3DVECTOR *vel);
    BOOL BASSDEF(BASS_ChannelGet3DPosition)(DWORD handle, BASS_3DVECTOR *pos, BASS_3DVECTOR *orient, BASS_3DVECTOR *vel);
    QWORD BASSDEF(BASS_ChannelGetLength)(DWORD handle, DWORD mode);
    BOOL BASSDEF(BASS_ChannelSetPosition)(DWORD handle, QWORD pos, DWORD mode);
    QWORD BASSDEF(BASS_ChannelGetPosition)(DWORD handle, DWORD mode);
    DWORD BASSDEF(BASS_ChannelGetLevel)(DWORD handle);
    BOOL BASSDEF(BASS_ChannelGetLevelEx)(DWORD handle, float *levels, float length, DWORD flags);
    DWORD BASSDEF(BASS_ChannelGetData)(DWORD handle, void *buffer, DWORD length);
    HSYNC BASSDEF(BASS_ChannelSetSync)(DWORD handle, DWORD type, QWORD param, SYNCPROC *proc, void *user);
    BOOL BASSDEF(BASS_ChannelRemoveSync)(DWORD handle, HSYNC sync);
    HDSP BASSDEF(BASS_ChannelSetDSP)(DWORD handle, DSPPROC *proc, void *user, int priority);
    BOOL BASSDEF(BASS_ChannelRemoveDSP)(DWORD handle, HDSP dsp);
    BOOL BASSDEF(BASS_ChannelSetLink)(DWORD handle, DWORD chan);
    BOOL BASSDEF(BASS_ChannelRemoveLink)(DWORD handle, DWORD chan);
    HFX BASSDEF(BASS_ChannelSetFX)(DWORD handle, DWORD type, int priority);
    BOOL BASSDEF(BASS_ChannelRemoveFX)(DWORD handle, HFX fx);
    
    BOOL BASSDEF(BASS_FXSetParameters)(HFX handle, const void *params);
    BOOL BASSDEF(BASS_FXGetParameters)(HFX handle, void *params);
    BOOL BASSDEF(BASS_FXReset)(HFX handle);
    BOOL BASSDEF(BASS_FXSetPriority)(HFX handle, int priority);
    
#ifdef __cplusplus
}

#if defined(_WIN32) && !defined(NOBASSOVERLOADS)
static inline HPLUGIN BASS_PluginLoad(const WCHAR *file, DWORD flags)
{
    return BASS_PluginLoad((const char*)file, flags|BASS_UNICODE);
}

static inline HMUSIC BASS_MusicLoad(BOOL mem, const WCHAR *file, QWORD offset, DWORD length, DWORD flags, DWORD freq)
{
    return BASS_MusicLoad(mem, (const void*)file, offset, length, flags|BASS_UNICODE, freq);
}

static inline HSAMPLE BASS_SampleLoad(BOOL mem, const WCHAR *file, QWORD offset, DWORD length, DWORD max, DWORD flags)
{
    return BASS_SampleLoad(mem, (const void*)file, offset, length, max, flags|BASS_UNICODE);
}

static inline HSTREAM BASS_StreamCreateFile(BOOL mem, const WCHAR *file, QWORD offset, QWORD length, DWORD flags)
{
    return BASS_StreamCreateFile(mem, (const void*)file, offset, length, flags|BASS_UNICODE);
}

static inline HSTREAM BASS_StreamCreateURL(const WCHAR *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user)
{
    return BASS_StreamCreateURL((const char*)url, offset, flags|BASS_UNICODE, proc, user);
}

static inline BOOL BASS_SetConfigPtr(DWORD option, const WCHAR *value)
{
    return BASS_SetConfigPtr(option|BASS_UNICODE, (const void*)value);
}
#endif
#endif

#endif

/*===========================================================================
 BASS_FX 2.4 - Copyright (c) 2002-2014 (: JOBnik! :) [Arthur Aminov, ISRAEL]
 [http://www.jobnik.org]
 
 bugs/suggestions/questions:
 forum  : http://www.un4seen.com/forum/?board=1
 http://www.jobnik.org/smforum
 e-mail : bass_fx@jobnik.org
 --------------------------------------------------
 
 NOTE: This header will work only with BASS_FX version 2.4.11.1
 Check www.un4seen.com or www.jobnik.org for any later versions.
 
 * Requires BASS 2.4 (available at http://www.un4seen.com)
 ===========================================================================*/

#ifndef BASS_FX_H
#define BASS_FX_H

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASS_FXDEF
#define BASS_FXDEF(f) WINAPI f
#endif
    
    // BASS_CHANNELINFO types
#define BASS_CTYPE_STREAM_TEMPO		0x1f200
#define BASS_CTYPE_STREAM_REVERSE	0x1f201
    
    // Tempo / Reverse / BPM / Beat flag
#define BASS_FX_FREESOURCE			0x10000	// Free the source handle as well?
    
    // BASS_FX Version
    DWORD BASS_FXDEF(BASS_FX_GetVersion)();
    
    /*===========================================================================
     DSP (Digital Signal Processing)
     ===========================================================================*/
    
    /*
     Multi-channel order of each channel is as follows:
     3 channels       left-front, right-front, center.
     4 channels       left-front, right-front, left-rear/side, right-rear/side.
     5 channels       left-front, right-front, center, left-rear/side, right-rear/side.
     6 channels (5.1) left-front, right-front, center, LFE, left-rear/side, right-rear/side.
     8 channels (7.1) left-front, right-front, center, LFE, left-rear/side, right-rear/side, left-rear center, right-rear center.
     */
    
    // DSP channels flags
#define BASS_BFX_CHANALL	-1				// all channels at once (as by default)
#define BASS_BFX_CHANNONE	0				// disable an effect for all channels
#define BASS_BFX_CHAN1		1				// left-front channel
#define BASS_BFX_CHAN2		2				// right-front channel
#define BASS_BFX_CHAN3		4				// see above info
#define BASS_BFX_CHAN4		8				// see above info
#define BASS_BFX_CHAN5		16				// see above info
#define BASS_BFX_CHAN6		32				// see above info
#define BASS_BFX_CHAN7		64				// see above info
#define BASS_BFX_CHAN8		128				// see above info
    
    // if you have more than 8 channels (7.1), use this macro
#define BASS_BFX_CHANNEL_N(n) (1<<((n)-1))
    
    // DSP effects
    enum {
        BASS_FX_BFX_ROTATE = 0x10000,			// A channels volume ping-pong	/ multi channel
        BASS_FX_BFX_ECHO,						// Echo							/ 2 channels max	(deprecated)
        BASS_FX_BFX_FLANGER,					// Flanger						/ multi channel		(deprecated)
        BASS_FX_BFX_VOLUME,						// Volume						/ multi channel
        BASS_FX_BFX_PEAKEQ,						// Peaking Equalizer			/ multi channel
        BASS_FX_BFX_REVERB,						// Reverb						/ 2 channels max	(deprecated)
        BASS_FX_BFX_LPF,						// Low Pass Filter 24dB			/ multi channel		(deprecated)
        BASS_FX_BFX_MIX,						// Swap, remap and mix channels	/ multi channel
        BASS_FX_BFX_DAMP,						// Dynamic Amplification		/ multi channel
        BASS_FX_BFX_AUTOWAH,					// Auto Wah						/ multi channel
        BASS_FX_BFX_ECHO2,						// Echo 2						/ multi channel		(deprecated)
        BASS_FX_BFX_PHASER,						// Phaser						/ multi channel
        BASS_FX_BFX_ECHO3,						// Echo 3						/ multi channel		(deprecated)
        BASS_FX_BFX_CHORUS,						// Chorus/Flanger				/ multi channel
        BASS_FX_BFX_APF,						// All Pass Filter				/ multi channel		(deprecated)
        BASS_FX_BFX_COMPRESSOR,					// Compressor					/ multi channel		(deprecated)
        BASS_FX_BFX_DISTORTION,					// Distortion					/ multi channel
        BASS_FX_BFX_COMPRESSOR2,				// Compressor 2					/ multi channel
        BASS_FX_BFX_VOLUME_ENV,					// Volume envelope				/ multi channel
        BASS_FX_BFX_BQF,						// BiQuad filters				/ multi channel
        BASS_FX_BFX_ECHO4,						// Echo	4						/ multi channel
        BASS_FX_BFX_PITCHSHIFT,					// Pitch shift using FFT		/ multi channel		(not available on mobile)
        BASS_FX_BFX_FREEVERB					// Reverb using "Freeverb" algo	/ multi channel
    };
    
    /*
     Deprecated effects in 2.4.10 version:
     ------------------------------------
     BASS_FX_BFX_ECHO		-> use BASS_FX_BFX_ECHO4
     BASS_FX_BFX_ECHO2		-> use BASS_FX_BFX_ECHO4
     BASS_FX_BFX_ECHO3		-> use BASS_FX_BFX_ECHO4
     BASS_FX_BFX_REVERB		-> use BASS_FX_BFX_FREEVERB
     BASS_FX_BFX_FLANGER		-> use BASS_FX_BFX_CHORUS
     BASS_FX_BFX_COMPRESSOR	-> use BASS_FX_BFX_COMPRESSOR2
     BASS_FX_BFX_APF			-> use BASS_FX_BFX_BQF with BASS_BFX_BQF_ALLPASS filter
     BASS_FX_BFX_LPF			-> use 2x BASS_FX_BFX_BQF with BASS_BFX_BQF_LOWPASS filter and appropriate fQ values
     */
    
    // Rotate
    typedef struct {
        float fRate;							// rotation rate/speed in Hz (A negative rate can be used for reverse direction)
        int   lChannel;							// BASS_BFX_CHANxxx flag/s (supported only even number of channels)
    } BASS_BFX_ROTATE;
    
    // Echo (deprecated)
    typedef struct {
        float fLevel;							// [0....1....n] linear
        int   lDelay;							// [1200..30000]
    } BASS_BFX_ECHO;
    
    // Flanger (deprecated)
    typedef struct {
        float fWetDry;							// [0....1....n] linear
        float fSpeed;							// [0......0.09]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_FLANGER;
    
    // Volume
    typedef struct {
        int   lChannel;							// BASS_BFX_CHANxxx flag/s or 0 for global volume control
        float fVolume;							// [0....1....n] linear
    } BASS_BFX_VOLUME;
    
    // Peaking Equalizer
    typedef struct {
        int   lBand;							// [0...............n] more bands means more memory & cpu usage
        float fBandwidth;						// [0.1...........<10] in octaves - fQ is not in use (Bandwidth has a priority over fQ)
        float fQ;								// [0...............1] the EE kinda definition (linear) (if Bandwidth is not in use)
        float fCenter;							// [1Hz..<info.freq/2] in Hz
        float fGain;							// [-15dB...0...+15dB] in dB (can be above/below these limits)
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_PEAKEQ;
    
    // Reverb (deprecated)
    typedef struct {
        float fLevel;							// [0....1....n] linear
        int   lDelay;							// [1200..10000]
    } BASS_BFX_REVERB;
    
    // Low Pass Filter (deprecated)
    typedef struct {
        float fResonance;						// [0.01...........10]
        float fCutOffFreq;						// [1Hz...info.freq/2] cutoff frequency
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_LPF;
    
    // Swap, remap and mix
    typedef struct {
        const int *lChannel;					// an array of channels to mix using BASS_BFX_CHANxxx flag/s (lChannel[0] is left channel...)
    } BASS_BFX_MIX;
    
    // Dynamic Amplification
    typedef struct {
        float fTarget;							// target volume level						[0<......1] linear
        float fQuiet; 							// quiet  volume level						[0.......1] linear
        float fRate;							// amp adjustment rate						[0.......1] linear
        float fGain;							// amplification level						[0...1...n] linear
        float fDelay;							// delay in seconds before increasing level	[0.......n] linear
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_DAMP;
    
    // Auto Wah
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2......2]
        float fWetMix;							// wet (affected) signal mix				[-2......2]
        float fFeedback;						// output signal to feed back into input	[-1......1]
        float fRate;							// rate of sweep in cycles per second		[0<....<10]
        float fRange;							// sweep range in octaves					[0<....<10]
        float fFreq;							// base frequency of sweep Hz				[0<...1000]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_AUTOWAH;
    
    // Echo 2 (deprecated)
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2......2]
        float fWetMix;							// wet (affected) signal mix				[-2......2]
        float fFeedback;						// output signal to feed back into input	[-1......1]
        float fDelay;							// delay sec								[0<......n]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_ECHO2;
    
    // Phaser
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2......2]
        float fWetMix;							// wet (affected) signal mix				[-2......2]
        float fFeedback;						// output signal to feed back into input	[-1......1]
        float fRate;							// rate of sweep in cycles per second		[0<....<10]
        float fRange;							// sweep range in octaves					[0<....<10]
        float fFreq;							// base frequency of sweep					[0<...1000]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_PHASER;
    
    // Echo 3 (deprecated)
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2......2]
        float fWetMix;							// wet (affected) signal mix				[-2......2]
        float fDelay;							// delay sec								[0<......n]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_ECHO3;
    
    // Chorus/Flanger
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2......2]
        float fWetMix;							// wet (affected) signal mix				[-2......2]
        float fFeedback;						// output signal to feed back into input	[-1......1]
        float fMinSweep;						// minimal delay ms							[0<...6000]
        float fMaxSweep;						// maximum delay ms							[0<...6000]
        float fRate;							// rate ms/s								[0<...1000]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_CHORUS;
    
    // All Pass Filter (deprecated)
    typedef struct {
        float fGain;							// reverberation time						[-1=<..<=1]
        float fDelay;							// delay sec								[0<....<=n]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_APF;
    
    // Compressor (deprecated)
    typedef struct {
        float fThreshold;						// compressor threshold						[0<=...<=1]
        float fAttacktime;						// attack time ms							[0<.<=1000]
        float fReleasetime;						// release time ms							[0<.<=5000]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_COMPRESSOR;
    
    // Distortion
    typedef struct {
        float fDrive;							// distortion drive							[0<=...<=5]
        float fDryMix;							// dry (unaffected) signal mix				[-5<=..<=5]
        float fWetMix;							// wet (affected) signal mix				[-5<=..<=5]
        float fFeedback;						// output signal to feed back into input	[-1<=..<=1]
        float fVolume;							// distortion volume						[0=<...<=2]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_DISTORTION;
    
    // Compressor 2
    typedef struct {
        float fGain;							// output gain of signal after compression	[-60....60] in dB
        float fThreshold;						// point at which compression begins		[-60.....0] in dB
        float fRatio;							// compression ratio						[1.......n]
        float fAttack;							// attack time in ms						[0.01.1000]
        float fRelease;							// release time in ms						[0.01.5000]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_COMPRESSOR2;
    
    // Volume envelope
    typedef struct {
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
        int   lNodeCount;						// number of nodes
        const struct BASS_BFX_ENV_NODE *pNodes;	// the nodes
        BOOL  bFollow;							// follow source position
    } BASS_BFX_VOLUME_ENV;
    
#pragma pack(push,4)
    typedef struct BASS_BFX_ENV_NODE {
        double pos;								// node position in seconds (1st envelope node must be at position 0)
        float  val;								// node value
    } BASS_BFX_ENV_NODE;
#pragma pack(pop)
    
    // BiQuad Filters
    enum {
        BASS_BFX_BQF_LOWPASS,
        BASS_BFX_BQF_HIGHPASS,
        BASS_BFX_BQF_BANDPASS,					// constant 0 dB peak gain
        BASS_BFX_BQF_BANDPASS_Q,				// constant skirt gain, peak gain = Q
        BASS_BFX_BQF_NOTCH,
        BASS_BFX_BQF_ALLPASS,
        BASS_BFX_BQF_PEAKINGEQ,
        BASS_BFX_BQF_LOWSHELF,
        BASS_BFX_BQF_HIGHSHELF
    };
    
    typedef struct {
        int   lFilter;							// BASS_BFX_BQF_xxx filter types
        float fCenter;							// [1Hz..<info.freq/2] Cutoff (central) frequency in Hz
        float fGain;							// [-15dB...0...+15dB] Used only for PEAKINGEQ and Shelving filters in dB (can be above/below these limits)
        float fBandwidth;						// [0.1...........<10] Bandwidth in octaves (fQ is not in use (fBandwidth has a priority over fQ))
        // 						(between -3 dB frequencies for BANDPASS and NOTCH or between midpoint
        // 						(fGgain/2) gain frequencies for PEAKINGEQ)
        float fQ;								// [0.1.............1] The EE kinda definition (linear) (if fBandwidth is not in use)
        float fS;								// [0.1.............1] A "shelf slope" parameter (linear) (used only with Shelving filters)
        // 						when fS = 1, the shelf slope is as steep as you can get it and remain monotonically
        // 						increasing or decreasing gain with frequency.
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_BQF;
    
    // Echo 4
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[-2.......2]
        float fWetMix;							// wet (affected) signal mix				[-2.......2]
        float fFeedback;						// output signal to feed back into input	[-1.......1]
        float fDelay;							// delay sec								[0<.......n]
        BOOL  bStereo;							// echo adjoining channels to each other	[TRUE/FALSE]
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_ECHO4;
    
    // Pitch shift (not available on mobile)
    typedef struct {
        float fPitchShift;						// A factor value which is between 0.5 (one octave down) and 2 (one octave up) (1 won't change the pitch) [1 default]
        // (fSemitones is not in use, fPitchShift has a priority over fSemitones)
        float fSemitones;						// Semitones (0 won't change the pitch) [0 default]
        long  lFFTsize;							// Defines the FFT frame size used for the processing. Typical values are 1024, 2048 and 4096 [2048 default]
        // It may be any value <= 8192 but it MUST be a power of 2
        long  lOsamp;							// Is the STFT oversampling factor which also determines the overlap between adjacent STFT frames [8 default]
        // It should at least be 4 for moderate scaling ratios. A value of 32 is recommended for best quality (better quality = higher CPU usage)
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_PITCHSHIFT;
    
    // Freeverb
#define BASS_BFX_FREEVERB_MODE_FREEZE	1
    
    typedef struct {
        float fDryMix;							// dry (unaffected) signal mix				[0........1], def. 0
        float fWetMix;							// wet (affected) signal mix				[0........3], def. 1.0f
        float fRoomSize;						// room size								[0........1], def. 0.5f
        float fDamp;							// damping									[0........1], def. 0.5f
        float fWidth;							// stereo width								[0........1], def. 1
        DWORD lMode;							// 0 or BASS_BFX_FREEVERB_MODE_FREEZE, def. 0 (no freeze)
        int   lChannel;							// BASS_BFX_CHANxxx flag/s
    } BASS_BFX_FREEVERB;
    
    /*===========================================================================
     set dsp fx			- BASS_ChannelSetFX
     remove dsp fx		- BASS_ChannelRemoveFX
     set parameters		- BASS_FXSetParameters
     retrieve parameters - BASS_FXGetParameters
     reset the state		- BASS_FXReset
     ===========================================================================*/
    
    /*===========================================================================
     Tempo, Pitch scaling and Sample rate changers
     ===========================================================================*/
    
    // NOTE: Enable Tempo supported flags in BASS_FX_TempoCreate and the others to source handle.
    
    // tempo attributes (BASS_ChannelSet/GetAttribute)
    enum {
        BASS_ATTRIB_TEMPO = 0x10000,
        BASS_ATTRIB_TEMPO_PITCH,
        BASS_ATTRIB_TEMPO_FREQ
    };
    
    // tempo attributes options
    enum {
        BASS_ATTRIB_TEMPO_OPTION_USE_AA_FILTER = 0x10010,	// TRUE (default) / FALSE (default for multi-channel on mobile devices for lower CPU usage)
        BASS_ATTRIB_TEMPO_OPTION_AA_FILTER_LENGTH,			// 32 default (8 .. 128 taps)
        BASS_ATTRIB_TEMPO_OPTION_USE_QUICKALGO,				// TRUE (default on mobile devices for loswer CPU usage) / FALSE (default)
        BASS_ATTRIB_TEMPO_OPTION_SEQUENCE_MS,				// 82 default, 0 = automatic
        BASS_ATTRIB_TEMPO_OPTION_SEEKWINDOW_MS,				// 28 default, 0 = automatic
        BASS_ATTRIB_TEMPO_OPTION_OVERLAP_MS,				// 8  default
        BASS_ATTRIB_TEMPO_OPTION_PREVENT_CLICK				// TRUE / FALSE (default)
    };
    
    // tempo algorithm flags
#define BASS_FX_TEMPO_ALGO_LINEAR		0x200
#define BASS_FX_TEMPO_ALGO_CUBIC		0x400			// default
#define BASS_FX_TEMPO_ALGO_SHANNON		0x800
    
    HSTREAM BASS_FXDEF(BASS_FX_TempoCreate)(DWORD chan, DWORD flags);
    DWORD   BASS_FXDEF(BASS_FX_TempoGetSource)(HSTREAM chan);
    float   BASS_FXDEF(BASS_FX_TempoGetRateRatio)(HSTREAM chan);
    
    /*===========================================================================
     Reverse playback
     ===========================================================================*/
    
    // NOTES: 1. MODs won't load without BASS_MUSIC_PRESCAN flag.
    //		  2. Enable Reverse supported flags in BASS_FX_ReverseCreate and the others to source handle.
    
    // reverse attribute (BASS_ChannelSet/GetAttribute)
#define BASS_ATTRIB_REVERSE_DIR 0x11000
    
    // playback directions
#define BASS_FX_RVS_REVERSE -1
#define BASS_FX_RVS_FORWARD 1
    
    HSTREAM BASS_FXDEF(BASS_FX_ReverseCreate)(DWORD chan, float dec_block, DWORD flags);
    DWORD   BASS_FXDEF(BASS_FX_ReverseGetSource)(HSTREAM chan);
    
    /*===========================================================================
     BPM (Beats Per Minute)
     ===========================================================================*/
    
    // bpm flags
#define BASS_FX_BPM_BKGRND	1	// if in use, then you can do other processing while detection's in progress. Available only in Windows platforms (BPM/Beat)
#define BASS_FX_BPM_MULT2	2	// if in use, then will auto multiply bpm by 2 (if BPM < minBPM*2)
    
    // translation options (deprecated)
    enum {
        BASS_FX_BPM_TRAN_X2,		// multiply the original BPM value by 2 (may be called only once & will change the original BPM as well!)
        BASS_FX_BPM_TRAN_2FREQ,		// BPM value to Frequency
        BASS_FX_BPM_TRAN_FREQ2,		// Frequency to BPM value
        BASS_FX_BPM_TRAN_2PERCENT,	// BPM value to Percents
        BASS_FX_BPM_TRAN_PERCENT2	// Percents to BPM value
    };
    
    typedef void (CALLBACK BPMPROC)(DWORD chan, float bpm, void *user);
    typedef void (CALLBACK BPMPROGRESSPROC)(DWORD chan, float percent, void *user);
    typedef BPMPROGRESSPROC BPMPROCESSPROC;	// back-compatibility
    
    float BASS_FXDEF(BASS_FX_BPM_DecodeGet)(DWORD chan, double startSec, double endSec, DWORD minMaxBPM, DWORD flags, BPMPROGRESSPROC *proc, void *user);
    BOOL  BASS_FXDEF(BASS_FX_BPM_CallbackSet)(DWORD handle, BPMPROC *proc, double period, DWORD minMaxBPM, DWORD flags, void *user);
    BOOL  BASS_FXDEF(BASS_FX_BPM_CallbackReset)(DWORD handle);
    float BASS_FXDEF(BASS_FX_BPM_Translate)(DWORD handle, float val2tran, DWORD trans);	// deprecated
    BOOL  BASS_FXDEF(BASS_FX_BPM_Free)(DWORD handle);
    
    /*===========================================================================
     Beat position trigger
     ===========================================================================*/
    
    typedef void (CALLBACK BPMBEATPROC)(DWORD chan, double beatpos, void *user);
    
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatCallbackSet)(DWORD handle, BPMBEATPROC *proc, void *user);
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatCallbackReset)(DWORD handle);
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatDecodeGet)(DWORD chan, double startSec, double endSec, DWORD flags, BPMBEATPROC *proc, void *user);
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatSetParameters)(DWORD handle, float bandwidth, float centerfreq, float beat_rtime);
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatGetParameters)(DWORD handle, float *bandwidth, float *centerfreq, float *beat_rtime);
    BOOL BASS_FXDEF(BASS_FX_BPM_BeatFree)(DWORD handle);
    
    /*===========================================================================
     Macros
     ===========================================================================*/
    
    // translate linear level to logarithmic dB
#define BASS_BFX_Linear2dB(level) (20*log10(level))
    
    // translate logarithmic dB level to linear
#define BASS_BFX_dB2Linear(dB) pow(10,(dB)/20)
    
#ifdef __cplusplus
}
#endif

#endif

#ifndef BASSAPE_H
#define BASSAPE_H

#include "bass.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSAPEDEF
#define BASSAPEDEF(f) WINAPI f
#endif
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_APE	0x10700
    
    
    HSTREAM BASSAPEDEF(BASS_APE_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSAPEDEF(BASS_APE_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user);
    
#ifdef __cplusplus
}
#endif

#endif

#ifndef BASSTTA_H
#define BASSTTA_H

#include "bass.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSTTADEF
#define BASSTTADEF(f) WINAPI f
#endif
    
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_TTA	0x10f00
    
    
    HSTREAM BASSTTADEF(BASS_TTA_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSTTADEF(BASS_TTA_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user);
    
#ifdef __cplusplus
}
#endif

#endif

#ifndef BASSMPC_H
#define BASSMPC_H

#include "bass.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSMPCDEF
#define BASSMPCDEF(f) WINAPI f
#endif
    
    // Additional tags available from BASS_StreamGetTags
#define BASS_TAG_APE		6	// APE tags
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_MPC	0x10a00
    
    
    HSTREAM BASSMPCDEF(BASS_MPC_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSMPCDEF(BASS_MPC_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user);
    HSTREAM BASSMPCDEF(BASS_MPC_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *proc, void *user);
    
#ifdef __cplusplus
}
#endif

#endif

/*
	BASSmix 2.4 C/C++ header file
	Copyright (c) 2005-2015 Un4seen Developments Ltd.
 
	See the BASSMIX.CHM file for more detailed documentation
 */

#ifndef BASSMIX_H
#define BASSMIX_H

#include "bass.h"

#if BASSVERSION!=0x204
#error conflicting BASS and BASSmix versions
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSMIXDEF
#define BASSMIXDEF(f) WINAPI f
#endif
    
    // additional BASS_SetConfig option
#define BASS_CONFIG_MIXER_BUFFER	0x10601
#define BASS_CONFIG_MIXER_POSEX		0x10602
#define BASS_CONFIG_SPLIT_BUFFER	0x10610
    
    // BASS_Mixer_StreamCreate flags
#define BASS_MIXER_END			0x10000	// end the stream when there are no sources
#define BASS_MIXER_NONSTOP		0x20000	// don't stall when there are no sources
#define BASS_MIXER_RESUME		0x1000	// resume stalled immediately upon new/unpaused source
#define BASS_MIXER_POSEX		0x2000	// enable BASS_Mixer_ChannelGetPositionEx support
    
    // source flags
#define BASS_MIXER_BUFFER		0x2000	// buffer data for BASS_Mixer_ChannelGetData/Level
#define BASS_MIXER_LIMIT		0x4000	// limit mixer processing to the amount available from this source
#define BASS_MIXER_MATRIX		0x10000	// matrix mixing
#define BASS_MIXER_PAUSE		0x20000	// don't process the source
#define BASS_MIXER_DOWNMIX		0x400000 // downmix to stereo/mono
#define BASS_MIXER_NORAMPIN		0x800000 // don't ramp-in the start
    
    // mixer attributes
#define BASS_ATTRIB_MIXER_LATENCY	0x15000
    
    // splitter flags
#define BASS_SPLIT_SLAVE		0x1000	// only read buffered data
    
    // envelope node
    typedef struct {
        QWORD pos;
        float value;
    } BASS_MIXER_NODE;
    
    // envelope types
#define BASS_MIXER_ENV_FREQ		1
#define BASS_MIXER_ENV_VOL		2
#define BASS_MIXER_ENV_PAN		3
#define BASS_MIXER_ENV_LOOP		0x10000 // FLAG: loop
    
    // additional sync type
#define BASS_SYNC_MIXER_ENVELOPE		0x10200
#define BASS_SYNC_MIXER_ENVELOPE_NODE	0x10201
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_MIXER	0x10800
#define BASS_CTYPE_STREAM_SPLIT	0x10801
    
    DWORD BASSMIXDEF(BASS_Mixer_GetVersion)();
    
    HSTREAM BASSMIXDEF(BASS_Mixer_StreamCreate)(DWORD freq, DWORD chans, DWORD flags);
    BOOL BASSMIXDEF(BASS_Mixer_StreamAddChannel)(HSTREAM handle, DWORD channel, DWORD flags);
    BOOL BASSMIXDEF(BASS_Mixer_StreamAddChannelEx)(HSTREAM handle, DWORD channel, DWORD flags, QWORD start, QWORD length);
    
    HSTREAM BASSMIXDEF(BASS_Mixer_ChannelGetMixer)(DWORD handle);
    DWORD BASSMIXDEF(BASS_Mixer_ChannelFlags)(DWORD handle, DWORD flags, DWORD mask);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelRemove)(DWORD handle);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelSetPosition)(DWORD handle, QWORD pos, DWORD mode);
    QWORD BASSMIXDEF(BASS_Mixer_ChannelGetPosition)(DWORD handle, DWORD mode);
    QWORD BASSMIXDEF(BASS_Mixer_ChannelGetPositionEx)(DWORD channel, DWORD mode, DWORD delay);
    DWORD BASSMIXDEF(BASS_Mixer_ChannelGetLevel)(DWORD handle);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelGetLevelEx)(DWORD handle, float *levels, float length, DWORD flags);
    DWORD BASSMIXDEF(BASS_Mixer_ChannelGetData)(DWORD handle, void *buffer, DWORD length);
    HSYNC BASSMIXDEF(BASS_Mixer_ChannelSetSync)(DWORD handle, DWORD type, QWORD param, SYNCPROC *proc, void *user);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelRemoveSync)(DWORD channel, HSYNC sync);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelSetMatrix)(DWORD handle, const void *matrix);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelSetMatrixEx)(DWORD handle, const void *matrix, float time);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelGetMatrix)(DWORD handle, void *matrix);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelSetEnvelope)(DWORD handle, DWORD type, const BASS_MIXER_NODE *nodes, DWORD count);
    BOOL BASSMIXDEF(BASS_Mixer_ChannelSetEnvelopePos)(DWORD handle, DWORD type, QWORD pos);
    QWORD BASSMIXDEF(BASS_Mixer_ChannelGetEnvelopePos)(DWORD handle, DWORD type, float *value);
    
    HSTREAM BASSMIXDEF(BASS_Split_StreamCreate)(DWORD channel, DWORD flags, int *chanmap);
    DWORD BASSMIXDEF(BASS_Split_StreamGetSource)(HSTREAM handle);
    DWORD BASSMIXDEF(BASS_Split_StreamGetSplits)(DWORD handle, HSTREAM *splits, DWORD count);
    BOOL BASSMIXDEF(BASS_Split_StreamReset)(DWORD handle);
    BOOL BASSMIXDEF(BASS_Split_StreamResetEx)(DWORD handle, DWORD offset);
    DWORD BASSMIXDEF(BASS_Split_StreamGetAvailable)(DWORD handle);
    
#ifdef __cplusplus
}
#endif

#endif

/*
	BASSDSD 2.4 C/C++ header file
	Copyright (c) 2014 Un4seen Developments Ltd.
 
	See the BASSDSD.CHM file for more detailed documentation
 */

#ifndef BASSDSD_H
#define BASSDSD_H

#include "bass.h"

#if BASSVERSION!=0x204
#error conflicting BASS and BASSDSD versions
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSDSDDEF
#define BASSDSDDEF(f) WINAPI f
#else
#define NOBASSDSDOVERLOADS
#endif
    
    // Additional BASS_SetConfig options
#define BASS_CONFIG_DSD_FREQ		0x10800
#define BASS_CONFIG_DSD_GAIN		0x10801
    
    // Additional BASS_DSD_StreamCreateFile/etc flags
#define BASS_DSD_RAW				0x200
#define BASS_DSD_DOP				0x400
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_DSD		0x11700
    
    // Additional tag types
#define BASS_TAG_DSD_ARTIST			0x13000 // DSDIFF artist : ASCII string
#define BASS_TAG_DSD_TITLE			0x13001 // DSDIFF title : ASCII string
#define BASS_TAG_DSD_COMMENT		0x13100 // + index, DSDIFF comment : TAG_DSD_COMMENT structure
    
#pragma pack(push,1)
    typedef struct {
        WORD timeStampYear;		// creation year
        BYTE timeStampMonth;	// creation month
        BYTE timeStampDay;		// creation day
        BYTE timeStampHour;		// creation hour
        BYTE timeStampMinutes;	// creation minutes
        WORD cmtType;			// comment type
        WORD cmtRef;			// comment reference
        DWORD count;			// string length
#if __GNUC__ && __GNUC__<3
        char commentText[0];	// text
#else
        char commentText[];		// text
#endif
    } TAG_DSD_COMMENT;
#pragma pack(pop)
    
    // Additional attributes
#define BASS_ATTRIB_DSD_GAIN		0x14000
#define BASS_ATTRIB_DSD_RATE		0x14001
    
    HSTREAM BASSDSDDEF(BASS_DSD_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags, DWORD freq);
    HSTREAM BASSDSDDEF(BASS_DSD_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user, DWORD freq);
    HSTREAM BASSDSDDEF(BASS_DSD_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user, DWORD freq);
    
#ifdef __cplusplus
}

#if defined(_WIN32) && !defined(NOBASSDSDOVERLOADS)
static inline HSTREAM BASS_DSD_StreamCreateFile(BOOL mem, const WCHAR *file, QWORD offset, QWORD length, DWORD flags, DWORD freq)
{
    return BASS_DSD_StreamCreateFile(mem, (const void*)file, offset, length, flags|BASS_UNICODE, freq);
}

static inline HSTREAM BASS_DSD_StreamCreateURL(const WCHAR *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user, DWORD freq)
{
    return BASS_DSD_StreamCreateURL((const char*)url, offset, flags|BASS_UNICODE, proc, user, freq);
}
#endif
#endif

#endif

/*
	BASSWV 2.4 C/C++ header file
	Copyright (c) 2007-2013 Un4seen Developments Ltd.
 
	See the BASSWV.CHM file for more detailed documentation
 */

#ifndef BASSWV_H
#define BASSWV_H

#if BASSVERSION!=0x204
#error conflicting BASS and BASSWV versions
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSWVDEF
#define BASSWVDEF(f) WINAPI f
#endif
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_WV	0x10500
    
    HSTREAM BASSWVDEF(BASS_WV_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSWVDEF(BASS_WV_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user);
    HSTREAM BASSWVDEF(BASS_WV_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user);
    
#ifdef __cplusplus
}

#ifdef _WIN32
static inline HSTREAM BASS_WV_StreamCreateFile(BOOL mem, const WCHAR *file, QWORD offset, QWORD length, DWORD flags)
{
    return BASS_WV_StreamCreateFile(mem, (const void*)file, offset, length, flags|BASS_UNICODE);
}

static inline HSTREAM BASS_WV_StreamCreateURL(const WCHAR *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user)
{
    return BASS_WV_StreamCreateURL((const char*)url, offset, flags|BASS_UNICODE, proc, user);
}
#endif
#endif

#endif

/*
	BASSFLAC 2.4 C/C++ header file
	Copyright (c) 2004-2013 Un4seen Developments Ltd.
 
	See the BASSFLAC.CHM file for more detailed documentation
 */

#ifndef BASSFLAC_H
#define BASSFLAC_H

#include "bass.h"

#if BASSVERSION!=0x204
#error conflicting BASS and BASSFLAC versions
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSFLACDEF
#define BASSFLACDEF(f) WINAPI f
#endif
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_FLAC		0x10900
#define BASS_CTYPE_STREAM_FLAC_OGG	0x10901
    
    // Additional tag types
#define BASS_TAG_FLAC_CUE			12		// cuesheet : TAG_FLAC_CUE structure
#define BASS_TAG_FLAC_PICTURE		0x12000	// + index #, picture : TAG_FLAC_PICTURE structure
    
    typedef struct {
        DWORD apic;			// ID3v2 "APIC" picture type
        const char *mime;	// mime type
        const char *desc;	// description
        DWORD width;
        DWORD height;
        DWORD depth;
        DWORD colors;
        DWORD length;		// data length
        const void *data;
    } TAG_FLAC_PICTURE;
    
    typedef struct {
        QWORD offset;			// index offset relative to track offset (samples)
        DWORD number;			// index number
    } TAG_FLAC_CUE_TRACK_INDEX;
    
    typedef struct {
        QWORD offset;			// track offset (samples)
        DWORD number;			// track number
        const char *isrc;		// ISRC
        DWORD flags;
        DWORD nindexes;			// number of indexes
        const TAG_FLAC_CUE_TRACK_INDEX *indexes; // the indexes
    } TAG_FLAC_CUE_TRACK;
    
    typedef struct {
        const char *catalog;	// media catalog number
        DWORD leadin;			// lead-in (samples)
        BOOL iscd;				// a CD?
        DWORD ntracks;			// number of tracks
        const TAG_FLAC_CUE_TRACK *tracks; // the tracks
    } TAG_FLAC_CUE;
    
    // TAG_FLAC_CUE_TRACK flags
#define TAG_FLAC_CUE_TRACK_DATA	1	// data track
#define TAG_FLAC_CUE_TRACK_PRE	2	// pre-emphasis
    
    HSTREAM BASSFLACDEF(BASS_FLAC_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSFLACDEF(BASS_FLAC_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user);
    HSTREAM BASSFLACDEF(BASS_FLAC_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user);
    
#ifdef __cplusplus
}

#ifdef _WIN32
static inline HSTREAM BASS_FLAC_StreamCreateFile(BOOL mem, const WCHAR *file, QWORD offset, QWORD length, DWORD flags)
{
    return BASS_FLAC_StreamCreateFile(mem, (const void*)file, offset, length, flags|BASS_UNICODE);
}

static inline HSTREAM BASS_FLAC_StreamCreateURL(const WCHAR *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user)
{
    return BASS_FLAC_StreamCreateURL((const char*)url, offset, flags|BASS_UNICODE, proc, user);
}
#endif
#endif

#endif

/*
	BASSOPUS 2.4 C/C++ header file
	Copyright (c) 2012-2015 Un4seen Developments Ltd.
 
	See the BASSOPUS.CHM file for more detailed documentation
 */

#ifndef BASSOPUS_H
#define BASSOPUS_H

#include "bass.h"

#if BASSVERSION!=0x204
#error conflicting BASS and BASSOPUS versions
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef BASSOPUSDEF
#define BASSOPUSDEF(f) WINAPI f
#endif
    
    // BASS_CHANNELINFO type
#define BASS_CTYPE_STREAM_OPUS		0x11200
    
    // Additional attributes
#define BASS_ATTRIB_OPUS_ORIGFREQ	0x13000
#define BASS_ATTRIB_OPUS_GAIN		0x13001
    
    HSTREAM BASSOPUSDEF(BASS_OPUS_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
    HSTREAM BASSOPUSDEF(BASS_OPUS_StreamCreateURL)(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user);
    HSTREAM BASSOPUSDEF(BASS_OPUS_StreamCreateFileUser)(DWORD system, DWORD flags, const BASS_FILEPROCS *procs, void *user);
    
#ifdef __cplusplus
}

#if defined(_WIN32) && !defined(NOBASSOVERLOADS)
static inline HSTREAM BASS_OPUS_StreamCreateFile(BOOL mem, const WCHAR *file, QWORD offset, QWORD length, DWORD flags)
{
    return BASS_OPUS_StreamCreateFile(mem, (const void*)file, offset, length, flags|BASS_UNICODE);
}

static inline HSTREAM BASS_OPUS_StreamCreateURL(const WCHAR *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user)
{
    return BASS_OPUS_StreamCreateURL((const char*)url, offset, flags|BASS_UNICODE, proc, user);
}
#endif
#endif

#endif

//////////////////////////////////////////////////////////////////////////
//
// tags.h - TAGS: Yet Another Tag Reading Library for BASS 2.3+
//
// Author: Wraith, 2k5-2k6
// Public domain. No warranty.
//
// (public)
//
// Abstract:    reads tags from given BASS handle, formats them according
//              to given format string and returns the resulting string.
//
// read tags-readme.txt for details
//

#ifndef _YATRL_H_W2348_H4232
#define _YATRL_H_W2348_H4232

#ifdef __cplusplus
extern "C" {
#endif
    
    // Current version. Just increments each release.
#define TAGS_VERSION 18
    
    // get the loaded version
    DWORD WINAPI TAGS_GetVersion();
    
    // enable UTF-8 encoding
    BOOL WINAPI TAGS_SetUTF8( BOOL enable );
    
    // main purpose of this library
    const char* WINAPI TAGS_Read( DWORD dwHandle, const char* fmt );
    const char* WINAPI TAGS_ReadEx( DWORD dwHandle, const char* fmt, DWORD tagtype, int codepage );
    
    // returns description of the last error.
    const char* WINAPI TAGS_GetLastErrorDesc();
    
#ifdef __cplusplus
}
#endif

#endif
