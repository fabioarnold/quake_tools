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
	byte *pcol = qpal;
	int i;
	for (i = 0; i < 256; i++)
	{
		fprintf(file, "%d %d %d\n", pcol[0], pcol[1], pcol[2]);
		pcol += 3;
	}

	fclose(file);
}

void ReadGPL(const char *filename, byte **qpal)
{
	FILE *file = fopen(filename, "r");
	if (!file) return;

	char line[256];
	// skip header
	while (fgets(line, sizeof(line), file) && line[0] != '#');

	byte *pcol = *qpal;
	byte *pend = pcol+256*3;

	while (fgets(line, sizeof(line), file) && pcol < pend)
	{ // read three tokens on each line
		int num = 0;
		const char *del = " \t,;\n";
		char *tok = strtok(line, del);
		for (; tok && num < 3; tok = strtok(NULL, del), num++)
		{
			*pcol = atoi(tok); pcol++;
		}
	}
	fclose(file);

	// make rest of palette black
	for (; pcol < pend; pcol++) *pcol = 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;

	char *ext = strrchr(argv[1], (int)'.');
	if (!ext) return 1;

	if (!strcmp(ext, ".lmp"))
	{
		byte *qpal;
		int size = LoadFile (argv[1], (void **)&qpal);
		if (size != 256*3) return 1;
		WriteGPL("out.gpl", qpal);
	}
	else if (!strcmp(ext, ".gpl"))
	{
		byte *qpal = malloc(256*3);
		if (!qpal) return 1;
		ReadGPL(argv[1], &qpal);
		SaveFile("out.lmp", qpal, 256*3);
	}

	return 0;
}
