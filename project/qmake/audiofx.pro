TEMPLATE = subdirs

SUBDIRS = \
    lib \
    gen

lib.file = $$PWD/libaudiofx.pro
gen.file = $$PWD/afxgen.pro

gen.depends = lib
