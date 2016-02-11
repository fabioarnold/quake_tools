QBSP_FILES=qbsp/qbsp.c qbsp/region.c qbsp/map.c qbsp/csg4.c qbsp/surfaces.c \
	qbsp/merge.c qbsp/outside.c qbsp/portals.c qbsp/solidbsp.c qbsp/tjunc.c \
	qbsp/writebsp.c qbsp/nodraw.c qbsp/brush.c

all: bin/qbsp bin/bspinfo

bin/qbsp: ${QBSP_FILES} common/cmdlib.c common/mathlib.c common/bspfile.c
	cc -Icommon -Iqbsp $^ -o $@

bin/bspinfo: bspinfo/bspinfo.c common/cmdlib.c common/bspfile.c
	cc -Icommon -Ibspinfo $^ -o $@
