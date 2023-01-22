
# base variables
SKEL=skelly
BODY=body
OUTPUT=output
SANITY=sanity
LOGS=${OUTPUT}/logs

# sanity paths (to be deprecated)
SKEL_SANITY=${SKEL_EXAMPLES}/${SANITY}
BODY_SANITY=${BODY_EXAMPLES}/${SANITY}
OUTPUT_SANITY=${OUTPUT}/${SANITY}
PATH_SANITY=${LD_LIBRARY_PATH}:${PWD}/${OUTPUT_SANITY}

# skelly paths
SKEL_EXAMPLES=${SKEL}/examples
SKEL_OUTPUT=${OUTPUT}/${SKEL}

# body paths
BODY_EXAMPLES=${BODY}/examples
BODY_OUTPUT=${OUTPUT}/${BODY}

# build variables
EXE = body_dev_output
UNAME_S := $(shell uname -s)
TARGET = $(BODY)/body.cpp
SOURCES =  $(BODY)/so_fetch.cpp
SOLIBS = $(SKEL)/skelly.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(TARGET))))
OBJS += $(addsuffix .o, $(OUTPUT)/$(basename $(notdir $(SOURCES))))
OBJS += $(addsuffix .so, $(OUTPUT)/$(basename $(notdir $(SOLIBS))))
CXX = g++
CXXFLAGS = -std=c++11 -I$(SKEL) -I$(BODY)
CXXFLAGS += -g -Wall -Wformat

#	Build flags for Linux
ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

#	create param $(1) output folder if it doesn't exist
define new_dir
	if [ ! -d $(1) ]; then \
		echo "Creating $(1) directory..."; \
		mkdir $(1); \
	fi
endef

init:
	@$(call new_dir, ${OUTPUT})
	@$(call new_dir, ${LOGS})

help:
	echo "make sanity: runs SO sanity"
	echo "make build: builds Skelly"
	echo "make body: builds body integrated to Skelly SO"

sanity: ${SKEL_SANITY}/sanity.cpp ${SKEL_SANITY}/sanity.h log_init
	@$(call new_dir, ${OUTPUT_SANITY})
#	create .so from platform sanity check
	g++ --verbose -o ${OUTPUT_SANITY}/sanity.so -I${SKEL_SANITY}/ -shared ${SKEL_SANITY}/sanity.cpp 2> ${LOGS}/sanity.so.log
#	create application executable
	g++ --verbose -o ${OUTPUT_SANITY}/sanity -I${OUTPUT_SANITY} -Lsanity.so -Wall ${BODY_SANITY}/ex_sanity.cpp 2> ${LOGS}/sanity.log
#	add library path and run executable
	export LD_LIBRARY_PATH=${PATH_SANITY}; ${OUTPUT_SANITY}/sanity;

#	create .so from skelly 
build: ${SKEL}/skelly.cpp ${SKEL}/skelly.h log_init
	@$(call new_dir, ${SKEL_OUTPUT})
	g++ -fPIC --verbose -o ${SKEL_OUTPUT}/skelly.so -I${SKEL}/ -shared ${SKEL}/skelly.cpp 2> ${LOGS}/skelly.so.log

#body: ${BODY}/body.cpp ${BODY}/body.h log_init
#	@$(call new_dir, ${BODY_OUTPUT})
#	g++ --verbose -o ${OUTPUT}/body/body -I${SKEL_OUTPUT}/ -Lskelly.so ${BODY}/body.cpp 2> ${LOGS}/body.log

##---------------------------------------------------------------
##
##---------------------------------------------------------------

$(OUTPUT)/%.o: $(BODY)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT)/%.so: $(SKEL)/%.cpp
	$(CXX) $(CXXFLAGS) -c -shared -o $@ $<

body: init ${EXE}
	@echo Build complete.

$(EXE): $(OUTPUT)/$(OBJS)
	${CXX} -o ${OUTPUT}/$@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -rf ${OUTPUT}/