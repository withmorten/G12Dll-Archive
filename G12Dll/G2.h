WRAPPER void *_malloc(size_t Size) { EAXJMP(0x007B44C6); }
WRAPPER void *_calloc(size_t NumOfElements, size_t SizeOfElements) { EAXJMP(0x007B44F0); }
WRAPPER void *_realloc(void *Memory, size_t NewSize) { EAXJMP(0x007B44BA); }
WRAPPER void _free(void *Memory) { EAXJMP(0x007B44CC); }
WRAPPER int _rand(void) { EAXJMP(0x007D2F98); }
WRAPPER void *_memcpy(void *Dst, void *Src, size_t Size) { EAXJMP(0x007D5320); }
WRAPPER void *_memset(void *Dst, int Val, size_t Size) { EAXJMP(0x007DCA90); }

BYTE
GetAlpha(zCOLOR color)
{
	return *((BYTE *)&color + 3);
}

void
SetAlpha(zCOLOR *color, BYTE alpha)
{
	*((BYTE *)color + 3) = alpha;
}
