##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Book
ConfigurationName      :=Debug
WorkspacePath          := "/home/mnuck/prediction-market"
ProjectPath            := "/home/mnuck/prediction-market/Book"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Matthew Nuckolls
Date                   :=22/11/15
CodeLitePath           :="/home/mnuck/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/home/mnuck/autobahn $(IncludeSwitch)/home/mnuck/boost_1_58_0 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)UnitTest++ $(LibrarySwitch)pthread $(LibrarySwitch)boost_log $(LibrarySwitch)boost_log_setup $(LibrarySwitch)boost_thread $(LibrarySwitch)boost_system 
ArLibs                 :=  "libUnitTest++.a" "libpthread" "libboost_log" "libboost_log_setup" "libboost_thread" "libboost_system" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/home/mnuck/boost_1_58_0/stage/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Book.cpp$(ObjectSuffix) $(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) $(IntermediateDirectory)/Order.cpp$(ObjectSuffix) $(IntermediateDirectory)/Market.cpp$(ObjectSuffix) $(IntermediateDirectory)/FeedStdOut.cpp$(ObjectSuffix) $(IntermediateDirectory)/FeedWAMP.cpp$(ObjectSuffix) $(IntermediateDirectory)/WAMPAPI.cpp$(ObjectSuffix) $(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) $(IntermediateDirectory)/BroadcastObservable.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(ObjectSuffix) $(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(ObjectSuffix) $(IntermediateDirectory)/tests_TestMarketClose.cpp$(ObjectSuffix) $(IntermediateDirectory)/tests_TestCrossOrders.cpp$(ObjectSuffix) $(IntermediateDirectory)/tests_TestWAMP.cpp$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Book.cpp$(ObjectSuffix): Book.cpp $(IntermediateDirectory)/Book.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/Book.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Book.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Book.cpp$(DependSuffix): Book.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Book.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Book.cpp$(DependSuffix) -MM "Book.cpp"

$(IntermediateDirectory)/Book.cpp$(PreprocessSuffix): Book.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Book.cpp$(PreprocessSuffix) "Book.cpp"

$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix): Participant.cpp $(IntermediateDirectory)/Participant.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/Participant.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Participant.cpp$(DependSuffix): Participant.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Participant.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Participant.cpp$(DependSuffix) -MM "Participant.cpp"

$(IntermediateDirectory)/Participant.cpp$(PreprocessSuffix): Participant.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Participant.cpp$(PreprocessSuffix) "Participant.cpp"

$(IntermediateDirectory)/Order.cpp$(ObjectSuffix): Order.cpp $(IntermediateDirectory)/Order.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/Order.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Order.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Order.cpp$(DependSuffix): Order.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Order.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Order.cpp$(DependSuffix) -MM "Order.cpp"

$(IntermediateDirectory)/Order.cpp$(PreprocessSuffix): Order.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Order.cpp$(PreprocessSuffix) "Order.cpp"

$(IntermediateDirectory)/Market.cpp$(ObjectSuffix): Market.cpp $(IntermediateDirectory)/Market.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/Market.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Market.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Market.cpp$(DependSuffix): Market.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Market.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Market.cpp$(DependSuffix) -MM "Market.cpp"

$(IntermediateDirectory)/Market.cpp$(PreprocessSuffix): Market.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Market.cpp$(PreprocessSuffix) "Market.cpp"

$(IntermediateDirectory)/FeedStdOut.cpp$(ObjectSuffix): FeedStdOut.cpp $(IntermediateDirectory)/FeedStdOut.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/FeedStdOut.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FeedStdOut.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FeedStdOut.cpp$(DependSuffix): FeedStdOut.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FeedStdOut.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FeedStdOut.cpp$(DependSuffix) -MM "FeedStdOut.cpp"

$(IntermediateDirectory)/FeedStdOut.cpp$(PreprocessSuffix): FeedStdOut.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FeedStdOut.cpp$(PreprocessSuffix) "FeedStdOut.cpp"

$(IntermediateDirectory)/FeedWAMP.cpp$(ObjectSuffix): FeedWAMP.cpp $(IntermediateDirectory)/FeedWAMP.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/FeedWAMP.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FeedWAMP.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FeedWAMP.cpp$(DependSuffix): FeedWAMP.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FeedWAMP.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FeedWAMP.cpp$(DependSuffix) -MM "FeedWAMP.cpp"

$(IntermediateDirectory)/FeedWAMP.cpp$(PreprocessSuffix): FeedWAMP.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FeedWAMP.cpp$(PreprocessSuffix) "FeedWAMP.cpp"

