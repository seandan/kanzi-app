CC = @D:\qnx660\host\win32\x86\usr\bin\QCC
CCC = @D:\qnx660\host\win32\x86\usr\bin\QCC
CFLAGS := -fexceptions -frtti -O2 -fPIC -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-overlength-strings -fno-strict-aliasing -Vgcc_ntoarmv7le_gpp -lang-c++ -Wc,-std=gnu++0x -DKZ_OPENGL_VERSION=KZ_OPENGL_ES_2_0 -DKZ_OPENVG_VERSION=KZ_OPENVG_NONE -DRELEASE -DNDEBUG -DQNX -DQNX_SCREEN -D__GLIBCXX__ -DKANZI_COMPONENTS_API= -DKANZI_V8_API=

INCLUDES := -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\kanzi_v8\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\v8\include -IC:\KanziWorkspace_3_2_4_474_92176\Projects\NavigationApp\Application\src\Controller -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\boost\include -IC:\KanziWorkspace_3_2_4_474_92176\Projects\NavigationApp\Application\src -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\system\common\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\system\graphics_context\egl\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\system\windowing_system\screen\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\core\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\user\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\application_framework\common\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\headers\kanzi_components\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\v8\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\icu4c\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\opengl_es_2_0\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\opengl_es_2_0\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\freetype\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\freetype\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\harfbuzz\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\libunibreak\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\zlib\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\zlib\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\libjpeg\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\libjpeg\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\libpng\include -IC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\common\libpng\include
INCLUDES += -IF:\controller -I.
CPPDIR := F:/controller/*.cpp ./*.cpp
VPATH := F:/controller/ ./object/
LDFLAGS := -LE:\workstation\APP\Code_Kanzi\public\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\lib\qnx_screen\ES2_Release -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\v8\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\icu4c\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\freetype\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\harfbuzz\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\libunibreak\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\zlib\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\libjpeg\lib -LC:\KanziWorkspace_3_2_4_474_92176\Engine\libraries\platforms\qnx-arm\libpng\lib -Wl,--start-group
LDFLAGS2 := -Vgcc_ntoarmv7le_gpp -lunibreak -lharfbuzz -lfreetype -lGLESv2 -lEGL -licudata -licuuc -licui18n -lv8_snapshot -lv8_libbase -lv8_base -lv8_libplatform -lkanzi_v8 -lkanzi_components -lapplicationframework -luser -lcore -lsystem -lpps -limg -lscreen -lm -lstdc++ -ljpeg -lpng -lz -Wl,--end-group -Vgcc_ntoarmv7le_gpp -l:libbacktrace.a
OBJECTDIR = object/


TARGET = Car
CPPDIR += ./controller/*.cpp ./page/*.cpp 
INCLUDES +=-I./controller/ -I./page/
VPATH +=./controller/ ./page/


ABS_OBJECT = $(patsubst %.cpp,%.o,$(wildcard $(CPPDIR)))
TOTAOL_OBJECT = $(notdir $(ABS_OBJECT))
OBJECT=$(addprefix $(OBJECTDIR),$(TOTAOL_OBJECT))






all:PRE $(TARGET)

$(TARGET):$(OBJECT)
	@echo compile $@
	$(CCC) $(LDFLAGS) $^ $(LDFLAGS2)  -o $(OBJECTDIR)$@ 
	@echo compile finish! TARGET=$(TARGET)
	
$(OBJECT):$(TOTAOL_OBJECT)

$(TOTAOL_OBJECT):%.o:%.cpp
	@echo compile $@
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $(OBJECTDIR)$@

.PHONY:clean
clean:
	rm -f $(OBJECTDIR)*
	
.PHONY:PRE
PRE:
ifneq  ($(OBJECTDIR), $(wildcard $(OBJECTDIR)))
	mkdir -p $(OBJECTDIR)
endif