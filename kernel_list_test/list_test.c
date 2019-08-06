#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

#include "list.h"

#define HASH_MASK		((1 << 8) - 1)

struct list_head user_slots[HASH_MASK + 1];

struct user {
	struct list_head hnode;
	char mac[18]; 
	time_t active_time; 
	time_t magic_time; 
};

static void hash_init() {
	int i =0;
	for(; i<HASH_MASK; i++) {
		INIT_LIST_HEAD(&user_slots[i]); 
	}
}


static unsigned int hash_crc(const void *p, int len) {
	int i;
	unsigned int hash = 0;
	const unsigned char *addr = (const unsigned char*)p;

	for (i = 0; i < len; i++)
		hash += hash * 33 + addr[i];
	return hash;
}

static void set_user(int add, struct user *user , struct list_head *macslot,  char* mac,  time_t now) {
	if (!add) {
		list_del(&user->hnode);
		free(user);
		return;
	}
	if (strcmp(user->mac, mac)) {
		strcpy(user->mac, mac);
	}
	user->active_time = now;
	list_add(&user->hnode, macslot);
}


struct user *user_insert(char *mac) {

	struct user *user = NULL, *pos = NULL;
	struct list_head *user_slot =  &user_slots[hash_crc(mac, strlen(mac)) & HASH_MASK];
	time_t now = time(NULL);
	list_for_each_entry_safe(user, pos, user_slot, hnode) {
		if (!strcmp(mac, user->mac)) {
			user->active_time = now;
			return user;
		}
	}
	user = (struct user*)malloc(sizeof(struct user));
	if (!user) {
		return NULL;
	}
	memset(user, 0, sizeof(struct user));
	set_user(1, user, user_slot,  mac,  now);
	return user;
}

static void  user_delete(char *mac) {
	struct user *user = NULL, *pos = NULL;
	time_t now = time(NULL);
	struct list_head *user_slot =  &user_slots[hash_crc(mac, strlen(mac)) & HASH_MASK];
	list_for_each_entry_safe(user, pos, user_slot, hnode) {
		if (!strcmp(mac, user->mac)) {
			set_user(0, user, user_slot,  mac, now);
			return;
		}
	}
}

struct user *user_lookup(const char *mac) {
	struct user *user = NULL, *pos = NULL;
	struct list_head *user_slot =  &user_slots[hash_crc(mac, strlen(mac)) & HASH_MASK];
	list_for_each_entry_safe(user,pos, user_slot, hnode) {
		if ( !strcmp(mac, user->mac)) {
			return user;
		}
	}
	return NULL;
}

static void list_print() {
	int i = 0;
	struct user *user = NULL, *pos = NULL;
	struct list_head *user_slot = NULL;
	
	for(i=0; i<HASH_MASK; i++) {
		user_slot = &user_slots[i];
		list_for_each_entry_safe(user, pos, user_slot, hnode) {
			printf("user->mac = %s, user->actiev_time = %lu\n", user->mac, user->active_time);
		}
	}
	printf("\n");
}


int main(){
	hash_init();

	user_insert("EE:EE:FF:FF:EF");
	user_insert("12:34:56:78:98");
	user_insert("FF:FF:FF:FF:FF");
	user_insert("E3:E3:E3:E3:E4");
	
	list_print();
	
	user_delete("E3:E3:E3:E3:E4");
	user_delete("E3:E3:E3:E3:E4");
	
	user_insert("EF:88:88:88:88");
	
	list_print();
	
	return 0;
}