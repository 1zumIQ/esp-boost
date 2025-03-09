#include "esp_log.h"
#include "esp_heap_caps.h"
#include "esp_pthread.h"
#include "common_components.hpp"

static size_t memory_leak_threshold = 0;

static const char *TAG = "common_components";

void common_set_pthread_config(const char *name, int core_id, int stack, int prio, bool use_psram, bool inherit_cfg)
{
    auto cfg = esp_pthread_get_default_config();
    cfg.thread_name = name;
    cfg.pin_to_core = core_id;
    cfg.stack_size = stack;
    cfg.prio = prio;
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 3, 0)) && CONFIG_SPIRAM
    cfg.stack_alloc_caps = (use_psram ? MALLOC_CAP_SPIRAM : MALLOC_CAP_INTERNAL) | MALLOC_CAP_8BIT;
#endif
    cfg.inherit_cfg = inherit_cfg;
    esp_err_t err = esp_pthread_set_cfg(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_pthread_set_cfg err: %s\n", esp_err_to_name(err));
        abort();
    }
}

void common_reset_pthread_config()
{
    esp_pthread_cfg_t cfg = esp_pthread_get_default_config();
    esp_err_t err = esp_pthread_set_cfg(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_pthread_set_cfg err: %s\n", esp_err_to_name(err));
        abort();
    }
}

void common_set_memory_leak_threshold(size_t threshold)
{
    memory_leak_threshold = threshold;
}

size_t common_get_memory_leak_threshold()
{
    return memory_leak_threshold;
}
