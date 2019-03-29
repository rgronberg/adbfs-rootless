CXXFLAGS=-Wall $(shell pkg-config fuse --cflags)
LDFLAGS=-Wall $(shell pkg-config fuse --libs)

TARGET=adbfs
DESTDIR?=/
INSTALL_DIR?=${DESTDIR}/usr/

all:	$(TARGET)

debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGET)

adbfs.o: adbfs.cpp utils.h
	$(CXX) -c -o adbfs.o adbfs.cpp $(CXXFLAGS) $(CPPFLAGS)

cache_manager.o: cache_manager.cpp cache_manager.h
	$(CXX) -c -o cache_manager.o cache_manager.cpp $(CXXFLAGS) $(CPPFLAGS)

$(TARGET): adbfs.o cache_manager.o
	$(CXX) -o $(TARGET) adbfs.o cache_manager.o $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.o html/ latex/ $(TARGET)

doc: Doxyfile
	doxygen $<

install: ${TARGET}
	install -d ${INSTALL_DIR}/bin
	install -s $< ${INSTALL_DIR}/bin/
