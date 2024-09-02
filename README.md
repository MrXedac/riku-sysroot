# SysRoot for Riku
## Temporary instructions

* make a build folder `mkdir build`
* build autoconf, automake 
  * ../automake-1.11/configure --prefix=SYSROOT_PATH && make && make install
  * ../autoconf-2.65/configure --prefix=SYSROOT_PATH && make && make install
* symlink gcc, cc, ar, as, ranlib info x86_64-riku-fcc, cc, ar, as, ranlib
* configure newlib
  * ../newlib-2.5.0.20171222/configure --prefix=/usr --target=x86_64-riku --disable-multilib
  * make all
  * make DESTDIR=SYSROOT_PATH install
