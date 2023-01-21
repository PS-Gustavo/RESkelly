
# environment variables
SKEL=skelly
SRC=src
OUTPUT=output

SKEL_EXAMPLES=${SKEL}/examples
SRC_EXAMPLES=${SRC}/examples

# sanity paths
SKEL_SANITY=${SKEL_EXAMPLES}/sanity
SRC_SANITY=${SRC_EXAMPLES}/sanity
OUTPUT_SANITY=${OUTPUT}/sanity
PATH_SANITY=${LD_LIBRARY_PATH}:${PWD}/${OUTPUT_SANITY}


help:
	echo "make sanity: runs the sanity example"

sanity: ${SKEL_SANITY}/sanity.cpp ${SKEL_SANITY}/sanity.h
#	create sanity folder if it doesn't exist
	if [ ! -d ${OUTPUT}/sanity ]; then \
		echo "Creating sanity directory..."; \
		mkdir ${OUTPUT}/sanity; \
	fi
#	create .so from platform sanity check
	g++ -I${SKEL_SANITY}/ ${SKEL_SANITY}/sanity.cpp -shared -o ${OUTPUT_SANITY}/sanity.so
#	create application executable
	g++ -I${OUTPUT}/sanity -Lsanity.so -Wall -o ${OUTPUT}/sanity/sanity ${SRC_SANITY}/ex_sanity.cpp
#	add library path and run executable
	export LD_LIBRARY_PATH=${PATH_SANITY}; ${OUTPUT}/sanity/sanity;
