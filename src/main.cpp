#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <driver/i2s_std.h>

const char* ssid = "RED"; // NOMBRE DE TU RED WIFI
const char* password = "CONTRASEÑA"; // CONTRASEÑA DE TU RED WIFI
const char* udpAddress = "192.168.X.XXX"; // IP DE TU COMPUTADORA
const int udpPort = 4444;

WiFiUDP udp;
i2s_chan_handle_t rx_handle;

void setup_i2s() {
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    i2s_new_channel(&chan_cfg, NULL, &rx_handle);
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000), 
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {.mclk = I2S_GPIO_UNUSED, .bclk = GPIO_NUM_1, .ws = GPIO_NUM_2, .dout = I2S_GPIO_UNUSED, .din = GPIO_NUM_3},
    };
    i2s_channel_init_std_mode(rx_handle, &std_cfg);
    i2s_channel_enable(rx_handle);
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); }
    setup_i2s();
    Serial.println("Transmitiendo a Python...");
}

void loop() {
    int16_t buffer[512]; 
    size_t bytes_read;

    if (i2s_channel_read(rx_handle, &buffer, sizeof(buffer), &bytes_read, 100) == ESP_OK) {
        if (bytes_read > 0) {
            udp.beginPacket(udpAddress, udpPort);
            udp.write((uint8_t*)buffer, bytes_read);
            udp.endPacket();
        }
    }
}