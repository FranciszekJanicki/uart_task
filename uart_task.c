#include "uart_task.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "task.h"
#include "uart_manager.h"
#include "usart.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

static void uart_task_func(void* task_param)
{
    assert(task_param != NULL);

    uart_task_ctx_t* task_ctx = (uart_task_ctx_t*)task_param;

    uart_manager_t manager;
    uart_manager_initialize(&manager,
                            task_ctx->stream_buffer,
                            task_ctx->uart,
                            task_ctx->uart_buffer,
                            task_ctx->uart_buffer_size,
                            task_ctx->uart_action);

    while (1) {
        uart_manager_process(&manager);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

TaskHandle_t uart_task_initialize(uart_task_ctx_t* task_ctx,
                                  StaticTask_t* task_buffer,
                                  UBaseType_t task_priority,
                                  UBaseType_t task_stack_size,
                                  StackType_t* task_stack)
{
    assert(task_ctx && task_buffer && task_stack);

    return xTaskCreateStatic(uart_task_func,
                             "uart_task",
                             task_stack_size,
                             task_ctx,
                             task_priority,
                             task_stack,
                             task_buffer);
}

StreamBufferHandle_t uart_stream_buffer_initialize(StaticStreamBuffer_t* stream_buffer,
                                                   UBaseType_t stream_buffer_trigger,
                                                   UBaseType_t stream_buffer_storage_size,
                                                   uint8_t* stream_buffer_storage)
{
    assert(stream_buffer && stream_buffer_storage);

    return xStreamBufferCreateStatic(stream_buffer_storage_size,
                                     stream_buffer_trigger,
                                     stream_buffer_storage,
                                     stream_buffer);
}