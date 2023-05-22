container:
	docker build -t toy_codes/toy_codes_build:0.1 -f Dockerfile .

run_container:
	docker run -it --rm --name=toy_codes_build --mount type=bind,source=${PWD},target=/src toy_codes/toy_codes_build:0.1  bash
