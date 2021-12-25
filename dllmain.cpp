#include "multitask.h"

#define RELATIVE_ADDR(addr, size)       ((uintptr_t)((uintptr_t)(addr) + *(PINT)((uintptr_t)(addr) + ((size) - sizeof(INT))) + (size)))
#define rva(addr, size) (reinterpret_cast<unsigned char*>(addr + *reinterpret_cast<int*>(addr + (size - 4)) + size))


void Main() {

	static DWORD_PTR funcGetObjectName = NULL;
	auto basemodule = GetModuleHandle(0);

	hk_renderbasics::UWorld_Offset = g_Scanner->FindPattern(basemodule, skCrypt("\x48\x8B\x05\x00\x00\x00\x00\x4D\x8B\xC2"), skCrypt("xxx????xxx????"), 0); // UWORLD SIG HERE
	hk_renderbasics::UWorld_Offset = reinterpret_cast<decltype(hk_renderbasics::UWorld_Offset)>(rva(hk_renderbasics::UWorld_Offset, 7));

    pGetBoneMatrix = g_Scanner->FindPattern(basemodule, skCrypt("\xE8\x00\x00\x00\x00\x48\x8B\x47\x30\xF3\x0F\x10\x45"), skCrypt("x????xxxxxxxx?"), 0);
    pGetBoneMatrix = reinterpret_cast<decltype(pGetBoneMatrix)>(rva(pGetBoneMatrix, 5));

	PBYTE addr = (PBYTE)(DWORD64)GetModuleHandleW(NULL) + 0x79104B0; // LINEOFSIG SIG JERE
	LOS = reinterpret_cast<decltype(LOS)>(addr);

	auto address = g_Scanner->FindPattern(basemodule, ("\x0F\x84\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x48\x83\xC4\x28\xC3"), ("xx????xxx????xxxxx"), 0);
	auto offset = *reinterpret_cast<uint32_t*>(address + 9);

	auto Gobjects = g_Scanner->FindPattern(basemodule, skCrypt("\x48\x89\x05\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x45\x84\xF6"),
		("xxx????x????xxx"), 0);

	auto Gnames = g_Scanner->FindPattern(basemodule, skCrypt("\x48\x8B\x1D\x00\x00\x00\x00\x48\x03\xC0"),
		"xxx????xxx", 0);

	auto BoneMatrix = g_Scanner->FindPattern(basemodule, skCrypt("\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x10\x48\x89\x78\x20\x44\x89\x40\x18\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\xC8"),
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxx????xxxx", 0);

	BoneMatrix = reinterpret_cast<decltype(BoneMatrix)>(rva(BoneMatrix, 5));
	uintptr_t printfobject = 0;

	const auto offset = *reinterpret_cast<uint32_t*>(Gobjects + 3);
	printfobject = reinterpret_cast<decltype(printfobject)>(Gobjects + 7 + offset);

	render::RenderCanvas();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{ 
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		AllocConsole();
    	freopen("conin$", "r", stdin);
    	freopen("conout$", "w", stdout);
	    freopen("conout$", "w", stderr);
		Main();
	}

	return TRUE;
}