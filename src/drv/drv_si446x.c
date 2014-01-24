/*
 * drv_si446x.c
 *
 *  Created on: Jan 20, 2014
 *      Author: aadamson
 */

#include "board.h"

uint32_t active_freq       = RADIO_FREQ;
uint8_t active_pwr         = RADIO_PWR;
uint16_t si446x_powerlevel = RADIO_PWR;

static void si446xEnable(void)
{
    GPIO_ResetBits(SI446x_CS_GPIO_PORT, SI446x_CS_PIN);
}

static void si446xDisable(void)
{
    GPIO_SetBits(SI446x_CS_GPIO_PORT, SI446x_CS_PIN);
}

static void si446xSDNEnable(void)
{
    GPIO_SetBits(SI446x_SDN_GPIO_PORT, SI446x_SDN_PIN);
}

static void si446xSDNDisable(void)
{
    GPIO_ResetBits(SI446x_SDN_GPIO_PORT, SI446x_SDN_PIN);
}

static void si446xVCXOEnable(void)
{
    GPIO_SetBits(SI446x_VCXO_GPIO_PORT, SI446x_VCXO_PIN);
}

static void si446xVCXODisable(void)
{
    GPIO_ResetBits(SI446x_VCXO_GPIO_PORT, SI446x_VCXO_PIN);
}

static void si446xSendRecv(int byteCountTx, int byteCountRx, const uint8_t *pData)
{
    si446xEnable();

#if 0
    cliPrint("\n");
    cliPrint("tx: ");

    for (int k = 0; k < byteCountTx; k++)
    {
        cliPrintF("%x ", pData[k]);
    }

    cliPrint("\n");
#endif

    for (int j = 0; j < byteCountTx; j++)
    {
        uint8_t wordb = pData[j];
        spiTransfer(SI446x_SPI, wordb);
    }

    si446xDisable();
    delayMicroseconds(20);
    si446xEnable();

    uint8_t reply = 0x00;

    while (reply != 0xFF)
    {
        reply = spiTransfer(SI446x_SPI, 0x44);
        //cliPrintF("%x ", reply);
        if (reply != 0xFF)
        {
            si446xDisable();
            delayMicroseconds(20);
            si446xEnable();
        }
    }

#if 0
    cliPrint("\n");
    cliPrint("rx: ");

    for (int k = 0; k < byteCountRx; k++)
    {
        cliPrintF("%x ", spiTransfer(SI446x_SPI, 0x00));
    }

    cliPrint("\n");
#endif

    si446xDisable();
    delay(200); // wait half a second to prevent Serial buffer overflow
}

static void si446xSetFrequency(uint32_t freq)
{
    // Set the output divider according to recommended ranges given in Si446x datasheet
    uint8_t outdiv = 4;
    uint8_t band   = 0;

    if (freq < 705000000UL) { outdiv = 6;  band = 1; };
    if (freq < 525000000UL) { outdiv = 8;  band = 2; };
    if (freq < 353000000UL) { outdiv = 12; band = 3; };
    if (freq < 239000000UL) { outdiv = 16; band = 4; };
    if (freq < 177000000UL) { outdiv = 24; band = 5; };

    uint32_t f_pfd = 2 * VCXO_FREQ / outdiv;

    uint16_t n = ((uint16_t)(freq / f_pfd)) - 1;

    float ratio = (float)freq / (float)f_pfd;
    float rest  = ratio - (float)n;

    uint32_t m = (uint32_t)(rest * 524288UL);

    // set the band parameter
    uint8_t sy_sel = 8;

    uint8_t set_band_property_command[] = {0x11, 0x20, 0x01, 0x51, (band + sy_sel)}; //
    // send parameters
    si446xSendRecv(5, 1, set_band_property_command);

    // Set the pll parameters
    uint16_t m2 = m / 0x10000;
    uint16_t m1 = (m - m2 * 0x10000) / 0x100;
    uint16_t m0 = (m - m2 * 0x10000 - m1 * 0x100);

    // assemble parameter string
    //uint8_t set_freq_control_inte[] = {0x11, 0x40, 0x04, 0x00, n, m2, m1, m0};
    const uint8_t set_freq_control_inte[] = {0x11, 0x40, 0x08, 0x00, n, m2, m1, m0, 0x0B, 0x61, 0x20, 0xFA};
    //const uint8_t set_freq_control_inte[] = {0x11, 0x40, 0x08, 0x00, n, m2, m1, m0, 0x0B, 0x61, 0x20, 0xFA};
    // send parameters
    si446xSendRecv(12, 1, set_freq_control_inte);

}

