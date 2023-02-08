




CC=g++
CFLAGS=-Wall -g
SKELLY=skelly/skelly.cpp skelly/api/skellyapi.cpp
DLS=skelly/skelly.so
BODY=body/body.cpp body/utils/dlapi.cpp skelly/api/skellyapi.cpp
OUTPUT=body/body.out

all: $(DLS) $(OUTPUT)

%.so: %.cpp
	$(CC) $(CFLAGS) $(foreach lib, ${SKELLY}, -I${dir ${lib}}) -fPIC -shared -o output/$(shell basename $@) $(foreach lib, ${SKELLY}, ${lib})

%.out:
	$(CC) $(CFLAGS) $(foreach lib, ${BODY}, -I${dir ${lib}}) -o output/$(shell basename $@) $(BODY)

clean:
	echo "what"