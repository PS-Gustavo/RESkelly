struct:
	[ -d ./output ] || mkdir -p ./output
	cmake -S . -O output/

project:
	cp -R ./body ./${NAME}
	echo -n "\n${NAME}" >> ./config/project.list
	sed -i '1 s/body/${NAME}/' ./${NAME}/CMakeLists.txt

cfg:
	open ./config/project.config

help:
	echo "make project NAME=<PROJECT_NAME> : creates new project"
	echo "make struct : creates cmake build structure"