##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Practica2
ConfigurationName      :=Debug
WorkspacePath          :=E:/PRS2_marc.cespedes_alex.cabezas/Practica2
ProjectPath            :=E:/PRS2_marc.cespedes_alex.cabezas/Practica2
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=PGM
Date                   :=14/05/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW-4.8.1/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW-4.8.1/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="Practica2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW-4.8.1/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)allegro-5.0.10-monolith-mt-debug 
ArLibs                 :=  "liballegro-5.0.10-monolith-mt-debug.a" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW-4.8.1/bin/ar.exe rcu
CXX      := C:/MinGW-4.8.1/bin/g++.exe
CC       := C:/MinGW-4.8.1/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW-4.8.1/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/grafics.c$(ObjectSuffix) $(IntermediateDirectory)/LS_allegro.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/llistaPDI.c$(ObjectSuffix) $(IntermediateDirectory)/fitxers.c$(ObjectSuffix) $(IntermediateDirectory)/temps.c$(ObjectSuffix) $(IntermediateDirectory)/memoria.c$(ObjectSuffix) $(IntermediateDirectory)/logica.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/grafics.c$(ObjectSuffix): grafics.c $(IntermediateDirectory)/grafics.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/grafics.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/grafics.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/grafics.c$(DependSuffix): grafics.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/grafics.c$(ObjectSuffix) -MF$(IntermediateDirectory)/grafics.c$(DependSuffix) -MM grafics.c

$(IntermediateDirectory)/grafics.c$(PreprocessSuffix): grafics.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/grafics.c$(PreprocessSuffix) grafics.c

$(IntermediateDirectory)/LS_allegro.c$(ObjectSuffix): LS_allegro.c $(IntermediateDirectory)/LS_allegro.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/LS_allegro.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LS_allegro.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LS_allegro.c$(DependSuffix): LS_allegro.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LS_allegro.c$(ObjectSuffix) -MF$(IntermediateDirectory)/LS_allegro.c$(DependSuffix) -MM LS_allegro.c

$(IntermediateDirectory)/LS_allegro.c$(PreprocessSuffix): LS_allegro.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LS_allegro.c$(PreprocessSuffix) LS_allegro.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/llistaPDI.c$(ObjectSuffix): llistaPDI.c $(IntermediateDirectory)/llistaPDI.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/llistaPDI.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/llistaPDI.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/llistaPDI.c$(DependSuffix): llistaPDI.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/llistaPDI.c$(ObjectSuffix) -MF$(IntermediateDirectory)/llistaPDI.c$(DependSuffix) -MM llistaPDI.c

$(IntermediateDirectory)/llistaPDI.c$(PreprocessSuffix): llistaPDI.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/llistaPDI.c$(PreprocessSuffix) llistaPDI.c

$(IntermediateDirectory)/fitxers.c$(ObjectSuffix): fitxers.c $(IntermediateDirectory)/fitxers.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/fitxers.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fitxers.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fitxers.c$(DependSuffix): fitxers.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fitxers.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fitxers.c$(DependSuffix) -MM fitxers.c

$(IntermediateDirectory)/fitxers.c$(PreprocessSuffix): fitxers.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fitxers.c$(PreprocessSuffix) fitxers.c

$(IntermediateDirectory)/temps.c$(ObjectSuffix): temps.c $(IntermediateDirectory)/temps.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/temps.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/temps.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/temps.c$(DependSuffix): temps.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/temps.c$(ObjectSuffix) -MF$(IntermediateDirectory)/temps.c$(DependSuffix) -MM temps.c

$(IntermediateDirectory)/temps.c$(PreprocessSuffix): temps.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/temps.c$(PreprocessSuffix) temps.c

$(IntermediateDirectory)/memoria.c$(ObjectSuffix): memoria.c $(IntermediateDirectory)/memoria.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/memoria.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/memoria.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/memoria.c$(DependSuffix): memoria.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/memoria.c$(ObjectSuffix) -MF$(IntermediateDirectory)/memoria.c$(DependSuffix) -MM memoria.c

$(IntermediateDirectory)/memoria.c$(PreprocessSuffix): memoria.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/memoria.c$(PreprocessSuffix) memoria.c

$(IntermediateDirectory)/logica.c$(ObjectSuffix): logica.c $(IntermediateDirectory)/logica.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/PRS2_marc.cespedes_alex.cabezas/Practica2/logica.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/logica.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/logica.c$(DependSuffix): logica.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/logica.c$(ObjectSuffix) -MF$(IntermediateDirectory)/logica.c$(DependSuffix) -MM logica.c

$(IntermediateDirectory)/logica.c$(PreprocessSuffix): logica.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/logica.c$(PreprocessSuffix) logica.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


