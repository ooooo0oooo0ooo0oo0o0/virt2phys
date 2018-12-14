CXX     = g++
CFLAGS  = -std=c++14 -Wall -MMD -MP
LDFLAGS =
LIBS    =
INCLUDE = -I.
TARGET  = ./$(shell basename `readlink -f .`)
SRC_DIR = .

SRC     = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = ./.obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))
DEPENDS = $(OBJ:.o=.d)

$(TARGET): $(OBJ) $(LIBS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	-mkdir -p $(OBJ_DIR)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -rf $(OBJ_DIR) $(DEPENDS) $(TARGET)

-include $(DEPENDS)

