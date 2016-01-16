/******************************************************************************
 *
 *  Copyright (C) 2016 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#pragma once

#include <stdint.h>

typedef enum {
  DEVICE_TYPE_UNKNOWN,
  DEVICE_TYPE_BREDR,
  DEVICE_TYPE_LE,
  DEVICE_TYPE_DUMO,
} device_type_t;

// Record a pairing event at Unix epoch time |timestamp_ms|
// |device_class| and |device_type| denote the type of device paired.
// |disconnect_reason| is the HCI reason for pairing disconnection,
// see stack/include/hcidefs.h
void metrics_pair_event(uint32_t disconnect_reason, uint64_t timestamp_ms,
                        uint32_t device_class, device_type_t device_type);

typedef enum {
  WAKE_EVENT_UNKNOWN,
  WAKE_EVENT_ACQUIRED,
  WAKE_EVENT_RELEASED,
} wake_event_type_t;

// Record a wake event at Unix epoch time |timestamp_ms|.
// |type| specifies whether it was acquired or relased,
// |requestor| if provided is the service requesting the wake lock.
// |name| is the name of the wake lock held.
void metrics_wake_event(wake_event_type_t type, const char *requestor,
                        const char *name, uint64_t timestamp_ms);

typedef enum {
  SCAN_TYPE_UNKNOWN,
  SCAN_TECH_TYPE_LE,
  SCAN_TECH_TYPE_BREDR,
  SCAN_TECH_TYPE_BOTH,
} scan_tech_t;

// Record a scan event at Unix epoch time |timestamp_ms|.
// |start| is true if this is the beginning of the scan.
// |initiator| is a unique ID identifying the app starting the scan.
// |type| is whether the scan reports BR/EDR, LE, or both.
// |results| is the number of results to be reported.
void metrics_scan_event(bool start, const char *initator, scan_tech_t type,
                        uint32_t results, uint64_t timestamp_ms);

// Writes the metrics, in packed protobuf format, into the descriptor |fd|.
// If |clear| is true, metrics events are cleared afterwards.
void metrics_write(int fd, bool clear);

// Writes the metrics, in human-readable protobuf format, into the descriptor
// |fd|. If |clear| is true, metrics events are cleared afterwards.
void metrics_print(int fd, bool clear);
