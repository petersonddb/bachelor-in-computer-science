#include <windows.h>
#include <stdio.h>

#define KEY 0x80
#define L_P 0x37
#define L_A 0x93
#define L_B 0x6B

#define dc(addr, len, key) { \
	DWORD idx = 0; \
	while(idx < len) { \
		addr[idx] += key; \
		++idx; \
	} \
}

DWORD WINAPI
threadP(LPVOID);

DWORD WINAPI
threadA(LPVOID);

DWORD WINAPI
threadB(LPVOID);

int
result(int (* output)(const char *));

typedef struct tAData {
	LPBYTE lpBytes;
	HANDLE hEvt;
	BOOL (* setEvt)(HANDLE);
	void (* slp)(DWORD);
} tAData;

typedef struct tBData {
	HANDLE hEvt;
	BOOL (* setEvt)(HANDLE);
	void (* exitPs)(UINT);
	void (* slp)(DWORD);
} tBData;

HANDLE evtA, evtB;

typedef DWORD (* cb) (LPVOID);

BYTE key = KEY;
cb cba, cbb, cbp = threadP;

BYTE bytesAB[L_A + L_B] = {
	200,   9, 204, 164, 136, 200,   3, 108,
	184, 200,  11, 196, 164, 192, 200,   9,
	196, 164, 168, 200,  11, 196, 164, 168,
	200,  11, 200, 136, 200,  11, 196, 164,
	168, 127, 208, 144, 179,  64,   3, 120,
	129, 244, 225,  71, 196, 164, 160, 128,
	128, 128, 128,  11, 196, 164, 160, 200,
	 11, 204, 164, 168, 200,  11, 137, 143,
	 54, 132, 129, 189,  67, 128, 128, 128,
	244, 179,  11, 196, 164, 160, 200,  11,
	204, 164, 168, 200,  11, 137, 143,  54,
	132, 129, 189,  76, 128, 128, 128, 245,
	144,  11, 196, 164, 160, 200,  11, 204,
	164, 168, 200,  11, 137,  70, 132, 129,
	 67,  11, 196, 164, 160, 127,  64,   9,
	196, 164, 160, 107,  54,  57,  24, 186,
	128, 128, 200,  11, 196, 164, 168, 127,
	208, 152, 107,  24, 179,  64, 200,   3,
	 68, 184, 200,   9, 204, 164, 136, 200,
	  3, 108, 184, 200,  11, 196, 164, 192,
	200,   9, 196, 164, 160, 200,  11, 196,
	164, 160, 200,  11, 136, 200,  11, 196,
	164, 160, 127, 208, 136, 179,  64,   3,
	120, 129, 244, 186, 229, 200,  11, 132,
	165, 224, 128, 128, 128, 200,   3,  64,
	130, 200,   9, 196, 164, 168, 200,  11,
	196, 164, 168, 143,  54, 128,   5,  64,
	244, 141,  57, 127, 127, 127, 127, 200,
	 11, 196, 164, 160, 127, 208, 144,  57,
	 24, 186, 128, 128, 200,  11, 196, 164,
	160, 127, 208, 152, 107,  63, 179,  64,
	200,   3,  68, 184,  67
};

BYTE bytesR[L_P] = {
	 77, 142,  81,  41,  13,  77, 136, 241,
	 61, 203,  73,  41,  37,  73, 203,  73,
	 41,  38, 116, 203,  73,  41,  39, 115,
	203,  73,  41,  40, 106, 203,  73,  41,
	 41,  38, 203,  73,  41,  42,   5,  77,
	146,  81,  41,  37,   4,  89,  41,  69,
	 56, 197,  77, 136, 201,  61, 200
};

HANDLE hHeap;

int
main(void) {
	HANDLE hP;
	LPVOID lpMem;
	tAData tAData;
	tBData tBData;

	evtA  = CreateEvent(NULL, FALSE, FALSE, NULL);
	evtB  = CreateEvent(NULL, FALSE, FALSE, NULL);
	hP    = CreateThread(NULL, 0, threadP, NULL, 0, NULL);
	hHeap = HeapCreate(
		HEAP_CREATE_ENABLE_EXECUTE, L_A + L_B + L_P, L_A + L_B + L_P);
	lpMem = HeapAlloc(hHeap, 0, L_A + L_B);

	CopyMemory(lpMem, bytesAB, L_A + L_B);
	dc(((LPBYTE) lpMem), L_A + L_B, key);

	cba = lpMem;
	cbb = (cb) ((LPBYTE) lpMem + L_A);

	tAData.lpBytes = (LPBYTE) cbp;
	tAData.hEvt    = evtA;
	tAData.setEvt  = SetEvent;
	tAData.slp     = Sleep;

	tBData.hEvt   = evtB;
	tBData.setEvt = SetEvent;
	tBData.exitPs = ExitProcess;
	tBData.slp    = Sleep;

	CreateThread(NULL, 0, cba, &tAData, 0, NULL);
	CreateThread(NULL, 0, cbb, &tBData, 0, NULL);

	WaitForSingleObject(hP, INFINITE);

	return 0;
}

int
result(int (* output)(const char *)) {
	char done[6] = {'D','o','n','e','!',0};

	output(done);

	return 0;
}

DWORD
threadP(LPVOID notused) {
	HANDLE lpHandles[2] = {evtA, evtB};
	LPVOID lpMem;
	LPBYTE lpByte;
	BYTE bKey;
	WORD times;
	void (* cbr)(void);

	printf("Doing something...\n");

	WaitForMultipleObjects(
		2, lpHandles, TRUE, INFINITE);

	lpMem = HeapAlloc(hHeap, 0, L_P);

	CopyMemory(lpMem, bytesR, L_P);

	bKey   = 0;
	times  = 3;
	lpByte = (LPBYTE) cba;

	while(times > 0) {
		if(*lpByte == 0xC3)
			--times;

		bKey   += *lpByte;
		lpByte += 1;
	}

	dc(((LPBYTE) lpMem), L_P, bKey);
	cbr = lpMem;
	cbr(puts);

	ZeroMemory(lpMem, L_P);

	return 0;
}

DWORD
threadA(LPVOID data) {
	DWORD pos;
	tAData *tD;

	tD = (tAData *) data;

	tD->setEvt(tD->hEvt);

	while(TRUE) {
		pos = 0;

		while(tD->lpBytes[pos] != 0xC3) {
			if(tD->lpBytes[pos] == 0xCC)
				tD->lpBytes[pos] = 0xC3;

			++pos;
		}

		tD->slp(15000);
	}

	return 0;
}

DWORD
threadB(LPVOID data) {
	LPBYTE lpData;
	tBData *tD;

	tD = (tBData *) data;

	tD->setEvt(tD->hEvt);

	while(TRUE) {
		lpData = (LPBYTE) (__readgsqword(0x60) + 0x2);

		if(*lpData)
			tD->exitPs(-1);

		tD->slp(15000);
	}

	return 0;
}
