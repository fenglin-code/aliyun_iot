import time
from linkkit import linkkit
import serial


def on_connect(session_flag, rc, userdata):
    print("on_connect:%d,rc:%d,userdata:" % (session_flag, rc))
    pass


def on_disconnect(rc, userdata):
    print("on_disconnect:rc:%d,userdata:" % rc)


def on_thing_prop_post(self, request_id, code, data, message, userdata):
    print("on_thing_prop_post request id:%s, code:%d, data:%s message:%s" %
          (request_id, code, str(data), message))


def on_thing_prop_changed(params, userdata):
    number = str(('{0:0>3}'.format(params['DISPLAY']))).encode('utf-8')
    global value
    value = int(number)
    print(number)
    ser.write(bytes(number))
    pass


def get_cpu_temp():
    tempfile = open("/sys/class/thermal/thermal_zone0/temp")
    cpu_temp = tempfile.read()
    tempfile.close()
    return float(cpu_temp) / 1000


if __name__ == '__main__':
    lk = linkkit.LinkKit(
        host_name="cn-shanghai",
        product_key="a1f7IFloYwy",
        device_name="raspberrypi",
        device_secret="wIerQjDsvWuC6mEfh0mbx5mLJqn375j2")

    lk.on_disconnect = on_disconnect
    lk.on_connect = on_connect
    lk.on_thing_prop_post = on_thing_prop_post
    lk.thing_setup("tsl.json")
    lk.connect_async()
    lk.on_thing_prop_changed = on_thing_prop_changed

    global value
    value = 123

    while True:
        ser = serial.Serial('/dev/ttyAMA0', 115200)
        size = ser.inWaiting()

        if size != 0:
            response = ser.readline(9)
            ser.flushInput()

            if response is not None:
                c51_temp = round(float(response[:4]) / 100, 2)
                stm32_temp = round(float(response[4:9]), 2)
                pi_temp = round(get_cpu_temp(), 2)
                prop_data = dict(pi=pi_temp, c51=c51_temp, stm32=stm32_temp, DISPLAY=value)
                print(prop_data)
                try:
                    rc, request_id = lk.thing_post_property(prop_data)
                except Exception as e:
                    print('发生了异常：', e)