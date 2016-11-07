#ifndef CODAL_SYSTEM_CLOCK_H
#define CODAL_SYSTEM_CLOCK_H

#include <stdint.h>

#include "DeviceComponent.h"
#include "list.h"
#include "ErrorNo.h"

#include "Arduino.h"

#define SYSTEM_CLOCK_INIT 0x01

struct ClockEvent
{
    uint16_t value;
    uint64_t period;
    uint64_t countUs;
    struct list_head list;

    void addToList(list_head* head)
    {
        ClockEvent* tmp = NULL;
        struct list_head *iter, *q = NULL;

        list_for_each_safe(iter, q, head)
        {
            tmp = list_entry(iter, ClockEvent, list);

            if(tmp->countUs < this->countUs)
                continue;

            break;
        }

        list_add(&this->list, iter);
    }

    ClockEvent(uint64_t period, int value, list_head* head, bool repeating = false)
    {
        this->countUs = period;
        this->value = value;

        this->period = 0;

        if(repeating)
            this->period = period;

        addToList(head);
    };
};

struct ClockPrescalerConfig
{
    uint16_t prescaleValue;
    uint16_t register_config;
};

class SystemClock : protected DeviceComponent
{

public:

    /**
      * Constructor for a generic system clock interface.
      */
    SystemClock() {};

    /**
      * Initialises and starts this SystemClock instance
      */
    virtual int init() { return DEVICE_NOT_SUPPORTED; };

    /**
      * Retrieves the device component id for this SystemClock instance.
      */
    virtual int getId() { return DEVICE_NOT_SUPPORTED; };

    /**
      * Sets the current time tracked by this SystemClock instance
      * in milliseconds
      *
      * @param timestamp the new time for this SystemClock instance in milliseconds
      */
    virtual int setTime(uint64_t timestamp) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Sets the current time tracked by this SystemClock instance
      * in microseconds
      *
      * @param timestamp the new time for this SystemClock instance in microseconds
      */
    virtual int setTimeUs(uint64_t timestamp);

    /**
      * Retrieves the current time tracked by this SystemClock instance
      * in milliseconds
      *
      * @return the timestamp in milliseconds
      */
    virtual uint64_t getTime() { return 0; };

    /**
      * Retrieves the current time tracked by this SystemClock instance
      * in microseconds
      *
      * @return the timestamp in microseconds
      */
    virtual uint64_t getTimeUs() { return 0; };

    /**
      * Configures this SystemClock instance to fire an event after period
      * milliseconds.
      *
      * @param period the period to wait until an event is triggered, in milliseconds.
      *
      * @param value the value to place into the Events' value field.
      */
    virtual int eventAfter(uint64_t period, uint16_t value) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Configures this SystemClock instance to fire an event after period
      * microseconds.
      *
      * @param period the period to wait until an event is triggered, in microseconds.
      *
      * @param value the value to place into the Events' value field.
      */
    virtual int eventAfterUs(uint64_t period, uint16_t value) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Configures this SystemClock instance to fire an event every period
      * milliseconds.
      *
      * @param period the period to wait until an event is triggered, in milliseconds.
      *
      * @param value the value to place into the Events' value field.
      */
    virtual int eventEvery(uint64_t period, uint16_t value) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Configures this SystemClock instance to fire an event every period
      * microseconds.
      *
      * @param period the period to wait until an event is triggered, in microseconds.
      *
      * @param value the value to place into the Events' value field.
      */
    virtual int eventEveryUs(uint64_t period, uint16_t value) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Start this SystemClock instance.
      *
      * @param precisionUs The precisions that the timer should use.
      */
    virtual int start(uint64_t precisionUs) { return DEVICE_NOT_SUPPORTED; };

    /**
      * Stop this SystemClock instance
      */
    virtual int stop() { return DEVICE_NOT_SUPPORTED; };

    /**
      * Destructor for this SystemClock instance
      */
    virtual ~SystemClock() { stop(); };
};

#endif
