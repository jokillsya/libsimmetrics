#! /bin/sh

if hash libtoolize 2>&-
then
  libtoolize --automake
else
  glibtoolize --automake
fi

aclocal \
&& automake --gnu --add-missing \
&& autoconf
