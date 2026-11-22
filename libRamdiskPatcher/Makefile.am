AM_CFLAGS = -I$(top_srcdir)/include $(libgeneral_CFLAGS) $(libinsn_CFLAGS) $(libpatchfinder_CFLAGS) $(libramdisk_CFLAGS) $(openssl_CFLAGS)
AM_CXXFLAGS = $(AM_CFLAGS)
AM_LDFLAGS = $(libgeneral_LIBS) $(libinsn_LIBS) $(libpatchfinder_LIBS) $(libramdisk_LIBS) $(openssl_LIBS)

lib_LTLIBRARIES = libRamdiskPatcher.la

libRamdiskPatcher_la_CPPFLAGS = $(AM_CFLAGS)
libRamdiskPatcher_la_LIBADD = $(AM_LDFLAGS)
libRamdiskPatcher_la_SOURCES =  RPPF.cpp \
                                RPPF32.cpp \
                                RPPF64.cpp \
                                utils.cpp