void si446xInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the SDN/VCXO Pin Clock */
    RCC_AHBPeriphClockCmd(SI446x_SDN_GPIO_CLK | SI446x_VCXO_GPIO_CLK, ENABLE);

    /* Enable the VCXO Pin Clock */
    //RCC_AHBPeriphClockCmd(SI446x_VCXO_GPIO_CLK, ENABLE);

    // f1 code needed there, may not be needed on f3
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,     ENABLE); // HJI
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // HJI

    /* Configure the SDN pin */
    GPIO_InitStructure.GPIO_Pin     = SI446x_SDN_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;

    GPIO_Init(SI446x_SDN_GPIO_PORT, &GPIO_InitStructure);

    // put the si in shutdown via sdn pin HIGH
    delay(10);

    si446xSDNEnable(); // active high = shutdown

    /* Configure the VCXO pin */
    GPIO_InitStructure.GPIO_Pin     = SI446x_VCXO_PIN;

    GPIO_Init(SI446x_VCXO_GPIO_PORT, &GPIO_InitStructure);

    // turn on the VCXO at startup
    si446xVCXOEnable();

    /* Configure the GPIO0 and IRQ pins */
    GPIO_InitStructure.GPIO_Pin     = SI446x_IRQ_PIN | SI446x_GPIO0_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(SI446x_VCXO_GPIO_PORT, &GPIO_InitStructure);
}

static void si446xStartTx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x07}; //  Change to TX state
    si446xSendRecv(2, 1, change_state_command);
}

static void si446xStopTx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x03}; //  Change to Ready state
    si446xSendRecv(2, 1, change_state_command);
}

static void si446xTuneTx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x05}; //  Change to TX tune state
    si446xSendRecv(2, 1, change_state_command);
}

static void si446xStartRx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x08}; //  Change to RX state
    si446xSendRecv(2, 1, change_state_command);
}

static void si446xStopRx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x03}; //  Change to Ready state
    si446xSendRecv(2, 1, change_state_command);
}

static void si446xTuneRx(void)
{
    const uint8_t change_state_command[] = {0x34, 0x06}; //  Change to RX tune state
    si446xSendRecv(2, 1, change_state_command);
}

// Configuration parameter functions ---------------------------------------
static void si446xSetModem(void)
{
    // Set to CW mode
    //  cliPrint("Setting modem into CW mode\n");
    const uint8_t set_modem_mod_type_command[] = {0x11, 0x20, 0x01, 0x00, 0x00};
    si446xSendRecv(5, 1, set_modem_mod_type_command);
}

void si446xSetPower(uint8_t pwr)
{
    // Set the Power
    uint8_t set_pa_pwr_lvl_property_command[] = {0x11, 0x22, 0x01, 0x01, pwr};
    // send parameters
    si446xSendRecv(5, 1, set_pa_pwr_lvl_property_command);
}

