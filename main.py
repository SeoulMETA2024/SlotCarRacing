from core.printRanking import print_data
from core.record import Record
import serial
import time

record = Record()

# 시리얼 포트 연결
ser = serial.Serial(
    port='COM3',       # Windows는 'COM3', Linux는 '/dev/ttyACM0'
    baudrate=9600,     # 아두이노와 동일한 통신속도
    timeout=1          # 읽기 시간제한 1초
)

# 아두이노 리셋 대기
time.sleep(2)

while True:
    if ser.in_waiting > 0:  # 데이터가 있으면
        data = ser.readline().decode().strip()  # 데이터 읽기
        print(data)  # 받은 데이터 출력

        
        if record.add_record(records):
            print("새로운 기록이 추가되었습니다.")
        else:
            print("새로운 기록이 추가되지 않았습니다.")
        
        records = record.ranking
        for temp_data in records:
            print_data(temp_data)






