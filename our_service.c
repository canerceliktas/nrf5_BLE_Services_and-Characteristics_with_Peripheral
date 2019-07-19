//added github support
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "our_service.h"
#include "ble_srv_common.h"
#include "app_error.h"

extern int button_value;

// Declaration of a function that will take care of some housekeeping of ble connections related to our service and characteristic
void ble_our_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{       
        ble_gatts_evt_write_t * p_evt_write;
  	ble_os_t * p_our_service =(ble_os_t *) p_context;  
		//Implement switch case handling BLE events related to our service. 
                switch (p_ble_evt->header.evt_id)
                {
                    case BLE_GAP_EVT_CONNECTED:
                        p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
                        break;
                    case BLE_GAP_EVT_DISCONNECTED:
                        p_our_service->conn_handle = BLE_CONN_HANDLE_INVALID;
                        break;
                    case  BLE_GATTS_EVT_WRITE:
                        p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
                        
                        if(p_evt_write->handle == p_our_service->char_handles_3.value_handle) //If the write event come from characteristic 3 // write iþlemi gerçekleþen characteristic 3. ise
                        { 
                          if(*p_evt_write->data == 0x12)
                            {                             
                              button_value = 1;
                              nrf_gpio_pin_clear(14);
                              nrf_gpio_pin_set(15);
                              
                            }
                          else if(*p_evt_write->data == 0x13)
                            { 
                              button_value = 0;
                              nrf_gpio_pin_clear(15);
                              nrf_gpio_pin_set(14);
                              nrf_gpio_pin_set(16);
                            }

                        }
                        
                        break;
                    default:
                        // No implementation needed.
                        break;
                }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
static uint32_t our_char_add(ble_os_t * p_our_service)
{
    //Add a custom characteristic UUID
    uint32_t      err_code;
    ble_uuid_t    char_uuid;
    ble_uuid128_t base_uuid = BLE_UUID_OUR_BASE_UUID;
    char_uuid.uuid          = BLE_UUID_OUR_CHARACTERISTC_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
    APP_ERROR_CHECK(err_code);

    


    //Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
    char_md.char_props.read = 1;
    char_md.char_props.write = 1;



    
    //Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
    char_md.p_cccd_md           = &cccd_md;
    char_md.char_props.notify   = 1;

   
    
    //Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));
    attr_md.vloc = BLE_GATTS_VLOC_STACK; //Store the attributes in stack(softdevice)

	
    
    
    //Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    //Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid  = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;



    
    //Set characteristic length in number of bytes
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x12,0x34,0x56,0x78};
    attr_char_value.p_value     = value;


    // Add our new characteristic to the service
    err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_our_service->char_handles);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}


static uint32_t our_char_add_2(ble_os_t * p_our_service)
{
    //Add a custom characteristic UUID
    uint32_t      err_code;
    ble_uuid_t    char_uuid_2;
    ble_uuid128_t base_uuid = BLE_UUID_OUR_BASE_UUID;
    char_uuid_2.uuid          = BLE_UUID_OUR_CHARACTERISTC_UUID_2;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid_2.type);
    APP_ERROR_CHECK(err_code);

    


    //Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md_2;
    memset(&char_md_2, 0, sizeof(char_md_2));
    char_md_2.char_props.read = 1;
    char_md_2.char_props.write = 1;



    
    //Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md_2;
    memset(&cccd_md_2, 0, sizeof(cccd_md_2));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md_2.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md_2.write_perm);
    cccd_md_2.vloc                = BLE_GATTS_VLOC_STACK;    
    char_md_2.p_cccd_md           = &cccd_md_2;
    char_md_2.char_props.notify   = 1;

   
    
    //Configure the attribute metadata
    ble_gatts_attr_md_t attr_md_2;
    memset(&attr_md_2, 0, sizeof(attr_md_2));
    attr_md_2.vloc = BLE_GATTS_VLOC_STACK; //Store the attributes in stack(softdevice)

	
    
    
    //Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md_2.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md_2.write_perm);
    
    //Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value_2;
    memset(&attr_char_value_2, 0, sizeof(attr_char_value_2));
    attr_char_value_2.p_uuid  = &char_uuid_2;
    attr_char_value_2.p_attr_md = &attr_md_2;



    
    //Set characteristic length in number of bytes
    attr_char_value_2.max_len     = 4;
    attr_char_value_2.init_len    = 4;
    uint8_t value[4]              = {0x00,0x11,0x22,0x33};
    attr_char_value_2.p_value     = value;


    //Add our new characteristic to the service
    err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md_2,
                                   &attr_char_value_2,
                                   &p_our_service->char_handles_2);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}

