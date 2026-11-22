AC_PREREQ([2.69])
AC_INIT([libRamdiskPatcher], m4_esyscmd([git rev-list --count HEAD | tr -d '\n']), [tihmstar@gmail.com])

AC_CANONICAL_SYSTEM
AC_CANONICAL_HOST
LT_INIT([disable-static])

AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

AC_DEFINE([VERSION_COMMIT_COUNT], "m4_esyscmd([git rev-list --count HEAD | tr -d '\n'])", [Git commit count])
AC_DEFINE([VERSION_COMMIT_SHA], "m4_esyscmd([git rev-parse HEAD | tr -d '\n'])", [Git commit sha])
AC_SUBST([VERSION_COMMIT_COUNT], ["m4_esyscmd([git rev-list --count HEAD | tr -d '\n'])"])
AC_SUBST([VERSION_COMMIT_SHA], ["m4_esyscmd([git rev-parse HEAD | tr -d '\n'])"])

# Checks for programs.
AC_PROG_CXX([clang++])
AC_PROG_CC([clang++])

# Check for operating system
AC_MSG_CHECKING([whether we need platform-specific build settings])
case $host_os in
  darwin* )
        AC_MSG_RESULT([${host_os}])
        CXXFLAGS+=" -stdlib=libc++ "
        ;;
  *mingw32*|*cygwin*|*msys*)
        AC_MSG_RESULT([${host_os}])
        win32=true
        LDFLAGS+=" -lws2_32"
        ;;
esac

CXXFLAGS+=" -std=c++23 -O3"
CFLAGS+=" -std=c23"

# Checks for libraries.
LIBGENERAL_REQUIRES_STR="libgeneral >= 92"
LIBPATCHFINDER_REQUIRES_STR="libpatchfinder >= 178"
LIBRAMDISK_REQUIRES_STR="libramdisk >= 1"
OPENSSL_REQUIRES_STR="openssl >= 3.0.0"

PKG_CHECK_MODULES(libgeneral, $LIBGENERAL_REQUIRES_STR)
PKG_CHECK_MODULES(libpatchfinder, $LIBPATCHFINDER_REQUIRES_STR)
PKG_CHECK_MODULES(libramdisk, $LIBRAMDISK_REQUIRES_STR)
PKG_CHECK_MODULES(openssl, $OPENSSL_REQUIRES_STR)

AC_SUBST([libgeneral_requires], [$LIBGENERAL_REQUIRES_STR])
AC_SUBST([libpatchfinder_requires], [$LIBPATCHFINDER_REQUIRES_STR])
AC_SUBST([libramdisk_requires], [$LIBRAMDISK_REQUIRES_STR])
AC_SUBST([openssl_requires], [$OPENSSL_REQUIRES_STR])


AC_ARG_ENABLE([debug],
            [AS_HELP_STRING([--enable-debug],
            [enable debug build(default is no)])],
            [debug_build=true],
            [debug_build=false])

if test "$debug_build" = true; then
  echo "*** Note: debug build requested ***"
  CFLAGS+=" -g -O0 -DDEBUG=1"
  CXXFLAGS+=" -g -O0 -DDEBUG=1"
fi

GLOBAL_CFLAGS+=" -fvisibility=hidden"
case "$GLOBAL_CFLAGS" in
	*-fvisibility=hidden*)
		AC_DEFINE([HAVE_FVISIBILITY], [1], [Define if compiled with -fvisibility=hidden])
esac


LT_INIT

AC_CHECK_FUNCS([mkdtemp])

LDFLAGS+=" -no-undefined"

AC_SUBST(GLOBAL_CFLAGS)
AC_SUBST(GLOBAL_CXXFLAGS)
AC_SUBST(GLOBAL_LDFLAGS)

AC_CONFIG_FILES([Makefile
                include/Makefile
                libRamdiskPatcher.pc
                libRamdiskPatcher/Makefile])
AC_OUTPUT

echo "
Configuration for $PACKAGE-$VERSION:
-------------------------------------------

  install prefix ..........: $prefix
  debug build  ............: $debug_build"
echo "  compiler ................: ${CC}

  Now type 'make' to build $PACKAGE-$VERSION,
  and then 'make install' for installation.
"