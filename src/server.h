#ifndef SERVER_H
#define SERVER_H

#include <time.h>

#include "rirc.h"

#include "buffer.h"
#include "channel.h"

struct server_list
{
	struct server *head;
};

struct server
{
	//TODO: strdup this. Remove arbitrary NICKSIZE
	char nick[NICKSIZE + 1];
	//TODO: can be grouped together, autonick
	char *nicks;
	char *nptr;
	char *host;
	char *port;
	//TODO: this shouldn't persist with the server,
	// its only relevant on successful connection
	char *join;
	char usermodes[MODE_SIZE];
	//TODO: nicklist
	struct avl_node *ignore;
	//TODO channel_list
	struct channel *channel;
	//TODO:
	struct server *next;
	struct server *prev;
	//TODO: connection stuff
	char input[BUFFSIZE];
	char *iptr;
	int pinging;
	int soc;
	time_t latency_delta;
	time_t latency_time;
	time_t reconnect_delta;
	time_t reconnect_time;
	void *connecting;
	//TODO: WIP
	struct channel_list clist;

	struct {
		struct {
			/* Map lower + upper -> lower + upper */
			char F[26 * 2 + 1];
			char T[26 * 2 + 1];
		} PREFIX;
		struct {
			char *CHANMODES_A;
			char *CHANMODES_B;
			char *CHANMODES_C;
			char *CHANMODES_D;
			/* lower + upper + 4 terminators */
			char _[26 * 2 + 4];
		} CHANMODES;
	} config;
};

void server_set_N005(struct server*, char*);

struct server* server(char*, char*, char*);

struct server* server_add(struct server_list*, struct server*);
struct server* server_get(struct server_list*, struct server*);
struct server* server_del(struct server_list*, struct server*);

#endif
