// DLL_EXT_CLASS can be used to import or export entire classes
// in the extension DLL without the hassle of creating a .DEF file
// with decorated names.
// for exporting a class the DLL must define the _EXT_DLL flag
// and for importing classes the _EXPORT_DLL must be undefined

#if !defined _FMI_EXPORT_IMPORT_H_
#define _FMI_EXPORT_IMPORT_H_

#ifdef WIN32
	#ifdef _EXPORT_DLL_CLASS
		#define DLL_EXPORT			__declspec(dllexport)
		#define DLL_EXT_API_G       __declspec(dllexport)
		#define DLL_EXT_DATA_G      __declspec(dllexport)
		#define DLL_EXT_DATADEF_G
	#else
		#define DLL_EXPORT			__declspec(dllimport)
		#define DLL_EXT_API_G       __declspec(dllimport)
		#define DLL_EXT_DATA_G      __declspec(dllimport)
		#define DLL_EXT_DATADEF_G
	#endif
#else
	#define DLL_EXPORT
    #define DLL_EXT_API_G    
    #define DLL_EXT_DATA_G
    #define DLL_EXT_DATADEF_G
#endif

#endif //_FMI_EXPORT_IMPORT_H_