# Copyright (c) 1995, 1996 Cygnus Support
#
# The authors hereby grant permission to use, copy, modify, distribute,
# and license this software and its documentation for any purpose, provided
# that existing copyright notices are retained in all copies and that this
# notice is included verbatim in any distributions. No written agreement,
# license, or royalty fee is required for any of the authorized uses.
# Modifications to this software may be copyrighted by their authors
# and need not follow the licensing terms described here, provided that
# the new terms are clearly indicated on the first page of each file where
# they apply.
#

DESTDIR =
srcdir = ../../../../newlib-2.5.0.20171222/libgloss/doc
VPATH = ../../../../newlib-2.5.0.20171222/libgloss/doc

prefix = /usr
exec_prefix = ${prefix}
datarootdir = ${prefix}/share

mandir = ${datarootdir}/man
man1dir = $(mandir)/man1
infodir = ${datarootdir}/info

MAKEINFO = makeinfo
TEXI2DVI = TEXINPUTS=$(TEXIDIR):$(srcdir):$$TEXINPUTS texi2dvi

INSTALL	= /usr/bin/install -c
INSTALL_PROGRAM = /usr/bin/install -c
INSTALL_DATA = /usr/bin/install -c -m 644

# Where to find texinfo.tex to format docn with TeX
TEXIDIR = $(srcdir)/../../texinfo

MANPAGES =

all:

info:	porting.info 

html:	porting.html

dvi:	porting.dvi 

pdf:	porting.pdf

ps:	porting.ps 

doc:	info dvi

porting: porting.dvi porting.info

######################################################################
# DOCUMENTATION TARGETS
# TeX output
porting.dvi: $(srcdir)/porting.texi $(srcdir)/porting.texi
	$(TEXI2DVI) $(srcdir)/porting.texi

porting.pdf: $(srcdir)/porting.texi $(srcdir)/porting.texi
	$(TEXI2DVI) --pdf $(srcdir)/porting.texi

# info file for online browsing
porting.info: $(srcdir)/porting.texi $(srcdir)/porting.texi
	$(MAKEINFO) -I $(srcdir) -o porting.info $(srcdir)/porting.texi

porting.html: $(srcdir)/porting.texi $(srcdir)/porting.texi
	$(MAKEINFO) --html -I $(srcdir) -o porting.html $(srcdir)/porting.texi

porting.ps: porting.dvi
	dvips -f porting.dvi > porting.ps
		
#   different targets for -ms, -mm, -me
# Try to use a recent texi2roff.  v2 was put on prep in jan91.
# If you want an index, see texi2roff doc for postprocessing 
# and add -i to texi2roff invocations below.
# Workarounds for texi2roff-2 (probably fixed in later texi2roff's, delete
#    correspondint -e lines when later texi2roff's are current)
# + @ifinfo's deleted explicitly due to texi2roff-2 bug w nested constructs.
# + @c's deleted explicitly because texi2roff sees texinfo commands in them
# + @   (that's at-BLANK) not recognized by texi2roff, turned into blank
# + @alphaenumerate is ridiculously new, turned into @enumerate

# roff output (-ms)
porting.ms: $(srcdir)/porting.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e '/^@ifinfo/,/^@end ifinfo/d' \
		-e '/^@c/d' \
		-e 's/{.*,,/{/' \
		-e 's/@ / /g' \
		-e 's/^@alphaenumerate/@enumerate/g' \
		-e 's/^@end alphaenumerate/@end enumerate/g' \
		$(srcdir)/porting.texi | \
	$(TEXI2ROFF) -ms | \
	sed -e 's/---/\\(em/g' \
	>porting.ms 

# roff output (-mm)
# '@noindent's removed due to texi2roff-2 mm bug; if yours is newer, 
#   try leaving them in
porting.mm: $(srcdir)/porting.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e '/^@ifinfo/,/^@end ifinfo/d' \
		-e '/^@c/d' \
		-e 's/{.*,,/{/' \
		-e '/@noindent/d' \
		-e 's/@ / /g' \
		-e 's/^@alphaenumerate/@enumerate/g' \
		-e 's/^@end alphaenumerate/@end enumerate/g' \
		$(srcdir)/porting.texi | \
	$(TEXI2ROFF) -mm | \
	sed -e 's/---/\\(em/g' \
		>porting.mm

# roff output (-me)
porting.me: $(srcdir)/porting.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e '/^@ifinfo/,/^@end ifinfo/d' \
		-e '/^@c/d' \
		-e 's/{.*,,/{/' \
		-e 's/@ / /g' \
		-e 's/^@alphaenumerate/@enumerate/g' \
		-e 's/^@end alphaenumerate/@end enumerate/g' \
		$(srcdir)/porting.texi | \
	$(TEXI2ROFF) -me | \
	sed -e 's/---/\\(em/g' \
	>porting.me 


######################################################################

clean mostlyclean:
	-rm -f *.o *~ \#* core *.aux *.cp *.dvi *.fn *.ky *.log *.pg *.toc \
	*.tp *.vr *.cps *.fns *.kys *.pgs *.tps *.vrs *.info* *.1 *.ps

maintainer-clean realclean: clean
	-rm -f 

install: 

install-info: info
	for i in *.info* ; do \
		$(INSTALL_DATA) $$i $(DESTDIR)$(infodir)/$$i ; \
	done

clean-info:
	-rm -rf *.info*

distclean:      clean
	-rm -f Makefile config.cache config.log config.status 

Makefile: Makefile.in config.status 
	$(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck
