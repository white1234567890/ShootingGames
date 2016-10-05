#pragma once
#include "SingletonClass.h"
class FileManagerClass :
	public SingletonClass<FileManagerClass>
{
public:
	friend class SingletonClass<FileManagerClass>;

protected:
	FileManagerClass(void);
	virtual ~FileManagerClass(void);

public:
	bool ReadFile();
};

extern FileManagerClass* cl_FileManager;