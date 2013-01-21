#! /bin/sh
# On MAC OS X, GNU libtoolize is named 'glibtoolize':
if [ `uname 2>/dev/null` == 'Darwin' ]
then
 glibtoolize
else
 libtoolize
fi
aclocal \
&& automake --gnu --add-missing \
&& autoconf
