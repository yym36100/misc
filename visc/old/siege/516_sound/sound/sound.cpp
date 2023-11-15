#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <math.h>

typedef struct wavFileHeader
{
	long chunkId;           //"RIFF" (0x52,0x49,0x46,0x46)
	long chunkSize;         // (fileSize - 8)  - could also be thought of as bytes of data in file following this field (bytesRemaining)
	long riffType;          // "WAVE" (0x57415645)
};

typedef struct fmtChunk
{
	long chunkId;                       // "fmt " - (0x666D7420)
	long chunkDataSize;                 // 16 + extra format bytes
	short compressionCode;              // 1 - 65535
	short numChannels;                  // 1 - 65535
	long sampleRate;                    // 1 - 0xFFFFFFFF
	long avgBytesPerSec;                // 1 - 0xFFFFFFFF
	short blockAlign;                   // 1 - 65535
	short significantBitsPerSample;     // 2 - 65535
	short extraFormatBytes;             // 0 - 65535
};

typedef struct wavChunk
{
	long chunkId;
	long chunkDataSize;
};



char *readFileData(char *szFilename, long &dataLengthOut)
{
	FILE *fp = fopen(szFilename, "rb");
	long len;
	char *buffer;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = (char*) calloc(1, len+1);
	fread(buffer, 1, len, fp);
	fclose(fp);
	dataLengthOut = len;
	return buffer;
}

void parseWav(char *data)
{
	long *mPtr;
	long *tmpPtr;

	char *buffer;

	WAVEFORMATEX wf;
	volatile WAVEHDR wh;
	HWAVEOUT hWaveOut;

	fmtChunk mFmtChunk;
	wavChunk mDataChunk;

	mPtr = (long*)data;

	if ( mPtr[0] == 0x46464952) //  little endian check for 'RIFF'
	{
		mPtr += 3;
		if (mPtr[0] == 0x20746D66)  // little endian for "fmt "
		{
			// printf("Format chunk found\n");

			tmpPtr = mPtr;
			memcpy(&mFmtChunk, tmpPtr, sizeof(mFmtChunk));
			tmpPtr += 6;
			//tmpPtr += mFmtChunk.chunkDataSize;

			mPtr = (long*)tmpPtr;
			if (mPtr[0] == 0x61746164)        // little endian for "data"
			{
				printf("Data chunk found\n");


				tmpPtr = mPtr;
				memcpy(&mDataChunk, tmpPtr, sizeof(mDataChunk));
				mPtr += 2;

				buffer = (char*) malloc(mDataChunk.chunkDataSize);
				memcpy(buffer, mPtr, mDataChunk.chunkDataSize);

				printf("sampleRate: %d\n", mFmtChunk.sampleRate);

				wf.wFormatTag = mFmtChunk.compressionCode;
				wf.nChannels = mFmtChunk.numChannels;
				wf.nSamplesPerSec = mFmtChunk.sampleRate;
				wf.nAvgBytesPerSec = mFmtChunk.avgBytesPerSec;
				wf.nBlockAlign = mFmtChunk.blockAlign;
				wf.wBitsPerSample = mFmtChunk.significantBitsPerSample;
				wf.cbSize = mFmtChunk.extraFormatBytes;

				wh.lpData = buffer;
				wh.dwBufferLength = mDataChunk.chunkDataSize;
				wh.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
				wh.dwLoops = 2;


				printf("format tag: %d\n",wf.wFormatTag);
				printf("wf.nChannels: %d\n",wf.nChannels);
				printf("wf.nSamplesPerSec: %d\n",wf.nSamplesPerSec);
				printf("wf.nAvgBytesPerSec: %d\n",wf.nAvgBytesPerSec);
				printf("wf.nBlockAlign: %d\n",wf.nBlockAlign);
				printf("wf.wBitsPerSample: %d\n",wf.wBitsPerSample);
				printf("wf.cbSize: %d\n",wf.cbSize);
				printf("wh.dwBufferLength: %d\n",wh.dwBufferLength);



				waveOutOpen(&hWaveOut,WAVE_MAPPER,&wf,0,0,CALLBACK_NULL);
				waveOutPrepareHeader(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));
				waveOutWrite(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));

				do {}
				while (!(wh.dwFlags & WHDR_DONE));

				waveOutUnprepareHeader(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));
				waveOutClose(hWaveOut);

				free(buffer);
			}
		}

	}

	else
		printf("INvalid WAV\n");
}

WAVEFORMATEX wf;
	volatile WAVEHDR wh,wh2;
	HWAVEOUT hWaveOut;

