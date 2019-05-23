#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <atlstr.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <comdef.h>
#include <io.h>

using namespace cv;
using namespace std;

extern "C" __declspec(dllexport) int mkthumbnail(CString srcpath, CString dstpath, int total, int width, int height) {
	WIN32_FIND_DATA data;
	int result = 1;
	HANDLE handle = FindFirstFile(srcpath+L"\\*", &data);

	if (handle == INVALID_HANDLE_VALUE)
	{
		return -2;
	}

	time_t start, end;
	int count = 0;

	CString tmppath = srcpath;
	CString Lsrcpath, Ldstpath;

	int Ltotal = (total * 1000) + 1000;
	do {
		int i = 1;
		count++;
		_bstr_t b(data.cFileName);
		char* filestr = b;
		Lsrcpath = tmppath + L"\\";
		Lsrcpath += data.cFileName;

		Ldstpath = dstpath + L"\\" + data.cFileName + L".png";

		char* cpath = new char[Lsrcpath.GetLength()];
		char* cdstpath = new char[Ldstpath.GetLength()];
		strcpy(cpath, CT2A(Lsrcpath));
		strcpy(cdstpath, CT2A(Ldstpath));

		if (count > 2) {
			VideoCapture cap(cpath);
			if (!cap.isOpened()) {
				cout << "Error opening video stream" << endl;
				return -1;
			}
			cap.set(CAP_PROP_POS_MSEC, Ltotal);
			cap.set(CAP_PROP_BUFFERSIZE, 2);
			string strFilePath = "";

			Mat frame;
			cap >> frame;
			stringstream ss;

			ss << cdstpath;
			string s_ = ss.str();

			Mat img_resize;
			resize(frame, img_resize, Size(width, height));

			imwrite(s_, img_resize);
		}
		cpath = NULL;
		cdstpath = NULL;
		delete[] cpath;
		delete[] cdstpath;
	} while (FindNextFile(handle, &data));
	return 0;
}