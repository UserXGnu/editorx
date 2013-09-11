SOURCE_DIR = src/

libs:
	make -C $(SOURCE_DIR) -f Makefile libs

all:
	make -C $(SOURCE_DIR) -f Makefile all

clean:
	make -C $(SOURCE_DIR) -f Makefile clean
