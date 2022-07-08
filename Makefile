build:
	$(CXX) $(ENTRY) -O$(OFLAGS) -o $(OUTPUT) $(CXXFLAGS)

info:
	@echo trash version $(VERSION)

clean:
	rm -rf *.o

install: build
	mkdir -p $(DDIR)$(PREFIX)/bin
	cp -f $(OUTPUT) $(DDIR)$(PREFIX)/bin
	chmod 755 $(DDIR)$(PREFIX)/bin/$(OUTPUT)

dist: clean
	mkdir -p trash-$(VERSION)
	cp -R *.* trash-$(VERSION)
	tar -cf trash-$(VERSION) | gzip > trash-$(VERSION).tar.gz
	rm -rf trash-$(VERSION)
	

CXX=clang++
ENTRY=main.cpp
OFLAGS=3
OUTPUT=trash
CXXFLAGS=-Wall

# directory info
PREFIX = /usr/local

# version info
VERSION=1.0
