
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import serial
import time


app = FastAPI()

#allow all connections: Specify Ip address for security
origins = ['*']

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)




# Serial Object
# Arduino Communication
try:
    arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)  # Adjust port
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    arduino = None  # Handle the case where the port is not available

HS = 0  # Initialize Home Score
AS = 0  # Initialize Away Score

def write_read(hs, as_):
    if arduino is None:
        print("Serial port not available")
        return None
    data_to_send = f"{hs},{as_}\n"
    arduino.write(data_to_send.encode('utf-8'))
    time.sleep(0.05)
    try:
        data = arduino.readline().decode('utf-8').strip()
        return data
    except UnicodeDecodeError:
        return None #if there is a decoding error, just return none.

# Initialize timer values
minutes = 12
seconds = 0
timer_running = False
quarter = 1


class TimerData(BaseModel):
    minutes: int
    seconds: int
    timer_running: bool
    quarter: int

@app.get("/timer")
def get_timer():
    return TimerData(minutes=minutes, seconds=seconds, timer_running=timer_running, quarter=quarter)

@app.post("/timer")
def set_timer(timer_data: TimerData):
    global minutes, seconds, timer_running, quarter
    minutes = timer_data.minutes
    seconds = timer_data.seconds
    timer_running = timer_data.timer_running
    quarter = timer_data.quarter
    return {"message": "Timer updated"}


@app.get("/scores")
def get_scores():
    return {"home_score": HS, "away_score": AS}

@app.post("/home/{points}")
def add_home_points(points: int):
    global HS
    if points not in [1, 2, 3]:
        raise HTTPException(status_code=400, detail="Points must be 1, 2, or 3")
    HS += points
    result = write_read(HS, AS)
    if result:
        print("Received from Arduino:", result)
    return {"message": f"Added {points} points to Home. New Home Score: {HS}"}

@app.post("/away/{points}")
def add_away_points(points: int):
    global AS
    if points not in [1, 2, 3]:
        raise HTTPException(status_code=400, detail="Points must be 1, 2, or 3")
    AS += points
    result = write_read(HS, AS)
    if result:
        print("Received from Arduino:", result)
    return {"message": f"Added {points} points to Away. New Away Score: {AS}"}

@app.get("/reset")
def reset_scores():
    global HS,AS
    HS = 0
    AS = 0
    result = write_read(HS, AS)
    if result:
        print("Received from Arduino:", result)
    return {"message": "Scores reset to 0"}

print("FastAPI server started")

# Example usage (run with uvicorn main:app --reload):
# - GET /scores: Get current scores
# - POST /home/2: Add 2 points to Home
# - POST /away/3: Add 3 points to Away
# - GET /reset: reset scores to 0.
