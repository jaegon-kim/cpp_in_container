# cpp_in_container
C++ build & execution environment in container.

## Build & Run

* make build-env

This will construct a container image which includes g++ compiler and libraries.

<pre>
<code>
    $ docker images
    REPOSITORY           TAG       IMAGE ID       CREATED              SIZE
    cont-cpp-build-env   0.0.1     b7685b02db9a   About a minute ago   1.44GB
    ubuntu               22.04     58db3edaf2be   9 days ago           77.8MB
</code>
</pre>

* make (make build)

This will build program. It will mount local directory on the cont-cpp-build-env, and build.    


* make run

This will run the program. It will mount local directory on the ont-cpp-build-env, and run the program.   


* make term

This will temr the container of program by using docker rm -f $(container name)    

* make image

This will build the container image.   


* make clean

This will clean which was created by make(make build).    

 
* (Non container build environment)

sudo apt-get install -y libfmt-dev
sudo apt-get install -y libboost-all-dev


## EPI(Elements of Programming Interviews in C++) problem solvings for fun
Various algorithm problem solving over C++ container.

https://github.com/jaegon-kim/cpp_in_container/tree/main/src/epi