// Config reset ----------------------------------------------------------
static void si446xReset(void)
{
    si446xVCXOEnable();
    //  cliPrint("VCXO is enabled\n");
    delay(200);
    si446xSDNEnable();  // active high shutdown = reset

    delay(15);
    si446xSDNDisable();   // booting
    delay(15);
    // cliPrint("Radio is powered up\n");

    // Start talking to the Si446X radio chip
    //const uint8_t PART_INFO_command[] = {0x01}; // Part Info
    //si446xSendRecv(1, 9, PART_INFO_command);
    // cliPrint("Part info was checked\n");

    //divide VCXO_FREQ into its bytes; MSB first
    uint16_t x3 = VCXO_FREQ / 0x1000000;
    uint16_t x2 = (VCXO_FREQ - x3 * 0x1000000) / 0x10000;
    uint16_t x1 = (VCXO_FREQ - x3 * 0x1000000 - x2 * 0x10000) / 0x100;
    uint16_t x0 = (VCXO_FREQ - x3 * 0x1000000 - x2 * 0x10000 - x1 * 0x100);

    //POWER_UP
    const uint8_t init_command[] = {0x02, 0x01, 0x01, x3, x2, x1, x0};// no patch, boot main app. img, FREQ_VCXO, return 1 byte
    si446xSendRecv(7, 1 , init_command);
    // cliPrint("Radio booted\n");ssts

    const uint8_t get_int_status_command[] = {0x20, 0x00, 0x00, 0x00}; //  Clear all pending interrupts and get the interrupt status back
    si446xSendRecv(4, 9, get_int_status_command);
    // cliPrint("Radio ready\n");

    const uint8_t set_int_ctrl_enable[] = {0x11, 0x01, 0x01, 0x00, 0x00};
    si446xSendRecv(5, 1, set_int_ctrl_enable);
    // cliPrint("Setting no Interrupts (see WDS)\n");

    const uint8_t gpio_pin_cfg_command[] = {0x13, 0x02, 0x02, 0x02, 0x02, 0x08, 0x0B, 0x00}; //  Set all GPIOs LOW; Link NIRQ to CTS; Link SDO to MISO; Max drive strength
    si446xSendRecv(8, 8, gpio_pin_cfg_command);
    // cliPrint("LEDs should be switched off at this point\n");

    const uint8_t set_global_config1[] = {0x11, 0x00, 0x01, 0x03, 0x60};
    si446xSendRecv(5, 1, set_global_config1);
    // cliPrint("Setting special global Config 1 changes (see WDS)\n");

    const uint8_t set_global_xo_tune_command[] = {0x11, 0x00, 0x01, 0x00, 0x00};
    si446xSendRecv(5, 1, set_global_xo_tune_command);
    // cliPrint("Setting no additional capacitance on VXCO\n");

    si446xSetFrequency(active_freq);
    // cliPrint("Frequency set\n");

    si446xSetPower(active_pwr);
    // cliPrint("Power set\n");

    si446xSetModem();
    // cliPrint("CW mode set\n");

    si446xTuneTx();
    // cliPrint("TX tune\n");
}

void si446xPTTOn(void)
{
    si446xReset();

    // turn on the blue LED (GPIO2) to indicate TX
    const uint8_t gpio_pin_cfg_command2[] = {0x13, 0x02, 0x02, 0x03, 0x02, 0x08, 0x11, 0x00}; //  Set GPIO2 HIGH; Link NIRQ to CTS; Link SDO to MISO; Max drive strength
    si446xSendRecv(8, 1, gpio_pin_cfg_command2);

    si446xStartTx();
    si446x_powerlevel = 1023;
}

void si446xPTTOff(void)
{
    si446xStopTx();
    si446x_powerlevel = 0;

    // turn off the blue LED (GPIO2)
    const uint8_t gpio_pin_cfg_command0[] = {0x13, 0x02, 0x02, 0x02, 0x02, 0x08, 0x11, 0x00}; //  Set all GPIOs LOW; Link NIRQ to CTS; Link SDO to MISO; Max drive strength
    si446xSendRecv(8, 1, gpio_pin_cfg_command0);

    si446xSDNEnable();  // active high = shutdown
    //si446xVCXODisable(); // keep enabled for now
}

void si446xSetFreq(uint32_t freq)
{
    active_freq = freq;
}

/*
uint32_t si446xGetFreq(void)
{
    return active_freq;
}
*/

uint16_t si446xgetPower(void)
{
    return si446x_powerlevel;
}
