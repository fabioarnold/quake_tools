// takes the quake palette in lmp format and outputs a GIMP-compatible gpl file

#include "cmdlib.h"

void WriteGPL(const char *filename, byte *qpal)
{
	FILE *file = fopen(filename, "w");
	if (!file) return;

	fputs("GIMP Palette\n", file);
	fputs("Name: Quake I\n", file);
	fputs("Columns: 16\n", file);
	fputs("#\n", file);
	for (int i = 0; i < 256; i++) {
		fprintf(file, "%d %d %d\n", qpal[3*i+0], qpal[3*i+1], qpal[3*i+2]);
	}

	fclose(file);
}

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;

	byte *qpal;
	int size = LoadFile (argv[1], (void **)&qpal);
	if (size != 256*3) return 1;

	WriteGPL("quake1.gpl", qpal);

	return 0;
}
