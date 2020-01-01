/*
 * WPA Supplicant - Windows/NDIS driver interface
 * Copyright (c) 2004-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef DRIVER_NDIS_H
#define DRIVER_NDIS_H

#ifdef CONFIG_NDIS_EVENTS_INTEGRATED
struct ndis_events_data;
struct ndis_events_data * ndis_events_init(HANDLE *read_pipe, HANDLE *event,
					   const char *ifname,
					   const char *desc);
void ndis_events_deinit(struct ndis_events_data *events);
#endif /* CONFIG_NDIS_EVENTS_INTEGRATED */
#define MAX_DRV_EVENT_QUEUE  			10
#define MAX_DRV_EVENT_BUF_SIZE			64

struct ndis_pmkid_entry {
	struct ndis_pmkid_entry *next;
	u8 bssid[ETH_ALEN];
	u8 pmkid[16];
};

struct drv_event {
	u32 event;
	u32 data_len;
	u8	data[MAX_DRV_EVENT_BUF_SIZE];
};
struct wpa_driver_ndis_data {
	void *ctx;
	char ifname[100]; /* GUID: {7EE3EFE5-C165-472F-986D-F6FBEDFE8C8D} */
#ifdef _WIN32_WCE
	TCHAR *adapter_name;
	HANDLE event_queue; /* NDISUIO notifier MsgQueue */
	HANDLE connected_event; /* WpaSupplicantConnected event */
#endif /* _WIN32_WCE */
	u8 own_addr[ETH_ALEN];
#ifdef CONFIG_USE_NDISUIO
	HANDLE ndisuio;
#else /* CONFIG_USE_NDISUIO */
	LPADAPTER adapter;
#endif /* CONFIG_USE_NDISUIO */
	u8 bssid[ETH_ALEN];

	int has_capability;
	int no_of_pmkid;
	int radio_enabled;
	struct wpa_driver_capa capa;
	struct ndis_pmkid_entry *pmkid;
	char *adapter_desc;
	int wired;
	int mode;
	int wzc_disabled;
	int oid_bssid_set;
	int power_mode;
#ifdef CONFIG_NDIS_EVENTS_INTEGRATED
	HANDLE events_pipe, event_avail;
	struct ndis_events_data *events;
#endif /* CONFIG_NDIS_EVENTS_INTEGRATED */

#ifdef DRV_NOTIFY_USE_EVENT
	os_lock  event_lock;			// shared with wifi driver
#else
    os_lock  con_event_lock;    // lock for connection event
    struct drv_event *con_event;
    int con_status;
#endif
    unsigned int events;           	// event from driver
    struct drv_event *et_head;		// point to header of pending event
    struct drv_event *et_tail;		// point to tail of pending event
    struct drv_event et_queue[MAX_DRV_EVENT_QUEUE];  // event queue
    //unsigned char event_msg[524];	// event msg, length = header(12) + data(512)

    os_mailbox event_mbox;
    os_semaphore sem_oid;
    unsigned char oid_req_id;
    void *cb_oid_msg;
    int   cb_oid_len;
    unsigned int cb_oid_status;

    unsigned int reset; //AQU_RESET

	/**
	 * freq - Frequency of the channel the selected AP is using
	 * Frequency that the selected AP is using (in MHz as
	 * reported in the scan results)
	 */
	int freq;
};

#endif /* DRIVER_NDIS_H */
