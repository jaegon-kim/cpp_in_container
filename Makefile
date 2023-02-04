version := $(file < VERSION)

.PHONY: default
default: build

ifdef AT_CONTAINER
src_dir := src
output_dir := output
object_dir := $(output_dir)/.o
find = $(foreach e,$(wildcard $(1:=/*)),$(if $(filter $2,$e),$e,$(strip $(call find,$e,$2))))
cpp_files := $(call find,$(src_dir),%.cpp)
sources := $(filter-out %.test.cpp,$(cpp_files))
objects := $(sources:%.cpp=$(object_dir)/%.o)
program := $(output_dir)/$(src_dir)

CXXFLAGS := -Wpedantic -Wall -Wextra -O2 -g
CPPFLAGS := -I $(CURDIR)
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


include Container.mk

dev_env_image := cont-dev-env:$(version)

container_build = $(CONTAINER_RUNTIME) build \
	-f Containerfile \
	$(container_build_options) \
	--build-arg DEV_ENV_BASE_IMAGE=$(DEV_ENV_BASE_IMAGE) \
	.

container_run = $(CONTAINER_RUNTIME) run \
	--rm -t -h cont-dev-env -e AT_CONTAINER=true \
	--mount type=bind,source=$(CURDIR),target=/root/$(src_dir) -w /root/$(src_dir) \
	$(container_run_options) \
	--pull never $(dev_env_image)


.PHONY: dev-env
dev-env: container_build_options := -t $(dev_env_image) --target dev-env
dev-env:
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


.PHONY: clean
ifdef AT_CONTAINER
clean:
	@$(RM) -rf $(objects) $(program) $(depends) $(object_dir) $(output_dir)
else
clean:
	@$(container_run) make clean
endif
