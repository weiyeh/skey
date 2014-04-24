/*
 * S/KEY v1.1b (skey.h)
 *
 * Authors:
 *          Neil M. Haller <nmh@thumper.bellcore.com>
 *          Philip R. Karn <karn@chicago.qualcomm.com>
 *          John S. Walden <jsw@thumper.bellcore.com>
 *
 * Modifications:
 *          Scott Chasin <chasin@crimelab.com>
 *          Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Main client header
 *
 * $OpenBSD: skey.h,v 1.13 1999/07/15 14:33:48 provos Exp $
 */

/* Server-side data structure for reading keys file during login */
struct skey {
	FILE *keyfile;
	char buf[256];
	char *logname;
	int n;
	char *seed;
	char *val;
	long recstart;		/* needed so reread of buffer is efficient */
};

/* Client-side structure for scanning data stream for challenge */
struct mc {
	char buf[256];
	int skip;
	int cnt;
};

/* Maximum sequence number we allow */
#ifndef SKEY_MAX_SEQ
#define SKEY_MAX_SEQ		10000
#endif

/* Minimum secret password length (rfc1938) */
#ifndef SKEY_MIN_PW_LEN
#define SKEY_MIN_PW_LEN		10
#endif

/* Max secret password length (rfc1938 says 63 but allows more) */
#ifndef SKEY_MAX_PW_LEN
#define SKEY_MAX_PW_LEN		255
#endif

/* Max length of an S/Key seed (rfc1938) */
#ifndef SKEY_MAX_SEED_LEN
#define SKEY_MAX_SEED_LEN	16
#endif

/* Max length of S/Key challenge (otp-???? 9999 seed) */
#ifndef SKEY_MAX_CHALLENGE
#define SKEY_MAX_CHALLENGE	(11 + SKEY_MAX_HASHNAME_LEN + SKEY_MAX_SEED_LEN)
#endif

/* Max length of hash algorithm name (md4/md5/sha1/rmd160) */
#define SKEY_MAX_HASHNAME_LEN	6

/* Size of a binary key (not NULL-terminated) */
#define SKEY_BINKEY_SIZE	8

/* Location of random file for bogus challenges */
#define _SKEY_RAND_FILE_PATH_	"/var/db/host.random"

/* Prototypes */
void f(char *x);
int keycrunch(char *result, char *seed, char *passwd);
char *btoe(char *engout, char *c);
char *put8(char *out, char *s);
int etob(char *out, char *e);
void rip(char *buf);
int skeychallenge(struct skey * mp, char *name, char *ss);
int skeylookup (struct skey * mp, char *name);
int skeyverify (struct skey * mp, char *response);
int skeyzero (struct skey * mp, char *response);
void sevenbit (char *s);
void backspace (char *s);
char *skipspace (char *s);
char *readpass (char *buf, int n);
char *readskey (char *buf, int n);
int skey_authenticate (char *username);
int skey_passcheck (char *username, char *passwd);
char *skey_keyinfo (char *username);
int skey_haskey (char *username);
int getskeyprompt (struct skey *mp, char *name, char *prompt);
int atob8 (char *out, char *in);
int btoa8 (char *out, char *in);
int htoi (int c);
const char *skey_get_algorithm (void);
char *skey_set_algorithm (char *new);
int skeygetnext (struct skey *mp);
