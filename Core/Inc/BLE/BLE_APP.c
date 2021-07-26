/*
 * BLE_APP.c
 *
 *  Created on: 3 mar. 2021
 *      Author: pablo
 */


#include"BLE_APP.h"

#define ROLE_CENTRAL 0
#define ROLE_PERIPHERAL 1
#define BYTE_1 0x01
#define BYTE_2 0x01

#define ID_CENTENAS '1'
uint8_t bdaddr[6];





void StartBeaconing(void)
{

	    char local_name[8] = {AD_TYPE_COMPLETE_LOCAL_NAME,'H','O','W','L','A','B',ID_UNIDADES,0};
	    	  uint8_t manuf_data[26] = {
	    	    2,0x0A,0x00 /* 0 dBm */, // Trasmission Power
	    	    8,0x09,'H','O','W','L','A',ID_UNIDADES,0, // Complete Name
	    	    13,0xFF,0x01/*SKD version */,
	    	    0x02,
	    	    0x00, /* */
	    	    0x33, /* ACC+Gyro+Mag*/
	    	    0x00, /*  */
	    	    0x00, /*  */
	    	    0x00, /* BLE MAC start */
	    	    0x00,
	    	    0x00,
	    	    0x00,
	    	    0x00,
	    	    0x00, /* BLE MAC stop */
	    	  };

	    	  /* BLE MAC */
	    	  manuf_data[20] = bdaddr[5];
	    	  manuf_data[21] = bdaddr[4];
	    	  manuf_data[22] = bdaddr[3];
	    	  manuf_data[23] = bdaddr[2];
	    	  manuf_data[24] = bdaddr[1];
	    	  manuf_data[25] = bdaddr[0];

	    	  manuf_data[16] |= 0x20; /* Led */


	    	    manuf_data[17] |= 0x10; /* Pressure value*/

	    	    manuf_data[18] |=0x04;




	    	    int ret = 0;
	  /* disable scan response */
	   ret = hci_le_set_scan_resp_data(0,NULL);
	  ret = aci_gap_set_discoverable(ADV_IND, 0x05A0, 0x05A2, RANDOM_ADDR, NO_WHITE_LIST_USE, sizeof(local_name), local_name, 0, NULL, 0, 0);

	  /* Send Advertising data */
	  ret = aci_gap_update_adv_data(26, manuf_data);
}



 void Init_BlueNRG_Custom_Services(BLE_Estados_t estado_BLE)
{
	 if(estado_BLE == PERIPHERAL)
	 	{
		 Add_HWServW2ST_Service();
	 	}

	if(estado_BLE == PERIPHERAL)
	{
		StartBeaconing();
	}
	else if(estado_BLE == CENTRAL)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET);
	    HAL_Delay(1);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET);
		int ret = aci_gap_start_general_discovery_proc(0x4000,0x4000,STATIC_RANDOM_ADDR, 1);
		while(ret != 0);
	}
}




 void Init_BlueNRG_Stack(BLE_Estados_t estado_BLE)
 {
   const char BoardName[8] = {'H','O','W','L','A','B','1',0};
   uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
   uint8_t data_len_out;
   int ret;

   /* Initialize the BlueNRG HCI */
   hci_init(HCI_Event_CB, NULL);

   /*
   * Reset BlueNRG again otherwise we won't
   * be able to change its MAC address.
   * aci_hal_write_config_data() must be the first
   * command after reset otherwise it will fail.
   */
   aci_hal_read_config_data(CONFIG_DATA_RANDOM_ADDRESS, 6, &data_len_out, bdaddr);
   hci_reset();

      HAL_Delay(100);


      /* Set the public address */
      ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
                                      CONFIG_DATA_PUBADDR_LEN,
                                      bdaddr);

   if(ret)
   {
     goto fail;
   }



   //HAL_Delay(100);
   ret = aci_gatt_init();
   if(ret)
   {

     goto fail;
   }

if(estado_BLE == PERIPHERAL)
{
  ret = aci_gap_init_IDB05A1(GAP_PERIPHERAL_ROLE_IDB05A1, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);
}
else if(estado_BLE == CENTRAL)
{
   ret = aci_gap_init_IDB05A1(GAP_CENTRAL_ROLE_IDB05A1, 0, 0x09, &service_handle, &dev_name_char_handle, &appearance_char_handle);
}

   if(ret != BLE_STATUS_SUCCESS)
   {
     goto fail;
   }

   //STATIC_BLE_MAC
   ret = hci_le_set_random_address(bdaddr);
   if(ret)
   {
 	  goto fail;
   }

   ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0,  7, (uint8_t *)BoardName);
  //HAL_Delay(100);
   if(ret)
   {
     while(1);
   }

   ret = aci_gap_set_auth_requirement(MITM_PROTECTION_REQUIRED,
                                      OOB_AUTH_DATA_ABSENT,
                                      NULL, 7, 16,
                                      USE_FIXED_PIN_FOR_PAIRING, 123456,
                                      BONDING);
   if (ret != BLE_STATUS_SUCCESS)
   {
      goto fail;
   }

     /* Set output power level */
   aci_hal_set_tx_power_level(1,4);

   //HAL_Delay(100);
   return;

 fail:
   return;

 }
