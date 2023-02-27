######################################################
#                  Helper makefile                   #
######################################################

# Root directory containing the top level CMakeLists.txt file
ROOT_DIR:=$(PWD)

# Generated binary directory
BIN_DIR:=$(ROOT_DIR)/bin

# Make options
#VERBOSE="VERBOSE=1"
PARALLEL_BUILD?=-j 4

# Build type can be either Debug or Release
BUILD_TYPE?=Debug

# Default targets
default: gcc
deploy: deploy-gcc

# Phony targets
.PHONY:

# Silent makefile
.SILENT:

# Format code
format:
	@echo "Formatting source code..."
	@find ./src -name '*.h' -or -name '*.cpp' | xargs clang-format -i
	@find ./examples -name '*.h' -or -name '*.cpp' | xargs clang-format -i
	@echo "Formatting done!"

# Build/clean all targets
all: gcc clang
clean: clean-gcc clean-clang
	@-rm -rf $(BIN_DIR)

# Targets for gcc build
GCC_BUILD_DIR:=$(ROOT_DIR)/build_gcc
GCC_BIN_DIR:=$(BIN_DIR)/gcc
GCC_COVERAGE_DIR:=$(ROOT_DIR)/coverage_gcc
gcc: $(GCC_BUILD_DIR)/Makefile
	@echo "Starting gcc build..."
	@mkdir -p $(GCC_BIN_DIR)
	@make --silent -C $(GCC_BUILD_DIR) $(VERBOSE) $(PARALLEL_BUILD)
	@echo "gcc build done!"

tests-gcc: $(GCC_BUILD_DIR)/Makefile
	@echo "Starting gcc tests..."
	@make --silent -C $(GCC_BUILD_DIR) test ARGS=--output-on-failure
	@echo "gcc tests done!"

coverage-gcc: tests-gcc
	@echo "Generating coverage report..."
	@mkdir -p $(GCC_COVERAGE_DIR)
	@lcov --capture --directory $(GCC_BUILD_DIR)/src/ --output-file $(GCC_COVERAGE_DIR)/coverage.info
	@lcov --remove $(GCC_COVERAGE_DIR)/coverage.info '/usr/*' '$(ROOT_DIR)/3rdparty/**' '$(ROOT_DIR)/**/tests/*.cpp' -o $(GCC_COVERAGE_DIR)/filtered_coverage.info
	@genhtml $(GCC_COVERAGE_DIR)/filtered_coverage.info --output-directory $(GCC_COVERAGE_DIR)
	@echo "Coverage report done!"

clean-gcc:
	@-rm -rf $(GCC_BUILD_DIR)
	@-rm -rf $(GCC_BIN_DIR)
	@-rm -rf $(GCC_COVERAGE_DIR)
	@echo "gcc build cleaned!"

$(GCC_BUILD_DIR)/Makefile:
	@echo "Generating gcc makefiles..."
	@mkdir -p $(GCC_BUILD_DIR)
	@mkdir -p $(GCC_BIN_DIR)
	@cd $(GCC_BUILD_DIR) && export CC=gcc && export CXX=g++ && cmake -D CMAKE_BUILD_TYPE=$(BUILD_TYPE) $(ROOT_DIR)


# Targets for clang build
CLANG_BUILD_DIR:=$(ROOT_DIR)/build_clang
CLANG_BIN_DIR:=$(BIN_DIR)/clang
clang: $(CLANG_BUILD_DIR)/Makefile
	@echo "Starting clang build..."
	@mkdir -p $(CLANG_BIN_DIR)
	@make --silent -C $(CLANG_BUILD_DIR) $(VERBOSE) $(PARALLEL_BUILD)
	@echo "clang build done!"

tests-clang: $(CLANG_BUILD_DIR)/Makefile
	@echo "Starting clang native tests..."
	@make --silent -C $(CLANG_BUILD_DIR) test ARGS=--output-on-failure
	@echo "clang native tests done!"

clean-clang:
	@-rm -rf $(CLANG_BUILD_DIR)
	@-rm -rf $(CLANG_BIN_DIR)
	@echo "clang build cleaned!"

$(CLANG_BUILD_DIR)/Makefile:
	@echo "Generating clang makefiles..."
	@mkdir -p $(CLANG_BUILD_DIR)
	@mkdir -p $(CLANG_BIN_DIR)
	@cd $(CLANG_BUILD_DIR) && export CC=clang && export CXX=clang++ && cmake -D CMAKE_BUILD_TYPE=$(BUILD_TYPE) -D _CMAKE_TOOLCHAIN_PREFIX=llvm- $(ROOT_DIR)
