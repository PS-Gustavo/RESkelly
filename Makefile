CC=g++
CFLAGS=-Wall -g

EXE=initial_build
SKELLYLIBS=		skelly/skelly.so \
				skelly/utils/logger/logger.o
VENDORLIBS=		skelly/vendors/spdlog/include/spdlog.lib
BODYLIBS=		body/utils/dlapi/dlapi.o \
				body/utils/skellyloader/skellyloader.o \
				body/body.o
LINKLIBS+=${SKELLYLIBS}
LINKLIBS+=${BODYLIBS}
BUILDLIBS=${VENDORLIBS}
BUILDLIBS+=${LINKLIBS}

### Build rules

$(EXE): $(LINKLIBS)
	$(CC) $(CFLAGS) -rdynamic -o output/$@ $(foreach lib, $^, output/$(basename $(notdir $(lib)).o)) -ldl

body/%.o: body/%.cpp
	$(CC) $(CFLAGS) $(foreach lib, $(BUILDLIBS), -I$(dir $(lib))) -c -o output/$(notdir $@) $<

skelly/%.o: skelly/%.cpp
	$(CC) $(CFLAGS) $(foreach lib, $(BUILDLIBS), -I$(dir $(lib))) -c -o output/$(notdir $@) $<

%.so: %.cpp
	$(CC) $(CFLAGS) -fPIC $(foreach lib, $(BUILDLIBS), -I$(dir $(lib))) -c -o output/$(basename $(notdir $@)).o $^
	$(CC) $(CFLAGS) -shared -o output/$(notdir $@) output/$(basename $(notdir $@)).o

%.lib:

### Build options

#	Build Skelly
skelly: $(SKELLYLIBS)
	echo "Skelly build complete"

#	Build Body
body: $(BODYLIBS)
	echo "Body build complete"

#	Build all and link into executable
all: $(EXE)
	echo "Build $(EXE) complete"

#	Link all build outputs into executable
link:
	$(CC) $(CFLAGS) -rdynamic -o output/$@ $(foreach lib, $(LINKLIBS), output/$(basename $(notdir $(lib)).o)) -ldl

#	Run executable
run:
	./output/$(EXE)

#	Build all and then run executable
arun: all run

#	Build Skelly and then run executable
srun: skelly run

#	Build Body and then run executable
brun: body run

#	Clean build outputs and executable
clean:
	rm output/*.o
	rm output/*.so
	rm output/$(EXE)

#	Clean all outputs and logs
clean_all:
	rm -rf output/*

manual:
	g++ -Wall -g -fPIC -Iskelly/ -Iskelly/utils/logger/ -Iskelly/vendors/spdlog/include/ -c -o output/skelly.o skelly/skelly.cpp
	g++ -Wall -g -shared -o output/skelly.so output/skelly.o
	g++ -Wall -g -Iskelly/ -Iskelly/utils/logger/ -Iskelly/vendors/spdlog/include/ -c -o output/logger.o skelly/utils/logger/logger.cpp
	g++ -Wall -g -Ibody/utils/dlapi/ -c -o output/dlapi.o body/utils/dlapi/dlapi.cpp
	g++ -Wall -g -Iskelly/ -Iskelly/utils/logger/ -Iskelly/vendors/spdlog/include/ -Ibody/utils/dlapi/ -Ibody/utils/skellyloader/ -c -o output/skellyloader.o body/utils/skellyloader/skellyloader.cpp
	g++ -Wall -g  -Iskelly/vendors/spdlog/include/  -Iskelly/  -Iskelly/utils/logger/  -Ibody/utils/dlapi/  -Ibody/utils/skellyloader/  -Ibody/ -c -o output/body.o body/body.cpp
	g++ -Wall -g -rdynamic -o output/executable  output/skelly.so  output/logger.o  output/dlapi.o output/skellyloader.o output/body.o -ldl

cmake:
	cmake -S .