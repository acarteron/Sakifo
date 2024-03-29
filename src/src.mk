SRC=$(wildcard $(ROOT)/$(DIR_SRC)/*.cpp)
OBJ=$(SRC:$(ROOT)/$(DIR_SRC)/%.cpp=$(ROOT)/$(DIR_OBJ)/%.o)

-include $(ROOT)/$(DIR_SRC)/requests/src.mk
-include $(ROOT)/$(DIR_SRC)/files/src.mk
-include $(ROOT)/$(DIR_SRC)/html/src.mk
#-include $(ROOT)/$(DIR_SRC)/data/src.mk
#-include $(ROOT)/$(DIR_SRC)/database/src.mk

# Compilation of the program
$(EXEC): $(OBJ) $(REQ) $(FILE) $(HTM) $(DYNAMIC_LIBS:%=$(DIR_LK)/$(DIR_LIB)/%.so) #  $(DATA) $(DBS)
	@echo "Linking ..... : $@"
	@$(GXX) -ldl -o $@ $^ $(CFLAGS)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/%.o: $(ROOT)/$(DIR_SRC)/%.cpp
	@echo "Compiling ... : $@"
	@$(GXX) -ldl -c -o $@ $< $(CFLAGS_OBJ)
