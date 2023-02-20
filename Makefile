CC=g++
CFLAGS=-Wall -g

EXE=initial_build
LIBS=skelly/skelly.so body/utils/dlapi/dlapi.o body/utils/skellyloader/skellyloader.o body/body.o

all: $(EXE)
	echo "Build $(EXE) complete"

$(EXE): $(LIBS)
	$(CC) $(CFLAGS) -rdynamic -o output/$@ $(foreach lib, $^, output/$(basename $(notdir $(lib)).o)) -ldl

body/%.o: body/%.cpp
	$(CC) $(CFLAGS) $(foreach lib, $(LIBS), -I$(dir $(lib))) -c -o output/$(notdir $@) $<

%.so: %.cpp
	echo $@ 1
	$(CC) $(CFLAGS) -fPIC -I$(dir $@) -c -o output/$(basename $(notdir $@)).o $^
	$(CC) $(CFLAGS) -shared -o output/$(notdir $@) output/$(basename $(notdir $@)).o

run:
	./output/$(EXE)

brun: all run

clean:
	rm output/*.o
	rm output/*.so
	rm output/initial_build

clean_all:
	rm -rf output/*

manual:
	$(CC) $(CFLAGS) -Iskelly/ -fPIC -c -o output/skelly.o skelly/skelly.cpp
	$(CC) $(CFLAGS) -shared -o output/skelly.so output/skelly.o
	
	$(CC) $(CFLAGS) -Ibody/utils/dlapi -c -o output/dlapi.o body/utils/dlapi/dlapi.cpp 
	$(CC) $(CFLAGS) -Ibody/utils/skellyloader/ -Ibody/utils/dlapi -Iskelly -c -o output/skellyloader.o body/utils/skellyloader/skellyloader.cpp
	$(CC) $(CFLAGS) -Ibody -Ibody/utils/skellyloader/ -Ibody/utils/dlapi -Iskelly -c -o output/body.o body/body.cpp
	$(CC) $(CFLAGS) -rdynamic -o output/body output/*.o -ldl