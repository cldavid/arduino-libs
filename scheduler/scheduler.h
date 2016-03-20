//
//  scheduler.h
//  ds_motor
//
//  Created by David Cluytens on 12/10/12.
//  Copyright (c) 2012 Cluytens.net All rights reserved.
//

#ifndef ds_motor_scheduler_h
#define ds_motor_scheduler_h

#include <inttypes.h>

typedef struct {
    unsigned long   time;
    unsigned long   rt_time;
    unsigned int    pin;
    unsigned long   next_event;
    void            (*event_cb)(unsigned long time, unsigned int pin, unsigned long rt_time);
} event_t;

class SchedulerClass
{
    private:
    event_t     *events;
    size_t       event_size;
    size_t       max_index;
    
    public:
        void    set_event_list(event_t *list, size_t size);
        void    update_events(unsigned long new_epoch);
        void    update(unsigned long prev_time, unsigned long cur_time);
};

extern SchedulerClass Scheduler;


#endif
