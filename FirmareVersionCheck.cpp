//	Win8 - VENUE FW Version Checker
//	Dev: John Blatchford
//	Contact: john.blatchford@avid.com  
//

#include <iostream>
#include <fstream>
#include <memory.h>
#include <string>
using namespace std;

#define BUFFER_SIZE 40									// we only need 40 bytes
#define mBUFFER_SIZE 40									// Module FW has different offset for Version string
#define BIN_FOLDER "..\\"
#define CARBON_IMG_NAME		(BIN_FOLDER "FW/BonanzaUnitImage.bin")		// Default name for the Carbon image
#define ZIRCON_IMG_NAME		(BIN_FOLDER "FW/BonanzaZirconUnitImage.bin")// Default name for the Zircon image
#define KIRKWOOD_IMG_NAME	(BIN_FOLDER "FW/KirkwoodUnitImage.bin")		// Default name for the Kirkwood image
#define SOUNDWAVES_IMG_NAME (BIN_FOLDER "FW/SoundWavesUnitImage.bin")	// Default name for the SoundWaves Carbon2 image
#define E6L_MODULE_IMG_NAME (BIN_FOLDER "FW/ModuleFW.bin")				// Default name for the E6L ModuleFW Image


typedef struct         // Values stored in big endian
{
	char            unit_name[28];
	unsigned int    version_build;
	unsigned char    version_major;
	unsigned char    version_minor;
	unsigned char    version_revision; // 0 for Carbon Rev and 1 for Zircon Rev
	unsigned char    flags;
	unsigned long    checksum;        // Checksum of image (without this addition)
} 
IMAGE_IDENT; // Defining the above structure as IMAGE_IDENT
unsigned char buffer[BUFFER_SIZE]; // Setting the buffer size

