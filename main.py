from core.printRanking import print_data
from core.record import Record
import serial
import time
name = input("닉네임을 입력하세요: ")
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
        inform = [name, data]
        print(inform)

       
        record.newRecord(inform)
        records = record.ranking
        print("새로운 기록이 추가되었습니다.")
        
        
        for temp_data in records:
            print_data(records.index(temp_data)+1,temp_data['name'],temp_data['result'])






