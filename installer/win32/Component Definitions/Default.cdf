[System DLLs]
SELECTED=Yes
FILENEED=CRITICAL
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<WINSYSDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=These components are System DLLs you might need in order to run FreeAmp.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=System DLLs
requiredby0=Program Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=Windows Operating System\Windows System Folder

[MetaData\ID3v1]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component  reads metadata in the ID3v1 format.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=ID3v1 MetaData
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Components]
component17=Portable Players\Rio PMP300
component9=Input & Output\Soundcard Output
component0=System DLLs
component1=MetaData\ID3v1
component10=Default Plugins
component2=MetaData\ID3v2
component11=Program Files
component3=Input & Output
component12=Input & Output\OBS Input
component4=MetaData
component13=Default Theme
component5=Input & Output\DirectSound Output
component14=Playlist Formats\M3U
component6=Playlist Formats\PLS
component15=Playlist Formats
component7=Input & Output\HTTP Input
component16=Portable Players
component8=Theme Tools

[MetaData]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
member0=MetaData\ID3v1
FTPLOCATION=
member1=MetaData\ID3v2
VISIBLE=Yes
DESCRIPTION=These components allow FreeAmp to read metadata stored within music files so it can display it during playback.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Input & Output]
SELECTED=Yes
FILENEED=HIGHLYRECOMMENDED
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
member0=Input & Output\HTTP Input
FTPLOCATION=
member1=Input & Output\OBS Input
VISIBLE=Yes
DESCRIPTION=These components allow FreeAmp to receive data from various sources and also to output audio to various destinations.
member2=Input & Output\Soundcard Output
member3=Input & Output\DirectSound Output
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination\Plugins

[MetaData\ID3v2]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component  reads metadata in the ID3v2 format.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=ID3v2 MetaData
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[TopComponents]
component0=Program Files
component1=Input & Output
component2=MetaData
component3=Portable Players
component4=Playlist Formats
component5=System DLLs
component6=Default Plugins
component7=Default Theme
component8=Theme Tools

[Input & Output\DirectSound Output]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component allows FreeAmp to play audio through your sound card via DirectSound on Windows 95 and 98.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Direct Sound Output
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination\Plugins

[SetupType]
setuptype0=Compact
setuptype1=Typical
setuptype2=Custom

[Input & Output\HTTP Input]
SELECTED=Yes
FILENEED=HIGHLYRECOMMENDED
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component allows FreeAmp to receive data from HTTP and ShoutCast servers.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=HTTP Input
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination\Plugins

[Playlist Formats\PLS]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=PLS Playlist
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Theme Tools]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Tools
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component installs instructions on how to create your own FreeAmp themes and all necessary utilities.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Theme Tools
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[SetupTypeItem-Compact]
item5=Default Theme
Comment=
item0=System DLLs
item1=Input & Output
item2=Default Plugins
item3=Input & Output\Soundcard Output
Descrip=This choice will install only the minimum number of plugins needed by FreeAmp to run.
item4=Program Files
DisplayText=

[Default Plugins]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=Base set of plugins that are required for the application to run.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Default Plugins
requiredby0=Program Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Input & Output\Soundcard Output]
SELECTED=Yes
FILENEED=HIGHLYRECOMMENDED
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component allows FreeAmp to play audio through your sound card.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Soundcard Output
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination\Plugins

[Program Files]
required0=System DLLs
SELECTED=Yes
FILENEED=CRITICAL
required1=Default Plugins
HTTPLOCATION=
STATUS=
required2=Default Theme
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component is the core FreeAmp executable.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Program Executable Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[SetupTypeItem-Custom]
item5=Playlist Formats\PLS
item10=Input & Output\Soundcard Output
item6=Decoders\Xing MP3
item11=Default Plugins
item7=Input & Output\HTTP Input
item12=Program Files
item8=User Interfaces\FreeAmp
item13=Input & Output\OBS Input
item9=Theme Tools
item14=Playlist Formats\M3U
item15=Default Theme
item16=Portable Players
item17=Playlist Formats
Comment=
item18=Portable Players\Rio PMP300
item0=System DLLs
item1=MetaData\ID3v1
item2=MetaData\ID3v2
item3=Input & Output
Descrip=This choice allows you to select the plugins you would like to install.
item4=MetaData
DisplayText=

[Input & Output\OBS Input]
SELECTED=Yes
FILENEED=HIGHLYRECOMMENDED
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component allows FreeAmp to receive data from Obsequiem and other RTP compliant servers.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=OBS Input
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination\Plugins

[Playlist Formats\M3U]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=These components allow FreeAmp to read and write playlists in the M3U format.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=M3U Playlist
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Default Theme]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Themes
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This is the default theme file for FreeAmp and defines how it looks. Head over to http://www.freeamp.org to check out other cool themes that are available for download.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=Default Theme
requiredby0=Program Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Info]
Type=CompDef
Version=1.00.000
Name=

[SetupTypeItem-Typical]
item5=Input & Output\DirectSound Output
item10=Theme Tools
item6=Playlist Formats\PLS
item11=Input & Output\Soundcard Output
item7=Decoders\Xing MP3
item12=Default Plugins
item8=Input & Output\HTTP Input
item13=Program Files
item9=User Interfaces\FreeAmp
item14=Input & Output\OBS Input
item15=Playlist Formats\M3U
item16=Default Theme
item17=Portable Players
Comment=
item18=Playlist Formats
item19=Portable Players\Rio PMP300
item0=System DLLs
item1=MetaData\ID3v1
item2=MetaData\ID3v2
item3=Input & Output
Descrip=This choice will install the FreeAmp program and all plugins.
item4=MetaData
DisplayText=

[Portable Players]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
member0=Portable Players\Rio PMP300
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=These components allow FreeAmp to manage the music on your portable audio player.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Playlist Formats]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
member0=Playlist Formats\M3U
FTPLOCATION=
member1=Playlist Formats\PLS
VISIBLE=Yes
DESCRIPTION=These components allow FreeAmp to read and write playlists in various formats.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Portable Players\Rio PMP300]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>\Plugins
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component knows how to communicate with the Diamond Rio PMP300.
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=PMP300 Portable
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

