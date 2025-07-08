#ifndef UART_TASK_UART_TASK_H
#define UART_TASK_UART_TASK_H

#include "FreeRTOS.h"
#include "stm32l4xx_hal.h"
#include "stream_buffer.h"
#include "task.h"
#include "uart_config.h"
#include <stdint.h>

typedef struct {
    StreamBufferHandle_t stream_buffer;
    UART_HandleTypeDef* uart;
    size_t uart_buffer_size;
    uint8_t* uart_buffer;
    uart_action_t uart_action;
} uart_task_ctx_t;

TaskHandle_t uart_task_initialize(uart_task_ctx_t* task_ctx,
                                  StaticTask_t* task_buffer,
                                  UBaseType_t task_priority,
                                  UBaseType_t task_stack_size,
                                  StackType_t* task_stack);

StreamBufferHandle_t uart_stream_buffer_initialize(StaticStreamBuffer_t* stream_buffer,
                                                   UBaseType_t stream_buffer_trigger,
                                                   UBaseType_t stream_buffer_storage_size,
                                                   uint8_t* stream_buffer_storage);

#endif // UART_TASK_UART_TASK_H