/* $XConsortium: DviChar.c,v 1.7 91/07/31 00:39:31 keith Exp $ */

/*
 * DviChar.c
 *
 * Map DVI (ditrof output) character names to
 * font indexes and back
 */
/* $XFree86$ */

# include   <X11/Intrinsic.h>
# include   "DviChar.h"

# define allocHash()	((DviCharNameHash *) XtMalloc (sizeof (DviCharNameHash)))

struct map_list {
	struct map_list	*next;
	DviCharNameMap	*map;
};

static struct map_list	*world;

static int	standard_maps_loaded = 0;
static void	load_standard_maps (void);
static int	hash_name (const char *name);
static void	dispose_hash(DviCharNameMap *map);
static void	compute_hash(DviCharNameMap *map);

DviCharNameMap *
DviFindMap (const char *encoding)
{
	struct map_list	*m;

	if (!standard_maps_loaded)
		load_standard_maps ();
	for (m = world; m; m=m->next)
		if (!strcmp (m->map->encoding, encoding))
			return m->map;
	return NULL;
}

void
DviRegisterMap (DviCharNameMap *map)
{
	struct map_list	*m;

	if (!standard_maps_loaded)
		load_standard_maps ();
	for (m = world; m; m = m->next)
		if (!strcmp (m->map->encoding, map->encoding))
			break;
	if (!m) {
		m = (struct map_list *) XtMalloc (sizeof *m);
		m->next = world;
		world = m;
	}
	dispose_hash (map);
	m->map = map;
	compute_hash (map);
}

static void
dispose_hash (DviCharNameMap *map)
{
	DviCharNameHash	**buckets;
	DviCharNameHash	*h, *next;
	int		i;

	buckets = map->buckets;
	for (i = 0; i < DVI_HASH_SIZE; i++) {
		for (h = buckets[i]; h; h=next) {
			next = h->next;
			XtFree ((char *) h);
		}
	}
}

static int
hash_name (const char *name)
{
	int	i = 0;

	while (*name)
		i = (i << 1) ^ *name++;
	if (i < 0)
		i = -i;
	return i;
}

static void
compute_hash (DviCharNameMap *map)
{
	DviCharNameHash	**buckets;
	int		c, s, i;
	DviCharNameHash	*h;

	buckets = map->buckets;
	for (i = 0; i < DVI_HASH_SIZE; i++)
		buckets[i] = NULL;
	for (c = 0; c < DVI_MAP_SIZE; c++)
		for (s = 0; s < DVI_MAX_SYNONYMS; s++) {
			if (!map->dvi_names[c][s])
				break;
			i = hash_name (map->dvi_names[c][s]) % DVI_HASH_SIZE;
			h = allocHash ();
			h->next = buckets[i];
			buckets[i] = h;
			h->name = map->dvi_names[c][s];
			h->position = c;
		}
	
}

int
DviCharIndex (DviCharNameMap *map, const char *name)
{
	int		i;
	DviCharNameHash	*h;

	i = hash_name (name) % DVI_HASH_SIZE;
	for (h = map->buckets[i]; h; h=h->next)
		if (!strcmp (h->name, name))
			return h->position;
	return -1;
}