inline unsigned int big_endian_32(unsigned int v) // Inline function to convert to bigendian
{
	return ((v >> 24) | ((v & 0x00FF0000) >> 8) | ((v & 0x0000FF00) << 8) | (v << 24));
}
void cVersionCheck()
{
	ifstream cFirmwareFile(CARBON_IMG_NAME, ios::binary); // declare the file to open 
	if (cFirmwareFile.good()) // make sure the file is good before moving on
	{
		cFirmwareFile.seekg (-BUFFER_SIZE, ios_base::end);// seek to -40 bytes from the end
		streamoff length;
		length = cFirmwareFile.tellg(); // set the number of bytes as a stream obj
		char * buffer = new char[sizeof(IMAGE_IDENT)]; // set a pointer to the size of the buffer
		cFirmwareFile.read (buffer,length);  // read data as a block
		cout << "  " << length << " bytes in Carbon image ... " << endl;  // inform the user of action

		IMAGE_IDENT id = *(IMAGE_IDENT *)buffer; // fill the custom struct with the contents of the read buffer
		unsigned int build=big_endian_32(id.version_build); // set big endian for reading the bytes
		id.version_build=big_endian_32(id.version_build); // apply to structure
		cout << " \tCarbon FW version : " << id.unit_name << "." << static_cast<unsigned int>(id.version_major) << "." << static_cast<unsigned int>(id.version_minor) << "." << static_cast<unsigned int>(id.version_revision) << "." << id.version_build << endl;
	}
	else
	{
		cout << "\n ERROR: " << cFirmwareFile.gcount() << " bytes could be read from the Carbon Firmware \n";  // Some error reporting
		cFirmwareFile.close();   // ...buffer contains the entire file...
		cout << "Please check the Carbon firmware file.  It failed to open."  << endl; // report
	}
}
void zVersionCheck()
{
	ifstream zFirmwareFile(ZIRCON_IMG_NAME, ios::binary); // declare the file to open 
	if (zFirmwareFile.good()) // make sure the file is good before moving on
	{
		zFirmwareFile.seekg (-BUFFER_SIZE, ios_base::end);// seek to -40 bytes from the end
		streamoff length;
		length = zFirmwareFile.tellg(); // set the number of bytes as a stream obj
		char * buffer = new char[sizeof(IMAGE_IDENT)]; // set a pointer to the size of the buffer
		zFirmwareFile.read (buffer,length);  // read data as a block
		cout << "  " << length << " bytes in Zircon image ... " << endl;  // inform the user of action

		IMAGE_IDENT id = *(IMAGE_IDENT *)buffer; // apply the buffer to the custom structure
		unsigned int build=big_endian_32(id.version_build); // set big endian for reading the bytes
		id.version_build=big_endian_32(id.version_build); // apply to structure
		cout << " \tZircon FW version : " << id.unit_name << "." << static_cast<unsigned int>(id.version_major) << "." << static_cast<unsigned int>(id.version_minor) << "." << static_cast<unsigned int>(id.version_revision) << "." << id.version_build << endl;
	}
	else
	{
		cout << "\n ERROR: " << zFirmwareFile.gcount() << " bytes could be read from the Zircon Image \n";  // Some error reporting
		zFirmwareFile.close();   // ...buffer contains the entire file...
		cout << "Please check the Zircon firmware file.  It failed to open. \n";
	}
}
void kVersionCheck()
{
	ifstream kFirmwareFile(KIRKWOOD_IMG_NAME, ios::binary); // declare the file to open 
	if (kFirmwareFile.good()) // make sure the file is good before moving on
	{
		kFirmwareFile.seekg (-BUFFER_SIZE, ios_base::end);// seek to -40 bytes from the end
		streamoff length;
		length = kFirmwareFile.tellg(); // set the number of bytes as a stream obj
		char * buffer = new char[sizeof(IMAGE_IDENT)]; // set a pointer to the size of the buffer
		kFirmwareFile.read (buffer,length);  // read data as a block
		cout << "  " << length << " bytes in Kirkwood image ... " << endl;  // inform the user of action

		IMAGE_IDENT id = *(IMAGE_IDENT *)buffer; // apply the buffer to the custom structure
		unsigned int build=big_endian_32(id.version_build); // set big endian for reading the bytes
		id.version_build=big_endian_32(id.version_build); // apply to structure
		cout << " \tKirkwood FW version : " << id.unit_name << "." << static_cast<unsigned int>(id.version_major) << "." << static_cast<unsigned int>(id.version_minor) << "." << static_cast<unsigned int>(id.version_revision) << "." << id.version_build << endl;
	}
	else
	{
		cout << "\n ERROR: " << kFirmwareFile.gcount() << " bytes could be read from the Kirkwood Image \n";  // Some error reporting
		kFirmwareFile.close();   // ...buffer contains the entire file...
		cout << "Please check the Kirkwood firmware file.  It failed to open. \n";
	}
}
void sVersionCheck()
{
	ifstream sFirmwareFile(SOUNDWAVES_IMG_NAME, ios::binary); // declare the file to open 
	if (sFirmwareFile.good()) // make sure the file is good before moving on
	{
		sFirmwareFile.seekg (-BUFFER_SIZE, ios_base::end);// seek to -40 bytes from the end
		streamoff length;
		length = sFirmwareFile.tellg(); // set the number of bytes as a stream obj
		char * buffer = new char[sizeof(IMAGE_IDENT)]; // set a pointer to the size of the buffer
		sFirmwareFile.read (buffer,length);  // read data as a block
		cout << "  " << length << " bytes in SoundWaves image ... " << endl;  // inform the user of action

		IMAGE_IDENT id = *(IMAGE_IDENT *)buffer; // fill the custom struct with the contents of the read buffer
		unsigned int build=big_endian_32(id.version_build); // set big endian for reading the bytes
		id.version_build=big_endian_32(id.version_build); // apply to structure
		cout << " \tSoundWaves FW version : " << id.unit_name << "." << static_cast<unsigned int>(id.version_major) << "." << static_cast<unsigned int>(id.version_minor) << "." << static_cast<unsigned int>(id.version_revision) << "." << id.version_build << endl;
	}
	else
	{
		cout << "\n ERROR: " << sFirmwareFile.gcount() << " bytes could be read from the SoundWaves Firmware \n";  // Some error reporting
		sFirmwareFile.close();   // ...buffer contains the entire file...
		cout << "Please check the SoundWaves firmware file.  It failed to open."  << endl; // report
	}
}
void mVersionCheck()
{
	ifstream mFirmwareFile(E6L_MODULE_IMG_NAME, ios::binary); // declare the file to open 
	if (mFirmwareFile.good()) // make sure the file is good before moving on
	{
		mFirmwareFile.seekg (-mBUFFER_SIZE, ios_base::end);// seek to -40 bytes from the end
		streamoff length;
		length = mFirmwareFile.tellg(); // set the number of bytes as a stream obj
		char * buffer = new char[sizeof(IMAGE_IDENT)]; // set a pointer to the size of the buffer
		mFirmwareFile.read (buffer,length);  // read data as a block
		cout << "  " << length << " bytes in SoundWaves image ... " << endl;  // inform the user of action

		IMAGE_IDENT id = *(IMAGE_IDENT *)buffer; // fill the custom struct with the contents of the read buffer
		unsigned int build=big_endian_32(id.version_build); // set big endian for reading the bytes
		id.version_build=big_endian_32(id.version_build); // apply to structure
		cout << " \tE6L_Module FW version : " << id.unit_name << "." << static_cast<unsigned int>(id.version_major) << "." << static_cast<unsigned int>(id.version_minor) << "." << static_cast<unsigned int>(id.version_revision) << "." << id.version_build << endl;
	}
	else
	{
		cout << "\n ERROR: " << mFirmwareFile.gcount() << " bytes could be read from the E6L_Module Firmware \n";  // Some error reporting
		mFirmwareFile.close();   // ...buffer contains the entire file...
		cout << "Please check the E6L Module firmware file.  It failed to open."  << endl; // report
	}
}
int main(int argc,char *argv[])
{
	cout << "\n      VENUE Firmware Version Utility for Win8 v.6\n\n" << endl;
	memset(buffer,0,sizeof(buffer)); // Initalize memory for the buffer
	ifstream isCFirmware(CARBON_IMG_NAME); // declare the ifStream objects
	ifstream isZFirmware(ZIRCON_IMG_NAME); 
	ifstream isKFirmware(KIRKWOOD_IMG_NAME);
	ifstream isSFirmware(SOUNDWAVES_IMG_NAME);
//	ifstream isMFirmware(E6L_MODULE_IMG_NAME);

	cVersionCheck(); // Carbon FW Check function
	cout << endl << endl << endl;
	zVersionCheck(); // Zircon FW Check function
	cout << endl << endl << endl;
	kVersionCheck(); // Kirkwood FW Check Function
	cout << endl << endl << endl;
	sVersionCheck(); // SoundWaves FW Check Function
//	cout << endl << endl << endl;
//	mVersionCheck(); // E6L_Module FW Check Function	

	if (!isCFirmware)
		cerr << "\nCarbon firmware not found. \n" << endl;
	if (!isZFirmware)
		cerr << "\nZircon firmware not found. \n" << endl;
	if (!isKFirmware)
		cerr << "\nKirkwood firmware not found. \n" << endl;
	if (!isSFirmware)
		cerr << "\nSoundWaves firmware not found. \n" << endl;
//	if (!isMFirmware)
//		cerr << "\nE6L_Module firmware not found. \n" << endl;
	cin.get();
	return 0;
}
