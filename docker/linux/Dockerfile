FROM ubuntu:20.04
ENV TZ=Europe/Warsaw
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y \
	git \
	build-essential \
	cmake
	
RUN git clone https://github.com/piotoor/ruGroupAnalyser.git && \
	cd ruGroupAnalyser && \
	cd lib && \
	git submodule update --init --recursive && \
	cd .. && \
	mkdir build && \
	cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON && \
	make all
	
ENTRYPOINT ["ruGroupAnalyser/build/release/ruGroupAnalyser_tst"]
