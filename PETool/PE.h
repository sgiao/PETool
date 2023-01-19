#pragma once

/**
 * DOSͷ
 */  
struct DosHeader {
	unsigned short e_magic;
	unsigned short e_cblp;
	unsigned short e_cp;
	unsigned short e_crlc;
	unsigned short e_cparhdr;
	unsigned short e_minalloc;
	unsigned short e_maxalloc;
	unsigned short e_ss;
	unsigned short e_sp;
	unsigned short e_csum;
	unsigned short e_ip;
	unsigned short e_cs;
	unsigned short e_lfarlc;
	unsigned short e_ovno;
	unsigned short e_res[4];
	unsigned short e_oemid;
	unsigned short e_oeminfo;
	unsigned short e_res2[10];
	unsigned int e_lfanew;
};
/**
 * DOSͷ
 */
struct PeHeader {
	unsigned int Signature;
	unsigned short Machine;
	unsigned short NumberOfSections;
	unsigned int TimeDateStamp;
	unsigned int PointerToSymbolTable;
	unsigned int NumberOfSymbols;
	unsigned short SizeOfOptionalHeader;
	unsigned short Characteristics;
};
/**
 * ��ѡPEͷ
 */
struct OptPeHeader {
	unsigned short Magic;
	unsigned char MajorLinkerVersion;
	unsigned char MinorLinkerVersion;
	unsigned int SizeOfCode;
	unsigned int SizeOfInitializedData;
	unsigned int SizeOfUninitializedData;
	unsigned int AddressOfEntryPoint;
	unsigned int BaseOfCode;
	unsigned int BaseOfData;
	unsigned int ImageBase;
	unsigned int SectionAlignment;
	unsigned int FileAlignment;
	unsigned short MajorOperatingSystemVersion;
	unsigned short MinorOperatingSystemVersion;
	unsigned short MajorImageVersion;
	unsigned short MinorImageVersion;
	unsigned short MajorSubsystemVersion;
	unsigned short MinorSubsystemVersion;
	unsigned int Win32VersionValue;
	unsigned int SizeOfImage;
	unsigned int SizeOfHeaders;
	unsigned int CheckSum;
	unsigned short Subsystem;
	unsigned short DllCharacteristics;
	unsigned int SizeOfStackReserve;
	unsigned int SizeOfStackCommit;
	unsigned int SizeOfHeapReserve;
	unsigned int SizeOfHeapCommit;
	unsigned int LoaderFlags;
	unsigned int NumberOfRvaAndSizes;
	struct {
		unsigned int VirtualAddress;
		unsigned int Size;
	} DataDirectory[16];
};// PEͷ
/**
 * �ڱ�
 */ 
struct Sections {
	unsigned char name[8];  // ���������8���ֽڶ���ռ�õ����Ҳ���00��β����Ҫ�ֶ�����һ��
	unsigned int VirtualSize; // �ɸ�
	unsigned int VirtualAddress;
	unsigned int SizeOfRawData;
	unsigned int PointerToRawData;
	unsigned int PointerToRelocations;
	unsigned int PointerToLinenumbers;
	unsigned short NumberOfRelocations;
	unsigned short NumberOfLinenumbers;
	unsigned int Characteristics;
};
/**
 * ������
 */ 
struct ExportTable {
	unsigned int Characteristics;
	unsigned int TimeDateStamp;
	unsigned short MajorVersion;
	unsigned short MinorVersion;
	unsigned int Name;
	unsigned int Base;
	unsigned int NumberOfFunction; // ���㹫ʽ��������-��С���
	unsigned int NumberOfNames;
	unsigned int AddressOfFunction;
	unsigned int AddressOfNames;
	unsigned int AddressOfNameOrdinals;
};
/**
 * �����
 */ 
struct ImportTable {
	unsigned int OriginalFirstThunk;      // RVA ָ��IMAGE_THUNK_DATA�ṹ����				
	unsigned int TimeDateStamp;           // ʱ���				
	unsigned int ForwarderChain;
	unsigned int Name;					          // RVA,ָ��dll���֣���������0��β				
	unsigned int FirstThunk;              // RVA,ָ��IMAGE_THUNK_DATA�ṹ����				
};
/**
 * �󶨵����
 */
struct BoundImport {
	unsigned int TimeDateStamp;
	unsigned short OffsetModuleName;
	unsigned short NumberOfModule;
};
/**
 * �ܽṹ
 */ 
struct PE {
	DosHeader* dos;
	PeHeader* pe;
	OptPeHeader* ope;
	Sections* sections;
};

PE getPE(char* buffer);
PE getPE(const char* filePath);

// ================= Print Function =====================
void printDosHead(PE* pe);        // ��ӡ�����dosͷ
void printPeHead(PE* pe);         // ��ӡ�����peͷ
void printOptPeHead(PE* pe);      // ��ӡ�������ѡpeͷ
void printSection(PE* pe);        // ��ӡ������ڱ�
void printExportTable(PE* pe);    // ��ӡ�����������
void printRelocationTable(PE* pe);// ��ӡ������ض�λ��
void printImportTable(PE* pe, int isShowRepairAfter);// ��ӡ����������
void printBoundImport(PE* pe);    // ��ӡ������󶨵����

// ================= Tools Function =====================
void* rvaToFoa(PE* pe, int rva);
void* foaToRva(PE* pe, int foa);
void memoryInit(char* addr, int size, char value);
void memoryCopy(char* srcAddr, char* destAddr,int size);
int strEq(char* s1, char* s2);
int strLen(char* s1);
void closePE(PE* pe);