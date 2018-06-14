# setup.sh

# It is tricky to to make this work correctly if it
# is not run from the directory where this script resides.
CALLED=$0
if [ "$CALLED" = bash ]; then
  CALLED=$BASH_SOURCE
fi
PKGDIR=`pwd`/`dirname $CALLED`
PKGDIR=`readlink -f $PKGDIR`
if [ ! -r $PKGDIR/setup.sh ]; then
  echo Unable to locate the sourced package script
else
  echo Setting up package at $PKGDIR

  if [ -z "$DUNETPC_VERSION" ]; then
    echo "Please set up dunetpc."
  else
    if [ -z "$ACLICDIR" ]; then
      export ACLICDIR=.aclic_$DUNETPC_VERSION
      echo set ACLICDIR to $ACLICDIR
    fi
    LIBDIR=$PKGDIR/$ACLICDIR/lib
    HAVELIB=
    for LIB in `echo $LD_LIBRARY_PATH | sed 's/:/ /g'`; do
      if [ "$LIB" = $LIBDIR ]; then
        HAVELIB=true
      fi
    done
    if [ -z "$HAVELIB" ]; then
      LD_LIBRARY_PATH=$LIBDIR:$LD_LIBRARY_PATH
      echo Added $LIBDIR to library path
    fi
  fi
fi
