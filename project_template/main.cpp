/**
A demo of a basic manual PE loader - you can use it as a starting point for your own project,
or delete it and start from scratch
*/

#include <Windows.h>
#include <iostream>
#include <tchar.h>

#include <peconv.h> // include libPeConv header

BYTE* g_Payload = nullptr;
size_t g_PayloadSize = 0;

// manually load the PE file using libPeConv
bool load_payload(LPCTSTR pe_path)
{
	if (g_Payload) {
		// already loaded
		std::cerr << "[!] The payload is already loaded!\n";
		return false;
	}
#ifdef LOAD_FROM_PATH
	//if the PE is dropped on the disk, you can load it from the file:
	g_Payload = peconv::load_pe_executable(pe_path, g_PayloadSize);
#else // load from memory buffer
	/*
	in this example the memory buffer is first loaded from the disk,
	but it can as well be fetch from resources, or a hardcoded buffer
	*/
	size_t bufsize = 0;
	BYTE* buf = peconv::load_file(pe_path, bufsize);
	if (!buf) {
		return false;
	}
	// if the file is NOT dropped on the disk, you can load it directly from a memory buffer:
	g_Payload = peconv::load_pe_executable(buf, bufsize, g_PayloadSize);

	// at this point we can free the buffer with the raw payload:
	peconv::free_file(buf); buf = nullptr;
	
#endif
	if (!g_Payload) {
		return false;
	}

	// if the loaded PE needs to access resources, you may need to connect it to the PEB:
	peconv::set_main_module_in_peb((HMODULE)g_Payload);

	// load delayed imports (if present):
	const ULONGLONG loadBase = (ULONGLONG)g_Payload;
	peconv::load_delayed_imports(g_Payload, loadBase);

	return true;
}

int run_payload()
{
	if (!g_Payload) {
		std::cerr << "[!] The payload is not loaded!\n";
		return -1;
	}

	// if needed, you can run TLS callbacks before the Entry Point:
	peconv::run_tls_callbacks(g_Payload, g_PayloadSize);

	//calculate the Entry Point of the manually loaded module
	DWORD ep_rva = peconv::get_entry_point_rva(g_Payload);
	if (!ep_rva) {
		std::cerr << "[!] Cannot fetch EP!\n";
		return -2;
	}
	const ULONG_PTR ep_va = ep_rva + (ULONG_PTR)g_Payload;

	// run appropriate version of payload's main:
	int ret = 0;
	if (peconv::is_module_dll(g_Payload)) {
		//the prototype of the DllMain fuction:
		BOOL WINAPI _DllMain(
			HINSTANCE hinstDLL,  // handle to DLL module
			DWORD fdwReason,     // reason for calling function
			LPVOID lpvReserved);  // reserved
		auto new_main = reinterpret_cast<decltype(&_DllMain)>(ep_va);

		// call the Entry Point of the manually loaded PE :
		ret = new_main((HINSTANCE)g_Payload, DLL_PROCESS_ATTACH, 0);
	}
	else {
		//the simplest prototype of the main fuction:
		int basic_main(void);
		auto new_main = reinterpret_cast<decltype(&basic_main)>(ep_va);

		//call the Entry Point of the manually loaded PE:
		ret = new_main();
	}
	return ret;
}

int _tmain(int argc, LPTSTR argv[])
{
	if (argc < 2) {
		std::cout << "Args: <path to the exe>" << std::endl;
		return 0;
	}
	const LPTSTR pe_path = argv[1];
	if (!load_payload(pe_path)) {
		return -1;
	}
	std::cout << "Payload loaded!\n";
	return run_payload();
}
