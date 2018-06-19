CC=cc
CFLAGS=-g -O0 -Icommon

QBSP_FILES=qbsp/qbsp.c qbsp/region.c qbsp/map.c qbsp/csg4.c qbsp/surfaces.c \
	qbsp/merge.c qbsp/outside.c qbsp/portals.c qbsp/solidbsp.c qbsp/tjunc.c \
	qbsp/writebsp.c qbsp/nodraw.c qbsp/brush.c

all: bin/qbsp bin/bspinfo bin/qlumpy bin/qpal

clean:
	rm bin/qbsp bin/bspinfo bin/qlumpy bin/qpal

bin/qbsp: ${QBSP_FILES} common/cmdlib.c common/mathlib.c common/bspfile.c
	$(CC) $(CFLAGS) -Iqbsp $^ -o $@

bin/bspinfo: bspinfo/bspinfo.c common/cmdlib.c common/bspfile.c
	$(CC) $(CFLAGS) -Ibspinfo $^ -o $@

bin/qlumpy: qlumpy/qlumpy.c qlumpy/quakegrb.c common/cmdlib.c common/bmplib.c common/lbmlib.c common/scriplib.c common/wadlib.c
	$(CC) $(CFLAGS) -Iqlumpy $^ -o $@

bin/qpal: qlumpy/qpal.c common/cmdlib.c
	$(CC) $(CFLAGS) $^ -o $@
