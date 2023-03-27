struct:
	cmake -S . -O output/

project:
	cp -R ./body ./${NAME}
	echo -n "\n${NAME}" >> ./project.list
	sed -i '1 s/body/${NAME}/' ./${NAME}/CMakeLists.txt

help:
	echo "make project NAME=<PROJECT_NAME> : creates new project"
	echo "make structure : creates cmake build structure"