#ifndef DOLORI_FILES_MEMFILE_H_
#define DOLORI_FILES_MEMFILE_H_

class CMemFile
{
public:
	CMemFile();
	virtual ~CMemFile();

	virtual unsigned long size();
	virtual const unsigned char * read(unsigned long, unsigned long);
	//public unsigned long size();
	//public const unsigned char * read(unsigned long, unsigned long);
	//public void CMemFile(const class CMemFile &);
};

#endif // DOLORI_FILES_MEMFILE_H_
