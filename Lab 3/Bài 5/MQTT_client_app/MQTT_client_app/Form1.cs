using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace MQTT_client_app
{
    public partial class MQTT_Client_Form : Form
    {
        MqttClient mqttClient;
        string mqtt_broker = "192.168.212.85";
        string[] topic = { "cl21/2/nhom2/dht/value" };
        byte[] QoS = { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE };
        String ClientID = "HaiTC";
        float temp_val = 0;
        float hum_val = 0;

        public MQTT_Client_Form()
        {
            InitializeComponent();
        }
        
        private void MqttClient_MqttMsgPublishReceived(object sender, uPLibrary.Networking.M2Mqtt.Messages.MqttMsgPublishEventArgs e) //callback
        {
            var jsonmessage = Encoding.UTF8.GetString(e.Message);
            DHT22_Value dht22_val = new DHT22_Value();
            dht22_val = JsonConvert.DeserializeObject<DHT22_Value>(jsonmessage);
            temp_val = dht22_val.Temperature;
            hum_val = dht22_val.Humidity;
            string message = "Temperature: " + temp_val.ToString() + "°C" + " Humidity: " + hum_val.ToString() + "%.";
            dht_val_tb.Invoke((MethodInvoker)(() => dht_val_tb.Text += message));
            dht_val_tb.Invoke((MethodInvoker)(() => dht_val_tb.Text += Environment.NewLine));
            dht_val_tb.Invoke((MethodInvoker)(() => dht_val_tb.SelectionStart = dht_val_tb.Text.Length));
            dht_val_tb.Invoke((MethodInvoker)(() => dht_val_tb.ScrollToCaret()));

            if (temp_val < 25 || temp_val > 27 || hum_val < 40 || hum_val > 70)
            {
                dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.Text += "Abnormal Detection"));
                dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.Text += Environment.NewLine));
                mqttClient.Publish("cl21/2/nhom2/dht/detected", Encoding.UTF8.GetBytes("Abnormal Detection"), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
            }
            else
            {
                dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.Text += "Normal Condition"));
                dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.Text += Environment.NewLine));
                mqttClient.Publish("cl21/2/nhom2/dht/detected", Encoding.UTF8.GetBytes("Normal Condition"), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
            }
            dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.SelectionStart = dht_detected_tb.Text.Length));
            dht_detected_tb.Invoke((MethodInvoker)(() => dht_detected_tb.ScrollToCaret()));
        }

        [Serializable]
        private class DHT22_Value
        {
            [JsonProperty("temperature")]
            public float Temperature { get; set; }
            [JsonProperty("humidity")]
            public float Humidity { get; set; }
        }

        private void Connect_Clk(object sender, EventArgs e)
        {
            Task.Run(() =>
            {
                mqttClient = new MqttClient(mqtt_broker); //broker's ip or hostname
                mqttClient.MqttMsgPublishReceived += MqttClient_MqttMsgPublishReceived; //set callback
                mqttClient.Subscribe(topic, QoS);
                mqttClient.Connect(ClientID);
                if(mqttClient.IsConnected)
                {
                    MessageBox.Show("Connected to MQTT broker successfully!");
                }
                else
                {
                    MessageBox.Show("Failed to connect to MQTT broker!");
                }
            });
        }
    }
}
