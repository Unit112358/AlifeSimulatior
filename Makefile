gpparg = -mwindows -DDX_GCC_COMPILE -DDX_NON_INLINE_ASM -LDxLib -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt
filename = main

test:
		g++ -o ${filename}.exe ${filename}