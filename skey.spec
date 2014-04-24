Summary: S/Key suite of programs
Name: skey
%define version 1.1.5
Version: %{version}
Release: 1
Copyright: XFree/OpenBSD
Group: System Environment
Packager: Solaris Ports Collection 
Source: skey-1.1.5.tar.gz
BuildRoot: /tmp/skey
%description

                                S/Key
                                *****


This is the port of S/key implementation from OpenBSD source tree to
Solaris, Linux, *BSD, AIX and probably other *NIX systems. 

This port consists of the introduction of autoconf support and replacement of
OpenBSD library functions that are (regrettably) absent from other unices. 

Please refer to INSTALL document for information on how to install
S/key on your system.

This port has been tested on Solaris, Linux, NetBSD, FreeBSD and AIX.

All *new* code is released under XFree style license. 
The rest of the code is from OpenBSD source tree and has it's own 
licenses/copyrights, please refer to the source files for details.

Yuri Yudin <jjb@sparc.spb.su>
Saint Petersburg State University
Software Engineering & Expert Systems Laboratory


%prep
%setup -n skey-1.1.5

%build

CFLAGS="$RPM_OPT_FLAGS" \
    ./configure --prefix=/usr --sysconfdir=/etc/skey

make

%install
rm -rf $RPM_BUILD_ROOT

for I in usr/include/security usr/man/man1 usr/man/man5 usr/bin usr/lib; do
	mkdir -p $RPM_BUILD_ROOT/$I
done

/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/bin
/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/lib
/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/man
/usr/bin/install -c -d $RPM_BUILD_ROOT/etc
/usr/bin/install -c -d $RPM_BUILD_ROOT/etc/skey
/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/man/man1
/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/man/man8
/usr/bin/install -c -d $RPM_BUILD_ROOT/usr/include
/usr/bin/install -c -c -m 444 libskey.a $RPM_BUILD_ROOT/usr/lib
/usr/bin/install -c -c -m 444 skey.h $RPM_BUILD_ROOT/usr/include
for target in skey skeyinit skeyinfo skeyaudit; do \
        /usr/bin/install -c -c -s -m 555 $target $RPM_BUILD_ROOT/usr/bin; \
done
/usr/bin/install -c -c -m 555 skeyprune.pl $RPM_BUILD_ROOT/usr/bin/skeyprune
/usr/bin/install -c -c -m 444 skey.[01].out $RPM_BUILD_ROOT/usr/man/man1/skey.1
/usr/bin/install -c -c -m 444 skeyinit.[01].out $RPM_BUILD_ROOT/usr/man/man1/skeyinit.1
/usr/bin/install -c -c -m 444 skeyinfo.[01].out $RPM_BUILD_ROOT/usr/man/man1/skeyinfo.1
/usr/bin/install -c -c -m 444 skeyaudit.[01].out $RPM_BUILD_ROOT/usr/man/man1/skeyaudit.1
/usr/bin/install -c -c -m 444 skeyprune.[08].out $RPM_BUILD_ROOT/usr/man/man8/skeyprune.1
/bin/touch $RPM_BUILD_ROOT/etc/skey/skeykeys


%files

/usr/lib/libskey.a
/usr/include/skey.h 
/usr/include/sha1.h 
/usr/include/rmd160.h 
/usr/man/man1/skey.1
/usr/man/man1/skeyinit.1
/usr/man/man1/skeyinfo.1
/usr/man/man1/skeyaudit.1
/usr/man/man8/skeyprune.1
/etc/skey/skeykeys
/usr/bin/skey
/usr/bin/skeyinit
/usr/bin/skeyinfo
/usr/bin/skeyaudit
/usr/bin/skeyprune

