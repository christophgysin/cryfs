#pragma once
#ifndef CRYFS_LIB_CRYDEVICE_H_
#define CRYFS_LIB_CRYDEVICE_H_

#include <boost/filesystem.hpp>
#include <cryfs_lib/CryOpenFileList.h>
#include <memory>
#include <sys/stat.h>

#include "utils/macros.h"

namespace cryfs {
class CryNode;
class CryFile;
class CryOpenFile;
class CryDir;

namespace bf = boost::filesystem;

class CryDevice {
public:
	CryDevice(const bf::path &rootdir);
	virtual ~CryDevice();

	int openFile(const bf::path &path, int flags);
	void closeFile(int descriptor);
	void lstat(const bf::path &path, struct ::stat *stbuf);
	void fstat(int descriptor, struct ::stat *stbuf);
	void truncate(const bf::path &path, off_t size);
	void ftruncate(int descriptor, off_t size);
	void read(int descriptor, void *buf, size_t count, off_t offset);
	void write(int descriptor, const void *buf, size_t count, off_t offset);
	void fsync(int descriptor);
	void fdatasync(int descriptor);
	void access(const bf::path &path, int mask);
	int createFile(const bf::path &path, mode_t mode);

	const bf::path &RootDir() const;
private:
	std::unique_ptr<CryNode> Load(const bf::path &path);
	std::unique_ptr<CryFile> LoadFile(const bf::path &path);
	std::unique_ptr<CryDir> LoadDir(const bf::path &path);
	const bf::path _rootdir;
	CryOpenFileList _open_files;

  DISALLOW_COPY_AND_ASSIGN(CryDevice);
};

inline const bf::path &CryDevice::RootDir() const {
  return _rootdir;
}

}

#endif /* CRYFS_LIB_CRYDEVICE_H_ */