$(IntermediateDirectory)/WAMPAPI.cpp$(ObjectSuffix): WAMPAPI.cpp $(IntermediateDirectory)/WAMPAPI.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/WAMPAPI.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WAMPAPI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WAMPAPI.cpp$(DependSuffix): WAMPAPI.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WAMPAPI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WAMPAPI.cpp$(DependSuffix) -MM "WAMPAPI.cpp"

$(IntermediateDirectory)/WAMPAPI.cpp$(PreprocessSuffix): WAMPAPI.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WAMPAPI.cpp$(PreprocessSuffix) "WAMPAPI.cpp"

$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix): Logger.cpp $(IntermediateDirectory)/Logger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Logger.cpp$(DependSuffix): Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Logger.cpp$(DependSuffix) -MM "Logger.cpp"

$(IntermediateDirectory)/Logger.cpp$(PreprocessSuffix): Logger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Logger.cpp$(PreprocessSuffix) "Logger.cpp"

$(IntermediateDirectory)/BroadcastObservable.cpp$(ObjectSuffix): BroadcastObservable.cpp $(IntermediateDirectory)/BroadcastObservable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/BroadcastObservable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BroadcastObservable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BroadcastObservable.cpp$(DependSuffix): BroadcastObservable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BroadcastObservable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BroadcastObservable.cpp$(DependSuffix) -MM "BroadcastObservable.cpp"

$(IntermediateDirectory)/BroadcastObservable.cpp$(PreprocessSuffix): BroadcastObservable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BroadcastObservable.cpp$(PreprocessSuffix) "BroadcastObservable.cpp"

$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(ObjectSuffix): tests/TestBookParticipantOpen.cpp $(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/tests/TestBookParticipantOpen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(DependSuffix): tests/TestBookParticipantOpen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(DependSuffix) -MM "tests/TestBookParticipantOpen.cpp"

$(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(PreprocessSuffix): tests/TestBookParticipantOpen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_TestBookParticipantOpen.cpp$(PreprocessSuffix) "tests/TestBookParticipantOpen.cpp"

$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(ObjectSuffix): tests/TestOrderOpenAndClose.cpp $(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/tests/TestOrderOpenAndClose.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(DependSuffix): tests/TestOrderOpenAndClose.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(DependSuffix) -MM "tests/TestOrderOpenAndClose.cpp"

$(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(PreprocessSuffix): tests/TestOrderOpenAndClose.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_TestOrderOpenAndClose.cpp$(PreprocessSuffix) "tests/TestOrderOpenAndClose.cpp"

$(IntermediateDirectory)/tests_TestMarketClose.cpp$(ObjectSuffix): tests/TestMarketClose.cpp $(IntermediateDirectory)/tests_TestMarketClose.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/tests/TestMarketClose.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_TestMarketClose.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_TestMarketClose.cpp$(DependSuffix): tests/TestMarketClose.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_TestMarketClose.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_TestMarketClose.cpp$(DependSuffix) -MM "tests/TestMarketClose.cpp"

$(IntermediateDirectory)/tests_TestMarketClose.cpp$(PreprocessSuffix): tests/TestMarketClose.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_TestMarketClose.cpp$(PreprocessSuffix) "tests/TestMarketClose.cpp"

$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(ObjectSuffix): tests/TestCrossOrders.cpp $(IntermediateDirectory)/tests_TestCrossOrders.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/tests/TestCrossOrders.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(DependSuffix): tests/TestCrossOrders.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(DependSuffix) -MM "tests/TestCrossOrders.cpp"

$(IntermediateDirectory)/tests_TestCrossOrders.cpp$(PreprocessSuffix): tests/TestCrossOrders.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_TestCrossOrders.cpp$(PreprocessSuffix) "tests/TestCrossOrders.cpp"

$(IntermediateDirectory)/tests_TestWAMP.cpp$(ObjectSuffix): tests/TestWAMP.cpp $(IntermediateDirectory)/tests_TestWAMP.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mnuck/prediction-market/Book/tests/TestWAMP.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_TestWAMP.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_TestWAMP.cpp$(DependSuffix): tests/TestWAMP.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_TestWAMP.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_TestWAMP.cpp$(DependSuffix) -MM "tests/TestWAMP.cpp"

$(IntermediateDirectory)/tests_TestWAMP.cpp$(PreprocessSuffix): tests/TestWAMP.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_TestWAMP.cpp$(PreprocessSuffix) "tests/TestWAMP.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


