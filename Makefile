SHELL := /bin/sh

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -I./src
LDFLAGS :=

TARGET := main
BUILD_DIR := build

SRC_DIRS := src src/dao src/model src/service
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
