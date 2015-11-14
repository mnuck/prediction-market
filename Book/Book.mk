##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Book
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\mnuck\Documents\prediction-market"
ProjectPath            := "C:\Users\mnuck\Documents\prediction-market\Book"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=mnuck
Date                   :=14/11/2015
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=C:/TDM-GCC-32/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-32/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Book.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-32/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-32/bin/ar.exe rcu
CXX      := C:/TDM-GCC-32/bin/g++.exe
CC       := C:/TDM-GCC-32/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-32/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Book.cpp$(ObjectSuffix) $(IntermediateDirectory)/Feed.cpp$(ObjectSuffix) $(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) $(IntermediateDirectory)/Order.cpp$(ObjectSuffix) $(IntermediateDirectory)/Market.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Book.cpp$(ObjectSuffix): Book.cpp $(IntermediateDirectory)/Book.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/Book.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Book.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Book.cpp$(DependSuffix): Book.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Book.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Book.cpp$(DependSuffix) -MM "Book.cpp"

$(IntermediateDirectory)/Book.cpp$(PreprocessSuffix): Book.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Book.cpp$(PreprocessSuffix) "Book.cpp"

$(IntermediateDirectory)/Feed.cpp$(ObjectSuffix): Feed.cpp $(IntermediateDirectory)/Feed.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/Feed.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Feed.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Feed.cpp$(DependSuffix): Feed.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Feed.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Feed.cpp$(DependSuffix) -MM "Feed.cpp"

$(IntermediateDirectory)/Feed.cpp$(PreprocessSuffix): Feed.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Feed.cpp$(PreprocessSuffix) "Feed.cpp"

$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix): Participant.cpp $(IntermediateDirectory)/Participant.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/Participant.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Participant.cpp$(DependSuffix): Participant.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Participant.cpp$(DependSuffix) -MM "Participant.cpp"

$(IntermediateDirectory)/Participant.cpp$(PreprocessSuffix): Participant.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Participant.cpp$(PreprocessSuffix) "Participant.cpp"

$(IntermediateDirectory)/Order.cpp$(ObjectSuffix): Order.cpp $(IntermediateDirectory)/Order.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/Order.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Order.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Order.cpp$(DependSuffix): Order.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Order.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Order.cpp$(DependSuffix) -MM "Order.cpp"

$(IntermediateDirectory)/Order.cpp$(PreprocessSuffix): Order.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Order.cpp$(PreprocessSuffix) "Order.cpp"

$(IntermediateDirectory)/Market.cpp$(ObjectSuffix): Market.cpp $(IntermediateDirectory)/Market.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/mnuck/Documents/prediction-market/Book/Market.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Market.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Market.cpp$(DependSuffix): Market.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Market.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Market.cpp$(DependSuffix) -MM "Market.cpp"

$(IntermediateDirectory)/Market.cpp$(PreprocessSuffix): Market.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Market.cpp$(PreprocessSuffix) "Market.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


