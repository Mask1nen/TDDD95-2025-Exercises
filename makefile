.PHONY: clean

# Subdirectories containing .cpp files
EXERCISE_DIRS := $(wildcard */)

# Find all .cpp files in the subdirectories
CPP_FILES := $(foreach dir,$(EXERCISE_DIRS),$(wildcard $(dir)*.cpp))

# Define where the executables will be placed (subdirectories)
EXEC_FILES := $(CPP_FILES:.cpp=)

# Rule to compile and run each individual .cpp file
%: %.cpp
	@echo "Compiling $<..."
	g++ -o $@ $<      # Compile into the same directory
	@echo "Running $@..."
	./$@              # Run the executable

# Clean up: Remove all executables in the subdirectories
clean:
	@echo "Cleaning up executables..."
	rm -f $(EXEC_FILES)
	@echo "All executables removed."
