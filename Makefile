run_container: container.build.stamp
	#docker run -it --rm --name=toy_codes_build --mount type=bind,source=${PWD},target=/src toy_codes/toy_codes_build:0.1  bash
	docker run -it --rm --name=toy_codes_build -v ${PWD}:/src:Z toy_codes/toy_codes_build:0.1  bash

container:
	docker build --format docker -t toy_codes/toy_codes_build:0.1 -f Dockerfile .
	touch container.build.stamp

container.build.stamp: Dockerfile
	make container
