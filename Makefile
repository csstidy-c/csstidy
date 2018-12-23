name=csstidy
WORKINGDIR=$(shell pwd)
DIRNAME=$(shell basename `pwd`)
#VERSION=$(shell basename `pwd` |sed 's,$(name)-,,')
#VERSION=$(shell date +%Y%m%d)
VERSION=$(shell grep "#define.*FILE_VERSION" csstidy/csspp_private.h|cut -d'"' -f2)
RPM_SPECS_DIR=$(shell rpm -E '%_specdir')
RPM_SOURCES_DIR=$(shell rpm -E '%_sourcedir')

HOSTCC=gcc
#HOSTCC=$(shell if type gcc-4.1 >/dev/null 2>&1;then echo gcc-4.1;else echo gcc;fi)
HOSTCXX=g++
#INCLUDES=-I$(WORKINGDIR)/include -I$(WORKINGDIR)
#BASE_CFLAGS=-std=c99 -pedantic -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -DNO_PAGE_ALLOC_ERROR
OPTFLAGS=-O2 -fomit-frame-pointer $(RPM_OPT_FLAGS)
#EXTRACFLAGS=-Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -pipe
#HOSTCFLAGS=$(BASE_CFLAGS) $(OPTFLAGS) $(EXTRACFLAGS) $(EMBEDDED_CFLAGS) $(INCLUDES)
HOSTCFLAGS=$(OPTFLAGS)
HOSTLD=ld
HOSTLDFLAGS=

CFLAGS=$(HOSTCFLAGS)
LDCFLAGS=$(HOSTCFLAGS) -Wl,-z,noexecstack
CC=$(HOSTCC)
EXTRA_CFLAGS=
LD=$(HOSTLD)
LDFLAGS=$(HOSTLDFLAGS)
STRIP_ARGS=-s -R .note -R .comment
STRIP=strip $(STRIP_ARGS)
RM=/bin/rm
CP=/bin/cp -PpR 
MV=/bin/mv
LN=/bin/ln
INSTALL=install

DESTDIR=/
prefix=$(DESTDIR)/opt/$(name)
prefix=$(DESTDIR)/usr
exec_prefix=$(prefix)
bindir=$(prefix)/bin
mandir=$(prefix)/share/man
sbindir=$(prefix)/sbin
sysconfdir=$(DESTDIR)/etc
sysconfigdir=$(DESTDIR)/etc/sysconfig
datadir=$(prefix)/share
includedir=$(prefix)/include
libdir=$(prefix)/lib
libexecdir=$(prefix)/libexec
localstatedir=/var
sharedstatedir=$(prefix)/com
infodir=$(prefix)/share/info

RELEASE_DIR=release
CSSTIDYOBJS= \
	csstidy/background.o \
	csstidy/conversions.o \
	csstidy/cssopt.o \
	csstidy/csspp_globals.o \
	csstidy/misc.o \
	csstidy/csstidy.o \
	csstidy/file_functions.o \
	csstidy/umap.o \
	csstidy/main.o \
	csstidy/prepare.o \
	csstidy/parse_css.o \
	csstidy/trim.o \
	csstidy/print_css.o \
	csstidy/important.o \

MANPAGES= \
	csstidy/csstidy.1 \

.cpp.o:
	$(CXX) -o $(RELEASE_DIR)/$@ -c $(CFLAGS) $<

.PHONY: clean savets restorets ci pull csstidy mangz

all: releasedir $(CSSTIDYOBJS) csstidy

csstidy:
	cd $(RELEASE_DIR); $(CXX) $(LDCFLAGS) -o $(name)/$(name) $(CSSTIDYOBJS)

install: all mangz
	$(STRIP) $(RELEASE_DIR)/$(name)/$(name)
	mkdir -p $(bindir) $(mandir)/man1
	$(CP) $(RELEASE_DIR)/$(name)/$(name) $(bindir)/$(name)
	$(CP) $(RELEASE_DIR)/$(name)/$(name).1* $(mandir)/man1/
	-chown root:root $(bindir)/$(name) $(mandir)/man1/$(name).1*
	chmod 755 $(bindir)/$(name)
	chmod 644 $(mandir)/man1/$(name).1*

releasedir:
	mkdir -p $(RELEASE_DIR)/$(name)

clean::
	$(RM) -rf $(RELEASE_DIR)
 
distclean: clean
	#$(MAKE) savets

mangz: releasedir
	for f in $(MANPAGES); \
	do \
	  gzip -9 -f <$$f >$$f.gz; \
	  touch -r $$f $$f.gz; \
	  $(CP) $$f.gz $(RELEASE_DIR)/$(name)/; \
	done

dist: tgz

tgz: distclean savets manhtml
	@echo
	@echo Dir: $(DIRNAME) Version: $(VERSION)
	@perl -p -i -e 's,^Version:.*,Version: $(VERSION),' $(name).spec
	cd ..; \
	  $(RM) -rf $(DIRNAME)-$(VERSION); \
	  $(CP) $(DIRNAME) $(DIRNAME)-$(VERSION); \
	  find $(DIRNAME)-$(VERSION) -name .svn -exec $(RM) -rf {} \; 2>/dev/null; \
	  find $(DIRNAME)-$(VERSION) -type d -exec rmdir -p {} \; 2>/dev/null; \
	  tar cf - $(DIRNAME)-$(VERSION) | gzip -9 -f >$(DIRNAME)-$(VERSION).tar.gz

bintgz: tgz all
	@echo Dir: $(DIRNAME) Version: $(VERSION)
	cd ..; \
	  $(RM) -rf $(DIRNAME)-$(VERSION); \
	  $(CP) $(DIRNAME) $(DIRNAME)-$(VERSION); \
	  find $(DIRNAME)-$(VERSION) -name .svn -exec $(RM) -rf {} \; 2>/dev/null; \
	  find $(DIRNAME)-$(VERSION) -type d -exec rmdir -p {} \; 2>/dev/null; \
	  gzip -9 -f $(DIRNAME)-$(VERSION)/*/*.1; \
	  tar cf - \
	    $(DIRNAME)-$(VERSION)/tools/actionwhenfileold \
	    $(DIRNAME)-$(VERSION)/*/*.1.gz \
	    | gzip -9 -f >$(DIRNAME)-$(VERSION)-bin.tar.gz

rpm: tgz
	$(CP) $(NAME).spec $(SPECS_DIR)/
	cd ..;$(CP) $(DIRNAME).tar.gz $(SOURCES_DIR)/
	cd $(SPECS_DIR); rpmbuild -ba $(NAME).spec

manhtml:
	rman -v # PolyglotMan
	for f in */*.[18];do echo $$f;rman -f html $$f|sed '/HREF="[^#]/s,A HREF,/A HREF,' >$$f.html;touch -r $$f $$f.html;done

manhtml-clean:
	$(RM) -f */*.[18].html

ci: savets
	read -p 'comment for commit: ' comment && git commit -am "$$comment" && git push

pull:
	git pull
	$(MAKE) restorets

savets: distclean
	find . -type f -o -type d|egrep -v "\.svn\/|\.svn$$|\/\.git\/|\/\.git$$"|grep -v "\.timestamps"|sort|while read f;do echo $$(date +%s -r "$$f") "$$f";done >.timestamps;true

restorets:
	while read ts f;do test -e "$$f" && touch -d@$$ts "$$f";done<.timestamps;true