static DviCharNameMap ISO8859_1_map = {
	"iso8859-1",
	0,
{
{	NULL,		/* 0 */},
{	NULL,		/* 1 */},
{	NULL,		/* 2 */},
{	NULL,		/* 3 */},
{	NULL,		/* 4 */},
{	NULL,		/* 5 */},
{	NULL,		/* 6 */},
{	NULL,		/* 7 */},
{	NULL,		/* 8 */},
{	NULL,		/* 9 */},
{	NULL,		/* 10 */},
{	NULL,		/* 11 */},
{	NULL,		/* 12 */},
{	NULL,		/* 13 */},
{	NULL,		/* 14 */},
{	NULL,		/* 15 */},
{	NULL,		/* 16 */},
{	NULL,		/* 17 */},
{	NULL,		/* 18 */},
{	NULL,		/* 19 */},
{	NULL,		/* 20 */},
{	NULL,		/* 21 */},
{	NULL,		/* 22 */},
{	NULL,		/* 23 */},
{	NULL,		/* 24 */},
{	NULL,		/* 25 */},
{	NULL,		/* 26 */},
{	NULL,		/* 27 */},
{	NULL,		/* 28 */},
{	NULL,		/* 29 */},
{	NULL,		/* 30 */},
{	NULL,		/* 31 */},
{	NULL,		/* 32 */},
{	"!",		/* 33 */},
{	"\"",		/* 34 */},
{	"#",		/* 35 */},
{	"$",		/* 36 */},
{	"%",		/* 37 */},
{	"&",		/* 38 */},
{	"'",		/* 39 */},
{	"(",		/* 40 */},
{	")",		/* 41 */},
{	"*",		/* 42 */},
{	"+",		/* 43 */},
{	",",		/* 44 */},
{	"-","\\-",	/* 45 */},
{	".",		/* 46 */},
{	"/","sl",	/* 47 */},
{	"0",		/* 48 */},
{	"1",		/* 49 */},
{	"2",		/* 50 */},
{	"3",		/* 51 */},
{	"4",		/* 52 */},
{	"5",		/* 53 */},
{	"6",		/* 54 */},
{	"7",		/* 55 */},
{	"8",		/* 56 */},
{	"9",		/* 57 */},
{	":",		/* 58 */},
{	";",		/* 59 */},
{	"<",		/* 60 */},
{	"=","eq",	/* 61 */},
{	">",		/* 62 */},
{	"?",		/* 63 */},
{	"@",		/* 64 */},
{	"A",		/* 65 */},
{	"B",		/* 66 */},
{	"C",		/* 67 */},
{	"D",		/* 68 */},
{	"E",		/* 69 */},
{	"F",		/* 70 */},
{	"G",		/* 71 */},
{	"H",		/* 72 */},
{	"I",		/* 73 */},
{	"J",		/* 74 */},
{	"K",		/* 75 */},
{	"L",		/* 76 */},
{	"M",		/* 77 */},
{	"N",		/* 78 */},
{	"O",		/* 79 */},
{	"P",		/* 80 */},
{	"Q",		/* 81 */},
{	"R",		/* 82 */},
{	"S",		/* 83 */},
{	"T",		/* 84 */},
{	"U",		/* 85 */},
{	"V",		/* 86 */},
{	"W",		/* 87 */},
{	"X",		/* 88 */},
{	"Y",		/* 89 */},
{	"Z",		/* 90 */},
{	"[",		/* 91 */},
{	"\\",		/* 92 */},
{	"]",		/* 93 */},
{	"a^",		/* 94 */},
{	"_","ru","ul",	/* 95 */},
{	"`",		/* 96 */},
{	"a",		/* 97 */},
{	"b",		/* 98 */},
{	"c",		/* 99 */},
{	"d",		/* 100 */},
{	"e",		/* 101 */},
{	"f",		/* 102 */},
{	"g",		/* 103 */},
{	"h",		/* 104 */},
{	"i",		/* 105 */},
{	"j",		/* 106 */},
{	"k",		/* 107 */},
{	"l",		/* 108 */},
{	"m",		/* 109 */},
{	"n",		/* 110 */},
{	"o",		/* 111 */},
{	"p",		/* 112 */},
{	"q",		/* 113 */},
{	"r",		/* 114 */},
{	"s",		/* 115 */},
{	"t",		/* 116 */},
{	"u",		/* 117 */},
{	"v",		/* 118 */},
{	"w",		/* 119 */},
{	"x",		/* 120 */},
{	"y",		/* 121 */},
{	"z",		/* 122 */},
{	"{",		/* 123 */},
{	"|","or"	/* 124 */},
{	"}",		/* 125 */},
{	"a~","ap"	/* 126 */},
{	NULL,		/* 127 */},
{	NULL,		/* 128 */},
{	NULL,		/* 129 */},
{	NULL,		/* 130 */},
{	NULL,		/* 131 */},
{	NULL,		/* 132 */},
{	NULL,		/* 133 */},
{	NULL,		/* 134 */},
{	NULL,		/* 135 */},
{	NULL,		/* 136 */},
{	NULL,		/* 137 */},
{	NULL,		/* 138 */},
{	NULL,		/* 139 */},
{	NULL,		/* 140 */},
{	NULL,		/* 141 */},
{	NULL,		/* 142 */},
{	NULL,		/* 143 */},
{	NULL,		/* 144 */},
{	NULL,		/* 145 */},
{	NULL,		/* 146 */},
{	NULL,		/* 147 */},
{	NULL,		/* 148 */},
{	NULL,		/* 149 */},
{	NULL,		/* 150 */},
{	NULL,		/* 151 */},
{	NULL,		/* 152 */},
{	NULL,		/* 153 */},
{	NULL,		/* 154 */},
{	NULL,		/* 155 */},
{	NULL,		/* 156 */},
{	NULL,		/* 157 */},
{	NULL,		/* 158 */},
{	NULL,		/* 159 */},
{	NULL,		/* 160 */},
{	"I!",		/* 161 */},
{	"ct",		/* 162 */},
{	"po",		/* 163 */},
{	"cu",		/* 164 */},
{	"$J",		/* 165 */},
{	NULL,		/* 166 */},
{	"sc",		/* 167 */},
{	NULL,		/* 168 */},
{	"co",		/* 169 */},
{	NULL,		/* 170 */},
{	"d<",		/* 171 */},
{	"no",		/* 172 */},
{	"hy",		/* 173 */},
{	"rg",		/* 174 */},
{	"ma",		/* 175 */},
{	"de",		/* 176 */},
{	"+-",		/* 177 */},
{	NULL,		/* 178 */},
{	NULL,		/* 179 */},
{	"aa",		/* 180 */},
{	"*m",		/* 181 */},
{	"pp",		/* 182 */},
{	NULL,		/* 183 */},
{	"cd",		/* 184 */},
{	NULL,		/* 185 */},
{	NULL,		/* 186 */},
{	"d>",		/* 187 */},
{	"14",		/* 188 */},
{	"12",		/* 189 */},
{	"34",		/* 190 */},
{	"I?",		/* 191 */},
{	NULL,		/* 192 */},
{	NULL,		/* 193 */},
{	NULL,		/* 194 */},
{	NULL,		/* 195 */},
{	NULL,		/* 196 */},
{	NULL,		/* 197 */},
{	"AE",		/* 198 */},
{	NULL,		/* 199 */},
{	NULL,		/* 200 */},
{	NULL,		/* 201 */},
{	NULL,		/* 202 */},
{	NULL,		/* 203 */},
{	NULL,		/* 204 */},
{	NULL,		/* 205 */},
{	NULL,		/* 206 */},
{	NULL,		/* 207 */},
{	NULL,		/* 208 */},
{	NULL,		/* 209 */},
{	NULL,		/* 210 */},
{	NULL,		/* 211 */},
{	NULL,		/* 212 */},
{	NULL,		/* 213 */},
{	NULL,		/* 214 */},
{	"mu",		/* 215 */},
{	"O/",		/* 216 */},
{	NULL,		/* 217 */},
{	NULL,		/* 218 */},
{	NULL,		/* 219 */},
{	NULL,		/* 220 */},
{	NULL,		/* 221 */},
{	NULL,		/* 222 */},
{	"ss",		/* 223 */},
{	NULL,		/* 224 */},
{	NULL,		/* 225 */},
{	NULL,		/* 226 */},
{	NULL,		/* 227 */},
{	NULL,		/* 228 */},
{	NULL,		/* 229 */},
{	"ae",		/* 230 */},
{	NULL,		/* 231 */},
{	NULL,		/* 232 */},
{	NULL,		/* 233 */},
{	NULL,		/* 234 */},
{	NULL,		/* 235 */},
{	NULL,		/* 236 */},
{	NULL,		/* 237 */},
{	NULL,		/* 238 */},
{	NULL,		/* 239 */},
{	NULL,		/* 240 */},
{	NULL,		/* 241 */},
{	NULL,		/* 242 */},
{	NULL,		/* 243 */},
{	NULL,		/* 244 */},
{	NULL,		/* 245 */},
{	NULL,		/* 246 */},
{	NULL,		/* 247 */},
{	NULL,		/* 248 */},
{	NULL,		/* 249 */},
{	NULL,		/* 250 */},
{	NULL,		/* 251 */},
{	NULL,		/* 252 */},
{	NULL,		/* 253 */},
{	NULL,		/* 254 */},
{	NULL,		/* 255 */},
},
{
{   "fi",	    "fi",   },
{   "fl",	    "fl",   },
{   "ff",	    "ff",   },
{   "Fi",	    "ffi",   },
{   "Fl",	    "ffl",   },
{   NULL,	    NULL,    },
}
};

