version := $(file < VERSION)

.PHONY: default
default: build

src_dir := src
output_dir := output
project := hello
ifdef AT_CONTAINER
program := $(output_dir)/world
object_dir := $(output_dir)/.o
find = $(foreach e,$(wildcard $(1:=/*)),$(if $(filter $2,$e),$e,$(strip $(call find,$e,$2))))
cpp_files := $(call find,$(src_dir),%.cpp)
sources := $(filter-out %.test.cpp,$(cpp_files))
objects := $(sources:%.cpp=$(object_dir)/%.o)

CXXFLAGS := -Wpedantic -Wall -Wextra -O2 -g
CPPFLAGS := -I $(CURDIR)/$(src_dir)
DEPFLAGS = -MMD -MP -MT $@
LDLIBS := -pthread -lfmt -lboost_program_options

.SUFFIXES:
.SECONDEXPANSION:
.SECONDARY:

$(object_dir)/%.o: %.cc $(object_dir)/%.d | $$(@D)/
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(DEPFLAGS) -o $@ $<

$(object_dir)/%.o: %.cpp $(object_dir)/%.d | $$(@D)/
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(DEPFLAGS) -o $@ $<

%/:
	@mkdir -p $@

.PRECIOUS: %/
depends := $(objects:.o=.d) 
$(depends):

-include $(depends)

endif

ifndef AT_CONTAINER
include Container.mk

build_env_image := cont-cpp-build-env:$(version)

container_build = $(CONTAINER_RUNTIME) build \
	-f Containerfile \
	$(container_build_options) \
	--build-arg BUILD_ENV_BASE_IMAGE=$(BUILD_ENV_BASE_IMAGE) \
	--build-arg PROJECT=$(project) \
	--build-arg OUTPUT_DIR=$(output_dir) \
	.

container_run = $(CONTAINER_RUNTIME) run \
	--rm -t -h $(build_env_image) -e AT_CONTAINER=true \
	--mount type=bind,source=$(CURDIR),target=/root/$(src_dir) -w /root/$(src_dir) \
	$(container_run_options) \
	--pull never $(build_env_image)
endif

.PHONY: build-env
build-env: container_build_options := -t $(build_env_image) --target build-env
build-env:
	$(container_build)


.PHONY: build
ifdef AT_CONTAINER
build: $(program)
$(program): $(objects)
	$(CXX) -o $@ $^ $(LDLIBS)	
else
build:
	@$(container_run) make build
endif


.PHONY: run
ifdef AT_CONTAINER
run:
	@$(program)
else
run:
	@$(container_run) make run
endif

.PHONY: image
image: container_build_options := -t $(project):$(version) --target image
image:
ifdef AT_CONTAINER
	$(error You can't build image at container)
else
	$(container_build)
endif

.PHONY: clean
ifdef AT_CONTAINER
clean:
	@$(RM) -rf $(objects) $(program) $(depends) $(object_dir) $(output_dir)
else
clean:
	@$(container_run) make clean
endif
