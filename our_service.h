
#ifndef OUR_SERVICE_H__
#define OUR_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"


//#define BLE_UUID_OUR_BASE_UUID              {{0x33, 0xD1, 0x13, 0xEF, 0x5F, 0x78, 0x63, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}}
#define BLE_UUID_OUR_BASE_UUID              {{0x64, 0x4F, 0x76, 0xF7, 0xA6, 0x52, 0x42, 0xBC, 0xE9, 0x11, 0xD2, 0x91, 0xDA, 0x10, 0xE4, 0xAE}} // 128-bit base UUID
#define BLE_UUID_OUR_SERVICE_UUID                0xF00D // Just a random, but recognizable value
#define BLE_UUID_OUR_SERVICE_UUID_2                0xF00E // Just a random, but recognizable value


#define BLE_UUID_OUR_CHARACTERISTC_UUID          0xBEEA // Just a random, but recognizable value
#define BLE_UUID_OUR_CHARACTERISTC_UUID_2        0xBEEB // Just a random, but recognizable value
#define BLE_UUID_OUR_CHARACTERISTC_UUID_3        0xBEEC // Just a random, but recognizable value


// This structure contains various status information for our service. 
// The name is based on the naming convention used in Nordics SDKs. 
// 'ble� indicates that it is a Bluetooth Low Energy relevant structure and 
// �os� is short for Our Service). 
typedef struct
{
    uint16_t                    conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).*/
    uint16_t                    service_handle; /**< Handle of Our Service (as provided by the BLE stack). */
    ble_srv_cccd_security_mode_t custom_value_char_attr_md;
    // OUR_JOB: Step 2.D, Add handles for the characteristic attributes to our struct
    ble_gatts_char_handles_t    char_handles;
    ble_gatts_char_handles_t    char_handles_2;
    ble_gatts_char_handles_t    char_handles_3;
}ble_os_t;






/**@brief Function for handling BLE Stack events related to our service and characteristic.
 *
 * @details Handles all events from the BLE stack of interest to Our Service.
 *
 * @param[in]   p_our_service       Our Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_our_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Function for initializing our new service.
 *
 * @param[in]   p_our_service       Pointer to Our Service structure.
 */
void our_service_init(ble_os_t * p_our_service);

/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever our timer_timeout_handler triggers
 *
 * @param[in]   p_our_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */
void our_temperature_characteristic_update(ble_os_t *p_our_service, int32_t *temperature_value);

#endif  /* _ OUR_SERVICE_H__ */