static DviCharNameMap Adobe_Symbol_map = {
	"adobe-fontspecific",
	1,
{
{	NULL,		/* 0 */},
{	NULL,		/* 1 */},
{	NULL,		/* 2 */},
{	NULL,		/* 3 */},
{	NULL,		/* 4 */},
{	NULL,		/* 5 */},
{	NULL,		/* 6 */},
{	NULL,		/* 7 */},
{	NULL,		/* 8 */},
{	NULL,		/* 9 */},
{	NULL,		/* 10 */},
{	NULL,		/* 11 */},
{	NULL,		/* 12 */},
{	NULL,		/* 13 */},
{	NULL,		/* 14 */},
{	NULL,		/* 15 */},
{	NULL,		/* 16 */},
{	NULL,		/* 17 */},
{	NULL,		/* 18 */},
{	NULL,		/* 19 */},
{	NULL,		/* 20 */},
{	NULL,		/* 21 */},
{	NULL,		/* 22 */},
{	NULL,		/* 23 */},
{	NULL,		/* 24 */},
{	NULL,		/* 25 */},
{	NULL,		/* 26 */},
{	NULL,		/* 27 */},
{	NULL,		/* 28 */},
{	NULL,		/* 29 */},
{	NULL,		/* 30 */},
{	NULL,		/* 31 */},
{	NULL,		/* 32 */},
{	"!",		/* 33 */},
{	"fa",		/* 34 */},
{	"#",		/* 35 */},
{	"te",		/* 36 */},
{	"%",		/* 37 */},
{	"&",		/* 38 */},
{	"cm",		/* 39 */},
{	"(",		/* 40 */},
{	")",		/* 41 */},
{	"**",		/* 42 */},
{	"+","pl",	/* 43 */},
{	",",		/* 44 */},
{	"-","mi","\\-",	/* 45 */},
{	".",		/* 46 */},
{	"/","sl",	/* 47 */},
{	"0",		/* 48 */},
{	"1",		/* 49 */},
{	"2",		/* 50 */},
{	"3",		/* 51 */},
{	"4",		/* 52 */},
{	"5",		/* 53 */},
{	"6",		/* 54 */},
{	"7",		/* 55 */},
{	"8",		/* 56 */},
{	"9",		/* 57 */},
{	":",		/* 58 */},
{	";",		/* 59 */},
{	"<",		/* 60 */},
{	"=","eq",	/* 61 */},
{	">",		/* 62 */},
{	"?",		/* 63 */},
{	"=~",		/* 64 */},
{	"*A",		/* 65 */},
{	"*B",		/* 66 */},
{	"*C",		/* 67 */},
{	"*D",		/* 68 */},
{	"*E",		/* 69 */},
{	"*F",		/* 70 */},
{	"*G",		/* 71 */},
{	"*Y",		/* 72 */},
{	"*I",		/* 73 */},
{	NULL,		/* 74 */},
{	"*K",		/* 75 */},
{	"*L",		/* 76 */},
{	"*M",		/* 77 */},
{	"*N",		/* 78 */},
{	"*O",		/* 79 */},
{	"*P",		/* 80 */},
{	"*H",		/* 81 */},
{	"*R",		/* 82 */},
{	"*S",		/* 83 */},
{	"*T",		/* 84 */},
{	"*U",		/* 85 */},
{	"ts",		/* 86 */},
{	"*W",		/* 87 */},
{	"*C",		/* 88 */},
{	"*Q",		/* 89 */},
{	"*Z",		/* 90 */},
{	"[",		/* 91 */},
{	"tf",		/* 92 */},
{	"]",		/* 93 */},
{	"bt",		/* 94 */},
{	"ul",		/* 95 */},
{	"rn",		/* 96 */},
{	"*a",		/* 97 */},
{	"*b",		/* 98 */},
{	"*x",		/* 99 */},
{	"*d",		/* 100 */},
{	"*e",		/* 101 */},
{	"*f",		/* 102 */},
{	"*g",		/* 103 */},
{	"*y",		/* 104 */},
{	"*i",		/* 105 */},
{	NULL,		/* 106 */},
{	"*k",		/* 107 */},
{	"*l",		/* 108 */},
{	"*m",		/* 109 */},
{	"*n",		/* 110 */},
{	"*o",		/* 111 */},
{	"*p",		/* 112 */},
{	"*h",		/* 113 */},
{	"*r",		/* 114 */},
{	"*s",		/* 115 */},
{	"*t",		/* 116 */},
{	"*u",		/* 117 */},
{	NULL,		/* 118 */},
{	"*w",		/* 119 */},
{	"*c",		/* 120 */},
{	"*q",		/* 121 */},
{	"*z",		/* 122 */},
{	"{",		/* 123 */},
{	"|",		/* 124 */},
{	"}",		/* 125 */},
{	"a~","ap",	/* 126 */},
{	NULL,		/* 127 */},
{	NULL,		/* 128 */},
{	NULL,		/* 129 */},
{	NULL,		/* 130 */},
{	NULL,		/* 131 */},
{	NULL,		/* 132 */},
{	NULL,		/* 133 */},
{	NULL,		/* 134 */},
{	NULL,		/* 135 */},
{	NULL,		/* 136 */},
{	NULL,		/* 137 */},
{	NULL,		/* 138 */},
{	NULL,		/* 139 */},
{	NULL,		/* 140 */},
{	NULL,		/* 141 */},
{	NULL,		/* 142 */},
{	NULL,		/* 143 */},
{	NULL,		/* 144 */},
{	NULL,		/* 145 */},
{	NULL,		/* 146 */},
{	NULL,		/* 147 */},
{	NULL,		/* 148 */},
{	NULL,		/* 149 */},
{	NULL,		/* 150 */},
{	NULL,		/* 151 */},
{	NULL,		/* 152 */},
{	NULL,		/* 153 */},
{	NULL,		/* 154 */},
{	NULL,		/* 155 */},
{	NULL,		/* 156 */},
{	NULL,		/* 157 */},
{	NULL,		/* 158 */},
{	NULL,		/* 159 */},
{	NULL,		/* 160 */},
{	NULL,		/* 161 */},
{	"fm","mt",	/* 162 */},
{	"<=",		/* 163 */},
{	"/","sl"	/* 164 */},
{	"if",		/* 165 */},
{	NULL,		/* 166 */},
{	"Cc",		/* 167 */},
{	"Cd",		/* 168 */},
{	"Ch",		/* 169 */},
{	"Cs",		/* 170 */},
{	"<>",		/* 171 */},
{	"<-",		/* 172 */},
{	"ua",		/* 173 */},
{	"->",		/* 174 */},
{	"da",		/* 175 */},
{	"de",		/* 176 */},
{	"+-",		/* 177 */},
{	"sd",		/* 178 */},
{	">=",		/* 179 */},
{	"mu",		/* 180 */},
{	"pt",		/* 181 */},
{	"pd",		/* 182 */},
{	"bu",		/* 183 */},
{	"di",		/* 184 */},
{	"!=",		/* 185 */},
{	"==",		/* 186 */},
{	"~=",		/* 187 */},
{	"..",		/* 188 */},
{	"br",		/* 189 */},
{	"em",		/* 190 */},
{	"cr",		/* 191 */},
{	"al",		/* 192 */},
{	NULL,		/* 193 */},
{	NULL,		/* 194 */},
{	NULL,		/* 195 */},
{	"ax",		/* 196 */},
{	"a+",		/* 197 */},
{	"es",		/* 198 */},
{	"ca",		/* 199 */},
{	"cu",		/* 200 */},
{	"sp",		/* 201 */},
{	"ip",		/* 202 */},
{	"!s",		/* 203 */},
{	"sb",		/* 204 */},
{	"ib",		/* 205 */},
{	"mo",		/* 206 */},
{	"!m",		/* 207 */},
{	"ag",		/* 208 */},
{	"gr",		/* 209 */},
{	NULL,		/* 210 */},
{	NULL,		/* 211 */},
{	NULL,		/* 212 */},
{	NULL,		/* 213 */},
{	"sr",		/* 214 */},
{	"m.",		/* 215 */},
{	"no",		/* 216 */},
{	"an",		/* 217 */},
{	"lo",		/* 218 */},
{	"io",		/* 219 */},
{	"<:",		/* 220 */},
{	"u=",		/* 221 */},
{	":>",		/* 222 */},
{	"d=",		/* 223 */},
{	"dm",		/* 224 */},
{	"L<",		/* 225 */},
{	"rg",		/* 226 */},
{	"co",		/* 227 */},
{	"tm",		/* 228 */},
{	NULL,		/* 229 */},
{	NULL,		/* 230 */},
{	NULL,		/* 231 */},
{	NULL,		/* 232 */},
{	"lc",		/* 233 */},
{	NULL,		/* 234 */},
{	"lf",		/* 235 */},
{	"lt",		/* 236 */},
{	"lk",		/* 237 */},
{	"lb",		/* 238 */},
{	"bv",		/* 239 */},
{	"AL",		/* 240 */},
{	"R>",		/* 241 */},
{	"is",		/* 242 */},
{	NULL,		/* 243 */},
{	NULL,		/* 244 */},
{	NULL,		/* 245 */},
{	NULL,		/* 246 */},
{	NULL,		/* 247 */},
{	NULL,		/* 248 */},
{	"rc",		/* 249 */},
{	NULL,		/* 250 */},
{	"rf",		/* 251 */},
{	"rt",		/* 252 */},
{	"rk",		/* 253 */},
{	"rb",		/* 254 */},
{	NULL,		/* 255 */},
},
{
{	NULL,	    NULL	},
}
};

static void
load_standard_maps (void)
{
	standard_maps_loaded = 1;
	DviRegisterMap (&ISO8859_1_map);
	DviRegisterMap (&Adobe_Symbol_map);
}

