# VideoCapture
Capture the video's specific duration and save it as .png file

## How to use

Add the DLL in the x64/release directory
```C++
#pragma comment (lib, "Thumbnail.lib")
extern "C" __declspec (dllimport) int mkthumbnail(CString, CString, int, int, int);

int nrtn = mkthumbnail(sourceFolder, dstFolder, pngHeight, pngWidth, durationToCapture);
```

All the videos in the source folder will be captured.
It will capture the video of the duration you have set.
Captured images will be in dst folder.
You can decide png file's height and width.
