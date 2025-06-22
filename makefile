#File to compile caesar

###################################################################################################################################################
###                                                                 MACROS                                                                      ###
###################################################################################################################################################
#Macro C2O: Change all source name's elements from ./src%.c or ./src%.cpp to ./obj%.o.
#$(1) Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

###################################################################################################################################################
###                                                                 CONFIG                                                                      ###
###################################################################################################################################################
APP     := caesar
COMPCPP := g++
CCFLAGS := -Wall -pedantic -std=c++17
RM      := rm -r
MKDIR   := mkdir -p
SRC     := ./src
OBJ     := ./obj

ifdef DEBUG
   CCFLAGS += -g
else
   CCFLAGS += -O2
endif

SRCSUBDIRS   := $(shell find $(SRC) -type d)
OBJSUBDIRS   := $(patsubst $(SRC)%,$(OBJ)%,$(SRCSUBDIRS))
ALLCPPS      := $(shell find $(SRC) -type f -iname *.cpp)
ALLOBJSOFCPP := $(foreach SRCFILE,$(ALLCPPS),$(call C2O,$(SRCFILE)))

.PHONY : show clean cleanall

#Link all proyect's elememts.
$(APP) : $(OBJSUBDIRS) $(ALLOBJSOFCPP)
	$(COMPCPP) -o $(APP) $(ALLOBJSOFCPP) $(CCFLAGS)

#Compile proyect's elements.
$(OBJ)/%.o : $(SRC)/%.cpp
	$(COMPCPP) -o $@ -c $< $(CCFLAGS)

#Create the directory .obj if don't exist.
$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

#SHOW information rule.
show :
	$(info $(SRCSUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLOBJSOFCPP))

#CLEAN rules.
cleanall : clean
	$(RM) $(APP)
	
clean:
	$(RM) $(OBJ)

