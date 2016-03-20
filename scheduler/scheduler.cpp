//
//  scheduler.cpp
//  ds_motor
//
//  Created by David Cluytens on 12/10/12.
//  Copyright (c) 2012 Cluytens.net All rights reserved.
//

#include "Arduino.h"
#include "scheduler.h"
#include <Console.h>


void SchedulerClass::set_event_list(event_t *list, size_t size) {
    events      = list;
    event_size  = size;
    max_index   = size / sizeof(event_t);
}

void SchedulerClass::update_events(unsigned long new_epoch) {
    /* Update scheduler without triggering any events */
    for (size_t i = 0; i < max_index; i++) {
        /* Only Update Enabled tasks */
        if (events[i].time) {
            while (new_epoch > events[i].time) {
                events[i].time += events[i].next_event;
            }
        }
    }
    return;
}

void SchedulerClass::update(unsigned long prev_time, unsigned long cur_time) {
    for (size_t i = 0; i < max_index; i++) {
        /* Set Time to 0 To Disable Tasks */
        if ((events[i].time) && (cur_time >= events[i].time)) {
            events[i].event_cb(events[i].time, events[i].pin, events[i].rt_time);
            
            /* Only Update Enabled tasks */
            if (events[i].time) {
                do {
                    events[i].time += events[i].next_event;
                }while (cur_time > events[i].time);
            }
        }
    }
    return;
}

SchedulerClass Scheduler;