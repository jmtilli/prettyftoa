#!/bin/sh

if [ '!' -f "libprettyftoa.a" -o '!' -f "libprettyftoa.so" -o '!' -f "libprettyftoa.so.1" ]; then
  echo "prettyftoa not made"
  exit 1
fi

PREFIX="$1"

if [ "a$PREFIX" = "a" ]; then
  PREFIX=/usr/local
fi

P="$PREFIX"
H="`hostname`"

if [ '!' -w "$P" ]; then
  echo "No write permissions to $P"
  exit 1
fi
if [ '!' -d "$P" ]; then
  echo "Not a valid directory: $P"
  exit 1
fi

instlib()
{
  if [ -e "$P/lib/$1" ]; then
    ln "$P/lib/$1" "$P/lib/.$1.pftinstold.$$.$H" || exit 1
  fi
  cp "$1" "$P/lib/.$1.pftinstnew.$$.$H" || exit 1
  mv "$P/lib/.$1.pftinstnew.$$.$H" "$P/lib/$1" || exit 1
  if [ -e "$P/lib/.$1.pftinstold.$$.$H" ]; then
    # If you mount binaries across NFS, and run this command on the NFS server,
    # you might want to comment out this rm command.
    rm "$P/lib/.$1.pftinstold.$$.$H" || exit 1
  fi
}
instinc()
{
  if [ -e "$P/include/$1" ]; then
    ln "$P/include/$1" "$P/include/.$1.pftinstold.$$.$H" || exit 1
  fi
  cp "$1" "$P/include/.$1.pftinstnew.$$.$H" || exit 1
  mv "$P/include/.$1.pftinstnew.$$.$H" "$P/include/$1" || exit 1
  if [ -e "$P/include/.$1.pftinstold.$$.$H" ]; then
    # If you mount binaries across NFS, and run this command on the NFS server,
    # you might want to comment out this rm command.
    rm "$P/include/.$1.pftinstold.$$.$H" || exit 1
  fi
}
instsym()
{
  if [ "`readlink "$P/lib/$1"`" != "libprettyftoa.so.1" ]; then
    ln -s libprettyftoa.so.1 "$P/lib/.$1.pftinstnew.$$.$H" || exit 1
    mv "$P/lib/.$1.pftinstnew.$$.$H" "$P/lib/$1" || exit 1
  fi
}

instlib libprettyftoa.a
instlib libprettyftoa.so.1
instsym libprettyftoa.so

instinc prettyftoa.h

echo "All done, prettyftoa has been installed to $P"