void CALLBACK woproc(
  HWAVEOUT hwo,
  UINT uMsg,
  DWORD_PTR dwInstance,
  DWORD_PTR dwParam1,
  DWORD_PTR dwParam2
  ){
	  static int cnt = 0;
	  switch(uMsg){
		  case WOM_DONE:
			  if(cnt<2){
				  cnt++;
				  waveOutWrite(hwo,(LPWAVEHDR)&wh,sizeof(wh));
			  }
			  break;
	  }
}
int main()
{
#if 0
	//char *filename = "e:\\visc\\siege_fft_5\\516_sound\\tada.wav ";
	char *filename = "e:\\visc\\siege_fft_5\\516_sound\\notify.wav";

	char *buffer;
	long fileSize;

	buffer = readFileData(filename, fileSize);
	parseWav(buffer);

	free(buffer);
#else
	
#define buffersize	4096*2
	short buffer[buffersize];
	short buffer2[buffersize];

	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nChannels;
	wf.nBlockAlign = 4;
	wf.wBitsPerSample = 16;
	wf.cbSize = 0;

	wh.lpData = (LPSTR)buffer;
	wh.dwBufferLength = buffersize*2;
	wh.dwFlags = 0;
	wh.dwLoops = 2;

	wh2.lpData = (LPSTR)buffer2;
	wh2.dwBufferLength = buffersize*2;
	wh2.dwFlags = 0;
	wh2.dwLoops = 2;

	waveOutOpen(&hWaveOut,WAVE_MAPPER,&wf,0,0,CALLBACK_NULL);

	static double phase = 0;
	double ii = 1;


	for(int i = 0;i<buffersize;i+=2){
			phase += 2 * 3.14159265358 * 1200  / wf.nSamplesPerSec;
			//ii+=0.00001;
			buffer[i] =3200 * sin(phase);
			buffer[i] += 3200 * sin(2.0*3.141592* 500 * phase/(float)(wf.nSamplesPerSec*2));
			buffer[i] += 3200 * sin(2.0*3.141592* 261.63 * phase/(float)(wf.nSamplesPerSec*2));
			buffer[i] += 3200 * sin(2.0*3.141592* 329.63* phase/(float)(wf.nSamplesPerSec*2));
			buffer[i] += 3200 * sin(2.0*3.141592* 392.00* phase/(float)(wf.nSamplesPerSec*2));
			buffer[i+1] = buffer[i];
		}
		
		for(int i = 0;i<buffersize;i+=2){
			
			phase += 2 * 3.14159265358 * 1200  / wf.nSamplesPerSec;
			//ii+=0.00001;
			buffer2[i] =3200 * sin(phase);
			buffer2[i] += 3200 * sin(2.0*3.141592* 261.63 * phase/(float)(wf.nSamplesPerSec*2));
			buffer2[i] += 3200 * sin(2.0*3.141592* 329.63* phase/(float)(wf.nSamplesPerSec*2));
			buffer2[i] += 3200 * sin(2.0*3.141592* 392.00* phase/(float)(wf.nSamplesPerSec*2));
			buffer2[i+1] = buffer2[i];
		}


		waveOutPrepareHeader(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));
		waveOutPrepareHeader(hWaveOut,(LPWAVEHDR)&wh2,sizeof(wh));

		// play both buffers
		waveOutWrite(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));
		waveOutWrite(hWaveOut,(LPWAVEHDR)&wh2,sizeof(wh));

	for(int j=0;j<10;j++){

		// wait for buffer 1 to finish
		do {} while (!(wh.dwFlags & WHDR_DONE));

		// buffer 1 terminated, buffer 2playing
		//waveOutUnprepareHeader(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));

		// prepare buffer 1 again
		for(int i = 0;i<buffersize;i+=2){
			ii+=0.00001;
			phase += 2 * 3.14159265358 * ii*1200  / wf.nSamplesPerSec;		
			buffer[i] =3200 * sin(phase);		
			buffer[i+1] = buffer[i];
		}
		//waveOutPrepareHeader(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));
		waveOutWrite(hWaveOut,(LPWAVEHDR)&wh,sizeof(wh));

		// buffer 2 terminated, buffer 1 playing
		do {} while (!(wh2.dwFlags & WHDR_DONE));
		//waveOutUnprepareHeader(hWaveOut,(LPWAVEHDR)&wh2,sizeof(wh));

		//preprare buffer 2 again
		for(int i = 0;i<buffersize;i+=2){
			ii+=0.00001;
			phase += 2 * 3.14159265358 *ii* 1200  / wf.nSamplesPerSec;		
			buffer2[i] =3200 * sin(phase);		
			buffer2[i+1] = buffer2[i];
		}
		//waveOutPrepareHeader(hWaveOut,(LPWAVEHDR)&wh2,sizeof(wh));
		waveOutWrite(hWaveOut,(LPWAVEHDR)&wh2,sizeof(wh));


		
	}

	
	waveOutClose(hWaveOut);


#endif

	return 0;
}