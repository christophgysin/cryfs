#ifndef CRYFS_LIB_CRYOPENFILE_H_
#define CRYFS_LIB_CRYOPENFILE_H_

#include <boost/filesystem.hpp>
#include <sys/stat.h>

#include "utils/macros.h"

namespace cryfs {

namespace bf = boost::filesystem;

class CryOpenFile {
public:
  CryOpenFile(const bf::path &path, int flags);
  virtual ~CryOpenFile();

  void stat(struct ::stat *result) const;
  void truncate(off_t size) const;
  void read(void *buf, size_t count, off_t offset);
  void write(const void *buf, size_t count, off_t offset);
  void fsync();
  void fdatasync();
private:
  int _descriptor;

  DISALLOW_COPY_AND_ASSIGN(CryOpenFile);
};

}

#endif /* CRYFS_LIB_CRYOPENFILE_H_ */