static uint32_t our_char_add_3(ble_os_t * p_our_service)
{
    // Add a custom characteristic UUID
    uint32_t      err_code;
    ble_uuid_t    char_uuid_3;
    ble_uuid128_t base_uuid = BLE_UUID_OUR_BASE_UUID;
    char_uuid_3.uuid          = BLE_UUID_OUR_CHARACTERISTC_UUID_3;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid_3.type);
    APP_ERROR_CHECK(err_code);

    


    //Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md_3;
    memset(&char_md_3, 0, sizeof(char_md_3));
    char_md_3.char_props.read = 1;
    char_md_3.char_props.write = 1;



    
    //Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md_3;
    memset(&cccd_md_3, 0, sizeof(cccd_md_3));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md_3.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md_3.write_perm);
    cccd_md_3.vloc                = BLE_GATTS_VLOC_STACK;    
    char_md_3.p_cccd_md           = &cccd_md_3;
    char_md_3.char_props.notify   = 1;
    char_md_3.char_props.write_wo_resp = 1;

   
    
    //Configure the attribute metadata
    ble_gatts_attr_md_t attr_md_3;
    memset(&attr_md_3, 0, sizeof(attr_md_3));
    attr_md_3.vloc = BLE_GATTS_VLOC_STACK; //Store the attributes in stack(softdevice)

    //Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md_3.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md_3.write_perm);
    
    //Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value_3;
    memset(&attr_char_value_3, 0, sizeof(attr_char_value_3));
    attr_char_value_3.p_uuid  = &char_uuid_3;
    attr_char_value_3.p_attr_md = &attr_md_3;
    
    //Set characteristic length in number of bytes
    attr_char_value_3.max_len     = 1;
    attr_char_value_3.init_len    = 1;
    uint8_t value[2]              = {0x23};
    attr_char_value_3.p_value     = value;


    // Add our new characteristic to the service
    err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md_3,
                                   &attr_char_value_3,
                                   &p_our_service->char_handles_3);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**@brief Function for initiating our new service.
 *
 * @param[in]   p_our_service        Our Service structure.c
 */
void our_service_init(ble_os_t * p_our_service)
{
    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    //Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid_t        service_uuid_2;
    ble_uuid128_t     base_uuid = BLE_UUID_OUR_BASE_UUID;
    service_uuid_2.uuid = BLE_UUID_OUR_SERVICE_UUID_2; 
    service_uuid.uuid = BLE_UUID_OUR_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);  
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid_2.type);
    APP_ERROR_CHECK(err_code);
    
    // Set our service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.
    p_our_service->conn_handle = BLE_CONN_HANDLE_INVALID;

    // Add our service
		err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_our_service->service_handle);
                APP_ERROR_CHECK(err_code);
    //Call the function our_char_add() to add our new characteristic to the service. 
    our_char_add(p_our_service);
      
    //Add our service
		err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid_2,
                                        &p_our_service->service_handle);
                APP_ERROR_CHECK(err_code);
    our_char_add_2(p_our_service);
    our_char_add_3(p_our_service);
    
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








//Function to be called when updating characteristic value
void our_voltage_characteristic_update(ble_os_t *p_our_service, int32_t *voltage)
{
    // Update characteristic value
    if (p_our_service->conn_handle != BLE_CONN_HANDLE_INVALID)//baðlantý varmý diye kontorl ediyor. baðlantý yoksa soft device hata verir
    {
      uint16_t               len = 4;
      ble_gatts_hvx_params_t hvx_params;
      memset(&hvx_params, 0, sizeof(hvx_params));

      hvx_params.handle = p_our_service->char_handles.value_handle;
      hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
      hvx_params.offset = 0;
      hvx_params.p_len  = &len;
      hvx_params.p_data = (uint8_t*)voltage;  

      sd_ble_gatts_hvx(p_our_service->conn_handle, &hvx_params);
    }

}

// Function to be called when updating characteristic value
void our_temperature_characteristic_update_2(ble_os_t *p_our_service, int32_t *temperature)
{
    // Update characteristic value
    if (p_our_service->conn_handle != BLE_CONN_HANDLE_INVALID)//Checking the connection status, SoftDevice occurs error if there is no connection
    {
      uint16_t               len = 4;
      ble_gatts_hvx_params_t hvx_params;
      memset(&hvx_params, 0, sizeof(hvx_params));

      hvx_params.handle = p_our_service->char_handles_2.value_handle; //char_handles_2 olduðu için 2.karakteristiði güncelliyor
      hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
      hvx_params.offset = 0;
      hvx_params.p_len  = &len;
      hvx_params.p_data = (uint8_t*)temperature;  

      sd_ble_gatts_hvx(p_our_service->conn_handle, &hvx_params);
    }

}

